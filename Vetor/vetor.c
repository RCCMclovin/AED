#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"

void print_int(void* i){
    printf("%d ", *((int*) i));
}

int compara(void* a, void* b){
    return *((int*) a) - *((int*) b);
}

vetor* cria_vet(int size){
    vetor* vet = (vetor*) malloc(3*sizeof(int)+size*sizeof(void*));
    vet->size = size;
    vet->pos = 0;
    vet->vet = malloc(size*sizeof(void*));
    return vet;
}

void free_vet(vetor* vet, void (*freefunc) (void*)){
    if(freefunc != NULL) for(int i = 0; i < vet->pos; i++) freefunc(vet->vet[i]);
    free(vet->vet);
    free(vet);
}

void add_vet(vetor* vet, void* data){
    if(vet->pos >= vet->size){
        printf("Erro: Vetor Cheio!!\n");
        return;
    }
    vet->vet[vet->pos++]= data;
    //vet->pos++;
}

void* get_vet(vetor* vet, int pos){
    if(pos >= 0 && pos < vet->pos) return vet->vet[pos];
    else return NULL;
}

void del_vet(vetor* vet, int pos){
    if(vet->pos == 0) return;
    if(pos < --vet->pos) for(int i = pos; i < vet->pos; i++) vet->vet[i] = vet->vet[i+1];
    
}

void cp_vet(vetor* vet1, vetor* vet2){
    if(vet2->size < vet1->pos){
        printf("ERRO: Vetor origem grande demais para copiar no vetor alvo.\n");
        return;
    }
    vet2->pos = vet1->pos;
    for(int i = 0; i < vet2->pos; i++){
        vet2->vet[i] = vet1->vet[i];
    }

}

void print_vet(vetor* vet, void (*print) (void*)){
    for(int i = 0; i < vet->pos; i++) print(vet->vet[i]);
    printf("\n");
}

int bsearch_vet(vetor* vet, void* chave, int (*compare) (void*, void*)){
    if(vet->pos == 0) return -1;
    int s = 0, f = vet->pos-1, m;
    while(s <= f){
        m = (s+f)/2;
        //printf("- %d\n", m);
        if(compare(vet->vet[m], chave) == 0) return m;
        if(compare(vet->vet[m], chave) > 0) f = m-1;
        if(compare(vet->vet[m], chave) < 0) s = m+1;
    }
    return -1;
}

int ssearch_vet(vetor* vet, void* chave, int (*compare) (void*, void*)){
    if(vet->pos == 0) return -1;
    for(int i = 0; i < vet->pos; i++) if(compare(vet->vet[i], chave) == 0) return i;
    return -1;
}

void qsort_rec(vetor* vet, int s, int f, int (*compare) (void*, void*)){
    if(s < f){
        int pivot = (s+f)/2, j = f;
        int troca = 0;
        void* aux;
        for(int i = 0; i < pivot; i++){
            if(i>=s && compare(vet->vet[i], vet->vet[pivot]) > 0){
                troca = 0;
                for(j; j > pivot; j--){
                    if(compare(vet->vet[j], vet->vet[pivot]) <= 0){
                        troca = 1;
                        aux = vet->vet[i];
                        vet->vet[i] = vet->vet[j];
                        vet->vet[j] = aux;
                        j--;
                        break;
                    }
                }
                if(!troca){
                    aux = vet->vet[i];
                    vet->vet[i] = vet->vet[pivot -1];
                    vet->vet[pivot -1] = vet->vet[pivot];
                    vet->vet[pivot] = aux;
                    pivot--;
                    i--;
                }
            }
        }
        for(j; j > pivot; j--){
            if(j <= f && compare(vet->vet[j], vet->vet[pivot]) <= 0){
                aux = vet->vet[j];
                vet->vet[j] = vet->vet[pivot +1];
                vet->vet[pivot +1] = vet->vet[pivot];
                vet->vet[pivot] = aux;
                pivot++;
                j++;
            }
        }
        qsort_rec(vet, s, pivot-1, compare);
        qsort_rec(vet, pivot+1, f, compare);
    }
}

void qsort_vet(vetor* vet, int (*compare) (void*, void*)){
    if(vet->pos == 0) return;
    qsort_rec(vet, 0, vet->pos-1, compare);
}

void msort_rec(vetor* vet, void** aux, int s, int f,int (*compare) (void*, void*)){
    if(s<f){
        int m = (s+f)/2;
        int j = m+1, ap = s, i = s;

        msort_rec(vet, aux, s, m, compare);
        msort_rec(vet, aux, m+1, f, compare);

        while(i <= m && j <= f){
            if(compare(vet->vet[i], vet->vet[j]) < 0){
                aux[ap] = vet->vet[i];
                ap++;
                i++;
            }else{
                aux[ap] = vet->vet[j];
                ap++;
                j++;
            }
        }
        while(i<=m){
            aux[ap] = vet->vet[i];
            ap++;
            i++;
        }
        while(j<=f){
            aux[ap] = vet->vet[j];
            ap++;
            j++;
        }
        for(i = s; i <= f; i++) vet->vet[i] = aux[i];
    }
}

void msort_vet(vetor* vet, int (*compare) (void*, void*)){
    if(vet->pos == 0) return;
    void** aux = malloc(vet->pos*sizeof(void*));
    msort_rec(vet, aux, 0, vet->pos - 1, compare);
    free(aux);
}

void insort_vet(vetor* vet, int (*compare) (void*, void*)){
    if(vet->pos == 0) return;
    void* aux;
    int pivot;
    for(int i = 1; i < vet->pos; i++){
        pivot = i;
        aux = vet->vet[i];
        int j = i-1, troca = 0;
        for(j; j >= 0; j--){
            if(compare(aux, vet->vet[j]) < 0){
                troca = 1;
                vet->vet[j+1] = vet->vet[j];
                pivot = j;
            }
        }
        if(troca) vet->vet[pivot] = aux;

    }
}

void selsort_vet(vetor* vet, int (*compare) (void*, void*)){
    if(vet->pos == 0) return;
    int min;
    void* aux;
    for(int i = 0; i < vet->pos-1; i++){
        aux = vet->vet[i];
        min = i;
        for(int j = i+1; j < vet->pos; j++){
            if(compare(vet->vet[min], vet->vet[j])>0) min = j;
        }
        vet->vet[i] = vet->vet[min];
        vet->vet[min] = aux;
    }

}

/*
int main(void){
    vetor* vet = cria_vet(5);
    int v[] = {1,2, 2, 4, 5, 0};
    add_vet(vet, &v[4]);
    add_vet(vet,&v[5]);
    add_vet(vet, &v[2]);
    add_vet(vet,&v[3]);
    add_vet(vet, &v[1]);
    print_vet(vet, print_int);
    selsort_vet(vet, compara);
    print_vet(vet, print_int);
    free_vet(vet, NULL);

    return 0;
}
//*/
