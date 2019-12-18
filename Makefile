NAME = parser
FLAGS = -Wall -Werror -Wextra
FLAGS += -g

SOURCES =	main.c \
			parser.c \
			quote_control.c

DIR_O = objs

DIR_S = srcs

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

LIBFT = libft/libft.a

all:	$(NAME)

$(NAME): $(OBJS)
	@make -C ./libft
	@gcc $(FLAGS) $(OBJS) -o $(NAME) libft/libft.a

$(OBJS): $(DIR_O)/%.o: $(DIR_S)/%.c
	@mkdir -p $(DIR_O)
	gcc $(FLAGS) -c -Iincludes -o $@ $<

clean:
	@/bin/rm -Rf $(DIR_O)
	@make clean --directory ./libft

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean --directory ./libft

re:		fclean all