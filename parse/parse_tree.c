/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parse_tree.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: dmartiro <dmartiro@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/12/02 00:36:43 by dmartiro		  #+#	#+#			 */
/*   Updated: 2022/12/14 07:40:20 by dmartiro		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell_header.h"

t_cmds *parse(t_tok *token, t_table *table)
{
	t_cmds *commands;

	(void)commands;
	(void)table;
	(void)token;
	commands = malloc(sizeof(t_cmds));
	if (!commands)
		return (NULL);
	std(&commands);
	if (token && table)
		parse_to(token, table, &commands);
	separate(&commands);
	return (commands);
}

void	parse_to(t_tok *token, t_table *table, t_cmds **cmds)
{
	char	*joined;
	int rtr;

	while (token != NULL)
	{
		if (typeis_arg(token->type))
		{
			joined = NULL;
			joined = word_expansions(&token);
			(*cmds)->arguments = join_arguments((*cmds)->arguments, 1, joined);
			if (joined != NULL)
				free(joined);
			continue;
		}
		if (typeis_redirection(token->type))
		{
			select_filename(&token, *cmds);
			token = token->next;
			continue;
		}
		if (!type_is_p_h(&token, &cmds, table, &rtr))
		{	
			if(rtr == -1)
				break;
			continue;
		}
		token = token->next;
	}
	(*cmds)->next = NULL;
}

char *word_expansions(t_tok **token)
{
	char *word_exps;
	
	word_exps = NULL;
	while ((*token) != NULL)
	{
		word_exps = ft_strjoin(word_exps, (*token)->tok);
		*token = (*token)->next;
		if ((*token) != NULL && !typeis_arg((*token)->type))
			break;
	}
	return (word_exps);
}

t_cmdline *parse_tree(t_table *table)
{
	t_cmdline	*commands;
	t_tok		*tokens;

	if(table->syntax)
	{
		free_tokens(table->token);
		return (NULL);
	}
	commands = NULL;
	tokens = table->token;
	if (tokens != NULL)
	{
		commands = malloc(sizeof(t_cmdline));
		if (!commands)
			return (NULL);
		commands->cmds = parse(tokens, table);
		if (commands->cmds != NULL)
				return (commands);
	}
	return (NULL);
}

void	separate(t_cmds **commands)
{
	t_cmds *tmp;
	int i;

	if (!commands &&  !*commands)
		return ;
	tmp = *commands;
	while ((*commands) != NULL)
	{
		if ((*commands)->arguments != NULL)
			(*commands)->arg_pack = ft_split((*commands)->arguments, 1);
		commands = &(*commands)->next;
	}	
	while (tmp != NULL)
	{
		i = -1;
		if (tmp != NULL && tmp->arguments != NULL)
			while (tmp->arg_pack[++i])
				token_replacment(tmp->arg_pack[i], 3, ' ');
		tmp = tmp->next;
	}
}
// "echo $USER" | > file

//gcc -I includes */*.c minishell.c -lreadline -o minishell && ./minishell