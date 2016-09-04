#include <stdio.h>
#include <stdlib.h>
int main() {
/*primeiramente tenha o arquivo  cenario.mundo.txt q é pego no site*/
FILE *fp;
fp = fopen("cenario.mundo.txt","r");
FILE *nova;
nova=fopen("criptografia.txt","w");
/*esse nova é o novo aquivo que vc vai criar com os codgidos da criptografada q vai fica na mesma pasta do projeto*/
char senha[]="ROSEbud";/*senha do site*/
int fim,i;
char crip;

//verificacao de erro
if (fp == NULL) {
printf("Impossível abrir arquivo");
exit(1);
}

//verificacao de erro
if (nova == NULL) {
printf("Impossivel abrir arquivo");
exit(2);
}
/*fim recebe o valor da char q ele encontra no arquivo enquanto esse valor nao for igual a EOF ele continua */
for(i=0;(fim=fgetc(fp)) != EOF;i++)
{
    //pra repitir a senha varias vezes ele vai verificar se ele é igual ao seu tamanha se for ele volta a ser 0
    if(i==strlen(senha))
    {
        i=0;
    }
    //transformacao de um inteiro em char ja que \0 é um char nulo
    crip=fim-'\0';
    //criptografia o monitor disse q a criptografia era o char mais a senha, e o  inverso do char obitido na soma ai só fazer o contrario
    // esse til qr dizer INVERSO, ai ele coloca tudo no novo arquivo q vc criou ^^
    fprintf(nova,"%c",~crip-senha[i]);
}
    fclose(fp);
    fclose(nova);
return 0;
}
