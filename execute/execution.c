/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:34:37 by codespace         #+#    #+#             */
/*   Updated: 2022/12/21 23:14:15 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

static void close_all_pipes(int pips[][2], int pip);

void	execution(t_cmdline **commands, t_table **table)
{
	int pip;

    if(commands && *commands)
    {
        pip = pipes(&((*table)->token));
        if (pip == 0)
            execute(commands, table);
        else if (pip > 0)
            combined_execution(pip, commands, table);
        else
            return ;
    }
}

void	execute(t_cmdline **cmd, t_table **table)
{
    t_vars  v;
    
	if(!cmd && !*cmd && !table && !*table)
		return ;
	else if((*cmd)->cmds->arguments == NULL)	
		return ;
    v.dupcopy = dup(0);
    v.dupcopy2 = dup(1);
    v.built = find_in((*cmd)->cmds->arg_pack[0], (*table)->reserved);
    v.binar = cmd_check((*cmd)->cmds, table);
	(*table)->status = 0;
	dup2((*cmd)->cmds->i_stream, 0);
    dup2((*cmd)->cmds->o_stream, 1);
    if(v.built != -1)
        (*table)->builtin[v.built](*cmd, *table);   
    else if(!v.binar && (*cmd)->cmds->i_stream != -1 && (*cmd)->cmds->o_stream != -1)
    {
        (*cmd)->cmds->pid = fork(); 
        if((*cmd)->cmds->pid == 0)
        {
			(*table)->minienv = create_envp(&(*table)->env);
           execve((*cmd)->cmds->path, (*cmd)->cmds->arg_pack, (*table)->minienv);
        }
        else
	    {
			wait(&(*table)->status);
			if(WIFEXITED((*table)->status))
				(*table)->status = WEXITSTATUS((*table)->status);
			else if(WIFSIGNALED((*table)->status))
				(*table)->status = WTERMSIG((*table)->status);
			else if(WIFSTOPPED((*table)->status))
				(*table)->status = WIFSTOPPED((*table)->status);
	    }
    }	
    else if((*cmd)->cmds->i_stream == -1 || (*cmd)->cmds->o_stream == -1)
    {
		(*table)->status = 1;
        printf("%s%s%s", SHELLERR, (*cmd)->cmds->err, FILEERR); // no such file or direcotry
    }
    else if(v.binar == -2)
    {
		(*table)->status = 127;
        printf("%s%s%s", SHELLERR, (*cmd)->cmds->arg_pack[0], FILEERR); // no such file or direcotry
    }
    else
    {
		(*table)->status = 127;
        printf("%s%s%s", SHELLERR, (*cmd)->cmds->arg_pack[0], COMMANDERR); // command not found
    }
    dup2(v.dupcopy, 0);
    dup2(v.dupcopy2, 1);
    return ;
}

void	combined_execution(int pip, t_cmdline **cmd, t_table **table)
{
    t_vars v;
    int i;
    int (*pips)[2];

    pips = malloc(sizeof(*pips) * pip);
    if(!pips)
        return ;
    i = -1;
    while(++i < pip)
        pipe(pips[i]);
    i = 0;
    while((*cmd)->cmds != NULL)
    {
        v.built = find_in((*cmd)->cmds->arg_pack[0], (*table)->reserved);
        v.binar = cmd_check((*cmd)->cmds, table);
        (*cmd)->pid = fork();
        if((*cmd)->pid == 0)
        {
            if(i == 0)
            {
                dup2(pips[i][1], (*cmd)->cmds->o_stream);
                close_all_pipes(pips, pip);
            }
            else if(i > 0 && i < pip)
            {
                dup2(pips[i-1][0], (*cmd)->cmds->i_stream);
                dup2(pips[i][1], (*cmd)->cmds->o_stream);
                close_all_pipes(pips, pip);
            }
            else
            {
                dup2(pips[i-1][0], (*cmd)->cmds->i_stream);
                close_all_pipes(pips, pip);
            }

            if(v.built != -1)
                (*table)->builtin[v.built](*cmd, *table);
            else if(v.binar != -1)
            {
                (*table)->minienv = create_envp(&(*table)->env);
                execve((*cmd)->cmds->path, (*cmd)->cmds->arg_pack, (*table)->minienv);
                printf("%s%s%s", SHELLERR, (*cmd)->cmds->arg_pack[0], COMMANDERR); // command not found
            }
            else if((*cmd)->cmds->i_stream == -1 || (*cmd)->cmds->o_stream == -1)
            {
                (*table)->status = 1;
                printf("%s%s%s", SHELLERR, (*cmd)->cmds->err, FILEERR); // no such file or direcotry
            }
            else if(v.binar == -2)
            {
                (*table)->status = 127;
                printf("%s%s%s", SHELLERR, (*cmd)->cmds->arg_pack[0], FILEERR); // no such file or direcotry
            }
            else
            {
                (*table)->status = 127;
                printf("%s%s%s", SHELLERR, (*cmd)->cmds->arg_pack[0], COMMANDERR); // command not found
            }
            exit(1);
        }
        i++;
        v.let++;
        (*cmd)->cmds = (*cmd)->cmds->next;
    }
    if((*cmd)->pid != 0)
    {
        int a = -1;
        while(++a < pip)
        {
            close(pips[a][1]);
            close(pips[a][0]);
        }
        while(v.let--)
            wait(&(*table)->status);
    }
}

static void close_all_pipes(int pips[][2], int pip)
{
    int a;

    a = -1; 
    while(++a < pip)
    {
        close(pips[a][1]);
        close(pips[a][0]);
    }
}

// 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
