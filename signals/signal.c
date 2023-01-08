/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabazyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:05:55 by sabazyan          #+#    #+#             */
/*   Updated: 2022/12/07 12:06:56 by sabazyan         ###   ########.fr       */
=======
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
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
<<<<<<< HEAD
#include <termios.h>

void	new_prompt(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signals(int state)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &term);
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
}

// Signals

// state = 1
// ctrl-C in an empty prompt should display a new line with a new prompt.
// ctrl-\ in an empty prompt should not do anything.
// ctrl-D in an empty prompt should quit minishell --> RELAUNCH!

// state = 2
// ctrl-C in a prompt after you wrote some stuff should display
//												a new line with a new prompt.
// The buffer should be clean too. Press "Enter" to make sure nothing
//		from the previous line is executed.
// ctrl-D in a prompt after you wrote some stuff should not do anything.
// ctrl-\ in a prompt after you wrote some stuff should not do anything.

// state = 3
// Try ctrl-C after running a blocking command like cat without arguments
//														or grep “something“.
// Try ctrl-\ after running a blocking command like cat without arguments
//														or grep “something“.
// Try ctrl-D after running a blocking command like cat without arguments
// 														or grep “something“.

// Repeat multiple times using different commands.
// If something crashes, select the "crash" flag.
// If something doesn't work, select the "incomplete work" flag.
=======

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
>>>>>>> master
