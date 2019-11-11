
.PHONY: func


func:
	@cd tools; python -m languish.cli | indent -kr -br -brs -brf -ce -ci2 -cli2 -i2 -l150 -nut >../ddb2/func.c
	@cd tools; python -m languish.cli -i | indent -kr -br -brs -brf -ce -ci2 -cli2 -i2 -l150 -nut >../ddb2/headers/func.h

build: func
	@cd ddb2; /usr/bin/gcc -Wall -g  stack.c func.c ddb.c -o ../builds/ddbc

build-profile: func
	@cd ddb2; /usr/bin/gcc -Wall -pg  stack.c func.c ddb.c -o ../builds/ddbc

run:
	@builds/ddbc

func-test:
	@cd tools; python -m languish.cli

profile: build-profile run
	@gprof builds/ddbc gmon.out > profiles/profile.txt
