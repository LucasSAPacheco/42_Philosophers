/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantana <lsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:36:12 by lsantana          #+#    #+#             */
/*   Updated: 2023/03/12 17:59:14 by lsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"





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
