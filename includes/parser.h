/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:04:04 by hshawand          #+#    #+#             */
/*   Updated: 2020/02/10 20:52:33 by rbednar          ###   ########.fr       */
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
# include <fcntl.h>

# include <stdio.h> //DELETE

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

/*
** Defines for FLAGS
*/

# define PIPED_OUT 0x01
# define PIPED_IN 0x02
# define REDIRECTION 0x04
# define IS_BG 0x08
# define LOG_AND 0x10
# define LOG_OR 0x20
# define GR_START 0x40

/*
** Struct to save and work with techline
*/

typedef struct  		s_tech
{
   char					*line;
   size_t				len;
   size_t				alloc_size;
}               		t_tech;

/*
** Struct to work with lextree fd[3] needs to know if it is redirection
** FLAGS:
** 0x01 -- PIPED_OUTPUT
** 0x02 -- PIPED_INPUT
** 0x04 -- REDIRECTION (It's kinda different, as we have to take fd from another place)
** 0x08 -- IS_BG
*/

typedef struct  		s_ltree
{
	size_t				start; //index of start
	size_t				end;
	int					fd[3];
	int					flags;
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
	struct s_path		*next;
	struct s_path		*prev;
	char				flag;
}               		t_path;

typedef struct			s_dquote
{
	char				*cmd_buf;
	size_t				buf_len;
	int					flag_esc;
	int					flag_quote;
	t_stack				*check;
}						t_dquote;

/*
** Global vars
*/

char					*g_cmd;
size_t					g_cmd_size;
t_tech					g_techline;
t_dquote				g_dquote;

/*
** File parser.c
*/

int						parser(char *line);
int						pars_lex_exec(int tmp);
int						ft_get_techline(void);
char					get_tech_num(char check);

/*
** File slice_to_blocks.c
*/

int 					ft_block_start(t_list **list);
int						ft_block_add_to_list(t_ltree *block, t_list **list);
int     				ft_slice_fg(void);
int     				ft_slice_bg(size_t *i, t_ltree	*block, t_list **start_list);

/*
** File find_spec.c
*/

t_ltree					*ft_find_pipe(t_ltree *block, t_ltree *final, int *i);
t_ltree					*ft_find_logic(t_ltree *block, t_ltree *final);
int						ft_find_redirection(t_ltree *final);
char					*ft_word_to_redir(void);

/*
** Folder assignment__________________________________________________________
*/

/*
** File backend_variables.c
*/

int             		find_assignment_in_variables(size_t var,
							size_t eq, size_t val);
int						insert_assign_to_arrays(char *find, size_t var,
							size_t val, char **array);

/*
** Folder quoting_____________________________________________________________
*/

/*
** File check_start_quote.c
*/

void					init_dquote(void);
int						back_to_readline(void);
int						escape_character(void);
int						dquote_character(void);

/*
** File buffer_cmd_processing.c
*/

char					*init_buffer_cmd(size_t cmd_len, char *cmd,
							size_t *buf_len);
char            		*add_buffer_cmd(char *buf_cmd, size_t cmd_len,
                            char *cmd, size_t *buf_len);
char            		*add_buffer_last(char *buf_cmd, size_t cmd_len,
                            char *cmd, size_t *buf_len);

/*
** File block_processing.c
*/

int						dquote_character_open(void);
int						dquote_character_closed(void);
int						clear_cmd_from_slash(int flag);
char					*copy_without_slash_enter(char *cmd,
							char *buf_cmd, size_t *cmd_len, int sl_en);
int						check_quotes(int *flag_quotes, t_stack **check);

/*
** File quote_control.c
*/

int						nullify(char **techline, size_t size);
int						nullify_dquotes(char **ptr, t_stack **stack,\
						size_t *count);
int						nullify_backslash(char **ptr, t_stack **stack,\
						size_t *count);
int						nullify_comment(char **ptr, t_stack **stack);
int						nullify_promt_check(t_stack	**stack);

/*
** File pre_parsing_work.c
*/

int						pre_parsing_cut_glue(void);
int						pre_parsing_squote(size_t *i);
int						pre_parsing_back(size_t *i);
int						ft_reglue(size_t *i, int num);

/*
** Folder path_tree____________________________________________________________
*/

/*
** File ft_path.c
*/

char					**ft_path_pars(char *find, char *path,
							size_t *total, int *size_max);
void					ft_get_path(char *name, t_path **root,
							size_t *len, char *find);
void					insert(char *dp_name, t_path **root, size_t *len);

/*
** File ft_path_help.c
*/

int						ft_insert_prev(t_path **current,
							t_path **parent, t_path **temp, size_t *len);
int						ft_insert_next(t_path **current,
							t_path **parent, t_path **temp, size_t *len);
int						ft_path_free(t_path **root);
int						ft_input_buildins(t_path **root, size_t *len, char *find);

/*
** File ft_block.c funcs to add and spend massive char **str of exe files
*/

char					**ft_add_block(t_path **root, size_t len, int *max);
char					*ft_take_path(char *dir_name);
void					ft_addpath(char *name, t_path **buf);

/*
** Folder exec_________________________________________________________________
*/

/*
** File exec_init.c
*/

int						exec_init(t_ltree *pos);

/*
** File exec_core.c
*/

int						exec_core(char **exec_av, int flags);

#endif
