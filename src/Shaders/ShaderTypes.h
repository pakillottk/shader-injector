#pragma once
#ifndef SHADER_TYPES_H

namespace ShaderInjector {

    // supported shader programs
    enum SHADER_PROGRAM_TYPES
    {
        kVertex = 0,
        kFragment = 1,
        kGeometry = 2
    };

    // one value per type
    const char* SHADER_PROGRAM_EXTENSIONS[] = 
    {
        ".vert", // vertex
        ".frag", // fragment
        ".geom" // geometry
    };

    /**
    * Shader file found in the filesystem
    */
    struct shader_file_t
    {
        SHADER_PROGRAM_TYPES type;
        std::string path;
    };
    
}

#endif // SHADER_TYPES_H