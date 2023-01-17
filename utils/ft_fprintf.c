/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:58:28 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 04:24:56 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int	print_string(int fd, char *str);

int	ft_fprintf(int fd, const char *placeholder, ...)
{
	va_list	ap;
	int		i;
	int		cout;

	i = 0;
	cout = 0;
	va_start(ap, placeholder);
	while (placeholder[i])
	{
		if (placeholder[i] == '%')
		{
			if (placeholder[i + 1] == 's')
				cout += print_string(fd, va_arg(ap, char *));
			else if (placeholder[i + 1] == 'd')
				ft_putnbr_fd(va_arg(ap, int), fd);
			i++;
		}
		else
			cout += write(fd, &placeholder[i], 1);
		i++;
	}
	va_end(ap);
	return (cout);
}

int	print_string(int fd, char *str)
{
	int	cout;

	cout = 0;
	cout = write(fd, str, ft_strlen(str));
	return (cout);
}
