#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#define MAX 40
#define CJ 3

void inicio_jogo(int, int, int jogador1[], int jogador2[], int jogador3[], int jogador4[], int manilha[], int, int, int, int, int);
void criar(int*, int*);
void preencher_baralho(int cartas[]);
void inserir_cartas(int, int*, int*, int cartas[]);
void cartas_jogador(int*, int*, int cartas[], int jogador1[], int jogador2[], int jogador3[], int jogador4[]);
void manilhas(int manilha[], int cartas[], int*, int*);
void visual(int jogador1[], int, int, int);
int pedir_truco(int*);
int verificar_pontos_rodada(int, int jogador1[], int jogador2[], int jogador3[], int jogador4[], int *, int manilha[], int, int*, int*, int*, int);
void verificar_ganhador_rodada(int*, int*, int, int, int);
int visual_cartas_jogadores(int jogador1[], int jogador2[], int jogador3[], int jogador4[], int, int, int, int*, int *, int);
void carta_final(int jogador1[], int);
void partida_empate(int*, int*, int*, int*, int, int*);
void nova_rodada(int, int, int);
void vencedor_jogo(int total_time1, int total_time2);


int main()
{
	int manilha[4], n, inicio, final, ch, cartas[MAX], rodada = 0, vira, vencendor_rodada = 1;
	int jogador1[CJ], jogador2[CJ], jogador3[CJ], jogador4[CJ];
	int total_time1 = 0, total_time2 = 0;

	srand(time(NULL));
	setlocale(LC_ALL, "");
	system("cls");

	printf("\n1 - Iniciar jogo: ");
	printf("\n2 - Sair");

	while (1)
	{
		printf("\n\nEscolha uma opção : ");
		scanf("%d", &ch);

		switch (ch)
		{
		case 1:
			criar(&inicio, &final);
			while (inicio <= 38) {
				n = rand() % 40;
				inserir_cartas(n, &final, &inicio, cartas);
			}
			manilhas(manilha, cartas, &inicio, &vira);
			cartas_jogador(&inicio, &final, cartas, jogador1, jogador2, jogador3, jogador4);
			inicio_jogo(final, inicio, jogador1, jogador2, jogador3, jogador4, manilha, rodada, vira, total_time1, total_time2, vencendor_rodada);
			break;
		case 2:
			exit(0);
		default:
			printf("\nEscolha incorra, por favor digite novamente");
		}
	}
}

void nova_rodada(int total_time1, int total_time2, int vencendor_rodada)
{

	vencedor_jogo(total_time1, total_time2);

	int manilha[4], n, inicio, final, cartas[MAX], rodada = 0, vira;
	int jogador1[CJ], jogador2[CJ], jogador3[CJ], jogador4[CJ];

	srand(time(NULL));

	criar(&inicio, &final);
	while (inicio <= 38) {
		n = rand() % 40;
		inserir_cartas(n, &final, &inicio, cartas);
	}
	manilhas(manilha, cartas, &inicio, &vira);
	cartas_jogador(&inicio, &final, cartas, jogador1, jogador2, jogador3, jogador4);
	inicio_jogo(final, inicio, jogador1, jogador2, jogador3, jogador4, manilha, rodada, vira, total_time1, total_time2, vencendor_rodada);

}

void inicio_jogo(int final, int inicio, int jogador1[], int jogador2[], int jogador3[], int jogador4[], int manilha[], int rodada, int vira, int total_time1, int total_time2, int vencendor_rodada)
{
	int ch, valor_rodada = 1, pontos_time1 = 0, pontos_time2 = 0, empate = 0, vencedor_primeira=0;
	system("cls");

	while (1)
	{
		if (rodada >= 3) {
			verificar_ganhador_rodada(&total_time1, &total_time2, pontos_time1, pontos_time2, valor_rodada);
			system("pause");
			nova_rodada(total_time1, total_time2, vencendor_rodada);
			valor_rodada = 1;
		}

		if (rodada == 1) {
			vencedor_primeira = vencendor_rodada;
		}

		printf("\n\n\n\t\t\t---------------------------\n\t\t\t\t RODADA %d \n\t\t\t---------------------------\n\n\n", rodada + 1);
		ch = visual_cartas_jogadores(jogador1, jogador2, jogador3, jogador4, rodada, vencendor_rodada, vira, &valor_rodada, &pontos_time1, empate);

		switch (ch)
		{
		case 1:
			vencendor_rodada = verificar_pontos_rodada(rodada, jogador1, jogador2, jogador3, jogador4, &rodada, manilha, ch, &pontos_time1, &pontos_time2, &empate, vencedor_primeira);
			carta_final(jogador1, ch);
			rodada++;
			system("\npause\n");
			break;
		case 2:
			vencendor_rodada = verificar_pontos_rodada(rodada, jogador1, jogador2, jogador3, jogador4, &rodada, manilha, ch, &pontos_time1, &pontos_time2, &empate, vencedor_primeira);
			carta_final(jogador1, ch);
			rodada++;
			system("\npause\n");
			break;
		case 3:
			vencendor_rodada = verificar_pontos_rodada(rodada, jogador1, jogador2, jogador3, jogador4, &rodada, manilha, ch, &pontos_time1, &pontos_time2, &empate, vencedor_primeira);
			carta_final(jogador1, ch);
			rodada++;
			system("\npause\n");
			break;
		case 4:
			rodada = 3;
			system("\npause\n");
			break;
		case 5:
			printf("\nAVISO - DESEJA DESISTIR DA PARTIDA?\n\n");
			system("pause");
			main();
		default:
			printf("\nEscolha incorra, por favor digite novamente");
		}
	}
}

void criar(int *inicio, int *final)
{
	(*inicio) = (*final) = -1;
}

void inserir_cartas(int data, int *final, int *inicio, int cartas[])
{
	int i, resp = 0;
	// Verificar se número gerado já existe no baralho
	for (i = 0; i <= (*inicio); i++) {
		if (data == cartas[i]) {
			resp = 1; //há carta repetida
		}
	}
	//Não há carta repitida
	if (resp == 0) {

		if (((*inicio) == -1) && ((*final) == -1))
		{
			(*inicio)++;
			(*final)++;
			cartas[(*inicio)] = data;
			return;
		}
		else
		{
			cartas[(*inicio) + 1] = data;
			(*inicio)++;
		}
	}
}

/* Distribui cartas aos jogadores */
void cartas_jogador(int *inicio, int *final, int cartas[], int jogador1[], int jogador2[], int jogador3[], int jogador4[])
{
	int i, j;

	for (j = 0; j < CJ * 4; j++)
	{
		if (j<3)
			jogador1[j] = cartas[0];
		if ((j >= 3) && (j<6))
			jogador2[j - 3] = cartas[0];
		if ((j >= 6) && (j<9))
			jogador3[j - 6] = cartas[0];
		if (j >= 9)
			jogador4[j - 9] = cartas[0];
		for (i = 0; i < (*inicio); i++)
		{
			cartas[i] = cartas[i + 1];
		}
		cartas[i] = -99;
		(*inicio)--;

		if ((*inicio) == -1)
			(*final) = -1;
	}
}

/* Mostra cartas */
void visual(int jogador1[], int rodada, int vira, int empate) {
	int n = 0, y = 0, i, s = 0, k;
	char valornaipe[4][8] = { "OURO ","ESPADA ","COPAS ","PAUS " };
	char valorcarta[10][8] = { "QUATRO","CINCO","SEIS","SETE","DAMA","VALETE","REI","AS","DOIS","TRES" };

	if (rodada == 0) {
		for (i = 0;i<MAX;i++) {
			if (i == vira) {
				printf("\n------------------------\n VIRA \n------------------------\n\n");
				printf(" %s %s \n", valornaipe[n], valorcarta[y]);
			}
			if (i == 9 + s) {
				n += 1;
				y = -1;
				s += 10;
			}
			y++;
		}
		n = 0;y = 0;s = 0;
	}
	printf("\n------------------------\n SUAS CARTAS \n------------------------\n\n");
	for (k = 0;k<3 - rodada + empate;k++) {
		for (i = 0;i<MAX;i++) {
			if (i == jogador1[k]) {
				printf("%d - %s %s \n", k + 1, valornaipe[n], valorcarta[y]);
			}
			if (i == 9 + s) {
				n += 1;
				y = -1;
				s += 10;
			}
			y++;
		}
		n = 0;y = 0;s = 0;
	}
}

/* Manilha */
void manilhas(int manilha[], int cartas[], int *inicio, int* vira) {
	int i, l = 10, j = 1, resp = 0;
	manilha[0] = cartas[0];
	(*vira) = manilha[0];
	manilha[0] = manilha[0] + 1;
	for (i = 0; j < 4; i++)
	{
		if (cartas[i] == manilha[0] + l) {
			manilha[j] = cartas[i];
			if (resp == 0) {
				l += 10;
			}
			else {
				l = l - 10;
			}
			i = 0;
			j++;
		}
		if (i == 40) {
			l = -10;
			i = 0;
			resp = 1;
		}
	}
	for (i = 0; i < (*inicio); i++)
	{
		cartas[i] = cartas[i + 1];
	}
	cartas[i] = -99;
	(*inicio)--;
}

/* Pedir Truco */
int pedir_truco(int* valor_rodada) {
	int ch, resp;
	srand(time(NULL));
	if ((*valor_rodada) == 1) {
		resp = rand() % 2;
		if (resp == 1) {
			printf("\nPedido de truco recusado\n");
			printf("\n------------------------\nTime 1 ganhou a rodada \n------------------------\n\n");
			return 1;

		}
		else {
			printf("\nPedido de truco aceito\n");
			(*valor_rodada) = 3;
		}
	}
	while (1)
	{
		printf("\n\nPedir para aumentar aposta? 1-SIM / 2-NÃO ");
		scanf("%d", &ch);
		switch (ch)
		{
		case 1:
			resp = rand() % 2;
			if (resp == 1) {
				printf("\nPedido de truco recusado\n");
				printf("\n------------------------\nTime 1 ganhou a rodada \n------------------------\n\n");
				return 1;
			}
			else {
				printf("\nPedido de truco aceito\n");
				(*valor_rodada) += 3;
			}
			if ((*valor_rodada) == 12) {
				return 0;
			}
			break;
		case 2:
			return 0;
			break;
		default:
			printf("\nEscolha incorra, por favor digite novamente");
		}
	}
}

/*Verificar ganhador da rodada*/
int verificar_pontos_rodada(int valor, int jogador1[], int jogador2[], int jogador3[], int jogador4[], int *rodada, int manilha[], int ch, int* pontos_time1, int* pontos_time2, int* empate, int vencedor_primeira) {
	int i, time1 = 0, time2 = 0, manilha_maior = -1, vencendor_rodada;
	for (i = 0;i<4;i++) {
		if ((manilha[i] == jogador1[ch - 1])) {
			if (manilha_maior <= manilha[i]) {
				manilha_maior = manilha[i];
				time1 = 1;
				time2 = 0;
				vencendor_rodada = 1;
			}
		}
		if ((manilha[i] == jogador2[valor])) {
			if (manilha_maior <= manilha[i]) {
				manilha_maior = manilha[i];
				time1 = 1;
				time2 = 0;
				vencendor_rodada = 3;
			}
		}
		if ((manilha[i] == jogador3[valor])) {
			if (manilha_maior <= manilha[i]) {
				manilha_maior = manilha[i];
				time2 = 1;
				time1 = 0;
				vencendor_rodada = 2;
			}
		}
		if ((manilha[i] == jogador4[valor])) {
			if (manilha_maior <= manilha[i]) {
				manilha_maior = manilha[i];
				time2 = 1;
				time1 = 0;
			}
			vencendor_rodada = 4;
		}
	}
	if ((time1>0) || (time2>0)) {
		if (time1>time2) {
			printf("\n\t\t------------------------\n\t\tTime 1 ganhou a rodada \n\t\t------------------------\n\n");
			(*pontos_time1) += 1;
			return vencendor_rodada;
		}
		else {
			printf("\n\t\t------------------------\n\t\tTime 2 ganhou a rodada \n\t\t------------------------\n\n");
			(*pontos_time2) += 1;
			return vencendor_rodada;
		}
	}

	if ((((jogador1[ch - 1] % 10)>(jogador3[valor] % 10)) && ((jogador1[ch - 1] % 10)>(jogador4[valor] % 10))) || (((jogador2[valor] % 10)>(jogador3[valor] % 10)) && ((jogador2[valor] % 10)>(jogador4[valor] % 10)))) {
		printf("\n\t\t------------------------\n\t\tTime 1 ganhou a rodada \n\t\t------------------------\n\n");
		(*pontos_time1) += 1;
		if ((jogador1[ch - 1] % 10)>(jogador2[valor] % 10)) {
			vencendor_rodada = 1;
			return vencendor_rodada;
		}
		else if ((jogador1[ch - 1] % 10)<(jogador2[valor] % 10)) {
			vencendor_rodada = 3;
			return vencendor_rodada;
		}
		else if ((jogador1[ch - 1])>(jogador2[valor])) {
			vencendor_rodada = 1;
			return vencendor_rodada;
		}
		else {
			vencendor_rodada = 3;
			return vencendor_rodada;
		}
	}
	else if ((((jogador3[valor] % 10)>(jogador1[ch - 1] % 10)) && ((jogador3[valor] % 10)>(jogador2[valor] % 10))) || (((jogador4[valor] % 10)>(jogador1[ch - 1] % 10)) && ((jogador4[valor] % 10)>(jogador2[valor] % 10)))) {
		printf("\n\t\t------------------------\n\t\tTime 2 ganhou a rodada \n\t\t------------------------\n\n");
		(*pontos_time2) += 1;
		if ((jogador3[valor] % 10)>(jogador4[valor] % 10)) {
			vencendor_rodada = 2;
			return vencendor_rodada;
		}
		else if ((jogador3[valor] % 10)<(jogador4[valor] % 10)) {
			vencendor_rodada = 4;
			return vencendor_rodada;
		}
		else if ((jogador3[valor])>(jogador4[valor])) {
			vencendor_rodada = 2;
			return vencendor_rodada;
		}
		else {
			vencendor_rodada = 4;
			return vencendor_rodada;
		}
	}
	else {
		partida_empate(rodada, empate, pontos_time1, pontos_time2, vencedor_primeira, &vencendor_rodada);
		return vencendor_rodada;
	}
	return 0;
}

void partida_empate(int* rodada, int* empate, int* pontos_time1, int* pontos_time2, int vencedor_primeira, int *vencendor_rodada) {
	printf("\n\t\t------------------------\n\t\t\tEMPATE \n\t\t------------------------\n\n");

	if ((*rodada) == 0) {
		(*rodada)++;
		(*empate)++;
		(*vencendor_rodada) = 1;
	}
	else if ((((*rodada) == 1) || ((*rodada) == 2)) && ((*empate) == 0)) {
		if ((*pontos_time1) != (*pontos_time2)) {
			if (((vencedor_primeira) == 1) || ((vencedor_primeira) == 2)) {
				(*pontos_time1) = 3;
			}
			else {
				(*pontos_time2) = 3;
			}
		}
		(*vencendor_rodada) = vencedor_primeira;
		(*rodada)++;
	}
}

/* Mostra cartas jogadas na rodada */
int visual_cartas_jogadores(int jogador1[], int jogador2[], int jogador3[], int jogador4[], int valor, int vencendor_rodada, int vira, int* valor_rodada, int* pontos_time1, int empate) {
	int n = 0, y = 0, i, s = 0, j, ch, truco;
	char valornaipe[4][8] = { "OURO ","ESPADA ","COPAS ","PAUS " };
	char valorcarta[10][8] = { "QUATRO","CINCO","SEIS","SETE","DAMA","VALETE","REI","AS","DOIS","TRES" };

	for (j = 0;j <= 4;) {

		if (vencendor_rodada == 2) {
			Sleep(800);
			printf("\n\t------------------------\n\t ADVERSÁRIO 1 \n\t------------------------\n\n");
			for (i = 0;i<MAX;i++) {
				if (i == jogador3[valor]) {
					printf("\t%s %s \n", valornaipe[n], valorcarta[y]);
				}
				if (i == 9 + s) {
					n += 1;
					y = -1;
					s += 10;
				}
				y++;
			}
			n = 0;y = 0;s = 0;j++;
			vencendor_rodada++;
			if (j == 4) {
				return ch;
			}
		}

		if (vencendor_rodada == 3) {
			Sleep(800);
			printf("\n\t------------------------\n\t PARCEIRO \n\t------------------------\n\n");
			for (i = 0;i<MAX;i++) {
				if (i == jogador2[valor]) {
					printf("\t%s %s \n", valornaipe[n], valorcarta[y]);
				}
				if (i == 9 + s) {
					n += 1;
					y = -1;
					s += 10;
				}
				y++;
			}
			n = 0;y = 0;s = 0;j++;
			vencendor_rodada++;
			if (j == 4) {
				return ch;
			}
		}

		if (vencendor_rodada == 4) {
			Sleep(800);
			printf("\n\t------------------------\n\t ADVERSÁRIO 2\n\t------------------------\n\n");
			for (i = 0;i<MAX;i++) {
				if (i == jogador4[valor]) {
					printf("\t%s %s \n", valornaipe[n], valorcarta[y]);
				}
				if (i == 9 + s) {
					n += 1;
					y = -1;
					s += 10;
				}
				y++;
			}
			n = 0;y = 0;s = 0;j++;
			vencendor_rodada = 1;
			if (j == 4) {
				return ch;
			}
		}

		if (vencendor_rodada == 1) {
			Sleep(200);
			visual(jogador1, valor, vira, empate);
			printf("4 - PEDIR TRUCO");
			printf("\n5 - Voltar ao menu inicial");
			printf("\n\nEscolha uma opção: ");
			do {
				scanf("%d", &ch);
			} while ((ch>5));
			if (ch == 4) {
				truco = pedir_truco(valor_rodada);
				if (truco == 1) {
					(*pontos_time1) = 3;
					return 4;
				}
				printf("\n\nEscolha uma carta: ");
				scanf("%d", &ch);
			}
			printf("\n\t------------------------\n\t VOCÊ \n\t------------------------\n\n");
			for (i = 0;i<MAX;i++) {

				if (i == jogador1[ch - 1]) {
					printf("\t%s %s \n", valornaipe[n], valorcarta[y]);
				}
				if (i == 9 + s) {
					n += 1;
					y = -1;
					s += 10;
				}
				y++;
			}
			n = 0;y = 0;s = 0;j++;
			vencendor_rodada++;
			if (j == 4) {
				return ch;
			}
		}
	}
	return 0;
}

/*Passa carta do jogador para o inicio de sua mão */
void carta_final(int jogador1[], int ch) {
	int i;
	for (i = 0; i <= 3; i++)
	{
		if (jogador1[ch - 1] == jogador1[i])
		{
			for (; i < 3; i++)
			{
				jogador1[i] = jogador1[i + 1];
			}
		}
	}
}

/*Verifica ganhador da mao e atribui os pontos ao total do time ganhador */
void verificar_ganhador_rodada(int *total_time1, int *total_time2, int pontos_time1, int pontos_time2, int valor_rodada) {
	if (pontos_time1>pontos_time2) {
		printf("\n\n\n\t\t\t---------------------------\n\t\t\t*** TIME 1 GANHOU A MÃO ***\n\t\t\t---------------------------\n");
		(*total_time1) += valor_rodada;
	}
	else {
		printf("\n\n\n\t\t\t---------------------------\n\t\t\t*** TIME 2 GANHOU A MÃO ***\n\t\t\t---------------------------\n");
		(*total_time2) += valor_rodada;
	}
	printf("\n\n\n\t\t\t\t------------\n\t\t\t\tPLACAR TOTAL\n\t\t\t\t------------\n");
	printf("\n\t\t\t\tTIME 1\n\t\t\t\t%d\n", (*total_time1));
	printf("\n\t\t\t\tTIME 2\n\t\t\t\t%d\n\n", (*total_time2));
}

void vencedor_jogo(int total_time1, int total_time2) {
	if (total_time1 >= 12) {
		printf("\n\n\n\t\t\t---------------------------\n\t\t\t*** TIME 1 GANHOU O JOGO ***\n\t\t\t---------------------------\n\n\n");
		system("\npause\n");
		main();
	}
	if (total_time2 >= 12) {
		printf("\n\n\n\t\t\t---------------------------\n\t\t\t*** TIME 2 GANHOU O JOGO ***\n\t\t\t---------------------------\n\n\n");
		system("\npause\n");
		main();
	}
}

