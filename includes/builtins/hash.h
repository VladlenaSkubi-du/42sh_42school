#ifndef HASH_H
# define HASH_H

# define			HASHTABLE_LENGTH 4

/*
** For going out from functions, for convenience
** HASHTABLE_NF - did not find cmd in hashtable
** 
*/

# define			HASHTABLE_NF -1
# define			HASH_INVALID -2

typedef struct		s_hashcmd
{
	char			*cmd_name;
	char			*cmd_path;
	int				number;
}					t_hashcmd;

char			*hashtable_cmd_init(char *key);
int				hashtable_find(char *key);
char			*hashtable_add(char *key);
int				hashtable_check_valid(int index, char *key);
char			*hashtable_change(int index, char *key);

int				hashtable_init(void);
void			*get_hashtable_value(int *size);
int				change_hastable_value(void *hastable_array_new,
					int hashtable_array_size_new);
int				hashtable_clean(void);
t_hashcmd		*init_hash_cell(char *key);
void			clear_hash_cell(int index);

int				hashfunction(char *cmd);

#endif
