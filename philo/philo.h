#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_philo
{
   int i;
   long long start;
   int philo_num;
   int time_to_die;
   int time_to_eat;
   int time_to_sleep;
   int eat_x_times;
   int *eat_times;
   long long *last_time_ate;
   pthread_mutex_t *mutex_ate;
   pthread_t *philos;
   pthread_mutex_t print_mute;
   pthread_mutex_t *forks;
   pthread_mutex_t *times;
} s_philo;

int   all_philos_ate_x_times(s_philo *s, int num_philo, int times_to_eat);
long long timestamp();
void  philo_free(s_philo *s);
int ft_usleep(long long microseconds);
int print_mutex(s_philo *s, char *str, long long time, int philo);
void *func(s_philo *philo);
void philo_init(s_philo *s, int ac, char **av);
void  mutex_init(s_philo *s);
void thread_create(s_philo *s);
void  mutex_destroy(s_philo *s);
int  check_death(s_philo *s);
int   check_all_ate(s_philo *s, int ac, char **av);
int   check(s_philo *s, int ac, char **av);
int   parse(int ac,char **av);

#endif