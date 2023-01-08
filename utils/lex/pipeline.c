/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD:utils/lex/pipeline.c
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:14:09 by user              #+#    #+#             */
/*   Updated: 2022/11/20 16:10:29 by dmartiro         ###   ########.fr       */
=======
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:05:55 by sabazyan          #+#    #+#             */
/*   Updated: 2022/12/17 14:37:34 by dmartiro         ###   ########.fr       */
>>>>>>> master:signals/signal.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

<<<<<<< HEAD:utils/lex/pipeline.c
void add_pipe(char *cmdline, int *pos, int _p_ch, t_tok **token)
{
	int i;
	int _p;
	int type;
	char *pipe;
	
	i = *pos;
	_p = 1;
	while(cmdline[++i] && cmdline[i] == _p_ch)
		++_p;
	pipe = word(cmdline, _p, *pos);
	if(_p > 1)
		type = UNDEFINED;
	else
		type = PIPE;
	add(token, new_token(_p, pipe, type));
	free(pipe);
	*pos += _p;
=======
void inthandle(int sig)
{
	if(sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void handleterm(int sig)
{
	struct termios term;
	
	tcgetattr(0, &term);
	if(sig == 0)
	{
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSANOW, &term);
	}
}

void ft_signal(int handle)
{
	if(handle == 0)
		handleterm(handle);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, inthandle);
>>>>>>> master:signals/signal.c
}