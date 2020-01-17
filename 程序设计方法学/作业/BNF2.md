\<Program> -> \<Block>;

-> \<DeclList> BEGIN \<StmtList> END;



->  \<Decl> ; \<DeclList> 

​		BEGIN 

​			\<Stmt> ; \<StmtList>

​		END;



-> VARid: \<Type>;

​	\<Decl> ; \<DeclList>

​	BEGIN

​		\<Assignment>;

​		\<Stmt> ; \<StmtList> 

​	END;



-> VAR xyz: INTEGER;

​	 VARid: \<Type>;

​	BEGIN

​		\<Expr>:=\<Expr>;

​		\<Assignment>;

​	END;



-> VAR xyz: INTEGER;

​	 VAR count: INTEGER;

​	 BEGIN

​	 	\<Operand>:= \<Operand>

​	 	\<Expr>:=\<Expr>;

​	 END;



-> VAR xyz: INTEGER;

​	 VAR count: INTEGER;

​	 BEGIN

​	 	id:=Number

​	 	\<Operand>:=\<Expr> \<Operator> \<Operand>;

​	 END;



-> VAR xyz: INTEGER;

​	 VAR count: INTEGER;

​	 BEGIN

​	 	xyz:=5

​	 	id:=\<Operand> \<Operator> \<Operand>;

​	 END;



 -> VAR xyz: INTEGER;

​	 VAR count: INTEGER;

​	 BEGIN

​	 	xyz:=5

​	 	count:=id + Number;

​	 END;



 -> VAR xyz: INTEGER;

​	 VAR count: INTEGER;

​	 BEGIN

​	 	xyz:=5

​	 	count:=xyz + 1;

​	 END;

​	



