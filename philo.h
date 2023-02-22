/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-bou <abel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 00:47:50 by abel-bou          #+#    #+#             */
/*   Updated: 2022/10/01 16:32:41 by abel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	pthread_t		*th;
	int				num_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				must_eat;
	size_t			start_prog;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	vars;
	int				*exist_fork;
	int				num_plate;

}t_data;

typedef struct s_philo
{
	t_data	*data;
	int		left_fork;
	int		right_fork;
	int		index;
	size_t	time_ate;
	int		is_ate;
}t_philo;

int		ft_init_philo(t_philo *ph, t_data *data);
t_philo	*ft_init_data(t_philo *ph, t_data *data);
int		check_args(char **av);
int		ft_isdigit(char c);
int		ft_create_threads(t_philo *ph);
int		ft_check_is_ate(t_philo *ph);
size_t	get_time_of_day(void);
void	print_mutex(char *str, t_philo *ph);
int		sleeep(t_philo *ph, size_t i);
int		ft_atoi(char *str);

#endif