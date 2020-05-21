#include "shell42.h"
#include "readline.h"

int			make_ctrl_x(void)
{
	char			next;

	check_menu();
	read(1, &next, 1);
	if (next == '\025')
		undo(1);
	else
		incorrect_sequence();
	return (0);
}

int			undo_wrap(void)
{
	return (undo(1));
}

int			make_ctrl_p_wrap(void)
{
	return (make_ctrl_p(1, NULL));
}
