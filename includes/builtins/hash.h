#ifndef HASH_H
# define HASH_H

# define			HASHTABLE_LENGTH	20

/*
** For going out from functions, for convenience
** HASHTABLE_NF - did not find cmd in hashtable
** 
*/

# define			HASHTABLE_NF		-1
# define			HASH_INVALID		-2

# define			HASH_ERROR			-3

# define			SLOT_DELETED_HASH	-1
# define			SLOT_FILLED_HASH	1

# define			CDM_NON_EXEC		-1

typedef struct		s_hashcmd
{
	char			*cmd_name;
	char			*cmd_path;
	int				number;
	int				slot_state;
	int				cmd_state;
}					t_hashcmd;

/*
** File hashtable_values.c
*/

int				hashtable_init(void);
void			**get_hashtable_value(int *size);
int				get_hashtable_filled(void);
int				change_hashtable_filled_value(int times);

/*
** File hashtable_slots.c
*/

t_hashcmd		*init_hash_cell(char *key, char *path);
void			clear_hash_cell(int index,
					void **hashtable, int delete_key);
void			clear_hash_cell_full(int index,
					void **hashtable);
int				print_hash_cell(int index, void **hashtable);

/*
** File hashtable_backend.c
*/

char			*hashtable_add(char *key, void **hashtable,
					int hashtable_size, int *index);
int				hashtable_delete(char *key, void **hashtable,
					int hashtable_size, int hashtable_filled);
int				hashtable_clean(void **hashtable,
					int hashtable_size);
int				update_hashtable_slot_filled(t_hashcmd **slot_ptr);

/*
** File hashtable_from_exec.c
*/

char			*hashtable_cmd_init(char *key);
char			*hash_key_not_found(char *key, void **hashtable,
					int hashtable_size, int index);
int				hashtable_find(char *key, void **hashtable,
					int hashtable_size);
char			*hashtable_check_valid(int index, char *key,
					void **hashtable, int hashtable_size);

/*
** File hashtable_from_type.c
*/

char			*hashtable_type_init(int *where, char *key);
char			*hash_key_not_found_type(int *where, char *key);

#endif
