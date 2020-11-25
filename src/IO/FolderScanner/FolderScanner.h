#pragma once
#ifndef FOLDER_SCANNER_H

#include <string>
#include <vector>

#include "../../Shaders/ShaderTypes.h"

namespace ShaderInjector { namespace IO { namespace FolderScanner {
    
    // returns all shader files found in a folder (scan is recursive)
    std::vector<shader_file_t> scanFolder(const std::string &folder);

}}}

#endif // FOLDER_SCANNER_H