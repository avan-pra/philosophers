# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 11:50:27 by selgrabl          #+#    #+#              #
#    Updated: 2019/11/13 18:42:45 by selgrabl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

 SRCS1 = 	./philo_one/init_philo.c		\
		./philo_one/philo_action.c		\
		./philo_one/philo_live.c		\
		./philo_one/philo_monitoring.c		\
		./philo_one/tools.c			\
		./philo_one/philo_one.c			\
		./philo_one/philo_state.c		\
		./philo_one/philo_utils.c

 SRCS2 = 	./philo_two/init_philo.c		\
		./philo_two/philo_action.c		\
		./philo_two/philo_live.c		\
		./philo_two/philo_monitoring.c		\
		./philo_two/tools.c			\
		./philo_two/philo_two.c			\
		./philo_two/philo_state.c		\
		./philo_two/philo_utils.c

 SRCS3 = 	./philo_three/init_philo.c		\
		./philo_three/philo_action.c		\
		./philo_three/philo_live.c		\
		./philo_three/philo_monitoring.c	\
		./philo_three/tools.c			\
		./philo_three/philo_three.c		\
		./philo_three/philo_state.c		\
		./philo_three/philo_utils.c

OBJS_1 = $(SRCS1:.c=.o)

OBJS_2 = $(SRCS2:.c=.o)

OBJS_3 = $(SRCS3:.c=.o)

CC = gcc

FLAGS = -pthread

CFLAGS_1 = -Wall -Wextra -Werror -I ./philo_one

CFLAGS_2 = -Wall -Wextra -Werror -I ./philo_two

CFLAGS_3 = -Wall -Wextra -Werror -I ./philo_three

all: $(NAME)

philo_1:	$(OBJS_1)
	$(CC)	-o philo_1 $(FLAGS) $(CFLAGS_1) $(OBJS_1)

philo_2:	$(OBJS_2)
	$(CC)	-o philo_2 $(FLAGS) $(CFLAGS_2) $(OBJS_2)
 
philo_3:	$(OBJS_3)
	$(CC)	-o philo_3 $(FLAGS) $(CFLAGS_3) $(OBJS_3) 


clean:
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
