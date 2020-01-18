#include "../includes/parser.h"

int		parser(char *line)
{
	g_cmd = line;
	g_cmd_size = ft_strlen(g_cmd);
	// ft_get_techline();
	// nullify();
	// ft_slice();
	if (line != NULL)
		ft_putendl_fd(line, 1);
	free(line);
	return (0);
}

/*
** functioun to check if find char is in use or just text
*/

char	get_tech_num(char check)
{
	char	*base;
	size_t	i;

	base = " \\;&\"\'()[]{}$~|><*\n";
	i = 0;
	while (base[i])
	{
		if (base[i] == check)
			return (i + 1);
		i++;
	}
	return (0);
}

int		ft_get_techline(void)
{
	size_t	i;

	i = 0;
	g_techline->line = (char *)ft_xmalloc(g_cmd_size);
	while (g_cmd[i])
	{
		g_techline->line[i] = get_tech_num(g_cmd[i]);
		i++;
	}
	g_techline->len = i;
	return (0);
}

/*
int	ft_backslash_find(char *start, char *str)
{
	if (str > start && *(str - 1) != '\\')
		return(0);
	else
		return(1);
}
*/
/*
** Parser function that gets **string from Readline or from argv
** and do tech line
*/
/*
int	ft_parser(char **str)
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
*/
