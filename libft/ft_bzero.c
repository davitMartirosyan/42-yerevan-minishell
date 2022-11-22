/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:23:00 by dmartiro          #+#    #+#             */
/*   Updated: 2022/04/03 21:26:14 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *buffer, size_t n)
{
	size_t			i;
	unsigned char	*su;

	i = 0;
	su = (unsigned char *)buffer;
	while (i < n)
	{
		su[i] = 0;
		i++;
	}
	buffer = su;
}
