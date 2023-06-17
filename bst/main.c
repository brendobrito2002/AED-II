#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[]) {
    //declarar uma árvore
    arvore a;
    int opcao, aux, soma, alt, ex, primo, sucessor;

    //inicializar a árvore como uma árvore vazia
    a = NULL;

    while(1) {
        scanf("%d", &opcao);
        switch(opcao) {
            case 1:
                scanf("%d", &aux);
                a = inserir_bst(aux, a);
                break;
            case 2:
                pre_order_bst(a);
                printf("\n");
                break;
            case 3:
                in_order_bst(a);
                printf("\n");
                break;
            case 4:
                pos_order_bst(a);
                printf("\n");
                break;
            case 5:
                reverso_bst(a);
                printf("\n");
                break;
            case 6:
                printf("%d", primo = qtdPrimo_bst(a));
                printf("\n");
                break;
            case 7:
                scanf("%d", &aux);
                printf("%d", sucessor = printSucessor_bst(aux, a));
                printf("\n");
                break;
            case 8:
                scanf("%d", &aux);
                caminho_bst(aux, a);
                printf("\n");
                break;
            case 9:
                scanf("%d", &aux);
                remover_bst(aux, a);
                break;
            case 10:
                printf("%d", soma = somatorio_bst(a));
                printf("\n");
                break;
            case 11:
                scanf("%d", &aux);
                podar_bst(aux, a);
                break;
            case 12:
                scanf("%d", &aux);
                reajuste_bst(a, aux);
                break;
            case 13:
                scanf("%d", &aux);
                printf("%d", ex = existe_bst(a, aux));
                printf("\n");
                break;
            case 14:
                scanf("%d", &aux);
                descendente_bst(aux, a);
                printf("\n");
                break;
            case 15:
                printf("%d", alt = altura_bst(a));
                printf("\n");
                break;
            case 99:
                exit(0);
        }
    }
}
