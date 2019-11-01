
.PHONY: func


func:
	@python tools/build-lexer.py | indent -kr -ci2 -cli2 -i2 -l150 -nut >ddb2/func.c
	@python tools/build-lexer.py -i | indent -kr -ci2 -cli2 -i2 -l150 -nut >ddb2/headers/func.h

build: func
	@cd ddb2; /usr/bin/gcc -Wall -g  stack.c func.c ddb.c -o ../builds/ddbc

run:
	@builds/ddbc

func-test:
	@python tools/build-lexer.py 
