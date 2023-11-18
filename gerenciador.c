/*
=---------------=
=-> Cabe�alho <-=
=---------------=
*/
/**
 * @author Kau� dos Santos Lima
 * @since 14/11/2023
 * @version 14/11/2023
 * @todo Considere uma situa��o em que voc� est� desenvolvendo um sistema de gerenciamento 
 * de estoque para um armaz�m. A lista de produtos no estoque � extensa e est� ordenada pelo 
 * nome do produto. Cada produto tem um identificador �nico.
 **/

/*
=--------------=
=-> Includes <-=
=--------------=
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

/*
=----------------=
=-> Estruturas <-=
=----------------=
*/
// < Struct para os n�s do estoque >
struct _PRODUTO_ 
{
	int quantidade;
	float valor; // (R$)
	char nome[50];
	char id[50]; // 123-ABC
	struct _PRODUTO_ *prox; // ponteiro para o pr�ximo elemento
};

typedef struct _PRODUTO_ *T_PRODUTO;

/*
=------------------=
=-> Subprogramas <-=
=------------------=
*/
// < Fun��o para inicializar a lista simplesmente encadeada dos produtos >
T_PRODUTO criarProduto(int quantidade, float valor, char nome[], char id[])
{
	// < Declara��o de vari�veis locais >
	T_PRODUTO p;

	// < Aloca espa�o na mem�ria para o novo produto >
	p = (T_PRODUTO)malloc(sizeof(T_PRODUTO));

	// < Cria o novo produto >
	p->quantidade = quantidade;
	p->valor = valor;
	strcpy(p->nome, nome);
	strcpy(p->id, id);
	p->prox = NULL;

	// < Retorna o produto criado >
	return p;
}

//< Fun��o para adicionar novos produtos � lista >
T_PRODUTO adicionarProduto(int quantidade, float valor, char nome[], char id[], T_PRODUTO proximo)
{
	// < Declara��o de vari�veis locais >
	T_PRODUTO p;

	// < Aloca��o de mem�ria >
	p = (T_PRODUTO)malloc(sizeof(T_PRODUTO));

	// < Cria o novo produto >
	p->quantidade = quantidade;
	p->valor = valor;
	strcpy(p->nome, nome);
	strcpy(p->id, id);
	p->prox = proximo;

	// < Retorna o produto criado >
	return p;
}

// < Fun��o para gerar sigla de produtos >
char *addSigla(char *sigla)
{
	// < Declara��o de vari�veis locais >
	char nova_sigla[50] = "-";

	// < Coleta as tr�s letras iniciais >
	strncat(nova_sigla, sigla, 3);
	
	// < Envia a nova sigla para a sigla original >
	strcpy(sigla, nova_sigla);
	
	// < Retorna o id gerado >
	return sigla;
}

// < Procedimento para inser��o de produtos na lista >
void inserirProdutos(T_PRODUTO p)
{
	// < Declara��o de vari�veis locais >
	int cancelar, quantidade;
	float valor;
	char sigla[4], nome[50], id[50];
	
	// < Entrada de dados >
	do
	{
		printf("\n>--------<[ Informa��es do produto ]>--------<\n");
		
		printf("Nome: ");
		scanf("%s", nome);
		
		printf("Valor: R$");
		scanf("%f", &valor);
		
		printf("Quantidade (pode mudar depois!): ");
		scanf("%i", &quantidade);
		
		printf("ID num�rico: ");
		scanf("%s", id);
		
		strcpy(sigla, nome);
		
		// < Gera a sigla do produto >
		addSigla(sigla);
		
		// < Concatena o ID num�rico com a sigla >
		strcat(id, sigla);

		// < Verifica se a lista est� vazia, se estiver cria uma nova >
		if (p == NULL)
		{
			p = criarProduto(quantidade, valor, nome, id);
		}
		else
		{
			p = adicionarProduto(quantidade, valor, nome, id, p);
		}
		
		printf("[!] Sucesso! O produto \"%s\" foi criado com ID %s\n", nome, id);
		
		printf("[!] Adicionar mais produtos? Digite 1 para N�O ou 0 par SIM: ");
		scanf("%i", &cancelar);
		
	} while (cancelar != 1);
}

// < Procedimento para mostrar os produtos registrados >
void mostrarProdutos()
{
	// < Declara��o de vari�veis locais>
	char linha[20];
	
	printf("\n>-----------------<[ P R O D U T O S ]>-----------------<\n");
	system("pause");
}

// < Procedimento para o menu principal do programa >
void menu()
{
	// < Declara��o de vari�veis locais >
	int opcao;
	T_PRODUTO p;

	p = NULL;
	
	// < Entrada de dados >
	do
	{
		printf(">-----------------<[ A R M A Z � M ]>-----------------<\nEscolha abaixo uma das op��es que deseja acessar:\n[1]: Estoque\n\t=> Adicionar novos produtos no estoque.\n[2]: Base de dados\n\t=> Verificar o que est� em estoque.\n[3]: Sair do programa.\n\nSua escolha: ");
		scanf("%i", &opcao);
		
		switch(opcao)
		{
			case 1:
				inserirProdutos(p);
			break;
			
			case 2:
				mostrarProdutos();
			break;
			
			case 3:
				exit(1);
			break;
			
			default:
				printf("\n\n[!] Escolha uma op��o v�lida.\n\n");
				
				menu();
			break;
		}
	} while (opcao != 3);	
}
/*
=------------------------=
=-> Programa Principal <-=
=------------------------=
*/
int main (void)
{
	// < Aceita os acentos no terminal >
	setlocale(LC_ALL, "Portuguese");
	
	// < Inicia o menu principal >
	menu();
}

