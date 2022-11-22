/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 20:09:23 by dmartiro          #+#    #+#             */
/*   Updated: 2022/04/03 21:41:50 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*p_to_s1_mem;
	const unsigned char	*p_to_s2_mem;

	p_to_s1_mem = (const unsigned char *)s1;
	p_to_s2_mem = (const unsigned char *)s2;
	i = 0;
	if (n <= 0)
		return (0);
	while (i < n)
	{
		if (p_to_s1_mem[i] != p_to_s2_mem[i])
			return (p_to_s1_mem[i] - p_to_s2_mem[i]);
		i++;
	}
	return (0);
}
