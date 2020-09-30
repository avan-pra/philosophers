# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 11:50:27 by selgrabl          #+#    #+#              #
#    Updated: 2020/05/29 16:49:55 by raimbaul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

 SRCS1 = 	./srcs/philo_one/init_philo.c		\
		./srcs/philo_one/philo_action.c		\
		./srcs/philo_one/philo_live.c		\
		./srcs/philo_one/philo_monitoring.c		\
		./srcs/philo_one/tools.c			\
		./srcs/philo_one/philo_one.c			\
		./srcs/philo_one/philo_state.c		\
		./srcs/philo_one/philo_utils.c

 SRCS2 = 	./srcs/philo_two/init_philo.c		\
		./srcs/philo_two/philo_action.c		\
		./srcs/philo_two/philo_live.c		\
		./srcs/philo_two/philo_monitoring.c		\
		./srcs/philo_two/tools.c			\
		./srcs/philo_two/philo_two.c			\
		./srcs/philo_two/philo_state.c		\
		./srcs/philo_two/philo_utils.c

 SRCS3 = 	./srcs/philo_three/init_philo.c		\
		./srcs/philo_three/philo_action.c		\
		./srcs/philo_three/philo_live.c		\
		./srcs/philo_three/philo_monitoring.c	\
		./srcs/philo_three/tools.c			\
		./srcs/philo_three/philo_three.c		\
		./srcs/philo_three/philo_state.c		\
		./srcs/philo_three/philo_utils.c

OBJS_1 = $(SRCS1:.c=.o)

OBJS_2 = $(SRCS2:.c=.o)

OBJS_3 = $(SRCS3:.c=.o)

CC = clang

FLAGS = -pthread #-fsanitize=address -g3

CFLAGS_1 = -Wall -Wextra -Werror -I ./philo_one

CFLAGS_2 = -Wall -Wextra -Werror -I ./philo_two

CFLAGS_3 = -Wall -Wextra -Werror -I ./philo_three

ALL = philo_one philo_two philo_three

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3 

all: philo_1 philo_2 philo_3

philo_1:	$(OBJS_1)
	$(CC)	-o philo_one $(FLAGS) $(CFLAGS_1) $(OBJS_1)

philo_2:	$(OBJS_2)
	$(CC)	-o philo_two $(FLAGS) $(CFLAGS_2) $(OBJS_2)
 
philo_3:	$(OBJS_3)
	$(CC)	-o philo_three $(FLAGS) $(CFLAGS_3) $(OBJS_3)

clean:
	rm -f $(OBJS_1) $(OBJS_2) $(OBJS_3)

fclean : clean
	rm -f $(ALL)

re: fclean all

.PHONY: all re clean fclean
