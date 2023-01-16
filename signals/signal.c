/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:58:15 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/16 11:58:16 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	inthandle(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	handleterm(int sig)
{
	struct termios	term;

	tcgetattr(0, &term);
	if (sig == 0)
	{
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSANOW, &term);
	}
}

void	ft_signal(int handle)
{
	handleterm(handle);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, inthandle);
}
