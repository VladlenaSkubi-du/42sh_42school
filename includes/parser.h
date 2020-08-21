
#ifndef PARSER_H
# define PARSER_H

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

# define HEREDOC_BUF 200

/*
** Defines for FLAGS
*/

# define PIPED_OUT		0x00000001U
# define PIPED_IN		0x00000002U
# define REDIRECTION	0x00000004U
# define IS_BG			0x00000008U
# define LOG_AND_IN		0x00000010U
# define LOG_AND_OUT	0x00000020U
# define LOG_OR_IN		0x00000040U
# define LOG_OR_OUT		0x00000080U
# define GR_START		0x00000100U
# define ERR_EXSIGN		0x00000800U
# define ERR_IN			0x40000000U
# define ERR_R			0x20000000U
# define ERR_CONT		0x08000000U
# define ERR_OUT		0x10000000U

/*
** Is used in before_execution.c
*/

/*
** This defines needs for usage ft_tmpfile
*/

# define TMPL "tmp42sh_424242XXXXXX"

# define P_TMPDIR P_tmpdir
# ifndef P_tmpdir
#  define P_TMPDIR "/tmp"
# endif

# define L_TMPNAM 20

# define TMPFILE_TRY_SIZE 2000

/*
** @REW, @FF - flags used in rediretion to switch direction of find WORD
** @CLOSE - flag used in redirection to set fd like closed
** @MINUS - flag used in here-document to set "-" to delete tabs
** @CONTINUE - flag in t_ltree->flags to set block compile
** @LINE, @ASSIGN - used to choose mode of tilda expantion - like in line or in
** asssignment like "PATH=$PATH:~/dir"
*/

enum					e_way
{
	REW,
	FF,
	HERE,
	CLOSE = -42,
	SAVE,
	MINUS = 5,
	CONTINUE,
	PRINT,
	DEL_ALL,
	LINE,
	ASSIGN,
};

typedef	struct			s_word
{
	size_t				start;
	size_t				len;
}						t_word;

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
** @l_cmd is char line
** @l_tline is structure of tech chars and len info
** @start is the index with that block in l_cmd starts
** @end is the index with that block in l_cmd ends
** @fd is list of fd for redirection
** @envir is environment for the command to be executed
** @ar_v is an agrument for the command to be executed
** @ar_c is a number of arguments for the command to be executed
** @flags is int for bit masks
** @token is string of nearest token if error detected
** @err is string with text of error
** @err_i is index in l_cmd where error is detected
*/

typedef struct			s_ltree
{
	char				*l_cmd;
	t_tech				l_tline;
	int					start;
	int					end;
	t_list				*fd;
	char				**envir;
	char				**ar_v;
	int					ar_c;
	size_t				flags;
	char				*token;
	char				*err;
	size_t				err_i;
}						t_ltree;

/*
** Struct needs for list of redirections before exec
*/

typedef struct			s_fd
{
	int					fd_new;
	int					fd_old;
	int					type;
	char				*name;
}						t_fd_redir;

enum					e_redir
{
	GREAT,
	DGREAT,
	GREATAND,
	LESS,
	DLESS,
	DLESS_MIN,
	LESSAND,
};

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

/*
** Struct to save and work with here-docs
*/

typedef struct			s_stop
{
	char				*stop_w;
	int					flag;
	int					fd;
}						t_stop;

typedef struct			s_here
{
	t_list				*list;
	t_stop				stop;
	char				*g_cmd_copy;
	char				*g_techline_copy;
	size_t				g_len_copy; //нужно??
	char				**buf;
	int					buf_size;
}						t_here;

/*
** Global vars
*/

char					*g_cmd;
t_tech					g_techline;
t_here					g_heredoc;
t_list					*g_start_list;

/*
** File parser42.c
*/

int						parser(char *line);
int						pars_lex_exec(void);
int						ft_get_techline(char *cmd, t_tech *result);
char					get_tech_num(char check);
int						ltree_init(t_ltree *final);

/*
** File parser_processing.c
*/

int						shift_cmd_substitution(char **lcmd, int start,
							int end, int len_subst);
int						shift_techline_substitution(t_tech *tline, int start,
							int end, int len_subst);
void					clear_techline(t_tech *techline);

/*
** File slice_to_blocks.c
*/

int 					ft_block_start(t_list **list);
int						ft_block_foward(t_ltree **sub, t_list **start);
int						ft_block_add_to_list(t_ltree *block, t_list **list);
int     				ft_slice_fg(void);
int     				ft_slice_bg(size_t *i, t_ltree	*block, t_list **start_list);

/*
** File find_spec.c
*/

t_ltree					*ft_find_pipe(t_ltree *block, t_ltree *final, int *i);
t_ltree					*ft_find_logic(t_ltree *block, t_ltree *final);
t_ltree					*ft_check_andor_pipes(t_ltree *block, t_ltree *final,\
						t_list **list);
void					ft_lst_ltree_clear(t_list **begin_list);
int						ft_correct_after_andor_pipe(int *i);

/*
** File before_execution.c
*/

int						before_exec(t_ltree *sub);
int						argv_forming(t_ltree *sub);
t_word					ft_give_me_word(char const *s, char c, size_t len);
int						ft_local_copy_lines(t_ltree *sub, char *cmd,
							char *tline);
int						erroring_andor_pipe(t_ltree *final, int *i,
						int tmp, size_t block_end);

/*
** Folder REDIRECTION
** ____________________________________________________________________________
*/

/*
** File ft_tmpfile.c
*/

int						ft_tmpfile(char *template, int *fd);

/*
** File redirect.c
*/

int						ft_find_redirection_check(t_ltree *final, int *i);
char					*ft_word_to_redir(int *i, t_ltree *final,
							int rew_ff);
int						ft_word_to_redir_rew(int *i, t_ltree *final,
						long long *size, size_t *start);
int						ft_null_redir(t_ltree *pos, size_t i, long long num);
int						ft_error_redir(t_ltree *final);

/*
** File redir_types_out_check.c
*/

int						ft_redir_check(t_ltree *final);
int						ft_redir_great_check(t_ltree *final, int *i);
int						ft_redir_dgreat_check(t_ltree *final, int *i);
int						ft_redir_greatand_check(t_ltree *final, int *i);
int						ft_access_check(char **f_name, t_ltree *final,
							int type);

/*
** File redir_types_out_do.c
*/

void					ft_find_redirection_do(t_ltree *final);
int						ft_redir_great_do(t_ltree *final, t_fd_redir *fd);
int						ft_redir_dgreat_do(t_ltree *final, t_fd_redir *fd);
int						ft_redir_greatand_do(t_ltree *final, t_fd_redir *fd);

/*
** File redir_types_in_check.c
*/

int						ft_redir_less_check(t_ltree *final, int *i);
int						ft_redir_dless(t_ltree *final, int *i);
int						ft_redir_dless_min(t_ltree *final, int *i);
int						ft_redir_lessand_check(t_ltree *final, int *i);
int						ft_heredoc_form(t_fd_redir *fd_open, char **f_name,
						t_ltree *final, int flag);

/*
** File redir_types_in_do.c
*/

int						ft_redir_less_do(t_ltree *final, t_fd_redir *fd);
int						ft_redir_lessand_do(t_ltree *final, t_fd_redir *fd);
int						ft_redir_valid(t_ltree *final, int i);

/*
** File fd_block.c
*/

int						add_redir_fd(t_ltree *final, t_fd_redir *redir);
int						ft_check_n_redir_op(int i, t_ltree *final, int std);
int						ft_check_redir_op_n(char *find, int std);
int						ft_num_or_word_out(char **f_name, t_fd_redir *fd_open,
							t_ltree *final);
int						ft_num_or_word_in(char **f_name, t_fd_redir *fd_open,
							t_ltree *final);

/*
** File here_doc.c
*/

int						ft_check_is_heredoc(int	ret);
int						ft_check_heredoc_end(void);
int						ft_heredoc_fill(int ret);
int						ft_heredoc_rem(void);
int						ft_g_init_heredoc(void);

/*
** File here_doc_buffer.c
*/

int						add_to_heredoc_buf(char ***array, char *add,
						int *buf_size);
int						ft_sub_heredoc(t_ltree *sub);
int						null_here_line(void);
int						recover_g_cmd_here(void);
int						here_tab_remove(char **line);

/*
** Folder ASSIGNMENT
** ____________________________________________________________________________
*/

/*
** File backend_variables.c
*/

int             		find_assignment_in_vars(char *sub, size_t var,
							size_t eq, size_t val);
int						assignment_in_curv_var(t_ltree *sub,
							char **line, char *oper, int *i);
int						ft_colon_check(int *len, char **line,
							char **oper, size_t *j);
int						ft_alias_find(t_ltree *sub);

/*
** File assignment.c
*/

int						assignment(t_ltree *sub);
int						check_kind_assign(int i, int len_arg,
							char **arg_tline);
int						is_it_command(int i, char **arg_tline, int eq);
int						add_new_local_env(t_ltree *sub, int i,
							char **arg_tline);
int						assign_local_or_err(t_ltree *sub, char **find,
							int start);

/*
** File assignment_local.c
*/

int						change_var_in_local(t_ltree *sub, char **find,
							int start);
int						new_var_in_local(t_ltree *sub, char **find, int start);
int						form_local_str_from_arrays(t_ltree *sub, int i,
							char **arg_tline);
int						unset_from_array(char ***arr, int i);
int						add_vars_to_genvi(t_ltree *sub, char **arg_tline);


/*
** Folder SUBSTITUTION
** ____________________________________________________________________________
*/

/*
** File substitution.c
*/

int						ft_substitution(t_ltree *sub);
int						before_add(t_ltree *sub, t_list **lst);
int						ft_check_null(t_ltree *final, t_list **list);
int						insert_str_in_loc_strs(t_ltree *sub,
							char **insert, int *i, int flag);

/*
** File ft_find_var.c
*/

int	   					ft_find_var(t_ltree *sub);
int						ft_find_curv_var(t_ltree *sub);
char					*ft_find_var_value(char **find);
int						ft_param_empty(t_ltree *sub, char **find, int *i);
int						ft_error_vars(t_ltree *sub, int err, char *msg);

/*
** File ft_curv_var.c
*/

int						ft_type_param_check(t_ltree *sub, char **find,
							int *i);
int						ft_param_colon_dash(t_ltree *sub,
							char **line, char *oper, int *i);
int						ft_param_colon_equal(t_ltree *sub,
							char **line, char *oper, int *i);
int						ft_param_colon_qmark(t_ltree *sub,
							char **line, char *oper, int *i);
int						ft_param_colon_plus(t_ltree *sub,
							char **line, char *oper, int *i);

/*
** File ft_substring_var.c
*/

int						ft_substring_len(t_ltree *sub, char **line,
							char *oper, int *i);
int						ft_substring_s_l_prefix(t_ltree *sub,
							char **line, char *oper, int *i);
int						ft_substring_s_l_suffix(t_ltree *sub,
								char **line, char *oper, int *i);

/*
** File param_help_func.c
*/

int						ft_param_word_sub(t_ltree *sub,
							char **line, char *oper, int *i);
void					ft_one_ltree_clear(t_ltree *buf);
int     				ft_param_error_msg(t_ltree *sub, char **find,
							char *oper);
char					*ft_parsing_str(char *str);

/*
** File tilda.c
*/

int						ft_find_tilda(t_ltree *sub, int flag);
int						ft_getdir_by_name(t_ltree *sub, int *i, int flag);
int						ft_get_home(t_ltree *sub, int *i);
int						ft_find_dir_info(t_ltree *sub, char *user, int *i);
int						ft_find_dir_by_uid(t_ltree *sub, char *uid, int *i);

/*
** File history_sign.c
*/

int						ft_find_history(t_ltree *sub);

/*
** Folder QUOTING
** ____________________________________________________________________________
*/

/*
** File quote_control.c
*/

int						nullify(char **techline, size_t size);
int						nullify_dquotes(char **ptr, t_stack **stack);
int						nullify_backslash(char **ptr, t_stack **stack,\
						size_t *count, size_t size);
int						nullify_comment(char **ptr, t_stack **stack);
int						nullify_promt_check(t_stack	**stack);

/*
** File quote_control_err.c
*/

int						nullify_error(t_stack **stack);

/*
** File pre_parsing_work.c
*/

int						pre_parsing_cut_glue(t_ltree *sub);
int						pre_parsing_squote(int *i, t_ltree *sub);
int						pre_parsing_back(int *i, t_ltree *sub);
int						pre_parsing_andor_pipe(int *i, t_ltree *sub);
int						ft_reglue(int *i, int num, t_ltree *sub);

/*
** File pre_parsing_ansi.c
*/

int						pre_parsing_ansi(int *i, t_ltree *sub);
int						ansi_table_check(char *symbol, int *i, t_ltree *sub);
int						ansi_esc_symbols(char *symbol, int *i, t_ltree *sub);
int						ansi_esc_hex_symbols(char *symbol, int *i,
							t_ltree *sub);

/*
** Folder PATH_TREE
** ____________________________________________________________________________
*/

/*
** File ft_path.c
*/

char					**ft_path_pars(char *find, char *path,
							size_t *total, int *size_max);
void					ft_get_path(char *name, t_path **root,
							size_t *len, char *find);
void					insert_in_bintree(char *dp_name, t_path **root, size_t *len);

/*
** File ft_path_help.c
*/

int						ft_insert_prev(t_path **current,
							t_path **parent, t_path **temp, size_t *len);
int						ft_insert_next(t_path **current,
							t_path **parent, t_path **temp, size_t *len);
int						ft_path_free(t_path **root);
int						ft_input_builtins(t_path **root, size_t *len, char *find);

/*
** File ft_block.c funcs to add and spend massive char **str of exe files
*/

char					**ft_add_block(t_path **root, size_t len, int *max);
char					*ft_take_path(char *dir_name);
void					ft_addpath(char *name, t_path **buf);

#endif
