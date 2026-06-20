NAME = matrix
NAME_P = projection

CXX = c++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror

INC = $(wildcard include/*.hpp)

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

SRCS_P = main_projection.cpp
OBJS_P = $(SRCS_P:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

projection: $(NAME_P)

$(NAME_P): $(OBJS_P)
	$(CXX) $(CXXFLAGS) $(OBJS_P) -o $(NAME_P)

%.o: %.cpp $(INC)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_P)

fclean: clean
	rm -f $(NAME) $(NAME_P)

re: fclean all

.PHONY: all projection clean fclean re