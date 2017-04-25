## Generic rules for Makefiles

$(NAME):	$(OBJ)
		@$(ECHO)
		@$(ECHO) "$(BLUE) Compiled with : $(BOLD_WHITE)$(CXX)$(CLEAR)"
		@$(ECHO) "$(BLUE) Flags used \t  : $(BOLD_WHITE)$(CXXFLAGS)$(CLEAR)"
		@$(ECHO) "$(BLUE) Dependencies  :$(BOLD_WHITE)$(LDFLAGS)$(CLEAR)"
		@$(ECHO)
		@$(ECHO) "$(BLUE) ==== $(BOLD_WHITE) $(PROJECT_NAME)  Compiled $(BLUE) ==== $(CLEAR)\n\n"
ifeq ($(STATIC), YES)
		@$(LINKER) -o $(NAME) $(OBJ)
else
		@$(CXX) $(OBJ) -o $(NAME) $(INC) $(LDFLAGS)
endif
		@$(eval PROJECT_NAME=)
		@$(eval LDFLAGS=)
		@$(eval DLL=NO)
		@$(eval CXXFLAGS= -std=c++14 -W -Wall -Wextra)

all:		$(NAME)

clean:
		@$(ECHO)
		@$(ECHO) "$(BOLD_WHITE) [$(RED)RM$(BOLD_WHITE)] $(NAME) Obejcts files$(CLEAR)"
		@$(RM) $(OBJ)
#clean ui objects
		@$(RM) $(OBJ_UI)

fclean:     	clean
		@$(ECHO) "$(BOLD_WHITE) [$(RED)RM$(BOLD_WHITE)] $(NAME) Binary file$(CLEAR)\n"
		@$(RM) $(NAME)

re:		fclean all

.cpp.o:
		@$(CXX) $(CXXFLAGS) $(INC) $(LDFLAGS) -c $< -o $@
		@$(ECHO) "$(BOLD_WHITE) [$(GREEN)OK$(BOLD_WHITE)] Compiled "$<"$(CLEAR)"

.PHONY:		all clean fclean re
