#include "shell42.h"
#include "builtin42.h"

int			btin_unset(t_ltree *pos)
{
	int		i;
	int		tmp;
	int		j;
	char	*find;
	char	*error;

	i = 0;
	while (++i < pos->ar_c)
	{
		if ((tmp = ft_strchri(pos->ar_v[i], '=')) >= 0)
			find = ft_strndup(pos->ar_v[i], tmp);
		else
			find = ft_strdup(pos->ar_v[i]);
		j = find_in_variable(&tmp, find);
		if (g_envi[j][0] && (g_envi[j][0] & READONLY))
		{
			g_envi[j][0] &= ~ENV_VIS;
			error = ft_strjoin("unset: ", find);
			error_handler(VARIABLE_ERROR | (ERR_RDONLY << 9), error);
			free (error);
		}
		else
			g_envi[j][0] = 0;
		free(find);
	}
	return (0);	
}
