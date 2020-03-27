#include "shell42.h"
#include "builtin42.h"

int					btin_fc_route_execution(t_btin_fc *fc_arg, int flags,
						char **envir)
{

	if (flags & FLAG_E)
		return (btin_fc_execute_edition(fc_arg, flags, envir));
	else if (flags & FLAG_L)
	{
		if (flags & FLAG_R)
			return (btin_fc_execute_list_reverse(fc_arg, flags));
		else
			return (btin_fc_execute_list(fc_arg, flags));		
	}
	else if (flags & FLAG_S)
		return (btin_fc_execute_execution(fc_arg, flags));
	return (0);
}

int					btin_fc_execute_list_reverse(t_btin_fc *fc_arg, int flags)
{
	int				i;
	int				tmp;
	
	i = fc_arg->last_buf;
	while (fc_arg->last_buf - i >= fc_arg->first_buf &&
		fc_arg->last_buf - i >= 0)
	{
		tmp = ft_strlen(g_hist.hist[fc_arg->last_buf - i]);
		if (tmp > 0 && g_hist.hist[fc_arg->last_buf - i][tmp - 1] == '\n')
			tmp -= 1;
		if (!(flags & FLAG_N))
			ft_printf("%d\t%.*s\n", fc_arg->last - i, tmp,
				g_hist.hist[fc_arg->last_buf - i]);
		else
			ft_printf("\t%.*s\n", tmp, g_hist.hist[fc_arg->last_buf - i]);
		i++;
	}
	return (0);
}

int					btin_fc_execute_list(t_btin_fc *fc_arg, int flags)
{
	int				i;
	int				tmp;
	
	i = fc_arg->first_buf;
	while (fc_arg->first_buf + i <= fc_arg->last_buf &&
		fc_arg->first_buf + i < g_hist.len)
	{
		tmp = ft_strlen(g_hist.hist[fc_arg->first_buf + i]);
		if (tmp > 0 && g_hist.hist[fc_arg->first_buf + i][tmp - 1] == '\n')
			tmp -= 1;
		if (!(flags & FLAG_N))
			ft_printf("%d\t%.*s\n", fc_arg->first + i, tmp,
				g_hist.hist[fc_arg->first_buf + i]);
		else
			ft_printf("\t%.*s\n", tmp, g_hist.hist[fc_arg->first_buf + i]);
		i++;
	}
	return (0);
}