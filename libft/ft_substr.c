/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 02:56:56 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 02:56:57 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t n)
{
	size_t	i;
	char	*memory;

	if (n > ft_strlen(s))
		n = ft_strlen(s);
	if (!s)
		return (NULL);
	if ((size_t)start > ft_strlen(s))
		return (ft_strdup(""));
	memory = malloc(sizeof(char) * (n + 1));
	i = 0;
	if (!memory)
		return (0);
	while (i < n && s[start + i] != '\0')
	{
		memory[i] = s[start + i];
		i++;
	}
	memory[i] = '\0';
	return (memory);
}
