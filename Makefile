
.PHONY: func


func:
	@clear
	@cd tools; python -m languish.cli | indent -kr -br -brs -brf -ce -ci2 -cli2 -i2 -l150 -nut >../ddb2/expressions.c
	@cd tools; python -m languish.cli -e| indent -kr -br -brs -brf -ce -ci2 -cli2 -i2 -l150 -nut >../ddb2/headers/expressions.h
	@cd tools; python -m languish.cli -i | indent -kr -br -brs -brf -ce -ci2 -cli2 -i2 -l150 -nut >../ddb2/headers/func.h

build: func
#	@cd ddb2; /usr/bin/gcc -Wno-unused-variable -Wall -g  stack.c tokens.c func.c  ddb.c -o ../builds/ddbc  
	@cd ddb2; /usr/bin/gcc -Wno-unused-variable -Wall -g  expressions.c   stack.c parse.c   ddb.c -o ../builds/ddbc  

build-profile: func
	@cd ddb2; /usr/bin/gcc -Wno-unused-variable -Wall -pg  stack.c tokens.c  func.c ddb.c -o ../builds/ddbc 

run:
	@builds/ddbc test/sql/cli.txt

go: build run


func-test:
	@cd tools; python -m languish.cli

profile: build-profile run
	@gprof builds/ddbc profiles/gmon.out > profiles/profile.txt

watch-time:
	@watch -n .3 'time make run  >/dev/null'

pipe:
	@cat test/sql/cli.txt | builds/ddbc 

cli:
	@builds/ddbc test/sql/cli.txt
