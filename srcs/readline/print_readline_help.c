#include "shell42.h"
#include "readline.h"

void		print_help(short flag)
{
	char		*space;
	short		undo;

	space = "     ";
	undo = 10;
	if (flag == 1)
	{
		// ft_putstr_fd(find_env_value("0"), STDOUT_FILENO);
		ft_putendl_fd("e-bash, version 0.0.1", 1);
		ebash_long_options();
	}
	if (flag == 2)
		usage_btin("./42sh");
	if (flag > 2)
		print_readline_help(flag, undo, space);
}

void		print_readline_help(short flag, short undo, char *space)
{
	ft_putendl_fd(((flag == 3) ? "Keyboard Shortcuts for readline:" :
		"Keyboard Shortcuts for simple readline:"), 1);
	ft_printf("%sMoving the cursor:\n", space);
	ft_printf("%s'Ctrl + a' - Go to the beginning of the line\n", space);
	ft_printf("%s'Ctrl + e' - Go to the end of the line\n", space);
	if (flag == 3)
	{
		ft_printf("%s'Esc + b' - Back (left) one word\n", space);
		ft_printf("%s'Esc + f' - Forward (right) one word\n", space);
	}
	ft_printf("%s'Ctrl + b or ◄ (left)' - Backward one character\n", space);
	ft_printf("%s'Ctrl + f or ► (right)' - Forward one character\n", space);
	ft_putchar('\n');
	ft_printf("%sCut, copy and paste:\n", space);
	ft_printf("%s'Backspace' - Delete one character ", space);
	ft_printf("to the left of the cursor\n");
	if (flag == 3)
	{
		ft_printf("%s'Delete or Ctrl + d' - Delete one character ", space);
		ft_printf("underneath the cursor\n");
	}
	printf_readline_help_ccp(flag, undo, space);
}

void		printf_readline_help_ccp(short flag, short undo, char *space)
{
	ft_printf("%s'Ctrl + u' - Delete from the cursor ", space);
	ft_printf("back to the line start\n");
	ft_printf("%s'Ctrl + k' - Delete from the cursor ", space);
	ft_printf("to the end of the line\n");
	if (flag == 3)
	{
		ft_printf("%s'Esc + d' - Delete untill before ", space);
		ft_printf("the next word boundary\n");
		ft_printf("%s'Ctrl + w' - Delete untill after ", space);
		ft_printf("the previous word boundary\n");
	}
	ft_printf("%s'Ctrl + p' - Past the last deleted from the cursor\n", space);
	ft_putchar('\n');
	print_readline_help_other(flag, undo, space);
}

void		print_readline_help_other(short flag, short undo, char *space)
{
	ft_printf("%sUndo:\n", space);
	ft_printf("%s'Esc + r' - Undo all changes, clear the line\n", space);
	if (flag == 3)
	{
		ft_printf("%s'Ctrl + _' or 'Ctrl + x + Ctrl + u' - Undo the ", space);
		ft_printf("last editing command you can undo %hd operations\n", undo);
		ft_printf("%s'Ctrl + l' - Clear the screen, reprinting ", space);
		ft_printf("the current line at the top\n");
		ft_putchar('\n');
		ft_printf("%sTranspose:\n", space);
		ft_printf("%s'Ctrl + t' - Swap characters\n", space);
		ft_printf("%s'Esc + t' - Swap words\n", space);
		ft_printf("%sHistory:\n", space);
		ft_printf("%s'▲ (up)' - Insert the previous command from history ", space);
		ft_printf("instead of the current line\n", space);
		ft_printf("%s'▼ (down)' - Insert the following command from ", space);
		ft_printf("history instead of the current line\n", space);
		ft_printf("%s'Ctrl + r' - Incrementally search the line history\n", space);
	}
}
