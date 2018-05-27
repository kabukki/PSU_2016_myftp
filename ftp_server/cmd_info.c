/*
** cmd_misc.c for  in /home/le-rou_c/docs/PSU_2016_myftp
** 
** Made by Lucien Le Roux
** Login   <le-rou_c@epitech.net>
** 
** Started on  Wed May 10 18:10:18 2017 Lucien Le Roux
** Last update Fri May 19 22:49:04 2017 Lucien Le Roux
*/

#include "server.h"

void		cmd_syst(char *args __attribute__((unused)), t_ftp *ftp)
{
  send_msg(ftp->ctrl.sock, "215 UNIX Type: L8");
}

void		cmd_stat(char *args, t_ftp *ftp)
{
  char		buf[1024];

  send_msg(ftp->ctrl.sock, "213-Status follows:");
  if (!args)
    {
      send_msg(ftp->ctrl.sock, " Server address: %s:%d",
	       inet_ntoa(ftp->ctrl_lsn.sa.sin_addr),
	       htons(ftp->ctrl_lsn.sa.sin_port));
      send_msg(ftp->ctrl.sock, " Client address: %s:%d",
	       inet_ntoa(ftp->ctrl.sa.sin_addr), htons(ftp->ctrl.sa.sin_port));
      send_msg(ftp->ctrl.sock, " Logged in as: %s", "none");
      send_msg(ftp->ctrl.sock, " Type: %s", ftp->type == ASCII ? "ASCII" :
	       ftp->type == EBCDIC ? "EBCDIC" : "IMAGE");
    }
  else
    {
      strcpy(buf, "ls -la -- ");
      while (args)
	{
	  strncat(buf, args, strlen(args));
	  args = strtok(NULL, " ");
	}
      do_system(buf, ftp->ctrl.sock);
    }
  send_msg(ftp->ctrl.sock, "213 End of status.");
}

void		cmd_help(char *args __attribute__((unused)), t_ftp *ftp)
{
  int		i;

  i = 0;
  send_msg(ftp->ctrl.sock, "214-The following commands are supported:");
  while (g_cmds[i].command)
    {
      if (i > 0 && i % 5 == 0)
	dprintf(ftp->ctrl.sock, "\r\n");
      dprintf(ftp->ctrl.sock, " %s", g_cmds[i].command);
      i++;
    }
  dprintf(ftp->ctrl.sock, "\r\n");
  send_msg(ftp->ctrl.sock, "214 End of help.");
}
