/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usages.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:42:52 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/21 16:42:53 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int				usage_btin(char *str)
{
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd(": usage: ", STDOUT_FILENO);
	if (ft_strcmp(str, "./42sh") == 0)
		usage_42sh();
	else if (ft_strcmp(str, "fc") == 0)  
		usage_btin_fc();
	else if (ft_strcmp(str, "export") == 0)
		ft_putendl_fd("export [name[=value] ...] or export -p",
			STDOUT_FILENO);
	else if (ft_strcmp(str, "cd") == 0)
		ft_putendl_fd("cd [-L|-P] [dir]", STDOUT_FILENO);
	else if (ft_strcmp(str, "echo") == 0)
		ft_putendl_fd("echo [-neE] [arg ...]", STDOUT_FILENO);
	else if (ft_strcmp(str, "pwd") == 0)
		ft_putendl_fd("pwd [-LP]", STDOUT_FILENO);
	else if (ft_strcmp(str, "alias") == 0)
		ft_putendl_fd("alias [alias-name[=string]...]", STDOUT_FILENO);
	else if (ft_strcmp(str, "unalias") == 0)
		ft_putendl_fd("unalias [-a|alias-name ...]", STDOUT_FILENO);
	usage_btin_other(str);
	return (0);
}

int				usage_btin_other(char *str)
{
	if (ft_strcmp(str, "fg") == 0)
		ft_putendl_fd("fg [job_spec]", STDOUT_FILENO);
	else if (ft_strcmp(str, "bg") == 0)
		ft_putendl_fd("bg [job_spec ...]", STDOUT_FILENO);
	else if (ft_strcmp(str, "jobs") == 0)
		ft_putendl_fd("jobs [-l|-p] [job_spec ...]", STDOUT_FILENO);
	else if (ft_strcmp(str, "set") == 0)
		ft_putendl_fd("set [name=value ...]", STDOUT_FILENO);
	else if (ft_strcmp(str, "unset") == 0)
		ft_putendl_fd("unset [name ...]", STDOUT_FILENO);
	else if (ft_strcmp(str, "history") == 0)
		ft_putendl_fd("history [-c]", STDOUT_FILENO);
	else if (ft_strcmp(str, "exit") == 0)
		ft_putendl_fd("exit [numeric arg]", STDOUT_FILENO);
	else if (ft_strcmp(str, "hash") == 0)
		ft_putendl_fd("hash [-l|-r] [-d name ...] [name ...]", STDOUT_FILENO);
	else if (ft_strcmp(str, "type") == 0)
		ft_putendl_fd("type [name...]", STDOUT_FILENO);
	return (0);
}

int				usage_btin_fc(void)
{
	ft_putstr_fd("fc [-e editor] [-nlr] [first] [last]", STDOUT_FILENO);
	ft_putendl_fd(" or fc -s [pat=rep] [cmd]", STDOUT_FILENO);
	return (0);
}

int				usage_42sh(void)
{
	ft_putstr_fd(find_env_value("0"), STDOUT_FILENO);
	ft_putendl_fd(" [long option] [option] ...", STDOUT_FILENO);
	ebash_long_options();
	ft_putstr_fd(find_env_value("0"), STDOUT_FILENO);
	ft_putstr_fd(" options: ", STDOUT_FILENO);
	ft_putendl_fd("-c \"command\"", STDOUT_FILENO);
	return (0);
}

int				ebash_long_options(void)
{
	char		*space;
	
	space = "     ";
	ft_putstr_fd(find_env_value("0"), STDOUT_FILENO);
	ft_putendl_fd(" long options:", STDOUT_FILENO);
	ft_printf("%s--help\n", space);
	ft_printf("%s--readline\n", space);
	ft_printf("%s--simple\n", space);
	ft_printf("%s--version\n", space);
	return (0);
}
