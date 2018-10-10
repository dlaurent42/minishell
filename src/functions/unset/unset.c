/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 23:13:15 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/10 14:35:15 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			sh_unset(t_shell *sh, char **argv)
{
	int		i;
	char	res;
	size_t	argc;

	i = 0;
	res = 0;
	argc = ft_count_argv((void **)argv);
	if (argc == 0)
		return (sh_unset_error(NULL, 1));
	while (argv[i] && (res = sh_unset_remove(sh, argv[i])) == 0)
		i++;
	return (res);
}
