/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 01:32:43 by dmartiro          #+#    #+#             */
/*   Updated: 2022/11/03 18:52:57 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

t_cmds *parsing(t_tok **token, t_table *table, int count, char **envp);
static char **args(t_tok **tokens);
static int  typeis_arg(int type);
static void put_arg(char *arg_place, char *arg);
static int count_arguments(t_tok **tokens);


t_cmds *parsing(t_tok **token, t_table *table, int count, char **envp)
{
    int arg_count;
    t_cmds *cmds;
    /*
    cmds -> pid_t   pid;
    cmds -> int     i_stream;
    cmds -> int     o_stream;
    cmds -> char    *cmd;
    cmds -> char    **arg_pack;
    cmds -> char    *path;
    cmds -> char    **env;
    cmds -> struct  s_cmds *next;
    */
   
    
    cmds = malloc(sizeof(t_cmds));
    if(!cmds)
        return (NULL);
    arg_count = 0;
    cmds->arg_pack = malloc(sizeof(char *) * (count + 1));
    while((*token)->type != PIPE)
    {
        if(typeis_arg((*token)->type))
        {
            count++;
            token = &(*token)->next;
        }
        token = &(*token)->next;
    }
    return (NULL);
}

t_cmds *parse_tree(t_table *table, char **envp)
{
    int     cout;
	t_tok   *from;
    t_cmds  *cmds;

    from = table->token;
    if(from != NULL)
    {
        cout = count_arguments(&from);
        if(cout)
            cmds = parsing(&from, table, cout, envp);
    }
    else
        printf("There are no argumetns\n");
    return (NULL);
}

static int count_arguments(t_tok **tokens)
{
    int count;

    count = 0;
    while((*tokens) != NULL)
    {
        if(typeis_arg((*tokens)->type))
            count++;
        tokens = &(*tokens)->next;
    }
    return (count);
}

static int typeis_arg(int type)
{
    if(type == WORD || type == EXP_FIELD)
        return (1);
    return (0);
}

static char **args(t_tok **tokens)
{
    t_tok *tmp;
    int cout;
    char **arguments;
    int i;
    
    cout = 0;
    tmp = (*tokens);
    while(tmp != NULL)
    {
        if(typeis_arg(tmp->type))
            cout++;
        tmp = tmp->next;
    }
    if(cout == 0)
        return (NULL);
    arguments = malloc(sizeof(char *) * (cout + 1));
    i = 0;
    while(*tokens != NULL)
    {
        if(typeis_arg((*tokens)->type))
        {
            arguments[i] = malloc(sizeof(char) * ((*tokens)->len + 1));
            put_arg(arguments[i], (*tokens)->tok);
            i++;
        }
        (*tokens) = (*tokens)->next;
    }
    arguments[i] = '\0';
    return (arguments);
}

static void put_arg(char *arg_place, char *arg)
{
    int i;
    int len;

    len = ft_strlen(arg);
    i = 0;
    while(i < len)
    {
        arg_place[i] = arg[i];
        i++;
    }
    arg_place[i] = '\0';
}