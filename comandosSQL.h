#include <stdio.h>
#include <stdbool.h>
#include <string.h>


DataBase createDataBaseSQL (DataBase raiz, char **processado, int tam) {
    DataBase novo;
    novo = malloc (sizeof(struct database));
    novo->name = malloc (255 * sizeof(char));
    //printf("%s\n", processado[2]);
    strcpy (novo->name, processado[2]);
    //printf("%s\n", novo->name);
    return addDataBase(raiz, novo);
}
DataBase createTableSQL (DataBase db, char *nomeTable) {
    if (db == NULL) {
        printf ("Erro, banco de dados não selecionado.\n");
        return db;
    }
    Table novo;
    novo = malloc (sizeof(struct table));
    novo->name = malloc (255 * sizeof(char));
    //printf("%s\n", processado[2]);
    strcpy (novo->name, nomeTable);
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
    return db;
}
void showCollumnsSQL (DataBase db, char *table) {
    if (db == NULL) {
        printf ("Erro, banco de dados não selecionado.\n");
        return;
    }
    Table selectedTable = buscaTable (db->tables, table);
    if (selectedTable == NULL) {
        printf ("Erro, table não existe.\n");
        return;
    }
    printCollumns (selectedTable->columns);
}
DataBase useDataBaseSQL (DataBase raiz, char *database) {
    DataBase db = buscaDataBase(raiz, database);
    if (db == NULL) {
        printf ("Erro, database não existe\n");
    }
    return db;
}
void showTablesSQL (DataBase db) {
    if (db == NULL){
        printf ("Database não selecionado.\n");
        return;
    }
    printTables (db->tables);
}

void describeSQL (DataBase db,char * table) {
    if (db == NULL) {
        printf ("Erro, banco de dados não selecionado.\n");
        return;
    }
    Table selectedTable = buscaTable (db->tables, table);
    if (selectedTable == NULL) {
        printf ("Erro, table não existe.\n");
        return;
    }
    printf ("| NOME | TIPO |\n");
    printCollumnsCompleto(selectedTable->columns);
}

DataBase alterTableDropSQL (DataBase db, char * table, char *collumn) {
    if (db == NULL) {
        printf ("Erro, banco de dados não selecionado.\n");
        return db;
    }
    Table selectedTable = buscaTable (db->tables, table);
    if (selectedTable == NULL) {
        printf ("Erro, table não existe.\n");
        return db;
    }
    selectedTable->columns = removeCollumn(selectedTable->columns, collumn);
    return db;
}
DataBase alterTableAddSQL (DataBase db, char **processado, int tam) {
    if (db == NULL) {
        printf ("Erro, banco de dados não selecionado.\n");
        return db;
    }
    Table selectedTable = buscaTable (db->tables, processado[2]);
    if (selectedTable == NULL) {
        printf ("Erro, table não existe.\n");
        return db;
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

    //Pegar o numero de inserções anteriores
    int numero = numeroDeColunas(selectedTable->columns);
    //printf ("%d\n", numero);
    int i, j, z, tamanhoLista = 0;
    char **todasColunas = splitByChars (getNomeColunas(selectedTable->columns), ",");
    Collumn *collumns;
    collumns = malloc (numero * sizeof(Collumn));
    for (i = 1, j= 0; i < numero && todasColunas[i] != NULL; i++, j++) {
        collumns[j] = buscaCollumn(selectedTable->columns, todasColunas[i]);
        if (collumns[j] != NULL) {
            switch (getType(collumns[j]->tipo)) {
                case 1:
                    tamanhoLista = getTamanhoListaInteger(collumns[j]->integers);
                    break;
                case 2:
                    tamanhoLista = getTamanhoListaBoolean (collumns[j]->booleans);
                    break;
                case 3:
                    tamanhoLista = getTamanhoListaVarchar (collumns[j]->varchars);
                    break;
                case 4:
                    tamanhoLista = getTamanhoListaChar (collumns[j]->chars);
                    break;
                default:
                    printf ("Erro interno, alguma coluna não possui tipo correto.\n");
                    return db;
                    break;
            }
            break;
        }
    }
    //printf ("%d\n", tamanhoLista);
    switch (getType(processado[6]))
    {
    case 1:
        strcpy (novo->tipo,"INTEGER");
        Integer init;
        init = malloc(sizeof (struct integer));
        init->id = 0;
        init->valor = 0;
        novo->integers =  init;
        for (i = 1; i < tamanhoLista; i++) {
            insereInteger (novo->integers, 0);
        }
        break;
    case 2:
        strcpy(novo->tipo,"BOOLEAN");
        Booleano init1;
        init1 = malloc(sizeof (struct boolean));
        init1->id = 0;
        init1->valor = false;
        novo->booleans =  init1;
        for (i = 1; i < tamanhoLista; i++) {
            insereBoolean (novo->booleans, false);
        }
        break;
    case 3:
        strcpy (novo->tipo,"VARCHAR");
        int size = getSize (processado[7]);
        //printf ("%d\n", size);
        Varchar inicio;
        inicio = malloc(sizeof (struct varchar));
        inicio->id = 0;
        inicio->size = size;
        inicio->valor = malloc((inicio->size +1) *sizeof(char));
        strcmp (inicio->valor , " ");
        novo->varchars =  inicio;
        for (i = 1; i < tamanhoLista; i++) {
            insereVarchar (novo->varchars, "");
        }
        break;
    case 4:
        strcpy (novo->tipo,"CHAR");
        Char init2;
        init2 = malloc(sizeof (struct caracter));
        init2->id = 0;
        init2->valor = 0;
        novo->chars =  init2;
        for (i = 1; i < tamanhoLista; i++) {
            insereChar (novo->chars, 0);
        }
        break;
    default:
        printf ("Erro, tipo da coluna não suportado.\n");
        return db;
        break;
    }
     selectedTable->columns = addCollumn (selectedTable->columns, novo);
    return db;
}

DataBase alterTableModifySQL (DataBase db, char **processado, int tam) {
    if (db == NULL) {
        printf ("Erro, banco de dados não selecionado.\n");
        return db;
    }
    Table selectedTable = buscaTable (db->tables, processado[2]);
    if (selectedTable == NULL) {
        printf ("Erro, table não existe.\n");
        return db;
    }
    if (selectedTable->columns == NULL) {
         printf ("Erro, collumn não existe.\n");
        return db;
    }
    Collumn collumn = buscaCollumn(selectedTable->columns, processado[5]);
    if (collumn == NULL) {
         printf ("Erro, collumn não existe.\n");
        return db;
    }
    int tamanhoLista = 0, i;
    switch (getType(collumn->tipo)) {
        case 1:
            tamanhoLista = getTamanhoListaInteger(collumn->integers);
            break;
        case 2:
            tamanhoLista = getTamanhoListaBoolean (collumn->booleans);
            break;
        case 3:
            tamanhoLista = getTamanhoListaVarchar (collumn->varchars);
            break;
        case 4:
            tamanhoLista = getTamanhoListaChar (collumn->chars);
            break;
         default:
            printf ("Erro interno, alguma coluna não possui tipo correto.\n");
            return db;
            break;
    }
    switch (getType(processado[6]))
    {
    case 1:
        strcpy (collumn->tipo,"INTEGER");
        Integer init;
        init = malloc(sizeof (struct integer));
        init->id = 0;
        init->valor = 0;
        collumn->integers =  init;
        for (i = 1; i < tamanhoLista; i++) {
            insereInteger (collumn->integers, 0);
        }
        break;
    case 2:
        strcpy(collumn->tipo,"BOOLEAN");
        Booleano init1;
        init1 = malloc(sizeof (struct boolean));
        init1->id = 0;
        init1->valor = false;
        collumn->booleans =  init1;
        for (i = 1; i < tamanhoLista; i++) {
            insereBoolean (collumn->booleans, false);
        }
        break;
    case 3:
        strcpy (collumn->tipo,"VARCHAR");
        int size = getSize (processado[7]);
        Varchar inicio;
        inicio = malloc(sizeof (struct varchar));
        inicio->id = 0;
        inicio->size = size;
        inicio->valor = malloc((inicio->size +1) *sizeof(char));
        strcmp (inicio->valor , " ");
        collumn->varchars =  inicio;
        for (i = 1; i < tamanhoLista; i++) {
            insereVarchar (collumn->varchars, "");
        }
        break;
    case 4:
        strcpy (collumn->tipo,"CHAR");
        Char init2;
        init2 = malloc(sizeof (struct caracter));
        init2->id = 0;
        init2->valor = 0;
        collumn->chars =  init2;
        for (i = 1; i < tamanhoLista; i++) {
            insereChar (collumn->chars, 0);
        }
        break;
    default:
        printf ("Erro, tipo da coluna não suportado.\n");
        break;
    }
    return db;
}

DataBase insertIntoValuesSQL (DataBase db, char *table, char *collumns, char *values) {
    if (db == NULL) {
        printf ("Erro, banco de dados não selecionado.\n");
        return db;
    }
    Table selectedTable = buscaTable (db->tables, table);
    if (selectedTable == NULL) {
        printf ("Erro, table não existe.\n");
        return db;
    }
    char help [5] = {'(', ')',',' ,' ','\0'};
    char **nomeColunas = splitByChars (collumns, help);
    char **valores = splitByChars(values, help);
    int numeroColunas = 0, numeroValores = 0, j;
    for (j = 0; j < 255 && nomeColunas[j] != NULL; j++) numeroColunas++;
    for (j = 0; j < 255 && valores[j] != NULL; j++) {
      //  printf ("%s\n", valores[j]);
        numeroValores++;
    }
    if (numeroColunas != numeroValores) {
        printf ("Erro: Inconsistencia nos dados.\n");
        return db;
    } 
    for (j =0 ; j < numeroColunas-1; j++) {
        Collumn collumn = buscaCollumn(selectedTable->columns, nomeColunas[j]);
        if (collumn == NULL) {
            printf ("Erro: Coluna %s não existe.\n", nomeColunas[j]);
            return db;
        }
        switch (getType(collumn->tipo))
        {
        case 1:
            if (!verificaInteiro (valores[j])) {
                printf ("Valor %d da coluna %s não é inteiro!\n", j, collumn->name);
                return db;
            }
            break;
        case 2:
            if (!verificaBoolean (valores[j])) {
                printf ("Valor %d da coluna %s não é booleano!\n", j, collumn->name);
                return db;
            }
            break;
        case 3:
            if (!verificaVarchar (valores[j])) {
                printf ("Valor %d da coluna %s não é string!\n", j, collumn->name);
                return db;
            }
            break;
        case 4:
            if (!verificaChar (valores[j])) {
                printf ("Valor %d da coluna %s não é char!\n", j, collumn->name);
                return db;
            }
            break;
        default:
            printf ("Erro, tipo da coluna não suportado.\n");
            break;
        }
    }
    for (j =0 ; j < numeroColunas-1; j++) {
        Collumn collumn = buscaCollumn(selectedTable->columns, nomeColunas[j]);
        switch (getType(collumn->tipo))
        {
        case 1:
            insereInteger(collumn->integers, atoi (valores[j]));
            break;
        case 2:
            if (strcmp (valores[j], "TRUE") == 0) {
                insereBoolean (collumn->booleans, true);
            } else {
                insereBoolean(collumn->booleans, false);
            }
            break;
        case 3:
            insereVarchar(collumn->varchars, valores[j]);
            break;
        case 4:
            insereChar(collumn->chars, valores[j][1]);
            break;
        default:
            printf ("Erro, tipo da coluna não suportado.\n");
            break;
        }
    }
    //PREENCHER OS CAMPOS NÃO INSERIDOS COM VALORES NULOS
    int numero = numeroDeColunas(selectedTable->columns);
    //SE FOREM IGUAIS NÃO É PRECISO VERIFICAR
    if (numero == numeroColunas) {
        printf ("SUCESSO!\n");
        return db;
    } 
    int i , flag;
    char **todasColunas = splitByChars (getNomeColunas(selectedTable->columns), ",");
    for (j = 1; j < numero; j++) {
        flag = 1;
        for (i = 0; i < numeroColunas-1; i++) {
        if (strcmp( todasColunas[j], nomeColunas[i]) == 0 ) flag = 0;
        }
        if (flag) {
            Collumn collumn = buscaCollumn(selectedTable->columns, todasColunas[j]);
            switch (getType(collumn->tipo))
            {
                case 1:
                    insereInteger(collumn->integers, 0);
                    break;
                case 2:
                    if (strcmp (valores[j], "TRUE") == 0) {
                        insereBoolean (collumn->booleans, false);
                    }
                    break;
                case 3:
                    insereVarchar(collumn->varchars, "");
                    break;
                case 4:
                    insereChar(collumn->chars, 0);
                    break;
                default:
                    printf ("Erro, tipo da coluna não suportado.\n");
                    break;
            }
        }
    }
    printf ("SUCESSO!\n");
    return db;
}
void selectFromSQL (DataBase db, char **processado, int tam, int num) {
    int i, j;
    char *colunas;
    if (db == NULL) {
        printf ("Erro, banco de dados não selecionado.\n");
        return;
    }
    Table selectedTable = buscaTable (db->tables, processado[num+1]);
    if (selectedTable == NULL) {
        printf ("Erro, table não existe.\n");
        return;
    }
    colunas = malloc(255 * sizeof(char));
    strcpy (colunas, "");
    for (i = 1; i < num; i++) {
        strcat (colunas, processado[i]);
    }
    if (colunas[strlen(colunas)-1] ==  ',') {
        printf ("Erro de sintaxe identicado.\n");
        return;
    }
    char **nomeColunas = splitByChars (colunas, ",");
    int numeroColunasPesquisadas = 0;
    for (i = 0; i < 255 && nomeColunas[i] != NULL; i++) {
         //printf("%s\n", nomeColunas[i]);
         numeroColunasPesquisadas++;
    }
    if (strcmp(nomeColunas[0], "*") == 0) {
        int numero = numeroDeColunas(selectedTable->columns);
        char **todasColunas = splitByChars (getNomeColunas(selectedTable->columns), ",");
        Collumn *collumns;
        collumns = malloc (numero * sizeof(Collumn));
        for (i = 1, j= 0; i < numero && todasColunas[i] != NULL; i++, j++) {
            collumns[j] = buscaCollumn(selectedTable->columns, todasColunas[i]);
        }
       // printf ("OPA");
        //printf ("%s\n", collumns[0]->tipo);
        
        int *listaIDs, tamanhoLista;
        switch (getType(collumns[0]->tipo))
        {
        case 1:
            tamanhoLista = getTamanhoListaInteger (collumns[0]->integers);
            //printf ("Tamanho = %d\n", tamanhoLista);
            listaIDs = malloc(tamanhoLista * sizeof(int));
             listaIDs = listarIdOfCollumnInteger (collumns[0]->integers, listaIDs);
            break;
        case 2:
            tamanhoLista = getTamanhoListaBoolean (collumns[0]->booleans);
            //printf ("Tamanho = %d\n", tamanhoLista);
            listaIDs = malloc(tamanhoLista * sizeof(int));
            listaIDs = listarIdOfCollumnBoolean (collumns[0]->booleans, listaIDs);
            break;
        case 3:
            tamanhoLista = getTamanhoListaVarchar (collumns[0]->varchars);
            //printf ("Tamanho = %d\n", tamanhoLista);
            listaIDs = malloc(tamanhoLista * sizeof(int));
            listaIDs = listarIdOfCollumnVarchar(collumns[0]->varchars, listaIDs);
            break;
        case 4:
            tamanhoLista = getTamanhoListaChar (collumns[0]->chars);
            //printf ("Tamanho = %d\n", tamanhoLista);
            listaIDs = malloc(tamanhoLista * sizeof(int));
            listaIDs = listarIdOfCollumnChar(collumns[0]->chars, listaIDs);
            break;
        default:
            printf ("Erro, tipo da coluna não suportado.\n");
            break;
        }
        for (int i = 1; i < numero; i++) {
            printf ("| %s |", todasColunas[i]);
        }
        printf ("\n");
        Collumn aux;
        for (i = 1; i < tamanhoLista; i++) {
            for (j = 1; j < numero; j++) {
                aux = buscaCollumn (selectedTable->columns, todasColunas[j]);
                switch (getType(aux->tipo)) {
                    case 1:
                        printf ("| %d |", buscaIntegerById(listaIDs[i], aux->integers)->valor);
                        break;
                    case 2:
                        printf ("| %d |", buscaBooleanById(listaIDs[i], aux->booleans)->valor);
                        break;
                    case 3:
                        printf ("| %s |", buscaVarcharById(listaIDs[i], aux->varchars)->valor);
                        break;
                    case 4:
                        printf ("| %c |", buscaCharById(listaIDs[i], aux->chars)->valor);
                        break;
                }
            }
            printf ("\n");
        }
            
    } else {
        Collumn *collumns;
        collumns = malloc (numeroColunasPesquisadas * sizeof(Collumn));
        for (i = 0, j= 0; i < numeroColunasPesquisadas && nomeColunas[i] != NULL; i++, j++) {
            collumns[j] = buscaCollumn(selectedTable->columns, nomeColunas[i]);
            if (collumns[j] == NULL) {
                printf ("Erro, coluna %s não encontrada\n", nomeColunas[i]);
                return;
            }
        }
       // printf ("OPA");
        //printf ("%s\n", collumns[0]->tipo);
        
        int *listaIDs, tamanhoLista;
        switch (getType(collumns[0]->tipo))
        {
        case 1:
            tamanhoLista = getTamanhoListaInteger (collumns[0]->integers);
            //printf ("Tamanho = %d\n", tamanhoLista);
            listaIDs = malloc(tamanhoLista * sizeof(int));
             listaIDs = listarIdOfCollumnInteger (collumns[0]->integers, listaIDs);
            break;
        case 2:
            tamanhoLista = getTamanhoListaBoolean (collumns[0]->booleans);
            //printf ("Tamanho = %d\n", tamanhoLista);
            listaIDs = malloc(tamanhoLista * sizeof(int));
            listaIDs = listarIdOfCollumnBoolean (collumns[0]->booleans, listaIDs);
            break;
        case 3:
            tamanhoLista = getTamanhoListaVarchar (collumns[0]->varchars);
            //printf ("Tamanho = %d\n", tamanhoLista);
            listaIDs = malloc(tamanhoLista * sizeof(int));
            listaIDs = listarIdOfCollumnVarchar(collumns[0]->varchars, listaIDs);
            break;
        case 4:
            tamanhoLista = getTamanhoListaChar (collumns[0]->chars);
            //printf ("Tamanho = %d\n", tamanhoLista);
            listaIDs = malloc(tamanhoLista * sizeof(int));
            listaIDs = listarIdOfCollumnChar(collumns[0]->chars, listaIDs);
            break;
        default:
            printf ("Erro, tipo da coluna não suportado.\n");
            break;
        }
        for (int i = 0; i < numeroColunasPesquisadas; i++) {
            printf ("| %s |", nomeColunas[i]);
        }
        printf ("\n");
        Collumn aux;
        for (i = 1; i < tamanhoLista; i++) {
            for (j = 0; j < numeroColunasPesquisadas; j++) {
                aux = buscaCollumn (selectedTable->columns, nomeColunas[j]);
                switch (getType(aux->tipo)) {
                    case 1:
                        printf ("| %d |", buscaIntegerById(listaIDs[i], aux->integers)->valor);
                        break;
                    case 2:
                        printf ("| %d |", buscaBooleanById(listaIDs[i], aux->booleans)->valor);
                        break;
                    case 3:
                        printf ("| %s |", buscaVarcharById(listaIDs[i], aux->varchars)->valor);
                        break;
                    case 4:
                        printf ("| %c |", buscaCharById(listaIDs[i], aux->chars)->valor);
                        break;
                }
            }
            printf ("\n");
        }
    }
}

void selectFromWhereSQL (DataBase db, char ** processado,int tam, int num) {
    int i, j;
    char *colunas;
    if (db == NULL) {
        printf ("Erro, banco de dados não selecionado.\n");
        return;
    }
    Table selectedTable = buscaTable (db->tables, processado[num+1]);
    if (selectedTable == NULL) {
        printf ("Erro, table não existe.\n");
        return;
    }
    colunas = malloc(255 * sizeof(char));
    strcpy (colunas, "");
    for (i = 1; i < num; i++) {
        strcat (colunas, processado[i]);
    }
    if (colunas[strlen(colunas)-1] ==  ',') {
        printf ("Erro de sintaxe identicado.\n");
        return;
    }
    char **nomeColunas = splitByChars (colunas, ",");
    int numeroColunasPesquisadas = 0;
    for (i = 0; i < 255 && nomeColunas[i] != NULL; i++) {
         //printf("%s\n", nomeColunas[i]);
         numeroColunasPesquisadas++;
    }
    char *expressao;
    expressao = malloc (255*sizeof(255));
    strcpy (expressao, "");
    for (i = num+3; i < tam; i++) {
        strcat (expressao, processado[i]);
    }
    char **nomeExpressao = splitByCharsButNoRemove (expressao, "=><");
    int numeroExpressaoPesquisadas = 0;
    for (i = 0; i < 255 && nomeExpressao[i] != NULL; i++) {
        // printf("%s\n", nomeExpressao[i]);
         numeroExpressaoPesquisadas++;
    }
    if (numeroExpressaoPesquisadas != 3) {
        printf ("NOT SUPPORTED YET\n");
        return;
    }
    
        int numero = numeroDeColunas(selectedTable->columns);
        if (numero == 1) {
            printf ("Erro, não há colunas\n");
            return;
        }
        char **todasColunas = splitByChars (getNomeColunas(selectedTable->columns), ",");
        Collumn *collumns;
        collumns = malloc (numero * sizeof(Collumn));
        for (i = 1, j= 0; i < numero && todasColunas[i] != NULL; i++, j++) {
            collumns[j] = buscaCollumn(selectedTable->columns, todasColunas[i]);
        }
        int op = 0;
        for (i = 1, j= 0; i < numero && todasColunas[i] != NULL; i++, j++) {
            if (strcmp(todasColunas[i], nomeExpressao[0]) == 0) op = j;
            //collumns[j] = buscaCollumn(selectedTable->columns, todasColunas[i]);
        }
       // printf ("OPA");
        //printf ("%s\n", collumns[0]->tipo);
        if (collumns[op] == NULL) {
            printf ("Erro não esperado.\n");
            return;
        } else {
            //printf ("%s\n", collumns[op]->name);
            
        }
        
        //return;
        int *listaIDs, tamanhoLista;
        switch (getType(collumns[op]->tipo))
        {
        case 1:
            tamanhoLista = getTamanhoListaInteger (collumns[op]->integers);
            //printf ("Tamanho = %d\n", tamanhoLista);
            listaIDs = malloc(tamanhoLista * sizeof(int));
            //printf ("%d %c\n", atoi (nomeExpressao[2]), nomeExpressao[1][0]);
            for (i = 0; i < tamanhoLista; i++) {
                listaIDs[i] = -1;
            }
             listaIDs = listarIdOfCollumnIntegerByValor (collumns[op]->integers, listaIDs, atoi(nomeExpressao[2]), nomeExpressao[1][0]);
             //   listaIDs = listarIdOfCollumnInteger (collumns[op]->integers, listaIDs);
            break;
        case 2:
            tamanhoLista = getTamanhoListaBoolean (collumns[op]->booleans);
            //printf ("Tamanho = %d\n", tamanhoLista);
            listaIDs = malloc(tamanhoLista * sizeof(int));
            for (i = 0; i < tamanhoLista; i++) {
                listaIDs[i] = -1;
            }
            listaIDs = listarIdOfCollumnBooleanByValor (collumns[op]->booleans, listaIDs, nomeExpressao[2]);
            break;
        case 3:
            tamanhoLista = getTamanhoListaVarchar (collumns[op]->varchars);
            //printf ("Tamanho = %d\n", tamanhoLista);
            listaIDs = malloc(tamanhoLista * sizeof(int));
            for (i = 0; i < tamanhoLista; i++) {
                listaIDs[i] = -1;
            }
            listaIDs = listarIdOfCollumnVarcharByValor(collumns[op]->varchars, listaIDs, nomeExpressao[2], nomeExpressao[1][0]);
            break;
        case 4:
            tamanhoLista = getTamanhoListaChar (collumns[op]->chars);
            //printf ("Tamanho = %d\n", tamanhoLista);
            listaIDs = malloc(tamanhoLista * sizeof(int));
            for (i = 0; i < tamanhoLista; i++) {
                listaIDs[i] = -1;
            }
            listaIDs = listarIdOfCollumnCharByValor(collumns[op]->chars, listaIDs, nomeExpressao[2][1], nomeExpressao[1][0]);
            break;
        default:
            printf ("Erro, tipo da coluna não suportado.\n");
            break;
        }
    if (strcmp(nomeColunas[0], "*") == 0) {
        for (int i = 1; i < numero; i++) {
            printf ("| %s |", todasColunas[i]);
        }
        printf ("\n");
        Collumn aux;
        for (i = 0; i < tamanhoLista && listaIDs[i] >= 0; i++) {
            if (listaIDs[i] == 0) continue;
            //printf("%d", listaIDs[i]);
            for (j = 1; j < numero; j++) {
                aux = buscaCollumn (selectedTable->columns, todasColunas[j]);
                switch (getType(aux->tipo)) {
                    case 1:
                        printf ("| %d |", buscaIntegerById(listaIDs[i], aux->integers)->valor);
                        break;
                    case 2:
                        printf ("| %d |", buscaBooleanById(listaIDs[i], aux->booleans)->valor);
                        break;
                    case 3:
                        printf ("| %s |", buscaVarcharById(listaIDs[i], aux->varchars)->valor);
                        break;
                    case 4:
                        printf ("| %c |", buscaCharById(listaIDs[i], aux->chars)->valor);
                        break;
                }
            }
            printf ("\n");
        }
            
    } else {
        for (int i = 0; i < numeroColunasPesquisadas; i++) {
            Collumn aux = buscaCollumn (selectedTable->columns, nomeColunas[i]);
            if (aux == NULL) {
                printf ("Erro, coluna %s não existe.\n", nomeColunas[i]);
                return;
            }
        }
        for (int i = 0; i < numeroColunasPesquisadas; i++) {
            printf ("| %s |", nomeColunas[i]);
        }
        printf ("\n");
        Collumn aux;
        for (i = 0; i < tamanhoLista && listaIDs[i] >= 0; i++) {
            if (listaIDs[i] == 0) continue;
            for (j = 0; j < numeroColunasPesquisadas; j++) {
                aux = buscaCollumn (selectedTable->columns, nomeColunas[j]);
                switch (getType(aux->tipo)) {
                    case 1:
                        printf ("| %d |", buscaIntegerById(listaIDs[i], aux->integers)->valor);
                        break;
                    case 2:
                        printf ("| %d |", buscaBooleanById(listaIDs[i], aux->booleans)->valor);
                        break;
                    case 3:
                        printf ("| %s |", buscaVarcharById(listaIDs[i], aux->varchars)->valor);
                        break;
                    case 4:
                        printf ("| %c |", buscaCharById(listaIDs[i], aux->chars)->valor);
                        break;
                }
            }
            printf ("\n");
        }
    }
}


DataBase updateSQL (DataBase db, char **processado, int tam) {
    int i, j;
    if (db == NULL) {
        printf ("Erro, banco de dados não selecionado.\n");
        return db;
    }
    Table selectedTable = buscaTable (db->tables, processado[1]);
    if (selectedTable == NULL) {
        printf ("Erro, table não existe.\n");
        return db;
    }
    //Procura pelo where
    bool existeWhere = false;
    int ondeFicaWhere, numeroExpressaoPesquisadas;
    char *expressao;
    char **nomeExpressao;
    for (i = 3; i < tam; i++) {
        if (strcmp(processado[i], "WHERE") == 0) {
            existeWhere = true;
            ondeFicaWhere = i;
        }
    }
    if (existeWhere) {
        expressao = malloc (255*sizeof(255));
        strcpy (expressao, "");
        for (i = ondeFicaWhere+1; i < tam; i++) {
            strcat (expressao, processado[i]);
        }
        nomeExpressao = splitByCharsButNoRemove (expressao, "=><");
        numeroExpressaoPesquisadas = 0;
        for (i = 0; i < 255 && nomeExpressao[i] != NULL; i++) {
            // printf("%s\n", nomeExpressao[i]);
            numeroExpressaoPesquisadas++;
        }
        if (numeroExpressaoPesquisadas != 3) {
            printf ("NOT SUPPORTED YET\n");
            return db;
        }
    }

    //GET OS UPDATES
    char *update;
    int quantidadeDeUpdates = 0;
    char **nomeColunas;
    char **valores;
    update = malloc (255 * sizeof(char));
    strcpy (update, "");
    if (existeWhere) {
        for (i = 3; i < ondeFicaWhere; i++) {
            strcat (update, processado[i]);
        }
    } else {
        for (i = 3; i < tam; i++) {
            strcat (update, processado[i]);
        }
    }
    
    char **updates = splitByChars(update, " ");
    strcpy (update, "");
    for (i = 0; i < 255 && updates[i] != NULL; i++) {
        strcat (update, updates[i]);
    }
    updates = splitByChars (update, ",");
    for (i = 0; i < 255 && updates[i] != NULL; i++) {
       // printf ("%s\n", updates[i]);
        quantidadeDeUpdates++;
    }
    //printf ("%d\n", quantidadeDeUpdates);
    nomeColunas = malloc (quantidadeDeUpdates * sizeof(char *));
    valores = malloc (quantidadeDeUpdates * sizeof(char *));
    for (i = 0; i < 255 && updates[i] != NULL; i++) {
         char **aux = splitByChars (updates[i], "=");
         nomeColunas[i] = aux[0];
         valores[i] =  aux[1];
       // printf ("%s\n", updates[i]);
       // quantidadeDeUpdates++;
    }

    //VERIFICA SE AS COLUNAS EXISTEM E SE OS VALORES ESTÃO CORRETOS
    Collumn collumn;
    for (j = 0; j < quantidadeDeUpdates; j++) {
        collumn = buscaCollumn(selectedTable->columns, nomeColunas[j]);
        if (collumn == NULL) {
            printf ("Erro: Coluna %s não existe.\n", nomeColunas[j]);
            return db;
        }
        switch (getType(collumn->tipo))
        {
        case 1:
            if (!verificaInteiro (valores[j])) {
                printf ("Valor %d da coluna %s não é inteiro!\n", j, collumn->name);
                return db;
            }
            break;
        case 2:
            if (!verificaBoolean (valores[j])) {
                printf ("Valor %d da coluna %s não é booleano!\n", j, collumn->name);
                return db;
            }
            break;
        case 3:
            if (!verificaVarchar (valores[j])) {
                printf ("Valor %d da coluna %s não é string!\n", j, collumn->name);
                return db;
            }
            break;
        case 4:
            if (!verificaChar (valores[j])) {
                printf ("Valor %d da coluna %s não é char!\n", j, collumn->name);
                return db;
            }
            break;
        default:
            printf ("Erro, tipo da coluna não suportado.\n");
            break;
        }
    }

    //VERIFICA SE A EXPRESSÃO WHERE É VALIDA
    if (existeWhere) {
        collumn = buscaCollumn (selectedTable->columns, nomeExpressao[0]);
        if (collumn == NULL) {
            printf ("Erro: Coluna %s não existe.\n", nomeExpressao[0]);
            return db;
        }
        switch (getType(collumn->tipo))
        {
        case 1:
            if (!verificaInteiro (nomeExpressao[2])) {
                printf ("Valor %d da coluna %s não é inteiro!\n", 1, collumn->name);
                return db;
            }
            break;
        case 2:
            if (!verificaBoolean (nomeExpressao[2])) {
                printf ("Valor %d da coluna %s não é booleano!\n", 1, collumn->name);
                return db;
            }
            break;
        case 3:
            if (!verificaVarchar (nomeExpressao[2])) {
                printf ("Valor %d da coluna %s não é string!\n", 1, collumn->name);
                return db;
            }
            break;
        case 4:
            if (!verificaChar (nomeExpressao[2])) {
                printf ("Valor %d da coluna %s não é char!\n", 1, collumn->name);
                return db;
            }
            break;
        default:
            printf ("Erro, tipo da coluna não suportado.\n");
            break;
        }
    }

    //PEGA OS ITENS QUE DEVERÃO SER ALTERADOS
    int *listaIDs, tamanhoLista;
    if (!existeWhere)
        collumn = buscaCollumn (selectedTable->columns, nomeColunas[0]);
    switch (getType(collumn->tipo))
    {
    case 1:
        tamanhoLista = getTamanhoListaInteger (collumn->integers);
        //printf ("Tamanho = %d\n", tamanhoLista);
        listaIDs = malloc(tamanhoLista * sizeof(int));
        if (existeWhere) {
            for (i = 0; i < tamanhoLista; i++) {
                listaIDs[i] = -1;
            }
            listaIDs = listarIdOfCollumnIntegerByValor (collumn->integers, listaIDs, atoi(nomeExpressao[2]), nomeExpressao[1][0]);
            //   listaIDs = listarIdOfCollumnInteger (collumns[op]->integers, listaIDs);
        } else {
            listaIDs = listarIdOfCollumnInteger (collumn->integers, listaIDs);
        }
        //printf ("%d %c\n", atoi (nomeExpressao[2]), nomeExpressao[1][0]);
        
        break;
    case 2:
        tamanhoLista = getTamanhoListaBoolean (collumn->booleans);
        //printf ("Tamanho = %d\n", tamanhoLista);
        listaIDs = malloc(tamanhoLista * sizeof(int));
        for (i = 0; i < tamanhoLista; i++) {
            listaIDs[i] = -1;
        }
        if (existeWhere)
            listaIDs = listarIdOfCollumnBooleanByValor (collumn->booleans, listaIDs, nomeExpressao[2]);
        else 
            listaIDs = listarIdOfCollumnBoolean(collumn->booleans, listaIDs);
        break;
    case 3:
        tamanhoLista = getTamanhoListaVarchar (collumn->varchars);
        //printf ("Tamanho = %d\n", tamanhoLista);
        listaIDs = malloc(tamanhoLista * sizeof(int));
        for (i = 0; i < tamanhoLista; i++) {
            listaIDs[i] = -1;
        }
        if (existeWhere)
            listaIDs = listarIdOfCollumnVarcharByValor(collumn->varchars, listaIDs, nomeExpressao[2], nomeExpressao[1][0]);
        else 
            listaIDs = listarIdOfCollumnVarchar(collumn->varchars, listaIDs);
        break;
    case 4:
        tamanhoLista = getTamanhoListaChar (collumn->chars);
        //printf ("Tamanho = %d\n", tamanhoLista);
        listaIDs = malloc(tamanhoLista * sizeof(int));
        for (i = 0; i < tamanhoLista; i++) {
            listaIDs[i] = -1;
        }
        if (existeWhere)
            listaIDs = listarIdOfCollumnCharByValor(collumn->chars, listaIDs, nomeExpressao[2][1], nomeExpressao[1][0]);
        else 
            listaIDs = listarIdOfCollumnChar(collumn->chars, listaIDs);
        break;
    default:
        printf ("Erro, tipo da coluna não suportado.\n");
        break;
    }

    //EXECUTA O UPDATE 
    for (i = 0; i < tamanhoLista && listaIDs[i] >= 0; i++) {
        if (listaIDs[i] == 0) continue;
        for (j = 0; j < quantidadeDeUpdates; j++) {
            collumn = buscaCollumn (selectedTable->columns, nomeColunas[j]);
            switch (getType(collumn->tipo)) {
                case 1:
                    buscaIntegerById(listaIDs[i], collumn->integers)->valor = atoi(valores[j]);
                    break;
                case 2:
                    if (strcmp (valores[j], "TRUE") == 0)
                        buscaBooleanById(listaIDs[i], collumn->booleans)->valor = true;
                    else  buscaBooleanById(listaIDs[i], collumn->booleans)->valor = false;
                    break;
                case 3:
                    strcpy (buscaVarcharById(listaIDs[i], collumn->varchars)->valor, valores[j]);
                    break;
                case 4:
                    buscaCharById(listaIDs[i], collumn->chars)->valor = valores[j][1];
                    break;
            }
        }
        //printf ("\n");
    }
    printf ("UPDATE FEITO COM SUCESSO!\n");
    return db;
}

DataBase deleteWhereSQL (DataBase db, char **processado, int tam) {
    int i, j;
    if (db == NULL) {
        printf ("Erro, banco de dados não selecionado.\n");
        return db;
    }
    Table selectedTable = buscaTable (db->tables, processado[2]);
    if (selectedTable == NULL) {
        printf ("Erro, table não existe.\n");
        return db;
    }
    //PROCURA PELO WHERE
    bool existeWhere = false;
    int ondeFicaWhere, numeroExpressaoPesquisadas;
    char *expressao;
    char **nomeExpressao;
    for (i = 3; i < tam; i++) {
        if (strcmp(processado[i], "WHERE") == 0) {
            existeWhere = true;
            ondeFicaWhere = i;
            break;
        }
    }
    if (existeWhere) {
        expressao = malloc (255*sizeof(255));
        strcpy (expressao, "");
        for (i = ondeFicaWhere+1; i < tam; i++) {
            strcat (expressao, processado[i]);
        }
        nomeExpressao = splitByCharsButNoRemove (expressao, "=><");
        numeroExpressaoPesquisadas = 0;
        for (i = 0; i < 255 && nomeExpressao[i] != NULL; i++) {
            // printf("%s\n", nomeExpressao[i]);
            numeroExpressaoPesquisadas++;
        }
        if (numeroExpressaoPesquisadas != 3) {
            printf ("NOT SUPPORTED YET\n");
            return db;
        }
    }

    //VERIFICA SE A EXPRESSÃO WHERE É VALIDA
    Collumn collumn;
    if (existeWhere) {
        collumn = buscaCollumn (selectedTable->columns, nomeExpressao[0]);
        if (collumn == NULL) {
            printf ("Erro: Coluna %s não existe.\n", nomeExpressao[0]);
            return db;
        }
        switch (getType(collumn->tipo))
        {
        case 1:
            if (!verificaInteiro (nomeExpressao[2])) {
                printf ("Valor %d da coluna %s não é inteiro!\n", 1, collumn->name);
                return db;
            }
            break;
        case 2:
            if (!verificaBoolean (nomeExpressao[2])) {
                printf ("Valor %d da coluna %s não é booleano!\n", 1, collumn->name);
                return db;
            }
            break;
        case 3:
            if (!verificaVarchar (nomeExpressao[2])) {
                printf ("Valor %d da coluna %s não é string!\n", 1, collumn->name);
                return db;
            }
            break;
        case 4:
            if (!verificaChar (nomeExpressao[2])) {
                printf ("Valor %d da coluna %s não é char!\n", 1, collumn->name);
                return db;
            }
            break;
        default:
            printf ("Erro, tipo da coluna não suportado.\n");
            return db;
            break;
        }
    }

    //PEGA TODAS AS COLUNAS
    int numero = numeroDeColunas(selectedTable->columns);
    if (numero == 1) {
        printf ("Erro, não há colunas\n");
        return db;
    }
    char **todasColunas = splitByChars (getNomeColunas(selectedTable->columns), ",");
    Collumn *collumns;
    collumns = malloc (numero * sizeof(Collumn));
    for (i = 1, j= 0; i < numero && todasColunas[i] != NULL; i++, j++) {
        collumns[j] = buscaCollumn(selectedTable->columns, todasColunas[i]);
        if (collumns[j] == NULL) {
            printf("Erro, problema ao pegar colunas");
            return db;
        }
    }

    //printf ("Cheguei aqui 1\n");
    //PEGA OS ITENS QUE DEVERÃO SER DELETADOS
    int *listaIDs, tamanhoLista;
    if (!existeWhere)
        collumn = collumns[0];
    switch (getType(collumn->tipo))
    {
    case 1:
        tamanhoLista = getTamanhoListaInteger (collumn->integers);
        //printf ("Tamanho = %d\n", tamanhoLista);
        listaIDs = malloc(tamanhoLista * sizeof(int));
        if (existeWhere) {
            for (i = 0; i < tamanhoLista; i++) {
                listaIDs[i] = -1;
            }
            listaIDs = listarIdOfCollumnIntegerByValor (collumn->integers, listaIDs, atoi(nomeExpressao[2]), nomeExpressao[1][0]);
            //   listaIDs = listarIdOfCollumnInteger (collumns[op]->integers, listaIDs);
        } else {
            listaIDs = listarIdOfCollumnInteger (collumn->integers, listaIDs);
        }
        //printf ("%d %c\n", atoi (nomeExpressao[2]), nomeExpressao[1][0]);
        
        break;
    case 2:
        tamanhoLista = getTamanhoListaBoolean (collumn->booleans);
        //printf ("Tamanho = %d\n", tamanhoLista);
        listaIDs = malloc(tamanhoLista * sizeof(int));
        for (i = 0; i < tamanhoLista; i++) {
            listaIDs[i] = -1;
        }
        if (existeWhere)
            listaIDs = listarIdOfCollumnBooleanByValor (collumn->booleans, listaIDs, nomeExpressao[2]);
        else 
            listaIDs = listarIdOfCollumnBoolean(collumn->booleans, listaIDs);
        break;
    case 3:
        tamanhoLista = getTamanhoListaVarchar (collumn->varchars);
        //printf ("Tamanho = %d\n", tamanhoLista);
        listaIDs = malloc(tamanhoLista * sizeof(int));
        for (i = 0; i < tamanhoLista; i++) {
            listaIDs[i] = -1;
        }
        if (existeWhere)
            listaIDs = listarIdOfCollumnVarcharByValor(collumn->varchars, listaIDs, nomeExpressao[2], nomeExpressao[1][0]);
        else 
            listaIDs = listarIdOfCollumnVarchar(collumn->varchars, listaIDs);
        break;
    case 4:
        tamanhoLista = getTamanhoListaChar (collumn->chars);
        //printf ("Tamanho = %d\n", tamanhoLista);
        listaIDs = malloc(tamanhoLista * sizeof(int));
        for (i = 0; i < tamanhoLista; i++) {
            listaIDs[i] = -1;
        }
        if (existeWhere)
            listaIDs = listarIdOfCollumnCharByValor(collumn->chars, listaIDs, nomeExpressao[2][1], nomeExpressao[1][0]);
        else 
            listaIDs = listarIdOfCollumnChar(collumn->chars, listaIDs);
        break;
    default:
        printf ("Erro, tipo da coluna não suportado.\n");
        break;
    }

    //printf ("Cheguei aqui 2\n");
    //DELETAR ITENS
    for (i = 0; i < tamanhoLista && listaIDs[i] >= 0; i++) {
        if (listaIDs[i] == 0) continue;
        for (j = 0; j < numero && collumns[j] != NULL; j++) {
            collumn = collumns[j];
            switch (getType(collumn->tipo)) {
                case 1:
                    removeIntegerById(collumn->integers, listaIDs[i]);
                    break;
                case 2:
                    removeBooleanById(collumn->booleans, listaIDs[i]);
                    break;
                case 3:
                    removeVarcharById(collumn->varchars, listaIDs[i]);
                    break;
                case 4:
                    removeCharById(collumn->chars, listaIDs[i]);
                    break;
            }
        }
        //printf ("\n");
    }
    return db;
}