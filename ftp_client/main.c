/*
** client.c for  in /home/le-rou_c/docs/PSU_2016_myftp
** 
** Made by Lucien Le Roux
** Login   <le-rou_c@epitech.net>
** 
** Started on  Tue May  9 18:09:15 2017 Lucien Le Roux
** Last update Wed May 10 15:08:33 2017 Lucien Le Roux
*/

#include "client.h"

const t_cmd             g_cmds[] = {
  {"quit", &cmd_quit},
  {"passive", &cmd_pasv},
  //  {"port", &cmd_port},
  {"nop", &cmd_noop},
  {"help", &cmd_help},
  {NULL, NULL},
};

static void             usage(const char *bin)
{
  printf("Usage: %s host port\n", bin);
  exit(EXIT_FAILURE);
}

int                     setup_client(int addr, int port)
{
  struct sockaddr_in    sin;
  int                   client;

  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = addr;
  sin.sin_port = htons(port);
  if ((client = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    xperror("socket");
  if (connect(client, (struct sockaddr *)&sin, sizeof(sin)) == -1)
    xperror("bind");
  return (client);
}

int		process_input(char *input, t_client *client)
{
  int           i;

  i = 0;
  while (g_cmds[i].f != NULL)
    {
      if (strcmp(input, g_cmds[i].command) == 0)
	return ((*g_cmds[i].f)(input, client));
      i++;
    }
  if (g_cmds[i].f == NULL)
    printf("Unknown command\n");
  return (1);
}

void		my_ftp_client(t_client *client)
{
  char		buf[256];

  prompt();
  memset(buf, 0, 255);
  while (client->open && read(0, buf, 255) > 0)
    {
      buf[strcspn(buf, "\r\n")] = 0;
      if (strlen(buf) > 0 && process_input(buf, client) == 0)
	{
	  read(client->c_control, buf, 255);
	  printf("%s", buf);
	}
      memset(buf, 0, 255);
      prompt();
    }
  printf("Disconnected\n");
}

int             main(int ac, char **av)
{
  t_client	client;

  if (ac != 3)
    usage(av[0]);
  client.c_control = setup_client(inet_addr(av[1]), atoi(av[2]));
  client.c_data = FD_NONE;
  client.open = true;
  puts("--- Welcome to myFTP client ---");
  my_ftp_client(&client);
  close_client(&client);
  return (EXIT_SUCCESS);
}
