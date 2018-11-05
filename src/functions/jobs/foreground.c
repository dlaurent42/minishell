/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:06:51 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/05 18:13:56 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		put_job_in_foreground(t_job *job, int cont)
{
	tcsetpgrp(STDIN_FILENO, job->pgid);
	if (cont)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &(g_sh->termios));
		if (kill(-job->pgid, SIGCONT) < 0)
			ft_putendl_fd("kill (SIGCONT)", 2);
	}
	job_wait(job);
	tcsetpgrp(STDIN_FILENO, g_sh->pid);
	tcgetattr(STDIN_FILENO, &(g_sh->termios));
	tcsetattr(STDIN_FILENO, TCSADRAIN, &(g_sh->termios));
}
