#include <stdio.h>
#include "display_utils.h"
void display_help(size_t nb_opt, option opts[], char exec_name[])
{
    fprintf(stdout, "%s", exec_name);
    for(size_t i = 0 ; i < nb_opt ; i++)
    {
        opts[i].is_optional ? fprintf(stdout, "[") : 0;
        fprintf(stdout, "%s|%s", opts[i].small_opt, opts[i].long_opt);
        opts[i].is_optional ? fprintf(stdout, "]") : 0;
        fprintf(stdout, ":\n\t%s\n", opts[i].description);
    }
}