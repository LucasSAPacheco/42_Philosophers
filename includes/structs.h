/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantana <lsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:40:58 by lsantana          #+#    #+#             */
/*   Updated: 2023/03/13 18:57:52 by lsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_STRUCTS_H
# define PRINTF_STRUCTS_H

typedef pthread_mutex_t	t_mutex;
typedef pthread_t   t_thread;
typedef struct timeval	t_timeval;

typedef enum t_bool
{
    FALSE,
    TRUE
} t_bool;

typedef struct s_common
{
    int     nums_philos;
    size_t    time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    int     must_eat;
    int     finish_eat;
    size_t  start_time;
    t_bool  someone_died;
    t_mutex *print_control;
    t_mutex *control;
} t_common;

typedef struct s_philo
{
    int             id;
    int             eat_count;
    t_mutex         *left_fork;
    t_mutex         *right_fork;
    size_t          last_eat;
    t_common        *c_data;
} t_philo;

#endif