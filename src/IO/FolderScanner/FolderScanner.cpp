#include "FolderScanner.h"

#include <cstring>

#ifdef _MSC_VER
    // NOTE(pgm) On MSVC theres no dirent.h, we resort to this header file to
    // maintain compatibility
    #include "../../vendor/dirent/dirent.h"
#else
    #include <dirent.h>
#endif //_MSC_VER

using namespace ShaderInjector;
using namespace ShaderInjector::IO;

#define internal static
#define global_variable static

#ifdef _WIN32
    global_variable const char PATH_SEPARATOR = '\\';
#else
    global_variable const char PATH_SEPARATOR = '/';
#endif //_WIN32

global_variable const size_t SHADER_PROGRAM_EXTENSIONS_COUNT = 3;

// one value per type
global_variable const char* SHADER_PROGRAM_EXTENSIONS[SHADER_PROGRAM_EXTENSIONS_COUNT] = 
{
    ".vert", // vertex
    ".frag", // fragment
    ".geom" // geometry
};

// returns false if file is not a shader file
internal bool getShaderFileData(std::string filepath, shader_file_t &shaderFileData)
{
    std::string ext;
    for(size_t i = filepath.size() - 1; i >= 0 && i < filepath.size(); --i)
    {
        ext = ((char)tolower(filepath[i])) + ext;
        if(filepath[i] == '.')
        {
            break;
        }
    }

    // checks if its a valid shader file extension
    for(size_t i = 0; i < SHADER_PROGRAM_EXTENSIONS_COUNT; ++i)
    {
        const char *shaderExt = SHADER_PROGRAM_EXTENSIONS[i];
        if(strcmp(shaderExt, ext.c_str()) == 0)
        {
            // valid shader file found
            shaderFileData.type = (SHADER_PROGRAM_TYPES)i;
            shaderFileData.path = filepath;

            return true;
        }
    }

    // not a valid shader file
    return false;
}

internal void findShadersInFolder(const std::string &folder, std::vector<shader_file_t> &shadersFound, bool recursive)
{
    std::vector<std::string> subfolders;

    DIR *dir = opendir(folder.c_str());
    if( !dir )
    {
        return;
    }

    shader_file_t shaderData = {};
    dirent *file;
    while( (file = readdir(dir)) != NULL )
    {
        if( strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0 )
        {
            continue;
        }

        switch( file->d_type )
        {
            case DT_DIR:
                subfolders.push_back(folder + PATH_SEPARATOR + file->d_name);
            break;

            case DT_REG:
                if( getShaderFileData(folder + PATH_SEPARATOR + file->d_name, shaderData) )
                {
                    shadersFound.push_back(shaderData);
                }
            break;
        
            default:
                continue;
        }
    }

    closedir(dir);

    if( recursive )
    {
        for(size_t i = 0; i < subfolders.size(); ++i)
        {
            findShadersInFolder(subfolders[i], shadersFound, true);   
        }
    }
}

std::vector<shader_file_t> FolderScanner::scanFolder(const std::string &folder)
{
    std::vector<shader_file_t> shadersFound;

    findShadersInFolder(folder, shadersFound, true);

    return shadersFound;
}