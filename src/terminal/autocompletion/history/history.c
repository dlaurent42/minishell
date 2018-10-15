/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 09:05:58 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/15 19:37:21 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool				auto_history(t_shell *sh)
{
	bool			status;

	status = false;
	auto_hist_sed(sh, &status);
	auto_hist_double(sh, &status);
	auto_hist_number(sh, &status);
	auto_hist_name(sh, &status);
	return (status);
}
