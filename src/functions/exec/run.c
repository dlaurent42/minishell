/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 14:57:19 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/16 13:06:28 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_command_dispatch_builtinsr(t_shell *sh, t_env *env, char **cmd)
{
	if (ft_strcmps(cmd[0], "alias") == 0)
		return (sh_alias(sh, env, cmd + 1));
	if (ft_strcmps(cmd[0], "cd") == 0)
		return (sh_cd(sh, env, cmd + 1));
	if (ft_strcmps(cmd[0], "echo") == 0)
		return (sh_echo(sh, env, cmd + 1));
	if (ft_strcmps(cmd[0], "env") == 0)
		return (sh_env(sh, env, cmd + 1));
	if (ft_strcmps(cmd[0], "exit ") == 0)
		return (sh_exit(sh, env, cmd + 1));
	if (ft_strcmps(cmd[0], "export") == 0)
		return (sh_export(sh, env, cmd + 1));
	if (ft_strcmps(cmd[0], "history") == 0)
		return (sh_history(sh, env, cmd + 1));
	if (ft_strcmps(cmd[0], "read") == 0)
		return (sh__read(sh, env, cmd + 1));
	if (ft_strcmps(cmd[0], "setenv") == 0)
		return (sh_setenv(sh, env, cmd + 1));
	if (ft_strcmps(cmd[0], "unalias") == 0)
		return (sh_unalias(sh, env, cmd + 1));
	if (ft_strcmps(cmd[0], "unset") == 0)
		return (sh_unset(sh, env, cmd + 1));
	if (ft_strcmps(cmd[0], "unsetenv") == 0)
		return (sh_unsetenv(sh, env, cmd + 1));
	return (-1);
}

// static void	sh_command_dispatch_builtins(t_shell *sh, t_env *env, char **cmd)
// {
// 	if (ft_strcmps(cmd[0], "alias") == 0)
// 		exit(sh_alias(sh, env, cmd + 1));
// 	if (ft_strcmps(cmd[0], "cd") == 0)
// 		exit(sh_cd(sh, env, cmd + 1));
// 	if (ft_strcmps(cmd[0], "echo") == 0)
// 		exit(sh_echo(sh, env, cmd + 1));
// 	if (ft_strcmps(cmd[0], "env") == 0)
// 		exit(sh_env(sh, env, cmd + 1));
// 	if (ft_strcmps(cmd[0], "exit") == 0)
// 		exit(sh_exit(sh, env, cmd + 1));
// 	if (ft_strcmps(cmd[0], "export") == 0)
// 		exit(sh_export(sh, env, cmd + 1));
// 	if (ft_strcmps(cmd[0], "history") == 0)
// 		exit(sh_history(sh, env, cmd + 1));
// 	if (ft_strcmps(cmd[0], "read") == 0)
// 		exit(sh__read(sh, env, cmd + 1));
// 	if (ft_strcmps(cmd[0], "setenv") == 0)
// 		exit(sh_setenv(sh, env, cmd + 1));
// 	if (ft_strcmps(cmd[0], "unalias") == 0)
// 		exit(sh_unalias(sh, env, cmd + 1));
// 	if (ft_strcmps(cmd[0], "unset") == 0)
// 		exit(sh_unset(sh, env, cmd + 1));
// 	if (ft_strcmps(cmd[0], "unsetenv") == 0)
// 		exit(sh_unsetenv(sh, env, cmd + 1));
// 	exit(EXIT_FAILURE);
// }

// static char		sh_command_exec_builtin(t_shell *sh, t_env *env, char **cmd)
// {
// 	pid_t	pid;
// 	int		status;
// 	int		res;

// 	res = 0;
// 	if ((sh->pid = fork()) == -1)
// 		return (-1);
// 	else if (sh->pid == 0)
// 	{
// 		if ((res = sh_command_dispatch_builtinsr(sh, env, cmd)) != 0)
// 			exit(EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		pid = wait(&status);
// 		if (res == 0)
// 			exit(EXIT_SUCCESS);
// 		if (WIFEXITED(status))
// 			return (WEXITSTATUS(status));
// 	}
// 	return (res);
// }

static char		sh_command_exec(t_shell *sh, char **cmd, char **env)
{
	pid_t	pid;
	int		status;

	if ((sh->pid = fork()) == -1)
		return (-1);
	else if (sh->pid == 0)
		execve(cmd[0], cmd, env);
	else
	{
		pid = wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (-1);
}

char		sh_command_dispatch(t_shell *sh, t_env *env, char **argv)
{
	char	res;

	if (!argv || !argv[0])
		return (1);
	env_insert(sh, env, "_", argv[0]);
	sh_unset_termios(sh);
	if (!sh_is_not_builtin(argv[0]))
	{
		tcgetattr(STDIN_FILENO, &(sh->termios));
		sh->termios.c_lflag &= ~(ICANON);
		sh->termios.c_lflag &= ~(ECHO);
		sh->termios.c_cc[VMIN] = 1;
		sh->termios.c_cc[VTIME] = 0;
		tcsetattr(STDIN_FILENO, TCSADRAIN,  &(sh->termios));
		res = sh_command_dispatch_builtinsr(sh, env, argv);
	}
	else
	{
		res = sh_command_exec(sh, argv, env->environment);
	}
	sh_set_termios(sh);
	sh_set_termios(sh);
	return (res);
}
