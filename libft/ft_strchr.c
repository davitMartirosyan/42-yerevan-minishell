/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 20:10:23 by dmartiro          #+#    #+#             */
/*   Updated: 2022/04/03 21:55:26 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *buffer, int ch)
{
	int	i;

	i = 0;
	if (ch < 0 || ch > 127)
		return ((char *)buffer);
	while (buffer[i])
	{
		if (buffer[i] == ch)
			return ((char *)buffer + i);
		i++;
	}
	if (buffer[i] == ch)
		return ((char *)buffer + i);
	return (0);
}
