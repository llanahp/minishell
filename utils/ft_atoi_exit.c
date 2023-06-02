/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:28:03 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/05/31 19:14:53 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static unsigned long long int	look_max(int sig, unsigned long long int num)
{
	if (num > 9223372036854775806)
	{
		if (sig > 0)
			return (-1);
		else
			return (-0);
	}
	return (num);
}

int	handle_correct_exit_code(int sig, unsigned long long int num)
{
	unsigned long long int	max_code;
	unsigned long long int	converted_num;

	max_code = 255;
	if (num > max_code)
	{
		converted_num = num % (max_code + 1);
		if (converted_num == 0)
			converted_num = max_code;
	}
	else
		converted_num = num;
	if (sig < 0)
	{
		if (converted_num != 0)
			converted_num = max_code - converted_num + 1;
	}
	return ((int)converted_num);
}

int	check_signs(const char *str, int *i)
{
	int	sig;

	sig = 1;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sig = (sig * -1);
		(*i)++;
	}
	return (sig);
}

int	ft_atoi_exit(const char *str)
{
	int						i;
	int						sig;
	unsigned long long int	num;
	int						res;

	num = 0;
	i = 0;
	sig = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
	{
		i++;
	}
	sig = check_signs(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	num = look_max(sig, num);
	res = handle_correct_exit_code(sig, num);
	return (res);
}
