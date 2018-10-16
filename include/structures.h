/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 18:01:18 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/16 10:31:33 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "shell.h"

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct termios	t_termios;
typedef struct winsize	t_winsize;
typedef struct passwd	t_passwd;
typedef struct timeval	t_timeval;

typedef struct			s_cmd_attr
{
	char				*cmd;
	char				**options;
}						t_cmd_attr;

typedef struct			s_bin_obj
{
	char				*name;
	char				*path;
	t_stat				stats;
}						t_bin_obj;

typedef struct			s_bin_item
{
	char				*key;
	t_bin_obj			*value;
}						t_bin_item;

typedef struct			s_bin_auto
{
	char				*name;
	struct s_bin_auto	*next;
}						t_bin_auto;

typedef struct			s_bin
{
	size_t				size;
	size_t				count;
	t_bin_item			del;
	t_bin_item			**items;
	t_bin_auto			*bin_auto;
}						t_bin;

typedef struct			s_env_item
{
	char				*key;
	char				*value;
	bool				local;
}						t_env_item;

typedef struct			s_env
{
	char				*environment[ENV_MAX_SIZE + 1];
	size_t				size;
	size_t				count;
	t_env_item			del;
	t_env_item			**items;
}						t_env;

typedef struct			s_cmd
{
	char				content[ARG_MAX + 1];
	int					unicode_len;
	int					display_len;
	bool				is_new;
	unsigned int		id;
	struct s_cmd		*last;
	struct s_cmd		*prev;
	struct s_cmd		*next;
}						t_cmd;

typedef struct			s_cursor
{
	int					x;
	int					y;
	int					abs_pos;
	int					rel_pos;
}						t_cursor;

typedef struct			s_buffer
{
	int					unicode_len;
	int					display_len;
	int					ushift;
	int					dshift;
	char				content[ARG_MAX + 1];
	char				parsed[ARG_MAX + 1];
	char				stored[ARG_MAX + 1];
	t_cmd				*cmd;
}						t_buffer;

typedef struct			s_prompt
{
	int					rows;
	int					len;
	int					len_mod;
	char				*content;
	char				*location;
	char				last_exec_succeed;
}						t_prompt;

typedef struct			s_read
{
	char				line[LINE_SIZE];
	char				unicode_bytes_left;
}						t_read;

typedef struct			s_window
{
	short				width;
	short				height;
}						t_window;

typedef struct			s_modes
{
	unsigned char		auto_completion	: 1;
	unsigned char		select			: 1;
	unsigned char		browse			: 1;
	unsigned char		search			: 1;
	unsigned char		multiline		: 1;
	unsigned char		execution		: 1;
	unsigned char		others			: 2;
}						t_modes;

typedef struct			s_select
{
	int					start_rel;
	int					start_abs;
	int					stop;
	char				*content;
}						t_select;

typedef struct			s_search
{
	int					len;
	int					old_len;
	char				content[ARG_MAX + 1];
	t_cmd				*match;
}						t_search;

typedef struct			s_data
{
	int					file_number;

	char				*str;
	char				*parent_path;
	char				*path;

	int					len_of_str;

	int					type;
	mode_t				mode;
	int					links;
	int					rdev;
	char				sym_path[RL_BUFSIZE + 1];

	unsigned char		ifo		: 1;
	unsigned char		chr		: 1;
	unsigned char		dir		: 1;
	unsigned char		blk		: 1;
	unsigned char		reg		: 1;
	unsigned char		lnk		: 1;
	unsigned char		sock	: 1;
	unsigned char		wht		: 1;
	unsigned char		bin		: 1;
	unsigned char		env		: 1;
	unsigned char		no_file	: 1;
	unsigned char		fill	: 5;
}						t_data;

typedef struct			s_obj
{
	t_data				data;
	struct s_obj		*next;
	struct s_obj		*hor_next;
	struct s_obj		*hor_prev;
	struct s_obj		*ver_next;
	struct s_obj		*ver_prev;
}						t_obj;

typedef struct			s_ac
{
	char				**argv;

	char				*pre_file_name;
	char				*del_file_name;
	char				*file_name;
	int					file_name_len;
	char				cmp_mode;
	char				auto_mode;

	unsigned char		at_mode	: 1;
	unsigned char		fill	: 7;

	int					len_file_name;
	int					items_to_display;
	int					total_blocks;
	int					number_of_printed_rows;

	int					width;
	int					height;
	int					number_of_columns;

	t_obj				*obj;
	t_obj				*bin;
	t_obj				*env;
	t_obj				*current_obj;
	t_obj				*select;
	t_obj				*window_resize;
}						t_ac;

typedef struct			s_read_dir
{
	t_obj				*obj;
	t_obj				*tmp;
	t_obj				*head;
	t_obj				*last_obj;
	DIR					*directory;
	struct dirent		*file;
}						t_read_dir;

typedef struct			s_shell
{
	t_ac				*ac;
	char				*hist;
	pid_t				pid;
	t_bin				*bin;
	t_cmd				*cmd;
	t_env				*env;
	t_env				*alias;
	t_read				*read;
	t_modes				modes;
	t_cursor			cursor;
	t_prompt			prompt;
	t_window			window;
	t_buffer			buffer;
	t_search			search;
	t_select			selection;
	t_termios			termios;
}						t_shell;

t_shell					*g_sh;

#endif