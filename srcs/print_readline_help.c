/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_readline_help.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 20:00:31 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/23 15:37:06 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		print_help(short flag)
{
	char		*space;
	short		undo;

	space = "     ";
	undo = 10;
	ft_putendl_fd("42sh, version 0.0.1", 1);
	ft_putendl_fd("42sh long options:", 1);
	ft_printf("%s--readline\n", space);
	ft_printf("%s--simple\n", space);
	print_readline_help(flag, undo, space);
}

void		print_readline_help(short flag, short undo, char *space)
{
	ft_putendl_fd("Keyboard Shortcuts:", 1);
	ft_printf("%sMoving the cursor:\n", space);
	ft_printf("%s'Ctrl + a' - Go to the beginning of the line\n", space);
	ft_printf("%s'Ctrl + e' - Go to the end of the line\n", space);
	if (flag == 2)
	{
		ft_printf("%s'Esc + b' - Back (left) one word\n", space);
		ft_printf("%s'Esc + f' - Forward (right) one word\n", space);
	}
	ft_printf("%s'Ctrl + b or < (left)' - Backward one character\n", space);
	ft_printf("%s'Ctrl + f or > (right)' - Forward one character\n", space);
	ft_putchar('\n');
	ft_printf("%sCut, copy and paste:\n", space);
	ft_printf("%s'Backspace' - Delete one character ", space);
	ft_printf("to the left of the cursor\n");
	if (flag == 2)
	{
		ft_printf("%s'Delete or Ctrl + d' - Delete one character ", space);
		ft_printf("underneath the cursor\n");
	}
	printf_readline_help_further(flag, undo, space);
}

void		printf_readline_help_further(short flag, short undo, char *space)
{
	ft_printf("%s'Ctrl + u' - Delete from the cursor ", space);
	ft_printf("back to the line start\n");
	ft_printf("%s'Ctrl + k' - Delete from the cursor ", space);
	ft_printf("to the end of the line\n");
	if (flag == 2)
	{
		ft_printf("%s'Esc + d' - Delete untill before ", space);
		ft_printf("the next word boundary\n");
		ft_printf("%s'Ctrl + w' - Delete untill after ", space);
		ft_printf("the previous word boundary\n");
	}
	ft_putchar('\n');
	ft_printf("%sUndo:\n", space);
	ft_printf("%s'Esc + r' - Undo all changes, clear the line\n", space);
	if (flag == 2)
	{
		ft_printf("%s'Ctrl + _' or 'Ctrl + x + Ctrl + u' - Undo the last ", space);
		ft_printf("editing command you can undo %hd operations\n", undo);
		ft_printf("%s'Ctrl + l' - Clear the screen, reprinting ", space);
		ft_printf("the current line at the top\n");
		ft_putchar('\n');
		ft_printf("%sTranspose:\n", space);
		ft_printf("%s'Ctrl + t' - Swap characters\n", space);
		ft_printf("%s'Esc + t' - Swap words\n", space);
	}
}