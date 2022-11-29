/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswordpart.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 07:03:19 by root              #+#    #+#             */
/*   Updated: 2022/11/29 21:54:12 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_iswordpart(int ch)
{
    if(!ft_isspace(ch) && !ft_isspecial(ch) && ch != '\t')
        return (1);
    else
        return (0);
}