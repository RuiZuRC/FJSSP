int proximoIdTrabalho();//RETORNA O PROXIMO ID DO TRABALHO
void percorrerTrabalhos(Trabalhos *trabalhos);//PERCORRE A LISTA DE TRABALHOS
void listarTrabalho(Trabalhos *trabalhos, int idTrabalho);//MENU DE TRABALHOS
Trabalhos *AdicionarTrabalho(Trabalhos *trabalhos);//ADICIONAR NOVO BLOCO DE MEMORIA PARA TRABALHO
Trabalhos *InserirInicioListaTrabalhos(Trabalhos *trabalhos, int idTrabalho, char descTrabalho[100], Operacoes *operacoes);//INSERIR TRABALHO NO INICIO DA LISTA
Trabalhos *EditarTrabalho(Trabalhos *trabalhos, int idTrabalho);//EDITAR TRABALHO
Trabalhos *DeleteTrabalho(Trabalhos *trabalhos, int idTrabalho);//REMOVER TRABALHO

Trabalhos *lerFicheiro(Trabalhos *trabalhos);//LER TRABALHOS DO FICHEIRO TXT
void salvarFicheiro(Trabalhos *trabalhos);//GUARDAR TRABALHOS NO FICHEIRO TXT

void menuTrabalhos(Trabalhos *trabalhos);//MENU DE TRABALHOS
void EstatisticasJob1(Trabalhos *trabalhos);//ESTATISTICAS DOS JOBS