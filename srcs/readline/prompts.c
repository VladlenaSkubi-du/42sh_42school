#include "shell42.h"
#include "readline.h"

int				main_prompt(void)
{
	char		*prompt;

	// prompt = find_env_value("0");
	prompt = "e-bash";
	ft_putstr_fd("\033[1;31m", STDOUT_FILENO);
	ft_putstr_fd(prompt, STDOUT_FILENO);
	ft_putstr_fd("\033[0m", STDOUT_FILENO);
	ft_putstr_fd("> ", STDOUT_FILENO);
	g_prompt.prompt_len = ft_strlen(prompt) + 2;
	return (0);
}

int				dquote_prompt(void)
{
	const char	*prompt;
	
	prompt = "dquote> ";
	ft_putstr_fd(prompt, STDOUT_FILENO);
	g_prompt.prompt_len = ft_strlen(prompt);
	return (0);
}

int				heredoc_prompt(void)
{
	const char	*prompt;
	
	prompt = "heredoc> ";
	ft_putstr_fd(prompt, STDOUT_FILENO);
	g_prompt.prompt_len = ft_strlen(prompt);
	return (0);
}

int				other_prompt(void)
{
	const char	*prompt;
	
	prompt = "> ";
	ft_putstr_fd(prompt, STDOUT_FILENO);
	g_prompt.prompt_len = ft_strlen(prompt);
	return (0);
}

size_t			prompt_len(void) //DELETE
{
	size_t		len;
	
	len = 0;
	if (g_prompt.prompt_func == main_prompt)
		len = ft_strlen("e-bash> ");
	else if (g_prompt.prompt_func == dquote_prompt)
		len = ft_strlen("dquote> ");
	else if (g_prompt.prompt_func == heredoc_prompt)
		len = ft_strlen("heredoc> ");
	else if (g_prompt.prompt_func == other_prompt)
		len = ft_strlen("> ");
	else if (g_prompt.prompt_func == pipe_prompt)
		len = ft_strlen("pipe> ");
	else if (g_prompt.prompt_func == subshell_prompt)
		len = ft_strlen("subshell> ");
	else if (g_prompt.prompt_func == cursh_prompt)
		len = ft_strlen("cursh> ");
	else if (g_prompt.prompt_func == cmdandor_prompt)
		len = ft_strlen("cmdandor> ");
	return (len);
}