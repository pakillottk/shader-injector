#include "ArgsParser.h"

#include <cstring>

using namespace ShaderInjector;

#define internal static

internal void clearOptions(int optc, ShaderInjector::Args::cli_option_t *optv)
{
    for(int i = 0; i < optc; ++i)
    {
        optv[i].defined = false;
        optv[i].value = "";
    }
}

Args::cli_option_t Args::defineProgramArg(const std::string &flag, const std::string &option, const std::string &description, bool isRequired, bool requiresValue)
{
    cli_option_t opt = {};

    opt.flag = flag;
    opt.option = option;
    opt.description = description;

    opt.isRequired = isRequired;
    opt.requiresValue = requiresValue;

    return opt;
}

internal inline void printOption(const Args::cli_option_t *opt)
{
    printf("--%s, -%s: %s\n", opt->option.c_str(), opt->flag.c_str(), opt->description.c_str());
}

void Args::printUsage(const std::string &programName, int optc, Args::cli_option_t *optv)
{
    std::string optionsRequired;
    std::string optionsOptional;
    
    for(int i = 0; i < optc; ++i)
    {
        const Args::cli_option_t *opt = optv + i;

        std::string optionStr = "--" + opt->option;
        if(opt->requiresValue)
        {
            optionStr += " <value>";
        }

        if(i < optc - 1)
        {
            optionStr += " ";
        }

        if(opt->isRequired)
        {
            optionsRequired += optionStr;
        }
        else
        {
            optionsOptional += optionStr;
        }
    }

    if(optionsRequired.size() > 0)
    {
        optionsRequired = optionsRequired.substr(0, optionsRequired.size() - 1);
    }

    if(optionsOptional.size() > 0)
    {
        optionsOptional = "( " + optionsOptional + " )";
    }

    printf("\nUsage: %s %s %s\n", programName.c_str(), optionsRequired.c_str(), optionsOptional.c_str());

    printf("\nRequired:\n");
    for(int i = 0; i < optc; ++i)
    {
        const Args::cli_option_t *opt = optv + i;
        if(opt->isRequired)
        {
            printOption(opt);
        }
    }

    printf("\nOptional:\n");
    for(int i = 0; i < optc; ++i)
    {
        const Args::cli_option_t *opt = optv + i;
        if(!opt->isRequired)
        {
            printOption(opt);
        }
    }
}

enum OPTION_ID_FIELDS
{
    kFlag = 0,
    kOption
};

internal Args::cli_option_t* findOption(int optc, Args::cli_option_t *optv, OPTION_ID_FIELDS idField, const std::string &id)
{
    for(int i = 0; i < optc; ++i)
    {
        Args::cli_option_t *opt = optv + i;
        switch (idField)
        {
            case kFlag:
                if( id.find(opt->flag) != std::string::npos )
                {
                    return opt;
                }
            break;
        
            case kOption:
                if( id.find(opt->option) != std::string::npos )
                {
                    return opt;
                }
            break;

            default:
                return nullptr;
        }
    }

    return nullptr;
}

// false when some unexpected token found or a required option was missing
bool Args::parseProgramArgs(int argc, char** argv, int optc, cli_option_t *optv)
{
    clearOptions(optc, optv);

    for(int i = 0; i < argc; ++i)
    {
        std::string arg(argv[i]);

        if(arg.size() > 1)
        {
            if(arg[0] == '-')
            {
                cli_option_t *opt = nullptr;

                // could be a flag or an option
                if(arg[1] == '-')
                {
                    // is an option
                    opt = findOption(optc, optv, kOption, arg);
                }
                else
                {
                    // is a flag
                    opt = findOption(optc, optv, kFlag, arg);
                }

                if( opt == nullptr )
                {
                    // is not a valid arg
                    continue;
                }

                // option defined
                opt->defined = true;
                
                if( opt->requiresValue )
                {
                    if( i >= (argc - 1) )
                    {
                        return false;
                    }

                    // only valid if theres a non empty value
                    opt->value = argv[++i];
                    if( opt->value.size() == 0 )
                    {
                        return false;
                    }
                }
            }
        }       
    }

    for(int i = 0; i < optc; ++i)
    {
        if(optv[i].isRequired && !optv[i].defined)
        {
            return false;
        }
    }

    return true;
}