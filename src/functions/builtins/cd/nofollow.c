/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nofollow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 23:11:37 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/16 23:11:33 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_cd_get_real_path(t_shell *sh, t_env *env, char *param)
{
	char	*path;
	char	*rpath;
	char	*cdpath;

	path = NULL;
	rpath = NULL;
	if (param[0] == '/')
		return (realpath(param, NULL));
	if (param[0] == '\0')
		return (ft_strdup(env_search(env, "HOME")));
	if ((cdpath = env_search(env, "CDPATH")) && cdpath[0] && param[0] != '.')
		return (sh_cd_handle_cdpath(env, param));
	if (!(path = ft_strjoins(sh->prompt.location, "/")))
		return (NULL);
	if (!path)
		return (NULL);
	path = ft_strjoinf(path, param, 1);
	rpath = realpath(path, NULL);
	ft_strdel(&path);
	return (rpath);
}

char		sh_cd_nofollow(t_shell *sh, t_env *env, char *value, char *path)
{
	char	*rpath;
	t_stat	lstats;

	rpath = (path) ? path : sh_cd_get_real_path(sh, env, value);
	if (access(rpath, F_OK) == -1 || lstat(rpath, &lstats) == -1)
		return (sh_cd_error(value, rpath, 1));
	if (chdir(rpath) == -1)
		return (sh_cd_error(value, rpath, 3));
	env_insert(sh, env, "OLDPWD", env_search(env, "PWD"));
	env_insert(sh, env, "PWD", rpath);
	ft_strdel(&rpath);
	return (0);
}

char		sh_cd_nofollow_dash(t_shell *sh, t_env *env, char *val, char *path)
{
	char	*rpath;
	t_stat	lstats;

	rpath = (path) ? path : sh_cd_get_real_path(sh, env, val);
	if (!rpath || access(rpath, F_OK) == -1 || lstat(rpath, &lstats) == -1)
		return (sh_cd_error(val, rpath, 1));
	if (chdir(rpath) == -1)
		return (sh_cd_error(val, rpath, 3));
	env_insert(sh, env, "OLDPWD", env_search(env, "PWD"));
	env_insert(sh, env, "PWD", rpath);
	ft_putendl(rpath);
	ft_strdel(&rpath);
	return (0);
}
