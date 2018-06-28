#define ex5
#include "stdio.h"
#include "stdlib.h"
/*******
{
  "university": "Faculdade de Tecnologia",
  "unit":       "FATEC Baixada Santista Rubens Lara",
  "course":     "Analise e desenvolimento de sistemas - ADS",
  "opening":    "2º semestre/2017",
  "period":     "manha"
},
{
  "class":      "Linguagem de Programacao",
  "teacher":    "Rui Silvestrin",
  "cicle":      "2º",
  "day":        "sexta-feira",
  "hour":       "7:40am - 9:20pm | 11:10 - 12:50"
},
{
  "name":       "lista de exercicios capitulo 10",
  "description": "desenvolver codigo em C ",
  "author":     "Hugo Melo",
  "date":       "27/06/2018"
  },

********/

/*****************************************************************************

			EXERCICIOS ARQUIVOS

*****************************************************************************
1 - Crie uma funcao para escrever num arquivo os dados com a estrutura de dados
    e a inicialização abaixo. (utilize a funcao putc).
     nome, endereco, cidade, estado, cep = manoel, rua 4, santos, sp, 11000900
*/
#ifdef ex1
typedef struct cad{
    char nome[10],
        end[30],
        cidade[20],
        estado[3],
        cep[10];
}FORMULARIO;

void escreve_cadastro(FORMULARIO *pcad, FILE *p){
    int i;

    for (int i = 0; (pcad) -> nome[i] != '\0'; ++i){
      putc((pcad) -> nome[i],p);
    }
    putc('\n', p);
    for (int i = 0; (pcad) -> end[i] != '\0'; ++i){
      putc((pcad) -> end[i],p);
    }
    putc('\n', p);
    for (int i = 0; (pcad) -> cidade[i] != '\0'; ++i){
      putc((pcad) -> cidade[i],p);
    }
    putc('\n', p);
    for (int i = 0; (pcad) -> estado[i] != '\0'; ++i){
      putc((pcad) -> estado[i],p);
    }
    putc('\n', p);
    for (int i = 0; (pcad) -> cep[i] != '\0'; ++i){
      putc((pcad) -> cep[i],p);
    }
    putc('\n', p);

}

int main(){
    FILE *p;
    static FORMULARIO cad1 = {"manoel", "rua 4", "santos", "sp", "11000900"};

  if((p = fopen("teste_CAP10","w"))==NULL)
    {
    printf("erro na abertura do arquivo \n");
    exit(0);
    }

  escreve_cadastro(&cad1, p);

  fclose(p);
}
#endif // ex
/**
2 - Escreva uma funcao para ler do arquivo os dados gravados do exercicio
    anterior. (utilize a funcao getc).
*/
#ifdef ex2

void le_cadastro(FILE *p){
    int i;
    char ch = '*';

    for (int i = 0; ch != '\n'; ++i){
      ch = getc(p);
      putchar(ch);      
    }
    ch = '*';
    for (int i = 0; ch != '\n'; ++i){
      ch = getc(p);
      putchar(ch);      
    }
    ch = '*';
    for (int i = 0; ch != '\n'; ++i){
      ch = getc(p);
      putchar(ch);      
    }
    ch = '*';
    for (int i = 0; ch != '\n'; ++i){
      ch = getc(p);
      putchar(ch);      
    }
    ch = '*';
    for (int i = 0; ch != '\n'; ++i){
      ch = getc(p);
      putchar(ch);      
    }      
}

int main(){
  FILE *p;

  if((p = fopen("teste_CAP10","r"))==NULL)
    {
    printf("erro na abertura do arquivo \n");
    exit(0);
    }

  le_cadastro(p);

  fclose(p);
}
#endif // ex
/**
3 - Reescreva as funcoes de gravacao e leitura no arquivo dos exercicios
    anteriores utilizando as funcoes fwrite e fread.

OBS.: Todos os programa devem ser finalizados pelo usuario.
*/
#ifdef ex3

typedef struct cad{
    char nome[10],
        end[30],
        cidade[20],
        estado[3],
        cep[10];
}FORMULARIO;

void escreve_cadastro(FORMULARIO *pcad, FILE *p){
    fprintf(p,"%s ", pcad -> nome);
    fprintf(p,"%s ", pcad -> end);
    fprintf(p,"%s ", pcad -> cidade);
    fprintf(p,"%s ", pcad -> estado);
    fprintf(p,"%s ", pcad -> cep);
}
void le_cadastro(FILE *p, FORMULARIO *pcad){
  fscanf(p,"%s", pcad -> nome);
  fscanf(p,"%s", pcad -> end);
  fscanf(p,"%s", pcad -> cidade);
  fscanf(p,"%s", pcad -> estado);
  fscanf(p,"%s", pcad -> cep);

  printf("imprime na tela os dados formatados lidos do arquivo teste_CAP10\n\n");
  printf("nome    : %s\n", pcad -> nome);
  printf("endereco: %s\n", pcad -> end);
  printf("cidade  : %s\n", pcad -> cidade);
  printf("estado  : %s\n", pcad -> estado);
  printf("cep     : %s\n", pcad -> cep);   
}

int main(){
  char loop = 0;
  FILE *p;
  static FORMULARIO cad1 = {"Manuel", "rua 4", "santos", "sp", "11000900"}; 
  FORMULARIO cad_ler;

  while(loop != 115){
    if((p = fopen("teste_CAP10","w"))==NULL){
      printf("erro na abertura do arquivo \n");
      exit(0);
    }
    escreve_cadastro(&cad1, p);
    fclose(p);
    
    if((p = fopen("teste_CAP10","r"))==NULL){
      printf("erro na abertura do arquivo \n");
      exit(0);
    }

    le_cadastro(p, &cad_ler);
    fclose(p);

    //
    //saida do loop
    do{
        printf("\n\n\n ______________________\n Deseja encerrar? (s/n): ");
        scanf(" %c", &loop);
        loop |= 32; //transforma caracter para minuscula
    }while(loop != 110 && loop != 115); // valida se s (115) ou n (110) foi digitado
  }
}
#endif // ex
/**
4 - Faça um programa para:
    1 - criar/abrir um arquivo texto de nome ”arq.txt”,
    2 - receba via teclado diversos caracteres e armazene nesse arquivo.
        O caracter '0' finaliza a entrada de dados.
    3 - reabra o arquivo fazendo o ponteiro apontar para seu início
    4 - leia e imprima na tela todos os caracteres armazenados.
*/
#ifdef ex4

int main(){
  FILE *p;
  char entrada;
  int i, j = 0;


  if((p = fopen("arq","w"))==NULL){
    printf("erro na abertura do arquivo \n");
    exit(0);
  }

  printf("Digite diversos caracteres, o caracter 0 finaliza a entrada \n");
  while(entrada != '0'){
    scanf(" %c", &entrada);
    if(entrada != '0'){
      putc(entrada,p);
      j++;
    }
  }
  
  fclose(p);

  if((p = fopen("arq","r"))==NULL){
    printf("erro na abertura do arquivo \n");
    exit(0);
  }

  char ch[j];
  fread(ch,j,1,p);

  for (int i = 0; i < j; ++i){
    printf("%c",ch[i]);
  }
  

  fclose(p);

}
#endif // ex
/**
5 - Faça um programa para gerenciar uma agenda de contatos. Para cada contato
    armazene o nome, o telefone e o aniversário (dia e mês). O programa deve ter
    as opções:
    1 - inserir contato,
    2 - remover contato,
    3 - pesquisar um contato pelo nome,
    4 - listar todos os contatos,
    5 - listar os contatos cujo nome inicia com uma dada letra,
    6 - imprimir os aniversariantes do mês.
    Sempre que o programa for encerrado, os contatos devem ser armazenados. Quando
    o programa iniciar, os contatos devem ser inicializados com os dados contidos
    no arquivo.
*/
#ifdef ex5

typedef struct agenda{
  char nome[10];
  char telefone[10];
  int aniversario[2];
}AGENDA;

void inserir(AGENDA *contato, FILE *p){

  if((p = fopen("agenda","w"))==NULL){
    printf("erro na abertura do arquivo \n");
    exit(0);
  } 

  printf("\n\n Nome: ");
  scanf("%s", contato -> nome);
  printf(" Telefone: ");
  scanf("%s", contato -> telefone);
  printf(" Aniversario (dd/mm): ");
  scanf("%d/%d", &contato -> aniversario[0], &contato -> aniversario[1]);
  puts("\n\n");

  if(fwrite(contato,sizeof(AGENDA),1,p) != 1){
    printf(" --ERRO na isercao do contato \n");
    exit(0);
  }
  else
    printf(" --INSERIDO COM SUCESSO\n\n\n");

  fclose(p);
}

void remover(){

}

void buscar(){

}

void listar(AGENDA *contato, FILE *p){
  if((p = fopen("agenda","r"))==NULL){
    printf("erro na abertura do arquivo \n");
    exit(0);
  }

  if(fread(contato,sizeof(AGENDA),1,p) != 1){
    printf(" --ERRO na listagem do contato\n");
    exit(0);
  }  

  printf("\n\n Nome: %s\n", contato -> nome);
  printf(" Tel.: %s\n", contato -> telefone);
  printf(" Aniv.: %d/%d\n\n\n", contato -> aniversario[0], contato -> aniversario[1]);

  fclose(p);
}

void aniversarios(){

}


int main(){
  FILE *p;
  int opcao = 0;
  AGENDA contato; 
   

  while(opcao != 4){

    printf("\n # MENU AGENDA DE CONTATOS\n ----------------------------------------------------------------------\n");
    printf(" (1) INSERIR |");
    printf(" (2) LISTAR |");
    printf(" (3) BUSCAR POR NOME |");
    printf(" (4) BUSCAR POR INICIAL |\n");
    printf(" (5) EXCLUIR |");
    printf(" (6) ANIVERSARIANTES DO MES |");
    printf(" (7) SAIR \n");
    printf(" ----------------------------------------------------------------------\n");
    printf("\n opcao:> ");
    scanf("%d", &opcao);
    getchar();
  

    switch(opcao){
      case 1: inserir(&contato, p);
              break;
      case 2: listar(&contato, p);;
              break;
      // case 3: ;
      //         break;
      // case 4: ;
      //         break;
      // case 5: ;
      //         break;
      // case 6: ;
      //         break;
      // case 7: ;
      //         break;
      default: printf("\n --OPCAO INVALIDA\n\n\n\n");
    }
  }
}
#endif // ex
/**
6 - A partir do exercico 9 do capitulo de funcoes, acrescente as funções de leitura
    e escrita em arquivo. Estas funções devem ser usadas apenas quando for necessario.
*/
#ifdef ex6
main(){

}
#endif // ex
/**
7 - Implemente um controle simples de mercadorias em uma despensa doméstica.
    Sobre cada produto será armazenado um código numérico, descrição e
    quantidade atual.
    O programa deve ter as opções:
    1 - entrada de produtos
    2 - retirada de produtos
    3 - pesquisar uma mercadoria pela descrição
    4 - listar todos os produtos
    5 - listar os produtos não disponíveis.
    Escreva os itens das mercadorias direto no arquivo. (utilize a funcao fseek).

*/

#ifdef ex7
main(){

}
#endif // ex
