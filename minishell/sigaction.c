/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:46:35 by ralopez-          #+#    #+#             */
/*   Updated: 2023/03/10 13:46:35 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	manejar_sigchild(int signal)
{// ctrl-D
	if (signal == SIGINT)//ctrl-C
		exit(0);
	if (signal == SIGQUIT) //ctrl-Contrabarra
		exit(0);
}

void	init_sigaction(t_inf *info)
{
	ft_memset(&(*info).sa, 0, sizeof((*info).sa));
	(*info).sa.sa_handler = manejar_sigchild;
	sigaction(SIGCHLD, &(*info).sa, NULL);
}