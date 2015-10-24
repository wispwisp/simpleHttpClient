NAME:=simpleHttpClient
FLAGS:=-lstdc++ -std=c++11 -Wall -Wextra -Wshadow -pedantic -pedantic -O

all: $(NAME)

$(NAME): main.cpp Connection.cpp
	gcc $(FLAGS) $^ -o $(NAME).out

clean:
	rm -f *.out *~ $(NAME).out
