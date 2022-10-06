#ifndef STRUCTS_H
#define STRUCTS_H

typedef int t_list (*t_builtin_ptr)(t_list *, t_table);

typedef struct s_env
{
    char *key;
    char *val;
    struct s_env *next;
} t_env; 

typedef struct s_heredoc
{
    char *term;
	char *delimiter;
	char *heredoc;
} t_heredoc;

typedef struct s_cmds
{
    char    *cmd;
    char    *path;
    int     istream;
    int     ostream;
    struct  s_cmds *next;
}   t_cmds;

typedef struct s_table{
    char        **paths;
    char        **reserved;
    char        *cmdline;
	t_heredoc   *heredoc;
    t_env       *env;
    t_cmds      *cmds;
} t_table;

#endif