NAME = libftprintf.a

SOURCES = ft_printf.c \
			formats.c \
		  flags.c \
			flags2.c \
		  utils.c \
			ft_strlen.c \
			ft_putstr.c \
			ft_putchar.c \
			ft_putnbr.c \
			ft_itoa.c \
			ft_itoa_base.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_isdigit.c \
			ft_memcpy.c \
			ft_memset.c \
			ft_toupper.c \
			ft_strncmp.c 

BSOURCES =	ft_printf.c \
			formats.c \
		  flags.c \
			flags2.c \
		  utils.c \
			ft_strlen.c \
			ft_putstr.c \
			ft_putchar.c \
			ft_putnbr.c \
			ft_itoa.c \
			ft_itoa_base.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_isdigit.c \
			ft_memcpy.c \
			ft_memset.c \
			ft_toupper.c \
			ft_strncmp.c 


YELLOW = \033[33m
GREEN = \033[32m
RESET = \033[0m
BOLD = \033[1m

OBJECTS = $(SOURCES:.c=.o)
BOBJECTS = $(BSOURCES:.c=.o)

AR = ar -rvcs
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror 

# Targets
all: $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ 


$(NAME): $(OBJECTS)
	@echo "Creating $(NAME) archive..."
	@if ! $(AR) $@ $^ >> error.txt 2>&1; then \
		echo "$(RED)$(BOLD)MAKEFILE TERMINATED!$(RESET)"; \
		echo "$(YELLOW)Error creating $(NAME)$(RESET)"; \
		echo "\n\n$(RED)$(BOLD)ERROR$(RESET)"; \
		sed '$$d' error.txt; \
		echo "\n\n$(YELLOW)EXITING$(RESET)"; \
		exit 1; \
	fi
	@ranlib $@
	@echo "$(GREEN)$(BOLD)SUCCESS$(RESET)"
	@echo "$(YELLOW)Created: $(words $(OBJECTS) $(LIBFT_AR)) object file(s)$(RESET)"
	@echo "$(YELLOW)Created: $(NAME)$(RESET)"
	
bonus: .bonus_made

.bonus_made: $(OBJECTS) $(BOBJECTS)
	@echo "Creating $(NAME) archive (with bonus)..."
	$(AR) $(NAME) $?
	-@touch .bonus_made
	@echo "$(GREEN)$(BOLD)SUCCESS$(RESET)"
	@echo "$(YELLOW)Created: $(words $(OBJECTS) $(BOBJECTS)) object file(s)$(RESET)"
	@echo "$(YELLOW)Created: $(NAME)$(RESET)"

clean:
	-@$(RM) .bonus_made error.txt # dash to suppress error msgs
	@if [ -n "$$(ls -A $(OBJECTS) $(BOBJECTS) 2>/dev/null)" ]; then \
		$(RM) $(OBJECTS) $(BOBJECTS); \
		echo "$(GREEN)$(BOLD)SUCCESS$(RESET)"; \
		echo "$(YELLOW) Deleted: $(words $(OBJECTS) $(BOBJECTS)) object file(s)$(RESET)"; \
	fi

fclean: clean
	@if [ -n "$$(ls -A $(NAME)  2>/dev/null)" ]; then \
		$(RM) $(NAME) $(LIBFT_AR); \
		echo "$(GREEN)SUCCESS$(RESET)"; \
		echo "$(YELLOW) Deleted: $(NAME) and $(LIBFT_AR)$(RESET)"; \
	fi

re: fclean all

so:
	$(CC) -fPIC $(CFLAGS) -c $(SOURCES) $(BSOURCES)
	$(CC) -nostartfiles -shared -o libftprintf.so $(OBJECTS) $(BOBJECTS)
	@echo "$(GREEN)$(BOLD)SUCCESS$(RESET)"
	@echo "$(YELLOW)Created: libftprintf.so$(RESET)"

.PHONY: all bonus clean fclean re so
