/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:57:32 by kfalia-f          #+#    #+#             */
/*   Updated: 2020/08/26 20:55:03 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

char		*ft_join_cd(char *path, char *src_path, t_cd *flags)
{
	char	*tmp;
	char	*cur_path;

	cur_path = NULL;
	tmp = ft_strdup("1");
	if (src_path == NULL && flags && !flags->p)
		tmp = ft_strrejoin(tmp, get_pwd_value());
	else if (src_path == NULL && flags && flags->p)
		tmp = ft_strrejoin(tmp, (cur_path = getcwd(NULL, MAXDIR)));
	else if (src_path == NULL && !flags)
		tmp = ft_strrejoin(tmp, get_pwd_value());
	else
		tmp = ft_strrejoin(tmp, src_path);
	tmp = ft_strrejoin(tmp, "/");
	tmp = ft_strrejoin(tmp, path);
	if (cur_path)
		free(cur_path);
	return (tmp);
}

int			ft_error_cd(char *name, int en)
{
	char	*tmp;

	tmp = (name) ? ft_strjoin("cd: ", name) : ft_strdup("cd");
	if (en == 1 || en == 3 || en == 6 || en == 7)
	{
		if (en == 1)
			tmp = ft_strrejoin(tmp, ": String not in pwd");
		else if (en == 3)
			tmp = ft_strrejoin(tmp, ": Permission denied");
		else if (en == 6)
			tmp = ft_strrejoin(tmp, ": OLDPWD not set");
		else if (en == 7)
			tmp = ft_strrejoin(tmp, ": HOME not set");
		error_handler(VARIABLE_ERROR | (ERR_CD << 9), tmp);
	}
	else if (en == 2)
		error_handler(VARIABLE_ERROR | (ERR_CD_NO_FILE_DIR << 9), tmp);
	else if (en == 4)
		error_handler(VARIABLE_ERROR | (ERR_CD_NO_DIR << 9), tmp);
	else if (en == 5)
		error_handler(VARIABLE_ERROR | (ERR_TOO_MANY << 9), tmp);
	free(tmp);
	return (BTIN_ERROR);
}

int			ft_cd_helper(void)
{
	error_handler(OPTIONS_REQUIRED | (ERR_BTIN_INVALID << 9), "cd");
	usage_btin("cd");
	return (0);
}

int			btin_cd(t_process *pos)
{
	int		i;
	t_cd	*flags;
	int		flags_check;

	flags_check = find_options(2, (char*[]){"LP", "--help"}, pos->argv);
	if (flags_check == HELP_FLAG)
		return (usage_btin("cd"));
	if (flags_check < 0)
		return (BTIN_ERROR);
	flags = ft_xmalloc(sizeof(t_cd *));
	i = ft_cd_flags(pos->argv, flags);
	if (pos->argv[i] && pos->argv[i][0] == '-' && pos->argv[i][1] &&
			i > 0 && ft_strcmp(pos->argv[i - 1], "--"))
	{
		free(flags);
		return (ft_cd_helper());
	}
	if (ft_valid_cd(pos->argv, i) ||
			ft_cd_pars(pos->argv[i], pos->envp, flags))
	{
		free(flags);
		return (BTIN_ERROR);
	}
	free(flags);
	return (0);
}
