#include "shell42.h"
#include "readline.h"

int				main_prompt(void)
{
	char		*prompt;

	prompt = find_env_value("0");
	// prompt = "e-bash";
	ft_putstr_fd("\033[1;31m", STDOUT_FILENO);
	ft_putstr_fd(prompt, STDOUT_FILENO);
	ft_putstr_fd("\033[0m", STDOUT_FILENO);
	ft_putstr_fd("> ", STDOUT_FILENO);
	g_prompt.prompt_len_real = ft_strlen(prompt) + 2;
	return (0);
}

int				dquote_prompt(void)
{
	const char	*prompt;
	
	prompt = "dquote> ";
	ft_putstr_fd(prompt, STDOUT_FILENO);
	g_prompt.prompt_len_real = ft_strlen(prompt);
	return (0);
}

int				heredoc_prompt(void)
{
	const char	*prompt;
	
	prompt = "heredoc> ";
	ft_putstr_fd(prompt, STDOUT_FILENO);
	g_prompt.prompt_len_real = ft_strlen(prompt);
	return (0);
}

int				other_prompt(void)
{
	const char	*prompt;
	
	prompt = "> ";
	ft_putstr_fd(prompt, STDOUT_FILENO);
	g_prompt.prompt_len_real = ft_strlen(prompt);
	return (0);
}

int				count_prompt_len(void)
{
	if (g_screen.ws_col == 0)
	{
		if (ioctl(1, TIOCGWINSZ, &g_screen))
		{
			error_handler(TERMINAL_EXISTS, NULL);
			clean_everything();
			exit(TERMINAL_EXISTS);
		}
		if (g_screen.ws_col == 0)
			g_screen.ws_col = 80;
	}
	if (g_prompt.prompt_len_real >= g_screen.ws_col)
		g_prompt.prompt_len = g_prompt.prompt_len_real %
			g_screen.ws_col;
	else
		g_prompt.prompt_len = g_prompt.prompt_len_real;
	if (g_prompt.prompt_len == 0)
	{
		putcap("sf");
		g_rline.flag |= NEW_LINE_SY;
		g_rline.flag |= PROMPTLEN_ZERO;
	}
	return (g_prompt.prompt_len);
}