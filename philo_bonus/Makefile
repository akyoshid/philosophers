# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/20 22:45:05 by akyoshid          #+#    #+#              #
#    Updated: 2025/03/13 06:22:30 by akyoshid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		philo_bonus

INC_DIR =	inc/
SRC_DIR =	src/
OBJ_DIR =	obj/

INC = \
			$(INC_DIR)philo_bonus.h \

SRC = \
			$(SRC_DIR)exec_sim/create_os.c \
			$(SRC_DIR)exec_sim/create_philos.c \
			$(SRC_DIR)exec_sim/exec_sim.c \
			$(SRC_DIR)init/init_philo_data.c \
			$(SRC_DIR)init/init_semaphore.c \
			$(SRC_DIR)init/init_sim_data.c \
			$(SRC_DIR)os_routine/start_os_routine.c \
			$(SRC_DIR)philo_routine/start_philo_routine.c \
			$(SRC_DIR)utils/clean_up.c \
			$(SRC_DIR)utils/ft_strncpy.c \
			$(SRC_DIR)utils/get_time.c \
			$(SRC_DIR)utils/philo_atoi.c \
			$(SRC_DIR)utils/print_error.c \
			$(SRC_DIR)main.c
#			$(SRC_DIR)philo_routine/check_action_status.c \
			$(SRC_DIR)philo_routine/check_alive.c \
			$(SRC_DIR)philo_routine/check_eat_count.c \
			$(SRC_DIR)philo_routine/philo_eat.c \
			$(SRC_DIR)philo_routine/philo_sleep.c \
			$(SRC_DIR)philo_routine/philo_think.c \
			$(SRC_DIR)philo_routine/print_log.c \

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
