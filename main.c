#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#include <locale.h>
#include <windows.h>

//ESTRUTURA QUE ARMAZENA OS DADOS DAS MAQUINAS
typedef struct Maquina
{
    int idMaquina;
    char descMaquina[100];
    float tempo;
    struct Maquina *seguinte;
} Maquinas;

//ESTRUTURA QUE ARMAZENA OS DADOS DAS OPERAÇÕES
typedef struct Operacao
{
    int idOperacao;
    char descOperacao[100];
    Maquinas *maquinas;
    struct Operacao *seguinte;
} Operacoes;

//ESTRUTURA QUE ARMAZENA OS DADOS DOS TRABALHOS
typedef struct Trabalho
{
    int idTrabalho;
    char descTrabalho[100];
    Operacoes *operacoes;
    struct Trabalho *seguinte;
} Trabalhos;

#include "maquinas.h"
#include "operacoes.h"
#include "trabalhos.h"

void menuPrincipal(Trabalhos *trabalhos);//MENU PRINCIPAL

/*============= INICIO - MAQUINAS =============*/
int proximoIdMaquina()
{
    int idMaquina = 0;//INICIALIZA O ID DA MAQUINA COM 0
    FILE *arquivo = fopen("complemetFiles/proximoIdMaquina.txt", "r");//ABRE O FICHEIRO PARA LEITURA
    if (arquivo != NULL)
    {
        //SE O FICHEIRO EXISTIR
        fscanf(arquivo, "%d", &idMaquina);//LÊ O ID DA MAQUINA PRESENTE NO FICHEIRO
        fclose(arquivo);//FECHA O FICHEIRO
        arquivo = fopen("complemetFiles/proximoIdMaquina.txt", "w");//ABRE O FICHEIRO PARA ESCRITA
        fprintf(arquivo, "%d", idMaquina + 1);//SALVA O NOVO ID DA MAQUINA NO FICHEIRO
        fclose(arquivo);//FECHA O FICHEIRO
    }
    return idMaquina;//RETORNA O ID DA MAQUINA
}
Maquinas *AdicionarMaquina(Maquinas *maquinas, int tipo)
{
    int idMaquina;//VARIAVEL PARA ARMAZENAR O ID DA MAQUINA
    char descMaquina[100];//VARIAVEL PARA ARMAZENAR A DESCRIÇÃO DA MAQUINA
    float tempo;//VARIAVEL PARA ARMAZENAR O TEMPO DA MAQUINA

    system("cls");//LIMPA A TELA
    printf("||=======================================================||\n");
    printf("||                   INSERIR MAQUINA                     ||\n");
    printf("||=======================================================||\n");

    fflush(stdin);//LIMPA O BUFFER DO TECLADO
    printf("|| DIGITE O NOME DA MAQUINA: ");// INSERIR NOME DA MAQUINA ESTRUTURA
    scanf("%[^\n]s", descMaquina);//LÊ A DESCRIÇÃO DA MAQUINA
    fflush(stdin);//LIMPA O BUFFER DO TECLADO
    idMaquina = proximoIdMaquina();//CHAMA A FUNÇÃO PARA RETORNAR O PROXIMO ID DA MAQUINA

    if (tipo == 1)
    {
        //SE O TIPO FOR 1
        printf("INSIRA O TEMPO DE DURAÇÃO DA OPERAÇÃO: ");// INSERIR TEMPO DA MAQUINA ESTRUTURA
        scanf("%f", &tempo);//LÊ O TEMPO DA MAQUINA
    }
    else
    {
        //SE O TIPO FOR 2
        tempo = 0;//TEMPO DA MAQUINA COM 0
    }

    system("cls");//LIMPA A TELA
    maquinas = InserirInicioListaMaquinas(maquinas, idMaquina, descMaquina, tempo);//CHAMA A FUNÇÃO PARA INSERIR A MAQUINA NA LISTA
    return maquinas;//RETORNA A LISTA DE MAQUINAS
}
Maquinas *InserirInicioListaMaquinas(Maquinas *maquinas, int idMaquina, char descMaquina[100], float tempo)
{
    Maquinas *novaMaquina = (Maquinas *)malloc(sizeof(Maquinas));//ALOCA ESPACO NA MEMORIA PARA A NOVA MAQUINA
    novaMaquina->idMaquina = idMaquina;//INSERE O ID DA MAQUINA
    strcpy(novaMaquina->descMaquina, descMaquina);//INSERE A DESCRIÇÃO DA MAQUINA
    novaMaquina->tempo = tempo;//INSERE O TEMPO DA MAQUINA
    novaMaquina->seguinte = maquinas;//INSERE O PONTEIRO PARA O PROXIMO DA LISTA
    return novaMaquina;//RETORNA A LISTA DE MAQUINAS
}
void percorrerMaquinas(Maquinas *maquinas)
{
    Maquinas *listaDeMaquinas = maquinas;//VARIAVEL PARA ARMAZENAR A LISTA DE MAQUINAS AUXILIAR
    printf("||========================================================||\n");
    printf("||                  Listagem de Máquinas                  ||\n");
    printf("||========================================================||\n");
    while (listaDeMaquinas != NULL)
    {
        //ENQUANTO A LISTA DE MAQUINAS NÃO FOR VAZIA
        printf("\tID Máquina: %d\n", listaDeMaquinas->idMaquina);
        printf("\tNome da Máquina: %s\n", listaDeMaquinas->descMaquina);
        printf("\tTempo de duração da Operação: %.2f\n", listaDeMaquinas->tempo);
        if (listaDeMaquinas->seguinte != NULL)
        {
            printf("----------------------------------------------------------\n");
        }
        listaDeMaquinas = listaDeMaquinas->seguinte;//PROXIMO DA LISTA DE MAQUINAS
    }
    printf("||========================================================||\n");
    printf("\n\n");
}
void listarMaquinas(Maquinas *maquinas, Trabalhos *trabalhos)
{
    system("cls");//LIMPA A TELA
    Maquinas *listaDeMaquinas = maquinas;//VARIAVEL PARA ARMAZENAR A LISTA DE MAQUINAS AUXILIAR
    int opcao;//VARIAVEL PARA ARMAZENAR A OPÇÃO DO MENU
    int idMaquina;//VARIAVEL PARA ARMAZENAR O ID DA MAQUINA
    printf("||========================================================||\n");
    printf("||                  LISTAGEM DE MAQUINAS                  ||\n");
    printf("||========================================================||\n");
    while (listaDeMaquinas != NULL)
    {
        printf("\tID Máquina: %d\n", listaDeMaquinas->idMaquina);
        printf("\tNome da Máquina: %s\n", listaDeMaquinas->descMaquina);
        if (listaDeMaquinas->seguinte != NULL)
        {
            printf("----------------------------------------------------------\n");
        }
        listaDeMaquinas = listaDeMaquinas->seguinte;
    }
    printf("||========================================================||\n");
    printf("||                                                        ||\n");
    printf("|| 1 - ADICIONAR MAQUINA                                  ||\n");
    printf("|| 2 - EDITAR MAQUINA                                     ||\n");
    printf("|| 3 - REMOVER MAQUINA                                    ||\n");
    printf("|| 9 - VOLTAR                                             ||\n");
    printf("|| 0 - SAIR                                               ||\n");
    printf("||                                                        ||\n");
    printf("||========================================================||\n");
    printf("|| OPÇÃO: ");
    scanf("%d", &opcao);//LÊ A OPÇÃO DO MENU
    switch (opcao)
    {
    case 1:
        // ADICIONAR MAQUINA
        maquinas = AdicionarMaquina(maquinas, 0);//CHAMA A FUNÇÃO PARA ADICIONAR MAQUINA
        salvarFicheiroMaquinas(maquinas);//CHAMA A FUNÇÃO PARA SALVAR NO FICHEIRO DE MAQUINAS
        listarMaquinas(maquinas, trabalhos);//CHAMA A FUNÇÃO PARA LISTAR AS MAQUINAS
        break;
    case 2:
        // EDITAR MAQUINA
        printf("||========================================================||\n");
        printf("|| ID DA MAQUINA QUE PRETENDE EDITAR: ");
        scanf("%d", &idMaquina);//LÊ O ID DA MAQUINA
        maquinas = EditarMaquina(maquinas, idMaquina);//CHAMA A FUNÇÃO PARA EDITAR A MAQUINA
        salvarFicheiroMaquinas(maquinas);//CHAMA A FUNÇÃO PARA SALVAR NO FICHEIRO DE MAQUINAS
        listarMaquinas(maquinas, trabalhos);//CHAMA A FUNÇÃO PARA LISTAR AS MAQUINAS
        break;
    case 3:
        // REMOVER MAQUINA
        printf("||========================================================||\n");
        printf("|| ID DA MAQUINA QUE PRETENDE REMOVER: ");
        scanf("%d", &idMaquina);//LÊ O ID DA MAQUINA
        maquinas = DeleteMaquina(maquinas, idMaquina);//CHAMA A FUNÇÃO PARA REMOVER A MAQUINA
        salvarFicheiroMaquinas(maquinas);//CHAMA A FUNÇÃO PARA SALVAR NO FICHEIRO DE MAQUINAS
        listarMaquinas(maquinas, trabalhos);//CHAMA A FUNÇÃO PARA LISTAR AS MAQUINAS
        break;
    case 9:
        // VOLTAR AO MENU PRINCIPAL
        menuPrincipal(trabalhos);//CHAMA A FUNÇÃO PARA VOLTAR AO MENU PRINCIPAL
        break;
    case 0:
        exit(0);//SAI DO PROGRAMA
        break;
    default:
        // MENSAGEM DE ERRO
        printf("||========================================================||\n");
        printf("||                 OPÇÃO INVÁLIDA                         ||\n");
        printf("||========================================================||\n");
        system("pause");
        listarMaquinas(maquinas, trabalhos);//CHAMA A FUNÇÃO PARA LISTAR AS MAQUINAS
        break;
    }
}
Maquinas *EditarMaquina(Maquinas *maquinas, int idMaquina)
{
    int found = 0;//VARIAVEL PARA VERIFICAR SE A MAQUINA FOI ENCONTRADA
    system("cls");//LIMPA A TELA
    Maquinas *listaDeMaquinas = maquinas;//VARIAVEL PARA ARMAZENAR A LISTA DE MAQUINAS AUXILIAR
    while (listaDeMaquinas != NULL)
    {
        if (listaDeMaquinas->idMaquina == idMaquina)
        {
            // SE A MAQUINA FOR ENCONTRADA
            found = 1;//MAQUINA ENCONTRADA
            printf("||========================================================||\n");
            printf("||                     EDITAR MAQUINA                     ||\n");
            printf("||========================================================||\n");
            printf("\tID Maquina: %d\n", listaDeMaquinas->idMaquina);
            printf("\tNome da Maquina: %s\n", listaDeMaquinas->descMaquina);
            printf("||========================================================||\n");
            printf("|| NOVO NOME DA MAQUINA:");
            scanf("%s", listaDeMaquinas->descMaquina);//LÊ O NOVO NOME DA MAQUINA
        }

        listaDeMaquinas = listaDeMaquinas->seguinte;//PASSAR PARA A PROXIMA MAQUINA
    }
    if (found == 0)
    {
        // SE A MAQUINA NÃO FOR ENCONTRADA
        printf("||========================================================||\n");
        printf("||              ID DA MAQUINA NÃO ENCONTRADO              ||\n");
        printf("||========================================================||\n");
        system("pause");
    }
    return maquinas;//RETORNA A LISTA DE MAQUINAS ATUALIZADA
}
Maquinas *DeleteMaquina(Maquinas *maquinas, int idMaquina)
{
    system("cls");//LIMPA A TELA
    Maquinas *nodoAtual = maquinas;//VARIAVEL PARA ARMAZENAR A LISTA DE MAQUINAS ATUAL
    Maquinas *nodoAnterior;//VARIAVEL PARA ARMAZENAR A LISTA DE MAQUINAS ANTERIOR
    int found = 0;//VARIAVEL PARA VERIFICAR SE A MAQUINA FOI ENCONTRADA
    if (nodoAtual->idMaquina == idMaquina)
    {
        // SE A MAQUINA FOR ENCONTRADA NA PRIMEIRA POSIÇÃO
        found = 1;//MAQUINA ENCONTRADA
        maquinas = nodoAtual->seguinte;//ATUALIZA A LISTA DE MAQUINAS
        free(nodoAtual);//LIBERTA A MEMORIA
    }
    else
    {
        // SE A MAQUINA NÃO FOR ENCONTRADA NA PRIMEIRA POSIÇÃO
        nodoAnterior = maquinas;//ATUALIZA A LISTA DE MAQUINAS
        nodoAtual = nodoAnterior->seguinte;//ATUALIZA A LISTA DE MAQUINAS ATUAL
        while ((nodoAtual != NULL) && (nodoAtual->idMaquina != idMaquina))
        {
            // ATÉ A MAQUINA FOR ENCONTRADA OU ATÉ A LISTA DE MAQUINAS ACABAR
            nodoAnterior = nodoAtual;//ATUALIZA A LISTA DE MAQUINAS ANTERIOR COM A MAQUINA ATUAL
            nodoAtual = nodoAtual->seguinte;//ATUALIZA A LISTA DE MAQUINAS ATUAL COM A PROXIMA MAQUINA
        }
        if (nodoAtual != NULL)
        {
            // SE A MAQUINA FOR ENCONTRADA
            nodoAnterior->seguinte = nodoAtual->seguinte;//ATUALIZA A POSIÇÂO SEGUINTE DA LISTA DE MAQUINAS ANTERIOR COM A PROXIMA MAQUINA DA LISTA DE MAQUINAS ATUAL
            free(nodoAtual);//LIBERTA A MEMORIA
            found = 1;//MAQUINA ENCONTRADA
        }
    }

    if (found == 0)
    {
        // SE A MAQUINA NÃO FOR ENCONTRADA
        system("cls");//LIMPA A TELA
        printf("||========================================================||\n");
        printf("||               ID DA MAQUINA NÃO ENCONTRADO             ||\n");
        printf("||========================================================||\n");
        system("pause");
    }else{
        // SE A MAQUINA FOR ENCONTRADA
        system("cls");//LIMPA A TELA
        printf("||========================================================||\n");
        printf("||               MAQUINA REMOVIDA COM SUCESSO             ||\n");
        printf("||========================================================||\n");
        system("pause");
    }
    return maquinas;//RETORNA A LISTA DE MAQUINAS ATUALIZADA
}

Trabalhos *AdicionarMaquinaOperacao(Trabalhos *trabalhos, int idOperacao, int idTrabalho)
{
    system("cls");//LIMPA A TELA
    Maquinas *listaDeMaquinas = NULL;//VARIAVEL PARA ARMAZENAR A LISTA DE MAQUINAS
    listaDeMaquinas = lerFicheiroMaquinas(listaDeMaquinas);//LÊ O FICHEIRO DE MAQUINAS
    Maquinas *listaDeMaquinasAux = listaDeMaquinas;//VARIAVEL PARA ARMAZENAR A LISTA DE MAQUINAS AUXILIAR

    Trabalhos *listaDeTrabalhos = trabalhos;//VARIAVEL PARA ARMAZENAR A LISTA DE TRABALHOS AUXILIAR
    printf("||========================================================||\n");
    printf("||           LISTAGEM DE MAQUINAS DISPONIVEIS             ||\n");
    printf("||========================================================||\n");
    while (listaDeMaquinas != NULL)
    {
        printf("\tID Máquina: %d\n", listaDeMaquinas->idMaquina);
        printf("\tNome da Máquina: %s\n", listaDeMaquinas->descMaquina);
        if (listaDeMaquinas->seguinte != NULL)
        {
            printf("----------------------------------------------------------\n");
        }
        listaDeMaquinas = listaDeMaquinas->seguinte;//PASSAR PARA A PROXIMA MAQUINA
    }
    printf("||========================================================||\n");
    printf("|| ID DA MAQUINA QUE PRETENDE ADICIONAR: ");
    int idMaquina;//VARIAVEL PARA ARMAZENAR O ID DA MAQUINA
    int found = 0;//VARIAVEL PARA VERIFICAR SE A MAQUINA FOI ENCONTRADA
    scanf("%d", &idMaquina);//LÊ O ID DA MAQUINA
    listaDeMaquinas = listaDeMaquinasAux;//ATUALIZA A LISTA DE MAQUINAS
    while (listaDeMaquinasAux != NULL)
    {
        //PERCORRE A LISTA DE MAQUINAS GLOBAIS ATÉ A MAQUINA SER ENCONTRADA OU ATÉ A LISTA DE MAQUINAS ACABAR
        if (listaDeMaquinasAux->idMaquina == idMaquina)
        {
            // SE A MAQUINA FOR ENCONTRADA
            found = 1;//MAQUINA ENCONTRADA
            while (listaDeTrabalhos != NULL)
            {
                if (listaDeTrabalhos->idTrabalho == idTrabalho)
                {
                    // SE O TRABALHO FOR ENCONTRADO
                    Operacoes *listaDeOperacoes = listaDeTrabalhos->operacoes;//VARIAVEL PARA ARMAZENAR A LISTA DE OPERAÇÕES DO TRABALHO
                    while (listaDeOperacoes != NULL)
                    {
                        if (listaDeOperacoes->idOperacao == idOperacao)
                        {
                            // SE A OPERAÇÃO FOR ENCONTRADA
                            Maquinas *maquinas = listaDeOperacoes->maquinas;//VARIAVEL PARA ARMAZENAR A LISTA DE MAQUINAS DA OPERAÇÃO
                            Maquinas *maquinasAux = maquinas;//VARIAVEL PARA ARMAZENAR A LISTA DE MAQUINAS AUXILIAR
                            while (maquinas != NULL)
                            {
                                if (maquinas->idMaquina == idMaquina)
                                {
                                    // SE A MAQUINA FOR ENCONTRADA, É PORQUE JÁ ESTÁ ADICIONADA NA OPERAÇÃO
                                    printf("||========================================================||\n");
                                    printf("||              MAQUINA JÁ ADICIONADA A OPERAÇÃO         ||\n");
                                    printf("||========================================================||\n");
                                    system("pause");
                                    found = 2;//MAQUINA JÁ ADICIONADA
                                    break;
                                }
                                maquinas = maquinas->seguinte;//PASSAR PARA A PROXIMA MAQUINA
                            }

                            if (found == 1)
                            {
                                // SE A MAQUINA NÃO FOR ENCONTRADA
                                maquinas = listaDeMaquinas;//ATUALIZA A LISTA DE MAQUINAS
                                while (maquinas != NULL)
                                {
                                    if (maquinas->idMaquina == idMaquina)
                                    {
                                        // SE A MAQUINA FOR ENCONTRADA
                                        Maquinas *maquinaNova = (Maquinas *)malloc(sizeof(Maquinas));//ALOCA A MEMORIA PARA A NOVA MAQUINA
                                        maquinaNova->idMaquina = idMaquina;//ATRIBUI O ID DA MAQUINA
                                        strcpy(maquinaNova->descMaquina, maquinas->descMaquina);//ATRIBUI A DESCRIÇÃO DA MAQUINA
                                        printf("|| INSIRA O TEMPO DE DURAÇÃO DA OPERAÇÃO: ");//PERGUNTA AO UTILIZADOR O TEMPO DE DURAÇÃO DA OPERAÇÃO
                                        scanf("%f", &maquinaNova->tempo);//LÊ O TEMPO DE DURAÇÃO DA OPERAÇÃO
                                        maquinaNova->seguinte = maquinasAux;//ATRIBUI A MAQUINA AO INICIO DA LISTA DE MAQUINAS
                                        maquinasAux = maquinaNova;//ATUALIZA A LISTA DE MAQUINAS AUXILIAR
                                    }
                                    maquinas = maquinas->seguinte;//PASSAR PARA A PROXIMA MAQUINA
                                }

                                listaDeOperacoes->maquinas = maquinasAux;//ATRIBUI A LISTA DE MAQUINAS AUXILIAR A LISTA DE MAQUINAS DA OPERAÇÃO
                            }
                        }
                        listaDeOperacoes = listaDeOperacoes->seguinte;//PASSAR PARA A PROXIMA OPERAÇÃO
                    }
                }
                listaDeTrabalhos = listaDeTrabalhos->seguinte;//PASSAR PARA O PROXIMO TRABALHO
            }
        }
        listaDeMaquinasAux = listaDeMaquinasAux->seguinte;//PASSAR PARA A PROXIMA MAQUINA DA LISTA GLOBAL
    }
    return trabalhos;//RETORNA A LISTA DE TRABALHOS ATUALIZADA
}
Trabalhos *EditarMaquinaOperacao(Trabalhos *trabalhos, int idTrabalho, int idOperacao, int idMaquina)
{
    int found = 0;//VARIAVEL PARA VERIFICAR SE A MAQUINA FOI ENCONTRADA
    system("cls");//LIMPA A TELA
    Trabalhos *listaDeTrabalhos = trabalhos;//VARIAVEL PARA ARMAZENAR A LISTA DE TRABALHOS
    while (listaDeTrabalhos != NULL)
    {
        if (listaDeTrabalhos->idTrabalho == idTrabalho)
        {
            // SE O TRABALHO FOR ENCONTRADO
            Operacoes *listaDeOperacoes = listaDeTrabalhos->operacoes;//VARIAVEL PARA ARMAZENAR A LISTA DE OPERAÇÕES DO TRABALHO
            while (listaDeOperacoes != NULL)
            {
                if (listaDeOperacoes->idOperacao == idOperacao)
                {
                    // SE A OPERAÇÃO FOR ENCONTRADA
                    Maquinas *listaDeMaquinas = listaDeOperacoes->maquinas;//VARIAVEL PARA ARMAZENAR A LISTA DE MAQUINAS DA OPERAÇÃO
                    while (listaDeMaquinas != NULL)
                    {
                        if (listaDeMaquinas->idMaquina == idMaquina)
                        {
                            // SE A MAQUINA FOR ENCONTRADA
                            found = 1;//MAQUINA ENCONTRADA
                            printf("||========================================================||\n");
                            printf("||                     EDITAR MAQUINA                     ||\n");
                            printf("||========================================================||\n");
                            printf("\tID Máquina: %d\n", listaDeMaquinas->idMaquina);
                            printf("\tNome da Máquina: %s\n", listaDeMaquinas->descMaquina);
                            printf("\tTempo de duração da Operação: %f\n", listaDeMaquinas->tempo);
                            printf("||========================================================||\n");
                            printf("|| NOVO TEMPO DE DURAÇÃO DA OPERAÇÃO: ");//PERGUNTA AO UTILIZADOR O TEMPO DE DURAÇÃO DA OPERAÇÃO
                            scanf("%f", &listaDeMaquinas->tempo);//LÊ O TEMPO DE DURAÇÃO DA OPERAÇÃO
                        }
                        listaDeMaquinas = listaDeMaquinas->seguinte;//PASSAR PARA A PROXIMA MAQUINA
                    }
                }
                listaDeOperacoes = listaDeOperacoes->seguinte;//PASSAR PARA A PROXIMA OPERAÇÃO
            }
        }
        listaDeTrabalhos = listaDeTrabalhos->seguinte;//PASSAR PARA O PROXIMO TRABALHO
    }
    if (found == 0)
    {
        // SE A MAQUINA NÃO FOR ENCONTRADA
        printf("||========================================================||\n");
        printf("||               ID DA MAQUINA NÃO ENCONTRADO             ||\n");
        printf("||========================================================||\n");
        system("pause");
    }
    else if (found == 1)
    {
        // SE A MAQUINA FOR ENCONTRADA
        printf("||========================================================||\n");
        printf("||                      TEMPO EDITADO                     ||\n");
        printf("||========================================================||\n");
        system("pause");
    }
    return trabalhos;//RETORNA A LISTA DE TRABALHOS ATUALIZADA
}
Trabalhos *DeleteMaquinaOperacao(Trabalhos *trabalhos, int idOperacao, int idTrabalho, int idMaquina)
{
    int found = 0;//VARIAVEL PARA VERIFICAR SE A MAQUINA FOI ENCONTRADA
    Trabalhos *listaDeTrabalhos = trabalhos;//VARIAVEL PARA ARMAZENAR A LISTA DE TRABALHOS
    while (listaDeTrabalhos != NULL)
    {
        if (listaDeTrabalhos->idTrabalho == idTrabalho)
        {
            // SE O TRABALHO FOR ENCONTRADO
            Operacoes *listaDeOperacoes = listaDeTrabalhos->operacoes;//VARIAVEL PARA ARMAZENAR A LISTA DE OPERAÇÕES DO TRABALHO
            while (listaDeOperacoes != NULL)
            {
                if (listaDeOperacoes->idOperacao == idOperacao)
                {
                    // SE A OPERAÇÃO FOR ENCONTRADA
                    Maquinas *nodoAtual = listaDeOperacoes->maquinas;//VARIAVEL PARA ARMAZENAR A MAQUINA ATUAL
                    Maquinas *nodoAnterior;//VARIAVEL PARA ARMAZENAR A MAQUINA ANTERIOR
                    if (nodoAtual->idMaquina == idMaquina)
                    {
                        // SE A MAQUINA FOR A PRIMEIRA DA LISTA
                        listaDeOperacoes->maquinas = nodoAtual->seguinte;//ATUALIZA A LISTA DE MAQUINAS DA OPERAÇÃO
                        free(nodoAtual);//LIBERTA A MEMORIA DA MAQUINA
                        found = 1;//MAQUINA ENCONTRADA
                    }
                    else
                    {
                        // SE A MAQUINA NÃO FOR A PRIMEIRA DA LISTA
                        nodoAnterior = listaDeOperacoes->maquinas; //ATUALIZA A MAQUINA ANTERIOR
                        nodoAtual = nodoAnterior->seguinte; //ATUALIZA A MAQUINA ATUAL
                        while ((nodoAtual != NULL) && (nodoAtual->idMaquina != idMaquina))
                        {
                            // ATÉ A MAQUINA SER ENCONTRADA
                            nodoAnterior = nodoAtual;//ATUALIZA A MAQUINA ANTERIOR
                            nodoAtual = nodoAtual->seguinte;//ATUALIZA A MAQUINA ATUAL
                        }
                        if (nodoAtual != NULL)
                        {
                            // SE A MAQUINA FOR ENCONTRADA
                            nodoAnterior->seguinte = nodoAtual->seguinte;//ATUALIZA A LISTA DE MAQUINAS ANTERIOR NA POSIÇÃO SEGUINTE  COM A POSIÇÃO SEGUINTE DA MAQUINA ATUAL
                            free(nodoAtual);//LIBERTA A MEMORIA DA MAQUINA
                            found = 1;//MAQUINA ENCONTRADA
                        }
                    }
                }
                listaDeOperacoes = listaDeOperacoes->seguinte;//PASSAR PARA A PROXIMA OPERAÇÃO
            }
        }
        listaDeTrabalhos = listaDeTrabalhos->seguinte;//PASSAR PARA O PROXIMO TRABALHO
    }

    if (found == 0)
    {
        // SE A MAQUINA NÃO FOR ENCONTRADA
        system("cls");//LIMPA A TELA
        printf("||========================================================||\n");
        printf("||              ID DA MAQUINA NÃO ENCONTRADO              ||\n");
        printf("||========================================================||\n");
        system("pause");
    }else{
        // SE A MAQUINA FOR ENCONTRADA
        system("cls");//LIMPA A TELA
        printf("||========================================================||\n");
        printf("||               MAQUINA REMOVIDA COM SUCESSO             ||\n");
        printf("||========================================================||\n");
        system("pause");
    }
    return trabalhos;//RETORNA A LISTA DE TRABALHOS ATUALIZADA
}
/*============= FIM - MAQUINAS =============*/

/*============= INICIO - OPERAÇÕES =============*/
int proximoIdOperacao()
{
    int idOperacao = 0;//VARIAVEL PARA ARMAZENAR O ID DA OPERAÇÃO
    FILE *arquivo = fopen("complemetFiles/proximoIdOperacao.txt", "r");//ABRE O FICHEIRO PARA LEITURA
    if (arquivo != NULL)
    {
        // SE O FICHEIRO FOR ENCONTRADO
        fscanf(arquivo, "%d", &idOperacao);//LÊ O ID DA OPERAÇÃO
        fclose(arquivo);//FECHA O FICHEIRO
        arquivo = fopen("complemetFiles/proximoIdOperacao.txt", "w");//ABRE O FICHEIRO PARA ESCRITA
        fprintf(arquivo, "%d", idOperacao + 1);//ESCREVE O ID DA OPERAÇÃO INCREMENTADO
        fclose(arquivo);//FECHA O FICHEIRO
    }
    return idOperacao;//RETORNA O ID DA OPERAÇÃO
}
Trabalhos *AdicionarOperacao(Trabalhos *trabalhos, int idTrabalho)
{
    int idOperacao;//VARIAVEL PARA ARMAZENAR O ID DA OPERAÇÃO
    char descOperacao[100];//VARIAVEL PARA ARMAZENAR A DESCRIÇÃO DA OPERAÇÃO
    Maquinas *maquinas = NULL;//VARIAVEL PARA ARMAZENAR A LISTA DE MAQUINAS DA OPERAÇÃO
    Operacoes *operacoes = NULL;//VARIAVEL PARA ARMAZENAR A LISTA DE OPERAÇÕES DO TRABALHO
    system("cls");//LIMPA A TELA
    printf("||=======================================================||\n");
    printf("||                   INSERIR OPERAÇÃO                    ||\n");
    printf("||=======================================================||\n");

    fflush(stdin);//LIMPA O BUFFER DO TECLADO
    printf("|| DIGITE O NOME DA OPERAÇÃO: ");//PERGUNTA AO UTILIZADOR A DESCRIÇÃO DA OPERAÇÃO
    scanf("%s", descOperacao);//LÊ A DESCRIÇÃO DA OPERAÇÃO

    idOperacao = proximoIdOperacao();//CHAMA A FUNÇÃO PARA O ID DA OPERAÇÃO

    Trabalhos *listaDeTrabalhos = trabalhos;//VARIAVEL PARA ARMAZENAR A LISTA DE TRABALHOS
    while (listaDeTrabalhos != NULL)
    {
        if (listaDeTrabalhos->idTrabalho == idTrabalho)
        {
            // SE O TRABALHO FOR ENCONTRADO
            operacoes = listaDeTrabalhos->operacoes;//ARMAZENA A LISTA DE OPERAÇÕES ATUAIS DO TRABALHO
            operacoes = InserirInicioListaOperacoes(operacoes, idOperacao, descOperacao, maquinas);//CHAMA A FUNÇÃO PARA INSERIR A OPERAÇÃO NA LISTA DE OPERAÇÕES
            listaDeTrabalhos->operacoes = operacoes;//ATUALIZA A LISTA DE OPERAÇÕES DO TRABALHO
        }
        listaDeTrabalhos = listaDeTrabalhos->seguinte;//PASSAR PARA O PROXIMO TRABALHO
    }
    return trabalhos;//RETORNA A LISTA DE TRABALHOS ATUALIZADA
}
Operacoes *InserirInicioListaOperacoes(Operacoes *operacoes, int idOperacao, char descOperacao[100], Maquinas *maquinas)
{
    Operacoes *novaOperacao = (Operacoes *)malloc(sizeof(Operacoes));//ALOCA A MEMORIA PARA A NOVA OPERAÇÃO
    novaOperacao->idOperacao = idOperacao;//ATRIBUI O ID DA OPERAÇÃO
    strcpy(novaOperacao->descOperacao, descOperacao);//ATRIBUI A DESCRIÇÃO DA OPERAÇÃO
    novaOperacao->maquinas = maquinas;//ATRIBUI A LISTA DE MAQUINAS DA OPERAÇÃO
    novaOperacao->seguinte = operacoes;//NOVA OPERAÇÃO APONTA PARA A OPERAÇÃO ANTERIOR
    return novaOperacao;//RETORNA A NOVA OPERAÇÃO
}
void percorrerOperacoes(Operacoes *operacoes)
{
    Operacoes *listaDeOperacoes = operacoes;//VARIAVEL PARA ARMAZENAR A LISTA DE OPERAÇÕES
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
            listaDeOperacoes->maquinas = listaDeOperacoes->maquinas->seguinte;//PASSAR PARA A PROXIMA MAQUINA
        }
        if (listaDeOperacoes->seguinte != NULL)
        {
            printf("----------------------------------------------------------\n");
        }
        listaDeOperacoes = listaDeOperacoes->seguinte;//PASSAR PARA A PROXIMA OPERAÇÃO
    }
    printf("||========================================================||\n");
    printf("\n\n");
}
void listarOperacao(Trabalhos *trabalhos, int idOperacao, int idTrabalho)
{
    system("cls");//LIMPA A TELA
    int found = 0;//VARIAVEL PARA VERIFICAR SE A OPERAÇÃO FOI ENCONTRADA
    int opcao;//VARIAVEL PARA ARMAZENAR A OPÇÃO DO UTILIZADOR
    int idMaquina;//VARIAVEL PARA ARMAZENAR O ID DA MAQUINA
    Trabalhos *listaDeTrabalhos = trabalhos;//VARIAVEL PARA ARMAZENAR A LISTA DE TRABALHOS
    while (listaDeTrabalhos != NULL)
    {
        if (listaDeTrabalhos->idTrabalho == idTrabalho)
        {
            // SE O TRABALHO FOR ENCONTRADO
            printf("||========================================================||\n");
            printf("||                       OPERAÇÃO                         ||\n");
            printf("||========================================================||\n");
            /*
                printf("\tID Trabalho: %d\n", listaDeTrabalhos->idTrabalho);
                printf("\tNome do Trabalho: %s\n", listaDeTrabalhos->descTrabalho);
                printf("\tOperações do Trabalho: \n");
             */
            Operacoes *listaDeOperacoes = listaDeTrabalhos->operacoes;//VARIAVEL PARA ARMAZENAR A LISTA DE OPERAÇÕES
            while (listaDeOperacoes != NULL)
            {
                if (listaDeOperacoes->idOperacao == idOperacao)
                {
                    // SE A OPERAÇÃO FOR ENCONTRADA
                    found = 1;//OPERAÇÃO ENCONTRADA
                    printf("\tID Operação: %d\n", listaDeOperacoes->idOperacao);
                    printf("\tNome da Operação: %s\n", listaDeOperacoes->descOperacao);
                    printf("\tMáquinas Operação: \n");
                    Maquinas *listaDeMaquinas = listaDeOperacoes->maquinas;//VARIAVEL PARA ARMAZENAR A LISTA DE MAQUINAS
                    while (listaDeMaquinas != NULL)
                    {
                        printf("\t\tID Máquina: %d\n", listaDeMaquinas->idMaquina);
                        printf("\t\tNome da Máquina: %s\n", listaDeMaquinas->descMaquina);
                        printf("\t\tTempo de duração da Operação: %.2f\n", listaDeMaquinas->tempo);
                        printf("\t\t------------------------\n");
                        listaDeMaquinas = listaDeMaquinas->seguinte;//PASSAR PARA A PROXIMA MAQUINA
                    }

                    printf("\t------------------------\n");
                }
                listaDeOperacoes = listaDeOperacoes->seguinte;//PASSAR PARA A PROXIMA OPERAÇÃO
            }
        }
        listaDeTrabalhos = listaDeTrabalhos->seguinte;//PASSAR PARA A PROXIMO TRABALHO
    }
    if (found == 0)
    {
        // SE A OPERAÇÃO NÃO FOR ENCONTRADA
        system("cls");//LIMPA A TELA
        printf("||========================================================||\n");
        printf("||              ID DE OPERAÇÃO NÃO ENCONTRADO             ||\n");
        printf("||========================================================||\n");
        system("pause");
        listarTrabalho(trabalhos, idTrabalho);//VOLTA AO MENU DE TRABALHOS
    }
    printf("||========================================================||\n");
    printf("||                                                        ||\n");
    printf("|| 1 - ADICIONAR MAQUINA                                  ||\n");
    printf("|| 2 - EDITAR MAQUINA                                     ||\n");
    printf("|| 3 - REMOVER MAQUINA                                    ||\n");
    printf("|| 9 - VOLTAR                                             ||\n");
    printf("|| 0 - SAIR                                               ||\n");
    printf("||                                                        ||\n");
    printf("||========================================================||\n");
    printf("|| OPÇÃO: ");//PERGUNTA AO UTILIZADOR A OPÇÃO
    scanf("%d", &opcao);//LÊ A OPÇÃO
    switch (opcao)
    {
    case 1:
        // ADICIONAR MAQUINA
        trabalhos = AdicionarMaquinaOperacao(trabalhos, idOperacao, idTrabalho);//CHAMA A FUNÇÃO PARA ADICIONAR MAQUINA A OPERAÇÃO
        salvarFicheiro(trabalhos);//CHAMA A FUNÇÃO PARA SALVAR NO FICHEIRO
        listarOperacao(trabalhos, idOperacao, idTrabalho);//VOLTA AO MENU DE OPERAÇÕES
        break;
    case 2:
        // EDITAR MAQUINA
        printf("||========================================================||\n");
        printf("|| ID DA MAQUINA QUE PRETENDE EDITAR: ");//PERGUNTA AO UTILIZADOR O ID DA MAQUINA QUE PRETENDE EDITAR
        scanf("%d", &idMaquina);//LÊ O ID DA MAQUINA
        trabalhos = EditarMaquinaOperacao(trabalhos, idTrabalho, idOperacao, idMaquina);//CHAMA A FUNÇÃO PARA EDITAR A MAQUINA
        salvarFicheiro(trabalhos);//CHAMA A FUNÇÃO PARA SALVAR NO FICHEIRO
        listarOperacao(trabalhos, idOperacao, idTrabalho);//VOLTA AO MENU DE OPERAÇÕES
        break;
    case 3:
        // REMOVER MAQUINA
        printf("||========================================================||\n");
        printf("|| ID DA MAQUINA QUE PRETENDE REMOVER: ");//PERGUNTA AO UTILIZADOR O ID DA MAQUINA QUE PRETENDE REMOVER
        scanf("%d", &idMaquina);//LÊ O ID DA MAQUINA
        trabalhos = DeleteMaquinaOperacao(trabalhos, idOperacao, idTrabalho, idMaquina);//CHAMA A FUNÇÃO PARA REMOVER A MAQUINA
        salvarFicheiro(trabalhos);//CHAMA A FUNÇÃO PARA SALVAR NO FICHEIRO
        listarOperacao(trabalhos, idOperacao, idTrabalho);//VOLTA AO MENU DE OPERAÇÕES
        break;
    case 9:
        // VOLTAR
        listarTrabalho(trabalhos, idTrabalho);//VOLTA AO MENU DE TRABALHOS
        break;
    case 0:
        exit(0);//SAIR
        break;
    default:
        // SE A OPÇÃO NÃO FOR VALIDA
        printf("||========================================================||\n");
        printf("||                 OPÇÃO INVÁLIDA                         ||\n");
        printf("||========================================================||\n");
        system("pause");
        listarOperacao(trabalhos, idOperacao, idTrabalho);//VOLTA AO MENU DE OPERAÇÕES
        break;
    }
}
Trabalhos *EditarOperacao(Trabalhos *trabalhos, int idTrabalho, int idOperacao)
{
    int found = 0;//VARIAVEL PARA VERIFICAR SE A OPERAÇÃO FOI ENCONTRADA
    system("cls");//LIMPA A TELA
    Trabalhos *listaDeTrabalhos = trabalhos;//VARIAVEL PARA ARMAZENAR A LISTA DE TRABALHOS
    while (listaDeTrabalhos != NULL)
    {
        if (listaDeTrabalhos->idTrabalho == idTrabalho)
        {
            // SE O TRABALHO ENCONTRADO
            Operacoes *listaDeOperacoes = listaDeTrabalhos->operacoes;//VARIAVEL PARA ARMAZENAR A LISTA DE OPERAÇÕES
            while (listaDeOperacoes != NULL)
            {
                if (listaDeOperacoes->idOperacao == idOperacao)
                {
                    // SE A OPERAÇÃO ENCONTRADA
                    found = 1;//OPERAÇÃO ENCONTRADA
                    printf("||========================================================||\n");
                    printf("||                     EDITAR OPERAÇÃO                    ||\n");
                    printf("||========================================================||\n");
                    printf("\tID Operação: %d\n", listaDeOperacoes->idOperacao);
                    printf("\tNome da Operação: %s\n", listaDeOperacoes->descOperacao);
                    printf("||========================================================||\n");
                    printf("|| NOVO NOME DA OPERAÇÃO:");//PERGUNTA AO UTILIZADOR O NOVO NOME DA OPERAÇÃO
                    scanf("%s", listaDeOperacoes->descOperacao);//LÊ O NOVO NOME DA OPERAÇÃO
                }

                listaDeOperacoes = listaDeOperacoes->seguinte;//PROXIMA OPERAÇÃO
            }
        }

        listaDeTrabalhos = listaDeTrabalhos->seguinte;//PROXIMO TRABALHO
    }
    if (found == 0)
    {
        // SE A OPERAÇÃO NÃO FOR ENCONTRADA
        printf("||========================================================||\n");
        printf("||              ID DE OPERAÇÃO NÃO ENCONTRADO             ||\n");
        printf("||========================================================||\n");
        system("pause");
    }
    return trabalhos;//RETORNA A LISTA DE TRABALHOS ATUALIZADA
}
Trabalhos *DeleteOperacao(Trabalhos *trabalhos, int idOperacao, int idTrabalho)
{
    int found = 0;//VARIAVEL PARA VERIFICAR SE A OPERAÇÃO FOI ENCONTRADA
    Trabalhos *listaDeTrabalhos = trabalhos;//VARIAVEL PARA ARMAZENAR A LISTA DE TRABALHOS
    while (listaDeTrabalhos != NULL)
    {
        if (listaDeTrabalhos->idTrabalho == idTrabalho)
        {
            // SE O TRABALHO ENCONTRADO
            Operacoes *nodoAtual = listaDeTrabalhos->operacoes;//VARIAVEL PARA ARMAZENAR O TRABALHO ATUAL
            Operacoes *nodoAnterior;//VARIAVEL PARA ARMAZENAR O ANTERIOR O TRABALHO
            if(nodoAtual != NULL){
                if (nodoAtual->idOperacao == idOperacao)
                {
                    // SE A OPERAÇÃO ENCONTRADA NA PRIMEIRO POSIÇÃO
                    listaDeTrabalhos->operacoes = nodoAtual->seguinte;//ATUALIZA A LISTA DE OPERAÇÕES 
                    free(nodoAtual);//LIBERTA A MEMORIA
                    found = 1;//OPERAÇÃO ENCONTRADA
                }
                else
                {
                    nodoAnterior = listaDeTrabalhos->operacoes; //ATUAILIZA O ANTERIOR
                    nodoAtual = nodoAnterior->seguinte;         //ATUALIZA O ATUAL
                    while ((nodoAtual != NULL) && (nodoAtual->idOperacao != idOperacao))
                    {
                        // ATÉ A OPERAÇÃO ENCONTRADA
                        nodoAnterior = nodoAtual;//ATUALIZA O ANTERIOR
                        nodoAtual = nodoAtual->seguinte;//ATUALIZA O ATUAL
                    }
                    if (nodoAtual != NULL)
                    {
                        // SE A OPERAÇÃO ENCONTRADA
                        nodoAnterior->seguinte = nodoAtual->seguinte;//LISTA DE OPERAÇÕES ANTERIOR APONTA PARA A PROXIMA OPERAÇÃO DA LISTA ATUAL
                        free(nodoAtual);//LIBERTA A MEMORIA
                        found = 1;//OPERAÇÃO ENCONTRADA
                    }
                }
            }
        }
        listaDeTrabalhos = listaDeTrabalhos->seguinte;//PROXIMO TRABALHO
    }

    if (found == 0)
    {
        // SE A OPERAÇÃO NÃO FOR ENCONTRADA
        system("cls");//LIMPA A TELA
        printf("||========================================================||\n");
        printf("||              ID DE OPERAÇÃO NÃO ENCONTRADO             ||\n");
        printf("||========================================================||\n");
        system("pause");
    }else{
        // SE A OPERAÇÃO FOR ENCONTRADA
        system("cls");//LIMPA A TELA
        printf("||========================================================||\n");
        printf("||              OPERAÇÃO REMOVIDA COM SUCESSO             ||\n");
        printf("||========================================================||\n");
        system("pause");
    }

    return trabalhos;//RETORNA A LISTA DE TRABALHOS ATUALIZADA
}
/*============= FIM - OPERAÇÕES =============*/

/*============= INICIO - TRABALHOS =============*/
int proximoIdTrabalho()
{
    int idTrabalho = 0;//VARIAVEL PARA ARMAZENAR O ID DO TRABALHO
    FILE *arquivo = fopen("complemetFiles/proximoIdTrabalho.txt", "r");//ABRE O FICHEIRO PARA LEITURA
    if (arquivo != NULL)
    {
        // SE O FICHEIRO FOI ABERTO
        fscanf(arquivo, "%d", &idTrabalho);//LÊ O ID DO TRABALHO
        fclose(arquivo);//FECHA O FICHEIRO
        arquivo = fopen("complemetFiles/proximoIdTrabalho.txt", "w");//ABRE O FICHEIRO PARA ESCRITA
        fprintf(arquivo, "%d", idTrabalho + 1);//ATUALIZA O ID DO TRABALHO INCREMENTANDO-O
        fclose(arquivo);//FECHA O FICHEIRO
    }
    return idTrabalho;//RETORNA O ID DO TRABALHO
}
Trabalhos *AdicionarTrabalho(Trabalhos *trabalhos)
{
    int idTrabalho;//VARIAVEL PARA ARMAZENAR O ID DO TRABALHO
    char descTrabalho[100];//VARIAVEL PARA ARMAZENAR A DESCRIÇÃO DO TRABALHO
    Operacoes *operacoes = NULL;//VARIAVEL PARA ARMAZENAR A LISTA DE OPERAÇÕES
    system("cls");//LIMPA A TELA
    printf("||=======================================================||\n");
    printf("||                    INSERIR TRABALHO                   ||\n");
    printf("||=======================================================||\n");

    fflush(stdin);//LIMPA O BUFFER DO TECLADO
    // INSERIR NOME DO TRABALHO
    printf("|| DIGITE O NOME DO TRABALHO: ");//PERGUNTA AO UTILIZADOR O NOME DO TRABALHO
    scanf("%s", descTrabalho);//LÊ O NOME DO TRABALHO
    fflush(stdin);//LIMPA O BUFFER DO TECLADO

    idTrabalho = proximoIdTrabalho();//CHAMA A FUNÇÃO PARA O ID DO TRABALHO

    system("cls");//LIMPA A TELA
    trabalhos = InserirInicioListaTrabalhos(trabalhos, idTrabalho, descTrabalho, operacoes);//CHAMA A FUNÇÃO PARA INSERIR O TRABALHO NA LISTA
    return trabalhos;//RETORNA A LISTA DE TRABALHOS ATUALIZADA
}
Trabalhos *InserirInicioListaTrabalhos(Trabalhos *trabalhos, int idTrabalho, char descTrabalho[100], Operacoes *operacoes)
{
    Trabalhos *novoTrabalho = (Trabalhos *)malloc(sizeof(Trabalhos));//ALOCA ESPACO PARA A NOVA LISTA DE TRABALHOS
    novoTrabalho->idTrabalho = idTrabalho;//ATRIBUI O ID DO TRABALHO
    strcpy(novoTrabalho->descTrabalho, descTrabalho);//ATRIBUI A DESCRIÇÃO DO TRABALHO
    novoTrabalho->operacoes = operacoes;//ATRIBUI A LISTA DE OPERAÇÕES
    novoTrabalho->seguinte = trabalhos;//ATRIBUI A PROXIMO TRABALHO COM A LISTA DE TRABALHOS ATUAL
    return novoTrabalho;//RETORNA A LISTA DE TRABALHOS ATUALIZADA
}
void percorrerTrabalhos(Trabalhos *trabalhos)
{
    Trabalhos *listaDeTrabalhos = trabalhos;//VARIAVEL PARA ARMAZENAR A LISTA DE TRABALHOS
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

        listaDeTrabalhos = listaDeTrabalhos->seguinte;//ATUALIZA A LISTA DE TRABALHOS
    }
    printf("||========================================================||\n");
}
void listarTrabalho(Trabalhos *trabalhos, int idTrabalho)
{
    system("cls");//LIMPA A TELA
    int found = 0;//VARIAVEL PARA VERIFICAR SE O TRABALHO FOI ENCONTRADO
    int opcao;//VARIAVEL PARA ARMAZENAR A OPÇÃO DO UTILIZADOR
    int idOperacao;//VARIAVEL PARA ARMAZENAR O ID DA OPERAÇÃO
    Trabalhos *listaDeTrabalhos = trabalhos;//VARIAVEL PARA ARMAZENAR A LISTA DE TRABALHOS
    while (listaDeTrabalhos != NULL)
    {
        if (listaDeTrabalhos->idTrabalho == idTrabalho)
        {
            //SE TRABALHO ENCONTRADO
            found = 1;//TRABALHO ENCONTRADO
            printf("||========================================================||\n");
            printf("||                       TRABALHO                         ||\n");
            printf("||========================================================||\n");
            printf("\tID Trabalho: %d\n", listaDeTrabalhos->idTrabalho);
            printf("\tNome do Trabalho: %s\n", listaDeTrabalhos->descTrabalho);

            printf("\tOperações do Trabalho: \n");
            Operacoes *listaDeOperacoes = listaDeTrabalhos->operacoes;//VARIAVEL PARA ARMAZENAR A LISTA DE OPERAÇÕES DO TRABALHO
            while (listaDeOperacoes != NULL)
            {
                printf("\t\tID Operação: %d\n", listaDeOperacoes->idOperacao);
                printf("\t\tNome da Operação: %s\n", listaDeOperacoes->descOperacao);
                /*
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
                */
                printf("\t\t------------------------\n");
                listaDeOperacoes = listaDeOperacoes->seguinte;//ATUALIZA A LISTA DE OPERAÇÕES
            }
        }
        listaDeTrabalhos = listaDeTrabalhos->seguinte;//PROXIMO TRABALHO
    }
    if (found == 0)
    {
        //SE NÃO ENCONTRADO
        system("cls");//LIMPA A TELA
        printf("||========================================================||\n");
        printf("||              ID DE TRABALHO NÃO ENCONTRADO             ||\n");
        printf("||========================================================||\n");
        system("pause");
        menuTrabalhos(trabalhos);//VOLTA AO MENU DE TRABALHOS
    }
    printf("||========================================================||\n");
    printf("||                                                        ||\n");
    printf("|| 1 - VER OPERAÇÃO                                       ||\n");
    printf("|| 2 - ADICIONAR OPERAÇÃO                                 ||\n");
    printf("|| 3 - EDITAR NOME OPERAÇÃO                               ||\n");
    printf("|| 4 - REMOVER OPERAÇÃO                                   ||\n");
    printf("|| 9 - VOLTAR                                             ||\n");
    printf("|| 0 - SAIR                                               ||\n");
    printf("||                                                        ||\n");
    printf("||========================================================||\n");
    printf("|| OPÇÃO: ");//OPÇÃO DO UTILIZADOR
    scanf("%d", &opcao);//LÊ A OPÇÃO DO UTILIZADOR
    switch (opcao)
    {
    case 1:
        // VER OPERAÇÃO
        printf("||========================================================||\n");
        printf("|| ID DA OPERAÇÃO QUE PRETENDE VER: ");//ID DA OPERAÇÃO QUE PRETENDE VER
        scanf("%d", &idOperacao);//LÊ O ID DA OPERAÇÃO QUE PRETENDE VER
        listarOperacao(trabalhos, idOperacao, idTrabalho);//LISTA A OPERAÇÃO
        break;
    case 2:
        // ADICIONAR OPERAÇÃO
        trabalhos = AdicionarOperacao(trabalhos, idTrabalho);//CHAAMOS A FUNÇÃO DE ADICIONAR OPERAÇÃO
        salvarFicheiro(trabalhos);//SALVA NO FICHEIRO
        listarTrabalho(trabalhos, idTrabalho);//VOLTA AO MENU
        break;
    case 3:
        printf("||========================================================||\n");
        printf("|| ID DA OPERAÇÃO QUE PRETENDE EDITAR: ");//ID DA OPERAÇÃO QUE PRETENDE EDITAR
        scanf("%d", &idOperacao);//LÊ O ID DA OPERAÇÃO QUE PRETENDE EDITAR
        trabalhos = EditarOperacao(trabalhos, idTrabalho, idOperacao);//CHAMA A FUNÇÃO DE EDITAR OPERAÇÃO
        salvarFicheiro(trabalhos);//SALVA NO FICHEIRO
        listarTrabalho(trabalhos, idTrabalho);//VOLTA AO MENU
        break;
    case 4:
        printf("||========================================================||\n");
        printf("|| ID DA OPERAÇÃO QUE PRETENDE REMOVER: ");//ID DA OPERAÇÃO QUE PRETENDE REMOVER
        scanf("%d", &idOperacao);//LÊ O ID DA OPERAÇÃO QUE PRETENDE REMOVER
        DeleteOperacao(trabalhos, idOperacao, idTrabalho);//CHAMA A FUNÇÃO DE REMOVER OPERAÇÃO
        salvarFicheiro(trabalhos);//SALVA NO FICHEIRO
        listarTrabalho(trabalhos, idTrabalho);//VOLTA AO MENU
        break;
    case 9:
        // VOLTAR
        menuTrabalhos(trabalhos);//VOLTA AO MENU DE TRABALHOS
        break;
    case 0:
        exit(0);//SAIR
        break;
    default:
        // ERRO
        printf("||========================================================||\n");
        printf("||                 OPÇÃO INVÁLIDA                         ||\n");
        printf("||========================================================||\n");
        system("pause");
        listarTrabalho(trabalhos, idTrabalho);//VOLTA AO MENU
        break;
    }
}
Trabalhos *EditarTrabalho(Trabalhos *trabalhos, int idTrabalho)
{
    int found = 0;//VARIAVEL PARA VERIFICAR SE ENCONTROU O TRABALHO
    system("cls");//LIMPA A TELA
    Trabalhos *listaDeTrabalhos = trabalhos;//VARIAVEL PARA ARMAZENAR A LISTA DE TRABALHOS
    while (listaDeTrabalhos != NULL)
    {
        if (listaDeTrabalhos->idTrabalho == idTrabalho)
        {
            //SE ENCONTROU O TRABALHO
            found = 1;//TRABALHO ENCONTRADO
            printf("||========================================================||\n");
            printf("||                     EDITAR TRABALHO                    ||\n");
            printf("||========================================================||\n");
            printf("\tID Trabalho: %d\n", listaDeTrabalhos->idTrabalho);
            printf("\tNome do Trabalho: %s\n", listaDeTrabalhos->descTrabalho);
            printf("||========================================================||\n");
            printf("|| NOVO NOME DO TRABALHO:");//NOVO NOME DO TRABALHO
            scanf("%s", listaDeTrabalhos->descTrabalho);//LÊ O NOME DO TRABALHO
        }

        listaDeTrabalhos = listaDeTrabalhos->seguinte;//PROXIMO TRABALHO
    }
    if (found == 0)
    {
        //SE NÃO ENCONTRADO
        printf("||========================================================||\n");
        printf("||              ID DE TRABALHO NÃO ENCONTRADO             ||\n");
        printf("||========================================================||\n");
        system("pause");
    }
    return trabalhos;//RETORNA A LISTA DE TRABALHOS
}
Trabalhos *DeleteTrabalho(Trabalhos *trabalhos, int idTrabalho)
{
    system("cls");//LIMPA A TELA
    Trabalhos *nodoAtual = trabalhos;//VARIAVEL PARA ARMAZENAR O NODO ATUAL
    Trabalhos *nodoAnterior;//VARIAVEL PARA ARMAZENAR O NODO ANTERIOR
    int found = 0;//VARIAVEL PARA VERIFICAR SE ENCONTROU O TRABALHO
    if (nodoAtual->idTrabalho == idTrabalho)
    {
        //SE ENCONTROU O TRABALHO NA PRIMEIRA POSIÇÃO DA LISTA
        found = 1;//TRABALHO ENCONTRADO
        trabalhos = nodoAtual->seguinte;//ATUALIZA A LISTA
        free(nodoAtual);//LIBERTA A MEMORIA
    }
    else
    {
        //SE NÃO ENCONTROU O TRABALHO NA PRIMEIRA POSIÇÃO DA LISTA
        nodoAnterior = trabalhos;//ATUALIZA O NODO ANTERIOR
        nodoAtual = nodoAnterior->seguinte;//ATUALIZA O NODO ATUAL
        while ((nodoAtual != NULL) && (nodoAtual->idTrabalho != idTrabalho))
        {
            //ENQUANTO O NODO ATUAL FOR DIFERENTE DO NODO A SER REMOVIDO E O NODO ATUAL FOR DIFERENTE DE NULL
            nodoAnterior = nodoAtual;//ATUALIZA O NODO ANTERIOR
            nodoAtual = nodoAtual->seguinte;//ATUALIZA O NODO ATUAL
        }
        if (nodoAtual != NULL)
        {
            //SE ENCONTROU O NODO A SER REMOVIDO
            nodoAnterior->seguinte = nodoAtual->seguinte;//ATUALIZA A PROXIMA POSIÇÂO DO NODO ANTERIOR PARA A PROXIMA POSIÇÂO DO NODO ATUAL
            free(nodoAtual);//LIBERA A MEMORIA
            found = 1;//TRABALHO ENCONTRADO
        }
    }

    if (found == 0)
    {
        //SE NÃO ENCONTROU O TRABALHO
        printf("||========================================================||\n");
        printf("||              ID DE TRABALHO NÃO ENCONTRADO             ||\n");
        printf("||========================================================||\n");
        system("pause");
    }
    else
    {
        //SE ENCONTROU O TRABALHO
        printf("||========================================================||\n");
        printf("||                 TRABALHO REMOVIDO                      ||\n");
        printf("||========================================================||\n");
        system("pause");
    }

    return trabalhos;//RETORNA A LISTA DE TRABALHOS
}
/*============= FIM - TRABALHOS =============*/

/*============= INICIO - LER FICHEIRO MAQUINAS =============*/
Maquinas *lerFicheiroMaquinas(Maquinas *maquinas)
{
    FILE *file = fopen("complemetFiles/maquinas.txt", "r");
    char c = 1;
    char keywords[][20] = {"", "NomeMaquina", "IDMaquina"};
    char descMaquina[100];
    int idMaquina;
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
                                sscanf(key, "%*[:\" ]%[a-zA-Z0-9]s", descMaquina);
                                // printf("\n\n%s -> %s\n", keywords[1], descMaquina);
                            }
                            else if (!(strcmp(key, keywords[2])))
                            {
                                // ID DO TRABALHO
                                fgets(key, sizeof(key), file);
                                sscanf(key, "%*[:\" ]%[0-9]s", &idMaquina);
                                // printf("%s -> %s\n", keywords[2], &idMaquina);
                                maquinas = InserirInicioListaMaquinas(maquinas, idMaquina - '0', descMaquina, 0);
                            }

                            // printf("Guardar Maquina\n");
                        }
                    }
                }
            }
        }
        fclose(file);
        return maquinas;
    }
}
/*============= FIM - LER FICHEIRO MAQUINAS =============*/

/*============= INICIO - ESCREVER FICHEIRO MAQUINAS =============*/
void salvarFicheiroMaquinas(Maquinas *maquinas)
{
    FILE *file = fopen("complemetFiles/maquinas.txt", "w");
    if (file == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
    }
    else
    {
        fprintf(file, "[\n");
        Maquinas *listaDeMaquinas = maquinas;
        while (listaDeMaquinas != NULL)
        {
            fprintf(file, "\t{\n");

            fprintf(file, "\t\t\"NomeMaquina\": \"%s\"\n", listaDeMaquinas->descMaquina);
            fprintf(file, "\t\t\"IDMaquina\": %d\n", listaDeMaquinas->idMaquina);
            listaDeMaquinas = listaDeMaquinas->seguinte;
            if (listaDeMaquinas != NULL)
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
/*============= FIM - ESCREVER FICHEIRO MAQUINAS =============*/

/*============= INICIO - LER FICHEIRO TRABALHOS =============*/
Trabalhos *lerFicheiro(Trabalhos *trabalhos)
{
    FILE *file = fopen("complemetFiles/jobs_formated.txt", "r");
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
/*============= FIM - LER FICHEIRO =============*/

/*============= INICIO - ESCREVER FICHEIRO =============*/
void salvarFicheiro(Trabalhos *trabalhos)
{
    FILE *file = fopen("complemetFiles/jobs_formated.txt", "w");
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
/*============= FIM - ESCREVER FICHEIRO =============*/

void menuTrabalhos(Trabalhos *trabalhos)
{
    system("cls");//LIMPAR A TELA
    int opcao;//VARIAVEL PARA A OPÇÃO ESCOLHIDA
    int idTrabalho;//VARIAVEL PARA O ID DO TRABALHO
    percorrerTrabalhos(trabalhos);//PERCORRER A LISTA DE TRABALHOS
    printf("||                                                        ||\n");
    printf("|| 1 - VER TRABALHO                                       ||\n");
    printf("|| 2 - ADICIONAR TRABALHO                                 ||\n");
    printf("|| 3 - EDITAR NOME TRABALHO                               ||\n");
    printf("|| 4 - REMOVER TRABALHO                                   ||\n");
    printf("|| 9 - VOLTAR                                             ||\n");
    printf("|| 0 - SAIR                                               ||\n");
    printf("||                                                        ||\n");
    printf("||========================================================||\n");
    printf("|| OPÇÃO: ");//OPÇÃO
    scanf("%d", &opcao);//LER A OPÇÃO
    switch (opcao)
    {
    case 1:
        // VER TRABALHO
        printf("||========================================================||\n");
        printf("|| ID DO TRABALHO QUE PRETENDE VER: ");//ID DO TRABALHO QUE PRETENDE VER
        scanf("%d", &idTrabalho);//LER O ID DO TRABALHO QUE PRETENDE VER
        listarTrabalho(trabalhos, idTrabalho);//LISTAR O TRABALHO
        break;
    case 2:
        // ADICIONAR TRABALHO
        trabalhos = AdicionarTrabalho(trabalhos);//ADICIONAR TRABALHO
        salvarFicheiro(trabalhos);//SALVAR NO FICHEIRO
        menuTrabalhos(trabalhos);//VOLTAR AO MENU
        break;
    case 3:
        // EDITAR NOME TRABALHO
        printf("||========================================================||\n");
        printf("|| ID DO TRABALHO QUE PRETENDE EDITAR: ");//ID DO TRABALHO QUE PRETENDE EDITAR
        scanf("%d", &idTrabalho);//LER O ID DO TRABALHO QUE PRETENDE EDITAR
        trabalhos = EditarTrabalho(trabalhos, idTrabalho);//EDITAR O TRABALHO
        salvarFicheiro(trabalhos);//SALVAR NO FICHEIRO
        menuTrabalhos(trabalhos);//VOLTAR AO MENU
        break;
    case 4:
        // REMOVER TRABALHO
        printf("||========================================================||\n");
        printf("|| ID DO TRABALHO QUE PRETENDE ELIMINAR: ");//ID DO TRABALHO QUE PRETENDE ELIMINAR
        scanf("%d", &idTrabalho);//LER O ID DO TRABALHO QUE PRETENDE ELIMINAR
        DeleteTrabalho(trabalhos, idTrabalho);//ELIMINAR O TRABALHO
        salvarFicheiro(trabalhos);//SALVAR NO FICHEIRO
        menuTrabalhos(trabalhos);//VOLTAR AO MENU
        break;
    case 9:
        // VOLTAR
        menuPrincipal(trabalhos);//VOLTAR AO MENU PRINCIPAL
        break;
    case 0:
        exit(0);//SAIR
        break;
    default:
        // ERRO
        printf("||========================================================||\n");
        printf("||                      OPÇÃO INVÁLIDA                    ||\n");
        printf("||========================================================||\n");
        system("pause");
        menuTrabalhos(trabalhos);//VOLTAR AO MENU
        break;
    }
}
void menuPrincipal(Trabalhos *trabalhos)
{
    system("cls");//LIMPAR A TELA
    int opcao;//VARIAVEL PARA A OPÇÃO ESCOLHIDA
    Maquinas *maquinas = NULL;//VARIAVEL PARA A LISTA DE MAQUINAS
    printf("||========================================================||\n");
    printf("||                      MENU PRINCIPAL                    ||\n");
    printf("||========================================================||\n");
    printf("||                                                        ||\n");
    printf("|| 1 - VER TRABALHOS                                      ||\n");
    printf("|| 2 - VER MAQUINAS                                       ||\n");
    printf("|| 3 - VER ESTATISTICAS DO TRABALHO 1                     ||\n");
    printf("|| 0 - SAIR                                               ||\n");
    printf("||                                                        ||\n");
    printf("||========================================================||\n");
    printf("|| OPÇÃO: ");//OPÇÃO
    scanf("%d", &opcao);//LER A OPÇÃO
    switch (opcao)
    {
    case 1:
        // VER TRABALHOS
        menuTrabalhos(trabalhos);//VER MENU TRABALHOS
        break;
    case 2:
        // VER MAQUINAS
        maquinas = lerFicheiroMaquinas(maquinas);//LER O FICHEIRO DE MAQUINAS
        listarMaquinas(maquinas, trabalhos);//LISTAR AS MAQUINAS
        break;
    case 3:
        // VER ESTATISTICAS DO TRABALHO
        EstatisticasJob1(trabalhos);//ESTATISTICAS DO TRABALHO 1
        break;
    case 0:
        exit(0);//SAIR
        break;
    default:
        // ERRO
        printf("||========================================================||\n");
        printf("||                 OPÇÃO INVÁLIDA                         ||\n");
        printf("||========================================================||\n");
        system("pause");
        menuPrincipal(trabalhos);//VOLTAR AO MENU PRINCIPAL
        break;
    }
}
void EstatisticasJob1(Trabalhos *trabalhos)
{
    system("cls");//LIMPAR A TELA
    printf("||========================================================||\n");
    printf("||                 MELHOR TEMPO DE EXECUÇÃO               ||\n"); // SEM FONES
    printf("||========================================================||\n");
    int idTrabalho = 1;//DECLARAR VARIAVEL PARA O ID DO TRABALHO
    float MelhorTempoTotalJob = 0;//DECLARAR VARIAVEL PARA O MELHOR TEMPO TOTAL DO TRABALHO
    Trabalhos *listaDeTrabalhos = trabalhos;//DECLARAR VARIAVEL PARA A LISTA DE TRABALHOS
    Maquinas *MaquinaAux = NULL;//DECLARAR VARIAVEL PARA A LISTA DE MAQUINAS
    while (listaDeTrabalhos != NULL)
    {
        if (listaDeTrabalhos->idTrabalho == idTrabalho)
        {
            // SE TRABALHO ENCONTRADO
            printf("\tNome do Trabalho: %s\n", listaDeTrabalhos->descTrabalho);
            Operacoes *listaDeOperacoes = listaDeTrabalhos->operacoes;//DECLARAR VARIAVEL PARA A LISTA DE OPERAÇÕES DO TRABALHO
            while (listaDeOperacoes != NULL)
            {
                MaquinaAux = NULL;//RESETAR A LISTA DE MAQUINAS
                Maquinas *listaDeMaquinas = listaDeOperacoes->maquinas;//DECLARAR VARIAVEL PARA A LISTA DE MAQUINAS DA OPERAÇÃO
                printf("\t\tOperacao: %s\n", listaDeOperacoes->descOperacao);
                while (listaDeMaquinas != NULL)
                {
                    if (MaquinaAux != NULL && MaquinaAux->tempo > listaDeMaquinas->tempo)
                    {
                        // SE A MAQUINA ATUAL FOR MAIOR QUE A MAQUINA AUXILIAR
                        MaquinaAux = listaDeMaquinas;//ATUALIZAR A MAQUINA AUXILIAR
                    }
                    else if (MaquinaAux == NULL)
                    {
                        // SE A MAQUINA AUXILIAR FOR NULA
                        MaquinaAux = listaDeMaquinas;//ATUALIZAR A MAQUINA AUXILIAR
                    }
                    // printf("Nome Maquina %s\n", listaDeMaquinas->descMaquina);
                    listaDeMaquinas = listaDeMaquinas->seguinte;//PROXIMA MAQUINA
                }
                MelhorTempoTotalJob += MaquinaAux->tempo;//SOMAR O TEMPO DA MELHOR MAQUINA AO TEMPO TOTAL
                printf("\t\tTempo: %.2f\n", MaquinaAux->tempo);
                printf("\t\t\tMaquina: %s\n", MaquinaAux->descMaquina);
                printf("\t\t------------------------\n");
                listaDeOperacoes = listaDeOperacoes->seguinte;//PROXIMA OPERAÇÃO
            }
            printf("||========================================================||\n");
            printf("||O MELHOR TEMPO DE EXECUÇÃO DO TRABALHO É: %.2f\n", MelhorTempoTotalJob);//MELHOR TEMPO DE EXECUÇÃO
            printf("||========================================================||\n");
        }
        listaDeTrabalhos = listaDeTrabalhos->seguinte;//PROXIMO TRABALHO
    }
    printf("\n\n");
    printf("||========================================================||\n");
    printf("||                  PIOR TEMPO DE EXECUÇÃO                ||\n");
    printf("||========================================================||\n");
    float PiorTempoTotalJob = 0;//DECLARAR VARIAVEL PARA O PIOR TEMPO TOTAL DO TRABALHO
    listaDeTrabalhos = trabalhos;//DECLARAR VARIAVEL PARA A LISTA DE TRABALHOS
    MaquinaAux = NULL;//DECLARAR VARIAVEL PARA A LISTA DE MAQUINAS
    while (listaDeTrabalhos != NULL)
    {
        if (listaDeTrabalhos->idTrabalho == idTrabalho)
        {
            // SE TRABALHO ENCONTRADO
            printf("\tNome do Trabalho: %s\n", listaDeTrabalhos->descTrabalho);
            Operacoes *listaDeOperacoes = listaDeTrabalhos->operacoes;//DECLARAR VARIAVEL PARA A LISTA DE OPERAÇÕES DO TRABALHO
            while (listaDeOperacoes != NULL)
            {
                MaquinaAux = NULL;//RESETAR A LISTA DE MAQUINAS
                Maquinas *listaDeMaquinas = listaDeOperacoes->maquinas;//DECLARAR VARIAVEL PARA A LISTA DE MAQUINAS DA OPERAÇÃO
                printf("\t\tOperacao: %s\n", listaDeOperacoes->descOperacao);
                while (listaDeMaquinas != NULL)
                {
                    if (MaquinaAux != NULL && MaquinaAux->tempo < listaDeMaquinas->tempo)
                    {
                        // SE A MAQUINA ATUAL FOR MENOR QUE A MAQUINA AUXILIAR
                        MaquinaAux = listaDeMaquinas;//ATUALIZAR A MAQUINA AUXILIAR
                    }
                    else if (MaquinaAux == NULL)
                    {
                        // SE A MAQUINA AUXILIAR FOR NULA
                        MaquinaAux = listaDeMaquinas;//ATUALIZAR A MAQUINA AUXILIAR
                    }
                    // printf("Nome Maquina %s\n", listaDeMaquinas->descMaquina);
                    listaDeMaquinas = listaDeMaquinas->seguinte;//PROXIMA MAQUINA
                }
                PiorTempoTotalJob += MaquinaAux->tempo;//SOMAR O TEMPO DA PIOR MAQUINA AO TEMPO TOTAL
                printf("\t\tTempo: %.2f\n", MaquinaAux->tempo);
                printf("\t\t\tMaquina: %s\n", MaquinaAux->descMaquina);
                printf("\t\t------------------------\n");
                listaDeOperacoes = listaDeOperacoes->seguinte;//PROXIMA OPERAÇÃO
            }
            printf("||========================================================||\n");
            printf("||O PIOR TEMPO DE EXECUÇÃO DO TRABALHO É: %.2f\n", PiorTempoTotalJob);//PIOR TEMPO DE EXECUÇÃO
            printf("||========================================================||\n");
        }
        listaDeTrabalhos = listaDeTrabalhos->seguinte;//PROXIMO TRABALHO
    }
    printf("\n\n");
    printf("||========================================================||\n");
    printf("||                MÉDIA DE TEMPO DE EXECUÇÃO              ||\n");
    printf("||========================================================||\n");
    float MediaTempoOperacao = 0;//DECLARAR VARIAVEL PARA A MÉDIA DE TEMPO DE EXECUÇÃO
    int countMaquinas = 0;//VARIAVEL PARA CONTAR AS MAQUINAS
    listaDeTrabalhos = trabalhos;//DECLARAR VARIAVEL PARA A LISTA DE TRABALHOS
    MaquinaAux = NULL;//DECLARAR VARIAVEL PARA A LISTA DE MAQUINAS
    while (listaDeTrabalhos != NULL)
    {
        if (listaDeTrabalhos->idTrabalho == idTrabalho)
        {
            // SE TRABALHO ENCONTRADO
            printf("\tNome do Trabalho: %s\n", listaDeTrabalhos->descTrabalho);
            Operacoes *listaDeOperacoes = listaDeTrabalhos->operacoes;//DECLARAR VARIAVEL PARA A LISTA DE OPERAÇÕES DO TRABALHO
            while (listaDeOperacoes != NULL)
            {
                MaquinaAux = NULL;//RESETAR A LISTA DE MAQUINAS
                countMaquinas = 0;//RESETAR A VARIAVEL PARA CONTAR AS MAQUINAS
                MediaTempoOperacao = 0;//RESETAR A VARIAVEL PARA A MÉDIA DE TEMPO DE EXECUÇÃO
                Maquinas *listaDeMaquinas = listaDeOperacoes->maquinas;//DECLARAR VARIAVEL PARA A LISTA DE MAQUINAS DA OPERAÇÃO
                printf("\t\tOperacao: %s\n", listaDeOperacoes->descOperacao);
                while (listaDeMaquinas != NULL)
                {
                    MediaTempoOperacao = MediaTempoOperacao + listaDeMaquinas->tempo;//SOMAR O TEMPO DA MAQUINA AO TEMPO TOTAL
                    countMaquinas++;//INCREMENTAR A VARIAVEL PARA CONTAR AS MAQUINAS
                    listaDeMaquinas = listaDeMaquinas->seguinte;//PROXIMA MAQUINA
                }
                MediaTempoOperacao = MediaTempoOperacao / countMaquinas;//DIVIDIR O TEMPO TOTAL PELO NUMERO DE MAQUINAS
                printf("\t\tTEMPO MÉDIO DE EXECUÇÃO DA OPERAÇÃO: %.2f\n", MediaTempoOperacao);//MÉDIA DE TEMPO DE EXECUÇÃO DA OPERAÇÂO
                printf("\t\t------------------------\n");
                listaDeOperacoes = listaDeOperacoes->seguinte;//PROXIMA OPERAÇÃO
            }
        }
        listaDeTrabalhos = listaDeTrabalhos->seguinte;//PROXIMO TRABALHO
    }
    printf("||========================================================||\n");
    system("pause");
    menuPrincipal(trabalhos);//VOLTA AO MENU PRINCIPAL
}

int main()
{
    // Define o valor das páginas de código UTF8 e default do Windows
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    // Define codificação como sendo UTF-8
    SetConsoleOutputCP(CPAGE_UTF8);

    Trabalhos *trabalhos = NULL;//INICIALIZAR A LISTA DE TRABALHOS
    trabalhos = lerFicheiro(trabalhos);//LER O FICHEIRO DE TRABALHOS
    menuPrincipal(trabalhos);//MENU PRINCIPAL

    // Retorna codificação padrão do Windows
    SetConsoleOutputCP(CPAGE_DEFAULT);
}