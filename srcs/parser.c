#include "../parser.h"

/*
** functioun to check if find char is in use or just text
*/

int	ft_backslash_find(char *start, char *str)
{
	if (str > start && *(str - 1) != '\')
		return(0);
	else
		return(1);
}

/*
** Parser function that gets **string from Readline or from argv
** and separetes it to blockes to start
*/

int	ft_parser(char **str)
{
	char	**str_tech;
	char	*line;

	line = {0, ' ', '\\', ';', '&', '\"','\'', '(', ')', '[', ']', '{', '}', '$', '~', '|', '>', '<', '*'};
	//		0	1	 2	   3	4	 5	  6		7	 8	  9	  10	11	12	  13   14   15   16   17   18
	str_pars = NULL;
	if (ft_brackets(str) != 0)
		ft_readline(str);
	else
	{
		ft_get_techline(str, str_tech);
	}
}