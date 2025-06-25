CC = cc
NAME = philo

BUILD_DIR = .build
INCLUDES_DIR = ./includes
HEADER = philo.h

#CFLAGS = -Wall -Werror -Wextra -I $(INCLUDES_DIR)
CFLAGS = -Wall -Werror -Wextra -I $(INCLUDES_DIR) -fsanitize=thread -g3

INCLUDES_FILES = $(addprefix $(INCLUDES_DIR)/, $(HEADER))

SRCS_DIR = srcs
SRCS_FILES = 	main.c \
				utils/utils.c \
				utils/get_arg.c \
				utils/lstadd_bidir.c \
				parser/parser.c \
				initialiser/initialiser.c \
				resolver/resolver.c \
				resolver/resolver_utils.c \
				resolver/print_action.c \
				resolver/destroy_mtx.c \
				resolver/philo/ph_worker.c \
				resolver/philo/ph_worker_utils.c \
				resolver/philo/ph_fk_actions.c \
				resolver/philo/ph_get_dead.c \
				resolver/philo/ph_inc_meal_count.c \
				resolver/philo/ph_is_dead.c \
				resolver/philo/ph_sleep.c \
				resolver/manager.c \
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