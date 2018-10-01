/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 20:03:57 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/01 23:30:12 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			do_loop(t_frame *frame, t_args *args, int *position_on_row)
{
	if (args)
		frame->number_of_printed_rows = 1;
	else
		frame->number_of_printed_rows = 0;
	while (args && frame->number_of_printed_rows < (frame->height - frame->shell->cursor.y) - 1)
	{
		if (!args->data.no_file)
		{
			auto_display(frame, args);
			*position_on_row += 1;
			if (*position_on_row >= frame->number_of_columns && args->next)
			{
				ft_putchar('\n');
				*position_on_row = 0;
				frame->number_of_printed_rows++;
			}
		}
		args = args->next;
	}
}

static void			delete_str(t_frame *frame)
{
	int				len;

	len = ft_strlenu(frame->del_file_name);
	while (len--)
		sh_delete_char(frame->shell);
}

static void			clear_selection_screen(t_frame *frame)
{
	int				rows;

	rows = frame->number_of_printed_rows;
	ft_putstr(CLEAR_TO_EOL);
	ft_putstr(K_DOWN);
	while (rows--)
		ft_putstr(CLEAR_LINE);
	ft_putstr(K_UP);
}

static void			manage_buffer(t_frame *frame, char *new_display_str)
{
	while(*new_display_str)
	{
		frame->shell->read->line[0] = *new_display_str;
		sh_fill_buffer(frame->shell);
		new_display_str++;
	}
	ft_bzero(frame->shell->read->line, 5);
}

static void			auto_arrows_dispatcher(t_frame *frame)
{
	char			*line;

	line = frame->shell->read->line;
	frame->del_file_name = frame->select->data.str;
	if (line[2] == 65)
		auto_move_up(frame);
	else if (line[2] == 66)
		auto_move_down(frame);
	else if (line[2] == 67 || line[0] == 9)
		auto_move_right(frame);
	else if (line[2] == 68 || line[2] == 90)
		auto_move_left(frame);
}

static void			auto_read_dispatcher(t_frame *frame)
{
	t_shell			*shell;
	char			*line;

	shell = frame->shell;
	line = frame->shell->read->line;
	if (line[0] == 9 || (line[0] == 27 && line[1] == 91))
		auto_arrows_dispatcher(frame);
	else
	{
		if (sh_is_delete_combination(line))
			sh_deletion_dispatcher(frame->shell);
		else if (line[0] == 10)
			manage_buffer(frame, (frame->select->data.dir) ? "/" : " ");
		else
			sh_fill_buffer(shell);
		clear_selection_screen(frame);
		frame->shell->modes.auto_completion = 0;
	}
}

static void			move_up_to_prompt(t_frame *frame)
{
	int				rows;

	rows = frame->number_of_printed_rows;
	while (rows--)
		ft_putstr(K_UP);
}

static void			fill_buffer_with_wild(t_frame *frame, t_args *args)
{
	frame->del_file_name = frame->args->data.path;
	delete_str(frame);
	while (args)
	{
		if (!args->data.no_file && *args->data.str != '.')
		{
			manage_buffer(frame, args->data.path);
			manage_buffer(frame, " ");
		}
		args = args->next;
	}
}

void				auto_show_screen(t_frame *frame, t_args *head)//Rename
{
	t_args			*args;
	int				position_on_row;
	int				x;
	int				y;

	args = head;
	auto_do_file_admin(frame, args);
	if (frame->cmp_mode == MODE_NON)
		return ;
	frame->del_file_name = frame->file_name;
	if (frame->auto_mode == AUTO_WILD)
		fill_buffer_with_wild(frame, args);
	else
	{
		while (frame->shell->modes.auto_completion)
		{
			position_on_row = 0;
			auto_calculate_number_of_columns(frame);
			args = head;
			delete_str(frame);
			manage_buffer(frame, frame->select->data.str);
			if (frame->select->show_next == frame->select)
			{
				manage_buffer(frame, (frame->select->data.dir) ? "/" : " ");
				break ;
			}
			x = frame->shell->cursor.x;
			y = frame->shell->cursor.y;
			clear_selection_screen(frame);
			ft_putchar('\n');
			do_loop(frame, args, &position_on_row);
			move_up_to_prompt(frame);
			sh_move_to_xy(frame->shell, x, y);
			read(0, frame->shell->read->line, 4);
			if (frame->shell->read->line[0] == 4)
				break ;
			auto_read_dispatcher(frame);
			ft_bzero(frame->shell->read->line, LINE_SIZE);
		}
	}
}