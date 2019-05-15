#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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
char ** processar (char * resposta) {
    char **processado;
    int i, j= 0, x = 0, parenteses = 0;
    processado = malloc (255 * sizeof(char *));
    processado[0] = malloc(255*sizeof(char));
    //printf ("asjdg");
    for (i = 0; i < strlen(resposta); i++) {
        if (resposta[i] != ' ' || parenteses == 1) {
             processado[j][x++] = resposta[i];
        } else if (x != 0){
            processado[j][x] = '\0';
            x = 0;
            j++;
            processado[j] = malloc(255*sizeof(char));
        }
        if (resposta[i] == '(') {
            parenteses = 1;
        } else if (resposta[i] == ')') {
            parenteses = 0;
        }
        
    }
    return processado;
}
char** splitByChars (char *resposta, char *chars) {
    char **processado;
    int i, j= 0, x = 0, flag = 0, z;
    processado = malloc (255 * sizeof(char *));
    processado[0] = malloc(255*sizeof(char));
    //printf ("asjdg");
    for (i = 0; i < strlen(resposta); i++) {
        for (z = 0; z < strlen (chars); z++) {
            //printf ("%c %c", chars[z], resposta[i]);
            if (resposta[i] == chars[z]) flag = 1;
        }
        if (!flag) processado[j][x++] = resposta[i];
        else if (flag == 1 && x != 0){
            processado[j][x] = '\0';
            x = 0;
            j++;
            processado[j] = malloc(255*sizeof(char));
        }
        flag = 0;
    }
    return processado;
}

int verificaInteiro (char *numero) {
    int i;
    for (i = 0; i < strlen(numero); i++) {
        if (numero[i] < 48 || numero[i] > 57) return 0;
    }
    return 1;
}
int verificaBoolean (char *b) {
    if (!strcmp(b, "TRUE") || !strcmp(b, "FALSE")) return 1;
    return 0;
}
int verificaVarchar (char *v) {
    if (v[0] == '"' && v[strlen(v) - 1] == '"') return 1;
    return 0;
}
int verificaChar (char *v) {
    if (v[0] == '\'' && v[strlen(v) - 1] == '\'') return 1;
    return 0;
}