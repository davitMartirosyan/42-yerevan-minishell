/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 02:54:42 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 02:54:43 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void	*s, int c, size_t n)
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
