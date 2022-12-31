/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strjoin.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: codespace <codespace@student.42.fr>		+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/03/28 18:53:08 by dmartiro		  #+#	#+#			 */
/*   Updated: 2022/12/03 07:09:05 by codespace		###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*join;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	join = malloc(sizeof(char) * (s1len + s2len + 1));
	if (!join)
		return (NULL);
	ft_memmove(join, s1, s1len);
	ft_memmove(join + s1len, s2, s2len);
	join[s1len + s2len] = '\0';
	free((char *)s1);
	return (join);
}
