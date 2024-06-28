#ifndef vetor_h
#define vetor_h

typedef struct vetor{
    int size;       //Tamanho máximo do vetor
    int pos;        //Ocupação do vetor
    void** vet;     //Vetor
} vetor;

/*
Algumas funções exigem outras funções como parâmetro:
freefunc -> Função para liberar elementos dentro do vetor. NULL caso os elementos não sejam dinâmicamente alocados ou não devam ser liberados.
print -> Função para printar corretamente um elemento do vetor.
compare -> Função para comparar 2 elementos do vetor. Retorna 0 se forem iguais, <0 se o segundo parâmetro for maior e >0 caso o primeiro parâmetro seja maior.
*/

vetor* cria_vet(int size);                                                  //Alocação do vetor
void   free_vet(vetor* vet, void (*freefunc) (void*));                      //Liberação do vetor| freefunc libera os elementos dentro do vetor| Passar NULL caso não seja necessário
void   add_vet(vetor* vet, void* data);                                     //Adiciona elemento
int    len_vet(vetor* vet);                                                 //Retorna tamanho atual do vetor
int    maxSize_vet(vetor* vet);                                             //Retorna tamanho máximo do vetor
void   cp_vet(vetor* vet1, vetor* vet2);                                    //Copiar vet1 em vet2
void*  get_vet(vetor* vet, int pos);                                        //Acessa elemento
void   del_vet(vetor* vet, int pos);                                        //Remove elemento
void   print_vet(vetor* vet, void (*print) (void*));                        //Mostra o vetor
int    bsearch_vet(vetor* vet, void* chave, int (*compare) (void*, void*)); //Busca binária| Retorna posição se encontrar, -1 caso contrário
int    ssearch_vet(vetor* vet, void* chave, int (*compare) (void*, void*)); //Busca sequencial| Retorna posição se encontrar, -1 caso contrário
void   qsort_vet(vetor* vet, int (*compare) (void*, void*));                //Quick sort
void   msort_vet(vetor* vet, int (*compare) (void*, void*));                //Merge sort
void   insort_vet(vetor* vet, int (*compare) (void*, void*));               //Insertion sort
void   selsort_vet(vetor* vet, int (*compare) (void*, void*));              //Selection sort


#endif