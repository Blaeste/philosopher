/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:47:38 by eschwart          #+#    #+#             */
/*   Updated: 2025/05/21 13:26:22 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

// =============================
// 📚 Libraries
// =============================
# include <stdbool.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <unistd.h>
# include <sys/time.h>

// =============================
// 🎨 Defines (Colors)
// =============================
# define RESET "\033[0m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define CYAN "\033[1;36m"
# define BLUE "\033[1;34m"

typedef enum e_state
{
	FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}	t_state;

// =============================
// 🧱 Structures
// =============================
typedef struct s_data	t_data;
typedef struct s_philo	t_philo;
typedef struct s_args	t_args;

// 🔹 Philosopher
struct s_philo
{
	int				id;
	pthread_mutex_t	meals_m;
	int				meals_eaten;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread_id;
	t_data			*data;
};

// 🔹 args
struct s_args
{
	int			nbr_p;
	int			t_to_die;
	int			t_to_eat;
	int			t_to_sleep;
	int			nbr_meal;
	uint64_t	start_time;
};

// 🔹 Data
struct s_data
{
	t_args			args;
	pthread_mutex_t	dead_m;
	int				dead;
	pthread_mutex_t	print_m;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_t		monitor_id;
};

// =============================
// 📋 PROTOTYPES
// =============================

// 🔹 init.c
int			ft_error_msg(const char *msg);
int			ft_parse_args(int ac, char **av, t_data *data);
int			ft_init_data(t_data *data);

// 🔹 launch_threads.c
int			ft_launch_threads(t_data *data);

// 🔹 life.c
void		*ft_life_cycle(void *arg);

// 🔹 print.c
void		ft_print_state(t_philo *philo, const char *msg, t_state state);

// 🔹 time_utils.c
uint64_t	ft_get_timestamp_now(void);
uint64_t	ft_get_timestamp(t_data *data);
void		ft_smart_sleep(long ms, t_data *data);

// 🔹 monitor.c
void		*ft_monitor(void *arg);

// 🔹 utils.c
int			ft_is_dead(t_data *data);
int			ft_clean_exit(t_data *data, int status);
int			ft_onephilo(t_philo *philo);

// 🔹 utils_libft.c
int			ft_atoi(const char *nptr);
size_t		ft_strlen(const char *str);
int			ft_is_number(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

#endif // PHILOSOPHER_H