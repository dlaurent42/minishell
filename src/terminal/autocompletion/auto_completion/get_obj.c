/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 23:43:19 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/10 11:13:28 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "auto_completion.h"
#include "auto_completion_prot.h"

static bool			parse_obj(t_shell *sh, char **argv)
{
	t_obj			*obj;
	t_obj			*last_obj;

	last_obj = NULL;
	argv++;
	if (!(obj = auto_create_obj()))
		return (false);
	if (!(auto_path(obj, ".", *argv)))
	{
		free(obj);
		return (false);
	}
	sh->ac->obj = obj;
	return (true);
}

static bool			get_binaries(t_shell *sh)
{
	t_obj			*obj;
	t_obj			*last_obj;
	t_bin_auto		*bin_auto;

	last_obj = NULL;
	bin_auto = sh->bin->bin_auto;
	while (bin_auto)
	{
		if (!(obj = auto_create_obj()))
			return (false);
		obj->data.bin = 1;
		if (!(obj->data.str = ft_strdups(bin_auto->name)))
		{
			free(obj);
			return (false);
		}
		if (!sh->ac->bin)
			sh->ac->bin = obj;
		else if (last_obj)
			last_obj->next = obj;
		last_obj = obj;
		bin_auto = bin_auto->next;
	}
	return (true);
}

static bool			get_env(t_shell *sh)
{
	t_obj			*obj;
	t_obj			*last_obj;
	char			*equals;
	char			**env;

	last_obj = NULL;
	env = sh->env->environment;
	while (*env)
	{
		if ((equals = ft_strchr(*env, '=')))
		{
			if (!(obj = auto_create_obj()))
				return (false);
			obj->data.env = 1;
			if (!(obj->data.str = ft_strndup(*env, equals - *env)))
			{
				free(obj);
				return (false);
			}
			if (!sh->ac->env)
				sh->ac->env = obj;
			else if (last_obj)
				last_obj->next = obj;
			last_obj = obj;
			env++;
		}
	}
	return (true);
}

bool				auto_get_obj(t_shell *sh)
{
	if (sh->ac->auto_mode != AUTO_NON)
	{
		if (!(parse_obj(sh, sh->ac->argv)))
			return (false);
	}
	if (sh->ac->auto_mode == AUTO_BIN && sh->ac->auto_mode != AUTO_NON)
	{
		if (!(get_binaries(sh)))
			return (false);
		if (!(get_env(sh)))
			return (false);
	}
	return (true);
}
