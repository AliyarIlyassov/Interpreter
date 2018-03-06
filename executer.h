#ifndef __EXECUTER_H__
#define __EXECUTER_H__
#include "syntax.h"

struct Executer {
	Lex elem;

	void execute ( Poliz & prog );
};


struct Interpretator {
	Parser pars;
	Executer E;	
	Interpretator (const char *program) : pars(program) { }
	void interpretation();
};

#endif
