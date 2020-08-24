/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_from_exec_proc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 16:10:50 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/24 16:11:43 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "hash.h"

/*
** If we do not find a cmd by the path saved in the table or
** the cmd is non-executable - we try to find an executable one
** If we find the path and it is valid, we increase the number
** of address to the cmd and return the path-value
*/

char			*hashtable_check_valid(int index, char *key,
					void **hashtable, int hashtable_size)
{
	t_hashcmd	*slot_ptr;
	struct stat	stat_buf;
	
	slot_ptr = (t_hashcmd*)hashtable[index];
	if (access(slot_ptr->cmd_path, F_OK) == -1 ||
			access(slot_ptr->cmd_path, X_OK) == -1 ||
			stat(slot_ptr->cmd_path, &stat_buf) != 0
			|| (stat_buf.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) == 0 ||
			S_ISREG(stat_buf.st_mode) == 0)
	{
		printf("    command saved in hashtable is invalid\n");
		clear_hash_cell(index, hashtable, 0);
		return (hash_key_not_found(key, hashtable, hashtable_size, index));
	}
	slot_ptr->number++;
	return (ft_strdup(slot_ptr->cmd_path));
}

char			*hashtable_cmd_init_noninteractive(char *key)
{
	char		*path;
	
	path = path_search(key);
	if (path_init_errors(path, key) < 0)
		return (NULL);
	return (path);
}