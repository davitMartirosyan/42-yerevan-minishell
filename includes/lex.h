/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:20:19 by dmartiro          #+#    #+#             */
/*   Updated: 2022/09/28 20:36:36 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
#define LEX_H

void lexical_analyze(char *cmdline, t_env **env, t_table **table);
int contains(char *tok, char *cmdline);
#endif