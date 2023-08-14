#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

void Cardapio(char produto[21][50], float preco_produto[21]) {
    strcpy(produto[1], "Calabresa");
    strcpy(produto[2], "Frango com catupiry");
    strcpy(produto[3], "Frango com Bacon");
    strcpy(produto[4], "Quatro queijos");
    strcpy(produto[5], "Portuguesa");
    strcpy(produto[6], "Bacon");
    strcpy(produto[7], "Chocolate");
    strcpy(produto[8], "Romeu e Julieta");
    strcpy(produto[9], "Chocolate com Banana");
    strcpy(produto[10], "Banana com canela");
    strcpy(produto[11], "Coca-Cola");
    strcpy(produto[12], "Fanta Laranja");
    strcpy(produto[13], "Pepsi");
    strcpy(produto[14], "Guaraná Antarctica");
    strcpy(produto[15], "Suco de Laranja");
    strcpy(produto[16], "Suco de Maracujá");
    strcpy(produto[17], "Suco de Limão");
    strcpy(produto[18], "Guaraná Jesus");
    strcpy(produto[19], "Água");
    strcpy(produto[20], "Água com gás");

    preco_produto[1] = 24.90;
    preco_produto[2] = 29.90;
    preco_produto[3] = 31.90;
    preco_produto[4] = 29.90;
    preco_produto[5] = 31.90;
    preco_produto[6] = 24.90;
    preco_produto[7] = 29.90;
    preco_produto[8] = 24.90;
    preco_produto[9] = 24.90;
    preco_produto[10] = 24.90;
    preco_produto[11] = 6.50;
    preco_produto[12] = 6.00;
    preco_produto[13] = 6.00;
    preco_produto[14] = 6.00;
    preco_produto[15] = 7.50;
    preco_produto[16] = 7.50;
    preco_produto[17] = 7.50;
    preco_produto[18] = 6.00;
    preco_produto[19] = 5.00;
    preco_produto[20] = 5.50;
    
    printf("Cardápio:\n");
    printf("---------\n");

    for (int i = 1; i < 21; i++)
    {
        printf("%d. Produto: %s\n", i, produto[i]);
        printf("   Preço: R$ %.2f\n", preco_produto[i]);
        printf("---------\n");
    }
}


void CarrinhoPedido(char carrinho[][50], float preco_produto[], int quantidade_produto[], float totalPreco) {
    printf(" \n========\nCARRINHO:\n");
    for (int i = 1; i < 21; i++) {
        if (carrinho[i][0] != '\0' && quantidade_produto[i] > 0) {
            printf("CODIGO %d - %s  -  R$ %.2f - QTD: %d\n", i, carrinho[i], preco_produto[i], quantidade_produto[i]);
        }
        if (i == 20) {
            printf("PRECO TOTAL: R$ %.2f\n", totalPreco);
        }
    }
    printf("========\n\n");
}


void Pedido(int numeroProduto, char produto[21][50], float preco_produto[21], int *totalProdutos, float *totalPreco) {
    int quantidade_produto[21] = {0};
    float total_produto[21] = {0.0};

    *totalProdutos = 0;
    *totalPreco = 0.0;
    char carrinho[21][50];
    
    while (numeroProduto != 0)
    {
        printf("\nDigite o codigo do produto desejado (ou 0 para finalizar): ");
        scanf("%d", &numeroProduto);

        if (numeroProduto > 0 && numeroProduto <= 20)
        {
            printf("Produto escolhido: %s\n", produto[numeroProduto]);
            printf("Preço: R$ %.2f\n", preco_produto[numeroProduto]);

            int quantidade;
            do {
            printf("Digite a quantidade desejada: ");
            scanf("%d", &quantidade);
            } while (quantidade <= 0);

            float valor_total_produto = preco_produto[numeroProduto] * quantidade;

            *totalProdutos = *totalProdutos + quantidade;
            *totalPreco = *totalPreco + valor_total_produto;

            quantidade_produto[numeroProduto] = quantidade_produto[numeroProduto] + quantidade;
            total_produto[numeroProduto] += valor_total_produto;
            
            strcpy(carrinho[numeroProduto], produto[numeroProduto]);
            
            system(CLEAR_COMMAND);
            Cardapio(produto, preco_produto);
            CarrinhoPedido(carrinho, preco_produto, quantidade_produto, *totalPreco);
        }
        else
        {
            printf("Número de produto inválido.\n");
        }
    }
    
    system(CLEAR_COMMAND);
}


int Comparar(float a, float b) {
    float y = 0.0001;
    return (a - b) < y && (b - a) < y;
}

int Pagamento(float totalPreco) {
    float TotalPago = 0.0;
    int opcao;

    printf("\nEscolha a forma de pagamento (ou 0 para cancelar):\n");
    printf("1. PIX\n");
    printf("2. Cartão de crédito/débito\n");
    printf("3. Dinheiro\n\n");

    while (TotalPago < totalPreco) {
        printf("Faltam R$ %.2f para pagamento.", totalPreco - TotalPago);
        printf("\n");
        do {
            printf("Opção de pagamento: ");
            scanf("%d", &opcao);
        } while (opcao != 1 && opcao != 2 && opcao!= 3 && opcao != 0);

        if (opcao == 0) {
            printf("Pagamento cancelado. Pedido não finalizado.\n");
            return 0;
        }

        float valor;
        switch (opcao) {
            case 1:
                printf("Digite o valor do PIX: R$ ");
                scanf("%f", &valor);
                break;
            case 2:
                printf("Digite o valor do cartão: R$ ");
                scanf("%f", &valor);
                break;
            case 3:
                printf("Digite o valor em dinheiro: R$ ");
                scanf("%f", &valor);
                break;
            default:
                printf("Opção de pagamento inválida. Tente novamente.\n");
                continue;
        }

        TotalPago += valor;

        if (TotalPago >= totalPreco) {
            if (Comparar(TotalPago, totalPreco)) {
                printf("\nPagamento realizado com sucesso!\n");
                return 1;
            } else {
                printf("-------------------------------------------\n");
                printf("Pagamento não corresponde ao valor total da venda.\n");
                printf("Sobra: R$ %.2f\n", TotalPago - totalPreco);
                printf("Por favor, pague o valor correto para finalizar o pedido.\n");
                TotalPago = 0.0;
            }
        }
    }

    return 0;
}

void NotaFiscal(char produto[][50], int quantidade_produto[], float preco_produto[], float total_produto[], int totalProdutos, float totalPreco) {
    if (totalProdutos > 0) {
        printf("Nota Fiscal:\n");
        printf("-------------\n");

        for (int i = 1; i <= 20; i++) {
            if (quantidade_produto[i] > 0) {
                printf("Código do Produto: %d\n", i);
                printf("Nome do Produto: %s\n", produto[i]);
                printf("Quantidade: %d\n", quantidade_produto[i]);
                printf("Valor Unitário: R$ %.2f\n", preco_produto[i]);
                printf("Valor Total: R$ %.2f\n", total_produto[i]);
                printf("-------------\n\n");
            }
        }
        printf("Total de produtos: %d\n", totalProdutos);
        printf("Total a pagar: R$ %.2f\n", totalPreco);
    } else {
        printf("Nenhum produto foi escolhido.\n");
    }

    if (Pagamento(totalPreco)) {
        printf("Pedido finalizado, obrigado pela preferência e volte sempre!\n");
    } else {
        printf("Nenhum produto foi escolhido.\n");
    }
}



int main()
{
    char produto[21][50];
    float preco_produto[21];
    Cardapio(produto, preco_produto);
    
    int quantidade_produto[21] = {0};
    float total_produto[21] = {0.0};

    int totalProdutos = 0;
    float totalPreco = 0.0;
    char carrinho[21][50];
    int numeroProduto = 1;
    
    Pedido(numeroProduto, produto, preco_produto, &totalProdutos, &totalPreco);
    
    NotaFiscal(produto, quantidade_produto, preco_produto, total_produto, totalProdutos, totalPreco);

    return 0;
}