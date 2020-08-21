
#include "NewtonPascal.h"

/*
program ： program_head  routine  '.'
program_head ： 'PROGRAM'  ID  ';'
routine ： routine_head  routine_body
routine_head ： label_part  const_part  type_part  var_part  routine_part
label_part ： ε
const_part ： 'CONST'  const_expr_list  
|  ε

Program HelloWorld;
	
	{const_part}
	const 
		MAX = 1000;
	    MIN = 100;

	{type_part}
	TYPE 
		a = INTEGER; 
		b = ARRAY [1..10] OF INTEGER;
		c = b;
		d = ;
		Date=Record                   {定义Date(日期)记录类型}
			{type_decl}
			
       		day: 1..31;            {域名day表示天,为子界型(1..31)}
       		mon: 1..12;            {域名mon表示月,为子界型(1..12)}
       		yea: 1970..1999;     {域名yea表示年,为子界类型}
     	End;
	begin
	    writeln('Hello, world!');
	       {程序块的最后一条语句后不需要";" -
	         如果添加一个";"会在程序中增加一个“空语句”}
	end.

*/

void genCode(SyntaxTree T)
{
	if (T->type == PROGRAM)
	{
		if (T->type->left == 'program_head')
		{
			T->type->pcode = "lda";

		}
	}
}
