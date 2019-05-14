#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "structModel.h"
#include "operacoes.h"
#include "operacoesListaCaracter.h"
#include "operacoesListaVarchar.h"
DataBase db;
DataBase decoder (DataBase raiz, char **processado, int tam){
    int i = 0, j = 0;
    if (tam == 3) {
        if (strcmp(processado[0], "CREATE") == 0 && strcmp(processado[1], "DATABASE") == 0) {
            DataBase novo;
            novo = malloc (sizeof(struct database));
            novo->name = malloc (255 * sizeof(char));
            //printf("%s\n", processado[2]);
            strcpy (novo->name, processado[2]);
            //printf("%s\n", novo->name);
            return addDataBase(raiz, novo);
        }
        if (strcmp(processado[0], "DROP") == 0 && strcmp(processado[1], "DATABASE") == 0) {
            return removeDatabase(raiz, processado[2]);
        }
        if (strcmp(processado[0], "CREATE") == 0 && strcmp(processado[1], "TABLE") == 0) {
            if (db == NULL) {
                printf ("Erro, banco de dados não selecionado.\n");
            }
            Table novo;
            novo = malloc (sizeof(struct table));
            novo->name = malloc (255 * sizeof(char));
            //printf("%s\n", processado[2]);
            strcpy (novo->name, processado[2]);
            //printf("%s\n", novo->name);
            if (db->tables == NULL) {
                Table raiz;
                raiz = malloc (sizeof(struct table));
                raiz->name = malloc (255 * sizeof(char));
                //printf("%s\n", processado[2]);
                strcpy (raiz->name, "NNNNNNNNNNNNNNNNNN");
                db->tables = raiz;
            }
            db->tables = addTable(db->tables, novo);
        }
    }
    else if (tam == 2) {
         if (strcmp(processado[0], "USE") == 0) {
             db = buscaDataBase(raiz, processado[1]);
             if (db == NULL) {
                 printf ("Erro, database não existe\n");
             }
         }
          if (strcmp(processado[0], "SHOW") == 0 && strcmp (processado[1], "DATABASES") == 0) {
              printDataBases(raiz);
          }
          if (strcmp(processado[0], "SHOW") == 0 && strcmp (processado[1],"TABLES") == 0) {
              if (db == NULL){
                  printf ("Database não selecionado.\n");
              }
              printTables (db->tables);
          }
    } else if (tam > 3) {
        if (strcmp(processado[0], "CREATE") == 0 && strcmp(processado[1], "TABLE") == 0) {
            Table novo;
            novo = malloc (sizeof(struct table));
            novo->name = malloc (255 * sizeof(char));
            //printf("%s\n", processado[2]);
            strcpy (novo->name, processado[2]);
            //printf("%s\n", novo->name);
            if (db->tables == NULL) {
                Table raiz;
                raiz = malloc (sizeof(struct table));
                raiz->name = malloc (255 * sizeof(char));
                //printf("%s\n", processado[2]);
                strcpy (raiz->name, "NNNNNNNNNNNNNNNNNN");
                db->tables = raiz;
            }
            db->tables = addTable(db->tables, novo);
        }
    }
    return raiz;
} 
char ** processar (char * resposta) {
    char **processado;
    int i, j= 0, x = 0;
    processado = malloc (255 * sizeof(char *));
    processado[0] = malloc(255*sizeof(char));
    for (i = 0; i < strlen(resposta); i++) {
        if (resposta[i] != ' ')
            processado[j][x++] = resposta[i];
        else if (x != 0){
            processado[j][x] = '\0';
            x = 0;
            j++;
            processado[j] = malloc(255*sizeof(char));
        }
    }
    return processado;
}
int main () {
    printf("################################\n");
    printf("              PESQL             \n");
    printf("################################\n");
    char resposta [256], respostaLongas[10000];
    char **processado;
    DataBase raiz;
    raiz = malloc(sizeof(struct database));
    raiz->name = malloc (255* sizeof(char));
    strcpy (raiz->name, "NNNNNNNNNNNNNNNNNN");
    int tam = 0;
    while (true) {
        while (true) {
            scanf ("%[^\n]s", resposta);
            getchar();
            if (strcmp(resposta, "EXIT") == 0) {
                printf ("BYE\n");
                return 0;
            }
            if (strlen(resposta) != 0){
                if (resposta[strlen(resposta)-1] != ';') {
                    strcat (respostaLongas, resposta);
                    strcat (respostaLongas, " ");
                } else {
                    resposta[strlen(resposta)-1] = '\0';
                    strcat(respostaLongas, resposta);
                    break;
                }
            }
        }
        processado = processar(respostaLongas);
        for (int i = 0; i < 255 && processado[i] != NULL; i++) {
           // printf ("%s\n", processado[i]);
            tam++;
        }
        raiz = decoder(raiz, processado, tam);
        tam = 0;
        respostaLongas[0] ='\0';
    }
    
    return 0;
}