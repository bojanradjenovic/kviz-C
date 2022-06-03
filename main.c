#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "boje.h"
#define BROJPITANJA 1567
#define STRLIMIT 1000

void obrisiRazmakeNaKraju(char str[]){
    int index, i = 0;
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n'){
            index = i;
        }

        i++;
    }
    str[index + 1] = '\0';

}
short DaLiJeBroj(char str[]){
    int i;
    int duzina = strlen(str);
    for(i = 0; i < duzina; i++){
        if(isdigit(str[i]) == 0)
            return 0;
    }
    return 1;
}

void pretvoriUMalaSlova(char str[]){
    int i;
    int duzina = strlen(str);
    for(i = 0; i < duzina; i++){
        str[i] = tolower(str[i]);
    }
}

void izaberiPitanje(char *pitanje, char odgovor[]){
	srand(time(NULL));
	int index=1+rand()%BROJPITANJA, duzinapitanja = 0, brojac = 1;
	FILE *fptr;
	fptr = fopen("pitanja.txt", "r");
	if(fptr == NULL){
    	printf("Neuspesno otvaranje fajla sa pitanjima!");
    	exit(1);
	}

	char read_string[STRLIMIT];
	while(fgets(read_string,sizeof(read_string),fptr) != NULL){
    	brojac++;
    	if(brojac == index){
        	while(read_string[duzinapitanja] != '#'){
            	duzinapitanja++;
        	}
        	pitanje = realloc(pitanje, duzinapitanja+1);
        	pitanje[duzinapitanja] = '\0';
        	memcpy(pitanje,read_string,duzinapitanja);
        	strncpy(odgovor, read_string + duzinapitanja+1, sizeof(read_string) - duzinapitanja);

    	}
	}
	fclose(fptr);

}

void kviz(){
	char nastaviti;
	char brojrundistr[STRLIMIT];
	int brojrundi;
	float poeni;
	do{
	poeni = 0;
	do{
	printf("Dobro dosli u kviz! Izaberite koliko rundi zelite da igrate: ");
	fgets(brojrundistr, sizeof(brojrundistr), stdin);
	brojrundistr[strcspn(brojrundistr, "\n")] = '\0';
	}while(DaLiJeBroj(brojrundistr) == 0);
	brojrundi = atoi(brojrundistr);
    if(brojrundi == 0){
        exit(0);
    }
	system("cls");
	for(int i = 1; i <= brojrundi; i++){
    	char *pitanje = malloc(STRLIMIT);
    	char resenje[STRLIMIT];
    	char odgovor[STRLIMIT];
    	char resenjemalo[STRLIMIT];
    	short hint = 0;
    	izaberiPitanje(pitanje, resenje);
    	printf("Runda %d/%d\n", i,brojrundi);
    	printf("%s\nUnesite odgovor (U za pomoc): ", pitanje);
        fgets(odgovor, sizeof(odgovor), stdin);
    	resenje[strcspn(resenje, "\n")] = '\0';
    	odgovor[strcspn(odgovor, "\n")] = '\0';
    	obrisiRazmakeNaKraju(odgovor);
    	pretvoriUMalaSlova(odgovor);
        strcpy(resenjemalo,resenje);
        pretvoriUMalaSlova(resenjemalo);
    	if(strcmp(odgovor, "u\0") == 0){
            hint=1;
            if(strlen(resenje) <= 5)
                printf("POMOC: %c\n", resenje[0]);
            else
                printf("POMOC: %c%c%c\n", resenje[0],resenje[1],resenje[2]);
            printf("%s\nUnesite odgovor: ", pitanje);
            fgets(odgovor, sizeof(odgovor), stdin);
            odgovor[strcspn(odgovor, "\n")] = '\0';
            obrisiRazmakeNaKraju(odgovor);
            pretvoriUMalaSlova(odgovor);
    	}
    	if(strcmp(odgovor, resenjemalo) == 0){
            zelena();
        	printf("Tacno ste odgovorili na pitanje!\n");
        	if(hint == 1) poeni += 0.5;
            else poeni++;
        	sleep(2);
            bela();
        	system("cls");
    	}
    	else{
            crvena();
        	printf("Pogresan odgovor!\n");
            bela();
        	printf("Tacan odgovor je ");
            zelena();
            printf("%s", resenje);
            bela();
            printf(".\n");
        	sleep(2);
        	system("cls");
    	}
    	free(pitanje);
	}
        printf("Osvojili ste ");
        if(poeni == 0) crvena();
        else if(poeni >= brojrundi / 2.0) zelena();
        else zuta();
        printf("%.2f ", poeni);
        bela();
        printf("poena.\n");
        printf("Da li zelite da nastavite igru? (D/N): ");
    	scanf("%c", &nastaviti);
    	fflush(stdin);
    	system("cls");
	}while(nastaviti == 'D' || nastaviti == 'd' || nastaviti == 'y' || nastaviti == 'Y');
}

int main()
{
	kviz();
	return 0;
}
