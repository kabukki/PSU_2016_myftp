/*
** cmd_misc.c for  in /home/le-rou_c/docs/PSU_2016_myftp
** 
** Made by Lucien Le Roux
** Login   <le-rou_c@epitech.net>
** 
** Started on  Wed May 10 18:10:18 2017 Lucien Le Roux
** Last update Wed May 17 19:46:50 2017 Lucien Le Roux
*/

#include "server.h"

void		cmd_dele(char *args, t_ftp *ftp)
{
  struct stat	st;

  if (!args)
    send_msg(ftp->ctrl.sock, "500 Missing argument.");
  else if (stat(args, &st) != 0)
    send_msg(ftp->ctrl.sock, "550 File %s not found.", args);
  else if (!S_ISREG(st.st_mode))
    send_msg(ftp->ctrl.sock, "550 is not a regular file.", args);
  else if (unlink(args) != 0)
    send_msg(ftp->ctrl.sock, "550 Could not delete file (rights?).");
  else
    send_msg(ftp->ctrl.sock, "250 Successfully deleted file.");
}

void		cmd_rmd(char *args, t_ftp *ftp)
{
  struct stat	st;

  if (!args)
    send_msg(ftp->ctrl.sock, "500 Missing argument.");
  else if (stat(args, &st) != 0)
    send_msg(ftp->ctrl.sock, "550 Directory %s not found.", args);
  else if (!S_ISDIR(st.st_mode))
    send_msg(ftp->ctrl.sock, "550 is not a directory.", args);
  else if (rmdir(args) != 0)
    send_msg(ftp->ctrl.sock, "550 Could not delete directory (not empty?).");
  else
    send_msg(ftp->ctrl.sock, "250 Successfully deleted drectory.");
}

void		cmd_mkd(char *args, t_ftp *ftp)
{
  struct stat	st;
  char		buf[1024];

  if (!args)
    send_msg(ftp->ctrl.sock, "500 Missing argument.");
  else if (stat(args, &st) == 0)
    send_msg(ftp->ctrl.sock, "550 Directory %s already exists.", args);
  else if (mkdir(args, 0755) != 0)
    send_msg(ftp->ctrl.sock, "550 Could not create directory (rights?).");
  else
    {
      realpath(args, buf);
      send_msg(ftp->ctrl.sock, "257 \"%s\" Successfully created dir.", buf);
    }
}

void		cmd_pwd(char *args __attribute__((unused)), t_ftp *ftp)
{
  char		buf[1024];

  getcwd(buf, 1024);
  send_msg(ftp->ctrl.sock, "%d \"%s\"", 257, buf);
}

void		cmd_abor(char *args __attribute__((unused)), t_ftp *ftp)
{
  close_data(ftp);
  send_msg(ftp->ctrl.sock, "226 Data connection has been closed.");
}
