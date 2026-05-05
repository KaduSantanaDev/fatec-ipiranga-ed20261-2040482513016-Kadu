#include <stdio.h>
#include "minhabib.h"

int main() {
    No* raiz = NULL;

    // Valores usados para gerar uma BST com 4 niveis: 0, 1, 2 e 3.
    // Voce pode alterar estes valores para testar outras arvores.
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 35, 45};
    int quantidade = sizeof(valores) / sizeof(valores[0]);
    int valorBusca = 30;

    for (int i = 0; i < quantidade; i++) {
        raiz = inserir(raiz, valores[i]);
    }

    analisar_arvore(raiz, valorBusca);

    liberar_arvore(raiz);

    return 0;
}
