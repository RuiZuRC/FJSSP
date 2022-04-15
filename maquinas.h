int proximoIdMaquina();//RETORNA O PROXIMO ID DA MAQUINA
void percorrerMaquinas(Maquinas *maquinas);//PERCORRE A LISTA DE MAQUINAS
void listarMaquinas(Maquinas *maquinas, Trabalhos *trabalhos);//MENU DE MAQUINAS
Maquinas *AdicionarMaquina(Maquinas *maquinas, int tipo);//ADICIONAR NOVO BLOCO DE MEMORIA PARA MAQUINA
Maquinas *InserirInicioListaMaquinas(Maquinas *maquinas, int idMaquina, char descMaquina[100], float tempo);//INSERIR MAQUINA NO INICIO DA LISTA
Maquinas *EditarMaquina(Maquinas *maquinas, int idMaquina);//EDITAR MAQUINA
Maquinas *DeleteMaquina(Maquinas *maquinas, int idMaquina);//REMOVER MAQUINA

Trabalhos *AdicionarMaquinaOperacao(Trabalhos *trabalhos, int idOperacao, int idTrabalho);//ADICIONAR MAQUINA NA OPERACAO
Trabalhos *EditarMaquinaOperacao(Trabalhos *trabalhos, int idTrabalho, int idOperacao, int idMaquina);//EDITAR MAQUINA DA OPERACAO
Trabalhos *DeleteMaquinaOperacao(Trabalhos *trabalhos, int idOperacao, int idTrabalho, int idMaquina);//REMOVER MAQUINA DA OPERACAO

Maquinas *lerFicheiroMaquinas(Maquinas *maquinas);//LER MAQUINAS DO FICHEIRO TXT
void salvarFicheiroMaquinas(Maquinas *maquinas);//GUARDAR MAQUINAS NO FICHEIRO TXT