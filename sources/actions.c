/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantana <lsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:55:25 by lsantana          #+#    #+#             */
/*   Updated: 2023/03/12 17:56:32 by lsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void philo_eating(t_philo *philo)
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
    pthread_mutex_lock(philo->c_data->print_control);
    printf("%zu %d has taken a fork\n", get_time_diff(philo->c_data->start_time) ,philo->id);
    printf("%zu %d has taken a fork\n", get_time_diff(philo->c_data->start_time) ,philo->id);
    printf("%zu %d is eating\n", get_time_diff(philo->c_data->start_time) ,philo->id);
    pthread_mutex_unlock(philo->c_data->print_control);
    usleep(philo->c_data->time_to_eat);
    philo->eat_count++;
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void philo_think(t_philo *philo)
{
    pthread_mutex_lock(philo->c_data->print_control);
    printf("%zu %d is thinking\n", get_time_diff(philo->c_data->start_time) ,philo->id);
    pthread_mutex_unlock(philo->c_data->print_control);
}

void philo_sleep(t_philo *philo)
{
    pthread_mutex_lock(philo->c_data->print_control);
    printf("%zu %d is sleeping\n", get_time_diff(philo->c_data->start_time) ,philo->id);
    pthread_mutex_unlock(philo->c_data->print_control);
    usleep(philo->c_data->time_to_sleep);
}
