#include "shell42.h"

int				argument_needed_42sh(char *option, char *name)
{
	char		*arg;
	
	arg = ft_strjoin(name, ": ");
	arg = ft_strrejoin(arg, option);
	error_handler(OPTIONS_REQUIRED | (ERR_BTIN_ARG << 9), arg);
	free(arg);
	exit(OPTIONS_REQUIRED);
}

int				invalid_option_42sh(char *option, char *name)
{
	char		*arg;
	
	arg = ft_strjoin(name, ": ");
	arg = ft_strrejoin(arg, option);
	error_handler(OPTIONS_REQUIRED | (ERR_BTIN_INVALID << 9), arg);
	usage_btin(name);
	free(arg);
	exit(OPTIONS_REQUIRED);
}

int				check_42sh_c_option(int argc, char **argv)
{
	int			i;
	int			j;
	int			tmp;

	i = 0;
	tmp = 0;
	while (argv[++i] && argv[i][0] == '-')
	{
		j = 0;
		if (!argv[i][1])
			return (invalid_option_42sh(argv[i], argv[0]));
		while (argv[i][++j] == 'c' && argv[i][j])
			tmp = i;
		if (argv[i][j] == '-' && argv[i][j + 1])
			continue ;
		else if (argv[i][j] == '-' && !argv[i][j + 1])
			break ;
		if (j > 1 && (!(argv[i][j] == 'c' || argv[i][j] == '\0')))
			return (invalid_option_42sh(&argv[i][j], argv[0]));	
	}
	if (tmp > 0 && !argv[i])
		return (argument_needed_42sh("-c", argv[0]));
	return ((tmp > 0) ? noninteractive_shell(argc, &argv[i]) : 0);
}

int				check_42sh_options(int argc, char **argv)
{
	int			flags;
	int			mask;
	int			i;

	flags = find_options(OPTIONS_NUM,
		(char*[]){"c", "--version", "--help", "--readline", "--simple"}, argv);
	if (flags < 0)
		exit(OPTIONS_REQUIRED);
	mask = 1;
	mask = mask << SUBOPTION_STARTS;
	i = 0;
	while (i < OPTIONS_NUM)
	{
		if (flags & (mask << i))
			print_help(i + 1);
		i++;
	}
	if (flags == 0 && argc > 1 && argv[1][0] == '-' && !argv[1][1])
		return (invalid_option_42sh(argv[1], argv[0]));
	return ((flags & 1) ? check_42sh_c_option(argc, argv) : 0);
}
