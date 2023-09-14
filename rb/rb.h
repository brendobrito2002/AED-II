#ifndef RB_H
#define RB_H

enum cor { VERMELHO, PRETO, DUPLO_PRETO };

typedef struct no{
	int dado;
	enum cor cor;
	struct no *esq, *dir, *pai;
}no;

typedef no *arvore;

void inicializar(arvore *raiz); // 0
void inserir(int valor, arvore *raiz); // 1
void pre_order(arvore raiz); // 2
void remover (int valor, arvore *raiz); // 3


void ajustar(arvore *raiz, arvore elemento); // AUX_1
void rotacao_simples_direita(arvore *raiz, arvore pivo); // AUX_1
void rotacao_simples_esquerda(arvore *raiz, arvore pivo); // AUX_1
void rotacao_dupla_direita(arvore *raiz, arvore pivo); // AUX_1
void rotacao_dupla_esquerda(arvore *raiz, arvore pivo); // AUX_1


void imprimir_elemento(arvore raiz); // AUX_2


void reajustar(arvore *raiz, arvore elemento); // AUX_3
void retira_duplo_preto(arvore *raiz, arvore elemento); // AUX_3
int maior_elemento(arvore raiz); // AUX_3


enum cor cor(arvore elemento); // AUX_geral
int eh_raiz(arvore elemento); // AUX_geral
int eh_filho_esquerdo(arvore elemento); // AUX_geral
arvore irmao(arvore elemento); // AUX_geral
arvore tio(arvore elemento); // AUX_geral
int eh_filho_direito(arvore elemento); // AUX_geral

#endif




