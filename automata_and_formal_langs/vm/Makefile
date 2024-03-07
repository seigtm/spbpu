mvm:	vm.c lex.yy.c vmparse.tab.h main.c
	gcc -o mvm main.c vm.c lex.yy.c vmparse.tab.c

lex.yy.c:	vmlex.l
	flex vmlex.l

vmparse.tab.h:	vmparse.y
	bison -d vmparse.y
	
clean:
	rm lex.yy.c vmparse.tab.h vmparse.tab.c

distclean:
	rm mvm lex.yy.c vmparse.tab.h vmparse.tab.c

