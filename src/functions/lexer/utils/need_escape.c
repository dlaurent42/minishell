/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   need_escape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:49:10 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/30 17:34:49 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool		lexer_need_esc(char c)
{
	return (c == '!' || c == '"' || c == '#' || c == '$' || c == '&' || c == '\''
	|| c == '(' || c == ')' || c == '*' || c == ',' || c == ';' || c == '<'
	|| c == '=' || c == '>' || c == '?' || c == '[' || c == '\\' || c == ']'
	|| c == '^' || c == '`' || c == '{' || c == '|' || c == '}' || c == '~'
	|| c == '}' || c == ' ');
}
