#ifndef REGEX_H
#define REGEX_H

#define CMD         "/[*A-Za-z*]/"
#define FLAG        "/[-][-][A-Za-z]/"
#define HEREDOC     "/[<<][A-Za-z^|]/"

void regexp(char *cmdline, char *regex);

#endif
