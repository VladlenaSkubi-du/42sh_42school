#include "shell42.h"

/*
** Variable errors are errors that exit with 1
*/

int				variable_errors(int status, char *str)
{
	if ((status >> 9 & ERR_SET) || (status >> 9 & ERR_CD))
	{
		ft_putendl_fd(str, STDERR_FILENO);
		return (0);
	}
	ft_putstr_fd(str, STDERR_FILENO);
	if (status >> 9 & ERR_RDONLY)
		ft_putendl_fd(": readonly variable", STDERR_FILENO);
	else if (status >> 9 & ERR_HISTORY_NUM)
		ft_putendl_fd(": history specification out of range", STDERR_FILENO);
	else if (status >> 9 & ERR_HISTORY_EXEC)
		ft_putendl_fd(": no command found", STDERR_FILENO);
	else if (status >> 9 & ERR_UNSET)
		ft_putendl_fd(": parameter null or not set", STDERR_FILENO);
	else if (status >> 9 & ERR_JOB_NF)
		ft_putendl_fd(": no such job", STDERR_FILENO);
	else if (status >> 9 & ERR_HASH_NF)
		ft_putendl_fd(": no command found", STDERR_FILENO);
	return (0);
}

/*
** Option errors are errors that exit with 2
*/

int				options_errors(int status, char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	if (status >> 9 & ERR_BTIN_INVALID)
		ft_putendl_fd(": invalid option", STDERR_FILENO);
	else if (status >> 9 & ERR_BTIN_ARG)
		ft_putendl_fd(": option requires an argument", STDERR_FILENO);
	return (0);
}

/*
** Syntax errors are errors that exit with 258
*/

int				syntax_errors(int status, char *str)
{
	if (status >> 9 & ERR_SQUOTE)
	{
		ft_putstr_fd("unexpected EOF while looking for matching `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		ft_putstr_fd(find_env_value("0"), STDERR_FILENO);
		ft_putstr_fd(": syntax error: ", STDERR_FILENO);
		ft_putendl_fd("unexpected end of file", STDERR_FILENO);
		return (0);
	}
	if (status >> 9 & ERR_REDIR)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		return (0);
	}
	ft_putstr_fd(str, STDERR_FILENO);
	if (status >> 9 & ERR_BAD_FD)
		ft_putendl_fd(": Bad file descriptor", STDERR_FILENO);
	if (status >> 9 & ERR_NUMERIC)
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	return (0);
}