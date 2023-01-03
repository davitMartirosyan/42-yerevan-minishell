#include "minishell_header.h"

int istream(t_cmds *cmd, int (*pipe)[2], int i)
{
	if (cmd->i_stream != 0)
		return cmd->i_stream;
	return (pipe[i - 1][0]);
}

int ostream(t_cmds *cmd, int (*pipe)[2], int i)
{
	if (cmd->o_stream != 1)
		return cmd->o_stream;
	return (pipe[i][1]);
}

void	piping(t_cmds *cmd, int pip_ptr[][2], int i, int pip)
{

	int o_stream;
	int i_stream;

	if (i == 0)
	{
		o_stream = ostream(cmd, pip_ptr, i);
		dup2(o_stream, STDOUT_FILENO);
	}
	else if (i > 0 && i < pip)
	{
		i_stream = istream(cmd, pip_ptr, i);
		o_stream = ostream(cmd, pip_ptr, i);
		dup2(i_stream, STDIN_FILENO);
		dup2(o_stream, STDOUT_FILENO);
	}
	else
	{
		i_stream = istream(cmd, pip_ptr, i);
		dup2(i_stream, STDIN_FILENO);
		dup2(cmd->o_stream, STDOUT_FILENO);
	}
	close_all_pipes(pip_ptr, pip);
}

void	close_all_pipes(int pips[][2], int pip)
{
	int a;

	a = -1; 
	while (++a < pip)
	{
		close(pips[a][1]);
		close(pips[a][0]);
	}
}

void	handle_status__and_wait(int pid, int *status)
{
	waitpid(pid, status, 0);

	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		*status = WTERMSIG(*status);
	else if (WIFSTOPPED(*status))
		*status = WIFSTOPPED(*status);
}
