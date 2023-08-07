#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_philo
{
   int i;
   long long *start;
   int philo_num;
   int time_to_die;
   int time_to_eat;
   int time_to_sleep;
   int eat_x_times;
   int *eat_times;
   long long *last_time_ate;
   pthread_mutex_t *mutex_ate;
   pthread_t *philos;
   pthread_mutex_t *forks;
   pthread_mutex_t *times;
} s_philo;

int   all_philos_ate_x_times(int *eat_times, int num_philo, int times_to_eat)
{
   int i;
   int index;

   i = 0;
   index = 0;
   while (i < num_philo)
   {
      if (eat_times[i] >= times_to_eat)
         index++;
      i++;
   }
   if(index == num_philo)
      return(1);
   return(0);
}

long long timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL);
    long long milliseconds = te.tv_sec*1000 + te.tv_usec/1000;
    return milliseconds;
}

int ft_usleep(long long microseconds)
{
   long long i;
   long long j;
   long long k;
   long long l;
   
   i = 0;
   k = timestamp();
   l = k;
   while(timestamp() <= l + microseconds)
   {
      usleep(100);
   }
}

void *func(s_philo *philo)
{
   // long long   start;
   int n = philo->i;
   // start = timestamp();
   while (1)
   {
      //when philosopher 5 is eating he takes fork 1 and fork 5
      // gettimeofday(&end, NULL);
      // printf ("%d      Philosopher %d is thinking\n", end - start, n);
      
      pthread_mutex_lock(&philo->forks[n]);
      pthread_mutex_lock(&philo->forks[(n+1)%(philo->philo_num)]);
      printf ("%lld      Philosopher %d took the first chopstick\n",  timestamp() - philo->start[n], n);
      printf ("%lld      Philosopher %d took the second chopstick\n", timestamp() - philo->start[n], n);
      pthread_mutex_lock(&philo->times[n]);
      philo->eat_times[n]++;
      pthread_mutex_unlock(&philo->times[n]);
      pthread_mutex_lock(&philo->mutex_ate[n]);
      philo->last_time_ate[n] = timestamp();
      printf ("%lld      Philosopher %d is eating\n", philo->last_time_ate[n] - philo->start[n], n);
      pthread_mutex_unlock(&philo->mutex_ate[n]);

      ft_usleep(philo->time_to_eat);

      pthread_mutex_unlock(&philo->forks[n]);
      pthread_mutex_unlock(&philo->forks[(n+1)%(philo->philo_num)]);
      // end = timestamp();
      printf ("%lld      Philosopher %d sleeping\n", timestamp() - philo->start[n], n);

      ft_usleep(philo->time_to_sleep);
   }
   return(NULL);
}

// void philo_init(s_philo *s, int ac, char **av)
{
      s->philo_num = atoi(av[1]);
      s->time_to_eat = atoi(av[3]);
      s->time_to_sleep = atoi(av[4]);
      s->time_to_die = atoi(av[2]);
      if(ac == 6)
            s->eat_x_times = atoi(av[5]);
      s->start = malloc(sizeof(long long) * s->philo_num);
      s->philos = (pthread_t *)malloc(sizeof(pthread_t) * s->philo_num);
      s->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * s->philo_num);
      s->mutex_ate = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t ) * s->philo_num);
      s->times = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t ) * s->philo_num); 
      s->last_time_ate = malloc(sizeof(long long) * s->philo_num);
      s->eat_times = malloc(sizeof(long long) * s->philo_num);
      s->i = 0;
      long long fofo = timestamp();
      while(s->i < s->philo_num)
      {
         s->start[s->i]= fofo;
         s->last_time_ate[s->i] = fofo;
         s->eat_times[s->i] = 0;
         s->i++;
      }
}

void  mutex_init(s_philo *s)
{
   while(s->i < s->philo_num)
   {
      pthread_mutex_init(&s->forks[s->i],NULL);
      pthread_mutex_init(&s->mutex_ate[s->i],NULL);
      pthread_mutex_init(&s->times[s->i],NULL);
      s->i++;
   }
}

void thread_create(s_philo *s)
{
   s->i = 0;
   while(s->i < s->philo_num)
   {
      pthread_create(&s->philos[s->i],NULL,(void *)func,s);
      pthread_detach(s->philos[s->i]); 
      usleep(100);
      s->i++;
   }
}

void  mutex_destroy(s_philo *s)
{
   s->i = 0;
   while(s->i < s->philo_num)
   {
      pthread_mutex_destroy(&s->forks[s->i]);
      pthread_mutex_destroy(&s->mutex_ate[s->i]);
      pthread_mutex_destroy(&s->times[s->i]);
      s->i++;
   }
}

int parse(int ac,char **av)
{
   int i;
   int j;

   i = 0;
   j = 0;
   while(i < ac)
   {
      while(av[i][j])
      {
         if(!(av[i][j] >= 48 && av[i][j] <= 57))
            return(0);
         j++;
      }
      j = 0
   }
   return(1);
}

int main(int ac, char **av)
   {
      
      s_philo s;
      if(ac == 5 || ac == 6)
      {
         if(parse(ac, av) == 0)
            exit(0);
         philo_init(&s, ac, av);
         // s.philo_num = atoi(av[1]);
         // s.time_to_eat = atoi(av[2]);
         // s.time_to_sleep = atoi(av[3]);
         // s.time_to_die = atoi(av[4]);
         // if(ac == 6)
         //    s.eat_x_times = atoi(av[5]);
         // s.start = malloc(sizeof(long long) * s.philo_num);
         // s.philos = (pthread_t *)malloc(sizeof(pthread_t) * s.philo_num);
         // s.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * s.philo_num);
         // s.mutex_ate = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t ) * s.philo_num);
         // s.times = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t ) * s.philo_num); 
         // s.last_time_ate = malloc(sizeof(long long) * s.philo_num);
         // s.eat_times = malloc(sizeof(long long) * s.philo_num); 
         // memset(s.last_time_ate, 0, sizeof(long long) * s.philo_num);
         // long long fofo = timestamp();
         // for(s.i=0;s.i<s.philo_num;s.i++)
         // {
         //    s.start[s.i]= fofo;
         //    s.last_time_ate[s.i] = fofo;
         //    s.eat_times[s.i] = 0;
         // }
         // for(s.i=0;s.i<s.philo_num;s.i++)
         // {
         //    pthread_mutex_init(&s.forks[s.i],NULL);
         //    pthread_mutex_init(&s.mutex_ate[s.i],NULL);
         //    pthread_mutex_init(&s.times[s.i],NULL);
         // }
         mutex_init(&s);
         thread_create(&s);
         // for(s.i=0;s.i<s.philo_num;s.i++)
         // {
         //    pthread_create(&s.philos[s.i],NULL,(void *)func,&s);
         //    pthread_detach(s.philos[s.i]); 
         //    usleep(100);
         // }
            // while (1)
            // {
            //    int i = 0;
            //    while(i < s.i)
            //    {
            //       pthread_mutex_lock(&s.mutex_ate[i]);
            //       if( timestamp() - s.last_time_ate[i] >= s.time_to_die )
            //          {
            //             printf("philo %i died\n", i);
            //             exit(0);
            //          }
            //       pthread_mutex_unlock(&s.mutex_ate[i]);
            //       i++;
            //    }
            //    pthread_mutex_lock(&s.times[i]);
            //    if (ac == 6 && (all_philos_ate_x_times(s.eat_times, atoi(av[1]), atoi(av[5]))) == 1)
            //       exit(0);
            //    pthread_mutex_unlock(&s.times[i]);
            // }
            mutex_destroy(&s);
         // for(s.i=0;s.i<s.philo_num;s.i++)
         // {
         //    pthread_mutex_destroy(&s.forks[s.i]);
         //    pthread_mutex_destroy(&s.mutex_ate[s.i]);
         //    pthread_mutex_destroy(&s.times[s.i]);
         // }
         return 0;
      }
   }