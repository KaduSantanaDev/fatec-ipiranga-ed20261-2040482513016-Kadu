#include <stdio.h>
#include <stdlib.h>
#include "minhabib.h"

#define ESPACO_VISUAL 5

No* criar_no(int valor) {
    No* novo = (No*) malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro: memoria insuficiente para criar o no %d.\n", valor);
        exit(1);
    }

    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

No* inserir(No* raiz, int valor) {
    if (raiz == NULL) {
        return criar_no(valor);
    }

    if (valor < raiz->valor) {
        raiz->esq = inserir(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = inserir(raiz->dir, valor);
    } else {
        printf("Valor %d ignorado: a BST deste exemplo nao aceita repetidos.\n", valor);
    }

    return raiz;
}

No* buscar_no(No* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) {
        return raiz;
    }

    if (valor < raiz->valor) {
        return buscar_no(raiz->esq, valor);
    }

    return buscar_no(raiz->dir, valor);
}

int calcular_grau(No* no) {
    if (no == NULL) {
        return -1;
    }

    int grau = 0;

    if (no->esq != NULL) {
        grau++;
    }

    if (no->dir != NULL) {
        grau++;
    }

    return grau;
}

void imprimir_nos_internos(No* raiz) {
    if (raiz == NULL) {
        return;
    }

    if (raiz->esq != NULL || raiz->dir != NULL) {
        printf("%d ", raiz->valor);
    }

    imprimir_nos_internos(raiz->esq);
    imprimir_nos_internos(raiz->dir);
}

void imprimir_folhas(No* raiz) {
    if (raiz == NULL) {
        return;
    }

    if (raiz->esq == NULL && raiz->dir == NULL) {
        printf("%d ", raiz->valor);
    }

    imprimir_folhas(raiz->esq);
    imprimir_folhas(raiz->dir);
}

void imprimir_niveis(No* raiz, int nivel_atual) {
    if (raiz == NULL) {
        return;
    }

    printf("No %d | Nivel %d | Endereco: %p\n", raiz->valor, nivel_atual, (void*) raiz);

    imprimir_niveis(raiz->esq, nivel_atual + 1);
    imprimir_niveis(raiz->dir, nivel_atual + 1);
}

int calcular_altura(No* no) {
    if (no == NULL) {
        return -1;
    }

    int altura_esq = calcular_altura(no->esq);
    int altura_dir = calcular_altura(no->dir);

    if (altura_esq > altura_dir) {
        return altura_esq + 1;
    }

    return altura_dir + 1;
}

int calcular_profundidade(No* raiz, int valor, int profundidade_atual) {
    if (raiz == NULL) {
        return -1;
    }

    if (raiz->valor == valor) {
        return profundidade_atual;
    }

    if (valor < raiz->valor) {
        return calcular_profundidade(raiz->esq, valor, profundidade_atual + 1);
    }

    return calcular_profundidade(raiz->dir, valor, profundidade_atual + 1);
}

int imprimir_ancestrais_rec(No* raiz, int valor) {
    if (raiz == NULL) {
        return 0;
    }

    if (raiz->valor == valor) {
        return 1;
    }

    if (imprimir_ancestrais_rec(raiz->esq, valor) || imprimir_ancestrais_rec(raiz->dir, valor)) {
        printf("%d ", raiz->valor);
        return 1;
    }

    return 0;
}

void imprimir_ancestrais(No* raiz, int valor) {
    if (!imprimir_ancestrais_rec(raiz, valor)) {
        printf("Valor nao encontrado");
    }
}

void imprimir_descendentes(No* no) {
    if (no == NULL) {
        return;
    }

    if (no->esq != NULL) {
        printf("%d ", no->esq->valor);
        imprimir_descendentes(no->esq);
    }

    if (no->dir != NULL) {
        printf("%d ", no->dir->valor);
        imprimir_descendentes(no->dir);
    }
}

void imprimir_arvore_visual(No* raiz, int espaco) {
    if (raiz == NULL) {
        return;
    }

    espaco += ESPACO_VISUAL;

    imprimir_arvore_visual(raiz->dir, espaco);

    printf("\n");
    for (int i = ESPACO_VISUAL; i < espaco; i++) {
        printf(" ");
    }
    printf("%d\n", raiz->valor);

    imprimir_arvore_visual(raiz->esq, espaco);
}

void analisar_arvore(No* raiz, int valorBusca) {
    if (raiz == NULL) {
        printf("A arvore esta vazia.\n");
        return;
    }

    printf("==============================\n");
    printf(" DIAGNOSTICO GERAL DA ARVORE\n");
    printf("==============================\n");

    printf("Raiz: %d\n", raiz->valor);

    printf("Nos internos: ");
    imprimir_nos_internos(raiz);
    printf("\n");

    printf("Nos externos / folhas: ");
    imprimir_folhas(raiz);
    printf("\n");

    printf("Altura total da arvore: %d\n", calcular_altura(raiz));

    printf("\nExibicao por niveis:\n");
    imprimir_niveis(raiz, 0);

    printf("\nVisualizacao da arvore completa:\n");
    imprimir_arvore_visual(raiz, 0);

    printf("\n==============================\n");
    printf(" DIAGNOSTICO DO VALOR %d\n", valorBusca);
    printf("==============================\n");

    No* encontrado = buscar_no(raiz, valorBusca);

    if (encontrado == NULL) {
        printf("Valor %d nao encontrado na arvore.\n", valorBusca);
        return;
    }

    printf("No encontrado: %d\n", encontrado->valor);
    printf("Endereco de memoria: %p\n", (void*) encontrado);
    printf("Grau do no: %d\n", calcular_grau(encontrado));

    printf("Ancestrais ate a raiz: ");
    imprimir_ancestrais(raiz, valorBusca);
    printf("\n");

    printf("Descendentes: ");
    imprimir_descendentes(encontrado);
    printf("\n");

    printf("Altura do no: %d\n", calcular_altura(encontrado));
    printf("Profundidade do no: %d\n", calcular_profundidade(raiz, valorBusca, 0));

    printf("\nSub-arvore isolada com raiz em %d:\n", valorBusca);
    imprimir_arvore_visual(encontrado, 0);
}

void liberar_arvore(No* raiz) {
    if (raiz == NULL) {
        return;
    }

    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);
    free(raiz);
}
