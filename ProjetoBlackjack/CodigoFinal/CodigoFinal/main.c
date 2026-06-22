#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <stdbool.h>


// CRIAR A CARTA

typedef struct {
	char naipe;
	int numeroCarta;
	int valor;
} Carta;


//METODOS PROTOTIPADOS

void montarBaralho(Carta baralho[]);

void mostrarBaralho(Carta baralho[]);

void pontosPorCartas(Carta baralho[]);

void mostrarPontosCartas(Carta baralho[]);

void embaralhar(Carta baralho[], int tamanho);

void distribuirCartas(Carta baralho[], Carta jogador[], Carta dealer[]);

void prepararPartida(Carta baralho[], Carta jogador[], Carta dealer[]);

void mostrarCartasDealerOculta(Carta dealer[], int cartasDealer);

void mostrarCartasDealer(Carta dealer[], int cartasDealer);

void mostrarCartasJogador (Carta jogador[], int cartasJogador);

int calcularPontos(Carta mao[], int quantidadeCartas);

void mostrarPontos (int pontuacaoJogador, int pontuacaoDealer);

int pedirCartas (Carta baralho[], Carta mao[], int quantidadeCartas, int cartaTopo);

bool temBlackjack (int pontuacao, int quantidadeCartas);

bool temBlackJackInicial(bool blackjackJogador, bool blackjackDealer);

void turnoJogador(Carta baralho[], Carta jogador[], int *pontuacaoJogador, int *cartasJogador, int *cartaTopo);

void turnoDealerFacil(Carta baralho[], Carta daler[], int *pontuacaoDealer, int *cartasDealer, int *cartaTopo);

void turnoDealerMedio(Carta baralho[], Carta dealer[], int *pontuacaoDealer,int *pontuacaoJogador,int *cartasDealer, int *cartaTopo);

void turnoDealerDificil(Carta baralho[], Carta dealer[], int *pontuacaoDealer,int *pontuacaoJogador,int *cartasDealer, int *cartaTopo);

void resultadoPartida(Carta jogador[], Carta dealer[], int *cartasJogador, int *cartasDealer, int *pontuacaoJogador, int *pontuacaoDealer);

void escolherDificuldadeDealer(int *opDealer);

void executarTurnoDealer(int dificuldade, Carta baralho[], Carta dealer[], int *pontuacaoDealer, int *pontuacaoJogador, int *cartasDealer, int *cartaTopo);

int menuJogarNovamente();


// INICIZALIZAR O JOGO

int main(int argc, char const *argv[]){

	setlocale(LC_ALL, "Portuguese");
	
	//DEFINE O TAMANHO DO BARALHO E MÃO DE CADA JOGADOR
	
	Carta baralho[52]={};
	Carta jogador[12]={};
	Carta dealer[12]={};
	
	int jogarNovamente = 1;
	
	
	while(jogarNovamente == 1){
		
		int opDealer;
		escolherDificuldadeDealer(&opDealer);
		
		//Pontucao deve começar com zero
		
		int pontuacaoJogador = 0;
		int pontuacaoDealer = 0;
		
		// Monta o baralho, define os pontos das cartas e embaralha e distribui as cartas para a primeira rodada
		prepararPartida(baralho, jogador, dealer);
	
		int cartaTopo = 4; //define o indice quatro para a contagem de cartas no método pedir, pois é a carta que se encontra no topo do baralho
		int cartasJogador = 2; //após distribuição inicial de cartas o jogador possui 2 cartas
		int cartasDealer = 2; //após distribuição inicial de cartas o dealer possuiu 2 cartas
		//=======================================================================================================	
		
		mostrarCartasDealerOculta(dealer, cartasDealer);
		pontuacaoDealer = calcularPontos(dealer, cartasDealer);
		
		mostrarCartasJogador(jogador, cartasJogador);
		pontuacaoJogador = calcularPontos(jogador, cartasJogador);
		printf("Valor da mão do jogador: %d \n" ,pontuacaoJogador);
		
	
		// VERIFICAR SE O DEALER E O JOGADOR JÁ INICIARAM COM BLACKJACK (SOMA DE DUAS CARTAS IGUAL A 21 (BLACKJACK))
		bool blackjackJogador = temBlackjack(pontuacaoJogador, cartasJogador);
		bool blackjackDealer = temBlackjack(pontuacaoDealer, cartasDealer);
		bool fimPartida = temBlackJackInicial(blackjackJogador, blackjackDealer);
		//=======================================================================================================
		
		// CASO NÃO HAJA BLACKJACK, O JOGO SEGUE PARA O TURNO DO JOGADOR E DO DEALER (BASEADO NA DIFICULDADE ESCOLHIDA)
		if(!fimPartida){
				
			turnoJogador(baralho, jogador, &pontuacaoJogador, &cartasJogador, &cartaTopo);
				
			if(pontuacaoJogador <= 21){
				
				executarTurnoDealer(opDealer, baralho, dealer, &pontuacaoDealer, &pontuacaoJogador, &cartasDealer, &cartaTopo);
				
			}
		
			resultadoPartida(jogador, dealer, &cartasJogador, &cartasDealer, &pontuacaoJogador, &pontuacaoDealer);
		
		}
		
		jogarNovamente = menuJogarNovamente();
	
	}
	return 0;
}

// FUNÇÕES PARA MONTAR O BARALHO, ATRIBUIR VALORES, EMBARALHAR E DISTRIBUIR

void montarBaralho(Carta baralho[]){
	int valores[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
	char naipes[] = {'O', 'C', 'E', 'P'};

	int i, j, ind = 0;

	for(i=0; i<4; i++){
		for(j=0; j<13; j++){
			baralho[ind].naipe = naipes[i];
			baralho[ind].numeroCarta = valores[j];
			ind ++;
		}
	}
}

void mostrarBaralho(Carta baralho[]){
	int i;
	for (i=0; i<52; i++){
		printf("Carta %d: %d%c \n", i+1, baralho[i].numeroCarta, baralho[i].naipe);
	}
}

void pontosPorCartas(Carta baralho[]){

	
	int i;
	for(i=0 ; i<52; i++){
		if (baralho[i].numeroCarta == 1){
			baralho[i].valor = 11;
		} else if (baralho[i].numeroCarta >= 11){
			baralho[i].valor = 10;
		} else{
			baralho[i].valor = baralho[i].numeroCarta;
		}
	}
}

void mostrarPontosCartas(Carta baralho[]){
	int i;
	for(i=0; i<52; i++){
		printf("carta: %d%c | valor: %d \n", baralho[i].numeroCarta, baralho[i].naipe, baralho[i].valor);
	}
}

void embaralhar(Carta baralho[], int tamanho){

	srand(time(NULL));

	int i;
	for(i = tamanho - 1; i > 0; i -- ){
		//escolher um indice aleatorio
		int j = rand()%(i+1);

		//trocar cartas de lugar
		Carta aleatoria = baralho[i];
		baralho [i] = baralho [j];
		baralho [j] = aleatoria;

	}

}

void distribuirCartas(Carta baralho[], Carta jogador[], Carta dealer[]){

	int i ;
	int cartaTopo = 0;
	for (i=0; i<2; i++){
		dealer[i] = baralho[cartaTopo++];
		jogador[i] = baralho[cartaTopo++];
	}

}

// PREPARAR A PARTIDA BASEADA NAS FUNÇÕES ANTERIORES

void prepararPartida(Carta baralho[], Carta jogador[], Carta dealer[]){
	
	montarBaralho(baralho);
	pontosPorCartas(baralho);
	embaralhar(baralho, 52);
	distribuirCartas( baralho, jogador, dealer);

}


//MOSTRAR AS CARTAS DE CADA UM NAS SITUAÇÕES DO JOGO E CALCUALR OS PONTOS

// O jogador não pode ver a primeira carta do dealer até termianr sua jogada.
void mostrarCartasDealerOculta(Carta dealer[], int cartasDealer){
	int i;
	printf("Dealer: \n");
	for(i=0 ; i<cartasDealer; i++ ){
		if(i == 0){
			printf(" carta %d: [?] \n", i+1);
		}else {
			printf(" carta %d: %d-%c \n" , i+1, dealer[i].numeroCarta, dealer[i].naipe);
		}
	}
}

void mostrarCartasDealer(Carta dealer[],int cartasDealer){
	int i;
	printf("Dealer: \n");
	for(i=0 ; i<cartasDealer; i++ ){
		printf(" carta %d: %d-%c \n" , i+1, dealer[i].numeroCarta, dealer[i].naipe );
	}

	printf("\n");
}

void mostrarCartasJogador (Carta jogador[],int cartasJogador){
	int j;
	printf("Jogador: \n");
	for(j=0 ; j<cartasJogador; j++ ){
		printf(" carta %d: %d-%c | valor: %d \n" , j+1, jogador[j].numeroCarta, jogador[j].naipe, jogador[j].valor);
	}

	printf("\n");
}

int calcularPontos(Carta mao[], int quantidadeCartas){

	int pontuacao = 0;
	int ases = 0;
	int i;
	for(i=0; i<quantidadeCartas; i++){
		pontuacao += mao[i].valor;
		
		if(mao[i].numeroCarta == 1){
			ases++;
		}
		
	}
	while( pontuacao > 21 && ases > 0){
		pontuacao = pontuacao - 10;
		ases--;
	}
	return pontuacao;
}

void mostrarPontos (int pontuacaoJogador, int pontuacaoDealer){
	printf("Pontuação jogador: %d \n" , pontuacaoJogador);
	printf("Pontuação dealer: %d \n" ,pontuacaoDealer);
}

// PEDIR CARTAS

int pedirCartas (Carta baralho[], Carta mao[], int quantidadeCartas, int cartaTopo){

	mao[quantidadeCartas] = baralho[cartaTopo];

	return cartaTopo + 1;
}

// VERIFICAR SE HÁ BLACKJACK 

bool temBlackjack (int pontuacao, int quantidadeCartas){
	return (pontuacao == 21 && quantidadeCartas == 2);
}

bool temBlackJackInicial(bool blackjackJogador, bool blackjackDealer){
	
	if(blackjackJogador && !blackjackDealer){
		
		printf("Jogador obteve Blackjack!!!\n Jogador vence a partida!!! \n");
		return true;
		
	} else if(!blackjackJogador && blackjackDealer){
		
		printf("Dealer obteve Blackjack!!! \n Dealer vence a partida!!! \n");
		return true;
		
	} else if (blackjackJogador && blackjackDealer){
		
		printf("Jogador e dealer obtiveram Blackjack!!! \n Partida termina em empate !!! \n");
		return true;
	
	}  
	return false;	
}

// TURNO DO JOGADOR E DIFICULDADES DO TURNO DO DEALER

void turnoJogador(Carta baralho[], Carta jogador[], int *pontuacaoJogador, int *cartasJogador, int *cartaTopo){
	
	int op = 0;
	
	do {
		
		printf("+-------------------------------+\n");
		printf("|  Opções para próxima jogada   |\n");
		printf("+-------------------------------+\n");
		printf("|1- Pedir uma carta.            |\n");
		printf("|2- Parar jogada.               |\n");
		printf("|-------------------------------|\n");
		printf("|Opção:");
		scanf("%d", &op);
			
		switch(op){
			case 1:
					
				*cartaTopo = pedirCartas (baralho, jogador, *cartasJogador, *cartaTopo);
				(*cartasJogador)++;
				mostrarCartasJogador(jogador, *cartasJogador);
				*pontuacaoJogador = calcularPontos(jogador, *cartasJogador);
				printf("pontuação atual do jogador: %d \n" , *pontuacaoJogador);
					
				if(*pontuacaoJogador > 21){
						
			  		printf("Estourou os pontos \n");
						
				}
				break;
				
			case 2:
					
				printf("Jogador encerrou a jogada.\n");
					
				break;
				
			default:
					
			printf("Opção inválida, tente novamente");	
		}
			
	}while ((*pontuacaoJogador < 21) && (op!= 2));
	
}

void turnoDealerFacil(Carta baralho[], Carta dealer[], int *pontuacaoDealer, int *cartasDealer, int *cartaTopo){
	
	while(*pontuacaoDealer < 17){
		
		printf("Dealer compra cartas \n");
		
		*cartaTopo = pedirCartas (baralho, dealer, *cartasDealer, *cartaTopo);
		
		printf("Carta comprada: %d-%c | Valor: %d \n", dealer[*cartasDealer].numeroCarta, dealer[*cartasDealer].naipe, dealer[*cartasDealer].valor );
		
		(*cartasDealer)++;
		
		mostrarCartasDealer(dealer, *cartasDealer);
		
		*pontuacaoDealer = calcularPontos(dealer, *cartasDealer);
		
		printf("Pontuação do Dealer: %d \n", *pontuacaoDealer);
	}
	if(*pontuacaoDealer > 21){
		
		printf("Dealer estourou\n");
	
	}
}

void turnoDealerMedio(Carta baralho[], Carta dealer[], int *pontuacaoDealer,int *pontuacaoJogador,int *cartasDealer, int *cartaTopo){
		
	while((*pontuacaoDealer < 17) || (*pontuacaoDealer < *pontuacaoJogador)){
				
		printf("Dealer compra cartas \n");
				
		*cartaTopo = pedirCartas (baralho, dealer, *cartasDealer, *cartaTopo);
				
		printf("Carta comprada: %d-%c | Valor: %d \n", dealer[*cartasDealer].numeroCarta, dealer[*cartasDealer].naipe, dealer[*cartasDealer].valor );
				
		(*cartasDealer)++;
				
		mostrarCartasDealer(dealer, *cartasDealer);
				
		*pontuacaoDealer = calcularPontos(dealer, *cartasDealer);
				
		printf("Pontuação do Dealer: %d \n", *pontuacaoDealer);
	
	
		if(*pontuacaoDealer > 21){
		
			printf("Dealer estourou\n");
			break;
		}
	
	} 
			
}

void turnoDealerDificil(Carta baralho[], Carta dealer[], int *pontuacaoDealer,int *pontuacaoJogador,int *cartasDealer, int *cartaTopo){
	while((*pontuacaoDealer < 17) || ((*pontuacaoDealer < *pontuacaoJogador) && *pontuacaoDealer < 20)){
				
		printf("Dealer compra cartas \n");
				
		*cartaTopo = pedirCartas (baralho, dealer, *cartasDealer, *cartaTopo);
				
		printf("Carta comprada: %d-%c | Valor: %d \n", dealer[*cartasDealer].numeroCarta, dealer[*cartasDealer].naipe, dealer[*cartasDealer].valor );
				
		(*cartasDealer)++;
				
		mostrarCartasDealer(dealer, *cartasDealer);
				
		*pontuacaoDealer = calcularPontos(dealer, *cartasDealer);
				
		printf("Pontuação do Dealer: %d \n", *pontuacaoDealer);
	
	
		if(*pontuacaoDealer > 21){
		
			printf("Dealer estourou\n");
			break;
		}
	
	}
}

//RESULTADO DA PARTIDA

void resultadoPartida(Carta jogador[], Carta dealer[], int *cartasJogador, int *cartasDealer, int *pontuacaoJogador, int *pontuacaoDealer){
	printf("============================\n");
	printf("       RESULTADO FINAL      \n");
	printf("============================\n");
		
	mostrarPontos (*pontuacaoJogador, *pontuacaoDealer);
	
	printf("============================\n");
	mostrarCartasJogador(jogador, *cartasJogador);
		
	printf("============================\n");
	mostrarCartasDealer(dealer, *cartasDealer);
		
	if(*pontuacaoJogador > 21 && *pontuacaoDealer <= 21){
		
		printf("Pontuação do jogador estourou, o dealer vence a partida!! \n");
			
	} else if (*pontuacaoJogador <= 21 && *pontuacaoDealer > 21){
			
		printf("Pontuacao do dealer estourou, o jogador vence a partida!!\n");
			
	} else if(*pontuacaoJogador > *pontuacaoDealer){
			
		printf("Pontuação do jogador maior que a pontuação do dealer, jogador vence a partida!!\n");
			
	} else if(*pontuacaoJogador < *pontuacaoDealer){
			
		printf("Pontuação do dealer maior que a pontuação do jogador, dealer vence a partida!!\n");
			
	} else if(*pontuacaoJogador == *pontuacaoDealer){
			
		printf("Delaer e jogador terminaram a partida com mesma pontuação. Resultado: Empate!!\n");
			
	}	
	
}

// MENU PARA ESCOLHER DIFICULDADE

void escolherDificuldadeDealer(int *opDealer){

	printf("+-----------------------------------+\n");
	printf("|  Escolha a Dificuldade do Dealer  |\n");
	printf("+-----------------------------------+\n");
	printf("|1- Fácil.                          |\n");
	printf("|2- Médio.                          |\n");
	printf("|3- Difícil.                        |\n");
	printf("|-----------------------------------|\n");
	printf("|Opção:");
	do{
		scanf("%d", opDealer);
		if(*opDealer!= 1 && *opDealer!=2 && *opDealer !=3){
			printf("O valor digitado deve ser 1, 2 ou 3, digite novamente.\n");
			printf("Opcao: ");
		}
	} while (*opDealer!= 1 && *opDealer!=2 && *opDealer !=3);
}

// EXECUTAR O TURNO DO DEALER BASEADO NA DIFICULDADE DELE

void executarTurnoDealer(int dificuldade, Carta baralho[], Carta dealer[], int *pontuacaoDealer, int *pontuacaoJogador, int *cartasDealer, int *cartaTopo){
	
	switch(dificuldade){
		case 1:
			turnoDealerFacil(baralho, dealer, pontuacaoDealer, cartasDealer, cartaTopo);
			break;
		case 2:
			turnoDealerMedio(baralho, dealer, pontuacaoDealer, pontuacaoJogador, cartasDealer, cartaTopo);
			break;
		case 3:
			turnoDealerDificil(baralho, dealer, pontuacaoDealer, pontuacaoJogador, cartasDealer, cartaTopo);
			break;
		default:
			printf("Erro na seleção da dificuldade.\n");
	}
		
}

// MENU PARA JOGAR NOVAMENTE

int menuJogarNovamente(){

    int jogarNovamente;

    printf("+---------------------------+\n");
    printf("|  Deseja Jogar Novamente?  |\n");
    printf("+---------------------------+\n");
    printf("| 1 - Sim                   |\n");
    printf("| 2 - Não                   |\n");
    printf("+---------------------------+\n");
    printf("|Opção: ");

    do{

        scanf("%d", &jogarNovamente);

        if(jogarNovamente != 1 && jogarNovamente != 2){

            printf("O valor digitado deve ser 1 ou 2.\n");
            printf("Opção: ");

        }

    }while(jogarNovamente != 1 && jogarNovamente != 2);

    return jogarNovamente;
}
