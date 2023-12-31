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

// < Procedimento para mostrar os produtos registrados >
void mostrarProdutos(T_PRODUTO p)
{
	// < Declara��o de vari�veis locais >
	int i = 0;

	if (p == NULL)
	{
		printf("| ! | Lista vazia.\n");
	}
	else
	{
		printf("<---------------------<[ P R O D U T O S ]--------------------->\n");

		while (p != NULL)
		{
			i++;
			// < Imprime o produto >
			printf("<-<| %i |>->\tID: %s\tNome: %s\tValor: R$ %.2f\tQtd.: %i\n\n", i, p->id, p->nome, p->valor, p->quantidade);
			
			// < Anda na lista >
			p = p->prox;
		}
	}
}

// < Procedimento para deixar os produtos em ordem alfab�tica >
void ordemAlfabetica(T_PRODUTO p)
{
    // < Declara��o de vari�veis locais >
    T_PRODUTO aux, prox;
    int qtd_aux;
    float valor_aux;
    char nome_aux[50], id_aux[50];
    int trocou;

    do 
	{
        trocou = 0; // deixa a flag falsa para caso n�o haja trocas o loop parar

        aux = p;

        // < Percorre a lista >
        while (aux->prox != NULL)
        {
            prox = aux->prox;

            if (strcmp(aux->nome, prox->nome) > 0)
            {
                strcpy(nome_aux, prox->nome);
                strcpy(prox->nome, aux->nome);
                strcpy(aux->nome, nome_aux);

                // < Troca os IDs dos produtos >
                strcpy(id_aux, aux->id);
                strcpy(aux->id, prox->id);
                strcpy(prox->id, id_aux);

                // < Troca os pre�os dos produtos >
                valor_aux = aux->valor;
                aux->valor = prox->valor;
                prox->valor = valor_aux;

                // < Troca a quantidade de unidades do produto >
                qtd_aux = aux->quantidade;
                aux->quantidade = prox->quantidade;
                prox->quantidade = qtd_aux;

                trocou = 1; // Faz a troca e deixa a flag verdadeira para n�o parar o loop
            }

            // < Anda na lista >
            aux = aux->prox;
        }

    } while (trocou);
}

// < Procedimento para inser��o de produtos na lista >
T_PRODUTO inserirProdutos(T_PRODUTO p, int *qtd_produtos)
{
	// < Declara��o de vari�veis locais >
	int cancelar, quantidade;
	float valor;
	char sigla[4], nome[50], qtd_produtos_str[64];
	
	// < Entrada de dados >
	do
	{
		printf("\n>--------<[ Informa��es do produto ]>--------<\n");
		
		printf("Nome: ");
		scanf("%s", nome);
		
		printf("Valor: R$");
		scanf("%f", &valor);
		
		printf("Quantidade: ");
		scanf("%i", &quantidade);
		
		(*qtd_produtos)++;
		
		strcpy(sigla, nome);
		
		// < Gera a sigla do produto >
		addSigla(sigla);

		// < Converte int para string >
		if (*qtd_produtos < 10)
		{
			sprintf(qtd_produtos_str, "00%i", *qtd_produtos);
		}
		else if (*qtd_produtos < 100)
		{
			sprintf(qtd_produtos_str, "0%i", *qtd_produtos);
		}
		else
		{
			sprintf(qtd_produtos_str, "%i", *qtd_produtos);
		}

		// < Concatena o ID num�rico com a sigla >
		strcat(qtd_produtos_str, sigla);

		// < Verifica se a lista est� vazia, se estiver cria uma nova >
		if (p == NULL)
		{
			p = criarProduto(quantidade, valor, nome, qtd_produtos_str);
		}
		else
		{
			p = adicionarProduto(quantidade, valor, nome, qtd_produtos_str, p);
		}
		
		ordemAlfabetica(p);

		printf("[!] Sucesso! O produto \"%s\" foi criado com ID %s\n", nome, qtd_produtos_str);
		
		printf("[!] Adicionar mais produtos? Digite 1 para N�O ou 0 par SIM: ");
		scanf("%i", &cancelar);
		
	} while (cancelar != 1);

	return p;
}

// < Procedimento para o menu principal do programa >
void menu()
{
	// < Declara��o de vari�veis locais >
	int opcao, qtd_produtos = 0;
	T_PRODUTO p = NULL;

	// < Entrada de dados >
	do
	{
		printf(">-----------------<[ A R M A Z � M ]>-----------------<\nEscolha abaixo uma das op��es que deseja acessar:\n[1]: Estoque\n\t=> Adicionar novos produtos no estoque.\n[2]: Base de dados\n\t=> Verificar o que est� em estoque.\n[3]: Sair do programa.\n\nSua escolha: ");
		scanf("%i", &opcao);
		
		switch(opcao)
		{
			case 1:
				p = inserirProdutos(p, &qtd_produtos);
			break;
			
			case 2:
				mostrarProdutos(p);
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
	setlocale(LC_ALL, "");
	
	// < Inicia o menu principal >
	menu();
}

