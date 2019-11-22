NAME = ./42sh

CORE = main.c
MOD = strings.c exp.c extra.c built_ins.c built_in_cd_exit.c

OBJ = $(addprefix obj/, $(addprefix core/, $(CORE:.c=.o)) $(addprefix mod/, $(MOD:.c=.o)))

all: $(NAME)

$(NAME): libft obj/ $(OBJ)
	@gcc -g -L libft/ -lft $(OBJ) -o ./$(NAME)

obj/%.o: %.c
	@gcc -Wall -Wextra -Werror -g -I libft/includes -I includes -c $< -o $@
	@echo "msh–> new obj created: $@"

obj/:
	@mkdir obj
	@mkdir obj/core
	@mkdir obj/mod

libft:
	@git submodule init
	@git submodule update --remote --merge
	@make -C libft

clean:
	@make -C libft clean
	@rm -rf obj
	@echo "msh–> objs cleaned!"

fclean: clean
	@rm -rf $(NAME) $(NAME).dSYM
	@make -C libft fclean
	@echo "msh–> full cleaned!"

re: fclean all


.PHONY: libft all clean fclean re
