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

static void	handle_status__and_wait(int *status);
static void	close_all_pipes(int pips[][2], int pip);
static void	execute(t_cmdline *cmd, t_table *table);
static void	_execute(t_vars *v, t_cmdline *cmd, t_table *table);
static void	piping_execution(int pip, t_cmdline *cmd, t_table *table);
static void	piping(t_cmds *cmd, int pip_ptr[][2], int i, int pip);

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

static void	execute(t_cmdline *cmd, t_table *table)
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

static void	_execute(t_vars *v, t_cmdline *cmd, t_table *table)
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
	else
	{
		printf("error\n");
		table->status = 1;
	}
}

static void	piping_execution(int pip, t_cmdline *cmd, t_table *table)
{
	//fd[0] - read end
	//fd[1] - write end
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
		v.built = find_in(cmds->arg_pack[0], table->reserved);
		v.binar = cmd_check(cmds, table);
		if (!cmds->arg_pack)
		{
			cmds = cmds->next;
			continue;
		}
		cmds->pid = fork();
		if (cmds->pid == 0)
		{
			piping(cmds, pip_ptr, i, pip);
			if (v.built != -1)
				table->builtin[v.built](cmds, table);
			else if (v.binar != -1)
			{
				table->minienv = create_envp(&table->env);
				if (execve(cmds->path, cmds->arg_pack, table->minienv) == -1)
					exit(EXIT_FAILURE);
			}
		}
		ccount++;
		i++;
		cmds = cmds->next;
	}
	close_all_pipes(pip_ptr, pip);
	i = -1;
	while (ccount--)
		wait(&table->status);
	close_all_pipes(pip_ptr, pip);
	free(pip_ptr);
}

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

static void	piping(t_cmds *cmd, int pip_ptr[][2], int i, int pip)
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
	}
	close(o_stream);
	close(i_stream);
	close_all_pipes(pip_ptr, pip);
}


static void	handle_status__and_wait(int *status)
{
	//  wait(status);
	waitpid(-1, 0, WUNTRACED);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		*status = WTERMSIG(*status);
	else if (WIFSTOPPED(*status))
		*status = WIFSTOPPED(*status);
}

// void	execute(t_cmdline **cmd, t_table **table)
// {
//	 t_vars  v;  
// 	if (!cmd && !*cmd && !table && !*table)
// 		return ;
// 	else if ((*cmd)->cmds->arguments == NULL)	
// 		return ;
//	 v.dupcopy = dup(0);
//	 v.dupcopy2 = dup(1);
//	 v.built = find_in((*cmd)->cmds->arg_pack[0], (*table)->reserved);
//	 v.binar = cmd_check((*cmd)->cmds, table);
// 	(*table)->status = 0;
//	 dup2((*cmd)->cmds->i_stream, 0);
//	 dup2((*cmd)->cmds->o_stream, 1);
//	if (v.built != -1)
//		 (*table)->builtin[v.built](*cmd, *table);
//	 else if (!v.binar && (*cmd)->cmds->i_stream != -1 && (*cmd)->cmds->o_stream != -1)
//	 {
//		 (*cmd)->cmds->pid = fork();
//		if ((*cmd)->cmds->pid == 0)
//		 {
// 			(*table)->minienv = create_envp(&(*table)->env);
//			 execve((*cmd)->cmds->path, (*cmd)->cmds->arg_pack, (*table)->minienv);
//		 }
//		 else
// 			wait(&(*table)->status);
//		if (WIFEXITED((*table)->status))
//			 (*table)->status = WEXITSTATUS((*table)->status);
//		 else if (WIFSIGNALED((*table)->status))
//			 (*table)->status = WTERMSIG((*table)->status);
//		 else if (WIFSTOPPED((*table)->status))
//			 (*table)->status = WIFSTOPPED((*table)->status);
//	 }
//	 else if ((*cmd)->cmds->i_stream == -1 || (*cmd)->cmds->o_stream == -1)
//	 {
// 		(*table)->status = 1;
//		 printf("%s%s%s", SHELLERR, (*cmd)->cmds->err, FILEERR); // no such file or direcotry
//	 }
//	 else if (v.binar == -2)
//	 {
// 		(*table)->status = 127;
//		 printf("%s%s%s", SHELLERR, (*cmd)->cmds->arg_pack[0], FILEERR); // no such file or direcotry
//	 }
//	 else
//	 {
// 		(*table)->status = 127;
//		 printf("%s%s%s", SHELLERR, (*cmd)->cmds->arg_pack[0], COMMANDERR); // command not found
//	 }
//	 dup2(v.dupcopy, 0);
//	 dup2(v.dupcopy2, 1);
//	 return ;
// }

// void	combined_execution(int pip, t_cmdline **cmd, t_table **table)
// {
//	 t_vars v;
//	 int i;
//	 int (*pips)[2];
//	 pips = malloc(sizeof(*pips) * pip);
//	if (!pips)
//		 return ;
//	 i = -1;
//	 while (++i < pip)
//		 pipe(pips[i]);
//	 i = 0;
//	 while ((*cmd)->cmds != NULL)
//	 {
//		 v.built = find_in((*cmd)->cmds->arg_pack[0], (*table)->reserved);
//		 v.binar = cmd_check((*cmd)->cmds, table);
//		 (*cmd)->pid = fork();
//		if ((*cmd)->pid == 0)
//		 {
//			if (i == 0)
//			 {
//				 dup2(pips[i][1], (*cmd)->cmds->o_stream);
//				 close_all_pipes(pips, pip);
//			 }
//			 else if (i > 0 && i < pip)
//			 {
//				 dup2(pips[i-1][0], (*cmd)->cmds->i_stream);
//				 dup2(pips[i][1], (*cmd)->cmds->o_stream);
//				 close_all_pipes(pips, pip);
//			 }
//			 else
//			 {
//				 dup2(pips[i-1][0], (*cmd)->cmds->i_stream);
//				 close_all_pipes(pips, pip);
//			 }
//			if (v.built != -1)
//				 (*table)->builtin[v.built](*cmd, *table);
//			 else if (v.binar != -1)
//			 {
//				 (*table)->minienv = create_envp(&(*table)->env);
//				 execve((*cmd)->cmds->path, (*cmd)->cmds->arg_pack, (*table)->minienv);
//				 printf("%s%s%s", SHELLERR, (*cmd)->cmds->arg_pack[0], COMMANDERR); // command not found
//			 }
//			 else if ((*cmd)->cmds->i_stream == -1 || (*cmd)->cmds->o_stream == -1)
//			 {
//				 (*table)->status = 1;
//				 printf("%s%s%s", SHELLERR, (*cmd)->cmds->err, FILEERR); // no such file or direcotry
//			 }
//			 else if (v.binar == -2)
//			 {
//				 (*table)->status = 127;
//				 printf("%s%s%s", SHELLERR, (*cmd)->cmds->arg_pack[0], FILEERR); // no such file or direcotry
//			 }
//			 else
//			 {
//				 (*table)->status = 127;
//				 printf("%s%s%s", SHELLERR, (*cmd)->cmds->arg_pack[0], COMMANDERR); // command not found
//			 }
//			 exit(1);
//		 }
//		 i++;
//		 v.let++;
//		 (*cmd)->cmds = (*cmd)->cmds->next;
//	 }
//	if ((*cmd)->pid != 0)
//	 {
//		 int a = -1;
//		 while (++a < pip)
//		 {
//			 close(pips[a][1]);
//			 close(pips[a][0]);
//		 }
//		 while (v.let--)
//			 wait(&(*table)->status);
//	 }
// }

static void	close_all_pipes(int pips[][2], int pip)
{
	int a;

	a = -1; 
	while (++a < pip)
	{
		close(pips[a][1]);
		close(pips[a][0]);
	}
}

// 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