/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigaction_here.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 19:07:59 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/03 19:08:00 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_reset_prompt_here(int signal)
{
	if (signal == SIGINT)
	{
		(void)signal;
		g_info.must_continue = 0;
		g_info.last_code = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
		SIG_IGN ;
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_info.must_continue = 0;
	g_info.last_code = 1;
	write(1, "\n", 1);
	exit(1);
}
