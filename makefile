
EXEC = web-serve

CPP = c++

CPPFLAGS =-Wall -Wextra -Werror -std=c++98 -fsanitize=address

RQST= srcs/requests
SRCS =	srcs/web-server.cpp\
		$(RQST)/catchRequest.cpp\
		$(RQST)/parceRequest.cpp
HDRS =  srcs/web-server.hpp\
		$(RQST)/catchRequest.hpp\
		$(RQST)/parceRequest.hpp\

OBJS = $(SRCS:.cpp=.o)

YELLOW = \033[0;33m
GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS)
	@echo "$(YELLOW)Creating object files ...$(NC)"
	@$(CPP) $(CPPFLAGS) $(OBJS) -o $(EXEC)
	@echo "$(GREEN)Compiled successfully!$(NC)"

clean:
	@echo "$(YELLOW)Deleting objects file ...$(NC)"
	@rm -f $(OBJS) $(EXEC)
	@clear
	@echo "$(RED) object files deleted$(NC)"

fclean: clean
	@echo "$(YELLOW)Deleting executable...$(NC)"
	@rm -fr $(EXEC)
	@clear
	@echo "$(RED)executable deleted$(NC)"

re : fclean all
