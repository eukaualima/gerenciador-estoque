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
	char nome[50];
	char id[50];
};
typedef struct _PRODUTO_ T_PRODUTO;

/*
=------------------=
=-> Subprogramas <-=
=------------------=
*/
// < Fun��o para cria��o/abertura do arquivo >
FILE *criarArquivo(char filename[])
{
	// < Declara��o de vari�veis locais >
	FILE *arq;
	
	// < Abre (ou cria) o arquivo >	
	arq = fopen(filename, "ab");
	
	// < Retorna o arquivo aberto >
	return arq;
}

// < Fun��o para gerar sigla de produtos >
char *addSigla(char *sigla)
{
	// < Declara��o de vari�veis locais >
	char novo_nome[50] = "-";
	
	// < Coleta as tr�s letras iniciais >
	strncat(novo_nome, sigla, 3);
	
	strcpy(sigla, novo_nome);
	
	// < Retorna o id gerado >
	return sigla;
}

// < Procedimento para inser��o de produtos na lista >
void inserirProdutos()
{
	// < Declara��o de vari�veis locais >
	int cancelar;
	char sigla[4];
	T_PRODUTO produto;
	
	// < Cria ou inicia o arquivo >
	FILE *arq = criarArquivo("produtos.dat");
	
	// < Entrada de dados >
	do
	{
		printf("\n>--------<[ Informa��es do produto ]>--------<\n");
		
		printf("Nome: ");
		scanf("%s", produto.nome);
		
		printf("Valor: R$");
		scanf("%f", &produto.valor);
		
		printf("Quantidade (pode mudar depois!): ");
		scanf("%i", &produto.quantidade);
		
		printf("ID num�rico: ");
		scanf("%s", produto.id);
		
		strcpy(sigla, produto.nome);
		
		// < Gera a sigla do produto >
		addSigla(sigla);
		
		// < Concatena o ID num�rico com a sigla >
		strcat(produto.id, sigla);
		
		printf("[!] Sucesso! O produto \"%s\" foi criado com ID %s\n", produto.nome, produto.id);
		
		// < Escreve no arquivo >
		fwrite(&produto, sizeof(T_PRODUTO), 1, arq);
		
		printf("[!] Adicionar mais produtos? Digite 1 para N�O ou 0 par SIM: ");
		scanf("%i", &cancelar);
		
	} while (cancelar != 1);
	
	// < Fecha o arquivo >
	fclose(arq);
}

// < Procedimento para mostrar os produtos registrados >
void mostrarProdutos()
{
	// < Declara��o de vari�veis locais>
	char linha[20];
	int buffer[10];
	
	FILE *arq = fopen("produtos.dat", "rb");
	
	printf("\n>-----------------<[ P R O D U T O S ]>-----------------<\n");
	
	while(fgets(linha, 20, arq) != NULL)
	{
		fread(buffer,sizeof(T_PRODUTO),10,arq);
	}
	system("pause");
}

// < Procedimento para o menu principal do programa >
void menu()
{
	// < Declara��o de vari�veis locais >
	int opcao;
	
	// < Entrada de dados >
	do
	{
		printf(">-----------------<[ A R M A Z � M ]>-----------------<\nEscolha abaixo uma das op��es que deseja acessar:\n[1]: Estoque\n\t=> Adicionar novos produtos no estoque.\n[2]: Base de dados\n\t=> Verificar o que est� em estoque.\n[3]: Sair do programa.\n\nSua escolha: ");
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
