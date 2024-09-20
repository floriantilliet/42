CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = builtins/cd.c              execute/do_cmd.c              lexing/line_to_strings.c\
builtins/echo.c            execute/execute.c             lexing/merge_flags.c\
builtins/echo_flag.c       execute/initialise_cmd.c      lexing/merge_tokens.c\
builtins/export.c          execute/last_cmd.c            lexing/merging_utils.c\
builtins/export_parsing.c  execute/parse_exec.c          lexing/problem_checker.c\
builtins/export_utils.c    execute/redirect.c            lexing/strings_to_tokens.c\
builtins/ft_env.c          here_doc.c                    lexing/strings_to_tokens_utils.c\
builtins/ft_exit.c         lexing/check_env_var_utils.c lexing/check_env_var_utils_2.c  lexing/token_types.c\
builtins/ft_pwd.c          lexing/count_tokens.c         main.c\
builtins/unset.c           lexing/expander.c             signals.c\
cleaning_utils.c           lexing/expand_token_list.c\
env.c                      lexing/lexing_utils.c\

OBJ = $(SRC:.c=.o)
EXECUTABLE = minishell
LIBFT = libft/libft.a
all: $(EXECUTABLE)

$(LIBFT) :
	make -C libft bonus

$(EXECUTABLE): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ -lreadline -Llibft -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(EXECUTABLE)

re: fclean all

.PHONY: all clean fclean re
