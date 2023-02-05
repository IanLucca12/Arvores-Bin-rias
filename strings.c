#include <stdio.h>
#include <string.h>

typedef struct No No;
struct No{
char Campo_Chave[100];
int Linha;
No *Direita;
No *Esquerda;

};

FILE acessLine(FILE *fp, int line){  /* the first argument is a file pointer that points to the first element of a file*/
                                        /*the second argument is the line u want to acess*/
                                        /*after using this the next fgetc(fp) will point to the first element of the line u wanted to acess*/
    char ch;                            /*see an exemple in the main*/
    int count = 1;
    while(count<line){
        ch = fgetc(fp);
        if(ch == 10){
            count = count+1;
        }
    }
    return *fp;
}

void PrintNo(No* head, char nome_arquivo[30], FILE *fp){ /*parameters: n� raiz, nome do arquivo, ponteiro pro come�o do arquivo*/
    int a=1;
    int i=0;
    FILE *fp2;
    fp2 = fopen(nome_arquivo,"r");
    char ch[550];
    if (head->Esquerda==NULL && head->Direita==NULL){

        a=head->Linha;
        *fp2 = acessLine(fp, a);
        do{
            ch[i]=fgetc(fp2);
            i++;
        }while(ch[i]!=10);
        printf("%s", ch);
        i=0;
        fclose(fp2);
        }else if(head->Esquerda!=NULL){
            PrintNo(head->Esquerda, nome_arquivo, fp);
            a=head->Esquerda->Linha;
            *fp2 = acessLine(fp, a);
            do{
            ch[i]=fgetc(fp2);
            i++;
        }while(ch[i]!=10);
        printf("%s", ch);
        i=0;
        fclose(fp2);
        }else {
            a=head->Direita->Linha;
            *fp2 = acessLine(fp, a);
            do{
            ch[i]=fgetc(fp2);
            i++;
        }while(ch[i]!=10);
        printf("%s", ch);
        i=0;
            PrintNo(head->Direita, nome_arquivo,fp);}
            fclose(fp2);
}


void liberal_geral(No* head){
    if (head->Esquerda==NULL && head->Direita==NULL){
       free(head);
        }else if(head->Esquerda!=NULL){
            liberal_geral(head->Esquerda);
            free(head->Esquerda);
        }else {
            liberal_geral(head->Direita);
            free(head->Direita);}
}


int alfabeto(char str1[100], char str2[100]){      //retorna 1 se a str1 estiver depois no alfabeto
        int i = 0;                                  // caso contrario retorna 0
        int a = 0;
        int b = 0;

        while(str1[i] != '\0'){
            str1[i] = tolower(str1[i]);
            i = i+1;
        }i=0;
        while(str2[i] != '\0'){
            str2[i] = tolower(str2[i]);
            i = i+1;
        }i=0;
        while(str1[a] != '\0' && str2[b] != '\0'){
        if(str1[a]<=122 && str1[a ]>=97){
            if(str2[b]<=122 && str2[b]>=97){
                if(str1[a]>str2[b]){
                    return 1;
                }else if(str1[a]<str2[b]){
                    return 0;
                }else{a++;
                      b++;}
            }else{b++;}
        }else{a++;}

        }return 0;
}



No* tree(No *A, int Line, char Key[100]){
        if(A!=NULL){
            if(alfabeto(Key, A->Campo_Chave) == 0){
                    tree(A->Esquerda, Line, Key);

            }else{tree(A->Direita, Line, Key);}
        }else{
            A = (No*)malloc(sizeof(No));
            A -> Linha = Line;
            strcpy(A -> Campo_Chave, Key);
            A -> Esquerda = NULL;
            A -> Direita = NULL;
        }

}


int main() {
   // int count =0;
   FILE *ptr, *ptr2;
   No *Teste = NULL;
   No *B = NULL;
   int linha=1;
   int i=0;
   char ch;
   char Arquivo[30];
   char busca[100];
   char concatenada[100];
   char Country[100], Region[100], Sigla[10], str[50];
   long int A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16,A17,A18,A19,A20,A21,A22,A23,A24,A25,A26,A27,A28,A29,A30,A31;
do{
   printf("digite a opcao desejada\n");
   printf("1 - Para Carrregar o Arquivo\n");
   printf("2 - Emitir o Relatorio\n");
   printf("3 - Sair \n");
   scanf("%d",&i);
   switch(i){
   case 1:
        printf("digite o nome do arquivo de entrada com a extensao\n");
        scanf("%s",Arquivo);
        ptr=fopen(Arquivo,"r");
            if (ptr == NULL) {
                printf("no such file.\n");
            break;
            }else{
                printf("O arquivo foi aberto\n");
            }
            do{   printf("estou aqui\n");
                fscanf(ptr,"%s%s%s",Country, Sigla,Region);
                strcat(Country, Region);
                Teste = tree(Teste, linha, Country);
                linha++;
                fclose(ptr);
                ptr=fopen(Arquivo,"r");
                *ptr=acessLine(ptr,linha);
                ch = fgetc(ptr);
                printf("%d", linha);


            }while(linha!=216);
            ptr=fopen(Arquivo,"r");
        break;
    case 2:
        PrintNo(Teste,Arquivo,ptr);
        break;
    case 3:
        liberal_geral(Teste);
        fclose(ptr);
        break;
   }}while(i!=3);
   return 0;
}
