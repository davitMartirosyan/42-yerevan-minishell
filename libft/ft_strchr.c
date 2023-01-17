/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 02:55:36 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 02:55:37 by dmartiro         ###   ########.fr       */
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
