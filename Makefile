NAME = 42sh

FLAGS = -Wall -Werror #-Wextra
FLAGS += -g

#______________________________________________________________________________

BUILTIN_DIR = builtin
BUILTIN = \
			$(BUILTIN_DIR)/bg_fg_btin.c \
			$(BUILTIN_DIR)/echo.c \
			$(BUILTIN_DIR)/exit.c \
			$(BUILTIN_DIR)/history.c \
			$(BUILTIN_DIR)/init_structures.c \
			$(BUILTIN_DIR)/jobs_btin.c \
			$(BUILTIN_DIR)/pwd.c \
			$(BUILTIN_DIR)/set.c \
			$(BUILTIN_DIR)/unset.c \
			$(BUILTIN_DIR)/usages.c \
            $(CD) \
			$(FC)

CD_DIR = cd
CD =		$(BUILTIN_DIR)/$(CD_DIR)/cd.c \
			$(BUILTIN_DIR)/$(CD_DIR)/cd_flags.c \
			$(BUILTIN_DIR)/$(CD_DIR)/cd_valid.c \
			$(BUILTIN_DIR)/$(CD_DIR)/cd_parser.c \
			$(BUILTIN_DIR)/$(CD_DIR)/cd_change_path.c \
			$(BUILTIN_DIR)/$(CD_DIR)/cd_new_path.c

FC_DIR = fc
FC = 		$(BUILTIN_DIR)/$(FC_DIR)/fc.c \
			$(BUILTIN_DIR)/$(FC_DIR)/fc_exec_mode_e.c \
			$(BUILTIN_DIR)/$(FC_DIR)/fc_exec_mode_s.c \
			$(BUILTIN_DIR)/$(FC_DIR)/fc_exec.c \
			$(BUILTIN_DIR)/$(FC_DIR)/fc_modes_e.c \
			$(BUILTIN_DIR)/$(FC_DIR)/fc_modes_flags.c \
			$(BUILTIN_DIR)/$(FC_DIR)/fc_modes_l.c \
			$(BUILTIN_DIR)/$(FC_DIR)/fc_modes_no_arguments.c \
			$(BUILTIN_DIR)/$(FC_DIR)/fc_modes_s.c \
			$(BUILTIN_DIR)/$(FC_DIR)/fc_nums_calc.c \
			$(BUILTIN_DIR)/$(FC_DIR)/fc_tmpfile.c

#______________________________________________________________________________

GLOBAL_DIR = global
GLOBAL = 	$(GLOBAL_DIR)/clean_all42.c \
			$(GLOBAL_DIR)/error_handler42.c \
			$(GLOBAL_DIR)/options_proc42.c \
			$(GLOBAL_DIR)/options_42sh_42.c \
			$(GLOBAL_DIR)/signals_processing42.c \
			$(SHELL_VARIABLES) \
			$(UNIX_FUNCTIONS)

SHELL_VARS_DIR = shell_variables
SHELL_VARIABLES = \
			$(GLOBAL_DIR)/$(SHELL_VARS_DIR)/environment42.c \
			$(GLOBAL_DIR)/$(SHELL_VARS_DIR)/variables_processing42.c \
			$(GLOBAL_DIR)/$(SHELL_VARS_DIR)/variables_array_processing42.c \
			$(GLOBAL_DIR)/$(SHELL_VARS_DIR)/add_new_value.c

UNIX_FUNCS_DIR = unix_functions
UNIX_FUNCTIONS = \
			$(GLOBAL_DIR)/$(UNIX_FUNCS_DIR)/ft_count_words.c \
			$(GLOBAL_DIR)/$(UNIX_FUNCS_DIR)/ft_find_token.c \
			$(GLOBAL_DIR)/$(UNIX_FUNCS_DIR)/ft_make_techline.c
			
#______________________________________________________________________________

JOBS_DIR = jobs
JOBS =		$(JOBS_DIR)/bg_fg.c \
			$(JOBS_DIR)/exec_core.c \
			$(JOBS_DIR)/exec_init.c \
			$(JOBS_DIR)/exec_new.c \
			$(JOBS_DIR)/exec_utils.c \
			$(JOBS_DIR)/job_init.c \
			$(JOBS_DIR)/job_utils.c \
			$(JOBS_DIR)/jobs.c \
			$(JOBS_DIR)/path_parse.c \
			$(JOBS_DIR)/sig.c

#______________________________________________________________________________

PARSER_DIR = parser
PARSER = 	$(PARSER_DIR)/before_execution.c \
			$(PARSER_DIR)/find_spec.c \
			$(PARSER_DIR)/parser42.c \
			$(PARSER_DIR)/slice_to_blocks.c \
			$(ASSIGNMENT) \
			$(PATH_TREE) \
			$(QUOTING) \
			$(REDIRECTION) \
			$(SUBSTITUTION)

ASSIGNMENT_DIR = assignment
ASSIGNMENT = \
			$(PARSER_DIR)/$(ASSIGNMENT_DIR)/backend_variables.c \
			$(PARSER_DIR)/$(ASSIGNMENT_DIR)/assignment.c

PATH_TREE_DIR = path_tree
PATH_TREE = \
			$(PARSER_DIR)/$(PATH_TREE_DIR)/ft_block.c \
			$(PARSER_DIR)/$(PATH_TREE_DIR)/ft_path_help.c \
			$(PARSER_DIR)/$(PATH_TREE_DIR)/ft_path.c

QUOTING_DIR = quoting
QUOTING =	$(PARSER_DIR)/$(QUOTING_DIR)/quote_control.c \
			$(PARSER_DIR)/$(QUOTING_DIR)/pre_parsing_work.c \
			$(PARSER_DIR)/$(QUOTING_DIR)/quote_control_err.c

REDIRECTION_DIR = redirection
REDIRECTION = \
			$(PARSER_DIR)/$(REDIRECTION_DIR)/redirect.c \
			$(PARSER_DIR)/$(REDIRECTION_DIR)/ft_tmpfile.c \
			$(PARSER_DIR)/$(REDIRECTION_DIR)/redir_types_out.c \
			$(PARSER_DIR)/$(REDIRECTION_DIR)/redir_types_in.c \
			$(PARSER_DIR)/$(REDIRECTION_DIR)/fd_block.c \
			$(PARSER_DIR)/$(REDIRECTION_DIR)/here_doc.c \
			$(PARSER_DIR)/$(REDIRECTION_DIR)/here_doc_buffer.c

SUBSTITUTION_DIR = substitution
SUBSTITUTION = \
			$(PARSER_DIR)/$(SUBSTITUTION_DIR)/substitution.c \
			$(PARSER_DIR)/$(SUBSTITUTION_DIR)/ft_find_var.c \
			$(PARSER_DIR)/$(SUBSTITUTION_DIR)/param_help_func.c \
			$(PARSER_DIR)/$(SUBSTITUTION_DIR)/tilda.c \
			$(PARSER_DIR)/$(SUBSTITUTION_DIR)/ft_curv_var.c \
			$(PARSER_DIR)/$(SUBSTITUTION_DIR)/ft_substring_var.c

#______________________________________________________________________________

READLINE_DIR = readline
READLINE = 	$(READLINE_DIR)/colors.c \
			$(READLINE_DIR)/ctrl_key.c \
			$(READLINE_DIR)/cursor_position.c \
			$(READLINE_DIR)/escape.c \
			$(READLINE_DIR)/front_cursor_changes.c \
			$(READLINE_DIR)/front_insertions.c \
			$(READLINE_DIR)/print_readline_help.c \
			$(READLINE_DIR)/prompts.c \
			$(READLINE_DIR)/prompts_other.c \
			$(READLINE_DIR)/readline.c \
			$(READLINE_DIR)/start_readline42.c \
			$(READLINE_DIR)/str_edit.c \
			$(READLINE_DIR)/termcap_usage.c \
			$(READLINE_DIR)/terminal_input_changes.c \
			$(READLINE_DIR)/undo_yank_call.c \
			$(READLINE_DIR)/undo.c \
			$(READLINE_SIMPLE) \
			$(KEY_ACTIONS) \
			$(AUTO_COMPLETION) \
			$(HISTORY)

READLINE_SIMPLE_DIR = readline_simple
READLINE_SIMPLE = \
			$(READLINE_DIR)/$(READLINE_SIMPLE_DIR)/readline_simple.c \
			$(READLINE_DIR)/$(READLINE_SIMPLE_DIR)/str_edit_simple.c \
			$(READLINE_DIR)/$(READLINE_SIMPLE_DIR)/escape_simple.c \
			$(READLINE_DIR)/$(READLINE_SIMPLE_DIR)/keys_simple.c

KEY_ACTIONS_DIR = key_actions
KEY_ACTIONS = \
			$(READLINE_DIR)/$(KEY_ACTIONS_DIR)/arrow_keys.c \
			$(READLINE_DIR)/$(KEY_ACTIONS_DIR)/ctrl_kwuae.c \
			$(READLINE_DIR)/$(KEY_ACTIONS_DIR)/ctrl_tly.c \
			$(READLINE_DIR)/$(KEY_ACTIONS_DIR)/cut_keys.c \
			$(READLINE_DIR)/$(KEY_ACTIONS_DIR)/easter_egg.c \
			$(READLINE_DIR)/$(KEY_ACTIONS_DIR)/esc_t.c \
			$(READLINE_DIR)/$(KEY_ACTIONS_DIR)/esc_word_proc.c \
			$(READLINE_DIR)/$(KEY_ACTIONS_DIR)/jump_keys.c

AUTO_COMPL_DIR = auto_completion
AUTO_COMPLETION = \
			$(READLINE_DIR)/$(AUTO_COMPL_DIR)/start_completion.c \
			$(READLINE_DIR)/$(AUTO_COMPL_DIR)/front_part_compl.c \
			$(READLINE_DIR)/$(AUTO_COMPL_DIR)/analyse_line_compl.c \
			$(READLINE_DIR)/$(AUTO_COMPL_DIR)/cursor_position_completion.c \
			$(READLINE_DIR)/$(AUTO_COMPL_DIR)/menu_receipt_compl.c \
			$(READLINE_DIR)/$(AUTO_COMPL_DIR)/question_if_many_compl.c \
			$(READLINE_DIR)/$(AUTO_COMPL_DIR)/path_processing_compl.c \
			$(READLINE_DIR)/$(AUTO_COMPL_DIR)/output_buffer_compl.c

HISTORY_DIR = history
HISTORY = 	$(READLINE_DIR)/$(HISTORY_DIR)/start_history.c \
			$(READLINE_DIR)/$(HISTORY_DIR)/history_processing.c \
			$(READLINE_DIR)/$(HISTORY_DIR)/history_buffer_proc.c \
			$(READLINE_DIR)/$(HISTORY_DIR)/history_file_proc.c \
			$(READLINE_DIR)/$(HISTORY_DIR)/front_part_hist.c \
			$(READLINE_DIR)/$(HISTORY_DIR)/back_part_hist.c

#______________________________________________________________________________

SOURCES =	main.c \
			$(BUILTIN) \
			$(GLOBAL) \
			$(JOBS) \
			$(PARSER) \
			$(READLINE)

#______________________________________________________________________________

DIR_O = objs

DIR_S = srcs

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

LIBFT = libft42
LIB_INCLUDE = $(LIBFT)/includes
LIBFT_PATH = $(LIBFT)/libft42.a

INCLUDE_DIR = includes
BUILTIN_INCLUDE_DIR = $(INCLUDE_DIR)/builtins
SHARED_INCLUDE_DIR = $(INCLUDE_DIR)

#______________________________________________________________________________

all:	$(NAME)

$(NAME): $(OBJS)
	@make -C ./libft42
	@echo "\033[32;01mCompiling 42sh...\033[0m"
	@gcc $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT_PATH) -ltermcap
	@echo "\033[32;01m42sh is ready\033[0m"

$(OBJS): $(DIR_O)/%.o: $(DIR_S)/%.c includes/shell42.h
	@mkdir -p $(DIR_O)
#_____________________________________________________
	@mkdir -p $(DIR_O)/$(BUILTIN_DIR)
	@mkdir -p $(DIR_O)/$(BUILTIN_DIR)/$(CD_DIR)
	@mkdir -p $(DIR_O)/$(BUILTIN_DIR)/$(FC_DIR)
#_____________________________________________________
	@mkdir -p $(DIR_O)/$(GLOBAL_DIR)
	@mkdir -p $(DIR_O)/$(GLOBAL_DIR)/$(SHELL_VARS_DIR)
	@mkdir -p $(DIR_O)/$(GLOBAL_DIR)/$(UNIX_FUNCS_DIR)	
#_____________________________________________________	
	@mkdir -p $(DIR_O)/$(PARSER_DIR)
	@mkdir -p $(DIR_O)/$(PARSER_DIR)/$(PATH_TREE_DIR)
	@mkdir -p $(DIR_O)/$(PARSER_DIR)/$(QUOTING_DIR)
	@mkdir -p $(DIR_O)/$(PARSER_DIR)/$(ASSIGNMENT_DIR)
	@mkdir -p $(DIR_O)/$(PARSER_DIR)/$(SUBSTITUTION_DIR)
	@mkdir -p $(DIR_O)/$(PARSER_DIR)/$(REDIRECTION_DIR)
#_____________________________________________________
	@mkdir -p $(DIR_O)/$(JOBS_DIR)
#_____________________________________________________	
	@mkdir -p $(DIR_O)/$(READLINE_DIR)
	@mkdir -p $(DIR_O)/$(READLINE_DIR)/$(READLINE_SIMPLE_DIR)
	@mkdir -p $(DIR_O)/$(READLINE_DIR)/$(KEY_ACTIONS_DIR)
	@mkdir -p $(DIR_O)/$(READLINE_DIR)/$(AUTO_COMPL_DIR)
	@mkdir -p $(DIR_O)/$(READLINE_DIR)/$(HISTORY_DIR)
#_____________________________________________________	
	gcc $(FLAGS) -c -I$(LIB_INCLUDE) -I$(BUILTIN_INCLUDE_DIR) -I$(SHARED_INCLUDE_DIR) -o $@ $<

clean:
	@echo "\033[34mDeleting 42sh o-files\033[0m"
	@/bin/rm -Rf $(DIR_O)
	@make clean --directory ./libft42

fclean: clean
	@echo "\033[34mDeleting 42sh binary\033[0m"
	@/bin/rm -f $(NAME)
	@make fclean --directory ./libft42

re:		fclean all

.PHONY: all fclean clean re
