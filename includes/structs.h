/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:56:43 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 04:53:32 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
/*  
  [nonprintable] ->  ?  ->  1
  ' ' ->  ?  ->  3
   $  ->  ?  ->  4
   |  ->  ?  ->  5
   '  ->  \a ->  7
   "  ->  \b ->  8
*/
typedef struct s_vars		t_vars;
typedef struct s_table		t_table;
typedef struct s_cmdline	t_cmdline;
typedef struct s_env		t_env;
typedef struct s_tok		t_tok;
typedef struct s_cmds		t_cmds;
typedef void				(*t_built)(t_cmds *cmds, t_table *table);

typedef struct s_vars
{
	int	fd;
	int	var;
	int	let;
	int	def;
	int	log;
	int	cconst;
	int	built;
	int	binar;
	int	dupcopy;
	int	dupcopy2;
}	t_vars;

typedef enum s_types
{
	STDIN,
	STDOUT,
	STDERR,
	SEP,
	WORD,
	SGL,
	DBL,
	EXP_FIELD,
	REDIR_OUT,
	REDIR_IN,
	APPEND,
	HEREDOC,
	PIPE,
	UNDEFINED
}	t_types;

typedef enum s_status
{
	SYNTAX_ERR_STATUS = 258,
	CMD_ERR_STATUS = 127,
	PATH_ERR_STATUS = 1,
	HEREDOC_WARNING_STATUS = 1,
	HEREDOC_LIMIT_ERR_STATUS = 2
}	t_status;

typedef struct s_cmdline
{
	t_cmds	*cmds;
	pid_t	pid;
	char	**env;
}	t_cmdline;

typedef struct s_cmds
{
	char			*arguments;
	char			**arg_pack;
	char			*path;
	char			*patherr;
	int				exit_status;
	int				i_stream;
	int				o_stream;
	int				e_stream;
	pid_t			pid;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct s_tok
{
	int				len;
	char			*tok;
	int				type;
	struct s_tok	*next;
}	t_tok;

typedef struct s_table
{
	char		cwd[10000];
	char		**minienv;
	char		*reserved[8];
	char		*err_handling;
	char		*syntax;
	char		**paths;
	int			(*pip_ptr)[2];
	int			pip;
	int			type;
	int			status;
	int			q_c[2];
	int			hdocs;
	int			get_heredoc_flag;
	int			dup0;
	int			dup1;
	int			get_pid;
	int			pwd_status;
	int			first;
	t_built		builtin[8];
	t_env		*env;
	t_tok		*token;
	t_vars		v;
}	t_table;
#endif
