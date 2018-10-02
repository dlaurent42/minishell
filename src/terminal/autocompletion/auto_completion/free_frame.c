/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 22:44:38 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/02 10:05:57 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				auto_free_frame(t_frame *frame)
{
	auto_free_args(&frame->args);
	free(frame->argv);
	free(frame->file_name);
	free(frame->pre_file_name);
}
