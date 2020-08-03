#include "shell42.h"
#include "builtin42.h"

int		btin_bg(t_ltree *pos)
{
	int				flags;
	
	flags = find_options(2, (char*[]){"", "--help"}, pos->ar_v);
	if (flags == HELP_FLAG)
		return (usage_btin("bg"));
	if (flags < 0)
		return (btin_return_exit_status());
	return (btin_bg_check_options(pos->ar_c, pos->ar_v));
}

int		btin_bg_check_options(int argc, char **argv)
{
	int				i;

	i = 0;
	while (argv[++i])
	{
		if (argv[i][0] == '-')
		{
			if (!argv[i][1])
				return (btin_bg_fg_error_message(2, argv[i], VARIABLE_ERROR));
			else if (argv[i][1] == '-' && !argv[i][2])
				return (btin_bg_init(argc - i, &argv[i]));
		}
		else
		{
			argc -= i - 1;
			if (argc >= 2 && !(argv[i][0] == '%'))
				return (btin_bg_fg_error_message(2, argv[i], VARIABLE_ERROR));
			return (btin_bg_init(argc, &argv[i - 1]));
		}
	}
	return (btin_bg_init(argc, &argv[0]));
}