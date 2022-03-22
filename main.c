#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//#include <locale.h>
#include <windows.h>

/* ================= STRUCT MAQUINA ================= */
typedef struct Maquina
{
    int idMaquina;
    char descMaquina[100];
    struct Maquina *seguinte;
} Maquinas;

Maquinas *inserirInicio(Maquinas *maquinas);                        // INSERIR NOVA MAQUINA NO INICIO DA LISTA
Maquinas *inserirFicheiro(Maquinas *maquinas);                      // INSERIR MAQUINAS NO FICHEIRO
Maquinas *lerFicheiro(Maquinas *maquinas);                          // LER MAQUINAS DO FICHEIRO
Maquinas *lerProximoNoFicheiro(Maquinas *maquinas, FILE *ficheiro); // LER PROXIMA MAQUINA DO FICHEIRO
void percorrerMaquinas(Maquinas *maquinas);                         // PERCORRER A LISTA
int proximoIdMaquina();                                             // GERAR O PROXIMO ID DA MAQUINA

/* ================= STRUCTS FOR JOBS ================= */
typedef struct MaquinaOperacao
{
    int idMaquina;
    float tempo;
    struct MaquinaOperacao *seguinte;
} MaquinasOperacao;

typedef struct Operacao
{
    int idOperacao;
    char descOperacao[100];
    int idTrabalho;
    MaquinasOperacao *maquinas;
    struct Operacao *seguinte;
} Operacoes;

typedef struct Trabalho
{
    int idTrabalho;
    char descTrabalho[100];
    Operacoes *operacoes;
    struct Trabalho *seguinte;
} Trabalhos;

/* ================= MAQUINAS JOBS ================= */
MaquinasOperacao *inserirInicioMaquinaOperacao(MaquinasOperacao *maquinasOperacao, Maquinas *maquinas); // INSERIR NOVA MAQUINA DE OPERACAO NO INICIO DA LISTA
MaquinasOperacao *inserirInicioMaquinaOperacao(MaquinasOperacao *maquinasOperacao, Maquinas *maquinas)
{
    MaquinasOperacao *novaMaquinaOperacao = (MaquinasOperacao *)malloc(sizeof(MaquinasOperacao));

    if (novaMaquinaOperacao != NULL)
    {
        percorrerMaquinas(maquinas);
        printf("Insira o ID da maquina que pretende disponibilizar para a operação: ");
        scanf("%d", &novaMaquinaOperacao->idMaquina);
        printf("Insira o tempo que a maquina demora a executar a operação: ");
        scanf("%f", &novaMaquinaOperacao->tempo);
        novaMaquinaOperacao->seguinte = maquinasOperacao;
        return novaMaquinaOperacao;
    }
    else
    {
        return maquinasOperacao;
    }
}

/* ================= TRABALHOS ================= */
Trabalhos *inserirInicioTrabalho(Trabalhos *trabalhos);
Trabalhos *inserirFicheiroTrabalhos(Trabalhos *trabalhos);
Trabalhos *lerFicheiroTrabalhos(Trabalhos *trabalhos);
Trabalhos *lerProximoNoFicheiroTrabalhos(Trabalhos *trabalhos, FILE *ficheiro);
void percorrerTrabalhos(Trabalhos *trabalhos);
int proximoIdTrabalho();
void verTrabalhos(Trabalhos *trabalhos);
void verTrabalho(Trabalhos *trabalhoEscolhido);

/* ================= OPERAÇÕES ================= */
void adicionarOperacao(Trabalhos *trabalhoEscolhido);
int proximoIdOperacao();
Operacoes *inserirInicioOperacao(Operacoes *operacoes, int idTrabalho);

/*
    DADOS
    0 - sem maquina
    outro numero - ocupado

    job 1 -> [1,1,1,1],
    job 2 -> [3,3,3,3,],
    job 3 -> [0,0,0,0],
    job 4 -> [0,0,0,0]
    job 5 -> [0],
    job 6 -> [0],
    job 7 -> [0],
    job 8 -> [0]

*/

/*

    JOB 1:
    {
        Nome: "OPERAÇÃO 1",
        Maquinas:[{
            Maquina: "Maquina 1",
            Tempo: "4"
        },
        {
            Maquina: "Maquina 3",
            Tempo: "5"
        }]
    },
    {
        Nome: "OPERAÇÃO 2",
        Maquinas:[{
            Maquina: "Maquina 2",
            Tempo: "4"
        },
        {
            Maquina: "Maquina 4",
            Tempo: "5"
        }]
    },
    {
        Nome: "OPERAÇÃO 3",
        Maquinas:[{
            Maquina: "Maquina 3",
            Tempo: "5"
        },
        {
            Maquina: "Maquina 5",
            Tempo: "6"
        }]
    },
    {
        Nome: "OPERAÇÃO 4",
        Maquinas:[{
            Maquina: "Maquina 4",
            Tempo: "5"
        },
        {
            Maquina: "Maquina 5",
            Tempo: "5"
        },
        {
            Maquina: "Maquina 6",
            Tempo: "4"
        },
        {
            Maquina: "Maquina 7",
            Tempo: "5"
        },
        {
            Maquina: "Maquina 8",
            Tempo: "9"
        }]
    },

 */

/* ================= MENUS ================= */
void menu();           // MENU PRINCIPAL
void gestaoMaquinas(); // GESTÃO DE MAQUINAS
void gestaoJobs();     // GESTÃO DE JOBS

int main()
{
    // Define o valor das páginas de código UTF8 e default do Windows
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();

    // Define codificação como sendo UTF-8
    SetConsoleOutputCP(CPAGE_UTF8);
    /*
        Maquinas *maquinas = NULL;
        MaquinasOperacao *maquinasOperacao = NULL;
        maquinas = lerFicheiro(maquinas); // LER MAQUINAS DO FICHEIRO
        maquinasOperacao = inserirInicioMaquinaOperacao(maquinasOperacao, maquinas);
        system("pause"); */
    /*
        Maquinas *maquinas = NULL;
        maquinas = inserirInicio(maquinas);
        maquinas = inserirInicio(maquinas);
        maquinas = inserirInicio(maquinas);
        inserirFicheiro(maquinas); //INSERIR MAQUINAS NO FICHEIRO
        maquinas = lerFicheiro(maquinas); // LER MAQUINAS DO FICHEIRO
        percorrerMaquinas(maquinas);      // PERCORRER A LISTA
        system("pause");
    */
    menu();
    // Retorna codificação padrão do Windows
    SetConsoleOutputCP(CPAGE_DEFAULT);
}
void menu()
{
    printf("MENU PRINCIPAL\n\n");
    printf("\t1 - Gestao de Maquinas\n");
    printf("\t2 - Gestao de Jobs\n");
    printf("\t0 - Sair\n");
    int opcao;
    printf("\n\nOpção: ");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
        system("cls");
        gestaoMaquinas();
        break;
    case 2:
        system("cls");
        gestaoJobs();
        break;
    case 0:
        exit(0);
        break;
    default:
        system("cls");
        printf("Opcao invalida\n");
        system("pause");
        system("cls");
        menu();
        break;
    }
}

/* ================= MAQUINAS ================= */
Maquinas *inserirInicio(Maquinas *maquinas)
{
    Maquinas *novaMaquina = (Maquinas *)malloc(sizeof(Maquinas)); // CRIAR NOVA "ESTRUTURA"

    // VERIFICAR SE A ESTRUTURA ESTÁ CRIADA
    if (novaMaquina != NULL)
    {
        char temp;
        scanf("%c", &temp); // temp statement to clear buffer
        // INSERIR NOME DA MAQUINA ESTRUTURA
        printf("Digite o nome da maquina: ");
        // scanf("%s", novaMaquina->descMaquina);//BREACKS WITH SPACES
        fgets(novaMaquina->descMaquina, 50, stdin);
        system("cls");
        // INSERIR ID DA MAQUINA ESTRUTURA
        int idMaquina = proximoIdMaquina();
        novaMaquina->idMaquina = idMaquina;
        novaMaquina->seguinte = maquinas;
        return novaMaquina;
    }
    else
    {
        return maquinas;
    }
}
Maquinas *inserirFicheiro(Maquinas *maquinas)
{

    FILE *ficheiro;
    ficheiro = fopen("complementFiles/maquinas.bin", "wb");
    if (ficheiro == NULL)
    {
        printf("Ficheiro nao encontrado");
    }
    else
    {
        while (maquinas != NULL)
        {
            // fprintf(ficheiro, "ID: %d\n NOME: %s\n", maquinas->idMaquina, maquinas->descMaquina);
            fseek(ficheiro, 0, SEEK_END);
            fwrite(maquinas, sizeof(*maquinas), 1, ficheiro);
            maquinas = maquinas->seguinte;
        }
        fclose(ficheiro);
    }
}
Maquinas *lerFicheiro(Maquinas *maquinas)
{
    FILE *ficheiro;
    ficheiro = fopen("complementFiles/maquinas.bin", "rb");
    if (ficheiro == NULL)
    {
        printf("Ficheiro nao encontrado");
        return maquinas;
    }
    else
    {

        fseek(ficheiro, 0, SEEK_END);
        long tamanhoFicheiro = ftell(ficheiro);
        rewind(ficheiro);
        int numeroMaquinas = (int)(tamanhoFicheiro / (sizeof(Maquinas)));
        for (int i = 0; i < numeroMaquinas; i++)
        {
            fseek(ficheiro, (sizeof(Maquinas) * (i)), SEEK_SET);
            maquinas = lerProximoNoFicheiro(maquinas, ficheiro);
        }
    }
    fclose(ficheiro);
    return maquinas;
}
Maquinas *lerProximoNoFicheiro(Maquinas *maquinas, FILE *ficheiro)
{
    if (maquinas == NULL)
    {
        Maquinas *novaMaquina = (Maquinas *)malloc(sizeof(Maquinas));
        fread(novaMaquina, sizeof(Maquinas), 1, ficheiro);
        novaMaquina->seguinte = NULL;
        maquinas = novaMaquina;
        return maquinas;
        // printf("ID: %d\n NOME: %s\n", maquinas->idMaquina, maquinas->descMaquina);
    }
    else
    {
        Maquinas *aux = maquinas;
        Maquinas *novaMaquina = (Maquinas *)malloc(sizeof(Maquinas));
        fread(novaMaquina, sizeof(Maquinas), 1, ficheiro);
        // printf("ID: %d\n NOME: %s\n", novaMaquina->idMaquina, novaMaquina->descMaquina);
        novaMaquina->seguinte = maquinas;
        return novaMaquina;
    }
}
void percorrerMaquinas(Maquinas *maquinas)
{
    Maquinas *listaDeMaquinas = maquinas;
    printf("**========================================================**\n");
    printf("\t\tListagem de Máquinas\n");
    printf("**======================================================**\n");
    while (listaDeMaquinas != NULL)
    {
        printf("\tID: %d \t  |\t Nome: %s\n", listaDeMaquinas->idMaquina, listaDeMaquinas->descMaquina);
        if (listaDeMaquinas->seguinte != NULL)
        {
            printf("----------------------------------------------------------\n");
        }
        listaDeMaquinas = listaDeMaquinas->seguinte;
    }
    printf("**======================================================**\n");
    printf("\n\n");
}
int proximoIdMaquina()
{
    int idMaquina = 0;
    FILE *arquivo = fopen("complementFiles/proximoIdMaquina.txt", "r");
    if (arquivo != NULL)
    {
        fscanf(arquivo, "%d", &idMaquina);
        fclose(arquivo);
        arquivo = fopen("complementFiles/proximoIdMaquina.txt", "w");
        fprintf(arquivo, "%d", idMaquina + 1);
        fclose(arquivo);
    }
    return idMaquina;
}
void gestaoMaquinas()
{
    Maquinas *maquinas = NULL;
    maquinas = lerFicheiro(maquinas);
    Maquinas *listaDeMaquinas = maquinas;
    printf("**======================================================**\n");
    printf("\t\tListagem de Máquinas\n");
    printf("**======================================================**\n");
    while (listaDeMaquinas != NULL)
    {
        printf("\tID: %d \t  |\t Nome: %s\n", listaDeMaquinas->idMaquina, listaDeMaquinas->descMaquina);
        if (listaDeMaquinas->seguinte != NULL)
        {
            printf("----------------------------------------------------------\n");
        }
        listaDeMaquinas = listaDeMaquinas->seguinte;
    }
    printf("**======================================================**\n");
    printf("\n\n");
    printf("*** AÇÕES ***\n\n");
    int opcao;
    printf("\t1 - Inserir Maquina\n");
    printf("\t2 - Remover Maquina\n");
    printf("\t3 - Alterar Maquina\n");
    printf("\t0 - Voltar\n");
    printf("\n\nOpção: ");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
        system("cls");
        maquinas = inserirInicio(maquinas);
        inserirFicheiro(maquinas);
        gestaoMaquinas();
        break;
    case 2:
        system("cls");
        // removerMaquina(maquinas);
        break;
    case 3:
        system("cls");
        // alterarMaquina(maquinas);
        break;
    case 0:
        system("cls");
        menu();
        break;
    default:
        system("cls");
        printf("Opcao invalida\n");
        system("pause");
        system("cls");
        gestaoMaquinas();
        break;
    }
    system("pause");
}

/* ================= TRABALHOS ================= */
void gestaoJobs()
{
    Trabalhos *trabalhos = NULL;
    trabalhos = lerFicheiroTrabalhos(trabalhos);
    percorrerTrabalhos(trabalhos); // LISTAR TRABALHOS
    printf("*** AÇÕES ***\n\n");
    printf("\t1 - Inserir Job\n");
    printf("\t2 - Alterar Job (+Em Falta+)\n");
    printf("\t3 - Remover Job (+Em Falta+)\n");
    printf("\t4 - Ver Job \n");
    printf("\t0 - Voltar\n");
    printf("\n\nOpção: ");
    int opcao;
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
        system("cls");
        trabalhos = inserirInicioTrabalho(trabalhos);
        // trabalhos = inserirInicioTrabalho(trabalhos);
        // percorrerTrabalhos(trabalhos);
        gestaoJobs();
        system("pause");
        break;
    case 2:
        system("cls");
        // alterarJob();
        break;
    case 3:
        system("cls");
        // removerJob();
        break;
    case 4:
        system("cls");
        verTrabalhos(trabalhos);
        break;
    case 0:
        system("cls");
        menu();
        break;
    default:
        system("cls");
        printf("Opcao invalida\n");
        system("pause");
        system("cls");
        gestaoJobs();
        break;
    }
}
Trabalhos *inserirInicioTrabalho(Trabalhos *trabalhos)
{
    Trabalhos *novoTrabalho = (Trabalhos *)malloc(sizeof(Trabalhos));
    if (novoTrabalho != NULL)
    {
        char temp;
        scanf("%c", &temp); // temp statement to clear buffer
        novoTrabalho->idTrabalho = proximoIdTrabalho();
        printf("Insira a descricao do trabalho: ");
        // scanf("%s", novoTrabalho->descTrabalho);
        fgets(novoTrabalho->descTrabalho, 100, stdin);
        // system("cls");
        novoTrabalho->operacoes = NULL;
        novoTrabalho->seguinte = trabalhos;
        inserirFicheiroTrabalhos(novoTrabalho);
        return novoTrabalho;
    }
    else
    {
        return trabalhos;
    }
}
Trabalhos *inserirFicheiroTrabalhos(Trabalhos *trabalhos)
{

    FILE *ficheiro;
    ficheiro = fopen("complementFiles/trabalhos.bin", "wb");
    if (ficheiro == NULL)
    {
        printf("Ficheiro nao encontrado");
    }
    else
    {
        while (trabalhos != NULL)
        {
            fseek(ficheiro, 0, SEEK_END);
            fwrite(trabalhos, sizeof(*trabalhos), 1, ficheiro);
            trabalhos = trabalhos->seguinte;
        }
        fclose(ficheiro);
    }
}
Trabalhos *lerFicheiroTrabalhos(Trabalhos *trabalhos)
{
    FILE *ficheiro;
    ficheiro = fopen("complementFiles/trabalhos.bin", "rb");
    if (ficheiro == NULL)
    {
        printf("Ficheiro nao encontrado");
        return trabalhos;
    }
    else
    {

        fseek(ficheiro, 0, SEEK_END);
        long tamanhoFicheiro = ftell(ficheiro);
        rewind(ficheiro);
        int numeroTrabalhos = (int)(tamanhoFicheiro / (sizeof(Trabalhos)));
        for (int i = 0; i < numeroTrabalhos; i++)
        {
            fseek(ficheiro, (sizeof(Trabalhos) * (i)), SEEK_SET);
            trabalhos = lerProximoNoFicheiroTrabalhos(trabalhos, ficheiro);
        }
    }
    fclose(ficheiro);
    return trabalhos;
}
Trabalhos *lerProximoNoFicheiroTrabalhos(Trabalhos *trabalhos, FILE *ficheiro)
{
    if (trabalhos == NULL)
    {
        Trabalhos *novoTrabalho = (Trabalhos *)malloc(sizeof(Trabalhos));
        fread(novoTrabalho, sizeof(Trabalhos), 1, ficheiro);
        novoTrabalho->seguinte = NULL;
        trabalhos = novoTrabalho;
        return trabalhos;
    }
    else
    {
        Trabalhos *aux = trabalhos;
        Trabalhos *novoTrabalho = (Trabalhos *)malloc(sizeof(Trabalhos));
        fread(novoTrabalho, sizeof(Trabalhos), 1, ficheiro);
        novoTrabalho->seguinte = trabalhos;
        return novoTrabalho;
    }
}
void percorrerTrabalhos(Trabalhos *trabalhos)
{
    printf("**======================================================**\n");
    printf("\t\tListagem de Jobs\n");
    printf("**======================================================**\n");
    Trabalhos *listaTrabalhos = trabalhos;
    while (listaTrabalhos != NULL)
    {
        printf("\tID: %d \t  |\t Descrição: %s\n", listaTrabalhos->idTrabalho, listaTrabalhos->descTrabalho);
        if (listaTrabalhos->seguinte != NULL)
        {
            printf("----------------------------------------------------------\n");
        }
        listaTrabalhos = listaTrabalhos->seguinte;
    }
    printf("**======================================================**\n");
    printf("\n\n");
}
int proximoIdTrabalho()
{
    int idTrabalho = 0;
    FILE *arquivo = fopen("complementFiles/proximoIdTrabalho.txt", "r");
    if (arquivo != NULL)
    {
        fscanf(arquivo, "%d", &idTrabalho);
        fclose(arquivo);
        arquivo = fopen("complementFiles/proximoIdTrabalho.txt", "w");
        fprintf(arquivo, "%d", idTrabalho + 1);
        fclose(arquivo);
    }
    return idTrabalho;
}
void verTrabalhos(Trabalhos *trabalhos)
{
    Trabalhos *trabalhoEscolhido = (Trabalhos *)malloc(sizeof(Trabalhos));
    int idTrabalho;
    bool found = false;
    percorrerTrabalhos(trabalhos);
    printf("*** AÇÕES ***\n\n");
    printf("Insira o ID do trabalho que pretende ver: ");
    scanf("%d", &idTrabalho);
    Trabalhos *listaTrabalhos = trabalhos;
    while (listaTrabalhos != NULL)
    {
        if (listaTrabalhos->idTrabalho == idTrabalho)
        {
            found = true;
            trabalhoEscolhido->operacoes = NULL;
            trabalhoEscolhido = listaTrabalhos;
            break;
        }
        listaTrabalhos = listaTrabalhos->seguinte;
    }
    if (found)
    {
        verTrabalho(trabalhoEscolhido);
    }
    else
    {
        system("cls");
        printf("Trabalho nao encontrado\n");
        system("pause");
        system("cls");
        verTrabalhos(trabalhos);
    }
}
void verTrabalho(Trabalhos *trabalhoEscolhido)
{

    system("cls");
    // printf("Trabalho encontrado!\n");
    printf("**======================================================**\n");
    printf("\tID: %d \t  |\t Descrição: %s\n", trabalhoEscolhido->idTrabalho, trabalhoEscolhido->descTrabalho);
    printf("**======================================================**\n");
    if(trabalhoEscolhido->operacoes != NULL){
            printf("**======================================================**\n");
            printf(" Listagem de Operações do Trabalho %s", trabalhoEscolhido->descTrabalho);
            printf("**======================================================**\n");
            //IMPRIME APENAS A 1º OPERACAO
            printf("-> %s\n", trabalhoEscolhido->operacoes->descOperacao);
    }
    printf("\n\n");
    printf("*** AÇÕES ***\n\n");
    printf("1 - Adicionar Operação (+Em Falta Adicionar a Ficheiro+)\n");
    printf("2 - Ver Operações (+Em Falta+)\n");
    printf("0 - Voltar\n");
    int opcao;
    printf("Opcão: ");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
        adicionarOperacao(trabalhoEscolhido);
        break;
    case 2:
        //verOperacoes(trabalhoEscolhido);
        break;
    case 0:

        break;
    default:
        printf("Opção inválida!\n");
        system("pause");
        verTrabalho(trabalhoEscolhido);
        break;
    }
}

/* ================= OPERAÇÕES ================= */

void adicionarOperacao(Trabalhos *trabalhoEscolhido)
{
    int idTrabalho = trabalhoEscolhido->idTrabalho;
    Operacoes *operacoes = NULL;
    operacoes = inserirInicioOperacao(operacoes, idTrabalho);
    trabalhoEscolhido->operacoes = operacoes;
    verTrabalho(trabalhoEscolhido);
    system("pause");           
}
int proximoIdOperacao(){
    int idOperacao = 0;
    FILE *arquivo = fopen("complementFiles/proximoIdOperacao.txt", "r");
    if (arquivo != NULL)
    {
        fscanf(arquivo, "%d", &idOperacao);
        fclose(arquivo);
        arquivo = fopen("complementFiles/proximoIdOperacao.txt", "w");
        fprintf(arquivo, "%d", idOperacao + 1);
        fclose(arquivo);
    }
    return idOperacao;
};
Operacoes *inserirInicioOperacao(Operacoes *operacoes, int idTrabalho){
    Operacoes *novaOperacao = (Operacoes *)malloc(sizeof(Operacoes)); // CRIAR NOVA "ESTRUTURA"
    // VERIFICAR SE A ESTRUTURA ESTÁ CRIADA
    if (novaOperacao != NULL)
    {
        system("cls");
        char temp;
        scanf("%c", &temp); // temp statement to clear buffer
        // INSERIR NOME DA MAQUINA ESTRUTURA
        printf("Digite o nome da Operação: ");
        fgets(novaOperacao->descOperacao, 100, stdin);
        system("cls");
        // INSERIR ID DA MAQUINA ESTRUTURA
        int idOperacao = proximoIdOperacao();
        novaOperacao->idTrabalho = idTrabalho;
        novaOperacao->idOperacao = idOperacao;
        novaOperacao->seguinte = operacoes;
        return novaOperacao;
    }else{
        printf("Erro ao criar estrutura!\n");
        system("pause");
        return operacoes;
    }
}