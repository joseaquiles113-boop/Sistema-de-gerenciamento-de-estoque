#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct produtos{
    char nome[201];
    int id;
    int quantidade;
    double valor;
    struct produtos *proximo;
}produtos;

typedef struct{
    produtos *inicio;
    int quantidade_itens;
}Lista;


void cadastrar_produto(Lista *lista, const char *nome, int id, int quantidade, double valor);
void produtos_cadastrados(Lista *lista, int escolha, const char *nome, int id);
void edicao_produto(Lista *lista, int escolha, const char *nome, int id);
void relatorio(Lista *lista, int escolha, const char *nome, int id);
void limpar();
void liberar_memoria(Lista *lista);


int main(){
    Lista lista;

    lista.inicio = NULL;

    char nome[201];
    int id, quantidade, opcao;
    double valor;

    while(1){
        puts("\n--- SISTEMA DE GERENCIAMENTO DE ESTOQUE ---\n");
        puts("1 - Cadastrar novo produto\n2 - Ver produtos cadastrados\n3 - Editar produto\n4 - Relatorio do estoque\n0 - Sair do app");
        scanf("%d", &opcao);
        limpar();

        if(opcao == 1){

            system("cls");
            puts("Nome do produto:");
            scanf("%200[^\n]", nome);
            limpar();
            puts("ID do produto:");
            scanf("%d", &id);
            limpar();
            puts("Unidades a adicionar:");
            scanf("%d", &quantidade);
            limpar();
            puts("Valor do produto:");
            scanf("%lf", &valor);
            limpar();
            system("cls");
            cadastrar_produto(&lista, nome, id, quantidade, valor);

        }else if(opcao == 2){

            int esc;
            system("cls");
            puts("1 - Ver todos os produtos cadastrados\n2 - Procurar produto");
            scanf("%d", &esc);
            limpar();

            if(esc == 1){
                produtos_cadastrados(&lista, esc, nome, id);
            }else if(esc == 2){
                system("cls");
                puts("Digite o nome do produto:");
                scanf("%200[^\n]", nome);
                limpar();
                puts("Digite o ID do produto:");
                scanf("%d", &id);
                limpar();
                system("cls");
                produtos_cadastrados(&lista, esc, nome, id);
            }else{
                puts("Opcao invalida!");
            }
            
        }else if(opcao == 3){

            int esc;
            system("cls");
            puts("1 - Remover unidades de produtos\n2 - Adicionar unidades de produtos\n3 - Alterar valor de produtos\n4 - Excluir um produto");
            scanf("%d", &esc);
            limpar();

            system("cls");
            puts("Digite o nome do produto:");
            scanf("%200[^\n]", nome);
            limpar();
            puts("Digite o ID do produto:");
            scanf("%d", &id);
            limpar();
            system("cls");

            edicao_produto(&lista, esc, nome, id);

        }else if(opcao == 4){

            int esc;
            system("cls");
            puts("1 - Mostrar o valor total do estoque\n2 - Mostrar o valor total de um produto");
            scanf("%d", &esc);
            limpar();

            if(esc == 1){
                relatorio(&lista, esc, nome, id);
            }else if(esc == 2){
                system("cls");
                puts("Digite o nome do produto:");
                scanf("%200[^\n]", nome);
                limpar();
                puts("Digite o ID do produto:");
                scanf("%d", &id);
                limpar();
                system("cls");
                relatorio(&lista, esc, nome, id);
            }else{
                puts("Opcao invalida!");
            }
            
        }else if(opcao == 0){

            system("cls");
            puts("Saindo...");
            break;

        }else{

            system("cls");
            puts("Opcao invalida!");

        }
    }

    liberar_memoria(&lista);

    return 0;
}


void cadastrar_produto(Lista *lista, const char *nome, int id, int quantidade, double valor){
    produtos *novo_produto = (produtos*)malloc(sizeof(produtos));
    produtos *verificacao = lista->inicio;

    if(novo_produto == NULL)return;

    while(verificacao != NULL && (strcmp(verificacao->nome, nome)) != 0 && verificacao->id != id){
        verificacao = verificacao->proximo;
    }if(verificacao != NULL){
        free(novo_produto);
        puts("Produto ja cadastrado!");
    }else{
        strncpy(novo_produto->nome, nome, sizeof(novo_produto->nome) -1);
        novo_produto->nome[sizeof(novo_produto->nome) -1] = '\0';

        novo_produto->id = id;
        novo_produto->quantidade = quantidade;
        novo_produto->valor = valor;
        novo_produto->proximo = lista->inicio;
        lista->inicio = novo_produto;
        lista->quantidade_itens++;

        puts("Produto adicionado a lista!");
    }
}

void produtos_cadastrados(Lista *lista, int escolha, const char *nome, int id){
    produtos *produto = lista->inicio;

    if(escolha == 1){
        if(produto == NULL){
            puts("Nao ha produtos cadastrados!");
        }else{
            while(produto != NULL){
                printf("Nome do produto: %s\nID do produto: %d\nUnidades disponiveis: %d\nValor do produto: R$%.2f", produto->nome, produto->id, produto->quantidade, produto->valor);

                produto = produto->proximo;

                puts("\n");
            }
        }
    }else if(escolha == 2){
        while(produto != NULL && (strcmp(produto->nome, nome)) != 0 && produto->id != id){
            produto = produto->proximo;
        }if(produto == NULL || (strcmp(produto->nome, nome)) != 0 || produto->id != id){
            puts("Produto nao encontrado!");
        }else{
            printf("Nome do produto: %s\nID do produto: %d\nUnidades disponiveis: %d\nValor do produto: R$%.2f\n", produto->nome, produto->id, produto->quantidade, produto->valor);
        }
    }
}

void edicao_produto(Lista *lista, int escolha, const char *nome, int id){
    produtos *produto = lista->inicio;

    while(produto != NULL && (strcmp(produto->nome, nome)) != 0 && produto->id != id){
        produto = produto->proximo;
    }if(produto == NULL || (strcmp(produto->nome, nome)) != 0 || produto->id != id){
        puts("Produto nao encontrado!");
    }else{
        if(escolha == 1){
            int q_remover;
            puts("Quantidade de unidade(s) a ser(em) removida(s):");
            scanf("%d", &q_remover);
            limpar();
            system("cls");
            if(q_remover < 0){
                puts("Valor invalido!");
            }else if(produto->quantidade < q_remover){
                puts("O estoque nao possui unidades suficientes!");
            }else{
                produto->quantidade -= q_remover;
                printf("%d unidade(s) de %s removida(s)!\n", q_remover, produto->nome);
            }
        }else if(escolha == 2){
            int q_adicionar;
            puts("Quantidade de unidade(s) a ser(em) adicionada(s):");
            scanf("%d", &q_adicionar);
            limpar();
            system("cls");
            if(q_adicionar < 0){
                puts("Valor invalido!");
            }else{
                produto->quantidade += q_adicionar;
                printf("%d unidade(s) de %s adicionada(s)!\n", q_adicionar, produto->nome);
            }
        }else if(escolha == 3){
            double valor;
            puts("Digite o novo valor do produto:");
            scanf("%lf", &valor);
            limpar();
            system("cls");
            if(valor <= 0){
                puts("Valor invalido!");
            }else{
                produto->valor = valor;
                printf("O valor do produto %s foi alterado para R$%.2f", produto->nome, produto->valor);
            }
        }else if(escolha == 4){
            produtos *produtoExcluir = NULL;
            produtos *inicio = lista->inicio;

            if(inicio != NULL && (strcmp(inicio->nome, nome)) == 0 && inicio->id == id){
                produtoExcluir = inicio->proximo;
                lista->inicio = produtoExcluir->proximo;
            }else{
                while(inicio != NULL && inicio->proximo != NULL && (strcmp(inicio->proximo->nome, nome)) != 0 && inicio->proximo->id != id){
                    inicio = inicio->proximo;
                }if(inicio != NULL && inicio->proximo != NULL && (strcmp(inicio->proximo->nome, nome)) == 0 && inicio->proximo->id == id){
                    produtoExcluir = inicio->proximo;
                    inicio->proximo = produtoExcluir->proximo;
                }else{
                    puts("Produto nao encontrado!");
                }
            }

            if(produtoExcluir != NULL){
                free(produtoExcluir);
                puts("Produto removido!");
            }
        }else{
            puts("Opcao invalida!");
        }
    }
}

void relatorio(Lista *lista, int escolha, const char *nome, int id){
    produtos *produto = lista->inicio;
    double soma = 0;

    if(escolha == 1){
        while(produto != NULL){
            soma += produto->valor * produto->quantidade;
            produto = produto->proximo;
        }if(soma == 0){
            puts("Nenhum produto encontrado!");
        }else{
            printf("Valor total do estoque: R$%.2f\n", soma);
        }
    }else if(escolha == 2){
        while(produto != NULL && (strcmp(produto->nome, nome)) != 0 && produto->id != id){
            produto = produto->proximo;
        }if(produto == NULL || (strcmp(produto->nome, nome)) != 0 || produto->id != id){
            puts("Produto nao encontrado!");
        }else{
            soma = produto->valor * produto->quantidade;
            printf("Valor total do produto %s: R$%.2f", produto->nome, soma);
        }
    }else{
        puts("Opcao invalida!");
    }
}

void limpar(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void liberar_memoria(Lista *lista){
    produtos *atual = lista->inicio;

    while(atual != NULL){
        produtos *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    lista->inicio = NULL;
}