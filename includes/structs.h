/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:36:09 by dmartiro          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/12/07 15:26:44 by user             ###   ########.fr       */
=======
/*   Updated: 2022/12/18 14:32:14 by dmartiro         ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

/*  
  [nonprintable] ->  ?  ->  1
  ' ' ->  ?  ->  3
   $  ->  ?  ->  4
   |  ->  ?  ->  5
   '  ->  \a ->  7
   "  ->  \b ->  8
*/

typedef struct s_vars t_vars;
typedef struct s_table t_table;
typedef struct s_cmdline t_cmdline;
typedef struct s_env t_en;
typedef struct s_tok t_tok;
typedef struct s_cmds t_cmds;
typedef void (*t_built)(t_cmdline *, t_table *);

typedef struct s_vars
{
<<<<<<< HEAD
=======
    int fd;
>>>>>>> master
    int var;
    int let;
    int def;
    int log;
    int cconst;
    int built;
    int binar;
    int dupcopy;
    int dupcopy2;
} t_vars;

typedef enum s_types
{
    STDIN,         // 0  0
    STDOUT,        // 1  1
    STDERR,        // 2  2
    SEP,           // 3  [' ']
    WORD,          // 4  [A-Z_0-9]
    SGL,           // 5  '
    DBL,           // 6  "
    EXP_FIELD,     // 7  "..." || '...'
    REDIR_OUT,     // 8  >
    REDIR_IN,      // 9  <
    APPEND,        // 10 >>
    HEREDOC,       // 11 <<
    PIPE,          // 12 |
    UNDEFINED      // 13
} t_types;

typedef enum s_status
{
    SYNTAX_ERR_STATUS = 258,
    CMD_ERR_STATUS = 127,
    PATH_ERR_STATUS = 1,
    HEREDOC_WARNING_STATUS = 1,
    HEREDOC_LIMIT_ERR_STATUS = 2
} t_status;

typedef struct s_cmdline
{
    t_cmds  *cmds;
<<<<<<< HEAD
=======
    pid_t   pid;
>>>>>>> master
    char    **env;
}   t_cmdline;

typedef struct s_cmds
{
    char    *arguments;
    char    **arg_pack;
    char    *path;
    char    *err;
    int     exit_status;
    int     i_stream;
    int     o_stream;
    int     e_stream;
    pid_t   pid;
    struct  s_cmds *next;
<<<<<<< HEAD
    struct  s_cmds *prev;
=======
>>>>>>> master
}   t_cmds;

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
} t_tok;

typedef struct s_table{
    char        cwd[10000];
    char        **minienv;
<<<<<<< HEAD
    char        **paths;
    char        **reserved;
    char        *err_handling;
    int         q_c[2];
	int			status;
    t_built     builtin[7];
=======
    char        *reserved[8];
    char        *err_handling;
    int         type;
    int         status;
    int         q_c[2];
    int         hdocs;
    int         get_heredoc_flag;
    int         dup0;
    int         dup1;
    int         get_pid;
    t_built     builtin[8];
>>>>>>> master
    t_env       *env;
    t_tok       *token;
} t_table;

#endif