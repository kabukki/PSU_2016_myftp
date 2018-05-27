/*
** myftp.h for  in /home/le-rou_c/docs/PSU_2016_myftp
** 
** Made by Lucien Le Roux
** Login   <le-rou_c@epitech.net>
** 
** Started on  Tue May  9 13:15:40 2017 Lucien Le Roux
** Last update Fri May 19 22:37:25 2017 Lucien Le Roux
*/

#ifndef MYFTP_H_
# define MYFTP_H_

# include <arpa/inet.h>
# include <netinet/in.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <stdarg.h>
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

/* Server */
# define        MAX_CLIENTS     10
# define	FD_NONE		-1

typedef enum	e_type
  {
    ASCII,
    EBCDIC,
    IMAGE
  }		t_type;

typedef struct		s_endpoint
{
  struct sockaddr_in	sa;
  int			sock;
}			t_endpoint;

typedef struct		s_ftp
{
  t_endpoint		ctrl;
  t_endpoint		ctrl_lsn;
  t_endpoint		data;
  t_endpoint		data_lsn;
  socklen_t		sin_size;
  enum e_type		type;
  char			user[256];
  char			rename_buf[1024];
  bool			logged_in;
}			t_ftp;

/* Commands */
typedef struct	s_cmd
{
  char		*command;
  void		(*f)(char *, t_ftp *);
  bool		auth;
}		t_cmd;

/* Login */
void             cmd_user(char *args, t_ftp *ftp);
void             cmd_pass(char *args, t_ftp *ftp);
void             cmd_acct(char *args, t_ftp *ftp);
void             cmd_cwd(char *args, t_ftp *ftp);
void             cmd_cdup(char *args, t_ftp *ftp);

/* Logout */
void             cmd_quit(char *args, t_ftp *ftp);

/* Transfer */
void             cmd_pasv(char *args, t_ftp *ftp);
void             cmd_port(char *args, t_ftp *ftp);
void             cmd_type(char *args, t_ftp *ftp);

/* Actions */
void             cmd_allo(char *args, t_ftp *ftp);
void             cmd_rest(char *args, t_ftp *ftp);
void             cmd_stor(char *args, t_ftp *ftp);
void             cmd_stou(char *args, t_ftp *ftp);
void             cmd_retr(char *args, t_ftp *ftp);

void             cmd_list(char *args, t_ftp *ftp);
void             cmd_nlst(char *args, t_ftp *ftp);
void             cmd_appe(char *args, t_ftp *ftp);
void             cmd_rnfr(char *args, t_ftp *ftp);
void             cmd_rnto(char *args, t_ftp *ftp);

void             cmd_dele(char *args, t_ftp *ftp);
void             cmd_rmd(char *args, t_ftp *ftp);
void             cmd_mkd(char *args, t_ftp *ftp);
void             cmd_pwd(char *args, t_ftp *ftp);
void             cmd_abor(char *args, t_ftp *ftp);

/* Information */
void             cmd_syst(char *args, t_ftp *ftp);
void             cmd_stat(char *args, t_ftp *ftp);
void             cmd_help(char *args, t_ftp *ftp);

/* Miscellaneous */
void             cmd_site(char *args, t_ftp *ftp);
void             cmd_noop(char *args, t_ftp *ftp);

extern const t_cmd	g_cmds[];

/* Wrappers */
void            xperror(const char *msg);
void            mclose(int *fd);
void		close_server(t_ftp *ftp);
void		setup_listener(t_ftp *ftp, int port);
void		exec_cmd(const char *cmd, t_ftp *ftp);

/* Util */
void		sighandler(int signum);
void		send_msg(int socket, const char *fmt, ...);
void		do_system(const char *cmd, int fd);
int		open_data(t_ftp *ftp);
void		close_data(t_ftp *ftp);

/* Parsing */
struct sockaddr_in      get_addr(char *s);
int                     translate_port(char *s);
int                     translate_address(char *s);

/* GNL */
ssize_t			mgetline(FILE *fp, char **line);

/* Module User */
# define USER_NAME	0
# define USER_PASS	1
# define USER_HOME	2

typedef struct		s_user
{
  char			*name;
  char			*pass;
  char			*home;
}			t_user;

char			*get_user_pass(const char *name);
char			*get_user_home(const char *name);
void			set_user_pass(const char *name, char *pass);
void			set_user_home(const char *name, char *home);
t_user			*get_user_info(const char *name);

extern t_user		g_users[];

#endif /* MYFTP_H_ */
