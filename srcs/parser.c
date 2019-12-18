#include "../includes/parser.h"
#include "../includes/parser.h"

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
** and do tech line
*/

int	ft_techline(char **str)
{
	char	*str_tech;
	char	*line;
	int		i;

	line = {' ', '\\', ';', '&', '\"','\'', '(', ')', '[', ']', '{', '}', '$', '~', '|', '>', '<', '*'};
	//		0	 1	   2	3	 4	  5		6	  7	   8	9	10	 11	  12   13   14   15   16   17
	if (!(str_tech = ft_strdup(*str)))
		return (1);
	i = 0;
	while (*str[i])
	{
		j = -1;
		while (++j < 19)
		{
			if (j != 18)
				if (str_tech[i] == line[j])
					str_tech[i] = j;
			else
					str_tech[i] = 0;
		}
		i++;
	}
}