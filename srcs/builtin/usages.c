#include "shell42.h"
#include "builtin42.h"

int				usage_btin(char *str)
{
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd(": usage: ", STDOUT_FILENO);
	if (ft_strcmp(str, "fc") == 0)  
		usage_btin_fc();
	else if (ft_strcmp(str, "./42sh") == 0)
		usage_42sh();
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
	// ft_putstr_fd(find_env_value("0"), STDOUT_FILENO);
	ft_putendl_fd("e-bash [long option] [option] ...", STDOUT_FILENO);
	ebash_long_options();
	// ft_putstr_fd(find_env_value("0"), STDOUT_FILENO);
	ft_putstr_fd("e-bash options: ", STDOUT_FILENO);
	ft_putendl_fd("-c \"command\"", STDOUT_FILENO);
	return (0);
}

int				ebash_long_options(void)
{
	char		*space;
	
	space = "     ";
	// ft_putstr_fd(find_env_value("0"), STDOUT_FILENO);
	ft_putendl_fd("e-bash long options:", STDOUT_FILENO);
	ft_printf("%s--help\n", space);
	ft_printf("%s--readline\n", space);
	ft_printf("%s--simple\n", space);
	ft_printf("%s--version\n", space);
	return (0);
}
