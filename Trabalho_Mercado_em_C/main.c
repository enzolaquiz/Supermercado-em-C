#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 50
#define MAX_CARRINHO 50

typedef struct {
    int codigo;
    char nome[30];
    float preco;
} Produto;

typedef struct {
    Produto produto;
    int quantidade;
} Carrinho;

Produto produtos[MAX_PRODUTOS];
Carrinho carrinho[MAX_CARRINHO];
int numProdutos = 0;
int numCarrinho = 0;

void menu();
void cadastrarProduto();
void listarProdutos();
void comprarProduto();
void visualizarCarrinho();
void fecharPedido();
void removerProdutoCarrinho();
int temNoCarrinho(int codigo);
int pegarProdutoPorCodigo(int codigo);
void infoProduto(Produto prod);

int main() {
    menu();
    return 0;
}

void menu() {
    int opcao;

    do {
        printf("\n=== Supermercado do Enzo ===\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Comprar Produto\n");
        printf("4. Visualizar Carrinho\n");
        printf("5. Remover Produto do Carrinho\n");
        printf("6. Fechar Pedido\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                listarProdutos();
                break;
            case 3:
                comprarProduto();
                break;
            case 4:
                visualizarCarrinho();
                break;
            case 5:
                removerProdutoCarrinho();
                break;
            case 6:
                fecharPedido();
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 7);
}

void cadastrarProduto() {
    if (numProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos cadastrados atingido!\n");
        return;
    }

    Produto prod;
    printf("\nDigite o codigo do produto: ");
    scanf("%d", &prod.codigo);
    printf("Digite o nome do produto: ");
    scanf("%s", prod.nome);
    printf("Digite o preco do produto: ");
    scanf("%f", &prod.preco);

    produtos[numProdutos] = prod;
    numProdutos++;

    printf("Produto cadastrado com sucesso!\n");
}

void listarProdutos() {
    if (numProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\n=== Lista de Produtos ===\n");
    for (int i = 0; i < numProdutos; i++) {
        infoProduto(produtos[i]);
    }
}

void comprarProduto() {
    if (numProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    int codigo;
    printf("Digite o codigo do produto a ser comprado: ");
    scanf("%d", &codigo);

    int indexProduto = pegarProdutoPorCodigo(codigo);
    if (indexProduto == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }

    int indexCarrinho = temNoCarrinho(codigo);
    if (indexCarrinho != -1) {
        carrinho[indexCarrinho].quantidade++;
        printf("Produto ja esta no carrinho. Quantidade atualizada.\n");
    } else {
        if (numCarrinho >= MAX_CARRINHO) {
            printf("Carrinho cheio!\n");
            return;
        }

        carrinho[numCarrinho].produto = produtos[indexProduto];
        carrinho[numCarrinho].quantidade = 1;
        numCarrinho++;

        printf("Produto adicionado ao carrinho.\n");
    }
}

void visualizarCarrinho() {
    if (numCarrinho == 0) {
        printf("Carrinho vazio.\n");
        return;
    }

    printf("\n=== Carrinho de Compras ===\n");
    for (int i = 0; i < numCarrinho; i++) {
        printf("Codigo: %d | Nome: %s | Preco: %.2f | Quantidade: %d\n",
               carrinho[i].produto.codigo, carrinho[i].produto.nome,
               carrinho[i].produto.preco, carrinho[i].quantidade);
    }
}

void fecharPedido() {
    if (numCarrinho == 0) {
        printf("Carrinho vazio. Nenhum pedido a fechar.\n");
        return;
    }

    float total = 0;
    printf("\n=== Fatura ===\n");
    for (int i = 0; i < numCarrinho; i++) {
        float subtotal = carrinho[i].produto.preco * carrinho[i].quantidade;
        printf("Codigo: %d | Nome: %s | Preco: %.2f | Quantidade: %d | Subtotal: %.2f\n",
               carrinho[i].produto.codigo, carrinho[i].produto.nome,
               carrinho[i].produto.preco, carrinho[i].quantidade, subtotal);
        total += subtotal;
    }
    printf("Total a pagar: %.2f\n", total);

    numCarrinho = 0;
    printf("Pedido finalizado e carrinho esvaziado.\n");
}

void removerProdutoCarrinho() {
    if (numCarrinho == 0) {
        printf("Carrinho vazio. Nenhum produto para remover.\n");
        return;
    }

    int codigo;
    printf("Digite o codigo do produto a ser removido: ");
    scanf("%d", &codigo);

    int indexCarrinho = temNoCarrinho(codigo);
    if (indexCarrinho == -1) {
        printf("Produto nao encontrado no carrinho!\n");
        return;
    }

    if (carrinho[indexCarrinho].quantidade > 1) {
        carrinho[indexCarrinho].quantidade--;
        printf("Quantidade do produto diminuída. Nova quantidade: %d\n", carrinho[indexCarrinho].quantidade);
    } else {
        for (int i = indexCarrinho; i < numCarrinho - 1; i++) {
            carrinho[i] = carrinho[i + 1];
        }
        numCarrinho--;
        printf("Produto removido do carrinho.\n");
    }
}

int temNoCarrinho(int codigo) {
    for (int i = 0; i < numCarrinho; i++) {
        if (carrinho[i].produto.codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int pegarProdutoPorCodigo(int codigo) {
    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void infoProduto(Produto prod) {
    printf("Codigo: %d | Nome: %s | Preco: %.2f\n", prod.codigo, prod.nome, prod.preco);
}