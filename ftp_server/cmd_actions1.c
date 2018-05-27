/*
** cmd_misc.c for  in /home/le-rou_c/docs/PSU_2016_myftp
** 
** Made by Lucien Le Roux
** Login   <le-rou_c@epitech.net>
** 
** Started on  Wed May 10 18:10:18 2017 Lucien Le Roux
** Last update Thu May 18 18:50:27 2017 Lucien Le Roux
*/

#include "server.h"

void		cmd_allo(char *args __attribute__((unused)), t_ftp *ftp)
{
  send_msg(ftp->ctrl.sock, "202 Obsolete command, ignored.");
}

void		cmd_rest(char *args, t_ftp *ftp)
{
  (void)args;
  (void)ftp;
}

void		cmd_stor(char *args, t_ftp *ftp)
{
  char		buf[1024];
  FILE		*fp;
  int		n;

  if ((fp = fopen(args, "wb")) == NULL)
    send_msg(ftp->ctrl.sock, "451 Could not create file.");
  else
    {
      if (open_data(ftp) == 0)
	{
	  send_msg(ftp->ctrl.sock, "150 Starting file transfer.");
	  while ((n = read(ftp->data.sock, buf, 1024)) > 0)
	    fwrite(buf, sizeof(char), n, fp);
	  if (n < 0)
	    send_msg(ftp->ctrl.sock, "426 Data connection was dropped.");
	  else
	    send_msg(ftp->ctrl.sock, "226 Transfer complete.");
	  close_data(ftp);
	}
      else
	send_msg(ftp->ctrl.sock, "425 Data connection cannot be established.");
      fclose(fp);
    }
}

void		cmd_stou(char *args, t_ftp *ftp)
{
  (void)args;
  (void)ftp;
}

void		cmd_retr(char *args, t_ftp *ftp)
{
  char		buf[1024];
  FILE		*fp;
  size_t	n;

  if ((fp = fopen(args, "rb")) == NULL)
    send_msg(ftp->ctrl.sock, "451 Could not open file.");
  else
    {
      if (open_data(ftp) == 0)
	{
	  send_msg(ftp->ctrl.sock, "150 Starting file transfer.");
	  while (!feof(fp))
	    {
	      n = fread(buf, sizeof(char), 1024, fp);
	      write(ftp->data.sock, buf, n);
	    }
	  send_msg(ftp->ctrl.sock, "226 Transfer complete.");
	  close_data(ftp);
	}
      else
	send_msg(ftp->ctrl.sock, "425 Data connection cannot be established.");
      fclose(fp);
    }
}
