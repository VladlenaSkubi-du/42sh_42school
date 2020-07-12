#include <shell42.h>
#include <cd.h>

static char	*oldpwd;
static char *pwd;

char	*get_oldpwd_value(void)
{
	return (oldpwd);
}

int		change_oldpwd_value(char *str)
{
	free(oldpwd);
	oldpwd = ft_strdup(str);
	return (0);
}

int		cd_free_static(void)
{
	free(oldpwd);
	free(pwd);
	return (0);
}

char	*get_pwd_value(void)
{
	return (pwd);
}

int		change_pwd_value(char *str)
{
	free(pwd);
	pwd = ft_strdup(str);
	return (0);
}
