#include <stdio.h>
#include <stdbool.h>
#include <string.h>
int getType (char *tipo) {
    if (tipo == NULL) return 0;
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

char ** processar (char * resposta) {
    char **processado;
    int i, j= 0, x = 0;
    processado = malloc (255 * sizeof(char *));
    processado[0] = malloc(255*sizeof(char));
    //printf ("asjdg");
    for (i = 0; i < strlen(resposta); i++) {
        if (resposta[i] != ' ') {
             processado[j][x++] = resposta[i];
        } else if (x != 0){
            processado[j][x] = '\0';
            x = 0;
            j++;
            processado[j] = malloc(255*sizeof(char));
        }
        if (resposta[i] == '(') {
            i++;
            while (i < strlen(resposta)) {
                if (resposta[i] != ')') {
                    processado[j][x++] = resposta[i];
                    i++;
                }else {
                    processado[j][x++] = resposta[i];
                    break;
                }
            }
        }
        if (resposta[i] == '"') {
            i++;
            while (i < strlen(resposta)) {
                if (resposta[i] != '"') {
                    processado[j][x++] = resposta[i];
                    i++;
                } else {
                    processado[j][x++] = resposta[i];
                    break;
                }
            }
        }
    }
    return processado;
}
char** splitByChars (char *resposta, char *chars) {
    char **processado;
    int i, j= 0, x = 0, flag = 0, z, aspas = 1;
    processado = malloc (255 * sizeof(char *));
    processado[0] = malloc(255*sizeof(char));
    //printf ("asjdg");
    for (i = 0; i < strlen(resposta); i++) {
        for (z = 0; z < strlen (chars); z++) {
           // printf ("%c %c", chars[z], resposta[i]);
            if (resposta[i] == chars[z] && aspas) flag = 1;
        }
        if (resposta[i] == '"') {
            if (aspas) aspas = 0;
            else aspas = 1;
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
char** splitByCharsButNoRemove (char *resposta, char *chars) {
    char **processado;
    int i, j= 0, x = 0, flag = 0, z, aspas = 1;
    processado = malloc (255 * sizeof(char *));
    processado[0] = malloc(255*sizeof(char));
    //printf ("asjdg");
    for (i = 0; i < strlen(resposta); i++) {
        for (z = 0; z < strlen (chars); z++) {
            //printf ("%c %c", chars[z], resposta[i]);
            if (resposta[i] == chars[z] && aspas) flag = 1;
        }
        if (resposta[i] == '"') {
            if (aspas) aspas = 0;
            else aspas = 1;
        }
        if (!flag) processado[j][x++] = resposta[i];
        else if (flag == 1 && x != 0){
            processado[j][x] = '\0';
            x = 0;
            j++;
            processado[j] = malloc(255*sizeof(char));
            processado[j][0] = resposta[i];
            processado[j][1] = '\0';
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
int getSize (char *processado) {
   // printf("oxsnkjdvh");
    char **aux;
    aux = splitByChars (processado, "[]");
    return atoi(aux[0]);
}