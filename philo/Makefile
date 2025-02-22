# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/20 22:45:05 by akyoshid          #+#    #+#              #
#    Updated: 2025/02/22 08:24:39 by akyoshid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		philo

INC_DIR =	inc/
SRC_DIR =	src/
OBJ_DIR =	obj/

INC = \
			$(INC_DIR)philo.h \
			$(INC_DIR)ft_printf.h

SRC = \
			$(SRC_DIR)ft_printf/ft_print_char.c \
			$(SRC_DIR)ft_printf/ft_print_dec.c \
			$(SRC_DIR)ft_printf/ft_print_hex.c \
			$(SRC_DIR)ft_printf/ft_printf.c \
			$(SRC_DIR)main.c \
			$(SRC_DIR)philo_atoi.c \
			$(SRC_DIR)print_error.c \
			$(SRC_DIR)init_sim_data.c

OBJ =		$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

CC = 		cc
CFLAGS = 	-Wall -Wextra -Werror
RM = 		rm -f
AR = 		ar rcs

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -I$(INC_DIR) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
