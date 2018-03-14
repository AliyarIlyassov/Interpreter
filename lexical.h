#ifndef __LEXICAL_H__
#define __LEXICAL_H__
#include <cstring>
#include <string>

using namespace std;

bool blank(char c);

enum type_lex {
	LEX_NULL, LEX_ASSIGN, LEX_FIN, LEX_FLOAT, 			// 0, 1, 2, 3
	LEX_ID, LEX_INT, LEX_MULT, LEX_DIV, 						// 4, 5, 6, 7
	LEX_MINUS, LEX_PLUS, LEX_PRINT, POLIZ_ADDRESS,	// 8, 9, 10, 11
	LEX_EOF																					// 12
};

struct Lex {
	type_lex t_lex;
	string v_lex;

	Lex (  );
	Lex ( type_lex t, string v );
	friend ostream & operator << ( ostream & s, Lex l );
	friend bool operator != (Lex a, Lex b);
	friend Lex operator + (Lex a, Lex b);
	friend Lex operator - (Lex a, Lex b);
};

struct Ident {
	string name;
	bool declare;
	type_lex type;
	type_lex numb_type;
	bool assign;
	string value;

	Ident ( );
//	Ident ( string Name, bool Declare, type_lex Type, bool Assign, string Value);
	friend ostream & operator << ( ostream &s, Ident &I);
};

struct tabl_ident {
	Ident * p;
	int size;
	int top;

	tabl_ident (int max_size);
	~tabl_ident ( );
	Ident & operator[] (int k);
	void put ( string buf);
};

struct Scanner {
	enum state { H, IDENT, NUMB, COM, DELIM };
	state ST;
	FILE * fp;
	char c;
	string buf;
	int buf_top;

	static type_lex TWords[];
	static type_lex TDlms[];
	static string TW[];
	static string TD[];

	Lex get_lex();
	void clear();
	void gc();
	int look ( string buf, string * list );
	Scanner ( const char * filename );
};

#endif
