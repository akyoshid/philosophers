# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/20 22:45:05 by akyoshid          #+#    #+#              #
#    Updated: 2025/02/25 21:48:48 by akyoshid         ###   ########.fr        #
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
			$(SRC_DIR)check_action_status.c \
			$(SRC_DIR)check_alive.c \
			$(SRC_DIR)clean_up_mutex.c \
			$(SRC_DIR)exec_sim.c \
			$(SRC_DIR)get_current_time_ms.c \
			$(SRC_DIR)init_mutex.c \
			$(SRC_DIR)init_sim_data.c \
			$(SRC_DIR)philo_atoi.c \
			$(SRC_DIR)philo_eat.c \
			$(SRC_DIR)print_error.c \
			$(SRC_DIR)print_log.c \
			$(SRC_DIR)start_philo_routine.c \
			$(SRC_DIR)main.c

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
