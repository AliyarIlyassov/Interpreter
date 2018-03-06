#include "executer.h"
#include <iostream>

extern tabl_ident TID;

template <typename T, int max_size >
void Stack <T, max_size >::push(T i) {
	if ( !is_full() ) {
		s[top++] = i;
	} else
		throw "Stack is full";
}

template <class T, int max_size >
T Stack <T, max_size >::pop() {
	if ( !is_empty() ) {
		--top;
		return s[top];
	} else
		throw "Stack is empty";
}


void Interpretator::interpretation() {
	pars.analyze();
	pars.prog.print();
	cout << "\nStart execute:\n";
	E.execute(pars.prog);
}

int find(string key) {
	for (int i = 0; i < TID.top; i++) {
		if (TID.p[i].name == key)
			return i;
	}
}

void Executer::execute ( Poliz& prog ) {
	Stack < Lex, 100 > args;
	int i, j, index = 0, size = prog.free;
	Lex L1, L2;
	while ( index < size ) {

		elem = prog [ index ];

		switch(elem.t_lex) {
			case LEX_FNUM:
			case LEX_INUM:
			case POLIZ_ADDRESS:
				args.push(elem);
				break;
			case LEX_ID:
				i = find(elem.v_lex);
				if (TID[i].assign) {
					args.push(elem);
					break;
				} else
					throw "POLIZ : indefinite identifier";
				break;
			case LEX_PRINT:
				i = find((args.pop()).v_lex);
				cout << TID.p[i].value << "\n";
				break;
			case LEX_PLUS:
				L2 = args.pop();
				L1 = args.pop();
				args.push(L1 + L2);
				break;
			case LEX_MINUS:
				L2 = args.pop();
				L1 = args.pop();
				args.push(L1 - L2);
				break;
			case LEX_ASSIGN:
				L2 = args.pop();
				L1 = args.pop();
				j = find(L1.v_lex);
				TID.p[j].value = L2.v_lex;
				TID.p[j].assign = true;
				break;
			default:
				throw "POLIZ : unexpected elem " + to_string(elem.t_lex) + " " +  elem.v_lex;
		}
		++index;
	}
	cout << "Execute finished!\n";
}
