/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-bou <abel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 00:35:42 by abel-bou          #+#    #+#             */
/*   Updated: 2022/10/01 16:33:10 by abel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_is_ate(t_philo *ph)
{
	int		i;
	size_t	time;

	while (1)
	{
		i = 0;
		while (i < ph->data->num_philo)
		{
			pthread_mutex_lock(&ph->data->vars);
			time = get_time_of_day() - ph[i].time_ate;
			if ((time > ph->data->time_to_die && ph->is_ate == 0))
			{
				time = get_time_of_day() - ph[i].data->start_prog;
				pthread_mutex_lock(&ph[i].data->print);
				printf("%zu ms Philo[%d] died\n", time, ph[i].index);
				return (1);
			}
			if (ph[i].data->must_eat * ph->data->num_philo
				< ph[i].data->num_plate && ph->data->must_eat != -1)
				return (1);
			pthread_mutex_unlock(&ph->data->vars);
			i++;
		}
	}
	return (0);
}

void	routine(t_philo *ph)
{
	while (1)
	{
		pthread_mutex_lock(&ph->data->vars);
		ph->is_ate = 0;
		pthread_mutex_unlock(&ph->data->vars);
		pthread_mutex_lock(&ph->data->forks[ph->left_fork]);
		print_mutex("has taken a lfork", ph);
		pthread_mutex_lock(&ph->data->forks[ph->right_fork]);
		print_mutex("has taken a rfork", ph);
		print_mutex("is eating", ph);
		pthread_mutex_lock(&ph->data->vars);
		ph->is_ate = 1;
		ph->time_ate = get_time_of_day();
		ph->data->num_plate++;
		pthread_mutex_unlock(&ph->data->vars);
		if (!(sleeep(ph, ph->data->time_to_eat)))
		{
			print_mutex("is sleeping", ph);
			pthread_mutex_unlock(&ph->data->forks[ph->left_fork]);
			pthread_mutex_unlock(&ph->data->forks[ph->right_fork]);
		}
		if (!(sleeep(ph, ph->data->time_to_sleep)))
			print_mutex("is thinking", ph);
	}
}

void	*routine_ph(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	routine(ph);
	return (NULL);
}

int	ft_create_threads(t_philo *ph)
{
	int	i;

	ph->data->th = malloc(sizeof(pthread_t) * ph->data->num_philo);
	if (!ph->data->th)
		return (-1);
	i = 0;
	while (i < ph->data->num_philo)
	{
		ph[i].index = i + 1;
		ph[i].time_ate = get_time_of_day();
		if (pthread_create(&ph->data->th[i], NULL, routine_ph, &ph[i]))
			return (1);
		usleep(50);
		i++;
	}
	return (0);
}
