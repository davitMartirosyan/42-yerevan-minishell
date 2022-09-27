#ifndef STRUCTS_H
#define STRUCTS_H

#define DOUBLEQUOTE "\""
#define PIPE		"|"
#define HEREDOC		"<<"

typedef struct s_env
{
    char *key;
    char *val;
    struct s_env *next;
} t_env;

typedef struct s_heredoc
{
	char *hd_term;
	char *heredoc;
} t_heredoc;

typedef struct s_table{
    char **paths;
    char *cmdline;
	char *hd;
} t_table;

#endif