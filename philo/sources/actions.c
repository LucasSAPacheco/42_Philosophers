/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantana <lsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:55:25 by lsantana          #+#    #+#             */
/*   Updated: 2023/03/14 12:11:00 by lsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	set_last_meal(t_philo *philo)
{
	pthread_mutex_lock(philo->c_data->control);
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->c_data->control);
}

void	print_action(t_philo *philo, char *str, int i)
{
	if (get_someone_dead(philo) == FALSE)
	{
		while (i--)
			print_msg(philo, str);
	}
}

void	philo_eating(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	set_last_meal(philo);
	pthread_mutex_lock(philo->c_data->print_control);
	print_action(philo, "has taken a fork", 2);
	print_action(philo, "is eating", 1);
	pthread_mutex_unlock(philo->c_data->print_control);
	usleep(philo->c_data->time_to_eat);
	philo->eat_count++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(philo->c_data->print_control);
	print_action(philo, "is thinking", 1);
	pthread_mutex_unlock(philo->c_data->print_control);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->c_data->print_control);
	print_action(philo, "is sleeping", 1);
	pthread_mutex_unlock(philo->c_data->print_control);
	usleep(philo->c_data->time_to_sleep);
}
