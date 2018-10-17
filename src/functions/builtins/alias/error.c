/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 16:43:31 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/17 11:26:35 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_alias_error(char *key, char *val, int err_id, char *msg)
{
	(err_id == 1 && msg) ? ft_putstr_fd("alias: -", 2) : 0;
	(err_id == 1 && !msg) ? ft_putstr_fd("alias", 2) : 0;
	(err_id == 1 && msg) ? ft_putstr_fd(msg, 2) : 0;
	(err_id == 1) ? ft_putendl_fd(": unknown option", 2) : 0;
	(err_id == 1) ? ft_putendl_fd("Usage: alias [-p] [name[=value]...]", 2)
		: 0;
	(err_id == 2) ? ft_putendl_fd("alias: invalid format", 2) : 0;
	(err_id == 3) ? ft_putstr_fd("alias: ", 2) : 0;
	(err_id == 3) ? ft_putstr_fd(msg, 2) : 0;
	(err_id == 3) ? ft_putendl_fd(" not found", 2) : 0;
	(err_id == 4) ? ft_putendl_fd("alias: environment is full", 2) : 0;
	(err_id == 5 && msg) ? ft_putstr_fd("alias: ", 2) : 0;
	(err_id == 5 && msg) ? ft_putstr_fd(msg, 2) : 0;
	(err_id == 5 && msg) ? ft_putendl_fd(" is already public", 2) : 0;
	ft_strdel(&key);
	ft_strdel(&val);
	return (1);
}
