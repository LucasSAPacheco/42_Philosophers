/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantana <lsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:41:15 by lsantana          #+#    #+#             */
/*   Updated: 2023/03/12 18:00:19 by lsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

int ft_atoi(const char *str);
int	ft_isdigit(int c);
int	ft_strlen(char *str);
int is_number(char *str);
int check_errors(int argc, char *argv[]);
void forks_destroy(t_philo *philos, t_common c_data);
size_t	get_time(void);
size_t get_time_diff(size_t start_time);
void philo_eating(t_philo *philo);
void philo_think(t_philo *philo);
void philo_sleep(t_philo *philo);
void wait_threads(t_thread *threads, t_common c_data);
void *routine(void *_philo);
void init_common_data(t_common *c_data, char *argv[]);
t_philo *init_philo(t_philo *philos, t_common *c_data);
void init_threads(t_thread *threads, t_philo *philos);

#endif