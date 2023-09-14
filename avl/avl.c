#include <stdio.h>
#include <stdlib.h>
#include "avl.h"


// Inicializa a arvore
void inicializar_avl(arvore *raiz) { // 0
	*raiz = NULL;
}

// Inserir
arvore inserir_avl(int valor, arvore raiz, int *cresceu) { // 1
    if(raiz == NULL) {
        // Tudo inicializado
        arvore novo = (arvore) malloc(sizeof(struct no));
        novo->valor = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->fb = 0;
        *cresceu = 1;
        return novo;
    }
    // valor < raiz->valor --> raiz->esq
    if(valor < raiz->valor) {
        raiz->esq = inserir_avl(valor, raiz->esq, cresceu);
        if(*cresceu) {
            switch(raiz->fb) {
                // --> -2
                case -1:
                    *cresceu = 0;
                    return rotacionar_avl(raiz);
                // --> -1
                case 0:
                    raiz->fb = -1;
                    *cresceu = 1;
                    break;
                // --> 0
                case 1:
                    raiz->fb = 0;
                    *cresceu = 0;
                    break;
            }
        }
    // valor > raiz->valor --> raiz->dir
    } else {
        raiz->dir = inserir_avl(valor, raiz->dir, cresceu);
        if(*cresceu) {
            switch(raiz->fb) {
                // --> 0
                case -1:
                    raiz->fb = 0;
                    *cresceu = 0;
                    break;
                // --> 1
                case 0:
                    raiz->fb = 1;
                    *cresceu = 1;
                    break;
                // --> 2
                case 1:
                    *cresceu = 0;
                    return rotacionar_avl(raiz);
            }
        }
    }
    return raiz; 
}


// Direcionador para a rotação correta
arvore rotacionar_avl(arvore raiz){ // aux
    // Raiz relativa
    if(raiz->fb > 0){
        // Analisar sub-arvore direita da raiz relativa e seu fb
        switch(raiz->dir->fb){
            // 0 = RSE
            // Só ocorre no remover
            case 0:
                return rotacao_simples_esquerda(raiz);
            // +2 +1 = RSE
            case 1:
                //printf("ROTACAO SIMPLES ESQUERDA %d\n", raiz->valor);
                return rotacao_simples_esquerda(raiz);
            // +2 -1 = RDE
            case -1:
                //printf("ROTACAO DUPLA ESQUERDA %d\n", raiz->valor);
                return rotacao_dupla_esquerda(raiz);
        }
    } else if (raiz->fb < 0) {
        // Analisar sub-arvore esquerda da raiz relativa e seu  fb
        switch(raiz->esq->fb){
            // 0 = RSD
            // So ocorre no remover
            case 0:
                return rotacao_simples_direita(raiz);
            case -1:
                //printf("ROTACAO SIMPLES DIREITA %d\n", raiz->valor);
                return rotacao_simples_direita(raiz);
            case 1:
                //printf("ROTACAO DUPLA DIREITA %d\n", raiz->valor);
                return rotacao_dupla_direita(raiz);
        }
    }
}


// RSE = +2 +1
arvore rotacao_simples_esquerda(arvore raiz){ // aux
    arvore p, u, t1, t2, t3;
    
    // Inicializar os ponteiros
    p = raiz;
    u = p->dir;
    t1 = p->esq;
    t2 = u->esq;
    t3 = u->dir;
    
    // Atualiza os ponteiros
    p->dir = t2;
    u->esq = p;
    
    // Atualizar o fatores de balanço de acordo com o fb de u
    if(u->fb == 1){
        //printf("u->fb = 1\n");
        p->fb = 0;
        u->fb = 0;
    }else{
        //printf("u->fb = 0\n");
        // 0 - so ocorre no remover
        p->fb = 1;
        u->fb = -1;
    }
    // Retorna nova raiz relativa
    return u;
}


// RSD = -2 -1
arvore rotacao_simples_direita(arvore raiz){ // aux
    arvore p, u, t1, t2, t3;
    
    // Inicializar ponteiros
    p = raiz;
    u = p->esq;
    t1 = u->esq;
    t2 = u->dir;
    t3 = p->dir;
    
    // Atualizar ponteiros
    p->esq = t2;
    u->dir = p;
    
    // Atualizar os fb
    if(u->fb == -1){
        //printf("u->fb = -1\n");
        p->fb = 0;
        u->fb = 0;
    }else{
        //printf("v->fb = 0\n");
        // 0 - so ocorre no remover
        p->fb = -1;
        u->fb = 1;
    }
    // Retorna nova raiz relativa
    return u;
}


// RDE = +2 -1
arvore rotacao_dupla_esquerda(arvore raiz){ // aux
    arvore p, u, v, t1, t2, t3, t4;
    
    // Inicializar ponteiros
    p = raiz;
    u = p->dir;
    v = u->esq;
    t1 = p->esq;
    t2 = v->esq;
    t3 = v->dir;
    t4 = u->dir;
    
    // Atualizar ponteiros
    v->esq = p;
    p->dir = t2;
    v->dir = u;
    u->esq = t3;
    
    // Atualizar os fb
    switch(v->fb){
        case -1:
            //printf("v->fb = -1\n");
            p->fb = 0;
            u->fb = 1;
            break;
        case 0:
            //printf("v->fb = 0\n");
            p->fb = 0;
            u->fb = 0;
            break;
        case 1:
            //printf("v->fb = 1\n");
            p->fb = -1;
            u->fb = 0;
            break;
    }
    v->fb = 0;
    return v;
}


// RDD = -2 +1
arvore rotacao_dupla_direita(arvore raiz){ // aux
    arvore p, u, v, t1, t2, t3, t4;
    
    // Inicializar ponteiros
    p = raiz;
    u = p->esq;
    v = u->dir;
    t1 = u->esq;
    t2 = v->esq;
    t3 = v->dir;
    t4 = p->dir;
    
    // Atualizar ponteiros
    v->esq = u;
    u->dir = t2;
    v->dir = p;
    p->esq = t3;
    
    // Atualiza os fb
    switch(v->fb){
        case -1:
            //printf("v->fb = -1\n");
            p->fb = 1;
            u->fb = 0;
            break;
        case 0:
            //printf("v->fb = 0\n");
            p->fb = 0;
            u->fb = 0;
            break;
        case 1:
            //printf("v->fb = 1\n");
            p->fb = 0;
            u->fb = -1;
            break;
    }
    v->fb = 0;
    return v;
}


// Impressão pre-order
void pre_order_avl(arvore raiz){ // relativa - esq - dir // 2
    if(raiz != NULL){
        //processar a raiz relativa
        printf("[%d %d]", raiz->valor, raiz->fb);

        //encadeamentos recursivos esq, dir
        pre_order_avl(raiz->esq);
        pre_order_avl(raiz->dir);

    } //else caso base implícito não faz nada

}


// Remover 
arvore remover_avl(int valor, arvore raiz, int *diminuiu) { // 3
    if(raiz == NULL) {
        // Valor não encontrado ou arvore vazia
        *diminuiu = 0;
        return NULL;
    }
    //Encontrou o elemento
    if(raiz->valor == valor) {
        *diminuiu = 1;
        //Verificação de 0 filhos, 1 filho, 2 filhos
        //caso 1: 0 filhos
        if(raiz->esq == NULL && raiz->dir == NULL) {
        //printf("Achou(1): raiz->valor = [%d %d]\n", raiz->valor, raiz->fb);
            free(raiz);
            return NULL;
        }
        //caso 2.1: 1 filho esq
        if(raiz->esq != NULL && raiz->dir == NULL) {
        //printf("Achou(2.1): raiz->dir = [%d %d]\n", raiz->valor, raiz->fb);
            arvore aux = raiz->esq;
            free(raiz);
            return aux;
        }
        //caso 2.2: 1 filho direito
        if(raiz->esq == NULL && raiz->dir != NULL){
        //printf("Achou(2.2): raiz->esq = [%d %d]\n", raiz->valor, raiz->fb);
            arvore aux = raiz->dir;
            free(raiz);
            return aux;
        }

        //caso 3: dois filhos
        //não precisa de if
        arvore temp = raiz->esq;
        while(temp->dir != NULL) {
            temp = temp->dir;
        }
        //printf("Achou(3): raiz->esq = [%d %d]\n", raiz->valor, raiz->fb);
        raiz->valor = temp->valor;
        raiz->esq = remover_avl(temp->valor, raiz->esq, diminuiu);
        
        return raiz;
        
    }
    // valor < raiz->valor --> raiz->esq
    if(valor < raiz->valor){
        raiz->esq = remover_avl(valor, raiz->esq, diminuiu);
        if(*diminuiu) {
            switch(raiz->fb) {
                case -1:
                    //printf("valor < raiz->valor(Case -1)\n");
                    raiz->fb = 0;
                    *diminuiu = 1;
                    break;
                case 0:
                    //printf("valor < raiz->valor(Case 0)\n");
                    raiz->fb = 1;
                    *diminuiu = 0;
                    break;
                case 1:
                    //printf("valor < raiz->valor(Case 1)\n");
                    *diminuiu = 0;
                    rotacionar_avl(raiz);
            }
        }
    // valor > raiz->valor --> raiz->dir
    }else if(valor > raiz->valor) {
        raiz->dir = remover_avl(valor, raiz->dir, diminuiu);
        if(*diminuiu) {
            switch(raiz->fb) {
                case -1:
                    //printf("valor > raiz->valor(Case -1)\n");
                    *diminuiu = 0;
                    rotacionar_avl(raiz);
                case 0:
                    //printf("valor > raiz->valor(Case 0)\n");
                    raiz->fb = -1;
                    *diminuiu = 0;
                    break;
                case 1:
                    //printf("valor > raiz->valor(Case 1)\n");
                    raiz->fb = 0;
                    *diminuiu = 1;
                    break;
            }
        }
    }
    return raiz;
}