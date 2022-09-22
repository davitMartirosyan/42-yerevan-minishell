/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:57 by dmartiro          #+#    #+#             */
/*   Updated: 2022/09/22 08:20:40 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell_header.h"

int main(int argc, char *argv[], char *envp[])
{
    t_envkeys   *env;
    t_table     *table;

    table = malloc(sizeof(t_table));
    env = env_tokenizing(envp);
    add_paths(&env, &table);
    printf("%s", table->paths[0]);
}











//  char *cmd;

    // t_envkeys *e;

    // e = NULL;
    // env_tokenizing(&e, envp);
    
    // printf("%s\n", e->val);
//     cmd = readline("$ ");
//     printf("%s\n", cmd);

// gcc -lreadline env/*.c utils/*.c libft/libft.a  minishell.c -o minishell
// gcc env/*.c utils/*.c libft/libft.a  minishell.c -o minishell




//  char *cmdline;
//     char **tok;
//     char *path;
    
//     cmdline = readline("dmbash$ ");
//     tok = ft_split(cmdline, ' ');
//     path = ft_strjoin("/bin/", tok[0]);
//     execve(path, tok, NULL);