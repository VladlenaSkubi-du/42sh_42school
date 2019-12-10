#include "readline.h"
#define ACTIONS_MAX 10

t_action_stack	*action_new(void)
{
	t_action_stack	*new;

	new = (t_action_stack *)xmalloc(sizeof(t_action_stack))
	new->cmd_b = (char *)xmalloc(ft_strlen(g_rline->cmd) + 1);
	ft_strcpy(new->cmd_b, g_rline->cmd);
	new->pos_b = g_rline->pos;
	new->num_b = g_rline->str_num;
	new->next = 0;
	new->prev = 0;
	return (new);
}

int				action_add(t_action_stack **start, t_action_stack **end)
{
	t_action_stack	*new;

	new = action_new();
	if (!(*start))
	{
		*start = new;
		*end = *start;
		return (0);
	}
	(*start)->prev = new;
	new->next = *start;
	*start = new;
	return  (0);
}

void			action_alloc_management(t_action_stack *start)
{
	static t_action_stack	save;
	t_action_stack			*temp;

	if (start)
		save = start;
	else
	{
		while (save)
		{
			temp = save;
			save = save->next;
			free(temp->cmd_b);
			free(temp);
		}
	}
}

void			action_pull(t_action_stack **start)
{
	t_action_stack			*temp;

	temp = *start;
	if (start && *start)
	{
		g_rline->cmd = (*start)->cmd_b;
		g_rline->pos = (*start)->pos_b;
		g_rline->str_num = (*start)->num_b;
		*start = (*start)->next;
		*start->prev = 0;
		free(temp);
	}
}

int		undo(int mode)
{
	static t_action_stack	actions = 0;
	static t_action_stack	end = 0;
	static size_t			actions_num = 0;

	if (!mode)
	{
		action_add(&actions, &end);
		actions_num++;
	}
	else if (actions_num)
	{
		action_pull(&actions)
		actions_num--;
	}
	action_alloc_management(actions);
	if (actions_num > ACTIONS_MAX)
	{
		end->prev->next = 0;
		free(end)
		actions_num--;
	}
	return (0);
}