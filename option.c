#include <stdlib.h>
#include <string.h>
#include "option.h"
#include "hash_map.h"
#include "simple_linked_list.h"
#include "display_utils.h"

static hash_map* option_map = NULL; //Map of all options
static hash_map* arg_map = NULL; //map of arg passed to the programme
static option* opts_t = NULL; //structure of options
static size_t option_size = 0; //size of all options

static void set_opt(option* opts,  
            char small_opt[3],
            char long_opt[30],
            char description[200],
            uint8_t is_optional,
            enum opts_type opt_arg);
static void parse_opt(int argc, char* argv[]);
static inline uint8_t is_a_arg(char* arg);
static uint8_t free_list(simple_linked_list* list);

static inline uint8_t is_a_arg(char* arg)
{
    return (arg[0] == '-');
}

static uint8_t free_option(option* opt)
{
    free(opt->long_opt);
    free(opt->description);
    return 1;
}

static void set_opt(option* opts,  
            char small_opt[3],
            char long_opt[30],
            char description[200],
            uint8_t is_optional,
            enum opts_type opt_arg)
{
    static size_t current_idx = 0;
    if(opts == NULL) return;
    option* opt = &(opts[current_idx]);
    size_t long_opt_size = strnlen(long_opt, 30)+1;
    size_t description_size = strnlen(description, 200)+1;
    opt->long_opt = calloc(long_opt_size, sizeof(char));
    opt->description = calloc(description_size, sizeof(char));
    strncpy(opt->small_opt, small_opt, 3);
    strncpy(opt->long_opt, long_opt, long_opt_size);
    strncpy(opt->description, description, description_size);
    opt->is_optional = is_optional;
    opt->opt_arg = opt_arg;
    create_or_add_hash_map_str(&option_map, small_opt, 0, opt, 0, (uint8_t (*)(void*))free_option);
    create_or_add_hash_map_str(&option_map, long_opt, 0, opt, 0, NULL);
    current_idx++;
}
//TODO Modifier hash map !
static void parse_opt(int argc, char* argv[])
{
    char* current_arg = NULL;
    char* last_arg = NULL;
    enum opts_type expected_args = NONE;
    simple_linked_list* list = NULL;
    for(int i = 1 ; i < argc ; i++)
    {
        current_arg = argv[i];
        if(is_a_arg(current_arg))
        {
            if(expected_args == NONE)
            {
                option* opt = get_hash_map_str(option_map, current_arg);
                if(opt != NULL)
                {
                    create_or_add_hash_map_str(&arg_map, current_arg, 0, NULL, 0, NULL);
                    expected_args = opt->opt_arg;
                    last_arg = current_arg;
                    if (expected_args == NONE)
                    {
                        uint8_t tmp = 1;
                        modify_hash_map_str_auto(arg_map, last_arg, sizeof(uint8_t), &tmp); //boolean
                    }
                } else {
                    //arg does not exist
                    display_help(option_size, opts_t, argv[0]);
                    return;
                }
            } else {
                //unexpected arg
                display_help(option_size, opts_t, argv[0]);
                return;
            }
        }
        else if(expected_args == NONE && last_arg == NULL)
        {
            //unexpected arg
            display_help(option_size, opts_t, argv[0]);
            return;
        }
        else if(expected_args == UNIQUE)
        {
            modify_hash_map_str_auto(arg_map, last_arg, strlen(current_arg)+1, current_arg);
            expected_args = NONE;
        }
        else 
        {
            size_t arg_size = strlen(current_arg)+1;
            char *tmp = calloc(arg_size, sizeof(char));
            strncpy(tmp, current_arg, arg_size);
            coa_simple_linked_list(&list, tmp);
            modify_hash_map_str(arg_map, last_arg, 0, list, 0, 0, (uint8_t (*)(void*))free_list);
            if((i+1) < argc)
            {
                if(is_a_arg(argv[i+1]))
                    expected_args = NONE;
            }
        }
    }
}

static uint8_t free_list(simple_linked_list* list)
{
    simple_linked_list* next = NULL;
    for(;list != NULL;)
    {
        free(list->data);
        next = list->next;
        free(list);
        list = next;
    }
    return 1;
}

void init_opt(int argc, char* argv[])
{
    option_size = 2;
    opts_t = calloc(option_size, sizeof(option));
    set_opt(opts_t, "-f", "--filename",
            "File to encrypt or decrypt", 0, MULTIPLE);
    set_opt(opts_t, "-g", "--genkey",
            "generate a key of [number] size", 0, UNIQUE);
    parse_opt(argc,argv);
}

void free_option_all(void)
{
    free_hash_map(option_map);
    free(opts_t);
    free_hash_map(arg_map);
}
