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
}Lex operator + (Lex a, Lex b) {
  cout << a << " " << b << endl;
  if (a.t_lex != LEX_ID && b.t_lex != LEX_ID) {
    if (a.t_lex == b.t_lex) {
      if (a.t_lex == LEX_INUM) {
      	int a_ival = atoi(a.v_lex.c_str());
      	int b_ival = atoi(b.v_lex.c_str());
        cout << "HERE!";
        return Lex(LEX_INUM, to_string(a_ival + b_ival));
      }
      cout << "HERE2";
      float a_fval = atof(a.v_lex.c_str());
      float b_fval = atof(b.v_lex.c_str());
      return Lex(LEX_FNUM, to_string(a_fval + b_fval));
    }
  } else {
    int j;
    if (a.t_lex == LEX_ID) {
      j = find(a.v_lex);
      if (b.t_lex == LEX_ID) {
        int i = find(b.v_lex);
        return Lex(TID.p[j].type, TID.p[j].value) + Lex(TID.p[i].type, TID.p[i].value);
      }
      return Lex(TID.p[j].type, TID.p[j].value) + b;
    }
    j = find(b.v_lex);
    b.t_lex = a.t_lex;
    b.v_lex = a.v_lex;
    return Lex(TID.p[j].type, TID.p[j].value) + b;
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
				if (L1.t_lex != L2.t_lex)
					TID.p[j].type = LEX_FLOAT;
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
