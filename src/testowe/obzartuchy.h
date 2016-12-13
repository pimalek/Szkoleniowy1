#ifndef _INC_STDIO
#include <stdio.h>
#endif

#ifndef _INC_STDLIB
#include <stdlib.h>
#endif


#define DOBA 24*3600
#define TEST 1

struct _proba{
	unsigned int uczestnicy;
	unsigned long ciastka;
	unsigned int *sekundy;
};
typedef struct _proba proba;

struct _test{
	unsigned int ilosc_prob;
	proba *proby;
};
typedef struct _test test;

extern void liczPudelka(test *dane, unsigned int *wyniki);
extern int glownyProgram(test *dane);
extern test dane_testowe();
extern test dane_zwykle();

extern void _getProby(test *dane);
extern void _getUczestnicy(test *dane, unsigned int proba);
extern void _getCiastka(test *dane, unsigned int proba);
extern void _getCzas(test *dane, unsigned int proba);

extern void wypiszTestoweDane(test *dane);
