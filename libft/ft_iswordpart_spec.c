/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswordpart_spec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 23:26:47 by dmartiro          #+#    #+#             */
/*   Updated: 2022/12/04 23:27:51 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h"

int ft_iswordpart_spec(int ch)
{
    if(!ft_isspace(ch) && !ft_isspecial_spec(ch))
        return (1);
    else
        return (0);
}