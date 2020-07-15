#include "shell42.h"
#include "readline.h"

/*
** @pool = pool of variables: binary-files (1), variables (2),
** arguments (3), bell (nothing can be done - 0);
** @total = total number of options
** @max_len = maximal length of the option-string within the whole
** menu array - is needed for the buffer output part
** @tech_line = is needed for analysis of the g_complete string -
** parsing of the g_complete string
** @delete = by each TAB a word-option is added to the
** g_complete part. If this option does not taken by the user and
** the user pushes TAB to change the option - the old option should
** be deleted - as many symbols as in @delete variable
** If there are no options to be auto-completed, there is a bell.
*/

int					auto_completion(void)
{
	int				max_len;
	char			*tech_line;

	if (g_rline.flag & TAB)
	{
		g_compl.tablevel++;
		return (insert_word_compl());
	}
	init_completion();
	max_len = 0;
	tech_line = ft_make_techline(g_compl.to_compl, g_rline.pos);
	if (tech_line[0] == END_T)
		g_compl.menu = route_by_prompts(&g_compl.total, &max_len);
	else
		g_compl.menu = route_menu_receipt(tech_line, g_rline.pos, &max_len);
	free(tech_line);
	if (g_compl.menu == NULL || g_compl.menu[0] == 0)
		return (clear_completion(1));
	if (print_menu(max_len))
		return (clear_completion(0));
	g_compl.len_tocompl = ft_strlen(g_compl.to_compl);
	return (0);
}

/*
** Not in the main prompt pushing TAB in the first-pool position
** will auto-complete directory arguments because other prompts
** usually mean that we already have a program in the cmd-line
*/

char				**route_by_prompts(int *total, int *max_len)
{
	char			**menu;
	t_path			*root;

	if (g_prompt.prompt_func == main_prompt)
	{
		menu = ft_path_pars("", find_env_value("PATH"),
			(size_t*)total, max_len);
	}
	else
	{
		root = fill_tree_with_arguments("./", "", total);
		if (root == NULL)
			return (NULL);
		menu = ft_add_block(&root, (size_t)*total, max_len);
		ft_path_free(&root);
	}
	return (menu);
}

/*
** If the @g_complete line is empty and @pool is 1, menu consists of all
** the binary-options found in the environmental variable PATH and
** in the internal list of builtin programs.
** If @g_complete is not empty and @pool is 1 - the function
** ft_path_pars returns only those options that match.
** The same principle for other pools.
*/

char				**route_menu_receipt(char *tech_line,
						int tech_len, int *max_len)
{
	char			**menu;
	int				pool;
	int				tmp;
	char			*final;

	menu = NULL;
	pool = 0;
	tmp = -1;
	if (g_rline.cmd[g_rline.pos] == 0 || g_rline.cmd[g_rline.pos] == ' ')
		tmp = analyse_techline_compl(g_compl.to_compl,
			tech_line, tech_len, &pool);
	if (tmp < 0)
		return (NULL);
	final = ft_strdup(g_compl.to_compl + tmp);
	free(g_compl.to_compl);
	g_compl.to_compl = final;
	if (pool == 1)
		menu = ft_path_pars(g_compl.to_compl, find_env_value("PATH"),
			(size_t*)&g_compl.total, max_len);
	else if (pool == 2)
		menu = get_variables(g_compl.to_compl, &g_compl.total, max_len);
	else if (pool == 3)
		menu = get_arguments(&g_compl.to_compl, &g_compl.total, max_len);
	return (menu);
}

/*
** Here we insert an option to the cmd-line
** Example: we have "ca[] abcd" where cursor stays on the []
** And the first option to be inserted is the "caffeinate"
** @g_complete is "ca"
** @g_compl_len is 2
** @len_option is 10
** @counter is the position of the word in the menu-buffer, if
** caffeinate is the first word in the list like:
** "caffeinate cal calendar caller cancel cap_mkdb captoinfo case cat"
** @counter will be 1
** @flag is for pool 2: {$PARAMETER}
*/

int					insert_word_compl(void)
{
	int				len_option;
	int				counter;
	int				flag;

	flag = 0;
	clean_after_line();
	(g_compl.to_del > 0) ? delete_till_compl(g_compl.to_del) : 0;
	if (g_compl.tablevel > 0 && g_compl.total > 0)
	{
		if (g_rline.pos > 1 && g_rline.pos - g_compl.len_tocompl - 2 >= 0 &&
				g_rline.cmd[g_rline.pos - g_compl.len_tocompl - 1] == '{' &&
				g_rline.cmd[g_rline.pos - g_compl.len_tocompl - 2] == '$')
			flag = 1;
		counter = (g_compl.tablevel - 1 < g_compl.total) ?
			g_compl.tablevel - 1 : (g_compl.tablevel - 1) % g_compl.total;
		len_option = ((flag == 1) ? ft_strlen(g_compl.menu[counter]) + 1 :
			ft_strlen(g_compl.menu[counter]));
		g_compl.to_del = len_option - g_compl.len_tocompl;
		insert_word_by_cases_compl(&g_compl.to_del, flag,
			g_compl.menu[counter], g_compl.len_tocompl);
		front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x,
			&g_rline.pos_y, 1);
		print_menu_buf_after_insert(g_rline.pos);
	}
	return (0);
}

int					insert_word_by_cases_compl(int *delete, int flag,
						char *menu_word, int compl_len)
{
	int				i;
	int				space;
	
	i = -1;
	space = 0;
	while (++i < *delete - flag)
	{
		if (menu_word[compl_len + i] == ' ')
		{
			char_add_without_undo('\\', NULL);
			space++;
		}
		char_add_without_undo(menu_word[compl_len + i], NULL);
	}
	(flag > 0) ? char_add_without_undo('}', NULL) : 0;
	*delete += space;
	return (0);
}
