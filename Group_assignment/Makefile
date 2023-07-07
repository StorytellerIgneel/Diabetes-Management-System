.PHONY: all compile clean test

CFLAG = g++ -Wall -Wextra -Werror

#SRC := $(wildcard ft*)

#BINS := $(SRC:%.cpp=%)

MAIN := $(shell bash -c 'read -p "Main: " main; echo $$main')

ARGS ?= $(shell bash -c 'read -p "Arguments: "; args')

#FILENAME := $(shell bash -c 'cut -d "." -f 1 <<< $(MAIN);')

#NEW := $(shell ls -tp | grep -v /$ | head -1)

all : $(BINS)

% : %.o
	$(CFLAG) $< -o $@

%.o : %.c
	g++ -c $<

compile:
	@$(CFLAG) $(MAIN).cpp -o $(MAIN)
	@clear
	@./$(MAIN)

auto:
	@cleear
	@$(CFLAG) $(SRC) $(NEW) -o $(FILENAME)
	@./$(FILENAME)
	@clear

test:
	echo $(MAIN)

clear:
	@clear

clean:
	@rm *.txt *.o
	@echo "cleaned"