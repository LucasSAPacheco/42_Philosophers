/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_datas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantana <lsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:50:44 by lsantana          #+#    #+#             */
/*   Updated: 2023/03/12 17:56:27 by lsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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