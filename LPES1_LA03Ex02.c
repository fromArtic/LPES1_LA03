#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define codigoTAM 9

//Struct Livro
typedef struct{
    char titulo[100];
    char codigo[codigoTAM];
    char autor[100];
    char editora[100];
    int anoPublicacao;
    float preco;
    char consulta[100];
}Livro;

//Sub-rotinas
int menu();
Livro cadastrarLivro();
void busca();
void consultaLivro();
void consultaPorPreco();
void consultaAutor();
void relatorio();

//Variaveis globais
Livro livro;
int choice;

int main(){
    Livro livros[MAX];
    int contadorLivros = 0;

    do{
        choice = menu();
        if((choice < 1) || (choice > 6)){
            printf("\nESCOLHA INVALIDA.\n");
            system("PAUSE");
        }
        switch(choice){
            case 1:
                if((contadorLivros < MAX)){
                    livros[contadorLivros] = cadastrarLivro(livros);
                    contadorLivros++;
                }else{
                    printf("\nO limite maximo de livros armazenados (%d) foi atingido.\n", MAX);
                    system("PAUSE");
                }
                break;
            case 2:
                busca();
                consultaLivro(livros, contadorLivros);
                break;
            case 3:
                consultaPorPreco(livros, contadorLivros);
                break;
            case 4:
                busca();
                consultaAutor(livros, contadorLivros);
                break;
            case 5:
                relatorio(livros, contadorLivros);
                break;
            case 6:
                printf("\nEncerrando o programa . . .\n");
        }
    }while(choice != 6);

    system("PAUSE");
    return 0;
}

//Menu de opcoes
int menu(){
    system("CLS");
    printf("MENU DE OPCOES\n\n");
    printf("1. Cadastrar livro\n");
    printf("2. Consultar livro\n");
    printf("3. Consultar livros com preco abaixo do valor especificado\n");
    printf("4. Consultar numero de livros cadastrados de um autor especifico\n");
    printf("5. Relatorio de livros\n");
    printf("6. Sair\n\n");
    printf("Insira sua escolha: ");
    scanf("%d", &choice);
    return choice;
}

//1. Cadastro de livro
Livro cadastrarLivro(Livro livros[]){
    int i, check = 0;
    getchar();
    printf("\n");
    printf("Informe o titulo do livro que deseja registrar: ");
    gets(livro.titulo);
    for(i = 0; i < MAX; i++){
        if(stricmp(livros[i].titulo, livro.titulo) == 0){
            check = 1;
            while(check == 1){
                printf("ERRO: O livro informado ja foi armazenado. informe outro titulo que deseja cadastrar: ");
                gets(livro.titulo);
                 if(stricmp(livros[i].titulo, livro.titulo) != 0){
                    check = 0;
                }
            }
        }
    }
    printf("Insira o codigo do livro (ate %d digitos): ", codigoTAM);
    gets(livro.codigo);
    for(i = 0; i < MAX; i++){
        while(strlen(livro.codigo) > codigoTAM){
            printf("ERRO: o codigo inserido supera o limite de digitos suportado. Insira outra sequencia, de ate %d algarismos: ", codigoTAM);
            gets(livro.codigo);
        }
        if(stricmp(livros[i].codigo, livro.codigo) == 0){
            check = 1;
            while(check == 1){
                printf("ERRO: O codigo inserido ja esta vinculado a outro livro. Insira outra sequencia: ");
                gets(livro.codigo);
                if(stricmp(livros[i].codigo, livro.codigo) != 0){
                    check = 0;
                }
            }
        }
    }
    printf("Qual o nome do autor da obra? ");
    gets(livro.autor);
    printf("Qual a editora responsavel pelo livro? ");
    gets(livro.editora);
    printf("Qual o ano de publicacao do livro? ");
    scanf("%d", &livro.anoPublicacao);
    printf("E qual o valor, em reais, do produto? R$");
    scanf("%f", &livro.preco);
    printf("\nCADASTRO CONCLUIDO COM SUCESSO.\n");
    system("PAUSE");
    return livro;
}

//Requisicao do titulo, codigo ou autor do livro
void busca(){
    getchar();
    printf("\n");
    if(choice == 2){
        printf("Informe o titulo ou codigo do livro que deseja consultar: ");
    }
    if(choice == 4){
        printf("Informe qual o autor que deseja consultar: ");
    }
    gets(livro.consulta);
    return livro;
}

//2. Consulta de um livro especifico
void consultaLivro(Livro livros[], int contadorLivros){
    int i, check = 0;
    system("CLS");
    for(i = 0; i < contadorLivros; i++){
        if((stricmp(livros[i].titulo, livro.consulta) == 0) || (stricmp(livros[i].codigo, livro.consulta) == 0)){
            printf("CONSULTA\n");
            printf("\n- Titulo da obra: %s", livros[i].titulo);
            printf("\n- Autor: %s", livros[i].autor);
            printf("\n- Editora: %s", livros[i].editora);
            printf("\n- Ano de publicacao: %d", livros[i].anoPublicacao);
            printf("\n- Codigo: %s", livros[i].codigo);
            printf("\n\n- Preco do livro: R$%.2f", livros[i].preco);
            printf("\n\n");
            check++;
        }
    }
    if(check == 0){
        printf("Nao foram encontrados registros do livro que procura.\n\n");
    }
    system("PAUSE");
}

//3. Consulta de livros abaixo do preco especificado
void consultaPorPreco(Livro livros[], int contadorLivros){
    float precoMax;
    int i, check = 0;
    printf("\nInforme o valor maximo: R$");
    scanf("%f", &precoMax);
    system("CLS");
    printf("Livros encontrados abaixo do preco especificado (R$%.2f):\n", precoMax);
    for(i = 0; i < contadorLivros; i++){
        if(livros[i].preco < precoMax){
            printf("\n--> %s, de %s, publicado em %d", livros[i].titulo, livros[i].autor, livros[i].anoPublicacao);
            printf("\n- Editora: %s", livros[i].editora);
            printf("\n- Codigo: %s", livros[i].codigo);
            printf("\n- Preco: R$%.2f\n", livros[i].preco);
            check++;
        }
    }
    if(check == 0){
        printf("\n- Nao ha registros.\n");
    }
    printf("\n");
    system("PAUSE");
}

//4. Consulta de quantos livros de um autor especifico estao cadastrados
void consultaAutor(Livro livros[], int contadorLivros){
    int i, count = 0;
    system("CLS");
    printf("Autor: %s\n\n", livro.consulta);
    for(i = 0; i < contadorLivros; i++){
        if(stricmp(livros[i].autor, livro.consulta) == 0){
            count++;
        }
    }
    if(count > 0){
        printf("- Livros cadastrados: %d", count);
    }else{
        printf("- Nao foram encontrados registros de livros do autor que procura.");
    }
    printf("\n\n");
    system("PAUSE");
}

//5. Relatorio geral dos livros cadastrados
void relatorio(Livro livros[], int contadorLivros){
    int i;
    system("CLS");
    if(contadorLivros > 0){
        printf("Lista de livros cadastrados:\n");
        for(i = 0; i < contadorLivros; i++){
            printf("\n--> %s, de %s, publicado em %d", livros[i].titulo, livros[i].autor, livros[i].anoPublicacao);
            printf("\n- Editora: %s", livros[i].editora);
            printf("\n- Codigo: %s", livros[i].codigo);
            printf("\n- Preco: R$%.2f", livros[i].preco);
            printf("\n");
        }
    }else{
        printf("Nao foram encontrados quaisquer dados de livros registrados.\n");
    }
    printf("\n");
    system("PAUSE");
}
