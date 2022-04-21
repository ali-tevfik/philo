#include "philo.h"

t_data *fill_data(char **argv)
{
    t_data *data;
    
    data = malloc(1024);
    data->die = ft_atoi(argv[1]);
    data->eat = ft_atoi(argv[1]);
    data->sleep = ft_atoi(argv[1]);
    return (data);
}
int main(int argc, char *argv[])
{
    t_data *data;
    printf("Data %d\n",argc);
    if (argc != 2)
        exit(1);
    data = fill_data(argv);
    printf("%d",data->sleep);
}
