/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 02:52:34 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 02:52:37 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void	*buffer, size_t n)
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
