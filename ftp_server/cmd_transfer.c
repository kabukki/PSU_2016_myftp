/*
** cmd_misc.c for  in /home/le-rou_c/docs/PSU_2016_myftp
** 
** Made by Lucien Le Roux
** Login   <le-rou_c@epitech.net>
** 
** Started on  Wed May 10 18:10:18 2017 Lucien Le Roux
** Last update Fri May 19 22:39:18 2017 Lucien Le Roux
*/

#include "server.h"

void			cmd_pasv(char *args __attribute__((unused)), t_ftp *ftp)
{
  struct sockaddr_in	sin_data;
  char			addr[INET_ADDRSTRLEN];
  char			*p;

  if (ftp->data.sock != FD_NONE)
    mclose(&ftp->data.sock);
  if (ftp->data_lsn.sock != FD_NONE)
    mclose(&ftp->data_lsn.sock);
  sin_data.sin_family = AF_INET;
  sin_data.sin_addr.s_addr = ftp->ctrl_lsn.sa.sin_addr.s_addr;
  sin_data.sin_port = htons(0);
  if ((ftp->data_lsn.sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    xperror("socket");
  if (bind(ftp->data_lsn.sock, (struct sockaddr *)
	   &sin_data, ftp->sin_size) == -1)
    xperror("bind");
  if (listen(ftp->data_lsn.sock, MAX_CLIENTS) == -1)
    xperror("listen");
  inet_ntop(ftp->ctrl_lsn.sa.sin_family, &(ftp->ctrl_lsn.sa.sin_addr),
	    addr, INET_ADDRSTRLEN);
  getsockname(ftp->data_lsn.sock, (struct sockaddr *)&sin_data, &ftp->sin_size);
  while ((p = strchr(addr, '.')))
    *p = ',';
  send_msg(ftp->ctrl.sock, "227 Entering passive mode (%s,%d,%d)", addr,
	   ntohs(sin_data.sin_port) / 256, ntohs(sin_data.sin_port) % 256);
}

void			cmd_port(char *args, t_ftp *ftp)
{
  if (ftp->data.sock != FD_NONE)
    mclose(&ftp->data.sock);
  if (!args)
    send_msg(ftp->ctrl.sock, "500 Missing argument.");
  else
    {
      ftp->data.sa = get_addr(args);
      send_msg(ftp->ctrl.sock, "200 Active mode enabled.");
    }
}

void			cmd_type(char *args, t_ftp *ftp)
{
  if (!args)
    {
      send_msg(ftp->ctrl.sock, "500 Missing argument.");
      return ;
    }
  if (strcmp(args, "A") == 0)
    ftp->type = ASCII;
  else if (strcmp(args, "E") == 0)
    ftp->type = EBCDIC;
  else if (strcmp(args, "I") == 0)
    ftp->type = IMAGE;
  else
    {
      send_msg(ftp->ctrl.sock, "501 Unknown type.");
      return ;
    }
  send_msg(ftp->ctrl.sock, "200 Command okay.");
}
