/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 20:09:11 by dmartiro          #+#    #+#             */
/*   Updated: 2022/04/03 21:37:31 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	cc;
	unsigned char	*ss;

	cc = c;
	ss = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ss[i] == cc)
			return ((unsigned char *)(s + i));
		i++;
	}
	return (0);
}
