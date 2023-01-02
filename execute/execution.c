/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   execution.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: dmartiro <dmartiro@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/11/26 20:34:37 by codespace		 #+#	#+#			 */
/*   Updated: 2022/12/19 10:37:09 by dmartiro		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell_header.h"

void	execution(t_cmdline **commands, t_table **table)
{
	int pip;

	if (commands && *commands)
	{
		pip = pipes(&((*table)->token));
		if (pip == 0)
			execute(*commands, *table);
		else if (pip > 0)
			piping_execution(pip, *commands, *table);
	}
}

void	execute(t_cmdline *cmd, t_table *table)
{
	t_vars v;

	if (!cmd->cmds->arg_pack)
		return;
	table->status = 0;
	table->dup0 = dup(0);
	table->dup1 = dup(1);
	v.built = find_in(cmd->cmds->arg_pack[0], table->reserved);
	v.binar = cmd_check(cmd->cmds, table);
	dup2(cmd->cmds->i_stream, 0);
	dup2(cmd->cmds->o_stream, 1);
	_execute(&v, cmd, table);
	dup2(table->dup0, 0);
	dup2(table->dup1, 1);
	close(table->dup0);
	close(table->dup1);
}

void	_execute(t_vars *v, t_cmdline *cmd, t_table *table)
{
	if (v->built != -1)
		table->builtin[v->built](cmd->cmds, table);
	else if (v->binar != -1)
	{
		signal(SIGINT, SIG_IGN);
		cmd->cmds->pid = fork();
		if (cmd->cmds->pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			table->minienv = create_envp(&table->env);
			execve(cmd->cmds->path, cmd->cmds->arg_pack, table->minienv);
			exit(0);
		}
		else
			handle_status__and_wait(&table->status);
	   ft_signal(0);
	}
	else if(cmd->cmds->i_stream == -1)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(cmd->cmds->patherr, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	else if(v->binar == -1)
	{
		ft_putstr_fd("-sadm: ", STDERR_FILENO);
		ft_putstr_fd(cmd->cmds->arg_pack[0], STDERR_FILENO);
		ft_putstr_fd(": Command not found\n", STDERR_FILENO);
	}
}

void	piping_execution(int pip, t_cmdline *cmd, t_table *table)
{
	t_vars v;
	t_cmds *cmds;
	int (*pip_ptr)[2];
	int i;
	int ccount;

	cmds = cmd->cmds;
	table->status = 0;
	pip_ptr = malloc(sizeof(*pip_ptr) * pip);
	if (!pip_ptr)
		return ;
	i = -1;
	while (++i < pip)
		pipe(pip_ptr[i]);
	i = 0;
	ccount = 0;
	while (cmds != NULL)
	{
		if (!cmds->arg_pack)
		{
			cmds = cmds->next;
			continue;
		}
		v.built = find_in(cmds->arg_pack[0], table->reserved);
		v.binar = cmd_check(cmds, table);
		cmds->pid = fork();
		if (cmds->pid == 0)
		{
			dup2(cmds->i_stream, STDIN_FILENO);
			dup2(cmds->o_stream, STDOUT_FILENO);
			piping(cmds, pip_ptr, i, pip);
			if (v.built != -1)
				table->builtin[v.built](cmds, table);
			else if (v.binar != -1 && cmds->i_stream != -1)
			{
				table->minienv = create_envp(&table->env);
				if (execve(cmds->path, cmds->arg_pack, table->minienv) == -1)
					exit(EXIT_FAILURE);
			}
			else if(cmds->i_stream == -1)
			{
				ft_putstr_fd("bash: ", STDERR_FILENO);
				ft_putstr_fd(cmds->patherr, STDERR_FILENO);
				ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
				exit(1);
			}
			else if(v.binar == -1)
			{
				ft_putstr_fd("-sadm: ", STDERR_FILENO);
				ft_putstr_fd(cmds->arg_pack[0], STDERR_FILENO);
				ft_putstr_fd(": Command not found\n", STDERR_FILENO);
				exit(1);
			}
			dup2(cmds->i_stream, STDIN_FILENO);
		}
		ccount++;
		i++;
		cmds = cmds->next;
	}
	i = -1;
	close_all_pipes(pip_ptr, pip);
	while (ccount--)
		wait(&table->status);
	free(pip_ptr);
}

// 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