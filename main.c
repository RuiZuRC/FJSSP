#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#include <locale.h>
#include <windows.h>

typedef struct Maquina
{
    int idMaquina;
    char descMaquina[100];
    float tempo;
    struct Maquina *seguinte;
} Maquinas;

typedef struct Operacao
{
    int idOperacao;
    char descOperacao[100];
    Maquinas *maquinas;
    struct Operacao *seguinte;
} Operacoes;

typedef struct Trabalho
{
    int idTrabalho;
    char descTrabalho[100];
    Operacoes *operacoes;
    struct Trabalho *seguinte;
} Trabalhos;

void menuPrincipal(Trabalhos *trabalhos);
void menuTrabalhos(Trabalhos *trabalhos);
void EstatisticasJob1(Trabalhos *trabalhos);

Maquinas *AdicionarMaquina(Maquinas *maquinas);
Maquinas *InserirInicioListaMaquinas(Maquinas *maquinas, int idMaquina, char descMaquina[100], float tempo);
void percorrerMaquinas(Maquinas *maquinas);

Operacoes *InserirInicioListaOperacoes(Operacoes *operacoes, int idOperacao, char descOperacao[100], Maquinas *maquinas);
void percorrerOperacoes(Operacoes *operacoes);
void listarOperacao(Trabalhos *trabalhos, int idOperacao, int idTrabalho);

Trabalhos *AdicionarOperacao(Trabalhos *trabalhos, int idTrabalho);
Trabalhos *AdicionarTrabalho(Trabalhos *trabalhos);
Trabalhos *InserirInicioListaTrabalhos(Trabalhos *trabalhos, int idTrabalho, char descTrabalho[100], Operacoes *operacoes);
void percorrerTrabalhos(Trabalhos *trabalhos);
void listarTrabalho(Trabalhos *trabalhos, int idTrabalho);

/* INICIO MAQUINAS */
Maquinas *AdicionarMaquina(Maquinas *maquinas)
{
    int idMaquina;
    char descMaquina[100];
    float tempo;

    system("cls");
    printf("||=======================================================||\n");
    printf("||                   INSERIR MAQUINA                     ||\n");
    printf("||=======================================================||\n");

    // INSERIR NOME DA MAQUINA ESTRUTURA
    printf("Digite o nome da maquina: ");
    scanf("%[^\n]", descMaquina);

    // INSERIR ID DA MAQUINA ESTRUTURA
    printf("Insira o ID da máquina: ");
    scanf("%d", &idMaquina);

    // INSERIR TEMPO DA MAQUINA ESTRUTURA
    printf("Insira o tempo de duração da operação: ");
    scanf("%f", &tempo);

    system("cls");
    maquinas = InserirInicioListaMaquinas(maquinas, idMaquina, descMaquina, tempo);
    return maquinas;
}
Maquinas *InserirInicioListaMaquinas(Maquinas *maquinas, int idMaquina, char descMaquina[100], float tempo)
{
    Maquinas *novaMaquina = (Maquinas *)malloc(sizeof(Maquinas));
    novaMaquina->idMaquina = idMaquina;
    strcpy(novaMaquina->descMaquina, descMaquina);
    novaMaquina->tempo = tempo;
    novaMaquina->seguinte = maquinas;
    return novaMaquina;
}
void percorrerMaquinas(Maquinas *maquinas)
{
    Maquinas *listaDeMaquinas = maquinas;
    printf("||========================================================||\n");
    printf("||                  Listagem de Máquinas                  ||\n");
    printf("||========================================================||\n");
    while (listaDeMaquinas != NULL)
    {
        // printf("\tID: %d \t  |\t Nome: %s\n", listaDeMaquinas->idMaquina, listaDeMaquinas->descMaquina);
        printf("\tID Máquina: %d\n", listaDeMaquinas->idMaquina);
        printf("\tNome da Máquina: %s\n", listaDeMaquinas->descMaquina);
        printf("\tTempo de duração da Operação: %.2f\n", listaDeMaquinas->tempo);
        if (listaDeMaquinas->seguinte != NULL)
        {
            printf("----------------------------------------------------------\n");
        }
        listaDeMaquinas = listaDeMaquinas->seguinte;
    }
    printf("||========================================================||\n");
    printf("\n\n");
}
/* FIM MAQUINAS */

/* INICIO OPERAÇÕES */
Operacoes *InserirInicioListaOperacoes(Operacoes *operacoes, int idOperacao, char descOperacao[100], Maquinas *maquinas)
{
    Operacoes *novaOperacao = (Operacoes *)malloc(sizeof(Operacoes));
    novaOperacao->idOperacao = idOperacao;
    strcpy(novaOperacao->descOperacao, descOperacao);
    novaOperacao->maquinas = maquinas;
    novaOperacao->seguinte = operacoes;
    return novaOperacao;
}
void percorrerOperacoes(Operacoes *operacoes)
{
    Operacoes *listaDeOperacoes = operacoes;
    printf("||========================================================||\n");
    printf("||                  Listagem de Operações                 ||\n");
    printf("||========================================================||\n");
    while (listaDeOperacoes != NULL)
    {
        printf("\tID Operação: %d\n", listaDeOperacoes->idOperacao);
        printf("\tNome da Operação: %s\n", listaDeOperacoes->descOperacao);
        printf("\tMáquinas Operação: \n");
        while (listaDeOperacoes->maquinas != NULL)
        {
            printf("\t\tID Máquina: %d\n", listaDeOperacoes->maquinas->idMaquina);
            printf("\t\tNome da Máquina: %s\n", listaDeOperacoes->maquinas->descMaquina);
            printf("\t\tTempo de duração da Operação: %.2f\n", listaDeOperacoes->maquinas->tempo);
            printf("\t\t------------------------\n");
            listaDeOperacoes->maquinas = listaDeOperacoes->maquinas->seguinte;
        }
        if (listaDeOperacoes->seguinte != NULL)
        {
            printf("----------------------------------------------------------\n");
        }
        listaDeOperacoes = listaDeOperacoes->seguinte;
    }
    printf("||========================================================||\n");
    printf("\n\n");
}
void listarOperacao(Trabalhos *trabalhos, int idOperacao, int idTrabalho){
    system("cls");
    int found = 0;
    int opcao;
    int idMaquina;
    Trabalhos *listaDeTrabalhos = trabalhos;
    while (listaDeTrabalhos != NULL)
    {
        if(listaDeTrabalhos->idTrabalho == idTrabalho){
            printf("||========================================================||\n");
            printf("||                       OPERAÇÃO                         ||\n");
            printf("||========================================================||\n");
            /* 
                printf("\tID Trabalho: %d\n", listaDeTrabalhos->idTrabalho);
                printf("\tNome do Trabalho: %s\n", listaDeTrabalhos->descTrabalho);   
                printf("\tOperações do Trabalho: \n");
             */
            Operacoes *listaDeOperacoes = listaDeTrabalhos->operacoes;
            while (listaDeOperacoes != NULL)
            {
                if(listaDeOperacoes->idOperacao == idOperacao){
                    found = 1;
                    printf("\tID Operação: %d\n", listaDeOperacoes->idOperacao);
                    printf("\tNome da Operação: %s\n", listaDeOperacoes->descOperacao);
                    printf("\tMáquinas Operação: \n");
                    
                    Maquinas *listaDeMaquinas = listaDeOperacoes->maquinas;
                    while (listaDeMaquinas != NULL)
                    {
                        printf("\t\tID Máquina: %d\n", listaDeMaquinas->idMaquina);
                        printf("\t\tNome da Máquina: %s\n", listaDeMaquinas->descMaquina);
                        printf("\t\tTempo de duração da Operação: %.2f\n", listaDeMaquinas->tempo);
                        printf("\t\t------------------------\n");
                        listaDeMaquinas = listaDeMaquinas->seguinte;
                    } 
                   
                    printf("\t------------------------\n");
                }
                listaDeOperacoes = listaDeOperacoes->seguinte;
            }
        }
        listaDeTrabalhos = listaDeTrabalhos->seguinte;
    }
    printf("||========================================================||\n");
    if(found == 0){
        printf("||              ID DE OPERAÇÃO NÃO ENCONTRADO             ||\n");
        printf("||========================================================||\n");
        system("pause");
        menuTrabalhos(trabalhos);
    }
    printf("||                                                        ||\n");
    printf("|| 1 - ADICIONAR MAQUINA                                  ||\n");
    printf("|| 2 - EDITAR MAQUINA                                     ||\n");
    printf("|| 3 - REMOVER MAQUINA                                    ||\n");
    printf("|| 9 - VOLTAR                                             ||\n");
    printf("|| 0 - SAIR                                               ||\n");
    printf("||                                                        ||\n");
    printf("||========================================================||\n");
    printf("||========================================================||\n");
    printf("|| OPÇÃO: ");
    scanf("%d", &opcao);
    switch(opcao){
        case 1:
            //ADICIONAR MAQUINA
            break;
        case 2:
            //EDITAR MAQUINA
            break;
        case 3:
            //REMOVER MAQUINA
            break;
        case 9:
            listarTrabalho(trabalhos, idTrabalho);
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("||========================================================||\n");
            printf("||                 OPÇÃO INVÁLIDA                         ||\n");
            printf("||========================================================||\n");
            system("pause");
            listarOperacao(trabalhos, idOperacao, idTrabalho);
            break;
    }
}
/* FIM OPERAÇÕES */

/* INICIO TRABALHOS */
Trabalhos *AdicionarOperacao(Trabalhos *trabalhos, int idTrabalho)
{

    int idOperacao;
    char descOperacao[100];
    Maquinas *maquinas = NULL;
    Operacoes *operacoes = NULL;
    system("cls");
    printf("||=======================================================||\n");
    printf("||                   INSERIR OPERAÇÃO                    ||\n");
    printf("||=======================================================||\n");

    // INSERIR NOME DA OPERAÇÃO
    printf("Digite o nome da Operação: ");
    scanf("%s", descOperacao);

    // INSERIR ID DA OPERAÇÃO
    printf("Insira o ID da Operação: ");
    scanf("%d", &idOperacao);
    system("cls");

    Trabalhos *listaDeTrabalhos = trabalhos;
    while (listaDeTrabalhos != NULL)
    {
        if(listaDeTrabalhos->idTrabalho == idTrabalho){
            operacoes = listaDeTrabalhos->operacoes;
            operacoes = InserirInicioListaOperacoes(operacoes, idOperacao, descOperacao, maquinas);
            listaDeTrabalhos->operacoes = operacoes;
        }
        listaDeTrabalhos = listaDeTrabalhos->seguinte;
    }
    return trabalhos;
}
Trabalhos *AdicionarTrabalho(Trabalhos *trabalhos)
{
    int idTrabalho;
    char descTrabalho[100];
    Operacoes *operacoes = NULL;
    system("cls");
    printf("||=======================================================||\n");
    printf("||                    INSERIR TRABALHO                   ||\n");
    printf("||=======================================================||\n");

    // INSERIR NOME DO TRABALHO
    printf("Digite o nome do Trabalho: ");
    scanf("%s", descTrabalho);

    // INSERIR ID DA OPERAÇÃO
    printf("Insira o ID do Trabalho: ");
    scanf("%d", &idTrabalho);

    system("cls");
    trabalhos = InserirInicioListaTrabalhos(trabalhos, idTrabalho, descTrabalho, operacoes);
    return trabalhos;
}
Trabalhos *InserirInicioListaTrabalhos(Trabalhos *trabalhos, int idTrabalho, char descTrabalho[100], Operacoes *operacoes)
{
    Trabalhos *novoTrabalho = (Trabalhos *)malloc(sizeof(Trabalhos));
    novoTrabalho->idTrabalho = idTrabalho;
    strcpy(novoTrabalho->descTrabalho, descTrabalho);
    novoTrabalho->operacoes = operacoes;
    novoTrabalho->seguinte = trabalhos;
    return novoTrabalho;
}
void percorrerTrabalhos(Trabalhos *trabalhos)
{
    Trabalhos *listaDeTrabalhos = trabalhos;
    printf("||========================================================||\n");
    printf("||                  Listagem de Trabalhos                 ||\n");
    printf("||========================================================||\n");
    while (listaDeTrabalhos != NULL)
    {
        printf("\tID Trabalho: %d\n", listaDeTrabalhos->idTrabalho);
        printf("\tNome do Trabalho: %s\n", listaDeTrabalhos->descTrabalho);
        /*         
            printf("\tOperações do Trabalho: \n");
            Operacoes *listaDeOperacoes = listaDeTrabalhos->operacoes;
            while (listaDeOperacoes != NULL)
            {
                printf("\t\tID Operação: %d\n", listaDeOperacoes->idOperacao);
                printf("\t\tNome da Operação: %s\n", listaDeOperacoes->descOperacao);
                printf("\t\tMáquinas Operação: \n");
                Maquinas *listaDeMaquinas = listaDeOperacoes->maquinas;
                while (listaDeMaquinas != NULL)
                {
                    printf("\t\t\tID Máquina: %d\n", listaDeMaquinas->idMaquina);
                    printf("\t\t\tNome da Máquina: %s\n", listaDeMaquinas->descMaquina);
                    printf("\t\t\tTempo de duração da Operação: %.2f\n", listaDeMaquinas->tempo);
                    printf("\t\t\t------------------------\n");
                    listaDeMaquinas = listaDeMaquinas->seguinte;
                }
                printf("\t\t------------------------\n");
                listaDeOperacoes = listaDeOperacoes->seguinte;
            }
        */
        if (listaDeTrabalhos->seguinte != NULL)
        {
            printf("----------------------------------------------------------\n");
        }

        listaDeTrabalhos = listaDeTrabalhos->seguinte;
    }
    printf("||========================================================||\n");
}
Trabalhos *DeleteOperacao(Trabalhos *trabalhos, int idOperacao, int idTrabalho){
    Trabalhos *listaDeTrabalhos = trabalhos;
    while (listaDeTrabalhos != NULL)
    {
        Operacoes *nodoAtual = listaDeTrabalhos->operacoes;
        Operacoes *nodoAnterior;

        if (nodoAtual->idOperacao == idOperacao)
        {
            listaDeTrabalhos->operacoes = nodoAtual->seguinte;
            free(nodoAtual);
        }
        else
        {
            nodoAnterior = listaDeTrabalhos->operacoes;// Armazena a informação da operação
            nodoAtual = nodoAnterior->seguinte; // Segue para a proxima operação
            while ((nodoAtual != NULL) && (nodoAtual->idOperacao != idOperacao))
            {
                nodoAnterior = nodoAtual;
                nodoAtual = nodoAtual->seguinte;
            }
            if (nodoAtual != NULL)
            {
                nodoAnterior->seguinte = nodoAtual->seguinte;
                free(nodoAtual);
            }
        }
        listaDeTrabalhos = listaDeTrabalhos->seguinte;
    }
    return trabalhos;
}
void listarTrabalho(Trabalhos *trabalhos, int idTrabalho){
    system("cls");
    int found = 0;
    int opcao;
    int idOperacao;
    Trabalhos *listaDeTrabalhos = trabalhos;
    while (listaDeTrabalhos != NULL)
    {
        if(listaDeTrabalhos->idTrabalho == idTrabalho){
            printf("||========================================================||\n");
            printf("||                       TRABALHO                         ||\n");
            printf("||========================================================||\n");
            found = 1;
            printf("\tID Trabalho: %d\n", listaDeTrabalhos->idTrabalho);
            printf("\tNome do Trabalho: %s\n", listaDeTrabalhos->descTrabalho);
                    
            printf("\tOperações do Trabalho: \n");
            Operacoes *listaDeOperacoes = listaDeTrabalhos->operacoes;
            while (listaDeOperacoes != NULL)
            {
                printf("\t\tID Operação: %d\n", listaDeOperacoes->idOperacao);
                printf("\t\tNome da Operação: %s\n", listaDeOperacoes->descOperacao);
                printf("\t\tMáquinas Operação: \n");
                /* 
                Maquinas *listaDeMaquinas = listaDeOperacoes->maquinas;
                while (listaDeMaquinas != NULL)
                {
                    printf("\t\t\tID Máquina: %d\n", listaDeMaquinas->idMaquina);
                    printf("\t\t\tNome da Máquina: %s\n", listaDeMaquinas->descMaquina);
                    printf("\t\t\tTempo de duração da Operação: %.2f\n", listaDeMaquinas->tempo);
                    printf("\t\t\t------------------------\n");
                    listaDeMaquinas = listaDeMaquinas->seguinte;
                } 
                */
                printf("\t\t------------------------\n");
                listaDeOperacoes = listaDeOperacoes->seguinte;
            }
        }
        listaDeTrabalhos = listaDeTrabalhos->seguinte;
    }
    printf("||========================================================||\n");
    if(found == 0){
        printf("||              ID DE TRABALHO NÃO ENCONTRADO             ||\n");
        printf("||========================================================||\n");
        system("pause");
        menuTrabalhos(trabalhos);
    }
    printf("||                                                        ||\n");
    printf("|| 1 - VER OPERAÇÃO                                       ||\n");
    printf("|| 2 - ADICIONAR OPERAÇÃO                                 ||\n");
    printf("|| 3 - EDITAR OPERAÇÃO                                    ||\n");
    printf("|| 4 - REMOVER OPERAÇÃO                                   ||\n");
    printf("|| 9 - VOLTAR                                             ||\n");
    printf("|| 0 - SAIR                                               ||\n");
    printf("||                                                        ||\n");
    printf("||========================================================||\n");
    printf("||========================================================||\n");
    printf("|| OPÇÃO: ");
    scanf("%d", &opcao);
    switch(opcao){
        case 1:
            //VER OPERAÇÃO
            printf("||========================================================||\n");
            printf("|| ID DA OPERAÇÃO QUE PRETENDE VER: ");
            scanf("%d", &idOperacao);
            listarOperacao(trabalhos, idOperacao, idTrabalho);
            system("pause");        
            break;
        case 2:
            //ADICIONAR OPERAÇÃO
            trabalhos = AdicionarOperacao(trabalhos, idTrabalho);
            listarTrabalho(trabalhos, idTrabalho);
            break;
        case 3:
            //editarOperacao(trabalhos, IDTrabalho);
            break;
        case 4:
            //removerOperacao(trabalhos, IDTrabalho);
            break;
        case 9:
            menuTrabalhos(trabalhos);
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("||========================================================||\n");
            printf("||                 OPÇÃO INVÁLIDA                         ||\n");
            printf("||========================================================||\n");
            system("pause");
            listarTrabalho(trabalhos, idTrabalho);
            break;
    }
}
/* FIM TRABALHOS */

/* INICIO LER FICHEIRO */
Trabalhos *lerFicheiro(Trabalhos *trabalhos)
{
    FILE *file = fopen("complemetFiles/jobs_formated_print.txt", "r");
    char c = 1;
    char keywords[][20] = {"Trabalhos", "NomeTrabalho", "IDTrabalho", "Operações", "NomeOperação", "IDOperação", "Maquinas", "NomeMaquina", "IDMaquina", "TempoMaquina"};
    char descTrabalho[100];
    int idTrabalho;
    char descOperacao[100];
    int idOperacao;
    char descMaquina[100];
    int idMaquina;
    char tempoMaquina[100];
    if (file == NULL)
    {
        printf("Error: ERRO AO ABRIR FICHEIRO!\n");
        return NULL;
    }
    else
    {
        while ((c = fgetc(file)) != EOF)
        {
            if (c == ' ')
            {
                continue;
            }
            else
            {
                if (c == '[')
                {
                    continue;
                }
                if (c == '{')
                {

                    while ((c = fgetc(file)) != '}')
                    {
                        // printf("%c", c);
                        if (c == ' ' || c == '\n')
                        {
                            continue;
                        }
                        else
                        {
                            char key[100], value[100];
                            fscanf(file, "%[^\":,}]*c", key);
                            // printf("%d\n", sizeof(key));
                            if (!(strcmp(key, keywords[1])))
                            {
                                // NOME DO TRABALHO
                                fgets(key, sizeof(key), file);
                                sscanf(key, "%*[:\" ]%[a-zA-Z0-9]s", descTrabalho);
                                // printf("\n\n%s -> %s\n", keywords[1], descTrabalho);
                            }
                            else if (!(strcmp(key, keywords[2])))
                            {
                                // ID DO TRABALHO
                                fgets(key, sizeof(key), file);
                                sscanf(key, "%*[:\" ]%[0-9]d", &idTrabalho);
                                // printf("%s -> %s\n", keywords[2], &idTrabalho);
                            }
                            else if (!(strcmp(key, keywords[3])))
                            {
                                // OPERAÇÕES
                                fgets(key, sizeof(key), file);
                                // printf("%s------------------\n", keywords[3]);

                                // LER OPERAÇÕES
                                Operacoes *operacoes = NULL;
                                while ((c = fgetc(file)) != ']')
                                {

                                    if (c == ' ')
                                    {
                                        continue;
                                    }
                                    else
                                    {
                                        if (c == '[')
                                        {
                                            continue;
                                        }
                                        if (c == '{')
                                        {
                                            Maquinas *maquinas = NULL;
                                            while ((c = fgetc(file)) != '}')
                                            {
                                                if (c == ' ' || c == '\n')
                                                {
                                                    continue;
                                                }
                                                else
                                                {
                                                    char key[100], value[100];
                                                    fscanf(file, "%[^\":,}]*c", key);
                                                    if (!(strcmp(key, keywords[4])))
                                                    {
                                                        // NOME DA OPERAÇÃO
                                                        fgets(key, sizeof(key), file);
                                                        sscanf(key, "%*[:\" ]%[a-zA-Z0-9]s", descOperacao);
                                                        // printf("\t%s -> %s\n", keywords[4], descOperacao);
                                                    }
                                                    else if (!(strcmp(key, keywords[5])))
                                                    {
                                                        // NOME DA OPERAÇÃO
                                                        fgets(key, sizeof(key), file);
                                                        sscanf(key, "%*[:\" ]%[a-zA-Z0-9]s", &idOperacao);
                                                        // printf("\t%s -> %s\n", keywords[5], &idOperacao);
                                                    }
                                                    else if (!(strcmp(key, keywords[6])))
                                                    {
                                                        // MAQUINAS
                                                        fgets(key, sizeof(key), file);
                                                        // printf("\t%s------------------\n", keywords[6]);
                                                        //  LER MAQUINAS

                                                        while ((c = fgetc(file)) != ']')
                                                        {

                                                            if (c == ' ')
                                                            {
                                                                // printf("1");
                                                                continue;
                                                            }
                                                            else
                                                            {

                                                                if (c == '[')
                                                                {
                                                                    continue;
                                                                }
                                                                if (c == '{')
                                                                {

                                                                    while ((c = fgetc(file)) != '}')
                                                                    {
                                                                        if (c == ' ' || c == '\n')
                                                                        {
                                                                            continue;
                                                                        }
                                                                        else
                                                                        {
                                                                            char key[100], value[100];
                                                                            fscanf(file, "%[^\":,}]*c", key);
                                                                            if (!(strcmp(key, keywords[7])))
                                                                            {
                                                                                // NOME DA MAQUINA
                                                                                fgets(key, sizeof(key), file);
                                                                                sscanf(key, "%*[:\" ]%[a-zA-Z0-9]s", descMaquina);
                                                                                // printf("\t\t%s -> %s\n", keywords[7], descMaquina);
                                                                            }
                                                                            else if (!(strcmp(key, keywords[8])))
                                                                            {
                                                                                // ID DA MAQUINA
                                                                                fgets(key, sizeof(key), file);
                                                                                sscanf(key, "%*[:\" ]%[0-9]s", &idMaquina);
                                                                                // printf("\t\t%s -> %s\n", keywords[8], &idMaquina);
                                                                            }
                                                                            else if (!(strcmp(key, keywords[9])))
                                                                            {
                                                                                // TEMPO DA MAQUINA
                                                                                fgets(key, sizeof(key), file);
                                                                                sscanf(key, "%*[:\" ]%[0-9]s", tempoMaquina);
                                                                                // printf("\t\t%s -> %s\n", keywords[9], tempoMaquina);
                                                                            }
                                                                        }
                                                                    }
                                                                    // ADICIONAR NOVA MAQUINA À LISTA
                                                                    // printf("Guardar Maquina\n");
                                                                    maquinas = InserirInicioListaMaquinas(maquinas, idMaquina - '0', descMaquina, atof(tempoMaquina));
                                                                    // idMaquina - '0' converte o char para int
                                                                    // atof converte o char para float
                                                                }
                                                            }
                                                        }
                                                        // percorrerMaquinas(maquinas);
                                                    }
                                                }
                                            }
                                            // ADICIONAR NOVA OPERAÇÃO À LISTA
                                            // printf("Guardar Operação\n");
                                            operacoes = InserirInicioListaOperacoes(operacoes, idOperacao - '0', descOperacao, maquinas);
                                            maquinas = NULL;
                                        }
                                    }
                                }
                                // percorrerOperacoes(operacoes);
                                // ADICIONAR NOVO TRABALHO À LISTA
                                // printf("Guardar Trabalho\n");
                                trabalhos = InserirInicioListaTrabalhos(trabalhos, idTrabalho - '0', descTrabalho, operacoes);
                            }
                        }
                    }
                }
            }
        }
        fclose(file);
        // percorrerTrabalhos(trabalhos);
        return trabalhos;
    }
}
/* FIM LER FICHEIRO */

/* INICIO ESCREVER FICHEIRO */
void salvarFicheiro(Trabalhos *trabalhos)
{
    FILE *file = fopen("complemetFiles/jobs_formated_print.txt", "w");
    if (file == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
    }
    else
    {
        Trabalhos *listaDeTrabalhos = trabalhos;
        fprintf(file, "[\n");
        while (listaDeTrabalhos != NULL)
        {
            fprintf(file, "\t{\n");

            fprintf(file, "\t\t\"NomeTrabalho\": \"%s\"\n", listaDeTrabalhos->descTrabalho);
            fprintf(file, "\t\t\"IDTrabalho\": %d\n", listaDeTrabalhos->idTrabalho);
            fprintf(file, "\t\t\"Operações\": [\n");
            Operacoes *listaDeOperacoes = listaDeTrabalhos->operacoes;
            while (listaDeOperacoes != NULL)
            {
                fprintf(file, "\t\t\t{\n");

                fprintf(file, "\t\t\t\t\"NomeOperação\": \"%s\"\n", listaDeOperacoes->descOperacao);
                fprintf(file, "\t\t\t\t\"IDOperação\": %d\n", listaDeOperacoes->idOperacao);
                fprintf(file, "\t\t\t\t\"Maquinas\": [\n");
                Maquinas *listaDeMaquinas = listaDeOperacoes->maquinas;
                while (listaDeMaquinas != NULL)
                {
                    fprintf(file, "\t\t\t\t\t{\n");

                    fprintf(file, "\t\t\t\t\t\t\"NomeMaquina\": \"%s\"\n", listaDeMaquinas->descMaquina);
                    fprintf(file, "\t\t\t\t\t\t\"IDMaquina\": %d\n", listaDeMaquinas->idMaquina);
                    fprintf(file, "\t\t\t\t\t\t\"TempoMaquina\": %.2f\n", listaDeMaquinas->tempo);

                    listaDeMaquinas = listaDeMaquinas->seguinte;
                    if (listaDeMaquinas != NULL)
                    {
                        fprintf(file, "\t\t\t\t\t},\n");
                    }
                    else
                    {
                        fprintf(file, "\t\t\t\t\t}\n");
                    }
                }
                fprintf(file, "\t\t\t\t]\n");
                listaDeOperacoes = listaDeOperacoes->seguinte;
                if (listaDeOperacoes != NULL)
                {
                    fprintf(file, "\t\t\t},\n");
                }
                else
                {
                    fprintf(file, "\t\t\t}\n");
                }
            }
            fprintf(file, "\t\t]\n");
            listaDeTrabalhos = listaDeTrabalhos->seguinte;
            if (listaDeTrabalhos != NULL)
            {
                fprintf(file, "\t},\n");
            }
            else
            {
                fprintf(file, "\t}\n");
            }
        }
        fprintf(file, "]\n");
        fclose(file);
    }
}
/* FIM ESCREVER FICHEIRO */

void menuTrabalhos(Trabalhos *trabalhos){
    system("cls");
    int opcao;
    int idTrabalho;
    percorrerTrabalhos(trabalhos);
    printf("||                                                        ||\n");
    printf("|| 1 - VER JOB                                            ||\n");
    printf("|| 2 - ADICIONAR JOB                                      ||\n");
    printf("|| 3 - EDITAR JOB                                         ||\n");
    printf("|| 4 - REMOVER JOB                                        ||\n");
    printf("|| 9 - VOLTAR                                             ||\n");
    printf("|| 0 - SAIR                                               ||\n");
    printf("||                                                        ||\n");
    printf("||========================================================||\n");
    printf("||========================================================||\n");
    printf("|| OPÇÃO: ");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
        printf("||========================================================||\n");
        printf("|| ID DO JOB QUE PRETENDE VER: ");
        scanf("%d", &idTrabalho);
        listarTrabalho(trabalhos, idTrabalho);
        system("pause");
        break;
    case 2:
        trabalhos = AdicionarTrabalho(trabalhos);
        menuTrabalhos(trabalhos);
        break;
    case 3:
        break;
    case 4:
        break;
    case 9:
        menuPrincipal(trabalhos);
        break;
    case 0: 
        exit(0);
        break;
    default:
        printf("||========================================================||\n");
        printf("||                 OPÇÃO INVÁLIDA                         ||\n");
        printf("||========================================================||\n");
        system("pause");
        menuTrabalhos(trabalhos);
        break;
    }
}

void menuPrincipal(Trabalhos *trabalhos){
    system("cls");
    int opcao;
    printf("||========================================================||\n");
    printf("||                      MENU PRINCIPAL                    ||\n");
    printf("||========================================================||\n");
    printf("||                                                        ||\n");
    printf("|| 1 - VER JOBS                                           ||\n");
    printf("|| 2 - VER ESTATISTICAS DO TRABALHO 1                     ||\n");
    printf("|| 0 - SAIR                                               ||\n");
    printf("||                                                        ||\n");
    printf("||========================================================||\n");
    printf("|| OPÇÃO: ");
    scanf("%d", &opcao);
    switch(opcao){
        case 1:
            menuTrabalhos(trabalhos);
            break;
        case 2:
            EstatisticasJob1(trabalhos);
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("||========================================================||\n");
            printf("||                 OPÇÃO INVÁLIDA                         ||\n");
            printf("||========================================================||\n");
            system("pause");
            menuPrincipal(trabalhos);
            break;
    }
}   

void EstatisticasJob1(Trabalhos *trabalhos){
    system("cls");
    printf("||========================================================||\n");
    printf("||                 MELHOR TEMPO DE EXECUÇÃO               ||\n");
    printf("||========================================================||\n");
    int idTrabalho = 1;
    float MelhorTempoTotalJob = 0;
    Trabalhos *listaDeTrabalhos = trabalhos;
    Maquinas *MaquinaAux = (Maquinas *)malloc(sizeof(Maquinas));
    while(listaDeTrabalhos != NULL){
        if(listaDeTrabalhos->idTrabalho == idTrabalho){
            printf("\tNome do Trabalho: %s\n", listaDeTrabalhos->descTrabalho);
            Operacoes *listaDeOperacoes = listaDeTrabalhos->operacoes;
            while(listaDeOperacoes != NULL){
                MaquinaAux = NULL;
                Maquinas *listaDeMaquinas = listaDeOperacoes->maquinas;
                printf("\t\tOperacao: %s\n", listaDeOperacoes->descOperacao);
                while(listaDeMaquinas != NULL){
                    if(MaquinaAux != NULL && MaquinaAux->tempo > listaDeMaquinas->tempo){
                        MaquinaAux = listaDeMaquinas;
                    }else if(MaquinaAux == NULL){
                        MaquinaAux = listaDeMaquinas;
                    }
                    //printf("Nome Maquina %s\n", listaDeMaquinas->descMaquina);
                    listaDeMaquinas = listaDeMaquinas->seguinte;
                }
                MelhorTempoTotalJob += MaquinaAux->tempo;
                printf("\t\tTempo: %.2f\n", MaquinaAux->tempo);
                printf("\t\t\tMaquina: %s\n", MaquinaAux->descMaquina);
                printf("\t\t------------------------\n");
                listaDeOperacoes = listaDeOperacoes->seguinte;
            }
            printf("||========================================================||\n");
            printf("||O MELHOR TEMPO DE EXECUÇÃO DO TRABALHO É: %.2f\n", MelhorTempoTotalJob);
            printf("||========================================================||\n");
        }
        listaDeTrabalhos = listaDeTrabalhos->seguinte;        
    }
    printf("\n\n");
    printf("||========================================================||\n");
    printf("||                  PIOR TEMPO DE EXECUÇÃO                ||\n");
    printf("||========================================================||\n");
    float PiorTempoTotalJob = 0;
    listaDeTrabalhos = trabalhos;
    MaquinaAux = NULL;
    while(listaDeTrabalhos != NULL){
        if(listaDeTrabalhos->idTrabalho == idTrabalho){
            printf("\tNome do Trabalho: %s\n", listaDeTrabalhos->descTrabalho);
            Operacoes *listaDeOperacoes = listaDeTrabalhos->operacoes;
            while(listaDeOperacoes != NULL){
                MaquinaAux = NULL;
                Maquinas *listaDeMaquinas = listaDeOperacoes->maquinas;
                printf("\t\tOperacao: %s\n", listaDeOperacoes->descOperacao);
                while(listaDeMaquinas != NULL){
                    if(MaquinaAux != NULL && MaquinaAux->tempo < listaDeMaquinas->tempo){
                        MaquinaAux = listaDeMaquinas;
                    }else if(MaquinaAux == NULL){
                        MaquinaAux = listaDeMaquinas;
                    }
                    //printf("Nome Maquina %s\n", listaDeMaquinas->descMaquina);
                    listaDeMaquinas = listaDeMaquinas->seguinte;
                }
                PiorTempoTotalJob += MaquinaAux->tempo;
                printf("\t\tTempo: %.2f\n", MaquinaAux->tempo);
                printf("\t\t\tMaquina: %s\n", MaquinaAux->descMaquina);
                printf("\t\t------------------------\n");
                listaDeOperacoes = listaDeOperacoes->seguinte;
            }
            printf("||========================================================||\n");
            printf("||O PIOR TEMPO DE EXECUÇÃO DO TRABALHO É: %.2f\n", PiorTempoTotalJob);
            printf("||========================================================||\n");
        }
        listaDeTrabalhos = listaDeTrabalhos->seguinte;        
    }
    printf("\n\n");
    printf("||========================================================||\n");
    printf("||                MÉDIA DE TEMPO DE EXECUÇÃO              ||\n");
    printf("||========================================================||\n");
    float MediaTempoOperacao = 0;
    int countMaquinas = 0;
    listaDeTrabalhos = trabalhos;
    MaquinaAux = NULL;
    while(listaDeTrabalhos != NULL){
        if(listaDeTrabalhos->idTrabalho == idTrabalho){
            printf("\tNome do Trabalho: %s\n", listaDeTrabalhos->descTrabalho);
            Operacoes *listaDeOperacoes = listaDeTrabalhos->operacoes;
            while(listaDeOperacoes != NULL){
                MaquinaAux = NULL;
                countMaquinas = 0;
                MediaTempoOperacao = 0;
                Maquinas *listaDeMaquinas = listaDeOperacoes->maquinas;
                printf("\t\tOperacao: %s\n", listaDeOperacoes->descOperacao);
                while(listaDeMaquinas != NULL){
                    MediaTempoOperacao = MediaTempoOperacao + listaDeMaquinas->tempo;
                    countMaquinas++;
                    listaDeMaquinas = listaDeMaquinas->seguinte;
                }
                MediaTempoOperacao = MediaTempoOperacao/countMaquinas;
                printf("\t\tTEMPO MÉDIO DE EXECUÇÃO DA OPERAÇÃO: %.2f\n", MediaTempoOperacao);
                printf("\t\t------------------------\n");
                listaDeOperacoes = listaDeOperacoes->seguinte;
            }
        }
        listaDeTrabalhos = listaDeTrabalhos->seguinte;        
    }
    system("pause");
}

int main()
{
    // Define o valor das páginas de código UTF8 e default do Windows
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    // Define codificação como sendo UTF-8
    SetConsoleOutputCP(CPAGE_UTF8);

    /*
        Maquinas *maquinas = NULL;
        maquinas = AdicionarMaquina(maquinas);
        percorrerMaquinas(maquinas);
    */

    /*
        Operacoes *operacoes = NULL;
        operacoes = AdicionarOperacao(operacoes);
        percorrerOperacoes(operacoes);
    */

    /*
        Trabalhos *trabalhos = NULL;
        trabalhos = AdicionarTrabalho(trabalhos);
        percorrerTrabalhos(trabalhos);
    */


    /*     
        Trabalhos *trabalhos = NULL;
        trabalhos = lerFicheiro(trabalhos);
        trabalhos = DeleteOperacao(trabalhos, 5);
        percorrerTrabalhos(trabalhos);
        salvarFicheiro(trabalhos); 
    */
    Trabalhos *trabalhos = NULL;
    trabalhos = lerFicheiro(trabalhos);
    menuPrincipal(trabalhos);

    // Retorna codificação padrão do Windows
    SetConsoleOutputCP(CPAGE_DEFAULT);
}
