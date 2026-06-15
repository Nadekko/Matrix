NAME = matrix
NAME_P = projection
CXX = c++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -lm

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

SRCS_P = main_projection.cpp
OBJS_P = $(SRCS_P:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

projection: $(OBJS_P)
	$(CXX) $(CXXFLAGS) $(OBJS_P) -o $(NAME_P)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_P)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_P)

re: fclean all

# raccourcis exercices
ex00 ex01 ex02 ex03 ex04 ex05 ex06 ex07 \
ex08 ex09 ex10 ex11 ex12 ex13 all_test: $(NAME)
	./$(NAME) $@

.PHONY: all projection clean fclean re \
		ex00 ex01 ex02 ex03 ex04 ex05 ex06 ex07 \
		ex08 ex09 ex10 ex11 ex12 ex13 ex14 ex15