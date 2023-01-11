/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:25:01 by tumolabs          #+#    #+#             */
/*   Updated: 2023/01/11 20:25:59 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int ft_fprintf(int fd, const char *placeholder, ...)
{
    va_list ap;
    char    *s;
    int i;
    int cout;

    i = 0;
    cout = 0;
    va_start(ap, placeholder);
    while(placeholder[i])
    {
        if(placeholder[i] == '%')
        {
            if(placeholder[++i] == 's')
            {
                s = va_arg(ap, char *);
                cout += write(fd, s, ft_strlen(s));
            }
        }
        else
            cout += write(fd, &placeholder[i], 1);
        i++;
    }
    va_end(ap);
    return (cout);
}