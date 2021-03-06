HEADERS := $(wildcard src/*.h)
SOURCES := $(wildcard src/*.cpp)
PROJECT := knights_tour

all : $(PROJECT) $(TEST_PROJECT)

$(PROJECT) : $(HEADERS) $(SOURCES) Makefile
	g++ -o $(PROJECT) $(SOURCES) -lcryptominisat5 -g -Wall -Werror -Wextra -O1 -flto
