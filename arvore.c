#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct no{
    int chave;
    int bal;
    struct no *esq;
    struct no *dir;
}No;


void caso_inserir1(No **pt, int *h);
void caso_inserir2(No **pt, int *h);
void inserir(int x, No **pt_raiz, int *h, int *quantidade);

void caso_remover1(No** pt, int *h);
void caso_remover2(No** pt, int *h);
void trocar(No** pt, No** s);
void remover(int x, No **pt, int *h, int *quantidade);

void balancear(No** pt, char r , int *h);

int qtd_nos(No* pt);
void checa_avl(No* pt, int *avl);
int altura(No* pt);

void caso_inserir1(No **pt, int *h){

    No* ptu = (*pt)->esq;
    if(ptu->bal == -1){ 

        (*pt)->esq = ptu->dir;
        ptu->dir = (*pt);
        (*pt) = ptu;
        (*pt)->dir->bal = 0;

    }
    else{

        No* ptv = ptu->dir;
        ptu->dir = ptv->esq;
        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = (*pt);

        if (ptv->bal == 1){

            (*pt)->bal = 0;
            ptu->bal = -1;
        }
        else if(ptv->bal == 0){

            (*pt)->bal = 0;
            ptu->bal = 0;   
        }
        else{

            (*pt)->bal = 1;
            ptu->bal = 0;
        }
        (*pt) = ptv;
    }
    (*pt)->bal = 0;
    *h = 0;
}

void caso_inserir2(No **pt, int *h){   
    No* ptu = (*pt)->dir;

    if(ptu->bal == 1){
        (*pt)->dir = ptu->esq;
        ptu->esq = (*pt);
        (*pt) = ptu;
        (*pt)->esq->bal = 0;
    }

    else{
        No* ptv = ptu->esq;
        ptu->esq = ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = (*pt);

        switch (ptv->bal) {
            case 1:
                (*pt)->bal = -1;
                ptu->bal = 0;
                break;
            case 0:
                (*pt)->bal = 0;
                ptu->bal = 0;
                break; 
            case -1:  
                (*pt)->bal = 0;
                ptu->bal = 1;
                break;
        }

        (*pt) = ptv;
    }

    (*pt)->bal = 0;
    *h = 0;
}

void inserir(int x, No **pt_raiz, int *h, int *quantidade){
    No **pt = pt_raiz;

    if((*pt) == NULL){

        No *novo = (No*)malloc(sizeof(No));

        novo->chave = x;
        novo->bal = 0;
        novo->dir = NULL;
        novo->esq = NULL;

        *h = 1;
        (*pt) = novo;
        (*quantidade)++;

    }
    else{

        if (x != (*pt) -> chave){
            if (x < (*pt) -> chave){

                inserir(x, &(*pt)->esq, h, quantidade);

                if(*h){
                    if ((*pt)->bal == 1){ 
                        (*pt)->bal = 0;
                        *h = 0;
                    }

                    else{
                        if((*pt)->bal == 0){
                            (*pt)->bal = -1;
                        }

                        else{
                            if((*pt)->bal == -1){
                                caso_inserir1(pt, h);
                            }
                        }
                    }
                }
            }
            else{
                inserir(x, &(*pt)->dir, h, quantidade);

                if(*h){
                    if ((*pt)->bal == -1){
                        (*pt)->bal = 0;
                        *h = 0;
                    }
                    else{
                        if((*pt)->bal == 0){
                            (*pt)->bal = 1;
                        }
                        else{
                            if((*pt)->bal == 1){
                                caso_inserir2(pt, h);
                            }
                        }
                    }
                }
            }
        }
        else{
            *h = 0;
        }
    }
}


void caso_remover1(No** pt, int *h){
    No* ptu = (*pt)->esq;
    if(ptu->bal <= 0){

        (*pt)->esq = ptu->dir;
        ptu->dir = (*pt);
        *pt = ptu;

        if(ptu->bal == -1){

            ptu->bal = 0;
            (*pt) -> dir ->bal = 0; 
            *h = 1;
        }
        else{
            ptu->bal = 1;
            (*pt) -> dir ->bal = -1;
            *h = 0;
        }

    }
    else{
        No* ptv = ptu->dir;
        ptu->dir = ptv->esq;
        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = *pt;
        (*pt) = ptv;

        if(ptv->bal == -1){
            ptu->bal = 0;
            (*pt)->dir->bal = 1;
        }
        else{
            if(ptv->bal == 0){
                ptu->bal = 0;
                (*pt)->dir->bal = 0;
            }
            else{
                if(ptv->bal == 1){

                    ptu->bal = -1;
                    (*pt)->dir->bal = 0;
                }
            }
        }
        (*pt)->bal = 0;
        *h = 1;
    }
}

void caso_remover2(No** pt, int *h){

    No* ptu = (*pt)->dir;
    if(ptu->bal >= 0){
        (*pt)->dir = ptu->esq;
        ptu->esq = (*pt);
        *pt = ptu;

        if((*pt)->bal == 1){
            ptu->bal = 0;
            (*pt)->esq->bal = 0; 
            *h = 1;
        }
        else{
            ptu->bal = -1;
            (*pt)->esq->bal = 1;
            *h = 0;
        }
    }
    else{

        No* ptv = ptu->esq;
        ptu->esq= ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq= *pt;
        (*pt) = ptv;

        if(ptv->bal == 1){

            ptu->bal = 0;
            (*pt)->esq->bal = -1;
        }
        else{

            if(ptv->bal == 0){

                ptu->bal = 0;
                (*pt)->esq->bal = 0;
            }
            else{

                if(ptv->bal == -1){

                    ptu->bal = 1;
                    (*pt)->esq->bal = 0;
                }
            }
        }

        (*pt)->bal = 0;
        *h = 1;
    }
}

void trocar(No** pt, No** s){
    No* aux;
    int x;

    aux = *s;
    *s = *pt;
    *pt = aux;

    aux = (*s)->esq;
    (*s)->esq = (*pt)->esq;
    (*pt)->esq = aux;

    aux = (*s)->dir;
    (*s)->dir = (*pt)->dir;
    (*pt)->dir = aux;

    x = (*s)->bal;
    (*s)->bal = (*pt)->bal;
    (*pt)->bal = x;

}


void balancear(No** pt, char r , int *h){
    if(*h){

        if (r == 'D'){
            if ((*pt)-> bal == 1) (*pt)-> bal = 0;
            
            else{

                if ((*pt)-> bal == 0){
                    (*pt)-> bal = -1;
                    *h = 0;
                }  
                else caso_remover1(pt, h);
                
            }

        }else{

            if ((*pt)-> bal == -1) (*pt)-> bal = 0;

            else{

                if ((*pt)-> bal == 0){
                    (*pt)-> bal = 1;
                    *h = 0;
                }

                else caso_remover2(pt, h);

            }
        }
    }
}


void remover(int x, No **pt, int *h, int *quantidade){
    if((*pt) == NULL){
        *h = 0;
    }

    else{
        if(x < (*pt)-> chave){
            remover(x, &(*pt)->esq, h, quantidade);
            balancear(pt, 'E', h);

        }
        
        else{
            if (x > (*pt)-> chave){
                remover(x, &((*pt)->dir), h, quantidade);
                balancear(pt, 'D', h);
            }
            else{

                No *aux = *pt;
                if ((*pt)->esq == NULL){

                    (*pt) = (*pt)->dir;
                    *h = 1;
                    (*quantidade)--;

                    free(aux);    
                }
                else{
                    if ((*pt)->dir == NULL){

                        (*pt) = (*pt)->esq;
                        *h = 1;
                        (*quantidade)--;
                        free(aux); 
                    }else{

                        No* s = (*pt)->dir;
                        if (s->esq == NULL){

                            s->esq = (*pt)->esq;
                            s->bal = (*pt)->bal;
                            *pt = s;
                            *h = 1;
                            (*quantidade)--;
                            free(aux);
                            
                        }
                        
                        else{
                            No* paiS;
                            while (s->esq != NULL){

                                paiS = s;
                                s = s->esq;
                            }
                        
                            trocar(pt, &(paiS)->esq);
                            remover(x, &(*pt)->dir, h, quantidade);
                        }
                        balancear(pt, 'D', h);
                    }
                }
            }
        }
    }
}



int altura(No* pt){
    if(pt == NULL) return 0;
    else{
        int esq = altura(pt->esq);
        int dir = altura(pt->dir);

        if(dir > esq) return dir + 1;
        else return esq + 1;
    }
}

void checa_avl(No* pt, int *avl){
    if(pt != NULL){
        int esq = altura(pt->esq);
        int dir = altura(pt->dir);

        int avl_esq;
        int avl_dir;

        checa_avl(pt->esq,&avl_esq);
        checa_avl(pt->dir,&avl_dir);
        
        
        if(pt->bal != dir - esq || pt->bal < -1 && pt->bal > 1 && !avl_esq && !avl_dir){
            *avl = 0;
        }
    }
}

int qtd_nos(No* pt){
    if(pt == NULL) return 0;

    else return 1 + qtd_nos(pt->esq) + qtd_nos(pt->dir);
}

int main(){
    srand(time(NULL));

    clock_t t1 = clock();

    int h = 1;
    int avl = 1;

    int valor = 0;

    int AvlQ = 1000;

    int NoQ = 10000;

    int RmvQ = 1000;


    No *pt_raiz[AvlQ];

    for(int i = 0; i < AvlQ; i++){
        pt_raiz[i] = NULL;
    }

    int cont[AvlQ];
    for(int i =0; i<AvlQ;i++){
        cont[i] = 0;
    }

    for (int i = 0; i < AvlQ; i++){
        while (cont[i] < NoQ){
            valor  =  rand() % 100000;
            inserir(valor, &pt_raiz[i], &h, &cont[i]);
        }
    }

    printf("após as inserções\n");
    for (int i = 0; i < AvlQ; i++){ 
            printf ("━━━━━━━━━━━━━━━━━━━━━━━━\n");
            printf("\n avl %d:\n", i+1);

            printf("Quantidade de nós: %d\n",qtd_nos(pt_raiz[i]));
            printf("Altura: %d\n", altura(pt_raiz[i]));
            
            checa_avl(pt_raiz[i], &avl);

            if(avl){
                printf("Conclusão: essa arvore é avl\n");
            }

            else{
                printf("Conclusão: essa arvore nao é avl\n");
                avl = 1;
            }  
        
    }

    for (int i = 0; i < AvlQ; i++){
        while (cont[i] > NoQ - RmvQ){
            valor  =  rand() % 100000;
            remover(valor, &pt_raiz[i], &h, &cont[i]);
        }
    }

    
    printf("\n\napós as remocoes\n");
    for (int i = 0; i < AvlQ; i++){

            printf ("━━━━━━━━━━━━━━━━━━━━━━━━\n");
            printf("\navl %d:\n", i+1);
            
            printf("Quantidade de nós: %d\n",qtd_nos(pt_raiz[i]));
            printf("Altura: %d\n", altura(pt_raiz[i]));

            checa_avl(pt_raiz[i], &avl);
            if(avl){
                printf("Conclusão: essa arvore é avl\n\n");
            }
            else{
                printf("Conclusão: essa arvore nao é avl\n\n");
                avl = 1;
            }  
    }

    clock_t t0 = clock();
    printf("\n\nTempo de execucao: %ds\n", (int)((t0 - t1)/CLOCKS_PER_SEC));
    
    return 0;
}