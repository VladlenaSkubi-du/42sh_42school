
#ifndef LIBFT_42_H
# define LIBFT_42_H

typedef struct					s_stack
{
	int							data;
	struct s_stack				*next;
}								t_stack;

void							*ft_realloc(void *subj, size_t len_subj,
								size_t len, size_t len_needed);
void							*ft_xmalloc(size_t size);
void							swap_chars(char *cmd, int b, int a);
void							swap_ints(int *a, int *b);
int								ft_issign(char c);
char							*ft_straddsy(char *dest, char sy);
int								ft_strrchri(char *s, int c);
void                            ft_add_list_to_end(t_list **start,
									t_list *new_list);
char				            **ft_realloc_array(char ***subj, int len_subj,
									int len_needed);
void                            ft_lstclear(t_list **begin_list);
// t_list	            			*ft_lstlast(t_list **begin_list);
size_t	                        ft_count_words(char const *s, char c,
									size_t len);
size_t			                ft_strlenchri(const char *s, char c);
char                            *ft_find_token_sep(char *str);
int						        ft_gnl(const int fd, char **line);
void							ft_putnendl_fd(char *str, int n, int fd);
void							ft_putnstr_fd(char *str, int n, int fd);
int								ft_strchrdiff(const char *s1, const char *s2, char sy);
int								ft_strchrcmp(const char *s1, const char *s2, char x);

/*
** Folder stack_structure______________________________________________________
*/

/*
** User makes his own safety for the pop-stack function because it returns data
** that is int and it is impossible to return some "wrong" int to show the fail
** Maybe one day I rewrite.
*/

t_stack							*ft_init_stack(void);
int								ft_pop_stack(t_stack **head);
int								ft_push_stack(t_stack **head, int data);
void							ft_clear_stack(t_stack **head);
int				                ft_last_stack(t_stack **head);

#endif
