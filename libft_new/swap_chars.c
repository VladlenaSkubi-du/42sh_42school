/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_chars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 20:29:13 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/18 18:23:33 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_42sh.h"

void		swap_chars(char *cmd, int b, int a)
{
	char	tmp;

	tmp = cmd[b];
	cmd[b] = cmd[a];
	cmd[a] = tmp;
}