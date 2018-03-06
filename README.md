# Interpreter
#
# Interpreter of a simple language
#
# Prog   -> Dcls Stmts $
# Dcls   -> Dcl Dcls | Eps
# Dcl    -> "float" id | "int" id
# Stmts  -> Stm Stmts | Eps
# Stmt   -> id assign Val Expr | "print" id
# Expr   -> plus Val Expr | minus Val Expr | Eps
# Val    -> id | inum | fnum
# id     -> char id | Eps
# char   -> 'a' | 'b' | 'c' | ... | 'x' | 'y' | 'z'
# assign -> '='
# plus   -> '+'
# minus  -> '-'
# inum   -> 0 inum | 1 inum | ... | 9 inum | Eps
# fnum   -> 0 fnum '.' numb | 1 fnum '.' numb | ... | 9 fnum '.' numb
# numb   -> 0 inum | 1 inum | ... | 9 inum
# Eps    -> ''
#
# 1) Each identifier should be declared in the start of a program and declared once
# 2) In assign operator operands must be of the same type
# 3) In any place of a program, except identifiers, reserved words and numbers, there can be an arbitrary number of indents, tabs and spaces

