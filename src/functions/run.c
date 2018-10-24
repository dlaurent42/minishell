/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 20:27:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 21:27:24 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_command_run_checks(t_env *env, char *cmd)
{
	(void)env;
	if (!cmd || lexer_is_empty(cmd))
		return (STATUS_EMPTY);
	/*
		check quotes, needed elements, do expansion, globbing, etc.
	*/
	return (STATUS_OK);
}

static char	sh_command_run_lexer(t_shell *sh, t_env *env, t_lexer *lexer, char *cmd)
{
	char	status;

	(void)env;
	ft_bzero((void *)lexer, sizeof(t_lexer));
	status = (sh->modes.heredoc == FALSE)
		? lexer_fill(lexer, cmd)
		: sh_heredoc(sh, NULL);
	return (status);
}

static char	sh_command_run_ast(t_shell *sh, t_env *env, t_bin *bin, t_lexer lexer)
{
	char			status;
	t_token_tree	*list;

	list = build_list(lexer);
	lexer_delete(&lexer, status);
	if ((list = build_token_tree(list)))
	{
		// TODO: Reorganise tree(prioritising)
		status = execute_tree(sh, list); // returns last return code
	}
	else
		status = error_execution_tree();
	clean_tree(list);
	return (status);
}

char		sh_command_run(t_shell *sh, t_env *env, t_bin *bin, char *cmd)
{
	char			status;
	t_lexer			lexer;

	status = STATUS_OK;
	if ((status == sh_command_run_checks(env, cmd)) != STATUS_OK)
		return (status);
	if ((status == sh_command_run_lexer(sh, env, &lexer, cmd)) != STATUS_OK)
		return (lexer_delete(&lexer, status));
	sh->modes.multiline = FALSE;
	if ((sh->modes.exec = TRUE) && bin == sh->bin)
	{
		sh->bin = bin_update(sh, env, bin);
		command_add(sh, true);
	}
	status = sh_command_run_ast(sh, env, bin, lexer);
	return (lexer_delete(&lexer, status));
}
