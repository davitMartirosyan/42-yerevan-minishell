
#ifndef MINISHELL_HEADER_H
#define MINISHELL_HEADER_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_envkeys
{
    char *key;
    char *val;
    struct s_envkeys *next;
} t_envkeys;

#include "../libft/libft.h"
#include "./lex.h"
#include "./env.h"
#include "./utilities.h"

#endif