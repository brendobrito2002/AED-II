#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(int argc, char * argv[]) {
	arvore a;
	int opcao, controleFB, valor, diminuiu;
    inicializar_avl(&a);

	while(1) {
		scanf("%d", &opcao);

		switch(opcao) {
                case 1:
                    scanf("%d", &valor);
                    a = inserir_avl(valor, a, &controleFB);
                    break;
                case 2:
                    pre_order_avl(a);
                    printf("\n");
                    break;
                case 3:
                    scanf("%d", &valor);
                    remover_avl(valor, a, &diminuiu);
                    break;
				case 99:
					exit(0);
		}
	}
}