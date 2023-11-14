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

/*
=----------------=
=-> Estruturas <-=
=----------------=
*/
// < Struct para os produtos >
struct _PRODUTO_ 
{
	int quantidade;
	float valor;
	unsigned char nome[50];
	unsigned char id[50];
};
typedef struct _PRODUTO_ T_PRODUTO;

/*
=------------------=
=-> Subprogramas <-=
=------------------=
*/
// < Função para criação/abertura do arquivo >
FILE *criarArquivo(char filename[])
{
	// < Declaração de variáveis locais >
	FILE *arq;
	
	// < Abre (ou cria) o arquivo >	
	arq = fopen(filename, "a");
	
	// < Retorna o arquivo aberto >
	return arq;
}

// < Função para gerar sigla de produtos >
unsigned char *addSigla(unsigned char *sigla)
{
	// < Declaração de variáveis locais >
	unsigned char novo_nome[50] = "-";
	
	// < Coleta as três letras iniciais >
	strncat(novo_nome, sigla, 3);
	
	strcpy(sigla, novo_nome);
	
	// < Retorna o id gerado >
	return sigla;
}

// < Procedimento para inserção de produtos na lista >
void inserirProdutos()
{
	// < Declaração de variáveis locais >
	int i, cancelar, produtos;
	unsigned char sigla[4];
	T_PRODUTO produto[10];
	
	// < Cria ou inicia o arquivo >
	FILE *arq = criarArquivo("produtos.txt");
	
	// < Entrada de dados >
	i = 0;
	produtos = 0;
	
	do
	{
		printf("\n>--------<[ Informações do produto %i/10 ]>--------<\n", i+1);
		
		printf("Nome: ");
		scanf("%s", produto[i].nome);
		
		printf("Valor: R$");
		scanf("%f", &produto[i].valor);
		
		printf("Quantidade (pode mudar depois!): ");
		scanf("%i", &produto[i].quantidade);
		
		printf("ID numérico: ");
		scanf("%s", produto[i].id);
		
		strcpy(sigla, produto[i].nome);
		
		// < Gera a sigla do produto >
		addSigla(sigla);
		
		// < Concatena o ID numérico com a sigla >
		strcat(produto[i].id, sigla);
		
		printf("[!] Sucesso! O produto \"%s\" foi criado com ID %s\n", produto[i].nome, produto[i].id);
		
		// < Escreve no arquivo >
		fprintf(arq, "\nProduto %s\nNome: %s\nValor: R$%.2f\nQuantidade: %i\n", produto[i].id, produto[i].nome, produto[i].valor, produto[i].quantidade);
		
		printf("[!] Adicionar mais produtos? Digite 1 para NÃO ou 0 par SIM: ");
		scanf("%i", &cancelar);
		
		i++;
	} while (cancelar != 1 && i < 10);
	
	// < Fecha o arquivo >
	fclose(arq);
}

// < Procedimento para mostrar os produtos registrados >
void mostrarProdutos()
{
	// < Declaração de variáveis locais>
	unsigned char linha[20];
	
	FILE *arq = fopen("produtos.txt", "r");
	
	printf("\n>-----------------<[ P R O D U T O S ]>-----------------<\n");
	while(fgets(linha, 20, arq) != NULL)
	{
		printf("%s", linha);
	}
	system("pause");
}

// < Procedimento para o menu principal do programa >
void menu()
{
	// < Declaração de variáveis locais >
	int opcao;
	
	// < Entrada de dados >
	do
	{
		printf(">-----------------<[ A R M A Z É M ]>-----------------<\nEscolha abaixo uma das opções que deseja acessar:\n[1]: Estoque\n\t=> Adicionar novos produtos no estoque.\n[2]: Base de dados\n\t=> Verificar o que está em estoque.\n[3]: Sair do programa.\n\nSua escolha: ");
		scanf("%i", &opcao);
		
		switch(opcao)
		{
			case 1:
				inserirProdutos();
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

