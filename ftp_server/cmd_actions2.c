/*
** cmd_misc.c for  in /home/le-rou_c/docs/PSU_2016_myftp
** 
** Made by Lucien Le Roux
** Login   <le-rou_c@epitech.net>
** 
** Started on  Wed May 10 18:10:18 2017 Lucien Le Roux
** Last update Fri May 19 22:19:36 2017 Lucien Le Roux
*/

#include "server.h"

void		cmd_list(char *args, t_ftp *ftp)
{
  char		buf[1024];

  if (open_data(ftp) != 0)
    {
      send_msg(ftp->ctrl.sock, "425 Data connection cannot be established");
      return ;
    }
  send_msg(ftp->ctrl.sock, "150 Here comes the directory listing.");
  strcpy(buf, "ls -la -- ");
  while (args)
    {
      strncat(buf, args, strlen(args));
      args = strtok(NULL, " ");
    }
  do_system(buf, ftp->data.sock);
  send_msg(ftp->ctrl.sock, "226 Directory sent.");
  close_data(ftp);
}

void		cmd_nlst(char *args, t_ftp *ftp)
{
  char		buf[1024];

  if (open_data(ftp) != 0)
    {
      send_msg(ftp->ctrl.sock, "425 Data connection cannot be established");
      return ;
    }
  send_msg(ftp->ctrl.sock, "150 Here comes the directory listing.");
  strcpy(buf, "ls -1a -- ");
  while (args)
    {
      strncat(buf, args, strlen(args));
      args = strtok(NULL, " ");
    }
  do_system(buf, ftp->data.sock);
  send_msg(ftp->ctrl.sock, "226 Directory sent.");
  close_data(ftp);
}

void		cmd_appe(char *args, t_ftp *ftp)
{
  char          buf[1024];
  FILE          *fp;
  int           n;

  if ((fp = fopen(args, "ab")) == NULL)
    send_msg(ftp->ctrl.sock, "451 Could not open/create file.");
  else if (open_data(ftp) == 0)
    {
      send_msg(ftp->ctrl.sock, "150 Starting file transfer.");
      while ((n = read(ftp->data.sock, buf, 1024)) > 0)
	fwrite(buf, sizeof(char), n, fp);
      if (n < 0)
	send_msg(ftp->ctrl.sock, "426 Data connection was dropped.");
      else
	{
	  send_msg(ftp->ctrl.sock, "226 Transfer complete.");
	  printf("%s appended to %s\n", inet_ntoa(ftp->ctrl.sa.sin_addr), args);
	}
      close_data(ftp);
    }
  else
    {
      send_msg(ftp->ctrl.sock, "425 Data connection cannot be established.");
      fclose(fp);
    }
}

void		cmd_rnfr(char *args, t_ftp *ftp)
{
  if (!args)
    send_msg(ftp->ctrl.sock, "500 Missing argument.");
  else
    {
      if (access(args, F_OK) != -1)
	{
	  strcpy(ftp->rename_buf, args);
	  send_msg(ftp->ctrl.sock, "350 Awaiting new file name.");
	}
      else
	send_msg(ftp->ctrl.sock, "550 File %s not found.", args);
    }
}

void		cmd_rnto(char *args, t_ftp *ftp)
{
  if (!*ftp->rename_buf)
    send_msg(ftp->ctrl.sock, "503 Please send a RNFR before RNTO.");
  else
    {
      if (rename(ftp->rename_buf, args) != 0)
	send_msg(ftp->ctrl.sock, "550 Could not rename file.");
      memset(ftp->rename_buf, 0, 1024);
      send_msg(ftp->ctrl.sock, "250 Successfully renamed file.");
    }
}
