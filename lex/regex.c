#include "../includes/minishell_header.h"

void regexp(char *cmdline, char *regex)
{
    int i = 0;
    char *cmds;

    cmds = malloc(sizeof(char) * (ft_strlen(regex) + 1));
    cmds[0] = '\0';
    while(cmdline[i])
    {
        if(ft_isalpha(cmdline[i]))
        {
            int c = i;
            if(cmdline[i - 1] == ' ')
                cmds = ft_strjoin(cmds, "/");
            while(ft_isalpha(cmdline[c]))
                c++;
            cmds = ft_strjoin(cmds, "A-Za-z");
            if(cmdline[c] == ' ')
                cmds = ft_strjoin(cmds, "/");
            printf(":%c:\n", cmdline[c]);
        }
        i++;
    }
    printf("%s\n", cmds);
}

// [
//     [start, end],
//     [start, end],
//     .
//     .
//     .
//     .
// ]