/*
** commands.c for  in /home/le-rou_c/docs/PSU_2016_myftp
** 
** Made by Lucien Le Roux
** Login   <le-rou_c@epitech.net>
** 
** Started on  Tue May  9 21:53:39 2017 Lucien Le Roux
** Last update Wed May 10 16:26:11 2017 Lucien Le Roux
*/

#include "client.h"

int			cmd_pasv(char *cmd, t_client *client)
{
  struct sockaddr_in    sin;
  char			buf[256];

  dprintf(client->c_control, "PASV\n");
  read(client->c_control, buf, 255);
  printf("Deduced ip = %d, port = 0\n",
	 parse_addr(strchr(buf, '(')));//, parse_port(strchr(buf, '(')));
  return 0;
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = parse_addr(buf);
  sin.sin_port = parse_port(buf);
  if ((client->c_data = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    xperror("socket");
  if (connect(client->c_data, (struct sockaddr *)&sin, sizeof(sin)) == -1)
    xperror("bind");
  return (0);
}

int             cmd_quit(char *cmd, t_client *client)
{
  dprintf(client->c_control, "QUIT\n");
  client->open = false;
  return (0);
}

int             cmd_noop(char *cmd, t_client *client)
{
  dprintf(client->c_control, "NOOP\n");
  return (0);
}

int		cmd_help(char *cmd, t_client *client)
{
  char		*comma;
  int		i;

  i = 0;
  comma = "";
  while (g_cmds[i].command != NULL)
    {
      printf("%s%s", comma, g_cmds[i].command);
      comma = ", ";
      i++;
    }
  printf("\n");
  return (1);
}
