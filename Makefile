NAME = readline

FLAGS = -Wall #-Werror -Wextra
FLAGS += -g

READLINE_SIMPLE =	readline_simple/readline_simple.c \
			readline_simple/str_edit_simple.c \
			readline_simple/escape_simple.c \
			readline_simple/keys_simple.c

KEY_ACTIONS =		key_actions/ctrl_kwuae.c \
			key_actions/ctrl_tly.c \
			key_actions/arrow_keys.c \
			key_actions/esc_word_proc.c \
			key_actions/esc_t.c \
			key_actions/non_printable.c

AUTO_COMPLETION =	auto_completion/start_completion.c \
			auto_completion/output_buffer.c

LIBFT_42 =			libft_42/ft_xmalloc.c \
			libft_42/ft_realloc.c \
			libft_42/swap_chars.c \
			libft_42/swap_ints.c \
			libft_42/ft_straddsy.c \
			libft_42/ft_issign.c 

SOURCES =	main.c \
			signals.c \
			readline.c \
			prompts.c \
			terminal_input_changes.c \
			termcap_usage.c \
			cursor_position.c \
			str_edit.c \
			undo_yank_call.c \
			undo.c \
			escape.c \
			ctrl_key.c \
			print_readline_help.c \
			$(READLINE_SIMPLE) \
			$(KEY_ACTIONS) \
			$(AUTO_COMPLETION) \
			$(LIBFT_42)

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
	@mkdir -p $(DIR_O)/readline_simple
	@mkdir -p $(DIR_O)/auto_completion
	@mkdir -p $(DIR_O)/key_actions
	@mkdir -p $(DIR_O)/libft_42
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
