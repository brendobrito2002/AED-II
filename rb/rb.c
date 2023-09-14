#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

arvore no_null;

/*Inicializa a árvore vazia com a raiz = null e inicializa o nó nulo duplo preto que será utilizado no método remover.*/
void inicializar(arvore *raiz) { // 0
	*raiz = NULL;
	no_null = (arvore) malloc(sizeof(struct no));
	no_null->cor = DUPLO_PRETO;
	no_null->dado = 0;
    no_null->esq = NULL;
    no_null->dir = NULL;
}

/* Adiciona um novo elemento na árvore.*/
void inserir(int valor, arvore *raiz) { // 1
	arvore posicao, pai, novo;
    //utiliza-se *raiz, por ser um ponteiro de ponteiro
	posicao = *raiz;
	pai = NULL;

	/* vai descendo a raiz com um ponteiro "atrasado" para o pai do elemento até encontrar uma posição vaga(NULL) */
	while(posicao != NULL) {
		pai = posicao;
		if(valor > posicao->dado) 
			posicao = posicao->dir;
		else 
			posicao = posicao->esq;
	}

    //Após achar a posição, inicializa o novo elemento
	novo = (arvore) malloc(sizeof(struct no));
	novo->dado = valor;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->pai = pai;
	novo->cor = VERMELHO;

    //Atualiza a raiz da árvore, caso esteja inserindo o primeiro elemento
	if(eh_raiz(novo))	
			*raiz = novo;
	else {
        //Se não for a raiz, é preciso realizar a ligação do pai(direita ou esquerda) com o novo elemento
		if(valor > pai->dado)
			pai->dir = novo;
		else
			pai->esq = novo;
	}

    //Após inserir, verifica e ajusta a árvore resultante
	ajustar(raiz, novo);
}


/* Verifica se a árvore está obedecendo todas as regras da RB e aplica as correções necessárias após a inserção. Raiz absoluta e elemento recém inserido */
void ajustar(arvore *raiz, arvore elemento){ // AUX_1
    // A árvore está desajustada se tanto o elemento quanto o seu pai estiverem com a cor vermelha
    // Utilizamos um while para continuar a verificação até chegar a raiz, quando necessário
    
	while(cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO) {
			// Caso 1: Cor do tio é vermelha, desce o preto do avô
			if(cor(tio(elemento)) == VERMELHO) {
				tio(elemento)->cor = PRETO;
				elemento->pai->cor = PRETO;
				elemento->pai->pai->cor = VERMELHO;
				
				// Continua a verificação a partir do avô, que mudou para vermelho e pode ter gerado uma sequência vermelho-vermelho	
				elemento = elemento->pai->pai;
				
				continue;
			} 
			// Caso 2a: rotação simples direita
			if(eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)) {
				rotacao_simples_direita(raiz, elemento->pai->pai);
				elemento->pai->cor = PRETO;
				elemento->pai->dir->cor = VERMELHO;
				
				continue;
			}
			
			//caso 2b: rotação simples esquerda
			if(eh_filho_direito(elemento) && eh_filho_direito(elemento->pai)) {
			    rotacao_simples_esquerda(raiz, elemento->pai->pai);
			    elemento->pai->cor = PRETO;
			    elemento->pai->esq->cor = VERMELHO;
			    
				continue;
			}
			
			//caso 3a: rotação dupla direita
			if(eh_filho_direito(elemento) && eh_filho_esquerdo(elemento->pai)) {
                rotacao_dupla_direita(raiz, elemento->pai->pai);
			    elemento->cor = PRETO;
			    elemento->dir->cor = VERMELHO;
			    
				continue;
			}
			
			//caso 3b: rotação dupla esquerda
			if(eh_filho_esquerdo(elemento) && eh_filho_direito(elemento->pai)) {
			    rotacao_dupla_esquerda(raiz, elemento->pai->pai);
			    elemento->cor = PRETO;
			    elemento->esq->cor = VERMELHO;
			    
				continue;
			}
			
	}
    //Após todas as correções a raiz pode ter ficado na cor vermelha, portanto passamos ela novamente para cor preta
	(*raiz)->cor = PRETO;
}


void rotacao_simples_direita(arvore *raiz, arvore pivo){ // AUX_1
	arvore u, t1;
			
	u = pivo->esq;
    t1 = u->dir;

    /*Para fazer a ligação da raiz da sub-árvore resultante com o seu pai, é preciso saber se o pivo p era um filho esquerdo ou direito*/
	int posicao_pivo = eh_filho_esquerdo(pivo);
			
	//Atualização dos ponteiros
	pivo->esq = t1;
    if(t1 != NULL){
		t1->pai = pivo;
    }

	u->dir = pivo;

	u->pai = pivo->pai;
	pivo->pai = u;

			
     // Se não existir árvore acima de u, u passa a ser a raiz da árvore
	if(eh_raiz(u)){
	    u->pai = NULL;
		*raiz = u;
	}else {
            // Caso contrário (se existir) é preciso ligar o restante da árvore a esta sub-árvore, resultante da rotação
		if(posicao_pivo)
			u->pai->esq = u;
		else
			u->pai->dir = u;
	}
}


void rotacao_simples_esquerda(arvore *raiz, arvore pivo){ // AUX_1
    arvore u, t2;
    
    u = pivo->dir;
    t2 = u->esq;
    
    int posicao_pivo = eh_filho_esquerdo(pivo);
    
    // Atualização de ponteiros
    pivo->dir = t2;
    if(t2 != NULL){
        t2->pai = pivo;
    }
    
    u->esq = pivo;
    u->pai = pivo->pai;
    pivo->pai = u;
    
    //Se não existir árvore acima de u, u passa a ser a raiz da árvore
    if(eh_raiz(u)){
        u->pai = NULL;
        *raiz = u;
    }else{
        // Caso contrário (se existir) é preciso ligar o restante da árvore a esta sub-árvore, resultante da rotação
        if(posicao_pivo){
            u->pai->esq = u;
        }else{
            u->pai->dir = u;
        }
    }
}


void rotacao_dupla_direita(arvore *raiz, arvore pivo){ // AUX_1
    arvore u, v, t2, t3;
    
    u = pivo->esq;
    v = u->dir;
    t2 = v->esq;
    t3 = v->dir;

    int posicao_pivo = eh_filho_esquerdo(pivo);

    // Atualização de ponteiros
    v->esq = u;
    u->dir = t2;
    if (t2 != NULL) {
        t2->pai = u;
    }
    
    v->dir = pivo;
    pivo->esq = t3;
    if (t3 != NULL) {
        t3->pai = pivo;
    }

    u->pai = v;
    v->pai = pivo->pai;
    pivo->pai = v;
    
    // Se não existir árvore acima de v, v passa a ser a raiz da árvore
    if (eh_raiz(v)) {
        v->pai = NULL;
        *raiz = v;
    } else {
        // Caso contrário (se existir), é preciso ligar o restante da árvore a esta sub-árvore resultante da rotação
        if (posicao_pivo) {
            v->pai->esq = v;
        } else {
            v->pai->dir = v;
        }
        
    }
    
}

void rotacao_dupla_esquerda(arvore *raiz, arvore pivo){ // AUX_1
    arvore u, v, t2, t3;
    
    u = pivo->dir;
    v = u->esq;
    t2 = v->esq;
    t3 = v->dir;
    
    int posicao_pivo = eh_filho_esquerdo(pivo);
    
    // Atualização de ponteiros
    v->dir = u;
    u->esq = t3;
    if(t3 != NULL){
        t3->pai = u;
    }
    
    pivo->dir = t2;
    if(t2 != NULL){
        t2->pai = pivo;
    }
    
    v->esq = pivo;
    u->pai = v;
    v->pai = pivo->pai;
    pivo->pai = v;
    
    // Se não existir árvore acima de v, v passa a ser a raiz da árvore
    if (eh_raiz(v)) {
        v->pai = NULL;
        *raiz = v;
    } else {
        // Caso contrário (se existir), é preciso ligar o restante da árvore a esta sub-árvore resultante da rotação
        if (posicao_pivo) {
            v->pai->esq = v;
        } else {
            v->pai->dir = v;
        }
        
    }

}

//--------------------------------------------------------------------------------------------------------------------------------------------------

void pre_order(arvore raiz) { // 2
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		pre_order(raiz->esq);
		pre_order(raiz->dir);
	}
}


void imprimir_elemento(arvore raiz) { // AUX_2
	switch(raiz->cor){
		case PRETO:
			printf("[%d B]", raiz->dado);
			break;
		case VERMELHO:
			printf("[%d R]", raiz->dado);
			break;
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

void remover (int valor, arvore *raiz) { // 3
	arvore posicao;
	posicao = *raiz;

	while(posicao != NULL) {
		if(valor == posicao->dado) {
			//elemento possui dois filhos
            if(posicao->esq != NULL && posicao->dir != NULL) { 
                int temp = maior_elemento(posicao->esq);
	    		remover(temp, raiz);
    			posicao->dado = temp;   
                break;
            }

			//O elemento possui apenas um filho (direito)
			if(posicao->esq == NULL && posicao->dir != NULL) {
                //O seu filho direito sobe para a posição do elemento  a ser removido e recebe a cor preta
				posicao->dir->cor = PRETO;
                posicao->dir->pai = posicao->pai;

				if(eh_raiz(posicao)) {
					*raiz = posicao->dir;
				} else {
					if(eh_filho_esquerdo(posicao)) {
    					posicao->pai->esq = posicao->dir;
					} else {
						posicao->pai->dir = posicao->dir;
    				}
				}
                free(posicao);   
				break;
			}


			//O elemento possui apenas um filho (esquerdo)
			if(posicao->esq != NULL && posicao->dir == NULL) {
				posicao->esq->cor = PRETO;
				posicao->esq->pai = posicao->pai;
				
				if(eh_raiz(posicao)){
				    *raiz = posicao->esq;
				}else{
				    if(eh_filho_esquerdo(posicao)){
				        posicao->pai->esq = posicao->esq;
				    }else{
				        posicao->pai->dir = posicao->esq;
				    }
				}
				free(posicao);
				break;
			}

			//O elemento não possui filhos
			if(posicao->esq == NULL && posicao->dir == NULL) {
				//Remover raiz sem filhos					
				if(eh_raiz(posicao)) {
					*raiz = NULL;
                    free(posicao);
					break;
				}

				//Remover elemento que não possui filhos e não é raiz
				//Se for vermelho, apenas remove atualizando o ponteiro 
				//correspondente do pai
				if(posicao->cor == VERMELHO) {
					if(eh_filho_esquerdo(posicao))
						posicao->pai->esq = NULL;
					else
						posicao->pai->dir = NULL;
                    free(posicao);
					break;
				} else {
				//Se o elemento for preto, substitui pelo duplo preto e depois ajusta a árvore
                    no_null->cor = DUPLO_PRETO;
    				no_null->pai = posicao->pai;
    				if(eh_filho_esquerdo(posicao))
    					posicao->pai->esq = no_null;
    				else
    					posicao->pai->dir = no_null;
    				free(posicao);
                    reajustar(raiz, no_null);
    				break;
				}
			}
		}	
		if(valor > posicao->dado) 
			posicao = posicao->dir;
		else 
			posicao = posicao->esq;
	}
}

//Realiza a correção da árvore após a remoção de um elemento preto que não possui filhos, ou seja, elimina o nó null o duplo-preto.
void reajustar(arvore *raiz, arvore elemento){ // AUX_3
	//caso 1 (remove duplo preto)	
	if(eh_raiz(elemento)) {
		elemento->cor = PRETO;
        if(elemento == no_null) {
            *raiz = NULL;
		}
		return;
	}

	//caso 2 (não remove duplo preto)
	if(  cor(elemento->pai) == PRETO &&
		 cor(irmao(elemento)) == VERMELHO &&
		 cor(irmao(elemento)->dir) == PRETO &&
		 cor(irmao(elemento)->esq) == PRETO ) {
        //Verifica se é o caso 2 esquerdo ou direito
		if(eh_filho_esquerdo(elemento))
			rotacao_simples_esquerda(raiz, elemento->pai);
		else
			rotacao_simples_direita(raiz, elemento->pai);	
				
        elemento->pai->pai->cor = PRETO;
		elemento->pai->cor = VERMELHO;
				
        //Atenção à chamada recursiva do reajustar.
        reajustar(raiz, elemento);
		return;
	}

	//caso 3 (não remove duplo preto)
	if( cor(elemento->pai) == PRETO &&
	    cor(irmao(elemento)) == PRETO &&
	    cor(irmao(elemento)->dir) == PRETO &&
	    cor(irmao(elemento)->esq) == PRETO) {
	   
	    irmao(elemento)->cor = VERMELHO;
	    
	    
	    elemento->pai->cor = DUPLO_PRETO;
	    
	    //Verificar e remover o no_null
	    if(cor(elemento) == DUPLO_PRETO)
	        retira_duplo_preto(raiz, elemento);
	    
        //Chamada recursiva para eliminar o duplo preto do elemento P
        reajustar(raiz, elemento->pai);
		return ;
	}	

	//caso 4 (remove duplo preto)
	if( cor(elemento->pai) == VERMELHO &&
	    cor(irmao(elemento)) == PRETO &&
	    cor(irmao(elemento)->dir) == PRETO &&
	    cor(irmao(elemento)->esq) == PRETO) {
	    irmao(elemento)->cor = VERMELHO;
	    
	    elemento->pai->cor = PRETO;
	    
	    //Verificar e remover o no_null
	    if(cor(elemento) == DUPLO_PRETO)
	        retira_duplo_preto(raiz, elemento);
	        
		return;
	}

	//caso 5a(esq) (não remove duplo preto)
    if( cor(irmao(elemento)) == PRETO &&
        cor(irmao(elemento)->esq) == VERMELHO &&
        cor(irmao(elemento)->dir) == PRETO &&
        eh_filho_esquerdo(elemento)) {
            
	    rotacao_simples_direita(raiz, irmao(elemento));
	    
        elemento->pai->dir->cor = PRETO;
        elemento->pai->dir->dir->cor = VERMELHO;
	    
	    reajustar(raiz, elemento);
		return;
	}

	//caso 5b(dir) (não remove duplo preto)
	if( cor(irmao(elemento)) == PRETO &&
	    cor(irmao(elemento)->esq) == PRETO &&
	    cor(irmao(elemento)->dir) == VERMELHO &&
	    eh_filho_direito(elemento)) {
	        
	    rotacao_simples_esquerda(raiz, irmao(elemento));
	    
	    elemento->pai->esq->cor = PRETO;
	    elemento->pai->esq->esq->cor = VERMELHO;
	    
	    reajustar(raiz, elemento);
		return;
	}

	//caso 6a(esq) (remove duplo preto)
	if( cor(irmao(elemento)) == PRETO &&
	    cor(irmao(elemento)->dir) == VERMELHO &&
	    eh_filho_esquerdo(elemento)) {	
	        
	    rotacao_simples_esquerda(raiz, elemento->pai);
	    
        if(elemento->pai->cor == VERMELHO)
            elemento->pai->pai->cor = VERMELHO;
        else
            elemento->pai->pai->cor = PRETO;
	    
	    elemento->pai->cor = PRETO;
	    elemento->pai->pai->dir->cor = PRETO;
	    
	    retira_duplo_preto(raiz, elemento);
	    
		return;
	}

	//caso 6b(dir) (remove duplo preto)
	if( cor(irmao(elemento)) == PRETO &&
	    cor(irmao(elemento)->esq) == VERMELHO &&
	    eh_filho_direito(elemento)) {
	        
	    rotacao_simples_direita(raiz, elemento->pai);
	    
        if(elemento->pai->cor == VERMELHO)
            elemento->pai->pai->cor = VERMELHO;
        else
            elemento->pai->pai->cor = PRETO;
        
	    elemento->pai->cor = PRETO;
	    elemento->pai->pai->esq->cor = PRETO;
	    
	    retira_duplo_preto(raiz, elemento);
	    
		return;
	}
}


void retira_duplo_preto(arvore *raiz, arvore elemento) { // AUX_3
	if(elemento == no_null)
		if(eh_filho_esquerdo(elemento))
			elemento->pai->esq = NULL;
		else
			elemento->pai->dir = NULL;
	else
		elemento->cor = PRETO;
}


int maior_elemento(arvore raiz) { // AUX_3
	if(raiz == NULL)
		return -1;
	if(raiz->dir == NULL)
		return raiz->dado;
	else
		return maior_elemento(raiz->dir);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------

/*Retorna a cor de um nó. Observe que, por definição, o null é preto*/
enum cor cor(arvore elemento) { // AUX_geral
	enum cor c;
	if(elemento==NULL)
		return PRETO;
	else
		return elemento->cor;
	return c;
}
/*Verifica se um nó é a raiz da árvore*/
int eh_raiz(arvore elemento) { // AUX_geral
	return (elemento->pai == NULL);
}
/*Verifica se um nó é filho esquerdo*/
int eh_filho_esquerdo(arvore elemento) { // AUX_geral
	return (elemento->pai != NULL && elemento == elemento->pai->esq);
}

/*Verifica se um nó é filho direito*/
int eh_filho_direito(arvore elemento) { // AUX_geral
	return (elemento->pai != NULL && elemento == elemento->pai->dir);
}

arvore tio(arvore elemento) { // AUX_geral
	return irmao(elemento->pai);
}

arvore irmao(arvore elemento) { // AUX_geral
	if(eh_filho_esquerdo(elemento))
		return elemento->pai->dir;
	else
		return elemento->pai->esq;
}
