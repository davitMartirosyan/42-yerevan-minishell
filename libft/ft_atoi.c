/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 02:52:01 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 02:52:03 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	counter;
	int	syb;

	i = 0;
	counter = 0;
	syb = 1;
	if (nptr == (void *) 0)
		return (0);
	while (nptr[i] == '\n' || nptr[i] == '\t' || nptr[i] == '\r'
		|| nptr[i] == '\v'
		|| nptr[i] == '\f'
		|| nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
		syb = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		counter = counter * 10 + nptr[i] - '0';
		i++;
	}
	return (syb * counter);
}
