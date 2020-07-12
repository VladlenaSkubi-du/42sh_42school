#include "shell42.h"
#include "parser.h"

/*
** This function change var value in sub->envir array
*/

int		change_var_in_local(t_ltree *sub, char **name, int start)
{
	int			i;
	int			tmp;
	int			len_name;
	char 		*pars;

	i = 0;
	len_name = ft_strlen(*name);
	while (sub->envir[i])
	{
		tmp = ft_strchri(sub->envir[i], '=');
		if (ft_strncmp(sub->envir[i], *name, len_name) == 0 && (tmp == len_name))
		{
			free(sub->envir[i]);
			pars = ft_parsing_str(&(sub->ar_v[start][len_name]));
			*name = ft_strrejoin(*name, pars);
			free(pars);
			sub->envir[i] = ft_strdup(*name);
			return (0);
		}
		i++;
	}
	return (-1);
}

/*
** This function adds new var value in sub->envir array
*/

int		new_var_in_local(t_ltree *sub, char **name, int start)
{
	int		i;
	int		len_name;
	char 	*pars;

	i = 0;
	len_name = ft_strlen(*name);
	while (sub->envir[i])
		i++;
	pars = ft_parsing_str(&(sub->ar_v[start][len_name]));
	*name = ft_strrejoin(*name, pars);
	free(pars);
	sub->envir[i] = ft_strdup(*name);
	return (i);
}

/*
** This function rewrite l_cmd and l_tline from new arrays
*/

int		form_local_str_from_arrays(t_ltree *sub, int i, char **arg_tline)
{
	char	*buf_cmd;
	char	*buf_tline;

	buf_cmd = ft_xmalloc(sizeof(char));
	buf_tline = ft_xmalloc(sizeof(char));
	while (i < sub->ar_c)
	{
		buf_cmd = ft_strrejoin(buf_cmd, sub->ar_v[i]);
		buf_cmd = ft_strrejoin(buf_cmd, " ");
		buf_tline = ft_strrejoin(buf_tline, arg_tline[i]);
		buf_tline = ft_strrejoin(buf_tline, "\2");
		i++;
	}
	free(sub->l_cmd);
	sub->l_cmd = buf_cmd;
	free(sub->l_tline.line);
	sub->l_tline.line = buf_tline;
	sub->l_tline.len = ft_strlen(sub->l_tline.line);
	sub->l_tline.alloc_size = sub->l_tline.len + 1;
	ft_arrdel(arg_tline);
	return (0);
}

/*
** This function delete element with index "i" in array **arr
*/

int		unset_from_array(char ***arr, int i)
{
	char	**tmp;

	tmp = *arr;
	free(tmp[i]);
	tmp[i] = tmp[i + 1];
	i++;
	while (tmp[i])
	{
		tmp[i] = tmp[i + 1];
		i++;
	}
	return (0);
}

/*
** This function adds new local vars values in g_envi array
*/

int		add_vars_to_genvi(t_ltree *sub, char **arg_tline)
{
	int		i;
	int		ret;
    int     eq;

	i = 0;
	ft_arrdel(arg_tline);
	while(i < sub->ar_c)
	{
		eq = ft_strchri(sub->ar_v[i], '=');
        if ((ret = find_assignment_in_vars(sub->ar_v[i], 0,
		eq, ft_strlen(sub->ar_v[i]))) == ERR_OUT)
		{
			sub->flags |= ERR_IN | ERR_OUT;
            sub->err = ft_strndup(sub->ar_v[i], eq);
			return (ERR_OUT);
		}
		i++;
	}
	sub->flags |= ERR_IN;
	return (0);
}
