#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <iostream>

void novaCompra();
void buscarCompra();
void listarCompras();

int main() {
    int opcao;
    
    do {
        system("cls");
        printf("Seja bem vindo! O que deseja fazer?\n");
        printf("1. Nova compra\n");
        printf("2. Buscar compra\n");
        printf("3. Sair sem fazer nada\n");
        printf("4. Exibir historico de compras\n");
        printf("\n");
        printf("Digite (1/2/3/4): ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                novaCompra();
                break;
            case 2:
                buscarCompra();
                break;
            case 3:
                printf("Saindo...\n");
                exit(0);
                break;
            case 4:
                listarCompras();
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 3);

    return 0;
}

void novaCompra() {
    float valor, total = 0;
    int qtdProd;
    char nomeCompra[50];
    FILE *file;

    printf("Digite um nome para a compra: ");
    scanf("%s", nomeCompra);
    
    file = fopen(strcat(nomeCompra, ".txt"), "w");
    if (file == NULL) {
        printf("Erro ao criar arquivo!\n");
        return;
    }
    
    printf("Digite a quantidade de produtos: ");
    scanf("%d", &qtdProd);
    fprintf(file, "Quantidade de produtos: %d\n", qtdProd);
    
    for (int i = 0; i < qtdProd; i++) {
        printf("Produto %d, valor: ", i + 1);
        scanf("%f", &valor);
        total += valor;
        fprintf(file, "Produto %d, valor: %.2f\n", i + 1, valor);
    }
    
    fprintf(file, "Total da compra: %.2f\n", total);
    fclose(file);
    
    printf("Compra registrada com sucesso! Total: %.2f\n", total);
    system("pause");
}

void buscarCompra() {
    char nomeCompra[50];
    char linha[100];
    FILE *file;

    printf("Digite o nome da compra que deseja buscar: ");
    scanf("%s", nomeCompra);
    
    file = fopen(strcat(nomeCompra, ".txt"), "r");
    if (file == NULL) {
        printf("Compra nao encontrada!\n");
        system("pause");
        return;
    }

    printf("Historico da compra '%s':\n", nomeCompra);
    while (fgets(linha, sizeof(linha), file)) {
        printf("%s", linha);
    }
    
    fclose(file);
    system("pause");
}

void listarCompras() {
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        printf("Historico de compras registradas:\n");
        while ((dir = readdir(d)) != NULL) {
            if (strstr(dir->d_name, ".txt") != NULL) {
                printf("%s\n", dir->d_name);
            }
        }
        closedir(d);
    } else {
        printf("Erro ao acessar o diretorio.\n");
    }
    system("pause");
}
