/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:36:09 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/20 14:16:28 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

/*  
    $ -> ?  -> 4
    | -> ?  -> 5
    ' -> \a -> 7
    " -> \b -> 8
*/

typedef enum s_types
{
    STDIN,         // 0 0
    STDOUT,        // 1 1
    STDERR,        // 2 2
    SEP,           // 3 [' ']
    WORD,          // 4 [A-Z_0-9]
    SGL,           // 5 '
    DBL,           // 6 "
    APPEND,        // 7 >>
    HEREDOC,       // 8 <<
    PIPE           // 9 |
} t_type;

typedef struct s_env
{
    char *key;
    char *val;
    struct s_env *next;
} t_env; 

typedef struct s_table{
    char        **paths;
    char        **reserved;
    int         *fds;
    char        **files;
    int         q_c[2];
    t_env       *env;
} t_table;

typedef int (*t_builtin_ptr)(t_list *, t_table *);

#endif