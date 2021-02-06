#pragma once

#include <string.h>

#define TRUE 1
#define FALSE 0

class CPorter
{
public:
	static int stem(char * p, int i, int j);

private:
	static int cons(int i);
	static int m();
	static int vowelinstem();
	static int doublec(int j);
	static int cvc(int i);
	static int ends(char * s);
	static void setto(char * s);
	static void r(char * s);
	static void step1ab();
	static void step1c();
	static void step2();
	static void step3();
	static void step4();
	static void step5();

	static char * b;
	static int k,k0,j;

};
