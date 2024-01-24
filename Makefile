NAME = minishell
CFLAGS = -g3 -Wall -Werror -Wextra

# Paths for libraries
LIB_PATH = ./libs/libft
LIB_NAME = libft.a

# Colors Definition
GREEN = "\033[32;1m"
RED = "\033[31;1m"
CYAN = "\033[36;1;3;208m"
WHITE = "\033[37;1;4m"
COLOR_LIMITER = "\033[0m"

# Paths for libraries
BIN_PATH = ./bin/
SOURCES_PATH = ./src/
READ_SOURCES_PATH = ./src/read/
LEXER_SOURCES_PATH = ./src/lexer/
INCLUDES_PATH = ./includes/

SOURCES = main.c

READ_SOURCES = ft_readline.c

LEXER_SOURCES = ft_strtok.c tokens.c token_types.c

OBJECTS = $(addprefix $(BIN_PATH), $(SOURCES:%.c=%.o))

READ_OBJECTS = $(addprefix $(BIN_PATH), $(READ_SOURCES:%.c=%.o))

LEXER_OBJECTS = $(addprefix $(BIN_PATH), $(LEXER_SOURCES:%.c=%.o))


all: libft $(BIN_PATH) $(NAME)

libft:
ifeq ($(wildcard $(LIB_PATH)/$(LIB_NAME)),)
	@make -C $(LIB_PATH) --no-print-directory
endif

$(BIN_PATH)%.o: $(SOURCES_PATH)%.c
	@echo $(GREEN)[Compiling minishell]$(COLOR_LIMITER) $(WHITE)$(notdir $(<))$(COLOR_LIMITER)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_PATH)
	@echo " "

$(BIN_PATH)%.o: $(READ_SOURCES_PATH)%.c
	@echo $(GREEN)[Compiling minishell]$(COLOR_LIMITER) $(WHITE)$(notdir $(<))$(COLOR_LIMITER)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_PATH)
	@echo " "

$(BIN_PATH)%.o: $(LEXER_SOURCES_PATH)%.c
	@echo $(GREEN)[Compiling minishell]$(COLOR_LIMITER) $(WHITE)$(notdir $(<))$(COLOR_LIMITER)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_PATH)
	@echo " "

$(NAME): $(READ_OBJECTS) $(OBJECTS) $(LEXER_OBJECTS)
	@echo $(CYAN)" --------------------------------------------------"$(COLOR_LIMITER)
	@echo $(CYAN)"| MINISHELL executable was created successfully!! |"$(COLOR_LIMITER)
	@echo $(CYAN)"--------------------------------------------------"$(COLOR_LIMITER)
	@$(CC) $(CFLAGS) -o $(NAME) $(READ_OBJECTS) $(LEXER_OBJECTS) $(OBJECTS) -L $(LIB_PATH) -lft -lreadline
	@echo " "

$(BIN_PATH):
	@mkdir -p $(BIN_PATH)

clean:
	@echo $(RED)[Removing Objects]$(COLOR_LIMITER)
	@rm -rf $(LIB_PATH)/$(LIB_NAME)
	@rm -rf $(BIN_PATH)

fclean: clean fclean_bonus
	@echo $(RED)[Removing $(NAME) executable]$(COLOR_LIMITER)
	@make fclean -C $(LIB_PATH) --no-print-directory
	@rm -rf $(NAME)

fclean_bonus:
ifneq ($(wildcard $(BONUS_NAME)),)
	@echo $(RED)[Removing $(BONUS_NAME) executable]$(COLOR_LIMITER)
	@rm -rf $(BONUS_NAME)
endif

re: fclean
	@make --no-print-directory

.PHONY: all clean fclean re libft bonus