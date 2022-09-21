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


void printSigset(FILE *of, const char *prefix, const sigset_t *sigset)
{
    int sig, cnt;

    cnt = 0;
    for (sig = 1; sig < NSIG; sig++) {
        if (sigismember(sigset, sig)) {
            cnt++;
            fprintf(of, "%s%d (%s)\n", prefix, sig, strsignal(sig));
        }
    }
    

    if (cnt == 0)
        fprintf(of, "%s<empty signal set>\n", prefix);
}

                    /* Print mask of blocked signals for this process */ 
int printSigMask(FILE *of, const char *msg)
{
    sigset_t currMask;

    if (msg != NULL)
        fprintf(of, "%s", msg);

    if (sigprocmask(SIG_BLOCK, NULL, &currMask) == -1)
        return -1;

    printSigset(of, "\t\t", &currMask);

    return 0;
}

                    /* Print signals currently pending for this process */
int printPendingSigs(FILE *of, const char *msg)
{
    sigset_t pendingSigs;

    if (msg != NULL)
        fprintf(of, "%s", msg);

    if (sigpending(&pendingSigs) == -1)
        return -1;

    printSigset(of, "\t\t", &pendingSigs);

    return 0;
}
