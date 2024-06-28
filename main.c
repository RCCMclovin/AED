#include "Lista/listas.h"
#include <stdio.h>


void print_int(void* i){
    printf("%d ", *((int*) i));
}

int compara(void* a, void* b){
    return *((int*) a) - *((int*) b);
}

int main(void){

    int aux[] = {1, 5, 9, 13, 15};

    lista* l = cria_lista();
    add_lista(l, &aux[1]);
    add_lista(l, &aux[0]);
    add_lista(l, &aux[2]);
    add_lista(l, &aux[3]);
    add_lista(l, &aux[4]);

    print_lista(l, print_int);
    del_lista(l, 1);
    print_lista(l, print_int);

    int pos = ssearch_lista(l, &aux[2], compara);
    printf("%d\n", pos);

    print_int(get_lista(l, pos));

    return 0;
}