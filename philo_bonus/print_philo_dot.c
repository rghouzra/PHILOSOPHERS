#include "philosophers.h"

void print_philos_dot(t_philo **philos, int nb_philos) {
    int i;

    printf( "digraph philos {\n");
    printf( "    node [shape=circle, fontsize=12, fixedsize=true, width=0.5]\n");

    for (i = 0; i < nb_philos; i++) {
        printf("    philo%d [label=\"%d\"]\n", philos[i]->id, philos[i]->id);
    }

    printf("    node [shape=diamond, fontsize=12, fixedsize=true, width=0.5]\n");

    for (i = 0; i < nb_philos; i++) {
        printf("    fork%d [label=\"fork%d\"]\n", i, i);
    }

    for (i = 0; i < nb_philos; i++) {
        printf("    philo%d -> fork%d [label=\"left\"]\n", philos[i]->id, i);
        printf("    philo%d -> fork%d [label=\"right\"]\n", philos[i]->id, (i + 1) % nb_philos);
    }

    printf("}\n");
}
