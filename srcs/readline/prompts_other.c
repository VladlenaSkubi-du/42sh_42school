#include "shell42.h"
#include "readline.h"

int				pipe_prompt(void)
{
	ft_putstr_fd("pipe> ", STDOUT_FILENO);
	g_rline.prompt_len = 6;
	return (0);
}

int				subshell_prompt(void)
{
	ft_putstr_fd("subshell> ", STDOUT_FILENO);
	g_rline.prompt_len = 10;
	return (0);
}

int				cursh_prompt(void)
{
	ft_putstr_fd("cursh> ", STDOUT_FILENO);
	g_rline.prompt_len = 10;
	return (0);
}

int				cmdandor_prompt(void)
{
	ft_putstr_fd("cmdandor> ", STDOUT_FILENO);
	g_rline.prompt_len = 10;
	return (0);
}
