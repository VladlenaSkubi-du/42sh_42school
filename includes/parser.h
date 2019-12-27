/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:04:04 by hshawand          #+#    #+#             */
/*   Updated: 2019/12/20 00:06:27 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include <unistd.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <sys/stat.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <pwd.h>
# include <string.h>
# include <sys/acl.h>

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

/*
** Struct to save and work with techline
*/
typedef struct  		s_tech
{
   char					*line;
   size_t				len;
}               		t_tech;

/*
** Struct to work with lextree
*/

typedef struct  		s_ltree
{
	size_t				start; //index of start
	size_t				end;
}              			t_ltree;

/*
** Struct to save and work with env
** flag needs to know main list
*/

typedef struct  		s_block
{
	char				*name;
	char				*path;
	struct s_block		*next;
	struct s_block		*prev;
	struct s_block		*down;
	struct s_block		*up;
	char				flag;
}               		t_block;

/*
** Struct to save and work with PATH
*/

typedef struct  		s_path
{
	char				*name;
	char				*path;
	struct s_path		*next;
	struct s_path		*prev;
	char				flag;
}               		t_path;

/*
**Global vars
*/

char					*g_cmd;
size_t					g_cmd_size;
t_tech					*g_techline;

/*
** File pareser.c
*/

int						parser(char *line);

/*
** File quote_control.c
*/

int						nullify(void);

/*
** File brackets.c
*/

int						ft_brackets(char *str, int end);

/*
** File slice_to_blocks.c
*/

int 					ft_block_start_fg(t_ltree *block);
int						ft_block_start_bg(t_ltree *block);
int     				ft_slice(void);

/*
** File find_spec.c
*/

t_ltree					*ft_find_spec(t_ltree *block);

/*
** File ft_path.c
*/

char					**ft_path_pars(char *find, char *path);
void					ft_get_path(char *name, t_path **root, size_t *len, char *find);

/*
** File ft_block.c funcs to add and spend massive char **str of exe files
*/

char					**ft_add_block(t_path **root, size_t len);
char					*ft_take_path(char *dir_name);
void					ft_addpath(char *name, t_path *buf);



#endif