#pragma once
#ifndef ARGS_PARSER_H

#include <string>

namespace ShaderInjector { namespace Args  {

    /**
    * Possible program invokation argument
    */
    struct cli_option_t
    {
        bool isRequired;

        // key for -flag format
        std::string flag;
        // key for --option format
        std::string option;
        
        std::string description;

        // When false, only the definition of the -flag or --option is taken into account
        bool requiresValue;

        // true if option was found in parsed args
        bool defined;
        // value found in parsed args
        std::string value;
    };

    cli_option_t defineProgramArg(const std::string &flag, const std::string &option, const std::string &description, bool isRequired, bool requiresValue);

    void printUsage(const std::string &programName, int optc, cli_option_t *optv);

    // false when some unexpected token found or a required option was missing
    bool parseProgramArgs(int argc, char** argv, int optc, cli_option_t *optv);

}}

#endif // ARGS_PARSER_H