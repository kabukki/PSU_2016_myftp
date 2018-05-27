/*
** cmd_misc.c for  in /home/le-rou_c/docs/PSU_2016_myftp
** 
** Made by Lucien Le Roux
** Login   <le-rou_c@epitech.net>
** 
** Started on  Wed May 10 18:10:18 2017 Lucien Le Roux
** Last update Fri May 19 22:31:21 2017 Lucien Le Roux
*/

#include "server.h"

void		cmd_user(char *args, t_ftp *ftp)
{
  if (args)
    {
      ftp->logged_in = false;
      strncpy(ftp->user, args, strlen(args));
      send_msg(ftp->ctrl.sock, "331 Username ok, need password.");
    }
  else
    send_msg(ftp->ctrl.sock, "500 Missing argument.");
}

void		cmd_pass(char *args, t_ftp *ftp)
{
  t_user	*info;

  if (!args)
    args = "";
  info = get_user_info(ftp->user);
  if (ftp->logged_in)
    send_msg(ftp->ctrl.sock, "230 Already logged in.");
  else if (info->name && strcmp(info->pass, args) == 0)
    {
      if (chdir(info->home) == -1)
	send_msg(ftp->ctrl.sock, "451 Internal error.");
      else
	{
	  ftp->logged_in = true;
	  send_msg(ftp->ctrl.sock, "230 User logged in, proceed.");
	}
    }
  else
    {
      memset(ftp->user, 0, 256);
      send_msg(ftp->ctrl.sock, "530 Authentication failed.");
    }
}

void		cmd_acct(char *args, t_ftp *ftp)
{
  if (*ftp->user)
    send_msg(ftp->ctrl.sock, "202 User already logged in.");
  else if (args)
    send_msg(ftp->ctrl.sock, "230 User may proceed.");
  else
    send_msg(ftp->ctrl.sock, "530 Authentication failure.");
}

void		cmd_cwd(char *args, t_ftp *ftp)
{
  char          *dir;

  dir = args;
  if (!dir || !*dir)
    send_msg(ftp->ctrl.sock, "301 Missing argument.");
  else if (chdir(dir) == -1)
    send_msg(ftp->ctrl.sock, "550 %s: Directory not found.", dir);
  else
    send_msg(ftp->ctrl.sock, "250 Changed working directory.");
}

void		cmd_cdup(char *args __attribute__((unused)), t_ftp *ftp)
{
  if (chdir("..") == -1)
    send_msg(ftp->ctrl.sock, "550 Could not go up a dir.");
  else
    send_msg(ftp->ctrl.sock, "200 Changed working directory.");
}
