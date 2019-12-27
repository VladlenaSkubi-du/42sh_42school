
#include "../includes/parser.h"

int	main()
{
	char	*find;
	char 	*path;
	char 	**res;
	int		i;

	find = "ch";
	path = "/Users/rbednar/fdf/minilibx_macos/man/man3:/Users/rbednar/.brew/opt/openssl@1.1/bin:/Users/rbednar/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/TeX/texbin";
	i = 0;
	res = ft_path_pars(find, path);
	while (res[i])
	{
		printf("%s\n", res[i]);
		i++;
	}
	//free(res);
}
