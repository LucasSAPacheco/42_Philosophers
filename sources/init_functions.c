/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantana <lsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:58:29 by lsantana          #+#    #+#             */
/*   Updated: 2023/03/13 19:02:26 by lsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
    c_data->finish_eat = 0;
    c_data->someone_died = FALSE;
    c_data->start_time = get_time();
    c_data->print_control = (t_mutex *)malloc(sizeof(t_mutex));
    c_data->control = (t_mutex *)malloc(sizeof(t_mutex));
    pthread_mutex_init(c_data->print_control, NULL);
    pthread_mutex_init(c_data->control, NULL);
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
        philos[i].last_eat = c_data->start_time;
        i++;
    }
    return (philos);
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
    pthread_create(&threads[i], NULL, &monitor, philos);
}
