/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:33:39 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/24 18:58:38 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Falta handle cuando:
// Comillas simple, debe imprimir literalmente lo que tiene dentro, sin variables de entorno
// \ para mostrar caracteres especiales, ej: echo "This is a \"quoted\" word.", echo "Line 1\nLine 2"

// Hablar con Raul porque va a haber que hacer cambios en el tokeize.c
// Si hacemos cambios, fijarse que functione con comillas dobles, igual que sin comillas

int	echo(t_command *cmd)
{
	int	i;

	i = -1;
	if (!ft_strcmp(cmd->args[0], "-n")) 
		i++;
	// why i < 4 ??		
	while (cmd != NULL && cmd->args[++i] && i < 4)
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
	}
	if (ft_strcmp(cmd->args[0], "-n")) 
		printf("\n");
	return (0);
}
