#include <stdio.h>
#include <stdlib.h>
#include "listas.h"


lista*  cria_lista(void){
    lista* l = malloc(sizeof(lista));
    l->last = NULL;
    l->prim = NULL;
    return l;
}

no_lista* cria_no(void* data){
    no_lista* no = malloc(sizeof(no_lista));
    no->ant = NULL;
    no->prox = NULL;
    no->data = data;
    return no;
}

void    add_lista(lista* l, void* data){
    no_lista* no = cria_no(data);
    if(l->prim == NULL){
        l->prim = no;
        l->last = no;
    }else{
        no->prox = l->prim;
        l->prim->ant = no;
        l->prim = no;
    }
}

void    del_lista(lista* l, int pos){
    if(!l->prim) return;
    no_lista* aux = l->prim;
    while(pos >0 && aux->prox){
        pos--;
        aux = aux->prox;
    }
    if(aux->ant && aux->prox) {
        aux->ant->prox = aux->prox;
        aux->prox->ant = aux->ant;
    }
    if(aux == l->last && aux != l->prim) {
        l->last = aux->ant;
        aux->ant->prox = NULL;
    }
    if(aux == l->prim && aux != l->last) {
        l->prim = aux->prox;
        aux->prox->ant = NULL;
    }
    if(aux == l->last && aux == l->prim){
        l->last = NULL;
        l->prim = NULL; 
    } 
    free(aux);
}

void*   get_lista(lista* l, int pos){
    if(!l->prim) return NULL;
    if(pos < 0) return NULL;
    no_lista* aux = l->prim;
    while(pos >0 && aux->prox){
        pos--;
        aux = aux->prox;
    }
    if(pos > 0) return NULL;
    return aux->data;
}

void    print_lista(lista* l, void (*print) (void*)){
    no_lista* no = l->prim;
    while (no){
        print(no->data);
        no = no->prox;
    }
    printf("\n");
    
}

void    free_lista(lista* l, void (*freefunc) (void*)){
    if(!l->prim){
        free(l);
        return;
    } 
    no_lista* no = l->prim;
    while (no){
        if(freefunc) freefunc(no->data);
        no_lista* aux = no;
        no = no->prox;
        free(aux);
    }

}

int     ssearch_lista(lista* l, void* chave, int (*compare) (void*, void*)){
    if(!l->prim) return -1;
    no_lista* no = l->prim;
    int pos = 0;
    while (no){
        if(compare(no->data, chave) == 0) return pos;
        no = no->prox;
        pos++;
    }
    return -1;
    
}