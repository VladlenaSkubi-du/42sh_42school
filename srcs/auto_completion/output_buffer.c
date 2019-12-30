/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 16:43:04 by vladlenasku       #+#    #+#             */
/*   Updated: 2019/12/30 17:26:35 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#define			OUT_BUF 10

typedef struct			s_buf
{
	char				**buff;
	int					buff_lines;
	size_t				i;
	int					size;
	int					t_width;
	int					s_width;
}						t_buf;


int				buffer_col_init(void)
{
	return (0);
}