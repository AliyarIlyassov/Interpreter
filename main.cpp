#include <iostream>
#include "lexical.h"
#include "syntax.h"

tabl_ident TID(100);

int main() {

	Interpretator interpretator("program.txt");

	try {
		interpretator.interpretation();
	}
	catch(char c) { cout << "Error : " << c << "\n"; }
	catch(const char * S) { cout << "Error : " << S << "\n"; }
	catch(Lex L) { cout << "Error : " << L << "\n"; }
	catch(string S) { cout << "Error : " << S << "\n"; }
	catch(...) { cout << "Unknown Error\n"; }

	return 0;
}
