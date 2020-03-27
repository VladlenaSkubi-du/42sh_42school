#include "shell42.h"
#include "builtin42.h"

int				btin_exit(int status)
{
	//TODO чистка парсер
	ft_putendl_fd("exit", STDOUT_FILENO);
	fill_hist_in_file();
	clean_everything();
	//TODO функция, по типу atexit баша, с каким статусом завершилась программа
	exit(status);
}
