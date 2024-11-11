/*******************************************************************************
 *  Trabalho de Estrutura de Dados I
 *  Periodo: 2024.2
 *  Alunos:
 *      - Bruno Costa Barreto (202310309411)
 *      - Otávio Pessanha Costa (202310310611)
 *      - João Pedro Meirelles Silva (202410302211)
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

#if !defined(ERROR_ALLOC_LIST_VALUE) && !defined(ERROR_ALLOC_LIST_TYPE)
#define ERROR_ALLOC_LIST_TYPE ((void*)1)
#define ERROR_ALLOC_LIST_VALUE 255
#endif

#ifndef LIMPAR_TELA
#ifdef _WIN32
#define LIMPAR_TELA_FUNC do { system("cls"); } while (0)
#else
#define LIMPAR_TELA_FUNC do { system("clear"); } while (0)
#endif
#endif

typedef struct data_s {
    unsigned char dia;
    unsigned char mes;
    unsigned long ano;
} data_t;

typedef struct telefonica_s {
    data_t data;
    char* nome;
    char* telefone;
    char* email;
} telefonica_t;

typedef struct elemento_lista_s {
    telefonica_t item;
    /*  Usamos struct elemento_lista_s pois o tipo elemento_lista_t não está
        totalmente definido nesse momento no código */
    struct elemento_lista_s *proximo;
    struct elemento_lista_s *anterior;
} elemento_lista_t;

typedef struct lista_s {
    elemento_lista_t* inicio;
    elemento_lista_t* final;
    unsigned long tamanho;
} lista_t;

void init(void);
lista_t* criar_lista(void);
void menu_principal(void);
void print_input_box(unsigned long comprimento);
int main(void);

void init(void) {
    srand((unsigned) time(NULL));
}

lista_t* criar_lista(void) {
    lista_t* lista = (lista_t*)calloc(1, sizeof(lista_t));
    if (!lista) {
        fprintf(stderr, "Falha ao alocar espaço para lista\n");
        return ERROR_ALLOC_LIST_TYPE;
    }

    lista->inicio = NULL;
    lista->final = NULL;
    lista->tamanho = 0;
    return lista;
}

void print_input_box(unsigned long comprimento) {
    unsigned long i;

    // Top border
    printf("█");
    for (i = 0; i < comprimento - 2; i++) printf("▀");
    printf("█\n");

    printf("█ >");
    for (i = 0; i < comprimento - 4; i++) printf(" ");
    printf("█\n");

    // Bottom border
    printf("█");
    for (i = 0; i < comprimento - 2; i++) printf("▄");
    printf("█\n");

#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    
    if (hConsole != INVALID_HANDLE_VALUE && GetConsoleMode(hConsole, &dwMode)) {
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hConsole, dwMode);
    }

    COORD coord = {4, 2};
    SetConsoleCursorPosition(hConsole, coord);
#else
    printf("\033[A\033[A\033[C\033[C\033[C\033[C");
#endif
}

void menu_principal(void) {
    unsigned char escolha_geral = 0;
    unsigned char escolha_adicionar = 0;
    do {
        LIMPAR_TELA_FUNC;

        switch (escolha_geral) {
            case 1:
                do {
                    switch (escolha_adicionar) {
                        case 0:
                            break;
                        default:
                            printf("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
                            printf("█                                OPÇÃO INVÁLIDA                                █\n");
                            printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n");
                            break;
                    }

                    printf("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
                    printf("█                         PROGRAMA DE LISTA TELEFÔNICA                         █\n");
                    printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n");
                    printf("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
                    printf("█                              SUB-MENU ADICIONAR                              █\n");
                    printf("█──────────────────────────────────────────────────────────────────────────────█\n");
                    printf("█                                                                              █\n");
                    printf("█ [2] - ADICIONAR AO INICIO                                                    █\n");
                    printf("█ [3] - ADICIONAR AO FINAL                                                     █\n");
                    printf("█ [4] - ADICIONAR EM POSIÇÃO                                                   █\n");
                    printf("█ [0] - VOLTAR                                                                 █\n");
                    printf("█                                                                              █\n");
                    printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n");
                    print_input_box(80);
                    scanf("%hhu", &escolha_adicionar);
                    printf("\n");
                }while (escolha_adicionar != 0);
                break;
            case 0:
                break;
            default:
                printf("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
                printf("█                                OPÇÃO INVÁLIDA                                █\n");
                printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n");
        }

        printf("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
        printf("█                         PROGRAMA DE LISTA TELEFÔNICA                         █\n");
        printf("█──────────────────────────────────────────────────────────────────────────────█\n");
        printf("█                                                                              █\n");
        printf("█ Escrito por                                                                  █\n");
        printf("█ ├─ Bruno Costa Barreto (202310309411)                                        █\n");
        printf("█ ├─ João Pedro Meirelles Silva (202410302211)                                 █\n");
        printf("█ └─ Otávio Pessanha Costa (202310310611)                                      █\n");
        printf("█                                                                              █\n");
        printf("█ Banca                                                                        █\n");
        printf("█ ├─ Disciplina de Estrutura de Dados I                                        █\n");
        printf("█ └─ Professor Maximiano Martins                                               █\n");
        printf("█                                                                              █\n");
        printf("█ Informações                                                                  █\n");
        printf("█ ├─ Linguagem C                                                               █\n");
        printf("█ └─ Padrão ANSI C89 (ANSI X3.159-1989)                                        █\n");
        printf("█                                                                              █\n");
        printf("█──────────────────────────────────────────────────────────────────────────────█\n");
        printf("█                                                                              █\n");
        printf("█ [1] - CRIAR LISTA                                                            █\n");
        printf("█ [2] - ADICIONAR                                                              █\n");
        printf("█ [3] - REMOVER                                                                █\n");
        printf("█ [4] - EXIBIR LISTA                                                           █\n");
        printf("█ [5] - CONFIGURAR EXIBIÇÃO                                                    █\n");
        printf("█ [9] - AJUDA                                                                  █\n");
        printf("█ [0] - SAIR                                                                   █\n");
        printf("█                                                                              █\n");
        printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n");
        print_input_box(80);

        scanf("%hhu", &escolha_geral);
        printf("\n");
    } while (escolha_geral != 0);
}

int main(void) {
    lista_t* lista;
    init();

    lista = criar_lista();
    if (lista == ERROR_ALLOC_LIST_TYPE) {
        printf("ERROR %ud\n", ERROR_ALLOC_LIST_VALUE);
        free(lista);
        exit(ERROR_ALLOC_LIST_VALUE);
    }

    menu_principal();
    free(lista);
    return EXIT_SUCCESS;
}
