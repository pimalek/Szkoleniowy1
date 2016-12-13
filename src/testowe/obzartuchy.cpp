#include "obzartuchy.h"
#include <math.h>

#ifndef TEST
#define TEST 0
#endif

void wypiszTestoweDane(test *dane){
	int i,j;
	
	if(dane->ilosc_prob == 0){
		return;
	}
	
	printf("\n-------=========== dane testowe ==========----------\n");
	printf("Ilosc prob: %u", dane->ilosc_prob);
	
	for(i = 0; i < dane->ilosc_prob; i++){
		printf("\n - ilosc uczestnikow: %u", dane->proby[i].uczestnicy);
		printf("\n - ilosc ciastek w opakowaniu: %u", dane->proby[i].ciastka);
		
		for(j = 0; j < dane->proby[i].uczestnicy; j++){
			printf("\n   * czas zarcia %d grubasa: %u", j+1, dane->proby[i].sekundy[j]);
		}
		printf("\n");
	}
	
	printf("\n====================================================\n");
		
}


int main(){
	int wynik = 0;
	
	test dane_do_testu = TEST ? dane_testowe() : dane_zwykle();
	wypiszTestoweDane(&dane_do_testu);
	return glownyProgram(&dane_do_testu);
}
//=================================================================================

test dane_testowe(){
	proba raz = {2, 10, 0};
	proba dwa = {3, 356, 0};
	test dane_testowe;
	
	raz.sekundy = (unsigned int*) malloc(sizeof(unsigned int) * raz.uczestnicy);
	raz.sekundy[0] = 3600;
	raz.sekundy[1] = 1800;
	
	dwa.sekundy = (unsigned int*) malloc(sizeof(unsigned int) * dwa.uczestnicy);
	dwa.sekundy[0] = 123;
	dwa.sekundy[1] = 32999;
	dwa.sekundy[2] = 10101;
	
	dane_testowe = {2, 0};
	dane_testowe.proby = (proba*) malloc(sizeof(proba) * 2);
	dane_testowe.proby[0] = raz;
	dane_testowe.proby[1] = dwa;
	
	return dane_testowe;
}

test dane_zwykle(){
	return {0, 0};
}



void _getProby(test *dane){
	if(TEST){
		return (void)0;
	}
	
	printf("Podaj ilosc prob: ");
	scanf("%u", &dane->ilosc_prob);
	dane->proby = (proba*) malloc(sizeof(proba) * dane->ilosc_prob);
}

void _getUczestnicy(test *dane, unsigned int proba){
	if(TEST){
		return;
	}
	
	dane->proby[proba] = {0,0,0};
	
	printf("\nPodaj ilosc obzartuchow: ");
	scanf("%u", &(dane->proby[proba].uczestnicy));
	
	dane->proby[proba].sekundy = (unsigned int*) malloc(sizeof(unsigned int) * dane->proby[proba].uczestnicy);
	
	if(!dane->proby[proba].sekundy){
		perror("malloc - sekundy");
		return;
	}
}

void _getCiastka(test *dane, unsigned int proba){
	if(TEST){
		return;
	}
	
	printf("oraz ilosc ciastek w paczce: ");
	scanf("%u", &(dane->proby[proba].ciastka));
}

void _getCzas(test *dane, unsigned int proba){
	int i = 0;
	
	if(TEST){
		return;
	}
	
	if(dane->proby[proba].uczestnicy > 0){
		for(i = 0; i < dane->proby[proba].uczestnicy; i++){
			printf("Czas jedzenia ciastka przez obzarucha numer %d: ", i+1);
			scanf("%u", &dane->proby[proba].sekundy[i]);
		}
	}
}

int glownyProgram(test *dane){
	
	int i = 0;
	unsigned int p = 0;
	unsigned int *wyniki;
	
	_getProby(dane);

	wyniki = (unsigned int*) calloc(dane->ilosc_prob, sizeof(unsigned int));
	if(!wyniki){
		perror("malloc - wyniki");
		return EXIT_FAILURE;
	}

	while(dane->ilosc_prob - p){		
		_getUczestnicy(dane, p);		
		_getCiastka(dane, p);
		
		printf("\n");		
		_getCzas(dane, p++);
	}	
	
	
	liczPudelka(dane, wyniki);
	
	for(i = 0; i < dane->ilosc_prob; i++){
		printf("\nWynik dla %d proby: %u", i+1, wyniki[i]);
	}
	
	return 0;
}

void liczPudelka(test *dane, unsigned int *wyniki){
	int i, p = 0;
	
	while(p < dane->ilosc_prob){
		for(i = 0; i < dane->proby[p].uczestnicy; i++){
			wyniki[p] += DOBA/dane->proby[p].sekundy[i];
		}
		
		wyniki[p] = (unsigned int) ceil((double)wyniki[p]/dane->proby[p].ciastka);
		p++;
	}
}
