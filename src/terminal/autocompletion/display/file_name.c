/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 12:16:42 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/02 10:16:36 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			print_end_char(t_args *args)
{
	if (args->data.ifo)
		ft_putchar('|');
	else if (args->data.dir)
		ft_putchar('/');
	else if (args->data.lnk)
		ft_putchar('@');
	else if (args->data.sock)
		ft_putchar('=');
	else if (args->data.blk)
		ft_putchar('#');
	else if (args->data.wht || args->data.chr)
		ft_putchar('%');
	else if (auto_is_executeable(args))
		ft_putchar('*');
}

static void			print_colour(t_frame *frame, t_args *args)
{
	if (auto_is_executeable(args))
		ft_putstr(COL_EXE);
	if (args->data.ifo)
		ft_putstr(COL_IFO);
	if (args->data.chr)
		ft_putstr(COL_CHR);
	if (args->data.dir)
		ft_putstr(COL_DIR);
	if (args->data.blk)
		ft_putstr(COL_BLK);
	if (args->data.reg && !auto_is_executeable(args))
		ft_putstr(COL_REG);
	if (args->data.lnk)
		ft_putstr(COL_LNK);
	if (args->data.sock)
		ft_putstr(COL_SOCK);
	if (args == frame->select)
		ft_printf(COL_BG);
	ft_printf("%s", args->data.str);
}

void				auto_file_name(t_frame *frame, t_args *args)
{
	print_colour(frame, args);
	if (args != frame->select)
		ft_putstr(COL_CLR);
	print_end_char(args);
	if (frame->number_of_columns)
		auto_print_spaces(frame->len_file_name - args->data.len_of_str + 1);
	ft_putstr(COL_CLR);
}
