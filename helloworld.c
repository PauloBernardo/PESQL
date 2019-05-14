#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "structModel.h"
#include "operacoes.h"
#include "operacoesListaCaracter.h"
#include "operacoesListaVarchar.h"
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
    collumn2 = malloc (sizeof(struct collumn));
    collumn2->name = malloc (100 * sizeof(char));
    collumn2->tipo = malloc (20* sizeof(char));
    strcpy(collumn2->name, "Sexo");
    strcpy(collumn2->tipo, "Char");
     //printf("Adicionando char\n");
    Char c;
    c = malloc(sizeof(struct caracter));
    c->valor = 0;
    c->id = 0;
    collumn2->chars = c;
   // printf("Adicionando char\n");
    insereChar(collumn2->chars, 'M');
    insereChar(collumn2->chars, 'Z');
    insereChar (collumn2->chars, 'A');
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
      // printf("Adicionando collumn\n");
    aluno->columns = addCollumn (aluno->columns, collumn2);
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
    printf("teste");
    DataBase aux = buscaDataBase(escola, "AAA");
    printf("%s\n", aux->tables->name);
    //printf("teste");
    escola = removeDatabase(escola, "Abelha");
    //printf("teste");
    Collumn collumn3;
    collumn3 = malloc (sizeof(struct collumn));
    collumn3->name = malloc (100 * sizeof(char));
    collumn3->tipo = malloc (20* sizeof(char));
    strcpy(collumn3->name, "Nome");
    strcpy(collumn3->tipo, "Varchar");
    Varchar string;
    string = malloc(sizeof(struct varchar));
    string->id = 0;
    string->size = 20;
    string->valor = malloc(20 * sizeof(char));
    char name[] = "Bijhsajkhfdjkashkjfdhajks";
    name[20] = '\0';
    strcpy (string->valor, name);
    collumn3->varchars = string;
    //printf("%s\n", collumn3->varchars->valor);
    insereVarchar(collumn3->varchars, "WHATFOCA");
    insereVarchar(collumn3->varchars, "HAHAHAHA PARACE QUE VAI DAR CERTO");
    insereVarchar(collumn3->varchars, "Congratulationd");
    aluno->columns = addCollumn(aluno->columns, collumn3);
    //printf("teste");
    if (buscaCollumn(aluno->columns, "Nome") != NULL) {
        printf ("%d\n", buscaVarcharByValor("WHATFOCA", buscaCollumn(aluno->columns, "Nome")->varchars)->id);
    }
    if (aluno->columns->direita != NULL) {
        printf ("%c\n", buscaCharById(3, aluno->columns->direita->chars)->valor);
    }
    printf("Esquerda: %s\n", escola->esquerda->name);
    printf("Direita: %s\n", escola->direita->name);
    printf("%s\n", escola->name);
    printf("%s\n", escola->tables->name);
    printf("%s\n", escola->tables->columns->name);
    printf("%s\n", escola->tables->columns->tipo);
    printf("%d\n", escola->tables->columns->integers->valor);
    return 0;
}