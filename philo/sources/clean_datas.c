/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_datas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantana <lsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:50:44 by lsantana          #+#    #+#             */
/*   Updated: 2023/03/13 23:23:51 by lsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void destroy_mutexes(t_philo *philos, t_common *c_data)
{
    int i;

    i = 0;
    while (i < c_data->nums_philos)
    {
        pthread_mutex_destroy(philos[i].right_fork);
        i++;
    }
    pthread_mutex_destroy(c_data->control);
    pthread_mutex_destroy(c_data->print_control);
    pthread_mutex_destroy(c_data->anyone_died);
}

void wait_threads(t_thread *threads, t_common *c_data)
{
    int i;

    i = 0;
    while (i < c_data->nums_philos)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
    pthread_join(threads[i], NULL);
}