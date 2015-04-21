
NAME				=		computor

SRC_DIR				=		srcs
INCLUDE_DIR			=		includes
OBJ_DIR				=		objs

COMPILER			=		g++
CFLAGS				=		-std=c++11 -g3 -Wall -Wextra -Werror -c \
							-I $(INCLUDE_DIR)
LFLAGS				=		-o

SRC					=		main.cpp		\
							Computor.cpp Fraction.cpp Math.cpp

OBJ					=		$(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.cpp=.o)))

all: $(NAME)

$(NAME): $(OBJ)
	$(COMPILER) $(LFLAGS) $@ $^

$(OBJ): $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(COMPILER) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
