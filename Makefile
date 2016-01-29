.PHONY: all clean

NAME:=simpleHttpClient.out
FLAGS:=-lstdc++ -std=c++14 -ggdb -Wall -Wextra -Wshadow -pedantic -Weffc++ -O0

all: $(NAME)

$(NAME): main.cpp Connection.cpp Request.cpp Responce.cpp
	gcc $(FLAGS) $^ -o $@

clean:
	rm -f *~ $(NAME)
