#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

// Inserir um valor
arvore inserir_bst(int valor, arvore raiz){ // 1
    //caso base - inserir em uma árvore vazia
    if(raiz == NULL) {
        arvore novo = (arvore) malloc(sizeof(struct no));
        novo->esq = NULL;
        novo->dir = NULL;
        novo->valor = valor;
        //o retorno é a raiz da sub-árvore unitária que foi iniciada
        return novo;
    }
    //caso recursivo/indutivo
    else{
        if(valor > raiz->valor) {
            raiz->dir = inserir_bst(valor, raiz->dir);
        } else {
            raiz->esq = inserir_bst(valor, raiz->esq);
        }
        return raiz;
    }

}

// Impressão pre-order
void pre_order_bst(arvore raiz){ // relativa - esq - dir // 2
    if(raiz != NULL){
        //processar a raiz relativa
        printf("[%d]", raiz->valor);

        //encadeamentos recursivos esq, dir
        pre_order_bst(raiz->esq);
        pre_order_bst(raiz->dir);

    } //else caso base implícito não faz nada

}

// Impressão in-order
void in_order_bst(arvore raiz){ // esq - relativa - dir // 3
    if(raiz != NULL){
        in_order_bst(raiz->esq);
        printf("[%d]", raiz->valor);
        in_order_bst(raiz->dir);
    }
}

// Impressão pos-order
void pos_order_bst(arvore raiz){ // esq - dir - relativa // 4
    if(raiz != NULL){
        pos_order_bst(raiz->esq);
        pos_order_bst(raiz->dir);
        printf("[%d]", raiz->valor);
    }
}

// Impressão ordem reversa(decrescente)
void reverso_bst(arvore raiz){ // dir - relativa - esq // 5
    if(raiz != NULL){
        reverso_bst(raiz->dir);
        printf("[%d]", raiz->valor);
        reverso_bst(raiz->esq);
    }
}

// Função recursiva para contar nós que armazenam números primos
int qtdPrimo_bst(arvore raiz) { // 6
    if (raiz == NULL) {
        return 0;
    }

    int count = ehPrimo_bst(raiz->valor);

    count += qtdPrimo_bst(raiz->esq);
    count += qtdPrimo_bst(raiz->dir);

    return count;
}

// Função que diz se um numero é primo ou não
int ehPrimo_bst(int valor) { // 6.5 
    if (valor <= 1) {
        return 0;
    }

    for (int i = 2; i * i <= valor; i++) {
        if (valor % i == 0) {
            return 0;
        }
    }

    return 1;
}

// Imprime o sucessor
int printSucessor_bst(int valor, arvore raiz) { // 7
    arvore sucessor = searchSucessor_bst(raiz, valor);

    if (sucessor == NULL) {
        return -1;
    } else {
        return sucessor->valor;
    }
}

// Busca o sucessor
arvore searchSucessor_bst(arvore raiz, int valor) { // 7.5
    if (raiz == NULL){
        return NULL;
    }
    //  valor do nó atual > valor buscado, o sucessor está no subárvore esquerda
    if (raiz->valor > valor){
        return searchSucessor_bst(raiz->esq, valor);
    }
    // valor do nó atual < valor buscado, o sucessor está no subárvore direita
    if (raiz->valor < valor){
        return searchSucessor_bst(raiz->dir, valor);
    }
    // valor do nó atual = valor buscado, o sucessor está no subárvore direita ou em algum ancestral mais próximo que seja maior que o valor buscado
    if (raiz->dir != NULL) {
        raiz = raiz->dir;
        while (raiz->esq != NULL)
            raiz = raiz->esq;
        return raiz;
    }
    
    // Não há sucessor para o valor buscado
    return NULL;
}

// Imprime o caminho até o valor pedido
void caminho_bst(int valor, arvore raiz){ // 8 
    if(raiz != NULL){
    
        printf("[%d]", raiz->valor);
            
        if(raiz->valor == valor){
            printf("\n");
        }
        else if (valor < raiz->valor) {
            caminho_bst(valor, raiz->esq);
        } else {
            caminho_bst(valor, raiz->dir);
        }
    }
}

// Remover um elemento com 0, 1 (esquerdo ou direito) ou 2 filhos
arvore remover_bst(int valor, arvore raiz) { // 9
    //Remover de uma (sub)árvore vazia / remover elemento inexistente
    if(raiz == NULL) {
        return raiz;
    }
    //Encontrou o elemento
    if(raiz->valor == valor) {
        //Verificação de 0 filhos, 1 filho, 2 filhos
        //caso 1: 0 filhos
        if(raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }
        //caso 2.1: 1 filho esq
        if(raiz->esq != NULL && raiz->dir == NULL) {
            arvore aux = raiz->esq;
            free(raiz);
            return aux;
        }
        //caso 2.2: 1 filho direito
        if(raiz->esq == NULL && raiz->dir != NULL){
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

        raiz->valor = temp->valor;
        raiz->esq = remover_bst(temp->valor, raiz->esq);
        
        return raiz;
    }
    if(valor > raiz->valor) {
        raiz->dir = remover_bst(valor, raiz->dir);
    } else {
        raiz->esq = remover_bst(valor, raiz->esq);
    }
    return raiz;
}

// Soma recursivamente os elementos da arvore
int somatorio_bst(arvore raiz){ // 10
    if(raiz != NULL){
        return raiz->valor + somatorio_bst(raiz->esq) + somatorio_bst(raiz->dir);
    }
}

// Podar o valor escolhido e seus descendentes
arvore podar_bst(int valor, arvore raiz) { // 11
    if (raiz == NULL) {
        return raiz;
    }
    
    if (raiz->valor == valor) {
        raiz = liberar_bst(raiz);
        return NULL;
    }
    
    if (valor < raiz->valor) {
        raiz->esq = podar_bst(valor, raiz->esq);
    } else {
        raiz->dir = podar_bst(valor, raiz->dir);
    }
    
    return raiz;
}

// Libera espaço de memoria
arvore liberar_bst(arvore raiz) { // 11.5
    if (raiz == NULL) {
        return NULL;
    }
    
    raiz->esq = liberar_bst(raiz->esq);
    raiz->dir = liberar_bst(raiz->dir);
    free(raiz);
    
    return NULL;
}

// Reajustando os valores aplicando um valor percentual
void reajuste_bst(arvore raiz, int valor) { // 12
    if (raiz != NULL) {
        raiz->valor += (raiz->valor * valor / 100);
        reajuste_bst(raiz->esq, valor);
        reajuste_bst(raiz->dir, valor);
    }
}

// Busca um elemento recursivamente
int existe_bst(arvore raiz, int valor){ // 13
    if(raiz == NULL){
        return 0;
    }
    
    if(valor < raiz->valor){
        return existe_bst(raiz->esq, valor);
    }else if(valor > raiz->valor){
        return existe_bst(raiz->dir, valor);
    }else{
        return 1;
    }
}

// Encontrou agora imprime
void descendente_bst(int valor, arvore raiz) { // 14
    arvore no = busca_bst(raiz, valor);
    
    if (no == NULL) {
        return;
    }
    
    if (no->esq != NULL) {
        in_order_bst(no->esq);
    }
    
    if (no->dir != NULL) {
        in_order_bst(no->dir);
    }
}

// Busca nós
arvore busca_bst(arvore raiz, int valor) { // 14.5
    if (raiz == NULL || raiz->valor == valor) {
        return raiz;
    }
    
    if (valor < raiz->valor) {
        return busca_bst(raiz->esq, valor);
    } else {
        return busca_bst(raiz->dir, valor);
    }
}

// Calcula a altura da arvore recursivamente
int altura_bst(arvore raiz){ // 15
    if(raiz == NULL){
        return 0;
    }else{
        int esq = altura_bst(raiz->esq);
        int dir = altura_bst(raiz->dir);
        if(esq > dir){
            return esq + 1;
        }else{
            return dir + 1;
        }
    }
}
