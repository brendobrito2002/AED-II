#ifndef AVL_H
#define AVL_H

typedef struct no {
	int valor;
	int fb;
	struct no *esq, *dir;
} no;

typedef no *arvore;

void inicializar_avl(arvore *raiz); // 0
arvore inserir_avl(int valor, arvore raiz, int *cresceu); // 1
arvore rotacionar_avl(arvore raiz); // aux
arvore rotacao_simples_esquerda(arvore raiz); // aux
arvore rotacao_simples_direita(arvore raiz); // aux
arvore rotacao_dupla_esquerda(arvore raiz); // aux
arvore rotacao_dupla_direita(arvore raiz); // aux
void pre_order_avl(arvore raiz); // 2
arvore remover_avl(int valor, arvore raiz, int *diminuiu); // 3

#endif