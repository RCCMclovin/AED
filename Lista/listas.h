#ifndef listas_h
#define listas_h

typedef struct no{
    struct no* prox;
    struct no* ant;
    void* data;
} no_lista;

typedef struct lista{
    no_lista* prim;
    no_lista* last;
} lista;

lista*  cria_lista(void);
void    add_lista(lista* l, void* data);
int     ssearch_lista(lista* l, void* chave, int (*compare) (void*, void*));
void    del_lista(lista* l, int pos);
void    free_lista(lista* l, void (*freefunc) (void*));
void*   get_lista(lista* l, int pos);
void    print_lista(lista* l, void (*print) (void*));




#endif