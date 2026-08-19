NAME        = codexion
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread
INCLUDES    = -I includes

SRC_DIR     = src
SRC         = $(SRC_DIR)/main.c \
              $(SRC_DIR)/parsing.c \
              $(SRC_DIR)/init.c \
              $(SRC_DIR)/cleanup.c \
              $(SRC_DIR)/time_utils.c \
              $(SRC_DIR)/logging.c \
              $(SRC_DIR)/dongle.c \
              $(SRC_DIR)/dongle_utils.c \
              $(SRC_DIR)/coder.c \
              $(SRC_DIR)/monitor.c \
              $(SRC_DIR)/simulation.c \
              $(SRC_DIR)/scheduler_heap.c \
              $(SRC_DIR)/scheduler.c

OBJ_DIR     = obj
OBJ         = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/codexion.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
