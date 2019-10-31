
.PHONY: func


func:
	@python tools/build-lexer.py | indent -kr -ci2 -cli2 -i2 -l150 -nut >ddb2/func.c
	@python tools/build-lexer.py -i | indent -kr -ci2 -cli2 -i2 -l150 -nut >ddb2/headers/func.h

func-test:
	@python tools/build-lexer.py  | indent -kr -ci2 -cli2 -i2 -l150 -nut
