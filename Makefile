NAME = matrix
CXX = c++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror


SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# raccourcis exercices
ex00 ex01 ex02 ex03 ex04 ex05 ex06 ex07 \
ex08 ex09 ex10 ex11 ex12 ex13 ex14 ex15: $(NAME)
	./$(NAME) $@

.PHONY: all clean fclean re \
		ex00 ex01 ex02 ex03 ex04 ex05 ex06 ex07 \
		ex08 ex09 ex10 ex11 ex12 ex13 ex14 ex15