/*
** client.h for  in /home/le-rou_c/docs/PSU_2016_myftp
** 
** Made by Lucien Le Roux
** Login   <le-rou_c@epitech.net>
** 
** Started on  Tue May  9 21:40:14 2017 Lucien Le Roux
** Last update Wed May 10 16:13:46 2017 Lucien Le Roux
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include <arpa/inet.h>
# include <netinet/in.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

/* Client */
# define        FD_NONE         -1

typedef struct  s_client
{
  int           c_control;
  int           c_data;
  bool          open;
}               t_client;

/* Commands */
typedef struct  s_cmd
{
  char          *command;
  int           (*f)(char *, t_client *);
}               t_cmd;

int             cmd_pasv(char *cmd, t_client *client);
int             cmd_quit(char *cmd, t_client *client);
int             cmd_noop(char *cmd, t_client *client);
int             cmd_help(char *cmd, t_client *client);

extern const t_cmd      g_cmds[];

/* Util */
void            xperror(const char *msg);
void            close_client(t_client *client);
void            sighandler(int signum);
void		prompt(void);

/* Parsing */
int		parse_addr(char *str);
int		parse_port(char *str);

#endif /* CLIENT_H_ */
