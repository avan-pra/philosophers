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

CC = clang

CFLAGS = 

FLAGS = -pthread

CFLAGS_1 = -Wall -Wextra -Werror -I ./philo_one

CFLAGS_2 = -Wall -Wextra -Werror -I ./philo_two

CFLAGS_3 = -Wall -Wextra -Werror -I ./philo_three

ALL = philo_1 philo_2 philo_3

all: philo_1 philo_2 philo_3

philo_1:	$(OBJS_1)
	$(CC)	-o philo_1 $(FLAGS) $(CFLAGS_1) $(OBJS_1)

philo_2:	$(OBJS_2)
	$(CC)	-o philo_2 $(FLAGS) $(CFLAGS_2) $(OBJS_2)
 
philo_3:	$(OBJS_3)
	$(CC)	-o philo_3 $(FLAGS) $(CFLAGS_3) $(OBJS_3) 

mutex_semaphore: $(addprefix mutex_sema_version/, $(OBJS_1)) $(addprefix mutex_sema_version/, $(OBJS_2)) $(addprefix mutex_sema_version/, $(OBJS_3))
	$(CC)	-o philo_1 $(FLAGS) $(CFLAGS_1) $(addprefix mutex_sema_version/, $(OBJS_1))
	$(CC)	-o philo_2 $(FLAGS) $(CFLAGS_2) $(addprefix mutex_sema_version/, $(OBJS_2))
	$(CC)	-o philo_3 $(FLAGS) $(CFLAGS_3) $(addprefix mutex_sema_version/, $(OBJS_3))

clean:
	rm -f $(OBJS_1) $(OBJS_2) $(OBJS_3) $(addprefix mutex_sema_version/, $(OBJS_1)) $(addprefix mutex_sema_version/, $(OBJS_2)) $(addprefix mutex_sema_version/, $(OBJS_3))

fclean : clean
	rm -f $(ALL)

re: fclean all

.PHONY: all re clean fclean
