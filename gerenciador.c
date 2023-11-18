/*
=---------------=
=-> Cabeçalho <-=
=---------------=
*/
/**
 * @author Kauã dos Santos Lima
 * @since 14/11/2023
 * @version 14/11/2023
 * @todo Considere uma situação em que você está desenvolvendo um sistema de gerenciamento 
 * de estoque para um armazém. A lista de produtos no estoque é extensa e está ordenada pelo 
 * nome do produto. Cada produto tem um identificador único.
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
// < Struct para os nós do estoque >
struct _PRODUTO_ 
{
	int quantidade;
	float valor; // (R$)
	char nome[50];
	char id[50]; // 123-ABC
	struct _PRODUTO_ *prox; // ponteiro para o próximo elemento
};

typedef struct _PRODUTO_ *T_PRODUTO;

/*
=------------------=
=-> Subprogramas <-=
=------------------=
*/
// < Função para inicializar a lista simplesmente encadeada dos produtos >
T_PRODUTO criarProduto(int quantidade, float valor, char nome[], char id[])
{
	// < Declaração de variáveis locais >
	T_PRODUTO p;

	// < Aloca espaço na memória para o novo produto >
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

//< Função para adicionar novos produtos à lista >
T_PRODUTO adicionarProduto(int quantidade, float valor, char nome[], char id[], T_PRODUTO proximo)
{
	// < Declaração de variáveis locais >
	T_PRODUTO p;

	// < Alocação de memória >
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

// < Função para gerar sigla de produtos >
char *addSigla(char *sigla)
{
	// < Declaração de variáveis locais >
	char nova_sigla[50] = "-";

	// < Coleta as três letras iniciais >
	strncat(nova_sigla, sigla, 3);
	
	// < Envia a nova sigla para a sigla original >
	strcpy(sigla, nova_sigla);
	
	// < Retorna o id gerado >
	return sigla;
}

// < Procedimento para inserção de produtos na lista >
void inserirProdutos(T_PRODUTO p)
{
	// < Declaração de variáveis locais >
	int cancelar, quantidade;
	float valor;
	char sigla[4], nome[50], id[50];
	
	// < Entrada de dados >
	do
	{
		printf("\n>--------<[ Informações do produto ]>--------<\n");
		
		printf("Nome: ");
		scanf("%s", nome);
		
		printf("Valor: R$");
		scanf("%f", &valor);
		
		printf("Quantidade (pode mudar depois!): ");
		scanf("%i", &quantidade);
		
		printf("ID numérico: ");
		scanf("%s", id);
		
		strcpy(sigla, nome);
		
		// < Gera a sigla do produto >
		addSigla(sigla);
		
		// < Concatena o ID numérico com a sigla >
		strcat(id, sigla);

		// < Verifica se a lista está vazia, se estiver cria uma nova >
		if (p == NULL)
		{
			p = criarProduto(quantidade, valor, nome, id);
		}
		else
		{
			p = adicionarProduto(quantidade, valor, nome, id, p);
		}
		
		printf("[!] Sucesso! O produto \"%s\" foi criado com ID %s\n", nome, id);
		
		printf("[!] Adicionar mais produtos? Digite 1 para NÃO ou 0 par SIM: ");
		scanf("%i", &cancelar);
		
	} while (cancelar != 1);
}

// < Procedimento para mostrar os produtos registrados >
void mostrarProdutos()
{
	// < Declaração de variáveis locais>
	char linha[20];
	
	printf("\n>-----------------<[ P R O D U T O S ]>-----------------<\n");
	system("pause");
}

// < Procedimento para o menu principal do programa >
void menu()
{
	// < Declaração de variáveis locais >
	int opcao;
	T_PRODUTO p;

	p = NULL;
	
	// < Entrada de dados >
	do
	{
		printf(">-----------------<[ A R M A Z É M ]>-----------------<\nEscolha abaixo uma das opções que deseja acessar:\n[1]: Estoque\n\t=> Adicionar novos produtos no estoque.\n[2]: Base de dados\n\t=> Verificar o que está em estoque.\n[3]: Sair do programa.\n\nSua escolha: ");
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
				printf("\n\n[!] Escolha uma opção válida.\n\n");
				
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

