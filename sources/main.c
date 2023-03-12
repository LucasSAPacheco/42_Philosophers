/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantana <lsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:36:12 by lsantana          #+#    #+#             */
/*   Updated: 2023/03/12 13:34:58 by lsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

size_t	get_time(void)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void init_common_data(t_common *c_data, char *argv[])
{
    c_data->nums_philos = ft_atoi(argv[1]);
    c_data->time_to_die = (ft_atoi(argv[2]) * 1000);
    c_data->time_to_eat = (ft_atoi(argv[3]) * 1000);
    c_data->time_to_sleep = (ft_atoi(argv[4]) * 1000);
    if (argv[5])
        c_data->must_eat = ft_atoi(argv[5]);
    else
        c_data->must_eat = -1;
    c_data->start_time = get_time();
    c_data->print_control = (t_mutex *)malloc(sizeof(t_mutex));
    pthread_mutex_init(c_data->print_control, NULL);
}

t_philo *init_philo(t_philo *philos, t_common *c_data)
{
    t_mutex *forks;
    int i;

    i = 0;
    philos = (t_philo *)malloc(sizeof(t_philo) * c_data->nums_philos);
    forks = (t_mutex *)malloc(sizeof(t_mutex) * c_data->nums_philos);
    while (i < c_data->nums_philos)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
    i = 0;
    while (i < c_data->nums_philos)
    {
        philos[i].id = i + 1;
        philos[i].eat_count = 0;
        philos[i].c_data = c_data;
        philos[i].right_fork = &forks[i];
        philos[i].left_fork = &forks[(i + 1) % c_data->nums_philos];
        i++;
    }
    return (philos);
}

void forks_destroy(t_philo *philos, t_common c_data)
{
    int i;

    i = 0;
    while (i < c_data.nums_philos)
    {
        pthread_mutex_destroy(philos[i].right_fork);
        i++;
    }
}

size_t get_time_diff(size_t start_time)
{
    return (get_time() - start_time);
}

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

void *routine(void *_philo)
{
    t_philo *philo;

    philo = (t_philo*)_philo;
    while (TRUE)
    {
        philo_eating(philo);
        if (philo->eat_count == philo->c_data->must_eat)
            break;
        philo_sleep(philo);
        philo_think(philo);
    }
    return (NULL);
}

void init_threads(t_thread *threads, t_philo *philos)
{
    int i;

    i = 0;
    while (i < philos->c_data->nums_philos)
    {
        pthread_create(&threads[i], NULL, &routine, &philos[i]);
        i++;
    }
}

void wait_threads(t_thread *threads, t_common c_data)
{
    int i;

    i = 0;
    while (i < c_data.nums_philos)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
}

int main(int argc, char *argv[])
{
    t_common c_data;
    t_philo *philos;
    t_thread *threads;
    
    philos = NULL;
    if (check_errors(argc, argv))
        return (1);
    init_common_data(&c_data, argv);
    threads = (t_thread *)malloc(sizeof(t_thread) * c_data.nums_philos);
    philos = init_philo(philos, &c_data);
    init_threads(threads, philos);
    wait_threads(threads, c_data);
    forks_destroy(philos, c_data);
    return (0);
}
