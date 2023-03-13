/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantana <lsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:36:12 by lsantana          #+#    #+#             */
/*   Updated: 2023/03/13 19:12:30 by lsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void *routine(void *_philo)
{
    t_philo *philo;

    philo = (t_philo*)_philo;
    while (philo->c_data->someone_died == FALSE)
    {
        philo_eating(philo);
        if (philo->eat_count == philo->c_data->must_eat)
        {
            pthread_mutex_lock(philo->c_data->control);
            philo->c_data->finish_eat++;
            pthread_mutex_unlock(philo->c_data->control);
            break;
        }
        philo_sleep(philo);
        philo_think(philo);
    }
    return (NULL);
}

int get_finish_eat(t_philo *philo)
{
    int finish_eat;
    
    pthread_mutex_lock(philo->c_data->control);
    finish_eat = philo->c_data->finish_eat;
    pthread_mutex_unlock(philo->c_data->control);
    return (finish_eat);
}

size_t get_time_last_eat(t_philo *philo)
{
    size_t time_to_last_eat;
    
    pthread_mutex_lock(philo->c_data->control);
    time_to_last_eat = philo->last_eat;
    pthread_mutex_unlock(philo->c_data->control);
    return (time_to_last_eat);
}

void *monitor(void *_philos)
{
    t_philo *philos;
    int i;

    philos = (t_philo *)_philos;
    while (TRUE)
    {
        i = 0;
        while (i < philos->c_data->nums_philos)
        {
            if (get_finish_eat(&philos[i]) == philos[i].c_data->nums_philos)
                return (NULL);
            if (get_time_last_eat(&philos[i]) > philos[i].c_data->time_to_die)
            {
                philos[i].c_data->someone_died = TRUE;
                pthread_mutex_lock(philos->c_data->print_control);
                printf("%zu %d died\n", get_time_diff(philos->c_data->start_time), philos[i].id);
                pthread_mutex_unlock(philos->c_data->print_control);
                return (NULL);
            }
            i++;
        }
    }
    return (NULL);
}

// time to die - tempo que o filosofo pode ficar sem comer

int main(int argc, char *argv[])
{
    t_common c_data;
    t_philo *philos;
    t_thread *threads;
    
    philos = NULL;
    if (check_errors(argc, argv))
        return (1);
    init_common_data(&c_data, argv);
    threads = (t_thread *)malloc(sizeof(t_thread) * (c_data.nums_philos + 1));
    philos = init_philo(philos, &c_data);
    init_threads(threads, philos);
    wait_threads(threads, c_data);
    destroy_mutexes(philos, c_data);
    return (0);
}
