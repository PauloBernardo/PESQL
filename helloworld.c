#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "structModel.h"
#include "operacoes.h"
#include "operacoesListaCaracter.h"
int main () {
    DataBase escola, novo;
    novo = malloc(sizeof(struct database));
    novo->name = malloc(100*sizeof(char));
    DataBase novo2;
    novo2 = malloc(sizeof(struct database));
    novo2->name = malloc(100*sizeof(char));
    strcpy(novo->name, "SÃO FRANCISCO");
    strcpy(novo2->name, "Abelha");
    DataBase novo3;
    novo3 = malloc(sizeof(struct database));
    novo3->name = malloc(100*sizeof(char));
    strcpy(novo3->name, "AAA");
    Table aluno;
    Collumn collumn1, collumn2;
    collumn1 = malloc (sizeof(struct collumn));
    aluno = malloc (sizeof(struct table));
    escola = malloc (sizeof(struct database));
    escola->name = malloc (100 * sizeof(char));
    aluno->name = malloc (100 * sizeof(char));
    collumn1->name = malloc (100 * sizeof(char));
    collumn1->tipo = malloc (100 * sizeof(char));
    escola->tables = aluno;
    aluno->columns = collumn1;
    strcpy(aluno->name, "ALuno");
    strcpy(collumn1->name, "Idade");
    strcpy(collumn1->tipo, "Integer");
    Integer inteiro;
    inteiro = malloc(sizeof(int));
    inteiro->proximo = NULL;
    inteiro->id = 0;
    inteiro->valor = 0;
    insereInteger(inteiro, 10);
    insereInteger(inteiro, 20);
    insereInteger(inteiro, 3);
    printList(inteiro);
    removeIntegerById (inteiro, 1);
    printList(inteiro);
    Integer teste = buscaIntegerById(1, inteiro);
    if (teste == NULL) printf("OK\n");
    printf("%d\n", buscaIntegerById(3, inteiro)->valor);
    printf("%d\n", buscaIntegerByValor(20, inteiro)->id);
    collumn1->integers = inteiro;
    strcpy (escola->name, "ICARO");
    escola = addDataBase(escola, novo);
    escola = addDataBase(escola, novo2);
    escola = addDataBase(escola, novo3);
    novo3->tables = aluno;
    DataBase aux = buscaDataBase(escola, "AAA");
    printf("%s\n", aux->tables->name);
    escola = removeDatabase(escola, "Abelha");
    printf("Esquerda: %s\n", escola->esquerda->name);
    printf("Direita: %s\n", escola->direita->name);
    printf("%s\n", escola->name);
    printf("%s\n", escola->tables->name);
    printf("%s\n", escola->tables->columns->name);
    printf("%s\n", escola->tables->columns->tipo);
    printf("%d\n", escola->tables->columns->integers->valor);
    return 0;
}