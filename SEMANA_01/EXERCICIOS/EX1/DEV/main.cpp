#include <stdio.h>
#include <stdlib.h>

// 1 -  Faça uma função que recebe uma certa medida e ajusta ela percentualmente
// entre dois valores mínimo e máximo e retorna esse valor
int ajusta()
{
	int num, porcen, max, min, resultado;

	// o usuário coloca o valor maximo da lista que deseja
	printf("Digite o valor maximo: ");
	scanf("%d", &max);

	// o usuário coloca o valor minimo da lista que deseja
	printf("Digite o valor minimo: ");
	scanf("%d", &min);

	// o usuário digita o valor que será convertido percentualmente
	printf("Coloque o valor que deseja retornar: ");
	scanf("%d", &num);

	// conversão para percentual com base no último valor
	porcen = (num - min) * 100 / (max - min);

	// resposta final
	printf("Valor em percentual: %d%c", porcen, 37);
}
// 2 - Faça uma função que simule a leitura de um sensor lendo o
// valor do teclado ao final a função retorna este valor
int leitura()
{
	int num;
	printf("Leitura do sensor: %d", num);

	return num;
}
// 3 - Faça uma função que armazena uma medida inteira qualquer
// em um vetor fornecido. Note que como C não possui vetores
// nativos da linguagem, lembre-se que você precisa passar o
// valor máximo do vetor assim como a última posição preenchida
// Evite também que, por acidente, um valor seja escrito em
// uma área de memória fora do vetor
int armazena()
{
	int cap, x, i;

	scanf("%d", &cap);
	printf("%d", cap);

	int vetor[cap];

	for (x = 0; x < cap; x++)
	{
		scanf("%d", &vetor[x]);
	}

	for (i = 0; i < cap; i++)
	{
		if (i == 0)
		{
			printf("[ %d", vetor[0]);
		}
		else if (i == cap - 1)
		{
			printf(", %d]", vetor[cap]);
		}
		else
		{
			printf(", %d", vetor[i]);
		}
	}
}

// 4 - Faça uma função que recebe um vetor com 4 posições que contém
// o valor da distância de um pequeno robô até cada um dos seus 4 lados.
// A função deve retornar duas informações: A primeira é a direção
// de maior distância ("Direita", "Esquerda", "Frente", "Tras") e a
// segunda é esta maior distância.
int posicao()
{
    int vetor[4], x,i;
    i = 1;
    for (x = 0; x < 4; x++)
    {   printf("Digite o %d%c valor:",i,248);
        i++;
        scanf("%d", &vetor[x]);
    }

    if (vetor[0] > vetor[1] && vetor[0] > vetor[2] && vetor[0] > vetor[3])
    {   
        printf("Dire%c%co: Direita\nMaior dist%cncia: %d",135,198,131,vetor[0]);

     } else if (vetor[1] > vetor[2] && vetor[1] > vetor[3])
            {
                printf("Dire%c%co: Esquerda\nMaior dist%cncia: %d",135,198,131,vetor[1]);
            }
        
        else
            if (vetor[2] > vetor[3])
            {
                printf("Dire%c%co: Frente\nMaior dist%cncia: %d",135,198,131,vetor[2]);
            }
        
        else
        {
            printf("Dire%c%co: Tr%cs\nMaior dist%cncia: %d",135,198,160,131,vetor[3]);
        }
    }
// 5 - Faça uma função que pergunta ao usuário se ele deseja continuar o mapeamento e
// retorna verdadeiro ou falso

// 6 - A função abaixo (que está incompleta) vai "dirigindo" virtualmente um robô
// e através de 4 sensores em cada um dos 4 pontos do robo ("Direita", "Esquerda",
// "Frente", "Tras").
//      A cada passo, ele verifica as distâncias aos objetos e vai mapeando o terreno
// para uma movimentação futura.
//      Ele vai armazenando estas distancias em um vetor fornecido como parâmetro
// e retorna a ultima posicao preenchida do vetor.
//      Esta função deve ir lendo os 4 sensores até que um comando de pare seja enviado
//
//      Para simular os sensores e os comandos de pare, use as funções já construídas
// nos ítens anteriores e em um looping contínuo até que um pedido de parada seja
// enviado pelo usuário.
//
//      Complete a função com a chamada das funções já criadas
// int dirige(int *v,int maxv){
// 	int maxVetor = maxv;
// 	int *vetorMov = v;
// 	int posAtualVetor = 0;
// 	int dirigindo = 1;
// 	while(dirigindo){
// 		int medida = /// .. Chame a função de de leitura da medida para a "Direita"
// 		medida = converteSensor(medida,0,830);
// 		posAtualVetor = // Chame a função para armazenar a medida no vetor
//         ///////////////////////////////////////////////////////////////////////////
// 		// Repita as chamadas acima para a "Esquerda", "Frente", "Tras"
// 		// ................
// 		///////////////////////////////////////////////////////////////////////////
// 		dirigindo = leComando();
// 	}
// 	return posAtualVetor;
// }

// O trecho abaixo irá utilizar as funções acima para ler os sensores e o movimento
// do robô e no final percorrer o vetor e mostrar o movimento a cada direção baseado
// na maior distância a cada movimento
// void percorre(int *v,int tamPercorrido){
// 	int *vetorMov = v;
// 	int maiorDir = 0;

// 	for(int i = 0; i< tamPercorrido; i+=4){
// 		char *direcao = direcaoMenorCaminho(&(vetorMov[i]),&maiorDir);
// 		printf("Movimentando para %s distancia = %i\n",direcao,maiorDir);s
// 	}
// }

// int main(int argc, char** argv) {
// 	int maxVetor = 100;
// 	int vetorMov[maxVetor*4];
// 	int posAtualVet = 0;

// 	posAtualVet = dirige(vetorMov,maxVetor);
// 	percorre(vetorMov,posAtualVet);

// 	return 0;
// }