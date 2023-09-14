#include "rb.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[]) {
    arvore a;
    int opcao, valor;

    inicializar(&a);
    
    while(1){
        scanf("%d", &opcao);
        
        switch(opcao){
            case 1:
                scanf("%d", &valor);
                inserir(valor, &a);
                break;
            case 2:
                pre_order(a);
                printf("\n");
                break;
            case 3:
                scanf("%d", &valor);
                remover(valor, &a);
                break;
            case 99:
                exit(0);
        }
    }
}
