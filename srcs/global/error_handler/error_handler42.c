#include "shell42.h"

/*
** Enum structure for exxors is defined in exit_status.h
** status that comes is always a value from enum structure
** with binary shift to define the error type
**
** For example: error_handler(OPTIONS_REQUIRED | (ERR_EBASH_C << 9), "e-bash");
** where OPTIONS_REQUIRED is equal 2, if we after check exit status
** with echo $?, there will be 2
** But there are many errors that exit with 2, so we define error type
** by making shift << 9 and activating bits according to the mask defined in
** exit_status.h
** We decided that status always shifts by 9
**
** @status is an int with activated "exit" and error type bits
** @str is a name that is put after "e-bash: [NAME]: [TEXT]"
*/

int				error_handler(int status, char *str)
{
	ft_putstr_fd(find_env_value("0"), STDOUT_FILENO);
	ft_putstr_fd(": ", STDOUT_FILENO);
	// ft_putstr_fd("e-bash: ", STDERR_FILENO);
	if ((status & 0x1FF) == VARIABLE_ERROR)
		variable_errors(status, str);
	else if ((status & 0x1FF) == OPTIONS_REQUIRED)
		options_errors(status, str);
	else if ((status & 0xFF) == TMPFILE)
		ft_putendl_fd("can't open a temporal file", STDERR_FILENO); //TODO check
	else if ((status & 0xFF) >= TERMINAL_EXISTS &&
			(status & 0xFF) <= NONINERACTIVE)
		terminal_errors(status, str);
	else
		error_handler_continuation(status, str);
	return (exit_status_variable(status & 0x7F));
}

int				terminal_errors(int status, char *str)
{
	if ((status & 0x1FF) == TERMINAL_TO_CAN)
	{
		ft_putendl_fd("terminal can't be changed, reset the terminal",
			STDERR_FILENO); //TODO check
		return (0);
	}
	else if ((status & 0x1FF) == NONINERACTIVE)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": can't be launched in noninteractive mode",
			STDERR_FILENO);
		ft_putendl_fd("use shell in interactive mode", STDERR_FILENO);
		usage_42sh();
		return (0);
	}
	if ((status & 0x1FF) == TERMINAL_EXISTS)
		ft_putendl_fd("terminal does not exist", STDERR_FILENO);
	else if ((status & 0x1FF) == TERMINAL_TO_NON)
		ft_putendl_fd("terminal can't be changed", STDERR_FILENO);
	else if ((status & 0x1FF) == TERMINAL_CHANGED)
		ft_putendl_fd("terminal streams were changed", STDERR_FILENO);
	ft_putendl_fd("use shell in non-interactive mode", STDERR_FILENO);
	usage_42sh();
	return (0);
}

int				error_handler_continuation(int status, char *str)
{
	if ((status & 0x1FF) == COMMAND_NON_EXECUTABLE ||
		(status >> 9 & ERR_NO_ACC))
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	}
	else if ((status & 0x1FF) == COMMAND_NOT_FOUND &&
		(status >> 9 & ERR_COMMAND))
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	else if (((status & 0x1FF) == COMMAND_NOT_FOUND ||
		(status & 0x1FF) == SYNTAX_ERROR) &&
		status >> 9 & ERR_NO_FILE)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	else if ((status & 0x1FF) == SYNTAX_ERROR)
		syntax_errors(status, str);
	return (0);
}

/*
** bash --posix -c "/"
bash: /: is a directory
bash-3.2$ echo $?
126

** bash --posix -c "!"
bash: !: event not found
bash-3.2$ echo $?
0

** bash --posix -c "{"
bash: -c: line 1: syntax error: unexpected end of file
bash-3.2$ echo $?
2
*/