/*
** cmd_misc.c for  in /home/le-rou_c/docs/PSU_2016_myftp
** 
** Made by Lucien Le Roux
** Login   <le-rou_c@epitech.net>
** 
** Started on  Wed May 10 18:10:18 2017 Lucien Le Roux
** Last update Wed May 17 19:48:21 2017 Lucien Le Roux
*/

#include "server.h"

void		cmd_quit(char *args __attribute__((unused)), t_ftp *ftp)
{
  send_msg(ftp->ctrl.sock, "221 Goodbye.");
  close_server(ftp);
  exit(EXIT_SUCCESS);
}
