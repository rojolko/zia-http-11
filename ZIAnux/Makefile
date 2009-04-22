SRC =		Client.cpp \
		Config.cpp \
		ConnectionManager.cpp \
		DynamicObject.cpp \
		main.cpp \
		ModuleInfo.cpp \
		ModuleManager.cpp \
		Request.cpp \
		Response.cpp \
		Timer.cpp \
		Tools.cpp
#		utilisationthread.cpp
#		Thread.cpp \


OBJ =		$(SRC:.cpp=.o)

BIN =		zia

GCC =		g++

LDFLAGS	=	-ldl

CXXFLAGS =	-Wno-return-type  -I. -Innapi


$(BIN)	:	$(OBJ)
		$(GCC) $(LDFLAGS) $(OBJ) -o $(BIN)

all	:	$(BIN)

clean	:
		rm -f *~ *.o \#*\#

fclean	:	clean
		rm -f $(BIN)

re	:	fclean all

.PHONY	:	all clean fclean re
