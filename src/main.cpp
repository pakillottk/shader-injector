#include <cstdio>
#include <cassert>

#include "Args/ArgsParser.h"
#include "IO/FolderScanner/FolderScanner.h"

int main(int argc, char** argv)
{
    ShaderInjector::Args::cli_option_t options[2];
    options[0] = ShaderInjector::Args::defineProgramArg("d", "dummy", "This is a dummy option", true, false);
    options[1] = ShaderInjector::Args::defineProgramArg("v", "value", "This is an option that requires a value", false, true);

    ShaderInjector::Args::printUsage(*argv, 2, options);

    std::vector<ShaderInjector::shader_file_t> shaderFiles = ShaderInjector::IO::FolderScanner::scanFolder("test");

    printf("\nShaders found:\n");
    for(size_t i = 0; i < shaderFiles.size(); ++i)
    {
        printf("%s\n", shaderFiles[i].path.c_str());
    }

    return 0;
}