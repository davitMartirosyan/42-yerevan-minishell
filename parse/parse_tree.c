/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 01:32:43 by dmartiro          #+#    #+#             */
/*   Updated: 2022/11/07 20:25:25 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

t_cmdline   *parsing(t_tok **token, t_table *table, int count, char **envp);

static char **args(t_tok **tokens);
static void put_arg(char *arg_place, char *arg);


static void collect_args(t_tok **token, t_cmds *cmd);
static int  arguments(t_tok **tokens);
static int  pipes(t_tok *tokens);

static int  typeis_arg(int type);
static int  typeis_redirection(int type);

t_cmdline *parsing(t_tok **token, t_table *table, int count, char **envp)
{
    int pipe_count;
    t_cmdline   *commands;
    t_cmds      *cmds;
    
    pipe_count = pipes(*token) + 1;
    cmds = malloc(sizeof(t_cmds));
    if(!cmds)
        return (NULL);
        printf("%d\n", pipe_count);
    while(*token != NULL && pipe_count)
    {
        if(*token && typeis_arg((*token)->type))
        {
            collect_args(token, cmds);
            continue;
        }
        pipe_count--;
    }
    return (NULL);
}


void collect_args(t_tok **token, t_cmds *cmd)
{
    int count_args;

    count_args = arguments(token);
    printf("%d\n", count_args);
}

int pipes(t_tok *tokens)
{
    int pip;

    pip = 0;
    while(tokens != NULL)
    {
        if(tokens->type == PIPE)
            pip++;
        tokens = tokens->next;
    }
    return (pip);
}


static int arguments(t_tok **tokens)
{
    int count;

    count = 0;
    while((*tokens) != NULL)
    {
        if(typeis_arg((*tokens)->type))
            count++;
        if((*tokens)->type == PIPE)
            break;
        if(typeis_redirection((*tokens)->type))
            break;
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

static int typeis_redirection(int type)
{
    if(type == REDIR_IN || type == REDIR_OUT || type == APPEND \
        type == HEREDOC)
        return (1);
    return (0);
}



t_cmds *parse_tree(t_table *table, char **envp)
{
    int     cout;
	t_tok   *from;
    t_cmdline *commands;

    from = table->token;
    if(from != NULL)
    {
        // commands = parsing(&from, table, cout, envp);
        cout = arguments()
    }
    return (NULL);
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