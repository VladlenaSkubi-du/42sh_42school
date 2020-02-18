/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:15:50 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/18 21:33:28 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** It needs to check must to go to here-doc mode or not
*/

int		ft_check_is_heredoc(int ret)
{
	if (g_heredoc.list != NULL && g_prompt.prompt_func != heredoc_prompt)
	{
		g_prompt.prompt_func = heredoc_prompt;
		return (OUT);
	}
	else if (g_heredoc.list != NULL)
		if (ft_check_heredoc_end(ret) == OUT)
			return (OUT);
	ft_heredoc_fill(ret);
	return (ret);
}

/*
** It needs to check here-docs correctly ends
*/

int		ft_check_heredoc_end(int ret)
{
	t_list	*tmp;
	char	**lines_in;
	int		i;
	t_stop	*find;
	
	tmp = g_heredoc.list;
	lines_in = ft_strsplit(&g_cmd[g_heredoc.start], '\n');
	i = -1;
	while (tmp)
	{
		find = (t_stop *)tmp->content;
		while (lines_in[++i])
		{
			if (!ft_strcmp(find->stop_w, lines_in[i]))
				break ;
		}
		tmp = tmp->next;
		if (tmp != NULL && lines_in[i] == NULL)
		{
			ft_arrdel(lines_in);
			return (OUT);
		}
	}
	ft_arrdel(lines_in);
	return(ret);
}

/*
** function fills fd of tmp files by here-docs
*/

int		ft_heredoc_fill(int ret)
{
	t_list	*tmp;
	char	**lines_in;
	int		i;
	t_stop	*find;
	
	tmp = g_heredoc.list;
	lines_in = ft_strsplit(&g_cmd[g_heredoc.start], '\n');
	i = -1;
	while (tmp)
	{
		find = (t_stop *)tmp->content;
		while (lines_in[++i])
		{
			if (!ft_strcmp(find->stop_w, lines_in[i]))
				break ;
			ft_putendl_fd(lines_in[i], find->fd);			
		}
		tmp = tmp->next;
	}
	ft_arrdel(lines_in);
	g_prompt.prompt_func = main_prompt;
	return (ret);
}

/*
** function frees g_heardoc content
*/

int		ft_heredoc_rem(int ret)
{
	t_list	*tmp;
	t_stop	*find;

	tmp = g_heredoc.list;
	while(tmp)
	{
		find = (t_stop *)tmp->content;
		free(find->stop_w);
		tmp = tmp->next;
	}
	ft_lstclear(&g_heredoc.list);
	return (0);
}
