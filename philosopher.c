/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-bou <abel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:54:54 by abel-bou          #+#    #+#             */
/*   Updated: 2022/10/01 20:12:32 by abel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time_of_day(void)
{
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	return (tm.tv_sec * 1000 + tm.tv_usec / 1000);
}

int	sleeep(t_philo *ph, size_t i)
{
	size_t	time;

	time = get_time_of_day();
	while (get_time_of_day() - time < i)
	{
		if (get_time_of_day() - ph->time_ate > ph->data->time_to_die)
			return (1);
		usleep(50);
	}
	return (0);
}

void	print_mutex(char *str, t_philo *ph)
{
	pthread_mutex_lock(&ph->data->print);
	printf("%zu ms Philo[%d] %s\n", get_time_of_day() - ph->data->start_prog, \
	ph->index, str);
	pthread_mutex_unlock(&ph->data->print);
}

t_data	*init_args(int ac, char **av, t_data *data)
{
	data->num_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = -1;
	if (data->num_philo == 0
		|| data->time_to_die == 0 || data->time_to_eat == 0
		|| data->time_to_sleep == 0
		|| (ac == 6 && data->must_eat == 0))
		return (NULL);
	return (data);
}

int	main(int ac, char **av)
{
	t_philo	*ph;
	t_data	*data;
	int		size;

	size = 0;
	if (ac == 5 || ac == 6)
	{
		if (check_args(av))
			return (1);
		size = ft_atoi(av[1]);
		ph = malloc(sizeof(t_philo) * size);
		data = malloc(sizeof(t_data));
		data = init_args(ac, av, data);
		if (!data || !ph || pthread_mutex_init(&data->print, NULL))
			return (1);
		if (ft_init_philo(ph, data))
			return (1);
		ph = ft_init_data(ph, data);
		data->start_prog = get_time_of_day();
		ft_create_threads(ph);
		if (ft_check_is_ate(ph))
			return (1);
	}
	return (1);
}
