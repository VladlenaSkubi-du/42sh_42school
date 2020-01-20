/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshawand <hshawand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:04:04 by hshawand          #+#    #+#             */
/*   Updated: 2020/01/20 13:12:47 by hshawand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <dirent.h>
# include <sys/dir.h>
# include <sys/stat.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <pwd.h>
# include <string.h>

# include "exit_status.h"
# include "readline.h"
# include "builtin42.h"
# include "libft.h"
# include "libft_42.h"

# include <stdio.h> //DELETE

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
t_tech					g_techline;

/*
** File parser.c
*/

int						parser(char *line);
int						ft_get_techline(void);
char					get_tech_num(char check);

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
** Folder path_tree____________________________________________________________
*/

/*
** File ft_path.c
*/

char					**ft_path_pars(char *find, char *path, size_t *total);
void					ft_get_path(char *name, t_path **root,
							size_t *len, char *find);

/*
** File ft_path_help.c
*/

int						ft_insert_prev(t_path **current,
							t_path **parent, t_path **temp, size_t *len);
int						ft_insert_next(t_path **current,
							t_path **parent, t_path **temp, size_t *len);
int						ft_path_free(t_path **root);

/*
** File ft_block.c funcs to add and spend massive char **str of exe files
*/

char					**ft_add_block(t_path **root, size_t len);
char					*ft_take_path(char *dir_name);
void					ft_addpath(char *name, t_path **buf);

/*
** Folder exec_________________________________________________________________
*/

/*
** File exec_init.c
*/

int		exec_init(t_ltree *pos);

/*
** File exec_core.c
*/

int		exec_core(char **exec_av);

#endif
