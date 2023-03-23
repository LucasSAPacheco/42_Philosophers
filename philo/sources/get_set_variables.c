/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantana <lsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:00:42 by lsantana          #+#    #+#             */
/*   Updated: 2023/03/14 15:06:39 by lsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_bool	get_someone_dead(t_philo *philo)
{
	t_bool	someone_died;

	pthread_mutex_lock(philo->c_data->anyone_died);
	someone_died = philo->c_data->someone_died;
	pthread_mutex_unlock(philo->c_data->anyone_died);
	return (someone_died);
}

void	set_someone_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->c_data->anyone_died);
	philo->c_data->someone_died = TRUE;
	pthread_mutex_unlock(philo->c_data->anyone_died);
}

size_t	get_last_eat(t_philo *philo)
{
	size_t	last_eat;

	pthread_mutex_lock(philo->c_data->control);
	last_eat = philo->last_eat;
	pthread_mutex_unlock(philo->c_data->control);
	return (last_eat);
}
