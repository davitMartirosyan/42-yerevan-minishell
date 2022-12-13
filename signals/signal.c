/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabazyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:05:55 by sabazyan          #+#    #+#             */
/*   Updated: 2022/12/07 12:06:56 by sabazyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include <termios.h>

void	new_prompt(int sig)
{
	printf("\n");
	rl_on_new_line();
	// rl_replace_line("", 0);
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