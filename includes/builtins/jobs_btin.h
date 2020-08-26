/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_btin.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 12:10:42 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/26 12:16:34 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBS_BTIN_H
# define JOBS_BTIN_H

/*
** File jobs_main_btin.c
*/

int				btin_jobs_init(int argc, char **argv);
int				print_job_info(t_job *j, int options);
int				get_status(t_job *j, char *buff, int options);

/*
** File jobs_id_btin.c
*/

int				print_by_id(int argc, char **argv, int options);
int				id_check(int argc, char **argv);

/*
** File jobs_btin_processing.c
*/

int				btin_jobs_check_options(char **argv, int *iter);
int				btin_jobs_error_message(char *option, int error);

#endif
