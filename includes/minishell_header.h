/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_header.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:20:22 by dmartiro          #+#    #+#             */
/*   Updated: 2022/09/28 21:12:33 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_HEADER_H
#define MINISHELL_HEADER_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "./structs.h"
#include "../libft/libft.h"
#include "./lex.h"
#include "./env.h"
#include "./utilities.h"
#include "./builtins.h"

#endif