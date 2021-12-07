#include <stdlib.h>
#include <string.h>
#include "option.h"
#include "hash_map.h"
#include "simple_linked_list.h"

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
    create_or_add_hash_map_str(&option_map, small_opt, 0, opt, 1, 0);
    create_or_add_hash_map_str(&option_map, long_opt, 0, opt, 1, 0);
    current_idx++;
}

static void parse_opt(int argc, char* argv[])
{
    char* current_arg = NULL;
    char* last_arg = NULL;
    uint8_t expected_args = 0;
    simple_linked_list* list = NULL;
    for(int i = 1 ; i < argc ; i++)
    {
        current_arg = argv[i];
        if(is_a_arg(current_arg))
        {
            if(!expected_args)
            {
                option* opt = get_hash_map_str(option_map, current_arg);
                if(opt != NULL)
                {
                    create_or_add_hash_map_str(&arg_map, current_arg, 0, NULL, 0, 0);
                    expected_args = opt->opt_arg;
                    last_arg = current_arg;
                } else {
                    //arg doe not exist
                }
            } else {
                //unexpected arg
            }
        }
        else if(expected_args == 0 && last_arg == NULL)
        {
            //unexpected arg
        }
        else if(expected_args == 0)
        {
            uint8_t tmp = 1;
            modify_hash_map_str_auto(arg_map, last_arg, sizeof(uint8_t), (void*)(&tmp)); //boolean
        }
        else if(expected_args == 1)
        {
            modify_hash_map_str_auto(arg_map, last_arg, strlen(current_arg), current_arg);
            expected_args = 0;
        }
        else 
        {
            coa_simple_linked_list(&list, current_arg);
            modify_hash_map_str(arg_map, last_arg, 0, list, 1, 0, 0);
            if((i+1) < argc)
            {
                if(is_a_arg(argv[i+1]))
                    expected_args = 0;
            }
        }
    }
}

void init_opt(int argc, char* argv[])
{
    option_size = 2;
    opts_t = calloc(option_size, sizeof(option));
    set_opt(opts_t, "-f", "--filename",
            "File to encrypt or decrypt", 0, 2);
    set_opt(opts_t, "-g", "--genkey",
            "generate a key of [number] size", 0, 1);
    parse_opt(argc,argv);
}

void free_opt(void)
{
    for(size_t i = 0 ; i < option_size ; i++)
    {
        free(opts_t[i].description);
        free(opts_t[i].long_opt);
    }
    free(opts_t);
}
