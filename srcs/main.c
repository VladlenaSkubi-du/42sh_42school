#include "shell42.h"

int				noninteractive_shell(char **argv)
{
	char		*cmd;
	int			li;
	int			sy;

	li = find_in_variable(&sy, "42SH_NONINTERACTIVE");
	g_rdovar[li][sy] = '1';
	cmd = ft_strdup(argv[0]);
	g_prompt.prompt_func = NULL;
	parser(cmd);
	li = find_in_variable(&sy, "?");
	exit(ft_atoi(&g_rdovar[li][sy]));
}

int				main(int argc, char **argv)
{

	g_var_size = ENV_BUFFER;
	create_env();
	/*save_environment_variables();
	save_readonly_variables();
	save_local_variables();
	check_42sh_options(argc, argv);
	save_shell_variables();
	g_prompt.prompt_func = main_prompt;
	interactive_shell();
	*/return (0);
}
