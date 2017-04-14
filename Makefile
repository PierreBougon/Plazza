##
## Makefile for Makefile in /home/bougon_p/rendu/TEK2/cpp_plazza
## 
## Made by bougon_p
## Login   <bougon_p@epitech.net>
## 
## Started on  Sat Apr 15 00:37:20 2017 bougon_p
## Last update Sat Apr 15 00:48:46 2017 bougon_p
##

## Include colors and basic commands

include mk/colors.mk mk/commands.mk mk/definitions.mk

## Core variables

PROJECT_NAME	=	Plazza

# Main sources

SRC_MAIN	=	main.cpp				\

# Cipher sources

CIPHER_DIR	=	cipher/

SRC_CIPHER	+=	$(CIPHER_DIR)ICipher.cpp	\
			$(CIPHER_DIR)ACipher.cpp	\
			$(CIPHER_DIR)CaesarCipher.cpp	\
			$(CIPHER_DIR)XORCipher.cpp	\

SRC		= 	$(addprefix src/, $(SRC_MAIN))
SRC		+= 	$(addprefix src/, $(SRC_CIPHER))

OBJ 		=   	$(SRC:.cpp=.o)

NAME   		=      	plazza

INC     	=       -Iinclude -Iinclude/cipher

## Core rules

include mk/rules.mk
