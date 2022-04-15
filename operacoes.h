int proximoIdOperacao();//RETORNA O PROXIMO ID DA OPERACAO
void percorrerOperacoes(Operacoes *operacoes);//PERCORRE A LISTA DE OPERACOES
void listarOperacao(Trabalhos *trabalhos, int idOperacao, int idTrabalho);//MENU DE OPERACOES
Trabalhos *AdicionarOperacao(Trabalhos *trabalhos, int idTrabalho);//ADICIONAR NOVO BLOCO DE MEMORIA PARA OPERACAO
Operacoes *InserirInicioListaOperacoes(Operacoes *operacoes, int idOperacao, char descOperacao[100], Maquinas *maquinas);//INSERIR OPERACAO NO INICIO DA LISTA
Trabalhos *EditarOperacao(Trabalhos *trabalhos, int idTrabalho, int idOperacao);//EDITAR OPERACAO
Trabalhos *DeleteOperacao(Trabalhos *trabalhos, int idOperacao, int idTrabalho);//REMOVER OPERACAO
void removerOperacoesTodas(Operacoes *operacoes);//REMOVER TODAS AS OPERACOES