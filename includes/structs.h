#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct s_env
{
    char *key;
    char *val;
    struct s_env *next;
} t_env;

typedef struct s_heredoc
{
	char *hd_term;
    char *delimiter;
	char *heredoc;
} t_heredoc;

typedef struct s_table{
    char        **paths;
    char        *cmdline;
	t_heredoc   *heredoc;
    t_env       *env;
} t_table;

#endif