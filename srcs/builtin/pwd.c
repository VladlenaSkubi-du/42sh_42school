/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 18:14:07 by kfalia-f          #+#    #+#             */
/*   Updated: 2020/08/24 16:30:55 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>
#include <builtin42.h>

int		btin_pwd_error_message(char *option, int error)
{
	char	*error_message;

	error_message = ft_strjoin("pwd: ", option);
	error_handler(OPTIONS_REQUIRED | (ERR_BTIN_INVALID << 9), error_message);
	free(error_message);
	return (BTIN_ERROR);
}

int		btin_pwd_valid(char **argv)
{
	int		i;
	int		j;

	i = 1;
	while (argv[i])
	{
		j = 1;
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == 'L')
				return ((check_posix_option(argv[i], "LP",
					btin_pwd_error_message) != 0) ? BTIN_ERROR : 0);
			else if (argv[i][1] == 'P')
				return ((check_posix_option(argv[i], "LP",
					btin_pwd_error_message) != 0) ? BTIN_ERROR : 0);
			else if (argv[i][1] == '-' && !argv[i][2])
				return (0);
		}
		i++;
	}
	return (0);
}

int		btin_pwd_init(char **argv)
{
	t_cd	*flags;
	int		i;
	int		j;
	char	dir[MAXDIR];

	if (btin_pwd_valid(argv))
		return (BTIN_ERROR);
	flags = ft_xmalloc(sizeof(t_cd *));
	i = ft_cd_flags(argv, flags);
	if (flags->l)
	{
		i = find_in_variable(&j, "PWD");
		if (i < 0)
			return (0);
		ft_putendl_fd(g_envi[i] + j, STDOUT_FILENO);
	}
	else
	{
		getcwd(dir, MAXDIR);
		ft_putendl_fd(dir, STDOUT_FILENO);
	}
	free(flags);
	return (0);
}

int		btin_pwd(t_process *pos)
{
	int		flags;

	flags = find_options(2, (char*[]){"-LP", "--help"}, pos->argv);
	if (flags == HELP_FLAG)
		return (usage_btin("pwd"));
	if (flags < 0)
		return (btin_return_exit_status());
	return (btin_pwd_init(pos->argv));
}
