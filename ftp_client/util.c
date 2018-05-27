/*
** util.c for  in /home/le-rou_c/docs/PSU_2016_myftp
** 
** Made by Lucien Le Roux
** Login   <le-rou_c@epitech.net>
** 
** Started on  Mon May  8 21:34:43 2017 Lucien Le Roux
** Last update Tue May  9 22:04:11 2017 Lucien Le Roux
*/

#include "client.h"

void		xperror(const char *msg)
{
  perror(msg);
  exit(EXIT_FAILURE);
}

void		close_client(t_client *client)
{
  if (close(client->c_control) == -1)
    xperror("close");
  if (client->c_data != FD_NONE)
    if (close(client->c_data) == -1)
      xperror("close");
}

void		prompt(void)
{
  printf("myftp> ");
  fflush(stdout);
}
