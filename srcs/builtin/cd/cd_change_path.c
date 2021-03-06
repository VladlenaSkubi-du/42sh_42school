/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_change_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 16:08:29 by kfalia-f          #+#    #+#             */
/*   Updated: 2020/08/24 16:49:47 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>
#include <builtin42.h>

int			ft_to_dir(char *path)
{
	if (chdir(path) == -1)
	{
		ft_error_cd(path, 3);
		return (BTIN_ERROR);
	}
	change_oldpwd_value(get_pwd_value());
	return (0);
}

void		ft_change_pwd(char **env)
{
	int		i;
	int		j;
	int		c;
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", get_oldpwd_value());
	if ((i = find_in_any_variable(env, &j, "OLDPWD")) >= 0)
		change_env_value(tmp, (i = find_in_variable(&j, "OLDPWD")));
	else
	{
		c = add_new_env(tmp);
		g_envi[c][0] |= ENV_VIS;
	}
	free(tmp);
	tmp = ft_strjoin("PWD=", get_pwd_value());
	if ((i = find_in_any_variable(env, &j, "PWD")) >= 0)
		change_env_value(tmp, (i = find_in_variable(&j, "PWD")));
	else
	{
		c = add_new_env(tmp);
		g_envi[c][0] |= ENV_VIS;
	}
	free(tmp);
}

int			ft_change_path(char *path, char **env, t_cd *flags)
{
	if (ft_to_dir(path))
	{
		free(path);
		return (BTIN_ERROR);
	}
	if (flags->p)
	{
		free(path);
		path = getcwd(NULL, MAXDIR);
	}
	change_pwd_value(path);
	ft_change_pwd(env);
	free(path);
	return (0);
}
