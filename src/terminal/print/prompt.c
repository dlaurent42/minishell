/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:09:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/20 21:08:50 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_print_prompt(t_shell *sh)
{
	ft_putstr(sh->prompt.content);
	if (sh->prompt.len_mod == 0)
	{
		ft_putstr(K_DOWN);
		ft_putstr(K_COL_0);
	}
	sh->modes.display = TRUE;
}