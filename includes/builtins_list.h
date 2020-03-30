
#ifndef BUILTINS_LIST_H
# define BUILTINS_LIST_H

# define BUILTINS_NUM 17

static char		*g_builtins[] = {"alias_fff", "unalias_fff", \
	"hash_fff", "set", "unset", "export_fff", \
	"cd", "exit", "echo", "type_fff", "fg_ff", "bg_ff", "jobs_ff", "fc", \
	"history", "pwd", NULL};

static int 		(*g_builtins_func[BUILTINS_NUM])() = {NULL, NULL, \
	NULL, btin_set, btin_unset, NULL, btin_cd, btin_exit, \
	btin_echo, NULL, NULL, NULL, NULL, btin_fc, btin_history, btin_pwd, NULL};

#endif
