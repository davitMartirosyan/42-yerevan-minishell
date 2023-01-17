/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 02:56:46 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 02:56:47 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *buffer, int ch)
{
	char	*p;
	int		i;

	p = 0;
	i = 0;
	if (ch < 0 || ch > 127)
		return ((char *)buffer);
	while (buffer[i])
	{
		if (buffer[i] == ch)
			p = (char *)(buffer + i);
		i++;
	}
	if (buffer[i] == ch)
		p = (char *)(buffer + i);
	return (p);
}
