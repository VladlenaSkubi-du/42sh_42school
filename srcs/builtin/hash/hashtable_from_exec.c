/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_from_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:26:49 by sschmele          #+#    #+#             */
/*   Updated: 2020/09/04 20:09:15 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "hash.h"

static int		g_hash_command_error_static;
static char		*g_hash_command_error_name_static;

/*
** Is called form the path_init_function - needs path to be returned
** path can be NULL or a malloced char*
*/

char			*hashtable_cmd_init(char *key)
{
	void		**hashtable;
	int			hashtable_size;
	int			index;

	if (ft_atoi(find_env_value("42SH_NONINTERACTIVE")) > 0)
		return (hashtable_cmd_init_noninteractive(key));
	hashtable_size = -1;
	hashtable = get_hashtable_value(&hashtable_size);
	if (hashtable_size < 0)
		return (NULL);
	index = hashtable_find(key, hashtable, hashtable_size);
	if (index == HASHTABLE_NF)
		return (hash_key_not_found(key, hashtable, hashtable_size, index));
	return (hashtable_check_valid(index, key, hashtable, hashtable_size));
}

/*
** Here we search a command according to the PATH value
** @path can be NULL or a malloced char*
** If @path has a path-value and in hashtable_add a new slot was added,
** slot is updated and thee number of address to the command grows
** If command is non-executable, it is noted in the table and
** an error is returned
*/

char			*hash_key_not_found(char *key, void **hashtable,
					int hashtable_size, int index)
{
	char		*path;
	t_hashcmd	*slot_ptr;

	path = hashtable_add(key, hashtable, hashtable_size, &index);
	if (!path)
	{
		save_command_error(COMMAND_NOT_FOUND | (ERR_COMMAND << 9), key);
		exit_status_variables((COMMAND_NOT_FOUND | (ERR_COMMAND << 9)) & 0x7F);
		return (NULL);
	}
	slot_ptr = (t_hashcmd*)hashtable[index];
	update_hashtable_slot_filled(&slot_ptr);
	hashtable = get_hashtable_value(&hashtable_size);
	slot_ptr->number++;
	if (slot_ptr->cmd_state == CDM_NON_EXEC)
	{
		free(path);
		save_command_error(COMMAND_NON_EXECUTABLE | (ERR_NO_ACC << 9),
			slot_ptr->cmd_path);
		exit_status_variables((COMMAND_NON_EXECUTABLE |
			(ERR_NO_ACC << 9)) & 0x7F);
		return (NULL);
	}
	slot_ptr->cmd_state = 0;
	g_hash_command_error_static = 0;
	return (path);
}

int				save_command_error(int error, char *cmd_name)
{
	g_hash_command_error_static = error;
	g_hash_command_error_name_static = cmd_name;
	return (0);
}

int				get_command_error(void)
{
	return (g_hash_command_error_static);
}

char			*get_command_error_name(void)
{
	return (g_hash_command_error_name_static);
}
