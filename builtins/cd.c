/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:36:33 by ralopez-          #+#    #+#             */
/*   Updated: 2023/03/10 11:36:34 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	msg_error(char *str)
{
	perror(str);

	return (1);
}

int	cd(t_inf *info, char *line, t_command *cmd)
{
	char	*location;
	char	*tmp;
	get_pwd(info);
	//printf("Line: %s\n", line);
	//printf("Estoy en %s\n", info->pwd);
	//location = ft_strjoin(info->pwd,"/");

	location = ft_strjoin("./", ft_substr(line, 3, ft_strlen(line)));
	if (chdir(ft_strtrim(location, " "))!= 0)
	{
		tmp = ft_strjoin(info->pwd, "/");
		location = ft_strjoin(tmp, ft_substr(line, 3, ft_strlen(line)));
		if (chdir(ft_strtrim(location, " "))!= 0)
		{
			printf("No se ha podido cambiar de directorio\n");
			return (1);
		}
		else
		{
			change_var_env(info, "OLDPWD", info->pwd);
			change_var_env(info, "PWD", ft_strtrim(location, " "));
			printf("Cambio a %s gracias a ruta absoluta\n",location);
		}
	}
	else
	{
		change_var_env(info, "OLDPWD", info->pwd);
		change_var_env(info, "PWD", ft_strtrim(location, " "));
		printf("Cambio a %s gracias a ruta relativa\n",location);
	}
		

	//free(info->pwd);
	//info->pwd = location;
	//printf("Cambio a %s\n",location);
	return (0);
}
