/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:02:05 by dmartiro          #+#    #+#             */
/*   Updated: 2022/04/03 21:35:43 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ilen(long n)
{
	int	length;

	length = 0;
	if (n < 0)
	{
		n = n * -1;
		length++;
	}
	while (n > 0)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

char	*ft_iszero(char *str)
{
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*numstr;
	long	nn;	

	nn = n;
	len = ilen(n);
	numstr = malloc(sizeof(char) * len + 1);
	if (!numstr)
		return (NULL);
	numstr[len] = '\0';
	if (nn == 0)
		return (ft_iszero(numstr));
	if (nn < 0)
	{
		numstr[0] = '-';
		nn = nn * -1;
	}
	while (nn > 0)
	{
		numstr[--len] = (nn % 10) + '0';
		nn = nn / 10;
	}
	return (numstr);
}
