/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:36:09 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/31 01:42:53 by dmartiro         ###   ########.fr       */
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
    EXP_FIELD,     // 7  "..."
    EXP,           // 8  '...'
    REDIR_OUT,     // 9  >
    REDIR_IN,      // 10  <
    APPEND,        // 11 >>
    HEREDOC,       // 12 <<
    PIPE,          // 13 |
    UNDEFINED      // 14
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
    char        **in_files;
    char        **out_files;
    int         q_c[2];
    t_env       *env;
    t_tok       *token;
} t_table;

typedef int (*t_builtin_ptr)(t_list *, t_table *);

#endif