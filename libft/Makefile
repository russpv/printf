NAME = libft.a
SOURCES = ft_memcpy.c \
		  ft_memset.c \
		  ft_bzero.c \
		  ft_memmove.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_calloc.c \
		  ft_strlen.c \
		  ft_toupper.c \
		  ft_tolower.c \
		  ft_isalpha.c \
		  ft_isdigit.c \
		  ft_isalnum.c \
		  ft_isspace.c \
		  ft_isascii.c \
		  ft_strlcpy.c \
		  ft_strlcat.c \
		  ft_strncmp.c \
		  ft_strchr.c \
		  ft_strrchr.c \
		  ft_strnstr.c \
		  ft_isprint.c \
		  ft_strjoin.c \
		  ft_strtrim.c \
		  ft_substr.c \
		  ft_itoa.c \
		  ft_atoi.c \
		  ft_putchar_fd.c\
		  ft_putendl_fd.c \
		  ft_putnbr_fd.c \
		  ft_putstr_fd.c \
		  ft_split.c \
		  ft_strdup.c \
		  ft_strmapi.c \
		  ft_striteri.c

BSOURCES =	  ft_lstmap_bonus.c \
			  ft_lstnew_bonus.c \
			  ft_lstadd_front_bonus.c \
			  ft_lstadd_back_bonus.c \
			  ft_lstsize_bonus.c \
			  ft_lstdelone_bonus.c \
			  ft_lstclear_bonus.c \
			  ft_lstiter_bonus.c \
			  ft_lstlast_bonus.c 

ESOURCES = ft_memccpy_extra.c \
		   ft_putstr_extra.c \
		   ft_putchar_extra.c \
		   ft_strcpy_extra.c \
		   ft_strncat_extra.c \
		   ft_strncpy_extra.c \
		   ft_strnlen_extra.c \
		   ft_strscpy_extra.c \
		   ft_print_memory_extra.c \
		   ft_putchar_utf_extra.c \
		   ft_putendl_extra.c \
		   ft_putnbr_extra.c \
		   ft_strcat_extra.c

YELLOW = \033[33m
GREEN = \033[32m
RESET = \033[0m
BOLD = \033[1m

OBJECTS = $(SOURCES:.c=.o)
BOBJECTS = $(BSOURCES:.c=.o)
EOBJECTS = $(ESOURCES:.c=.o)

AR = ar
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB = ranlib

all: $(NAME)

$(NAME): $(OBJECTS) $(EOBJECTS)
	$(AR) -rvcs $@ $?  # ar update, create, update index
	$(LIB) $(NAME)
	@echo "$(GREEN)$(BOLD)SUCCESS$(RESET)"
	@echo "$(YELLOW)Created: $(words $(OBJECTS) $(EOBJECTS)) object file(s)$(RESET)"
	@echo "$(YELLOW)Created: $(NAME)$(RESET)"

bonus: .bonus_made

.bonus_made: $(OBJECTS) $(EOBJECTS) $(BOBJECTS)
	$(AR) -rvcs $(NAME) $?
	$(LIB) $(NAME)
	-@touch .bonus_made
	@echo "$(GREEN)$(BOLD)SUCCESS$(RESET)"
	@echo "$(YELLOW)Created: $(words $(OBJECTS) $(EOBJECTS) $(BOBJECTS)) object file(s)$(RESET)"
	@echo "$(YELLOW)Created: $(NAME)$(RESET)"

%.o: %.c
	$(CC) -c $(CFLAGS) $? #Initial compilation of .c files

clean:
	rm -f $(OBJECTS) $(BOBJECTS) $(EOBJECTS)
	-@rm -f .bonus_made
	@echo "$(GREEN)$(BOLD)SUCCESS$(RESET)"
	@echo "$(YELLOW) Deleted: $(words $(OBJECTS) $(BOBJECTS) $(EOBJECTS)) object file(s)$(RESET)"

fclean: clean
	rm -f $(NAME)
	@echo "$(GREEN)SUCCESS$(RESET)"
	@echo "$(YELLOW) Deleted $(words $(NAME)) object files(s)$(RESET)"
	@echo "$(YELLOW) Deleted: $(NAME)"

re: fclean all

so:
	$(CC) $(CFLAGS) -c $(SOURCES) $(ESOURCES) $(BSOURCES) -fPIC
	$(CC) -nostartfiles -shared -o libft.so $(OBJECTS) $(EOBJECTS) $(BOBJECTS)


.PHONY: all bonus clean fclean re so
