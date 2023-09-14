#ifndef BST_H
#define BST_H

typedef struct no {
    int valor;
    struct no *esq, *dir;
} no;

typedef no* arvore;

arvore inserir_bst(int valor, arvore raiz); // 1
void pre_order_bst(arvore raiz); // 2
void in_order_bst(arvore raiz); // 3
void pos_order_bst(arvore raiz); // 4
void reverso_bst(arvore raiz); // 5
int qtdPrimo_bst(arvore raiz); // 6
int ehPrimo_bst(int valor); // 6.5 
int printSucessor_bst(int valor, arvore raiz); // 7
arvore searchSucessor_bst(arvore raiz, int valor); // 7.5
void caminho_bst(int valor, arvore raiz); // 8
arvore remover_bst(int valor, arvore raiz); // 9
int somatorio_bst(arvore raiz); // 10
arvore podar_bst(int valor, arvore raiz); // 11
arvore liberar_bst(arvore raiz); // 11.5 
void reajuste_bst(arvore raiz, int valor); // 12
int existe_bst(arvore raiz, int valor); // 13
arvore busca_bst(arvore raiz, int valor); // 14
void descendente_bst(int valor, arvore raiz); // 14.5
int altura_bst(arvore raiz); // 15

#endif




