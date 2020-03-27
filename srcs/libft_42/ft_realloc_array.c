#include "shell42.h"
#include "libft_42.h"

char				**ft_realloc_array(char ***subj, int len_subj,
						int len_needed)
{
	int				i;
	char			**new;
	char			**old;

	i = 0;
	old = *subj;
	new = (char**)ft_xmalloc(sizeof(char*) * (len_needed + 1));
	while (old[i])
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	ft_arrdel(old);
	old = NULL;
	return (new);
}
