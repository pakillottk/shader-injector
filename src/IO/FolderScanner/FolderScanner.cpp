#include "FolderScanner.h"

#include <dirent.h>

using namespace ShaderInjector;
using namespace ShaderInjector::IO;

#define internal static

internal void findShadersInFolder(const std::string &folder, std::vector<shader_file_t> &shadersFound)
{
    // TODO
}

std::vector<shader_file_t> FolderScanner::scanFolder(const std::string &folder)
{
    std::vector<shader_file_t> shadersFound;

    // TODO

    return shadersFound;
}