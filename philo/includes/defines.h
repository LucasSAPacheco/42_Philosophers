/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantana <lsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:41:15 by lsantana          #+#    #+#             */
/*   Updated: 2023/03/14 15:01:58 by lsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;
typedef struct timeval	t_timeval;

typedef enum t_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_common
{
	int			nums_philos;
	size_t		time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat;
	int			finish_eat;
	size_t		start_time;
	t_bool		someone_died;
	t_mutex		*print_control;
	t_mutex		*control;
	t_mutex		*anyone_died;
}	t_common;

typedef struct s_philo
{
	int			id;
	int			eat_count;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	size_t		last_eat;
	t_common	*c_data;
}	t_philo;

int			ft_atoi(const char *str);
int			ft_isdigit(int c);
int			ft_strlen(char *str);
int			is_number(char *str);
int			check_errors(int argc, char *argv[]);
void		destroy_mutexes(t_philo *philos, t_common *c_data);
size_t		get_time(void);
size_t		get_t_diff(size_t start_time);
void		philo_eating(t_philo *philo);
void		philo_think(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		wait_threads(t_thread *threads, t_common *c_data);
void		*routine(void *_philo);
void		init_common_data(t_common *c_data, char *argv[]);
t_philo		*init_philo(t_philo *philos, t_common *c_data);
void		init_threads(t_thread *threads, t_philo *philos);
void		*monitor(void *_philos);
t_bool		get_someone_dead(t_philo *philo);
void		print_action(t_philo *philo, char *str, int i);
void		clean_data(t_philo *philos, t_common *data, t_thread *threads);
void		set_someone_dead(t_philo *philo);
void		print_msg(t_philo *philo, char *str);
size_t		get_last_eat(t_philo *philo);

#endif