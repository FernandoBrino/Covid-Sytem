//Used libraries
#include "stdio.h"
#include "conio.h"
#include "locale.h"
#include "stdlib.h"
#include "string.h"


//Color variables
#define YEL   "\x1B[33m"
#define RED   "\x1B[31m"
#define CYN   "\x1B[36m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"


struct dataPatient {//Struct to save data about the patients;
    char name[240];
    char cpf[240];
    char cellphone[240];
    char address[240];
    char yearBorn[5];
    char email[240];
    char diagnoseData[240];
    char comorbidity[240];
};

int menuLogin() {// Register/Login in the system;
    system("cls");
    int choice;

    printf(CYN" Bem-vindo a nossa batalha contra o COVID-19\n"RESET);
    printf("\n1. Logar\n");
    printf("2. Registrar-se\n");
    printf("\nSelecione uma opção: ");
    scanf("%d", &choice);

    return choice;
    //Send the user choice to main function.
}

int menuPatients() {//Menu to register/show patients, after successful login;
    system("cls");
    int choice;

    printf(CYN" Área de Pacientes\n"RESET);

    printf("\n1. Registrar pacientes\n");
    printf("2. Mostrar pacientes\n");
    printf("3. Pacientes em risco\n");
    printf("\nSelecione uma opção: ");
    scanf("%d", &choice);

    return choice;
    //Send the user choice to main function.
}

int login (){//Verify and do the login in the system to register the patients;
    system("cls");
    FILE *arc;
    arc = fopen("auth.txt", "r");

    int userExists = 0;
    int passwordExists = 0;
    char currentUser[99];
    char currentPassword[99];
    char user[99];
    char password[99];

    //Verify if the file is empty.
    if(arc == NULL) {
        printf(RED"Não existem usuários registrados!!\n"RESET);

        printf("\nDigite enter para retornar ao menu de opções...");
        getch();
        return 0;
    }

    //Read the 'auth.txt' file, to check the credentials.
    fread(&user, sizeof(user), 1, arc);
    fread(&password, sizeof(password), 1, arc);

    printf(CYN" ------ Login ------\n"RESET);

    fflush(stdin);
    printf("\nDigite seu nome de usuário: ");
    gets(currentUser);

    fflush(stdin);
    printf("Digite sua senha: ");
    gets(currentPassword);


    //Compare user credentials with the credentials inside the "auth.txt".
    userExists = strncmp(currentUser, user, strlen(user));
    passwordExists = strncmp(currentPassword, password, strlen(password));
    //If exists the function 'strncmp' return 0 otherwise return a number bigger or smaller than 0.

    fclose(arc);


    //Verifying the user and password using the 'strncmp' return.
    if(userExists != 0){
        printf(RED"\nUsuário não registrado!!\n"RESET);
        printf("\nDigite enter para retornar ao menu de opções...");
        getch();
        return 0;
    }

    if(passwordExists != 0){
        printf(RED"\nSenha incorreta!!\n"RESET);
        printf("\nDigite enter para retornar ao menu de opções...");
        getch();
        return 0;
    }

    if(userExists == 0 && passwordExists == 0) {
        printf(GRN"\nLogin efetuado com sucesso seja bem-vindo(a)%s\n", user);
        printf(RESET"\nDigite enter para retornar ao menu de opções...");
        getch();
        return -1;
    }


}

void registering(){//Register a account in 'auth.txt';
    system("cls");
    char user[99];
    char password[99];

    FILE *arc;
    arc = fopen("auth.txt", "a");

    printf(CYN" ------ Criação de Conta ------\n"RESET);

    fflush(stdin);
    printf("\nDigite seu nome de usuário: ");
    gets(user);

    fflush(stdin);
    printf("Digite sua senha: ");
    gets(password);


    //Write in 'auth.txt' the user credentials.
    fwrite(&user, sizeof(user), 1, arc);
    fwrite(&password, sizeof(password), 1, arc);
    fclose(arc);

    printf(GRN"\nUsuário registrado com sucesso!!\n"RESET);
    printf("\nDigite enter para retornar ao menu de opções...");
    getch();
    return 0;

}

int submitData (struct dataPatient *p){//Write in 'patientsList.txt'/'peopleAtRisk.txt' files data about the patients;
    system("cls");
    FILE *arc;
    arc = fopen("patientsList.txt", "ab");

    printf(CYN" ------ Registro de Pacientes ------\n"RESET);

    //Catching the patient data.
    fflush(stdin);
    printf("\nNome do Paciente: ");
    gets(p->name);

    fflush(stdin);
    printf("\nCPF[123.456.789-00]: ");
    gets(p->cpf);

    fflush(stdin);
    printf("\nTelefone [13912345678]: ");
    gets(p->cellphone);

    fflush(stdin);
    printf("\nEndereço [Rua, Número, Bairro, Cidade, Estado, CEP]: ");
    gets(p->address);

    fflush(stdin);
    printf("\nAno de Nascimento: ");
    gets(p->yearBorn);

    fflush(stdin);
    printf("\nEmail: ");
    gets(p->email);

    fflush(stdin);
    printf("\nData do Diagnóstico: ");
    gets(p->diagnoseData);

    fflush(stdin);
    printf("\nComorbidade [digite N, caso não possua]: ");
    gets(p->comorbidity);

    //Write all data in 'patientsList.txt'.
    fwrite(&(*p), sizeof(struct dataPatient), 1,arc);


    //Write data about the people at risk to 'peopleAtRisk.txt'.
    int yearAsNumber;
    int currentYear = 2021;
    int idade;
    int confirm;
    char auxComorbidity[2] = "N";
    int isComorbidity;

    //Verifying if there is comorbidity.
    isComorbidity = strncmp(p->comorbidity, auxComorbidity, strlen(auxComorbidity));

    //Passing the yearBorn(striing) to Number.
    yearAsNumber = atoi(p->yearBorn);
    idade = currentYear - yearAsNumber;


    //Verifying age and comorbidity to write in 'peopleAtRisk.txt'.
    if(idade <= 65 && isComorbidity != 0) {
        FILE *arc2;
        arc2 = fopen("peopleAtRisk.txt", "ab");
        fwrite(&(*p), sizeof(struct dataPatient), 1, arc2);
        fclose(arc2);
    }

    fclose(arc);

    printf(GRN"\nPaciente registrado com sucesso!!\n"RESET);
    printf("\nDigite enter para retornar ao menu de opções...");
    getch();
}

int showData (struct dataPatient *p){//Show registered patients;
    system("cls");
    FILE *arc;
    arc = fopen("patientsList.txt", "rb");

    int confirm = 0;
    int i= -1;

    //Verifying if the file is empty.
    if(arc == NULL) {
        printf(RED"Não existem pacientes registrados!!\n"RESET);

        printf("\nDigite enter para retornar ao menu de opções...");
        getch();
        return 0;
    }

    printf(CYN" ------ Pacientes Registrados ------\n"RESET);

    //Loop to read all patients in 'patientsList.txt'.
      while(1){
            i++;
            confirm = fread(&(*p), sizeof(struct dataPatient), 1, arc);
            if(confirm == 0 ){
                break;
            }
            printf("\nNome: "); puts(p->name);
            printf("CPF: "); puts(p->cpf);
            printf("Telefone: "); puts(p->cellphone);
            printf("Endereço: "); puts(p->address);
            printf("Email: "); puts(p->email);
            printf("Data do Diagnóstico: "); puts(p->diagnoseData);
            printf("Comorbidade: "); puts(p->comorbidity);
            printf("Nascimento: "); puts(p->yearBorn);
      }

    printf(YEL"\n\nPaciente(s) = %d ", i);
    printf(RESET"\n\nDigite enter para retornar ao menu de opções...");
    getch();


    fclose(arc);
}

void isAtRisk(struct dataPatient *p) {//Show registered patients at risk.
    system("cls");

    FILE *arc2;
    arc2 = fopen("peopleAtRisk.txt", "rb");

    int confirm = 0;
    int i=-1;

    //Verifying if the file is empty.
    if(arc2 == NULL) {
        printf(RED"Não existem pacientes registrados!!\n"RESET);
        printf("\nDigite enter para retornar ao menu de opções...");
        getch();
        return 0;
    }

     printf(CYN" ------ Pacientes em Risco ------\n"RESET);

     //Loop to read patients in 'peopleAtRisk.txt'.
     while(1){
        i++;
        confirm = fread(&(*p), sizeof(struct dataPatient), 1, arc2);
        if(confirm == 0) {
            break;
        }
        printf("\nNome: "); puts(p->name);
        printf("CPF: "); puts(p->cpf);
        printf("Telefone: "); puts(p->cellphone);
        printf("Endereço: "); puts(p->address);
        printf("Email: "); puts(p->email);
        printf("Data do Diagnóstico: "); puts(p->diagnoseData);
        printf("Comorbidade: "); puts(p->comorbidity);
        printf("Nascimento: "); puts(p->yearBorn);
     }

    printf(YEL"\n\nPacientes em risco = %d", i);
    printf(RESET"\n\nDigite enter para retornar ao menu de opções...");
    getch();

    fclose(arc2);

}

int main(void) {//Main function that call all the other in logic order.
    setlocale(LC_ALL, "portuguese");
    struct dataPatient dataPatient;
    struct dataPatient *p;
    p = &dataPatient;

    int choice;
    int isLogged = 0;
    do {//Loggin loop, if is logged the function login() return -1. If return -1, choice = 3 and the loop ends.
        choice = menuLogin();
        switch(choice) {
        case 1:
            isLogged = login();
            if(isLogged == -1){
                choice = 3;
            }
            break;
        case 2:
            registering();
            break;
        }
    }while(choice <=2 && choice >=1);

    do {//When choice = 3, user enter in this loop.
        choice = menuPatients();
        switch(choice){
        case 1:
            submitData(p);
            break;
        case 2:
            showData(p);
            break;
        case 3:
            isAtRisk(p);
            break;
        }
    }while(choice <=3 && choice >=1);

}
