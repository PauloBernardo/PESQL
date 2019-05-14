#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "structModel.h"
#include "operacoes.h"
#include "operacoesListaCaracter.h"
#include "operacoesListaVarchar.h"
DataBase db;
int getType (char *tipo) {
    if (strcmp(tipo, "INTEGER") == 0)
        return 1;
    if (strcmp(tipo, "BOOLEAN") == 0)
        return 2;
    if (strncmp(tipo, "VARCHAR", 7) == 0)
        return 3;
    if (strcmp(tipo, "CHAR") == 0)
        return 4;
    return 0;
}
int getSize (char **processado, int tam) {
    char *aux;
    aux = malloc (255 * sizeof(char));
    int i, j = 0, x= 0, flag = 0;
    for (i=6; i < tam; i++) {
        for (j == 0; j < strlen (processado[i]); j++) {
            if (processado[i][j] == '[') {
                flag = 1;
            } else if ( flag == 1) {
                aux[x++] = processado[i][j];
            } else if (processado[i] [j] == ']') {
                aux[x] = '\0';
                return atoi(aux);
            }
        }
    }
}
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
                return raiz;
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
    else if (tam == 4) {
        /*
         printf("HJGHJFHJ\n");
         printf("%s\n", processado[0]);
         printf("%s\n", processado[1]);
         printf("%s\n", processado[2]);
         */
         if (strcmp(processado[0], "SHOW") == 0 && strcmp (processado[1], "COLLUMNS") == 0 && strcmp(processado[2], "FROM") == 0) {
             //printf("HJGHJFHJ");
             if (db == NULL) {
                printf ("Erro, banco de dados não selecionado.\n");
                return raiz;
             }
             Table selectedTable = buscaTable (db->tables, processado[3]);
             if (selectedTable == NULL) {
                 printf ("Erro, table não existe.\n");
                 return raiz;
             }
             printCollumns (selectedTable->columns);
         }
    }
    else if (tam == 2) {
         if (strcmp(processado[0], "USE") == 0) {
             db = buscaDataBase(raiz, processado[1]);
             if (db == NULL) {
                 printf ("Erro, database não existe\n");
                 return raiz;
             }
         }
          if (strcmp(processado[0], "SHOW") == 0 && strcmp (processado[1], "DATABASES") == 0) {
              printDataBases(raiz);
          }
          if (strcmp(processado[0], "SHOW") == 0 && strcmp (processado[1],"TABLES") == 0) {
              if (db == NULL){
                  printf ("Database não selecionado.\n");
                  return raiz;
              }
              printTables (db->tables);
          }
          if (strcmp(processado[0], "DESCRIBE") == 0) {
            if (db == NULL) {
                printf ("Erro, banco de dados não selecionado.\n");
                return raiz;
             }
             Table selectedTable = buscaTable (db->tables, processado[1]);
             if (selectedTable == NULL) {
                 printf ("Erro, table não existe.\n");
                 return raiz;
             }
             printf ("| NOME | TIPO |\n");
             printCollumnsCompleto(selectedTable->columns);
          }
    } else if (tam == 6){
        if (strcmp(processado[0], "ALTER") == 0 && strcmp(processado[1], "TABLE") == 0 && strcmp (processado[3], "DROP") == 0 && strcmp(processado[4], "COLLUMN") == 0) {
            if (db == NULL) {
                printf ("Erro, banco de dados não selecionado.\n");
                return raiz;
             }
             Table selectedTable = buscaTable (db->tables, processado[2]);
             if (selectedTable == NULL) {
                 printf ("Erro, table não existe.\n");
                 return raiz;
             }
             selectedTable->columns = removeCollumn(selectedTable->columns, processado[5]);
        }
    } else if (tam >= 7) {
        if (strcmp(processado[0], "ALTER") == 0 && strcmp(processado[1], "TABLE") == 0 && strcmp (processado[3], "ADD") == 0 && strcmp(processado[4], "COLLUMN") == 0) {
             if (db == NULL) {
                printf ("Erro, banco de dados não selecionado.\n");
                return raiz;
             }
             Table selectedTable = buscaTable (db->tables, processado[2]);
             if (selectedTable == NULL) {
                 printf ("Erro, table não existe.\n");
                 return raiz;
             }
             if (selectedTable->columns == NULL) {
                Collumn inicial;
                inicial = malloc (sizeof(struct collumn));
                inicial->name = malloc (255 * sizeof(char));
                //printf("%s\n", processado[2]);
                strcpy (inicial->name, "NNNNNNNNNNNNNNNNNN");
                selectedTable->columns = inicial;
             }
            Collumn novo;
            novo = malloc (sizeof(struct collumn));
            novo->name = malloc (255 * sizeof(char));
            novo->tipo = malloc (20 * sizeof(char));
            strcpy (novo->name, processado[5]);
            switch (getType(processado[6]))
            {
            case 1:
                strcpy (novo->tipo,"INTEGER");
                Integer init;
                init = malloc(sizeof (struct integer));
                init->id = 0;
                init->valor = 0;
                novo->integers =  init;
                break;
            case 2:
                strcpy(novo->tipo,"BOOLEAN");
                Booleano init1;
                init1 = malloc(sizeof (struct boolean));
                init1->id = 0;
                init1->valor = false;
                novo->booleans =  init1;
                break;
            case 3:
                strcpy (novo->tipo,"VARCHAR");
                int size = getSize (processado, tam);
                Varchar inicio;
                inicio = malloc(sizeof (struct varchar));
                inicio->id = 0;
                inicio->size = size;
                inicio->valor = malloc((inicio->size +1) *sizeof(char));
                strcmp (inicio->valor , " ");
                novo->varchars =  inicio;
                break;
            case 4:
                strcpy (novo->tipo,"CHAR");
                Char init2;
                init2 = malloc(sizeof (struct caracter));
                init2->id = 0;
                init2->valor = 0;
                novo->chars =  init2;
                break;
            default:
                printf ("Erro, tipo da coluna não suportado.\n");
                break;
            }
            selectedTable->columns = addCollumn (selectedTable->columns, novo);
         }
    } 
    else if (tam > 3) {
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