#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

typedef struct {
	char naipe;
	int numeroCarta;
	int valor;
} Carta;

void montarBaralho(Carta baralho[]);
void mostrarBaralho(Carta baralho[]);
void pontosPorCartas(Carta baralho[]);
void mostrarPontosCartas(Carta baralho[]);
void embaralhar(Carta baralho[], int tamanho);
void distribuirCartas(Carta baralho[], Carta jogador[], Carta dealer[]);
void mostrarCartasDealer(Carta dealer[]);
void mostrarCartasJogador (Carta jogador[]);
int calcularPontos(Carta mao[], int quantidadeCartas);
void mostrarPontos (int pontuacaoJogador, int pontuacaoDealer);

int main(int argc, char const *argv[]){
	
	setlocale(LC_ALL, "Portuguese");
	
	Carta baralho[52]={}; 
	Carta jogador[3]={};
	Carta dealer[3]={};
	int valor;
	int tamanho = 52;
	int pontuacaoJogador = 0;
	int pontuacaoDealer = 0;
	
	montarBaralho(baralho);
	mostrarBaralho(baralho);
	pontosPorCartas(baralho);
	mostrarPontosCartas(baralho);
	printf("-------------\n");
	embaralhar(baralho, tamanho);
	mostrarBaralho(baralho);
	distribuirCartas( baralho, jogador, dealer);
	mostrarCartasDealer(dealer);
	mostrarCartasJogador(jogador);
	pontuacaoJogador = calcularPontos(jogador, 2);
	pontuacaoDealer = calcularPontos(dealer, 2);
	mostrarPontos (pontuacaoJogador, pontuacaoDealer);
	
	return 0;
}

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
	
	int valor = 1;
	int i;
	for(i=0 ; i<52; i++){
		if (baralho[i].numeroCarta >= 11){
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

void mostrarCartasDealer(Carta dealer[]){
	int i;
	printf("Dealer: ");
	for(i=0 ; i<2; i++ ){
		printf(" carta: %d%c | valor: %d " , dealer[i].numeroCarta, dealer[i].naipe, dealer[i].valor );
	}
	
	printf("\n");	
}

void mostrarCartasJogador (Carta jogador[]){
	int j;
	printf("Jogador:");
	for(j=0 ; j<2; j++ ){
		printf(" carta: %d%c | valor: %d " , jogador[j].numeroCarta, jogador[j].naipe, jogador[j].valor);
	}
	
	printf("\n");	
}

int calcularPontos(Carta mao[], int quantidadeCartas){
	
	int pontuacao = 0;
	int i;
	for(i=0; i<quantidadeCartas; i++){
		pontuacao += mao[i].valor;
	}
	return pontuacao;
}

void mostrarPontos (int pontuacaoJogador, int pontuacaoDealer){
	printf("Pontuação jogador: %d \n" , pontuacaoJogador);
	printf("Pontuação dealer: %d \n" ,pontuacaoDealer);
}

