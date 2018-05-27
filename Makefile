##
## Makefile for  in /home/le-rou_c/docs/PSU_2016_philo
## 
## Made by Lucien Le Roux
## Login   <le-rou_c@epitech.net>
## 
## Started on  Wed Mar  8 18:23:30 2017 Lucien Le Roux
## Last update Thu May 18 18:03:08 2017 Lucien Le Roux
##

SERVER	=	server
CLIENT	=	client

S_SRC	=	ftp_server/main.c		\
		ftp_server/cmd_login.c		\
		ftp_server/cmd_logout.c		\
		ftp_server/cmd_transfer.c	\
		ftp_server/cmd_actions1.c	\
		ftp_server/cmd_actions2.c	\
		ftp_server/cmd_actions3.c	\
		ftp_server/cmd_info.c		\
		ftp_server/cmd_misc.c		\
		ftp_server/wrappers.c		\
		ftp_server/util.c		\
		ftp_server/parsing.c		\
		ftp_server/gnl.c		\
		ftp_server/mod_user.c
S_OBJ	=	$(S_SRC:.c=.o)

C_SRC	=	ftp_client/main.c	\
		ftp_client/commands.c	\
		ftp_client/parsing.c	\
		ftp_client/util.c
C_OBJ	=	$(C_SRC:.c=.o)

INC	=	-I ./include
LIB	=	-L .

LDFLAGS	=	-lm -lelf
CFLAGS	=	-W -Wextra -Wall -g

CC	=	gcc $(INC) $(LIB) $(LDFLAGS) $(CFLAGS)
RM	=	rm -f

all:	$(SERVER)

$(SERVER)	:	$(S_OBJ)
	$(CC) $^ -o $@
$(CLIENT)	:	$(C_OBJ)
	$(CC) $^ -o $@
%.o :	%.c
	$(CC) -c $< -o $@

clean:
	$(RM) $(S_OBJ)
	$(RM) $(C_OBJ)
fclean:	clean
	$(RM) $(SERVER)
	$(RM) $(CLIENT)
re:	fclean all
