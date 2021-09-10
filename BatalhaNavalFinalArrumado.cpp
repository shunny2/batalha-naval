#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define AGUA '~'
#define BARCO '#'
#define DISPARO 'x'
#define ATINGIDO '$'
#define MAX 15

//Declaracoes de funcoes 
void Limpar_Tela(void);
void Limpar_Buffer(void);
void Iniciar_Tabuleiro(void);
void Imprime_Opcoes_De_Barcos(void);
void Imprime_Tabuleiro();
int Check_Barcos(int barco, char Matriz[MAX][MAX]);
void Dados_Do_Jogador(char Matriz[MAX][MAX]);
void Dados_Da_CPU(char Matriz[MAX][MAX]);
int Verificar_Round(int linha, int coluna, char Matriz[MAX][MAX]);
int Atirar(int linha, int coluna, char Matriz[MAX][MAX]);
void Verificar_Fim_Jogo();
void Turno_Do_Jogador();
void Turno_Da_Cpu();
void Rounds();
void Verificar_Fim_De_Jogo();
void Iniciar_Novo_Jogo();
void Guia_Jogo();
void Executar_Opcao_Menu(char opcao);
int Verificar_Barcos(int barco, int direcao, int linha, int coluna, char Matriz[MAX][MAX]);
int Verificar_Corveta(int direcao, int linha, int coluna, char Matriz[MAX][MAX]);
int Verificar_Submarino(int direcao, int linha, int coluna, char Matriz[MAX][MAX]);
int Verificar_Destroyer(int direcao, int linha, int coluna, char Matriz[MAX][MAX]);
int Verificar_Cruzador(int direcao, int linha, int coluna, char Matriz[MAX][MAX]);
int Verificar_PortaAvioes(int direcao, int linha, int coluna, char Matriz[MAX][MAX]);
int Verifica_Fragata(int direcaoDoBarco, int linha, int coluna, char Matriz[MAX][MAX]);
void GerarMenuPrincipalNovamente();
void Imprimir_Barcos(int barco, int direcaoDoBarco, int linha, int coluna, char Matriz[MAX][MAX]);//
void Imprimir_Corveta(int direcaoDoBarco, int linha, int coluna, char Matriz[MAX][MAX]);//
void Imprimir_Submarino(int direcaoDoBarco, int linha, int coluna, char Matriz[MAX][MAX]);//
void Imprimir_Destroyer(int direcaoDoBarco, int linha, int coluna, char Matriz[MAX][MAX]);//
void Imprimir_Cruzador(int direcaoDoBarco, int linha, int coluna, char Matriz[MAX][MAX]);//
void Imprimir_Fragata(int direcaoDoBarco, int linha, int coluna, char Matriz[MAX][MAX]);//
void Imprimir_PortaAvioes(int direcaoDoBarco, int linha, int coluna, char Matriz[MAX][MAX]);//
void Verificar_Fim_De_Jogo();

//Struct que define os barcos
struct Barco {
	int corveta;
	int submarino;
	int fragata;
	int destroyer;
	int cruzador;
	int portaAvioes;
};

typedef struct Barco barco;

//Tamanho do Tabuleiro:14x14
//Navios : Cada jogador possui 6 navios :
//• 1 corveta;
//• 1 submarino
//• 1 fragata
//• 1 destroyer
//• 1 cruzador
//• 1 porta-aviões

//Define a quantidade
barco num_de_barcos = { 1, 1, 1, 1, 1, 1 };
barco num_de_barcos_cpu = { 1, 1, 1, 1, 1, 1 };

//Criacao dos tabuleiros. Existem 3 pois foi o unico jeito que achamos para evitar um bug onde o tabulheiro sobreescrevia o outro
char TabuleiroJogador[MAX][MAX];
char TabuleiroCPU[MAX][MAX];
char TabuleiroRecriar[MAX][MAX];
int coordenada_Horizontal[MAX] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
int coordenada_Vertical[MAX] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14 };

//VETOR NOME DO JOGADOR. (PLAYER 1 = USUARIO E JOGADOR 2 = CPU).
char nome_jogador1[15] = "PLAYER 1";
char nome_jogador2[15] = "CPU";

//CONTA BARCOS OU SEJA LIMITE É 6 POR JOGO.
int contadorDeBarcos = 6;
int contadorDeBarcosCpu = 6;
int primeira_jogada = 1;

//VIDA DOS JOGADORES
int vidas_jogador = 23;
int vidas_cpu = 23;

//ACERTOS DE AMBOS PLAYERS
int cpu_acertou = 0;
int jogador_acertou = 0;

//FINAL DE JOGO E VENCEDOR
int fim_da_partida = 0;
int jogador_vence = 0;
int cpu_vence = 0;

// LIMPA A TELA ANTERIOR
void Limpar_Tela() {
	system("CLS");
};

//LIMPA O FLUXO (BUFFER)
void Limpar_Buffer() {
	fflush(stdin);
}

//INICIA OS 3 TABULEIROS
void Iniciar_Tabuleiro() {
	int i, j;

	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			TabuleiroJogador[i][j] = AGUA;
			TabuleiroCPU[i][j] = AGUA;
			TabuleiroRecriar[i][j] = AGUA;
		}
	}
}

//IMPRIMI QUAIS OPÇOES DE BARCOS EXISTENTES
void Imprime_Opcoes_De_Barcos() {
	printf("\t       **********************************\n");
	printf("\t       * >>>>  MOSTRANDO BARCOS!  <<<<  *\n");
	printf("\t       **********************************\n");
	if (num_de_barcos.corveta > 0) {
		printf("\t       * 1 - Corveta....... [1x2] (%d/1) *\n", num_de_barcos.corveta);
	}

	if (num_de_barcos.submarino > 0) {
		printf("\t       *                                *\n");
		printf("\t       * 2 - Submarino..... [1x3] (%d/1) *\n", num_de_barcos.submarino);
	}

	if (num_de_barcos.fragata > 0) {
		printf("\t       *                                *\n");
		printf("\t       * 3 - Fragata....... [1x3] (%d/1) *\n", num_de_barcos.fragata);
	}

	if (num_de_barcos.destroyer > 0) {
		printf("\t       *                                *\n");
		printf("\t       * 4 - Destroyer..... [1x4] (%d/1) *\n", num_de_barcos.destroyer);
	}

	if (num_de_barcos.cruzador > 0) {
		printf("\t       *                                *\n");
		printf("\t       * 5 - Cruzador...... [1x5] (%d/1) *\n", num_de_barcos.cruzador);
	}

	if (num_de_barcos.portaAvioes > 0) {
		printf("\t       *                                *\n");
		printf("\t       * 6 - Porta-Aviões.. [2x6] (%d/1) *\n", num_de_barcos.portaAvioes);
	}
	printf("\t       **********************************\n");
	printf("\n");
}

//IMPRIME O TABULEIRO INICIAL
void Imprime_Tabuleiro() {
	int i, j;
	//IMPRIME O NOME DO JOGADOR E DA CPU
	printf("\n\n");
	printf("\t       PLAYER 1: %s         ", nome_jogador1);
	printf("\t                        PLAYER 2: %s          \n", nome_jogador2);
	//IMPRIMI COLUNAS DO TABULEIRO
	printf("\t       ---------------------------------------------");
	printf("            ---------------------------------------------\n");

	printf("\t         |");
	for (i = 0; i < MAX - 1; i++) {
		printf("%3d", coordenada_Horizontal[i]);
	}
	printf("              |");
	for (i = 0; i < MAX - 1; i++) {
		printf("%3d", coordenada_Horizontal[i]);
	}
	//IMPRIMI LIINHAS DO TABULEIRO
	printf("\n\t       --+------------------------------------------");
	printf("            --+------------------------------------------\n");

	for (i = 1; i < MAX; i++) {
		printf("\t       %2c|", coordenada_Vertical[i - 1] + 64);
		for (j = 1; j < MAX; j++) {
			printf("  %c", TabuleiroJogador[i][j]);
		}
		printf("         ");
		printf("   %2c|", coordenada_Vertical[i - 1] + 64);
		for (j = 1; j < MAX; j++) {
			printf("  %c", TabuleiroRecriar[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

int Check_Barcos(int barco, char Matriz[MAX][MAX]) {
	switch (barco) {
	case 1:
		if (Matriz == TabuleiroJogador) {
			if (num_de_barcos.corveta == 0) {
				return 0;
			}
		}
		else {
			if (num_de_barcos_cpu.corveta == 0) {
				return 0;
			}
		}
		break;
	case 2:
		if (Matriz == TabuleiroJogador) {
			if (num_de_barcos.submarino == 0) {
				return 0;
			}
		}
		else {
			if (num_de_barcos_cpu.submarino == 0) {
				return 0;
			}
		}
		break;
	case 3:
		if (Matriz == TabuleiroJogador) {
			if (num_de_barcos.fragata == 0) {
				return 0;
			}
		}
		else {
			if (num_de_barcos_cpu.fragata == 0) {
				return 0;
			}
		}
		break;
	case 4:
		if (Matriz == TabuleiroJogador) {
			if (num_de_barcos.destroyer == 0) {
				return 0;
			}
		}
		else {
			if (num_de_barcos_cpu.destroyer == 0) {
				return 0;
			}
		}
		break;
	case 5:
		if (Matriz == TabuleiroJogador) {
			if (num_de_barcos.cruzador == 0) {
				return 0;
			}
		}
		else {
			if (num_de_barcos_cpu.cruzador == 0) {
				return 0;
			}
		}
		break;
	case 6:
		if (Matriz == TabuleiroJogador) {
			if (num_de_barcos.portaAvioes == 0) {
				return 0;
			}
		}
		else {
			if (num_de_barcos_cpu.portaAvioes == 0) {
				return 0;
			}
		}
		break;
	}
	return 1;
}

//Essa funcao coleta os dados do usuario sobre qual barco ele quer inserir no momento
void Dados_Do_Jogador(char Matriz[MAX][MAX]) {
	int barco, linha, coluna, direcaoDoBarco = 0;

	char letras;
	char op;

	do {
		Imprime_Opcoes_De_Barcos();
		printf("\t      -> Selecione um Barco: ");
		Limpar_Buffer();
		scanf("%d", &barco);

		while (barco <= 0 || barco > 6 || !Check_Barcos(barco, Matriz)) {
			printf("\t       ERRO! Este barco não existe. Informe um barco válido: ");
			getchar();
			scanf("%d", &barco);
		}
		getchar();
		printf("\t      -> Diga uma Direcao [h/v]: ");
		Limpar_Buffer();
		scanf("%c", &op);

		while (tolower(op) != 'h' && tolower(op) != 'v') {
			printf("\t       ERRO! Direção Inválida. Informe outra direção [h/v]: ");
			Limpar_Buffer();
			scanf("%c", &op);
		}

		(tolower(op) == 'h') ? (direcaoDoBarco = 1) : (direcaoDoBarco = 0);
		getchar();
		printf("\t      -> Insira uma Linha: ");
		Limpar_Buffer();
		scanf("%c", &letras);

		letras = tolower(letras);
		
		while (letras >= 112 || letras <= 96) {
			printf("\t       ERRO! Linha Inválida. Informe uma linha válida: ");
			Limpar_Buffer();
			scanf("%C", &letras);
		}

		linha = letras - 96;

		printf("\t      -> Insira uma Coluna: ");
		Limpar_Buffer();
		scanf("%d", &coluna);
		while (coluna >= MAX || coluna <= 0) {
			printf("\t        ERRO! Coluna Inválida. Informe uma coluna válida: ");
			Limpar_Buffer();
			scanf("%d", &coluna);
		}

		if (Verificar_Barcos(barco, direcaoDoBarco, linha, coluna, Matriz)) {
			Imprimir_Barcos(barco, direcaoDoBarco, linha, coluna, Matriz);
			Limpar_Tela();
			Imprime_Tabuleiro();
			contadorDeBarcos--;
			printf("\t       -> Jogador %s, seu barco foi alocado com sucesso!\n\n", nome_jogador1);
		}
		else {
			Limpar_Tela(); //SYSTEM CLS;
			Imprime_Tabuleiro();
			printf("\t       -> Erro, não foi possível alocar o seu barco. Jogador %s! Tente Novamente!\n\n", nome_jogador1);
		}
	} while (contadorDeBarcos);
}
//Funcao que utiliza a biblioteca MAth para usarmos a funcao RANDOM (rand())
void Dados_Da_CPU(char Matriz[MAX][MAX]) {
	int barco, linha, coluna, direcaoDoBarco = 0;

	//srand inicia os numeros random que vamos utilizar
	srand((unsigned)time(NULL));


	//Inseri todos os barcos da CPU aleatoriamente no mapa
	do {
		barco = (rand() % 6) + 1;
		while (!Check_Barcos(barco, Matriz)) {
			barco = (rand() % 6) + 1;
		}

		linha = (rand() % 14) + 1; //Numero random module 14 gera um numero random entre 1-14

		coluna = (rand() % 14) + 1;

		direcaoDoBarco = rand() % 2;


		//Verifica se nao ha conflito entre posicoes de barcos
		if (Verificar_Barcos(barco, direcaoDoBarco, linha, coluna, Matriz)) {
			Imprimir_Barcos(barco, direcaoDoBarco, linha, coluna, Matriz);
			contadorDeBarcosCpu--;
		}
	} while (contadorDeBarcosCpu);
}

//Funcao que verifica se o alvo foi atigindo
int Verificar_Round(int linha, int coluna, char Matriz[MAX][MAX]) {
	if (Matriz[linha][coluna] == DISPARO || Matriz[linha][coluna] == ATINGIDO) {
		return 0;
	}
	return 1;
}

//Funcao de disparo 
int Atirar(int linha, int coluna, char Matriz[MAX][MAX]) {
	if (Matriz == TabuleiroCPU) {
		if (Matriz[linha][coluna] == AGUA) {
			Matriz[linha][coluna] = DISPARO;
			TabuleiroRecriar[linha][coluna] = DISPARO;
			return 0;
		}
		else {
			Matriz[linha][coluna] = ATINGIDO;
			TabuleiroRecriar[linha][coluna] = ATINGIDO;
			vidas_cpu--;
			return 1;
		}
	}
	else {
		if (Matriz[linha][coluna] == AGUA) {
			Matriz[linha][coluna] = DISPARO;
			return 0;
		}
		else {
			Matriz[linha][coluna] = ATINGIDO;
			vidas_jogador--;
			return 1;
		}
	}
}

//Checa todo round se o jogo foi finalizado ou nao
void Verificar_Fim_Jogo() {
	if (vidas_jogador == 0 || vidas_cpu == 0) {
		fim_da_partida = 1;
		if (vidas_cpu == 0) {
			jogador_vence = 1;
		}
		else {
			cpu_vence = 1;
		}
	}
}

//inicia turno d jogador
void Turno_Do_Jogador() {
	int linha, coluna, jogada_ok = 0;

	Limpar_Tela();
	Imprime_Tabuleiro();

	//JOGADA DO JOGADOR.
	do {

		if (!primeira_jogada) {
			printf("\t       -> Jogador: ");
			//IF ELSE ternary
			(jogador_acertou) ? (printf("O BARCO DA CPU FOI ATINGIDO!!!\n")) : (printf("AGUA! VOCÊ ERROU!\n"));
			printf("\t       -> CPU: ");
			//IF ELSE ternary
			(cpu_acertou) ? (printf("O BARCO DO JOGADOR FOI ATINGIDO!!!\n")) : (printf("AGUA! VOCÊ ERROU!\n"));


			printf("\n\n\t        ----------Placar---------");
			printf("\n\t       | Vidas: %s = %d", nome_jogador1, vidas_jogador);
			printf("\n\t       | Vidas: CPU = %d", vidas_cpu);
		}
		else {
			primeira_jogada = 0;
		}

		printf("\n\n\t\t Partida Iniciada, sua vez de jogar. %s!\n\n", nome_jogador1);

		printf("\t      -> Insira uma Linha: ");
		Limpar_Buffer();
		scanf("%d", &linha);
		while (linha <= 0 || linha >= 15) {
			printf("\t       Informe uma linha válida, dentro dos limites do mapa!: ");
			Limpar_Buffer();
			scanf("%d", &linha);
		}

		printf("\t      -> Insira uma Coluna: ");
		Limpar_Buffer();
		scanf("%d", &coluna);
		while (coluna <= 0 || coluna >= 15) {
			printf("\t      Informe uma coluna válida, dentro dos limites do mapa!: ");
			Limpar_Buffer();
			scanf("%d", &coluna);
		}

		if (Verificar_Round(linha, coluna, TabuleiroCPU)) {
			if (Atirar(linha, coluna, TabuleiroCPU)) {
				Limpar_Tela();
				Imprime_Tabuleiro();
				jogador_acertou = 1;
			}
			else {
				Limpar_Tela();
				Imprime_Tabuleiro();
				jogador_acertou = 0;
			}
			jogada_ok = 1;
		}
		else {
			Limpar_Tela();
			Imprime_Tabuleiro();
			printf("\t       -> Jogada inválida! Você ja fez esta jogada. Faça outra jogada:\n\n");
			jogada_ok = 0;
		}

	} while (!jogada_ok);
}

//gera o round da CPU randomicamente
void Turno_Da_Cpu() {
	int linha, coluna, jogada_ok = 0;

	srand((unsigned)time(NULL));

	do {
		linha = (rand() % 14) + 1;

		coluna = (rand() % 14) + 1;

		if (Verificar_Round(linha, coluna, TabuleiroJogador)) {
			if (Atirar(linha, coluna, TabuleiroJogador)) {
				cpu_acertou = 1;
				//vidas_jogador--;
			}
			else {
				cpu_acertou = 0;
			}
			jogada_ok = 1;
		}
		else {
			jogada_ok = 0;
		}
	} while (!jogada_ok);
}


//Funcao que cicla entre os rounds da CPU e Usuario
void Rounds() {
	int turno = 1;

	do {
		if (turno) {
			Turno_Do_Jogador();
			turno = 0;
		}
		else {
			Turno_Da_Cpu();
			turno = 1;
		}
		Verificar_Fim_Jogo();
	} while (!fim_da_partida);

	Verificar_Fim_De_Jogo();
}


//Funcao que finaliza o jogo
void Verificar_Fim_De_Jogo() {
	Limpar_Tela();

	if (jogador_vence) {
		printf("\t\t\t\t******************************************\n");
		printf("\t\t\t\t*   PARABÉNS JOGADOR %s! Voce Venceu!!       *\n", nome_jogador1);
		printf("\t\t\t\t******************************************\n");

		//escreveNoRanking();
	}
	else {

		printf("\tJOGADOR %s. QUE PENA, VOCÊ PERDEU! \n", nome_jogador1);

	}

}
//funçao pra iniciar o jogo
void Iniciar_Novo_Jogo()
{
	Limpar_Tela();
	printf("************************\n");
	printf("*                      *\n");
	printf("*  JOGO INICIALIZADO!  *\n");
	printf("*                      *\n");
	printf("************************\n\n");
	printf("QUAL O SEU NICK, JOGADOR?: ");
	Limpar_Buffer();
	scanf("%[^\n]s", nome_jogador1);
	Limpar_Tela();

	Iniciar_Tabuleiro();
	Dados_Da_CPU(TabuleiroCPU);
	Imprime_Tabuleiro();
	Dados_Do_Jogador(TabuleiroJogador);
	Rounds();
}

//Funcao que abre o guia do jogo
void Guia_Jogo() {
	char opcao;


	printf("\n\t> Digite caracter [s] para voltar: ");

	do {
		Limpar_Buffer();
		scanf("%c", &opcao);

		if (opcao != 's') {
			printf("\n\t -> ERRO!!! Digite o caracter [s] para voltar: ");
		}
		else if (opcao == 's') {


			GerarMenuPrincipalNovamente();
		}

	} while (opcao != 's');
}

//Executa a opcao escolhida pelo usuario no menu principal
void Executar_Opcao_Menu(char opcao) {
	switch (opcao) {
	case '1':
		Iniciar_Novo_Jogo();
		break;
	case '2':
		Guia_Jogo();
		break;

	}
}


//Gera o menu principal
void GerarMenuPrincipal() {

	char verificar_opcao;
	char opcao;


	do {
		Limpar_Tela();

		printf("\n\n");
		printf("\t  *********************************\n");
		printf("\t  *          MENU INICIAL         *\n");
		printf("\t  ********************************* \t  **********************************************\n");
		printf("\t  *  (1) INICIAR JOGO             * \t  *   HENRIQUE - ALEXANDER - MATHEUS MISSACI   *\n");
		printf("\t  *  (2) INSTRUÇÕES DO JOGO       * \t  **********************************************\n");
		printf("\t  *  (3) HABILIDADES P/ BARCOS    * \t  *   ENGENHARIA DE SOFTWARE 2º SEMESTRE       *\n");
		printf("\t  *  (4) FINALIZAR JOGO           * \t  *   PROFESSORA MILENE UNIFAE                 *\n");
		printf("\t  ********************************* \t  **********************************************\n");
		printf("\t  *         BATALHA NAVAL         *\n");
		printf("\t  *********************************\n");
		printf("\n\t-> Digite uma das opções acima: ");
		Limpar_Buffer();
		scanf("%c", &opcao);

		while (opcao != '4' &&  opcao != '1' &&  opcao != '2' &&  opcao != '3') {
			printf("\t-> Digite uma opção válida! ");
			Limpar_Buffer();
			scanf("%c", &opcao);
		}
		if (opcao == '2')
		{
			printf("\n\n\t\tINFORMAÇÕES / AJUDA. \n\n");
			//Informações sobre como funciona e como jogar.
			printf("\t1- O jogo funciona da seguinte maneira, o jogador irá escolher onde deseja colocar o seu barco. \n");
			printf("\t2- O jogador irá escolher uma posição de 1 a 14 e de A até N. Exemplo: 5(linha) - F(coluna) \n");
			printf("\t3- Cada jogador poderá ter somente até 6 barcos espalhados pelo seu mapa. \n");
			printf("\t4- Existem 6 tipos de barco: Corveta, Submarino, Fragata, Destroyer, Cruzador, Porta-Aviões. \n");
			printf("\t5- Cada navio tem uma habilidade diferente do outro. Para saber mais, vá para a opção 3. \n");
			printf("\t6- Caso o jogador acertar irá aparecer uma parte do barco, caso contrário irá aparecer '~' que significa água. \n");
			printf("\t7- Lembrando: BARCO = '#' ATINGIDO = '$' AGUA = '~' DISPARO = 'x'. \n");
			printf("\t8- Uma vez que todos os navios de um dos jogadores forem afundados ele será derrotado. \n");
			printf("\n\n");
			system("pause"); // pausa e entra no while novamente após o enter.
		}
		if (opcao == '3')
		{
			printf("\n\n\t\t INFORMAÇÕES E HABILIDADES DE CADA BARCO. \n\n");
			//informações das habilidades dos barcos.
			printf("\t Corveta - Habilidades Especiais: 'Escudo e Satélite Espião.' \n");
			printf("\t Escudo: Cria um escudo 3x3 sobre o seu próprio campo, capaz de absorver até 5 tiros antes de ser destruído. \n\t Não pode ser lançado sobre a própria corveta. \n");
			printf("\t Satélite Espião: Revela todos os navios e bóias na superfície na área afetada, \n\t e mostra sua exata orientação e posição no campo. Não funciona em submarinos. \n");
			printf("\t Papel: Defesa e Inteligência. \n\n");
			printf("\t Submarino - Habilidades Especiais: 'Torpedo e Sonar.' \n");
			printf("\t Torpedo: Lança um torpedo que se move lentamente em uma linha reta através de um dos dois tabuleiros \n\t (não é possível lançar um torpedo no tabuleiro oposto). Se ele encontrar um navio no caminho, \n\t ele irá explodir, atingindo uma área 3x3, que ignora escudos. Os torpedos ignoram navios já destruídos. \n");
			printf("\t Sonar: Revela a posição de qualquer navio (incluindo submarinos) que estejam na área afetada. \n");
			printf("\t Papel: Ofensivo em áreas específicas e Inteligência. \n\n");
			printf("\t Fragata - Habilidades Especiais: 'Foguetes e Míssel Balístico.' \n");
			printf("\t Foguetes: Lança foguetes aleatórios em uma grande área. \n\t Cada quadrado na área tem uma chance de '50%' de ser atingido por um foguete. \n\t Altamente eficaz contra navios grandes, como o PortaAviões,o Cruzador, e o Destroyer. \n");
			printf("\t Míssel Balístico: Destrói todos os quadrados na área afetada, \n\t porém faz com que todos os jogadores descubram onde está a sua fragata. \n");
			printf("\t Papel: Ofensivo em larga escala. \n\n");
			printf("\t Destroyer - Habilidades Especiais: 'Cargas de Profundidade e Radar.' \n");
			printf("\t Cargas de Profundidade: Esta habilidade atinge uma área enorme, porém só atinge submarinos. \n\t Todos os outros navios e quadrados serão ignorados. \n");
			printf("\t Radar: Esta habilidade encontra navios na superfície em uma grande área, porém não pode encontrar submarinos. \n");
			printf("\t Papel: Inteligência e Anti-Submarino. \n\n");
			printf("\t Cruzador - Habilidades Especiais: 'Artilharia e Artilharia Pesada' \n");
			printf("\t Artilharia: A habilidade mais fraca e barata do jogo. Ela simplesmente atinge uma área 2x2. \n");
			printf("\t Artilharia Pesada: O mesmo que a artilharia, porém atinge uma área 3x3. \n");
			printf("\t Papel: Ofensivo Concentrado. \n\n");
			printf("\t Porta-Aviões - Habilidades Especiais: 'Bombardeio Linear e Pulso Eletromagnético' \n");
			printf("\t Bombardeio Linear: Atinge 8 quadrados ao longo de uma linha. \n\t Use o botão direito do mouse para rotacionar a área atingida. \n");
			printf("\t Pulso eletromagnético: Desabilita todos os navios de um jogador por duas Rounds. \n\t É a habilidade mais poderosa do jogo. \n");
			printf("\t Papel: Ofensivo e Estratégico. \n\n");
			printf("\n\n");
			system("pause"); // pausa e apos da enter ele entra no while novamente.		
		}
		if (opcao == '4') {
			break;
		}
	} while (opcao == '4');

	Executar_Opcao_Menu(opcao);
}

void GerarMenuPrincipalNovamente() {

	char opcao;
	char verificar_opcao;

	do {
		Limpar_Tela(); // limpa a tela system cls;

		//Desenha o menu principal na tela
		printf("\n\n");
		printf("\t  *********************************\n");
		printf("\t  *          MENU INICIAL         *\n");
		printf("\t  ********************************* \t  **********************************************\n");
		printf("\t  *  (1) INICIAR JOGO             * \t  *   HENRIQUE - ALEXANDER - MATHEUS MISSACI   *\n");
		printf("\t  *  (2) INSTRUÇÕES DO JOGO       * \t  **********************************************\n");
		printf("\t  *  (3) HABILIDADES P/ BARCOS    * \t  *   ENGENHARIA DE SOFTWARE 2º SEMESTRE       *\n");
		printf("\t  *  (4) FINALIZAR JOGO           * \t  *   PROFESSORA MILENE UNIFAE                 *\n");
		printf("\t  ********************************* \t  **********************************************\n");
		printf("\t  *         BATALHA NAVAL         *\n");
		printf("\t  *********************************\n");
		printf("\n\t-> Digite uma das opções acima: ");
		Limpar_Buffer();
		scanf("%c", &opcao);
		while (opcao != '4' &&  opcao != '1' &&  opcao != '2' && opcao != '3') {
			printf("\t Informe uma opção válida! ");
			Limpar_Buffer(); // limpa o buffer do while
			scanf("%c", &opcao);
		}
		if (opcao == '2')
		{
			printf("\n\n\t\tINFORMAÇÕES / AJUDA. \n\n");
			//Informações sobre como funciona e como jogar.
			printf("\t1- O jogo funciona da seguinte maneira, o jogador irá escolher onde deseja colocar o seu barco. \n");
			printf("\t2- O jogador irá escolher uma posição de 1 a 14 e de A até N. Exemplo: 5(linha) - F(coluna) \n");
			printf("\t3- Cada jogador poderá ter somente até 6 barcos espalhados pelo seu mapa. \n");
			printf("\t4- Existem 6 tipos de barco: Corveta, Submarino, Fragata, Destroyer, Cruzador, Porta-Aviões. \n");
			printf("\t5- Cada navio tem uma habilidade diferente do outro. Para saber mais, vá para a opção 3. \n");
			printf("\t6- Caso o jogador acertar irá aparecer uma parte do barco, caso contrário irá aparecer '~' que significa água. \n");
			printf("\t7- Lembrando: BARCO = '#' ATINGIDO = '$' AGUA = '~' DISPARO = 'x'. \n");
			printf("\t8- Uma vez que todos os navios de um dos jogadores forem afundados ele será derrotado. \n");
			printf("\n\n");
			system("pause"); // pausa e entra no while novamente após o enter.
		}
		if (opcao == '3')
		{
			printf("\n\n\t\t INFORMAÇÕES E HABILIDADES DE CADA BARCO. \n\n");
			//informações das habilidades dos barcos.
			printf("\t Corveta - Habilidades Especiais: 'Escudo e Satélite Espião.' \n");
			printf("\t Escudo: Cria um escudo 3x3 sobre o seu próprio campo, capaz de absorver até 5 tiros antes de ser destruído. \n\t Não pode ser lançado sobre a própria corveta. \n");
			printf("\t Satélite Espião: Revela todos os navios e bóias na superfície na área afetada, \n\t e mostra sua exata orientação e posição no campo. Não funciona em submarinos. \n");
			printf("\t Papel: Defesa e Inteligência. \n\n");
			printf("\t Submarino - Habilidades Especiais: 'Torpedo e Sonar.' \n");
			printf("\t Torpedo: Lança um torpedo que se move lentamente em uma linha reta através de um dos dois tabuleiros \n\t (não é possível lançar um torpedo no tabuleiro oposto). Se ele encontrar um navio no caminho, \n\t ele irá explodir, atingindo uma área 3x3, que ignora escudos. Os torpedos ignoram navios já destruídos. \n");
			printf("\t Sonar: Revela a posição de qualquer navio (incluindo submarinos) que estejam na área afetada. \n");
			printf("\t Papel: Ofensivo em áreas específicas e Inteligência. \n\n");
			printf("\t Fragata - Habilidades Especiais: 'Foguetes e Míssel Balístico.' \n");
			printf("\t Foguetes: Lança foguetes aleatórios em uma grande área. \n\t Cada quadrado na área tem uma chance de '50%' de ser atingido por um foguete. \n\t Altamente eficaz contra navios grandes, como o PortaAviões,o Cruzador, e o Destroyer. \n");
			printf("\t Míssel Balístico: Destrói todos os quadrados na área afetada, \n\t porém faz com que todos os jogadores descubram onde está a sua fragata. \n");
			printf("\t Papel: Ofensivo em larga escala. \n\n");
			printf("\t Destroyer - Habilidades Especiais: 'Cargas de Profundidade e Radar.' \n");
			printf("\t Cargas de Profundidade: Esta habilidade atinge uma área enorme, porém só atinge submarinos. \n\t Todos os outros navios e quadrados serão ignorados. \n");
			printf("\t Radar: Esta habilidade encontra navios na superfície em uma grande área, porém não pode encontrar submarinos. \n");
			printf("\t Papel: Inteligência e Anti-Submarino. \n\n");
			printf("\t Cruzador - Habilidades Especiais: 'Artilharia e Artilharia Pesada' \n");
			printf("\t Artilharia: A habilidade mais fraca e barata do jogo. Ela simplesmente atinge uma área 2x2. \n");
			printf("\t Artilharia Pesada: O mesmo que a artilharia, porém atinge uma área 3x3. \n");
			printf("\t Papel: Ofensivo Concentrado. \n\n");
			printf("\t Porta-Aviões - Habilidades Especiais: 'Bombardeio Linear e Pulso Eletromagnético' \n");
			printf("\t Bombardeio Linear: Atinge 8 quadrados ao longo de uma linha. \n\t Use o botão direito do mouse para rotacionar a área atingida. \n");
			printf("\t Pulso eletromagnético: Desabilita todos os navios de um jogador por duas Rounds. \n\t É a habilidade mais poderosa do jogo. \n");
			printf("\t Papel: Ofensivo e Estratégico. \n\n");
			printf("\n\n");
			system("pause"); // pausa e apos da enter ele entra no while novamente.		
		}
		if (opcao == '4') {
			printf("\t Tem certeza que realmente deseja sair [s/n]? ");
			Limpar_Buffer();
			scanf("%c", &verificar_opcao);

			while (tolower(verificar_opcao) != 's' && verificar_opcao != 'n') {
				printf("\t Insira uma opção válida! [s/n]");
				scanf("%c", &verificar_opcao);
				Limpar_Buffer();
			}
		}
	} while (opcao == '4');

	Executar_Opcao_Menu(opcao);
}

int Verificar_Barcos(int barco, int direcaoDoBarco, int linha, int coluna, char Matriz[MAX][MAX]) {
	switch (barco) {
	case 1:
		return Verificar_Corveta(direcaoDoBarco, linha, coluna, Matriz);
	case 2:
		return Verificar_Submarino(direcaoDoBarco, linha, coluna, Matriz);
	case 3:
		return Verifica_Fragata(direcaoDoBarco, linha, coluna, Matriz);
	case 4:
		return Verificar_Destroyer(direcaoDoBarco, linha, coluna, Matriz);
	case 5:
		return Verificar_Cruzador(direcaoDoBarco, linha, coluna, Matriz);
	case 6:
		return Verificar_PortaAvioes(direcaoDoBarco, linha, coluna, Matriz);
	}
	return 0;
}

void Imprimir_Barcos(int barco, int direcaoDoBarco, int linha, int coluna, char Matriz[MAX][MAX]) {
	switch (barco) {
	case 1:
		Imprimir_Corveta(direcaoDoBarco, linha, coluna, Matriz);
		break;
	case 2:
		Imprimir_Submarino(direcaoDoBarco, linha, coluna, Matriz);
		break;
	case 3:
		Imprimir_Fragata(direcaoDoBarco, linha, coluna, Matriz);
		break;
	case 4:
		Imprimir_Destroyer(direcaoDoBarco, linha, coluna, Matriz);
		break;
	case 5:
		Imprimir_Cruzador(direcaoDoBarco, linha, coluna, Matriz);
		break;
	case 6:
		Imprimir_PortaAvioes(direcaoDoBarco, linha, coluna, Matriz);
		break;
	}
}

//Funcao que checka se o DESTROYER esta corretamente posicionado
int Verificar_Destroyer(int direcaoDoBarco, int linha, int coluna, char Matriz[MAX][MAX]) {
	int i, j;

	if (direcaoDoBarco) {
		for (j = coluna; j <= coluna + 4; j++) {
			if (j >= MAX || Matriz[linha][j] == BARCO) {
				return 0;
			}
		}
	}
	else {
		for (i = linha; i <= linha + 4; i++) {
			if (i >= MAX || Matriz[i][coluna] == BARCO) {
				return 0;
			}
		}
	}
	return 1;
}
//Imprime um destroyer no mapa
void Imprimir_Destroyer(int direcaoDoBarco, int linha, int coluna, char Matriz[MAX][MAX]) {
	int i, j;

	if (direcaoDoBarco) {
		for (j = coluna; j < coluna + 4; j++) {
			Matriz[linha][j] = BARCO;
		}
	}
	else {
		for (i = linha; i < linha + 4; i++) {
			Matriz[i][coluna] = BARCO;
		}
	}

	if (Matriz == TabuleiroJogador) {
		num_de_barcos.destroyer--;
	}
	else {
		num_de_barcos_cpu.destroyer--;
	}
}
//Funcao que checka se o CRUZADOR esta corretamente posicionado
int Verificar_Cruzador(int direcaoDoBarco, int linha, int coluna, char Matriz[MAX][MAX]) {
	int i, j;

	if (direcaoDoBarco) {
		for (j = coluna; j <= coluna + 5; j++) {
			if (j >= MAX || Matriz[linha][j] == BARCO) {
				return 0;
			}
		}
	}
	else {
		for (i = linha; i <= linha + 5; i++) {
			if (i >= MAX || Matriz[i][coluna] == BARCO) {
				return 0;
			}
		}
	}
	return 1;
}
//Imprime um cruzador no mapa
void Imprimir_Cruzador(int direcaoDoBarco, int linha, int coluna, char Matriz[MAX][MAX]) {
	int i, j;

	if (direcaoDoBarco) {
		for (j = coluna; j < coluna + 5; j++) {
			Matriz[linha][j] = BARCO;
		}
	}
	else {
		for (i = linha; i < linha + 5; i++) {
			Matriz[i][coluna] = BARCO;
		}
	}

	if (Matriz == TabuleiroJogador) {
		num_de_barcos.cruzador--;
	}
	else {
		num_de_barcos_cpu.cruzador--;
	}
}
//Funcao que checka se o PORTA-AVIOES esta corretamente posicionado
int Verificar_PortaAvioes(int direcaoDoBarco, int linha, int coluna, char Matriz[MAX][MAX]) {
	int i, j;

	if (direcaoDoBarco) {
		for (i = linha; i < linha + 2; i++) {
			for (j = coluna; j < coluna + 6; j++) {
				if (i >= MAX || j >= MAX || Matriz[i][j] == BARCO) {
					return 0;
				}
			}
		}
	}
	else {
		for (i = linha; i < linha + 6; i++) {
			for (j = coluna; j < coluna + 2; j++) {
				if (i >= MAX || j >= MAX || Matriz[i][j] == BARCO) {
					return 0;
				}
			}
		}
	}
	return 1;
}
//Imprime um porta-avioes no mapa
void Imprimir_PortaAvioes(int direcaoDoBarco, int linha, int coluna, char Matriz[MAX][MAX]) {
	int i, j;

	if (direcaoDoBarco) {
		for (i = linha; i < linha + 2; i++) {
			for (j = coluna; j < coluna + 6; j++) {
				Matriz[i][j] = BARCO;
			}
		}
	}
	else {
		for (i = linha; i < linha + 6; i++) {
			for (j = coluna; j < coluna + 2; j++) {
				Matriz[i][j] = BARCO;
			}
		}
	}

	if (Matriz == TabuleiroJogador) {
		num_de_barcos.portaAvioes--;
	}
	else {
		num_de_barcos_cpu.portaAvioes--;
	}
}

//Funcao que checka se a FRAGATA esta corretamente posicionado
int Verifica_Fragata(int direcaoDoBarco, int linha, int coluna, char Matriz[MAX][MAX]) {
	int i, j;

	if (direcaoDoBarco) {
		for (j = coluna; j <= coluna + 3; j++) {
			if (j >= MAX || Matriz[linha][j] == BARCO) {
				return 0;
			}
		}
	}
	else {
		for (i = linha; i <= linha + 3; i++) {
			if (i >= MAX || Matriz[i][coluna] == BARCO) {
				return 0;
			}
		}
	}
	return 1;
}
//Imprime um fragata no mapa
void Imprimir_Fragata(int direcaoDoBarco, int linha, int coluna, char Matriz[MAX][MAX]) {
	int i, j;

	if (direcaoDoBarco) {
		for (j = coluna; j < coluna + 3; j++) {
			Matriz[linha][j] = BARCO;
		}
	}
	else {
		for (i = linha; i < linha + 3; i++) {
			Matriz[i][coluna] = BARCO;
		}
	}

	if (Matriz == TabuleiroJogador) {
		num_de_barcos.fragata--;
	}
	else {
		num_de_barcos_cpu.fragata--;
	}
}


//Funcao que checka se a CORVETA esta corretamente posicionado
int Verificar_Corveta(int direcaoDoBarco, int linha, int coluna, char Matriz[MAX][MAX]) {
	int i, j;

	if (direcaoDoBarco) {
		for (j = coluna; j < coluna + 2; j++) {
			if (j >= MAX || Matriz[linha][j] == BARCO) {
				return 0;
			}
		}
	}
	else {
		for (i = linha; i < linha + 2; i++) {
			if (i >= MAX || Matriz[i][coluna] == BARCO) {
				return 0;
			}
		}
	}
	return 1;
}
//Imprime um corveta no mapa
void Imprimir_Corveta(int direcaoDoBarco, int linha, int coluna, char Matriz[MAX][MAX]) {
	int i, j;

	if (direcaoDoBarco) {
		for (j = coluna; j < coluna + 2; j++) {
			Matriz[linha][j] = BARCO;
		}
	}
	else {
		for (i = linha; i < linha + 2; i++) {
			Matriz[i][coluna] = BARCO;
		}
	}

	if (Matriz == TabuleiroJogador) {
		num_de_barcos.corveta--;
	}
	else {
		num_de_barcos_cpu.corveta--;
	}
}
//Funcao que checka se o SUBMARINO esta corretamente posicionado
int Verificar_Submarino(int direcaoDoBarco, int linha, int coluna, char Matriz[MAX][MAX]) {
	int i, j;

	if (direcaoDoBarco) {
		for (j = coluna; j <= coluna + 3; j++) {
			if (j >= MAX || Matriz[linha][j] == BARCO) {
				return 0;
			}
		}
	}
	else {
		for (i = linha; i <= linha + 3; i++) {
			if (i >= MAX || Matriz[i][coluna] == BARCO) {
				return 0;
			}
		}
	}
	return 1;
}
//Funcao que imprime o submarino
void Imprimir_Submarino(int direcaoDoBarco, int linha, int coluna, char Matriz[MAX][MAX]) {
	int i, j;

	if (direcaoDoBarco) {
		for (j = coluna; j < coluna + 3; j++) {
			Matriz[linha][j] = BARCO;
		}
	}
	else {
		for (i = linha; i < linha + 3; i++) {
			Matriz[i][coluna] = BARCO;
		}
	}

	if (Matriz == TabuleiroJogador) {
		num_de_barcos.submarino--;
	}
	else {
		num_de_barcos_cpu.submarino--;
	}
}

int main() {
	//localizacao de vocabulario
	setlocale(LC_ALL, "Portuguese");
	//Funcao que inicia o jogo
	GerarMenuPrincipal();
	return 0; // retorna a nada.
}


