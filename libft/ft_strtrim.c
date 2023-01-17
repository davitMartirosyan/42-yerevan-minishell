/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 02:56:51 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 02:56:52 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	iff;
	size_t	len;
	char	*trimmed;

	if (!s1)
		return (NULL);
	if (!set)
		return (NULL);
	iff = 0;
	while (ft_strchr(set, s1[iff]))
		++iff;
	len = ft_strlen(s1);
	while (ft_strchr(set, s1[len]) && len > iff)
		--len;
	trimmed = ft_substr(s1, iff, len - iff + 1);
	return (trimmed);
}
