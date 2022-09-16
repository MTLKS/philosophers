NAME		= philo_bonus
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g
RM			= rm -rf

INCLUDES	= ./includes
SRC_PATH	= ./src
OBJ_PATH	= ./obj

SRCS	= $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
OBJS	= $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRCS)))))

all:	$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $^ $(MLXFLAGS) -I$(INCLUDES) -L$(LIBFT) -lft -o $@

$(OBJ_PATH)/%.o:	$(SRC_PATH)/%.c* | $(OBJ_PATH)
					$(CC) $(CFLAGS) $(MLXFLAGS2) -c -I$(INCLUDES) $< -o $@

$(OBJ_PATH):
				mkdir -p $(OBJ_PATH)

clean:
			rm -rf $(OBJ_PATH)

fclean:		clean
			rm -f $(NAME) $(CHECKER)

re:			fclean all

.PHONY:		all clean fclean re