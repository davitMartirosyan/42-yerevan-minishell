#include "../includes/minishell_header.h"

void env_tokenizing(t_envkeys **env, char **envp)
{
    int i;
    char **env_tokens;

    if (envp == NULL)
        return ;
    i = -1;
    while(envp[++i])
    {
        env_tokens = ft_split(envp[i], '=');
        *env = malloc(sizeof(**env));
        (*env)->key = env_tokens[0];
        (*env)->val = env_tokens[1];
        env = &((*env)->next);
    }
}

int main(int ac, char *av[], char *envp[])
{
    t_envkeys *env;

    env = NULL;
    env_tokenizing(&env, envp);

    while(env)
    {
        printf("%s -> %s\n", env->key, env->val);
        env = env->next;
    }

}