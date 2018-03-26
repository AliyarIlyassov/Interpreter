#include "executer.h"
#include <iostream>
#include <tgmath.h>

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
	cout << endl;
	pars.prog.print();
	cout << "\nStart execute:\n";
	cout << endl;
	E.execute(pars.prog);
}

Lex operator + (Lex a, Lex b);
Lex operator - (Lex a, Lex b);

Loop::Loop () : max_size(100), last(0) { }

void Executer::execute ( Poliz& prog ) {
	Stack < Lex, 100 > args;
	int i, j, index = 0, size = prog.free;
	float f;
	Lex L1, L2;
	while ( index < size ) {

		elem = prog [ index ];

		switch(elem.t_lex) {
			case LEX_HERE:
				j = prog.loop.last;
				index = prog.loop.st.s[j] -1;
				break;
			case LEX_UNTIL:
				L1 = args.pop();
				if (L1.t_lex == LEX_ID) {
					j = find(L1.v_lex);
					L1.t_lex = LEX_FLOAT;
					L1.v_lex = TID.p[j].value;
				}
				f = atof(L1.v_lex.c_str());
				if ((L1.t_lex == LEX_TRUE) || ((L1.t_lex == LEX_INT || L1.t_lex == LEX_FLOAT) && (f)))
					break;
				else if ((L1.t_lex == LEX_FALSE) || ((L1.t_lex == LEX_INT || L1.t_lex == LEX_FLOAT) && (!f))) {
					while(prog[index].t_lex != LEX_HERE)
						++index;
					prog.loop.last++;
				}
				break;
			case LEX_AND:
				args.push(args.pop() && args.pop());
				break;
			case LEX_OR:
				args.push(args.pop() || args.pop());
				break;
			case LEX_EQUAL:
				args.push(args.pop() == args.pop());
				break;
			case LEX_NEQUAL:
				args.push(args.pop() != args.pop());
				break;
			case LEX_IF:
				L1 = args.pop();
				if (L1.t_lex == LEX_ID) {
					j = find(L1.v_lex);
					L1.t_lex = LEX_FLOAT;
					L1.v_lex = TID.p[j].value;
				}
				f = atof(L1.v_lex.c_str());
				if ((L1.t_lex == LEX_TRUE) || ((L1.t_lex == LEX_INT || L1.t_lex == LEX_FLOAT) && (f)))
					break;
				else if ((L1.t_lex == LEX_FALSE) || ((L1.t_lex == LEX_INT || L1.t_lex == LEX_FLOAT) && (!f)))
					while(prog[index].t_lex != LEX_FI && prog[index].t_lex != LEX_ELSE)
						++index;
				break;
			case LEX_SQRT:
				j = find(args.pop().v_lex);
				args.push(Lex(LEX_FLOAT, to_string(sqrt(atof(TID.p[j].value.c_str())))));
				break;
			case LEX_LN:
				j = find(args.pop().v_lex);
				args.push(Lex(LEX_FLOAT, to_string(log(atof(TID.p[j].value.c_str())))));
				break;
			case LEX_EXP:
				j = find(args.pop().v_lex);
				args.push(Lex(LEX_FLOAT, to_string(exp(atof(TID.p[j].value.c_str())))));
				break;
			case LEX_ELSE:
				while (prog[index].t_lex != LEX_FI)
					++index;
			case LEX_FI:
			case LEX_NLINE:
				break;
			case LEX_FALSE:
			case LEX_TRUE:
			case LEX_INUM:
			case LEX_FNUM:
			case LEX_FLOAT:
			case LEX_INT:
				args.push(elem);
				break;
			case POLIZ_ADDRESS:
				args.push(elem);
				break;
			case LEX_ID:
				try {
					j = find(elem.v_lex);
					if (prog[index+1].t_lex == LEX_INUM) {
						TID.p[j].numb_type = LEX_INT;
						break;
					}
					else if (prog[index+1].t_lex == LEX_FNUM) {
						TID.p[j].numb_type = LEX_FLOAT;
						break;
					}
				}
				catch(...) { cout << "POLIZ ERROR : wrong declaration\n"; }
				i = find(elem.v_lex);
				if (TID.p[i].assign)
					args.push(elem);
				else
					throw "POLIZ ERROR : indefinite identifier " + elem.v_lex;
				break;
			case LEX_PRINT:
				i = find((args.pop()).v_lex);
				cout << TID.p[i].value << "\n";
				break;
			case LEX_PLUS:
				args.push(args.pop() + args.pop());
				break;
			case LEX_MINUS:
				args.push(args.pop() - args.pop());
				break;
			case LEX_MULT:
				args.push(args.pop() * args.pop());
				break;
			case LEX_DIV:
				args.push(args.pop() / args.pop());
				break;
			case LEX_ASSIGN:
				L2 = args.pop();
				L1 = args.pop();
				j = find(L1.v_lex);
				if (TID.p[j].numb_type == LEX_INT && L2.t_lex == LEX_FLOAT)
					throw "Execute ERROR : Operands " + L1.v_lex + " and " + L2.v_lex + " have different types\n";
				TID.p[j].value = L2.v_lex;
				TID.p[j].assign = true;
				break;
			default:
				throw "POLIZ : unexpected elem " + to_string(elem.t_lex) + " " +  elem.v_lex;
		}
		++index;
	}
//	cout << "Execute finished!\n";
}
