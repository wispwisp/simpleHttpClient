.PHONY: all clean

NAME:=simpleHttpClient.out
FLAGS:=-lstdc++ -std=c++11 -Wall -Wextra -Wshadow -pedantic -pedantic -O

all: $(NAME)

$(NAME): main.cpp Connection.cpp Request.cpp
	gcc $(FLAGS) $^ -o $@

clean:
	rm -f *~ $(NAME)
