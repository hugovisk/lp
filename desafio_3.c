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
  "name":       "Programa desafio 3",
  "description": "desenvolver codigo em C ",
  "author":     "Hugo Melo",
  "date":       "27/06/2018"
  },

********/

/*****************************************************************************

      PROGRAMA DESAFIO

*****************************************************************************
1 - Escreva um programa que tem a estrutura de dados abaixo. O programa tem as seguintes opções:
   1 – entra dados.
   2 – lista dados na tela.
   3 – pesquisa um registro por nome.
   4 – altera dados.
   5 – exclui dados.

 Todas as operações devem ser feitas direto no arquivo. (utilize a funcao fseek).

 Estrutura: nome, endereço, cidade,  estado e cep.
*/

int i;

typedef struct cad{
    char nome[10],
        end[30],
        cidade[20],
        estado[3],
        cep[10];
}FORMULARIO;

void inserir(FORMULARIO *pcad, FILE *p, FILE *i, int *n){
    
    if(!(p = fopen("cadastros","a"))){
      printf("erro na abertura do arquivo \n");
      exit(0);
    }

    printf("\n\n Nome: ");
    scanf(" %s", pcad -> nome);
    printf(" Endereco: ");
    scanf(" %s", pcad -> end);
    printf(" Cidade: ");
    scanf(" %s", pcad -> cidade);
    printf(" Estado: ");
    scanf(" %s", pcad -> estado);
    printf(" CEP: ");
    scanf(" %s", pcad -> cep);

    puts("\n\n");

    if(fwrite(pcad,sizeof(FORMULARIO),1,p) != 1){
      printf(" --ERRO na insercao do cadastro \n");
      exit(0);
    }
    else{
      printf(" --INSERIDO COM SUCESSO\n\n\n");
      *n += 1; //incrementa numero de formularios cadastrados
    }
    fclose(p);

    if(!(i = fopen("n_cadastros","w"))){
      printf("erro na abertura do arquivo contador \n");
      exit(0);
    }
    fprintf(i,"%d", *n);
    fclose(i);
}

void listar(FORMULARIO *pcad, FILE *p, int n){
  long desloc;

  if(n){
    if(!(p = fopen("cadastros","r"))){
      printf("erro na abertura do arquivo \n");
      exit(0);
    }
    for (int i = 0; i < n; ++i){
      desloc = i * sizeof(FORMULARIO);
      fseek(p,desloc,0);

      if(fread(pcad, sizeof(FORMULARIO), 1, p) != 1){
        printf(" --ERRO na listagem do pcad\n");
        exit(0);
      }  

      if(pcad -> nome[0] != '*'){
        printf("\n\n Nome: %s\n", pcad -> nome);
        printf(" Endereco: %s\n", pcad  -> end);
        printf(" Cidade: %s\n", pcad -> cidade);
        printf(" Estado: %s\n", pcad -> estado);
        printf(" CEP: %s", pcad -> cep);
      }
      
    }
    puts("\n\n");

    fclose(p);
  }
  else
    printf("\n --CADASTRO VAZIO\n\n");

  
}

long buscar(FORMULARIO *pcad, FILE *p, int n){
  char busca[20];
  int j;
  long desloc;

  if(n){
    printf(" Buscar: ");
    scanf(" %s", &busca[0]);

    if(!(p = fopen("cadastros","r"))){
      printf("erro na abertura do arquivo \n");
      exit(0);
    }

    for (int i = 0; i < n; ++i){
      desloc = i * sizeof(FORMULARIO);
      fseek(p,desloc,0);

      if(fread(pcad, sizeof(FORMULARIO), 1, p) != 1){
        printf(" --ERRO na listagem do pcad\n");
        exit(0);
      }  

      if(pcad -> nome[0] != '*'){
        for(j = 0; j < 20; j++){
          if ( busca[j] != pcad -> nome[j]){
            break;
          }else if (busca[j] == '\0'){
            printf("\n\n Nome: %s\n", pcad -> nome);
            printf(" Endereco: %s\n", pcad  -> end);
            printf(" Cidade: %s\n", pcad -> cidade);
            printf(" Estado: %s\n", pcad -> estado);
            printf(" CEP: %s", pcad -> cep);
            puts("\n\n");               
            return desloc;
          }
        }
      }    
    }
    fclose(p);
  }else
    printf("\n --CADASTRO VAZIO\n\n");  

  printf("\n --NUNHUM CADASTRO ENCONTRADO\n\n");
  return -1;   
  
}

void alterar(FORMULARIO *pcad, FILE *p, int n){
  long desloc = (buscar(pcad, p, n));  

  if(desloc != -1){
    if(!(p = fopen("cadastros","r+"))){
      printf("erro na abertura do arquivo \n");
      exit(0);
    }

    printf(" --Digite novo registro");
    printf("\n\n Nome: ");
    scanf(" %s", pcad -> nome);
    printf(" Endereco: ");
    scanf(" %s", pcad -> end);
    printf(" Cidade: ");
    scanf(" %s", pcad -> cidade);
    printf(" Estado: ");
    scanf(" %s", pcad -> estado);
    printf(" CEP: ");
    scanf(" %s", pcad -> cep);

    puts("\n\n");

    fseek(p,desloc,0);

    if(fwrite(pcad,sizeof(FORMULARIO),1,p) != 1){
      printf(" --ERRO na insercao do cadastro \n");
      exit(0);
    }
    else{
      printf(" --ALTERADO COM SUCESSO\n\n\n");
    }
    fclose(p);
  }
}

void excluir(FORMULARIO *pcad, FILE *p, int n){
  long desloc = (buscar(pcad, p, n));
  int opcao;  

  if(desloc != -1){
    printf(" Deseja mesmo excluir este registro?\n (1) SIM | (2) NAO");
    printf("\n opcao:> ");
    scanf("%d", &opcao);

    if(opcao == 1){
      if(!(p = fopen("cadastros","r+"))){
          printf("erro na abertura do arquivo \n");
          exit(0);
        }

        fseek(p,desloc,0);
        putc('*', p);        
        printf(" --EXCLUIDO COM SUCESSO\n\n\n");
        
        fclose(p);
    }  
  }    
}


int main(){
    FILE *p, *i;
    FORMULARIO cad;
    int opcao = 0, n_cad;
    

    if(!(i = fopen("n_cadastros","r"))){
      if(!(i = fopen("n_cadastros","w"))){
        printf("erro na abertura do arquivo contador \n");
        exit(0);
      } else{
          n_cad = 0;
          fprintf(i,"%d", n_cad);
          fclose(i);
      }
    }
      fscanf(i,"%d ", &n_cad);
      fclose(i);

    

    while(opcao != 6){

        printf("\n # MENU FORMULARIO\n -------------------------------------------------------------------------\n");
        printf(" (1) NOVO |");
        printf(" (2) LISTAR |");
        printf(" (3) BUSCAR |");
        printf(" (4) ALTERAR |");
        printf(" (5) EXCLUIR |");
        printf(" (6) SAIR \n");
        printf(" -------------------------------------------------------------------------\n");

        printf("\n opcao:> ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
        case 1: inserir(&cad, p, i, &n_cad);
                break;
        case 2: listar(&cad, p, n_cad);
                break;
        case 3: buscar(&cad, p, n_cad);
                break;
        case 4: alterar(&cad, p, n_cad);
                break;
        case 5: excluir(&cad, p, n_cad);
                break;
        case 6: printf("\n --PROGRAMA ENCERRADO\n\n\n\n");
                break;
        default: printf("\n --OPCAO INVALIDA\n\n\n\n");
        }
    }
    return 0;
}