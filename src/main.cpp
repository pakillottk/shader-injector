#include <cstdio>
#include <cassert>

#include "Args/ArgsParser.h"

static void clearOptions(int optc, ShaderInjector::Args::cli_option_t *optv)
{
    for(int i = 0; i < optc; ++i)
    {
        optv[i].defined = false;
        optv[i].value = "";
    }
}

int main(int argc, char** argv)
{
    ShaderInjector::Args::cli_option_t options[2];
    options[0] = ShaderInjector::Args::defineProgramArg("d", "dummy", "This is a dummy option", true, false);
    options[1] = ShaderInjector::Args::defineProgramArg("v", "value", "This is an option that requires a value", false, true);

    char* fakeArgs1[] = 
    {
        "-d",
        "-v",
        "someValue"
    };
    assert(ShaderInjector::Args::parseProgramArgs(3, fakeArgs1, 2, options));
    clearOptions(2, options);

    char* fakeArgs2[] = 
    {
        "--dummy"
    };
    assert(ShaderInjector::Args::parseProgramArgs(1, fakeArgs2, 2, options));
    clearOptions(2, options);

    char* fakeArgs3[] = 
    {
        "-d",
        "--value"
    };
    assert(!ShaderInjector::Args::parseProgramArgs(2, fakeArgs3, 2, options));
    clearOptions(2, options);

    char* fakeArgs4[] = 
    {
        "-v",
        "someValue"
    };
    assert(!ShaderInjector::Args::parseProgramArgs(2, fakeArgs4, 2, options));
    clearOptions(2, options);

    return 0;
}