## NAME="" make -e
NAME	=	zia_ban
SRC	=	$(NAME)/$(NAME).cpp
OBJ	=	$(SRC:.cpp=.o)
BIN	=	$(NAME).dll
CXXFLAGS +=	-I. -I../nnapi
LDFLAGS +=	-shared
GCC	=	g++

$(BIN)	:	$(OBJ)
		$(GCC) $(OBJ) $(LDFLAGS) -o $(BIN)

all	:	$(BIN)

clean	:
		rm -f $(OBJ) *~

fclean	:	clean
		rm -f $(BIN)

re	:	fclean all

.PHONY	:	all clean fclean re
