/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkerr_init_struc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-bou <abel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 00:34:51 by abel-bou          #+#    #+#             */
/*   Updated: 2022/09/30 15:43:07 by abel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char c)
{
	if (c >= 48 && c <= 57)
		return (0);
	return (-1);
}

int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

t_philo	*ft_init_data(t_philo *ph, t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->forks)
		return (NULL);
	data->exist_fork = malloc(sizeof(int) * data->num_philo);
	if (!data->exist_fork)
		return (NULL);
	i = 0;
	while (i < data->num_philo)
	{
		ph[i].data = data;
		ph[i].data->num_plate = 0;
		data->exist_fork[i] = 0;
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (NULL);
		i++;
	}
	return (ph);
}

int	ft_init_philo(t_philo *ph, t_data *data)
{
	int	index;

	index = 0;
	while (index < data->num_philo)
	{
		ph[index].time_ate = 0;
		ph[index].left_fork = index;
		ph[index].right_fork = (index + 1) % data->num_philo;
		index++;
	}
	if (pthread_mutex_init(&data->vars, NULL))
		return (1);
	return (0);
}
