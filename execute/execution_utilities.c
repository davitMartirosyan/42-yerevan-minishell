#include "minishell_header.h"

int check_command(t_cmds *cmds, t_vars *v, t_table *table)
{
	if (!cmds->arg_pack)
	{
		cmds = cmds->next;
		return (0);
	}
	v->built = find_in(cmds->arg_pack[0], table->reserved);
	v->binar = cmd_check(cmds, table);
	return (1);
}

void execute_pipe_command(t_cmds *cmds, t_vars *v, t_table *table)
{
	if (v->built != -1)
	{
		table->builtin[v->built](cmds, table);
		exit(0);
	}
	else if (v->binar != -1 && cmds->i_stream != -1)
	{
		table->minienv = create_envp(&table->env);
		if (execve(cmds->path, cmds->arg_pack, table->minienv) == -1)
			exit(EXIT_FAILURE);
	}
	else if(cmds->i_stream == -1)
	{
		ft_fprintf(STDERR_FILENO, \
		"bash: %s: No such file or directory\n", cmds->patherr);
		exit(1);
	}
	else if(v->binar == -1)
	{
		ft_fprintf(STDERR_FILENO, \
		"-sadm: %s: Command not found\n", cmds->arg_pack[0]);
		exit(1);
	}
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
		ft_fprintf(STDERR_FILENO, "bash: %s: No such file or directory\n", cmd->cmds->patherr);
	else if(v->binar == -1)
		ft_fprintf(STDERR_FILENO, "-sadm: %s: Command not found\n", cmd->cmds->arg_pack[0]);
}

int _execute_pipes(t_cmds *cmds, t_vars *v, t_table *table, int (*pip_ptr)[2])
{
	int pip;
	int ccount;
	int i;

	pip = pipes(&table->token);
	i = 0;
	ccount = 0;
	while (cmds != NULL)
	{
		if(!check_command(cmds, v, table))
			continue;
		cmds->pid = fork();
		if (cmds->pid == 0)
		{
			dup2(cmds->i_stream, STDIN_FILENO);
			dup2(cmds->o_stream, STDOUT_FILENO);
			piping(cmds, pip_ptr, i, pip);
			execute_pipe_command(cmds, v, table);
			dup2(cmds->i_stream, STDIN_FILENO);
		}
		ccount++;
		i++;
		cmds = cmds->next;
	}
	return (ccount);
}