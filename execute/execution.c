/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:34:37 by codespace         #+#    #+#             */
/*   Updated: 2022/12/18 14:54:50 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

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
            exit(1);
        }
        else
			wait(&(*table)->status);
    }
    else if((*cmd)->cmds->i_stream == -1 || (*cmd)->cmds->o_stream == -1)
		(*table)->status = 1;
    else if(v.binar == -2)
		(*table)->status = 127;
    else
		(*table)->status = 127;
	free((*cmd)->cmds->path);
    dup2(v.dupcopy, 0);
    dup2(v.dupcopy2, 1);
	print_err(table, cmd, &v);
    return ;
}

void	combined_execution(int pip, t_cmdline **cmd, t_table **table)
{
	(void)(pip);
	(void)(cmd);
	(void)(table);
}