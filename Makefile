##
## Makefile for Makefile in /home/bougon_p/rendu/TEK2/cpp_plazza
##
## Made by bougon_p
## Login   <bougon_p@epitech.net>
##
## Started on  Sat Apr 15 00:37:20 2017 bougon_p
## Last update Wed Apr 26 13:47:54 2017 bougon_p
##

## Include colors and basic commands

include mk/colors.mk mk/commands.mk mk/definitions.mk


## Core variables

PROJECT_NAME	=	Plazza

# Main sources

MAIN	    =	main.cpp \
	                CmdParser.cpp \

MAIN_UI		=	mainUI.cpp \
			PlazzaUI.cpp \
			UIAddedFile.cpp \

SRC_ALL	    =	FileParser.cpp \
			ThreadPool.cpp \
			Worker.cpp \
			PlazzaError.cpp \

# Cipher sources

CIPHER_DIR	=	cipher/

SRC_CIPHER	+=	$(CIPHER_DIR)ICipher.cpp	\
			$(CIPHER_DIR)ACipher.cpp	\
			$(CIPHER_DIR)CaesarCipher.cpp	\
			$(CIPHER_DIR)XORCipher.cpp	\

SRC		= 	$(addprefix src/, $(SRC_ALL))
SRC		+=	$(addprefix src/, $(SRC_CIPHER))
SRC		+= 	$(addprefix src/, $(MAIN))

SRC_UI	= 	$(addprefix src/, $(SRC_ALL))
SRC_UI	+=	$(addprefix src/, $(SRC_CIPHER))
SRC_UI	+= 	$(addprefix src/, $(MAIN_UI))


OBJ 		=   	$(SRC:.cpp=.o)
OBJ_UI 		=   	$(SRC_UI:.cpp=.o)

NAME   		=      	plazza

INC     	=       -Iinclude -Iinclude/cipher -I /home/${USER}/Qt5.8.0/5.8/gcc_64/include

LDFLAGS		+=	-Wl,-rpath=/home/${USER}/Qt5.8.0/5.8/gcc_64/lib -L/home/${USER}/Qt5.8.0/5.8/gcc_64/lib -lQt5Gui -lQt5Core -lQt5Widgets -lpthread

CXXFLAGS	+=	-pthread -fPIC

## Core rules

include mk/rules.mk

ui:		$(OBJ_UI)
		@$(ECHO)
		@$(ECHO) "$(BLUE) Compiled with : $(BOLD_WHITE)$(CXX)$(CLEAR)"
		@$(ECHO) "$(BLUE) Flags used \t  : $(BOLD_WHITE)$(CXXFLAGS)$(CLEAR)"
		@$(ECHO) "$(BLUE) Dependencies  :$(BOLD_WHITE)$(LDFLAGS)$(CLEAR)"
		@$(ECHO)
		@$(ECHO) "$(BLUE) ==== $(BOLD_WHITE) $(PROJECT_NAME)  Compiled $(BLUE) ==== \
$(CLEAR)\n\n"
ifeq ($(STATIC), YES)
		@$(LINKER) -o $(NAME) $(OBJ_UI)
else
		@$(CXX) $(OBJ_UI) -o $(NAME) $(INC) $(LDFLAGS)
endif
		@$(eval PROJECT_NAME=)
		@$(eval LDFLAGS=)
		@$(eval DLL=NO)
		@$(eval CXXFLAGS= -std=c++14 -W -Wall -Wextra)
