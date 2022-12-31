/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 20:11:31 by dmartiro          #+#    #+#             */
/*   Updated: 2022/04/03 22:03:26 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(void *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	length;
	char	*s;
	char	*d;

	s = (char *) src;
	d = (char *) dest;
	length = ft_strlen(src);
	i = 0;
	if (!dest || !src)
		return (0);
	if (n != 0)
	{
		while (s[i] != '\0' && i < (n - 1))
		{
			d[i] = s[i];
			i++;
		}
		if (n < length)
			d[n - 1] = '\0';
		else if (n != 0)
			d[i] = '\0';
		return (length);
	}
	return (length);
}
