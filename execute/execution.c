/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:34:37 by codespace         #+#    #+#             */
/*   Updated: 2022/12/13 11:56:23 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

static void	execute(t_cmdline **cmd, t_table **table);
static void	combined_execution(int pip, t_cmdline **cmd, t_table **table);

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

static void execute(t_cmdline **cmd, t_table **table)
{
    t_vars  v;
    
	if(!cmd && !*cmd && !table && !*table)
		return ;
	else if((*cmd)->cmds->arguments == NULL)	
		return ;
    v.dupcopy = dup(0);
    v.dupcopy2 = dup(1);
    v.built = find_in((*cmd)->cmds->arg_pack[0], (*table)->reserved);
    v.binar = cmd_check((*cmd)->cmds, (*table)->paths);
	dup2((*cmd)->cmds->i_stream, 0);
    dup2((*cmd)->cmds->o_stream, 1);
    if(v.built != -1)
        (*table)->builtin[v.built]((*cmd)->cmds, *table);
    else if(!v.binar && (*cmd)->cmds->i_stream != -1 && (*cmd)->cmds->o_stream != -1)
    {
        (*cmd)->cmds->pid = fork(); 
        if((*cmd)->cmds->pid == 0)
        {
            execve((*cmd)->cmds->path, (*cmd)->cmds->arg_pack, (*table)->minienv);
            exit(1);
        }
        else
            waitpid(-1, 0, 0);
    }
    else if((*cmd)->cmds->i_stream == -1 || (*cmd)->cmds->o_stream == -1)
        printf("%s%s%s", SHELLERR, (*cmd)->cmds->err, FILEERR);
    else if(v.binar == -2)
        printf("%s%s%s", SHELLERR, (*cmd)->cmds->arg_pack[0], FILEERR);
    else
        printf("%s%s%s", SHELLERR, (*cmd)->cmds->arg_pack[0], COMMANDERR);
    dup2(v.dupcopy, 0);
    dup2(v.dupcopy2, 1);
    return ;
}

static void combined_execution(int pip, t_cmdline **cmd, t_table **table)
{
  
}