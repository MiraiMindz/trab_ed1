//Otávio Pessanha Costa 202310310611
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct ElementoLista{
    //nome, telefone, data de nascimento, email
    char nome[50], telefone[10], dataDia[2], dataMes[2], dataAno[4], email[30];
    struct ElementoLista *proximo;//endereço do próximo elemento da lista
    struct ElementoLista *anterior;//endereço do elemento anterior da lista
}ElementoLista;

typedef struct Lista{
    struct ElementoFila *inicio;//endereço do primeiro elemento da lista
    struct ElementoFila *fim;//enedereço do ultimo elemento da lista
}Lista;

Lista* criarLista(){
    Lista *l = (Lista*)malloc(sizeof(Lista));//aloca em f o tamanho correto da lista
    if(l == NULL){//malloc retorna NULL quando ocorre falha na alocação
        exit(1);//encerra o programa com código 1(que geralmente indica erro)
    }else{
        //inicializar uma lista vazia
        l->inicio = NULL;
        l->fim = NULL;
        printf("\nLista inicializada!\n");
    }
    return l;
}

int listaVazia(Lista *l){
    if(l == NULL || l -> inicio == NULL){
        printf("Lista Vazia!");
        return 1;//lista vazia ou não inicializada
    }else{
        return 0;
    }
}


int main(){
    Lista *l = criarLista();
    listaVazia(l);

    return 0;
}