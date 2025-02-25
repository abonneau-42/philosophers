CC = cc
NAME = philo

BUILD_DIR = .build
INCLUDES_DIR = ./includes
HEADER = philo.h

CFLAGS = -Wall -Werror -Wextra -I $(INCLUDES_DIR)
INCLUDES_FILES = $(addprefix $(INCLUDES_DIR)/, $(HEADER))

SRCS_DIR = srcs
SRCS_FILES = 	main.c \
				utils/utils.c \
				utils/get_arg.c \
				utils/lstadd_bidir.c \
				parser/parser.c \
				initialiser/initialiser.c \
				resolver/resolver.c \
				free/free_list.c \

SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS = $(patsubst $(SRCS_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c $(INCLUDES_FILES) Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re