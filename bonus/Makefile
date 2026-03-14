##
## EPITECH PROJECT, 2026
## G-OOP-400-LIL-4-1-tekspice-27
## File description:
## Makefile
##

SRC_BONUS           =   GraphicalCircuit.cpp \
						main.cpp \
						VisualComponent.cpp \
						HandleMouse.cpp \
						Createcomponent.cpp \
						CreatePins.cpp
						

SRC 			=   ../src/AComponent.cpp							\
					../src/ComponentFactory.cpp					\
					../src/Circuit.cpp								\
					../src/Parser.cpp								\
					../src/Shell.cpp

SRC_GATES		=	../src/components/gates/C4001.cpp				\
					../src/components/gates/C4011.cpp				\
					../src/components/gates/C4030.cpp				\
					../src/components/gates/C4069.cpp				\
					../src/components/gates/C4071.cpp				\
					../src/components/gates/C4081.cpp

SRC_ADVANCED	=	../src/components/advanced/C4008.cpp			\
					../src/components/advanced/C4013.cpp			\
					../src/components/advanced/C4017.cpp			\
					../src/components/advanced/C4040.cpp			\
					../src/components/advanced/C4094.cpp			\
					../src/components/advanced/C4512.cpp			\
					../src/components/advanced/C4514.cpp			\
					../src/components/advanced/C4801.cpp			\
					../src/components/advanced/C2716.cpp

SRC_SPECIAL		=	../src/components/special/ClockComponent.cpp	\
					../src/components/special/FalseComponent.cpp	\
					../src/components/special/InputComponent.cpp	\
					../src/components/special/OutputComponent.cpp	\
					../src/components/special/TrueComponent.cpp	\
					../src/components/special/LoggerComponent.cpp
	
SRC_ELEMENTARY	=	../src/components/elementary/AndComponent.cpp	\
					../src/components/elementary/NotComponent.cpp	\
					../src/components/elementary/OrComponent.cpp	\
					../src/components/elementary/XorComponent.cpp

OBJ 		=	$(SRC:.cpp=.o) $(SRC_BONUS:.cpp=.o)  $(SRC_GATES:.cpp=.o) $(SRC_ADVANCED:.cpp=.o) $(SRC_SPECIAL:.cpp=.o) $(SRC_ELEMENTARY:.cpp=.o)

CXX 		=	g++

CXXFLAGS	= 	-Wall -Wextra -Werror -std=c++20 -I../include

LDFLAGS += -lsfml-graphics -lsfml-window -lsfml-system

RM 			=	rm -f

NAME 		=	nanotekspice_bonus

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME)  $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re