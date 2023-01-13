/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:25:01 by tumolabs          #+#    #+#             */
/*   Updated: 2023/01/14 01:44:21 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int ft_fprintf(int fd, const char *placeholder, ...)
{
    va_list ap;
    char *s;
    int i;
    int c;
    int cout;

    i = 0;
    cout = 0;
    va_start(ap, placeholder);
    while(placeholder[i])
    {
        if(placeholder[i] == '%')
        {
            if(placeholder[i+1] == 's')
            {
                s = va_arg(ap, char *);
                cout += write(fd, s, ft_strlen(s));
            }
            else if(placeholder[i+1] == 'd')
            {
                c = va_arg(ap, int);
                ft_putnbr_fd(c, fd);
            }
            i++;
        }
        else
            cout += write(fd, &placeholder[i], 1);
        i++;
    }
    va_end(ap);
    return (cout);
}