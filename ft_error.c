#include "minishell.h"
/** msg:
 * This function display an error message.
 * 
 * Returns ther code that recive as argument
 */
int	msg(char *str1, char *str2, char *str3, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putendl_fd(str3, 2);
	return (code);
}

void	end_shell(t_inf *info, int code)
{
	if (1 == 2)
		info = NULL;
	//ft_lstclear_cmds(info);
	//ft_lstclear_tokens(info);
	//ft_free_array(info->paths);
	//ft_free_array(info->env);
	exit(code);
}