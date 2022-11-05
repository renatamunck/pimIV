#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <locale.h>
#define quantidade 50

typedef struct
{
  int dia;
  int mes;
  int ano;
} rgData;

typedef struct
{
  char nome[50];
  char cep[9];
  char cpf[12];
  char telefone[12];
  char endereco[50];
  char email[60];
  int ativo;
  int idade;
  int temComorbidade; // 0 - nao tem | 1 - tem
  rgData dataNascimento;
  rgData dataDiagnostico;
  char comorbidade[20];
} Paciente;

int calculaIdade(rgData nasc, rgData hoje);
void welcome();
void altenticacao(); //prototipo da funcao
void menu();
void cadastrar();
void atribuiComorbidade();
void geraArquivoComComorbidade(Paciente novoPaciente);
void geraArquivoSemComorbidade(Paciente novoPaciente);
int validaRgData(rgData dt);
int validaTexto(char texto[]);
void obtemTextoDoUsuario(char label[], char atributo[]);
rgData obtemDataNascimento();
rgData obtemDataDiagnostico();
rgData entradaRgData();

char comorbidadeGlobal[20];
int temComorbidadeGlobal;

Paciente pacientes[quantidade];

rgData obtemDataNascimento()
{

  printf("Informe a data de nascimento");
  rgData data;

  int temErro;
  do
  {
    data = entradaRgData();
    temErro = validaRgData(data);

    if (temErro == 1)
    {
      printf("Data invalida, digite novamente");
    }
  } while (temErro == 1);

  return data;
}

rgData obtemDataDiagnostico()
{

  printf("Informe a data do diagnostico:");
  rgData data;

  int temErro;
  do
  {
    data = entradaRgData();
    temErro = validaRgData(data);

    if (temErro == 1)
    {
      printf("Data invalida, digite novamente");
    }
  } while (temErro == 1);

  return data;
}

rgData entradaRgData()
{
  rgData dt;

  printf("(dd/mm/aaaa): ");
  scanf("%d/%d/%d", &dt.dia, &dt.mes, &dt.ano);

  return dt;
}

int validaRgData(rgData dt)
{

  if (dt.dia < 1 || dt.dia > 31)
  {
    return 1;
  }
  if (dt.mes < 1 || dt.mes > 12)
  {
    return 1;
  }
  if (dt.ano < 0)
  {
    return 1;
  }
  return 0;
}

void obtemTextoDoUsuario(char label[], char atributo[])
{
  int temErro;

  do
  {
    fflush(stdin);
    printf("%s", label);
    scanf("%[^\n]", atributo);

    temErro = validaTexto(atributo);

    if (temErro == 1)
    {
      printf("Aldo deu errado, digite novamente");
    }

  } while (temErro == 1);
  fflush(stdin);
}

int validaTexto(char texto[])
{
  int temErro;

  if (strlen(texto) <= 1)
  {
    temErro = 1;
  }

  return temErro;
}

int main(int arg, char const *argv[])
{

  welcome();

  altenticacao();

  menu();

  return 0;
  getchar();
}
void welcome()
{
  system("cls");
  printf("*** CADASTRO DE PACIENTES SOFTVID19 *** \n");
}

void altenticacao()
{
  char login[15] = "pimunip";
  char login1[15];
  char senha[15] = "2022";
  char senha1[15];

  int continuar = 1;
  do
  {
    printf("-------- SEU LOGIN E SENHA---------\n");
    printf("LOGIN: ");
    scanf("%s", login1);

    printf("Senha: ");
    scanf("%s", senha1);

    if (strcmp(login, login1) == 0 && strcmp(senha, senha1) == 0)
    {
      printf("-- DEU CERTO! --\n\n");
      continuar = 0;
    }
    else
    {

      printf("--- DEU RUIM,TENTE OUTRA VEZ!---\n\n");
      printf("Gostaria de tentar novamente?\n1 - Tentar novamente\n0 - Sair\n");
      printf("Opção: ");
      scanf("%d", &continuar);
    }
  } while (continuar != 0);
}

void menu()
{
  setlocale(LC_ALL, "");
  printf(" _-_ Escolha  _-_\n");
  int op;
  do
  {
    printf("\n1 - Cadastrar Paciente\n0 - Sair\n");
    scanf("%d", &op);
    getchar();

    switch (op)
    {
    case 1:
      cadastrar();
      break;
    }
  } while (op != 0);
}

int calculaIdade(rgData nasc, rgData hoje)
{
  int idade;

  idade = hoje.ano - nasc.ano;
  if ((hoje.mes < nasc.mes) || (hoje.mes == nasc.mes) && (hoje.dia < nasc.dia))
    idade = idade - 1;
  return (idade);
}

void atribuiComorbidade()
{
  int temComorbidade;

  printf("\nPaciente com comorbidade?\n1 - Sim\n2 - Não\n");
  printf("Opção: ");
  scanf("%d", &temComorbidade);

  if (temComorbidade == 1)
  {
    int comorbidade;
    temComorbidadeGlobal = 1;

    printf("\nQual a comorbidade do paciente?\n1 - Diabetes\n2 - Obesidade\n3 - Hipertensão\n4 - Tuberculose\n5 - Outros\n");
    printf("Opção: ");
    scanf("%d", &comorbidade);

    switch (comorbidade)
    {
    case 1:
      strcpy(comorbidadeGlobal, "diabetes");
      break;
    case 2:
      strcpy(comorbidadeGlobal, "obesidade");
      break;
    case 3:
      strcpy(comorbidadeGlobal, "hipertensão");
      break;
    case 4:
      strcpy(comorbidadeGlobal, "tuberculose");
      break;

    default:
      strcpy(comorbidadeGlobal, "outros");
      break;
    }
  }
  else
  {
    strcpy(comorbidadeGlobal, "sem comorbidade");
    temComorbidadeGlobal = 0;
  }
}

void geraArquivoSemComorbidade(Paciente novoPaciente)
{
  FILE *pacientesArquivo = fopen("arquivo-pacientes-covid.txt", "a");

  fprintf(pacientesArquivo, "%s,%d,%s,%s,%d/%d/%d,%d/%d/%d,%s,%s,%s,%s\n",
          novoPaciente.nome,
          novoPaciente.idade,
          novoPaciente.cpf,
          novoPaciente.email,
          novoPaciente.dataNascimento.dia,
          novoPaciente.dataNascimento.mes,
          novoPaciente.dataNascimento.ano,
          novoPaciente.dataDiagnostico.dia,
          novoPaciente.dataDiagnostico.mes,
          novoPaciente.dataDiagnostico.ano,
          novoPaciente.cep,
          novoPaciente.endereco,
          novoPaciente.telefone,
          comorbidadeGlobal);

  fclose(pacientesArquivo);
}

void geraArquivoComComorbidade(Paciente novoPaciente)
{

  FILE *pacientesArquivo = fopen("arquivo-secretaria-da-saude.txt", "a");

  fprintf(pacientesArquivo, "%d,%s\n",
          novoPaciente.idade,
          novoPaciente.cep);

  fclose(pacientesArquivo);
}

void cadastrar()
{
  int op;
  do
  {

    Paciente novoPaciente;
    novoPaciente.temComorbidade = 0;

    system("cls");

    printf("\n---- Cadastrando paciente -----\n");
    fflush(stdin);

    obtemTextoDoUsuario("Nome:", novoPaciente.nome);

    novoPaciente.dataNascimento = obtemDataNascimento();
    fflush(stdin);

    novoPaciente.dataDiagnostico = obtemDataDiagnostico();
    fflush(stdin);

    obtemTextoDoUsuario("CPF:", novoPaciente.cpf);

    obtemTextoDoUsuario("Endereço:", novoPaciente.endereco);

    obtemTextoDoUsuario("CEP:", novoPaciente.cep);

    obtemTextoDoUsuario("Telefone:", novoPaciente.telefone);

    printf("Email: ");
    scanf("%s", novoPaciente.email);

    novoPaciente.idade = calculaIdade(novoPaciente.dataNascimento, novoPaciente.dataDiagnostico);
    fflush(stdin);

    atribuiComorbidade();

    if ((temComorbidadeGlobal == 1) || (novoPaciente.idade > 65))
    {
      geraArquivoComComorbidade(novoPaciente);
    }

    geraArquivoSemComorbidade(novoPaciente);

    printf("\nPaciente cadastrado com sucesso!\n");

    printf("\n-_- Deseja continuar? -_-\n");
    printf("\n1 - Continuar\n2 - Encerrar Sistema\n");
    scanf("%d", &op);

    if (op == 2)
    {
      exit(0);
    }
    getchar();

  } while (op == 1);
}


