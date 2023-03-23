/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantana <lsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:36:12 by lsantana          #+#    #+#             */
/*   Updated: 2023/03/14 17:26:48 by lsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*routine(void *_philo)
{
	t_philo	*philo;

	philo = (t_philo *)_philo;
	if (philo->c_data->nums_philos == 1)
	{
		pthread_mutex_lock(philo->c_data->print_control);
		print_msg(philo, "has taken a fork");
		pthread_mutex_unlock(philo->c_data->print_control);
		return (NULL);
	}
	while (get_someone_dead(philo) == FALSE)
	{
		philo_eating(philo);
		if (philo->eat_count == philo->c_data->must_eat)
		{
			pthread_mutex_lock(philo->c_data->control);
			philo->c_data->finish_eat++;
			pthread_mutex_unlock(philo->c_data->control);
			break ;
		}
		philo_sleep(philo);
		philo_think(philo);
		usleep(100);
	}
	return (NULL);
}

int	get_finish_eat(t_philo *philo)
{
	int	finish_eat;

	pthread_mutex_lock(philo->c_data->control);
	finish_eat = philo->c_data->finish_eat;
	pthread_mutex_unlock(philo->c_data->control);
	return (finish_eat);
}

void	print_msg(t_philo *philo, char *str)
{
	printf("%zu %d %s\n", get_t_diff(philo->c_data->start_time), philo->id, str);
}

void	*monitor(void *_phi)
{
	t_philo	*phi;
	int		i;

	phi = (t_philo *)_phi;
	while (TRUE)
	{
		i = 0;
		while (i < phi->c_data->nums_philos)
		{
			if (get_finish_eat(&phi[i]) == phi[i].c_data->nums_philos)
				return (NULL);
			if (get_t_diff(get_last_eat(&phi[i])) > phi[i].c_data->time_to_die)
			{
				set_someone_dead(&phi[i]);
				pthread_mutex_lock(phi->c_data->print_control);
				print_msg(phi, "died");
				pthread_mutex_unlock(phi->c_data->print_control);
				return (NULL);
			}
			i++;
		}
		usleep(150);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_common	c_data;
	t_philo		*philos;
	t_thread	*threads;

	philos = NULL;
	if (check_errors(argc, argv))
		return (1);
	init_common_data(&c_data, argv);
	threads = malloc(sizeof(t_thread) * (c_data.nums_philos + 1));
	philos = init_philo(philos, &c_data);
	init_threads(threads, philos);
	wait_threads(threads, &c_data);
	destroy_mutexes(philos, &c_data);
	clean_data(philos, &c_data, threads);
	return (0);
}
