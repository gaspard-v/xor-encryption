#include <stdlib.h>
#include <string.h>
#include "option.h"
#include "hash_map.h"

static hash_map* option_map = NULL;
static hash_map* arg_map = NULL;
static option* opts_t = NULL;
static size_t option_size = 0;

static void set_opt(option* opts,  
            char small_opt[3],
            char long_opt[30],
            char description[200],
            uint8_t is_optional,
            uint8_t opt_arg);
static void parse_opt(int argc, char* argv[]);
static inline uint8_t is_a_arg(char* arg);

static inline uint8_t is_a_arg(char* arg)
{
    return (arg[0] == '-');
}

static void set_opt(option* opts,  
            char small_opt[3],
            char long_opt[30],
            char description[200],
            uint8_t is_optional,
            uint8_t opt_arg)
{
    static size_t current_idx = 0;
    if(opts == NULL) return;
    option* opt = &(opts[current_idx]);
    size_t long_opt_size = strnlen(long_opt, 30);
    size_t description_size = strnlen(description, 200);
    opt->long_opt = calloc(long_opt_size, sizeof(char));
    opt->description = calloc(description_size, sizeof(char));
    strncpy(opt->small_opt, small_opt, 3);
    strncpy(opt->long_opt, long_opt, long_opt_size);
    strncpy(opt->description, description, description_size);
    opt->is_optional = is_optional;
    opt->opt_arg = opt_arg;
    create_or_add_hash_map_str(&option_map, small_opt, opt);
    create_or_add_hash_map_str(&option_map, long_opt, opt);
    current_idx++;
}

static void parse_opt(int argc, char* argv[])
{
    uint8_t nb_excpeted_arg = 0;
    char* last_argv = NULL;
    size_t idx = 1;

    char** mult_args = NULL;
    size_t nb_mult_args = 0;
    for(int i = 0 ; i < argc ; i++)
    {
        if(is_a_arg(argv[i])) {
            option* opt = (option*)get_hash_map_str(option_map, argv[i]);
            if(opt == NULL)
            {
                printf("\"%s\" n'existe pas !", argv[i]);
                return;
            }
            nb_excpeted_arg = opt->opt_arg;
            if(nb_excpeted_arg == 0)
            {
                create_or_add_hash_map_str(&arg_map, opt->small_opt, (void*)1);
            } else if (nb_excpeted_arg > 1) {
                nb_mult_args++;
                mult_args = calloc(nb_mult_args, sizeof(char*));
                create_or_add_hash_map_str(&arg_map, opt->small_opt, (void*)mult_args);
            }
            last_argv = opt->small_opt;
            continue;
        }
        if(nb_excpeted_arg == 1) {
            char* tmp = calloc(strlen(argv[i]) + 1, sizeof(char));
            create_or_add_hash_map_str(&arg_map, last_argv, (void*)tmp);
        } else {
            
        }
    }
}

void init_opt(void)
{
    option_size = 2;
    opts_t = calloc(option_size, sizeof(option));
    set_opt(opts_t, "-f", "--filename",
            "File to encrypt or decrypt", 0, 2);
    set_opt(opts_t, "-g", "--genkey",
            "generate a key of [number] size", 0, 1);
}

void delete_opt(void)
{
    for(size_t i = 0 ; i < option_size ; i++)
    {
        free(opts_t[i].description);
        free(opts_t[i].long_opt);
    }
    free(opts_t);
}
