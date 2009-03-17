SRC =		Client.cpp \
		ConnectionManager.cpp \
		main.cpp \
		Request.cpp \
		Response.cpp \
		Timer.cpp
##		Thread.cpp

OBJ =		$(SRC:.cpp=.o)

BIN =		zia

GCC =		g++

CXXFLAGS =	-W -Wall -I.


$(BIN)	:	$(OBJ)
		$(GCC) $(OBJ) -o $(BIN)

all	:	$(BIN)

clean	:
		rm -f *~ *.o \#*\#

fclean	:	clean
		rm -f $(BIN)

re	:	fclean all

.PHONY	:	all clean fclean re
