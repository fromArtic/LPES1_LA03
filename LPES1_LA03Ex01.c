#include <stdio.h>
#include <stdlib.h>

#define MAX 50
#define numeroTAM 9

//Struct Conta
typedef struct{
    char nome[35];
    char numeroConta[numeroTAM];
    float saldo;
    char consulta[35];
}Conta;

//Sub-rotinas
int menu();
Conta cadastrarConta();
void buscarCliente();
void checkMultiplasContas();
void deposito();
void saque();
void consulta();

//Variaveis globais
Conta conta;
int choice;

int main(){
    Conta contas[MAX];
    int contadorContas = 0, i;

    do{
        choice = menu();
        if((choice < 1) || (choice > 5)){
            printf("\nESCOLHA INVALIDA.\n");
            system("PAUSE");
        }
        switch(choice){
            case 1:
                if((contadorContas < MAX)){
                    contas[contadorContas] = cadastrarConta(contas);
                    contadorContas++;
                }else{
                    printf("\nO limite maximo de contas cadastradas (%d) foi atingido.\n", MAX);
                    system("PAUSE");
                }
                break;
            case 2:
                if(contadorContas > 0){
                    buscarCliente();
                    for(i = 0; i < contadorContas; i++){
                        if(stricmp(contas[i].nome, conta.consulta) == 0){
                            checkMultiplasContas(contas, contadorContas);
                        }
                    }
                    deposito(contas, contadorContas);
                }else{
                    printf("\nVoce deve ter ao menos uma conta cadastrada para acessar as outras opcoes.\n");
                    system("PAUSE");
                }
                break;
            case 3:
                if(contadorContas > 0){
                    buscarCliente();
                    for(i = 0; i < contadorContas; i++){
                        if(stricmp(contas[i].nome, conta.consulta) == 0){
                            checkMultiplasContas(contas, contadorContas);
                        }
                    }
                    saque(contas, contadorContas);
                }else{
                    printf("\nVoce deve ter ao menos uma conta cadastrada para acessar as outras opcoes.\n");
                    system("PAUSE");
                }
                break;
            case 4:
                if(contadorContas > 0){
                    buscarCliente();
                    consulta(contas, contadorContas);
                }else{
                    printf("\nVoce deve ter ao menos uma conta cadastrada para acessar as outras opcoes.\n");
                    system("PAUSE");
                }
                break;
            case 5:
                printf("\nEncerrando o programa . . .\n");
        }
    }while(choice != 5);

    system("PAUSE");
    return 0;
}

//Menu de opcoes
int menu(){
    system("CLS");
    printf("MENU DE OPCOES\n\n");
    printf("1. Cadastramento da conta\n");
    printf("2. Deposito\n");
    printf("3. Saque\n");
    printf("4. Consulta\n");
    printf("5. Sair\n\n");
    printf("Insira sua escolha: ");
    scanf("%d", &choice);
    return choice;
}

//1. Cadastramento da conta
Conta cadastrarConta(Conta contas[]){
    int i, check = 0;
    getchar();
    printf("\n");
    printf("Informe o nome que deseja registrar na conta: ");
    gets(conta.nome);
    printf("Insira o numero da conta (%d digitos): ", numeroTAM);
    gets(conta.numeroConta);
    for(i = 0; i < MAX; i++){
        while(strlen(conta.numeroConta) != numeroTAM){
            printf("ERRO: O numero da conta deve possuir %d digitos. Insira um numero valido para a conta: ", numeroTAM);
            gets(conta.numeroConta);
        }
        if(stricmp(contas[i].numeroConta, conta.numeroConta) == 0){
            check = 1;
            while(check == 1){
                printf("ERRO: O numero inserido ja esta vinculado a outra conta. Insira outro numero: ");
                gets(conta.numeroConta);
                if(stricmp(contas[i].numeroConta, conta.numeroConta) != 0){
                    check = 0;
                }
            }
        }
    }
    printf("Insira o saldo: R$");
    scanf("%f", &conta.saldo);
    printf("\nCADASTRO CONCLUIDO COM SUCESSO.\n");
    system("PAUSE");
    return conta;
}

//Requisicao do nome ou numero da conta
void buscarCliente(){
    getchar();
    printf("\n");
    if(choice == 2){
        printf("Informe o nome ou numero da conta na qual deseja aplicar o deposito: ");
    }
    if(choice == 3){
        printf("Informe o nome ou numero da conta na qual deseja efetuar o saque: ");
    }
    if(choice == 4){
        printf("Informe o nome ou numero da conta a ser consultada: ");
    }
    gets(conta.consulta);
    return conta;
}

//Checa, caso o cliente tenha informado um nome, qual a conta vinculada que deseja acessar
void checkMultiplasContas(Conta contas[], int contadorContas){
    int i;
    system("CLS");
    for(i = 0; i < contadorContas; i++){
        if(stricmp(contas[i].nome, conta.consulta) == 0){
            printf("Nome do cliente: %s", contas[i].nome);
            break;
        }
    }
    printf("\n\nCONTAS REGISTRADAS");
    for(i = 0; i < contadorContas; i++){
        if(stricmp(contas[i].nome, conta.consulta) == 0){
            printf("\n- %s", contas[i].numeroConta);
        }
    }
    printf("\n\nInsira o numero da conta que deseja acessar: ");
    gets(conta.consulta);
    return conta;
}

//2. Deposito
void deposito(Conta contas[], int contadorContas){
    int i, check = 0;
    float deposito;
    for(i = 0; i < contadorContas; i++){
        if((stricmp(contas[i].nome, conta.consulta) == 0) || (stricmp(contas[i].numeroConta, conta.consulta) == 0)){
            system("CLS");
            check++;
            printf("REALIZAR DEPOSITO BANCARIO\n\n");
            printf("Nome do cliente: %s - Numero da conta: %s\n", contas[i].nome, contas[i].numeroConta);
            printf("Saldo atual: R$%.2f\n\n", contas[i].saldo);
            printf("Informe a quantia que deseja depositar: R$");
            scanf("%f", &deposito);
            while(deposito < 0){
                printf("\nERRO: Voce nao pode depositar uma quantia negativa sobre seu saldo.\n");
                printf("Informe uma quantia valida que deseja depositar: R$");
                scanf("%f", &deposito);
            }
            if(deposito >= 0){
                contas[i].saldo += deposito;
            }
            printf("\nDEPOSITO EFETUADO COM SUCESSO.\n");
            break;
        }
    }
    if(check == 0){
        printf("\nNao foram encontrados registros sobre o nome ou numero informado.\n");
    }
    system("PAUSE");
}

//3. Saque
void saque(Conta contas[], int contadorContas){
    int i, check = 0;
    float saque;
    for(i = 0; i < contadorContas; i++){
        if((stricmp(contas[i].nome, conta.consulta) == 0) || (stricmp(contas[i].numeroConta, conta.consulta) == 0)){
            system("CLS");
            check++;
            printf("REALIZAR SAQUE\n\n");
            printf("Nome do cliente: %s - Numero da conta: %s\n", contas[i].nome, contas[i].numeroConta);
            printf("Saldo atual: R$%.2f\n\n", contas[i].saldo);
            printf("Informe a quantia que deseja sacar: R$");
            scanf("%f", &saque);
            while(saque > contas[i].saldo){
                printf("\nERRO: Voce nao pode sacar uma quantia maior que seu proprio saldo.\n");
                printf("Informe uma quantia valida que deseja sacar: R$");
                scanf("%f", &saque);
            }
            if(saque <= contas[i].saldo){
                contas[i].saldo -= saque;
            }
            printf("\nSAQUE EFETUADO COM SUCESSO.\n");
            break;
        }
    }
    if(check == 0){
        printf("\nNao foram encontrados registros sobre o nome ou numero informado.\n");
    }
    system("PAUSE");
}

//4. Consulta
void consulta(Conta contas[], int contadorContas){
    int i, check = 0;
    system("CLS");
    printf("DADOS DA CONTA\n\n");
    for(i = 0; i < contadorContas; i++){
        if((stricmp(contas[i].nome, conta.consulta) == 0) || (stricmp(contas[i].numeroConta, conta.consulta) == 0)){
            printf("Nome do cliente: %s\n", contas[i].nome);
            printf("Numero da conta: %s\n", contas[i].numeroConta);
            printf("Saldo: R$%.2f\n\n", contas[i].saldo);
            check++;
        }
    }
    if(check == 0){
        printf("Nao foram encontrados registros sobre o nome ou numero informado.\n\n");
    }
    system("PAUSE");
}
