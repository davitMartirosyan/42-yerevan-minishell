/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswordpart_spec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 02:53:33 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 02:53:34 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_iswordpart_spec(int ch)
{
	if (! ft_isspace(ch) && ! ft_isspecial_spec(ch))
		return (1);
	else
		return (0);
}
