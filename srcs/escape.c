#include "readline.h"
#define ESC_NUM 4

/*
** Function pointer array, should return function call
*/

static int		sequence_process(int sequence_num)
{
	int		(*seq_action[ESC_NUM])(void);

	seq_action[0] = key_right_proc;
	seq_action[1] = key_up_proc;
	seq_action[2] = key_left_proc;
	seq_action[3] = key_down_proc;
	return ((*seq_action[sequence_num])());
}

/*
** Should beep and do nothing
*/

static int		incorrect_sequence(void)
{
	return (0);
}



static int		escape_check(char **seq_base)
{
	size_t	i;
	char	buff[16];
	int		stage;

	i = 0;
	ft_bzero(buff, 16);
	while (read(1, buff + i, 1))
	{
		stage = 0;
		while (stage < ESC_NUM)
		{
			if (!ft_strncmp(buff, seq_base[stage], i + 1))
				break;
			stage++;
		}
		if (stage == ESC_NUM)
			return (incorrect_sequence());
		if (!ft_strncmp(buff, seq_base[stage], ft_strlen(seq_base[stage]) + 1))
			return (sequence_process(stage));
		i++;
	}
	return (0);
}

/*
** We have already read \033, so seq_base is formed without it
** [C -- KEY_RIGHT
** [A -- KEY_UP
** [D -- KEY_LEFT
** [B -- KEY_DOWN
*/

int				escape_init(void)
{
	char	*seq_base[ESC_NUM];

	seq_base[0] = "[C";
	seq_base[1] = "[A";
	seq_base[2] = "[D";
	seq_base[3] = "[B";
	escape_check(seq_base);
	return (0);
}