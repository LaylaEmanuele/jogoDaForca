#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#define corVermelho "\033[0;31m"
#define resetarCor "\033[0m"
#define corVerde "\033[1;32m"

char leValidaTema(char tema[], int i);
char leValidaPalavra(char palavra[], int i, char escondeP[]);
char forca(char tema[], char palavra[], char escondeP[], int i, int erro); 
char validaChute(char palavra[], char escondeP[], char chute, int i, int erro, int l, char letrasUsadas[]);
char chut(char palavra[], char escondeP[], char chute, int i, int erro);
int tentativaAcerto(char palavra[], char tentativa[], int i);

 main(){
 	system("cls");
 	int i, erro, l;
 	char tema[50], palavra[50], escondeP[50], chute, resposta, tentativa[50], letrasUsadas[50];		
	erro = 0;
	l = 0;
	setlocale(LC_ALL, "Portuguese");
	
	do{
		erro = 0;
		system("cls");
		leValidaTema(tema, i);
		leValidaPalavra(palavra, i, escondeP);
		
		system("cls");
		
		do{		
			forca(tema, palavra, escondeP, i, erro);
			printf("\nQuer tentar adivinhar a palavra? Caso 'SIM' digite 'S'");
			resposta = getch();
			resposta = toupper(resposta);
			fflush(stdin);
			if(resposta == 'S'){
				printf("\nQual a palavra a ser adivinhada?");
				gets(tentativa);
				for(i=0; i<strlen(tentativa); i++) {
                	tentativa[i]=toupper(tentativa[i]);
            	}	
            	erro = tentativaAcerto(palavra,tentativa, i);
            	break;
			}
			chute = validaChute(palavra, escondeP, chute, i, erro, l, letrasUsadas);
			erro = chut(palavra,  escondeP,  chute, i, erro);
			l++;		
		} while(erro != 8 && erro != 7); 
		
		forca(tema, palavra, escondeP, i, erro);
		printf("\nDeseja jogar novamente? Se 'SIM' digite 'S'.");
		resposta = getch();
		fflush(stdin);
		resposta = toupper(resposta);
	} while(resposta == 'S');
}

char leValidaTema(char tema[], int i){
	do{

		printf("Digite o tema desejado: \n");
		gets(tema);
		fflush(stdin);
		if(strlen(tema) == 0 ) {
			printf("ERRO. O tema não pode ser vazio.");
		}
	} while(strlen(tema) == 0);
	for(i=0; i<strlen(tema); i++) {
        	tema[i]=toupper(tema[i]);
    }
}

char leValidaPalavra(char palavra[], int i, char escondeP[]){
	int flag;
	do{
		flag = 0;
		printf("Digite a palavra que será adivinhada: \n");
		gets(palavra);
		fflush(stdin);
		for(i=0; i<strlen(palavra); i++) {
    		palavra[i]=toupper(palavra[i]);
    		if(strlen(palavra) == 0 ) {
				printf("ERRO. A palavra não pode ser vazio.");
			}
			if((palavra[i] < 'A' || palavra[i] >'Z') && (palavra[i] != '\n' )){
				printf("\nERRO. A palavra não pode ter números.\n");
				flag = 1;
			}
		}
	} while((strlen(palavra) == 0) || flag == 1 );
	

	for( i = 0; i <strlen(palavra); i++) {
        escondeP[i] = '_';
        escondeP[strlen(palavra)] = '\0';
    }
}

char forca(char tema[], char palavra[], char escondeP[], int i, int erro){	
	int contador,anima;
	contador=0;
	system("cls");
	printf("O tema escolhido foi: %s \n",tema);
	printf(" _______\n");
	printf("|     %s %c %s \n",(erro>=7? corVermelho :" "), (erro>=1 &&erro!=8?'O':' '), (erro>=7? resetarCor : " "));
	printf("|     %s%c%c%c%s \n",(erro>=7? corVermelho :" "),(erro>=2 &&erro!=8?'/':' '),(erro>=2 &&erro!=8?'|':' '),(erro>=3 &&erro!=8? '\\' : ' '),(erro>=7? resetarCor : " "));
	printf("|      %s%c%s \n",(erro>=7? corVermelho :" "),(erro>=4 &&erro!=8?'|':' '),(erro>=7? resetarCor : " "));
	printf("|     %s%c %c%s\n",(erro>=7? corVermelho :" "),(erro>=5 &&erro!=8?'/':' '),(erro>=6 &&erro!=8?'\\':' '),(erro>=7? resetarCor : " "));
	printf("|\n");
	
	if(erro !=7 && erro != 8){
		for(i = 0 ; i <  strlen(escondeP); i++) {
        	printf("%c",escondeP[i]);
        	printf(" ");
    	}
	}
	if(erro == 7){
		printf("\nA palavra certa era: %s", palavra);
	}
	if(erro == 8){
		
		system("cls");
		
		do {

		for(anima = 0;anima<20;anima++){
			system("cls");
			printf("PARABÉNS VOCÊ GANHOU!!! \nA palavra era: %s %s %s\n",corVerde,palavra,resetarCor);
			printf("___________ \n|         | \n|        _|_\n|\n|\n|         O \n|        /|\\ \n|        / \\\n|\n\n");
		}
		
		for(anima =0;anima<20;anima++){
			system("cls");
			printf("PARABÉNS VOCÊ GANHOU!!! \nA palavra era: %s %s %s\n",corVerde,palavra,resetarCor);
			printf("___________ \n|         | \n|        _|_\n|\n|\n|\n|        _O_\n|         | \n|        / \\\n\n");	
		}

		for(anima = 0;anima<20;anima++){
			system("cls");
			printf("PARABÉNS VOCÊ GANHOU!!! \nA palavra era: %s %s %s\n",corVerde,palavra,resetarCor); 	
	    	printf("___________ \n|         | \n|        _|_\n|\n|\n|        \\O/\n|         | \n|        / \\\n|\n\n");
		}

			contador++;
		} while(contador<15);
		
	
	}
}

char validaChute(char palavra[], char escondeP[], char chute, int i, int erro, int l, char letrasUsadas[]){
	int flag;
	do{
		flag = 0;
		printf("\nDigite seu chute: ");
		chute = getch();	
		fflush(stdin);
		chute = toupper(chute);
		if(chute < 'A' || chute >'Z'){
			printf("\nERRO. O chute deve ser uma letra do alfabeto.");
		}
		for(i=0;i<l;i++){
			if(chute == letrasUsadas[i]){
				printf("\nERRO. Essa letra já foi utilizada.");
				flag = 1;
			}
		}
	}while((chute < 'A' || chute >'Z') || flag == 1);
	letrasUsadas[l] = chute;
	return chute;
}

char chut(char palavra[], char escondeP[], char chute, int i, int erro){
	
	int flag;
	flag = 0;
	for(i=0;i<strlen(palavra); i++){	
		if(chute == palavra[i]){
			escondeP[i] = chute;
			flag = 1;
		}
	}
	if(flag == 0){
		erro = erro + 1;
	}	
	if(strcmp(escondeP,palavra)==0){
		erro = 8;
		return erro;
	}
	return erro;
}

int tentativaAcerto(char palavra[], char tentativa[], int i){
	if(strcmp(tentativa, palavra) == 0){
		i = 8;
	}
	else {
		i = 7;	
	}
	return i;
}







