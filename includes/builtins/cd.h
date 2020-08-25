/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:08:19 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/25 22:40:19 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

typedef struct	s_cd
{
	int			p;
	int			l;
}				t_cd;

/*
** File cd.c
*/

int				ft_error_cd(char *name, int en);
char			*ft_join_cd(char *path, char *src_path);
int				ft_cd_helper(void);

/*
** File cd_flags.c
*/

int				ft_cd_flags(char **argv, t_cd *flags);

/*
** File cd_valid.c
*/

int				ft_valid_cd(char **argv, int i);

/*
** File cd_parser.c
*/

int				ft_cd_pars(char *path, char **env, t_cd *flags);

/*
** File cd_change_path.c
*/

int				ft_to_dir(char *path);
void			ft_change_pwd(char **env);
int				ft_change_path(char *path, char **env, t_cd *flags);

/*
** File cd_new_path.c
*/

char			*ft_new_path(char *path, char *src_path);

/*
** File cd_static.c
*/

char			*get_oldpwd_value(void);
char			*get_pwd_value(void);
int				change_oldpwd_value(char *str);
int				change_pwd_value(char *str);
int				cd_free_static(void);

#endif
