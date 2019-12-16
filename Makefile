NAME = readline

FLAGS = -Wall #-Werror -Wextra
FLAGS += -g

SOURCES =	main.c \
			readline.c \
			terminal_input_changes.c \
			termcap_usage.c \
			cursor_position.c \
			str_edit.c \
			undo.c \
			non_printable.c \
			escape.c \
			ctrl_key.c \
			ctrl_kwuae.c \
			ctrl_tl.c \
			arrow_keys.c \
			esc_cursor_ccp.c \
			esc_undo_completion_transpose.c \
			print_readline_help.c \
			ft_xmalloc.c \
			ft_realloc.c \
			swap_chars.c \
			ft_issign.c

DIR_O = objs

DIR_S = srcs

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

LIBFT = libft/libft.a

all:	$(NAME)

$(NAME): $(OBJS)
	@make -C ./libft
	@echo "\x1b[32;01mCompiling readline...\x1b[0m"
	@gcc $(FLAGS) $(OBJS) -o $(NAME) libft/libft.a -ltermcap
	@echo "\x1b[32;01mReadline is ready\x1b[0m"

$(OBJS): $(DIR_O)/%.o: $(DIR_S)/%.c includes/readline.h
	@mkdir -p $(DIR_O)
	gcc $(FLAGS) -c -I includes -o $@ $<

clean:
	@echo "\033[34mDeleting ft_select o-files\033[0m"
	@/bin/rm -Rf $(DIR_O)
	@make clean --directory ./libft

fclean: clean
	@echo "\033[34mDeleting ft_select binary\033[0m"
	@/bin/rm -f $(NAME)
	@make fclean --directory ./libft

re:		fclean all

.PHONY: all fclean clean re
