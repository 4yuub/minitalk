INC = mylib.h

SERVER_SRCS = server.c ft_print.c
CLIENT_SRCS = client.c ft_atoi.c ft_print.c

SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf 

all: server client

client:$(CLIENT_OBJS)
	@$(CC) $(CFLAGS) $(CLIENT_OBJS) -o client
	@echo "client created successfully"

server:$(SERVER_OBJS)
	@$(CC) $(CFLAGS) $(SERVER_OBJS) -o server 
	@echo "server created successfully"

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)
	@echo "object files removed successfully"

fclean:clean
	@$(RM) client server
	@echo "client and server removed successfully"
