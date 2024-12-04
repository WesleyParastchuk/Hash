// Wesley Parastchuk - GRR20235617

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 128

typedef struct Contato {
    char nome[64];
    char telefone[16];
    struct Contato *proximo;
} Contato;

Contato *tabelaHash[TABLE_SIZE];

unsigned int hashFunction(const char *nome) {
    unsigned int hash = 0;
    while (*nome) {
        hash += *nome++;
    }
    return hash % TABLE_SIZE;
}

void strToLower(char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

void adicionarContato() {
    char nome[50], telefone[15];
    printf("Digite o nome: ");
    scanf("%s", nome);
    printf("Digite o telefone: ");
    scanf("%s", telefone);

    strToLower(nome);

    unsigned int indice = hashFunction(nome);

    Contato *novoContato = (Contato *)malloc(sizeof(Contato));
    strcpy(novoContato->nome, nome);
    strcpy(novoContato->telefone, telefone);
    novoContato->proximo = tabelaHash[indice];
    tabelaHash[indice] = novoContato;

    printf("Contato adicionado com sucesso!\n");
}

void buscarContato() {
    char nome[50];
    printf("Digite o nome para buscar: ");
    scanf("%s", nome);

    strToLower(nome);

    unsigned int indice = hashFunction(nome);
    Contato *atual = tabelaHash[indice];

    while (atual) {
        if (strcmp(atual->nome, nome) == 0) {
            printf("Contato encontrado: %s - %s\n", atual->nome, atual->telefone);
            return;
        }
        atual = atual->proximo;
    }
    printf("Contato nao encontrado.\n");
}

void removerContato() {
    char nome[50];
    printf("Digite o nome para remover: ");
    scanf("%s", nome);

    strToLower(nome);

    unsigned int indice = hashFunction(nome);
    Contato *atual = tabelaHash[indice];
    Contato *anterior = NULL;

    while (atual) {
        if (strcmp(atual->nome, nome) == 0) {
            if (anterior) {
                anterior->proximo = atual->proximo;
            } else {
                tabelaHash[indice] = atual->proximo;
            }
            free(atual);
            printf("Contato removido com sucesso.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Contato nao encontrado.\n");
}

void exibirContatos() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Contato *atual = tabelaHash[i];
        while (atual) {
            printf("%s - %s\n", atual->nome, atual->telefone);
            atual = atual->proximo;
        }
    }
}

int main() {
    int opcao;

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opcao: ");
        
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarContato();
                break;
            case 2:
                buscarContato();
                break;
            case 3:
                removerContato();
                break;
            case 4:
                exibirContatos();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
