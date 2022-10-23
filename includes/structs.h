/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:36:09 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/23 07:54:22 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

/*  
    < -> ?  -> 2
    > -> ?  -> 3
    $ -> ?  -> 4
    | -> ?  -> 5
    ' -> \a -> 7
    " -> \b -> 8
*/

typedef enum s_types
{
    STDIN,         // 0  0
    STDOUT,        // 1  1
    STDERR,        // 2  2
    SEP,           // 3  [' ']
    WORD,          // 4  [A-Z_0-9]
    SGL,           // 5  '
    DBL,           // 6  "
    REDIR_OUT,     // 7  >
    REDIR_IN,      // 8  <
    APPEND,        // 9  >>
    HEREDOC,       // 10 <<
    PIPE           // 11 |
} t_type;

typedef struct s_env
{
    char *key;
    char *val;
    struct s_env *next;
} t_env;

typedef struct s_tok
{
    int     len;
    char    *tok;
    int     type;
    struct  s_tok *next;
    struct  s_tok *prev;
} t_tok;

typedef struct s_table{
    char        **paths;
    char        **reserved;
    int         *fds;
    char        **files;
    int         q_c[2];
    t_env       *env;
    t_tok       *token;
} t_table;

typedef int (*t_builtin_ptr)(t_list *, t_table *);

#endif