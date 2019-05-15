#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "structModel.h"
#include "operacoes.h"
#include "operacoesListaCaracter.h"
#include "operacoesListaVarchar.h"
#include "utils.h"
#include "comandosSQL.h"

DataBase db;
DataBase decoder (DataBase raiz, char **processado, int tam){
    int i = 0, j = 0;
    if (tam == 3) {
        if (strcmp(processado[0], "CREATE") == 0 && strcmp(processado[1], "DATABASE") == 0) {
            return createDataBaseSQL(raiz, processado, tam);
        }
        if (strcmp(processado[0], "DROP") == 0 && strcmp(processado[1], "DATABASE") == 0) {
            return removeDatabase(raiz, processado[2]);
        }
        if (strcmp(processado[0], "CREATE") == 0 && strcmp(processado[1], "TABLE") == 0) {
            db = createTableSQL(db, processado);
        }
    }
    else if (tam == 4) {
         if (strcmp(processado[0], "SHOW") == 0 && strcmp (processado[1], "COLLUMNS") == 0 && strcmp(processado[2], "FROM") == 0) {
             showCollumnsSQL (db, processado[3]);
         }
    }
    else if (tam == 2) {
         if (strcmp(processado[0], "USE") == 0) {
             db = useDataBaseSQL(raiz, processado[1]);
         }
          if (strcmp(processado[0], "SHOW") == 0 && strcmp (processado[1], "DATABASES") == 0) {
              printDataBases(raiz);
          }
          if (strcmp(processado[0], "SHOW") == 0 && strcmp (processado[1],"TABLES") == 0) {
              showTablesSQL (db);
          }
          if (strcmp(processado[0], "DESCRIBE") == 0) {
              describeSQL (db, processado[1]);
          }
    } else if (tam == 6){
        if (strcmp(processado[0], "ALTER") == 0 && strcmp(processado[1], "TABLE") == 0 && strcmp (processado[3], "DROP") == 0 && strcmp(processado[4], "COLLUMN") == 0) {
            db = alterTableDropSQL (db,processado[2], processado[5]);
        }
        if (strcmp(processado[0], "INSERT") == 0 && strcmp(processado[1], "INTO") == 0 && strcmp (processado[4], "VALUES") == 0) {
            db = insertIntoValuesSQL (db, processado[2], processado[3], processado[5]);
        }
    } else if (tam >= 7) {
        if (strcmp(processado[0], "ALTER") == 0 && strcmp(processado[1], "TABLE") == 0 && strcmp (processado[3], "ADD") == 0 && strcmp(processado[4], "COLLUMN") == 0) {
             db = alterTableAddSQL (db, processado, tam);
         }
         if (strcmp(processado[0], "ALTER") == 0 && strcmp(processado[1], "TABLE") == 0 && strcmp (processado[3], "MODIFY") == 0 && strcmp(processado[4], "COLLUMN") == 0) {
             db = alterTableModifySQL (db, processado, tam);
         }
    } 
    return raiz;
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