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

    /**
    * Shader file found in the filesystem
    */
    struct shader_file_t
    {
        SHADER_PROGRAM_TYPES type;
        std::string path;
    };
    
    /**
    * Shader program files composed by: 
    * a vertex file, a fragment file and a geometry file
    */
    struct shader_program_t
    {
        shader_file_t *vertexProgramFile;
        shader_file_t *fragmentProgramFile;
        shader_file_t *geometryProgramFile;
    };
}

#endif // SHADER_TYPES_H