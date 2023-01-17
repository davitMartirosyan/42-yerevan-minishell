/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 02:56:42 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 02:56:43 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *buffer, const char *find, size_t n)
{
	size_t	i;
	int		len;
	char	*string;
	char	*search;

	i = 0;
	len = ft_strlen(find);
	string = (char *)buffer;
	search = (char *)find;
	if (*find == '\0')
		return ((char *)buffer);
	while (string[i] != '\0' && (i + len) <= n)
	{
		if (ft_strncmp((string + i), search, len) == 0)
		{
			return (string + i);
		}
		i++;
	}
	return (NULL);
}
