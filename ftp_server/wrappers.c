/*
** wrappers.c for  in /home/le-rou_c/docs/PSU_2016_myftp
** 
** Made by Lucien Le Roux
** Login   <le-rou_c@epitech.net>
** 
** Started on  Thu May 11 16:59:41 2017 Lucien Le Roux
** Last update Fri May 19 22:27:50 2017 Lucien Le Roux
*/

#include "server.h"

/*
 * Calls perror then exits
 */
void            xperror(const char *msg)
{
  perror(msg);
  exit(EXIT_FAILURE);
}

/*
 * Closes a filedes and sets it to FD_NONE
 */
void		mclose(int *fd)
{
  if (close(*fd) == -1)
    xperror("close");
  *fd = FD_NONE;
}

/*
 * Closes the server, ensuring that all
 *  sockets are closed
 */
void            close_server(t_ftp *ftp)
{
  if (ftp->ctrl.sock != FD_NONE)
    mclose(&ftp->ctrl.sock);
  if (ftp->ctrl_lsn.sock != FD_NONE)
    mclose(&ftp->ctrl_lsn.sock);
  close_data(ftp);
  printf("[-] Connection from %s closed.\n", inet_ntoa(ftp->ctrl.sa.sin_addr));
}

/*
 * Creates a socket listening on a given port
 *  and returns its file descriptor
 */
void            setup_listener(t_ftp *ftp, int port)
{
  int           opt;

  opt = 1;
  ftp->ctrl_lsn.sa.sin_family = AF_INET;
  ftp->ctrl_lsn.sa.sin_addr.s_addr = htons(INADDR_ANY);
  ftp->ctrl_lsn.sa.sin_port = htons(port);
  if ((ftp->ctrl_lsn.sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    xperror("socket");
  if ((setsockopt(ftp->ctrl_lsn.sock, SOL_SOCKET,
		  SO_REUSEADDR, &opt, sizeof(opt))) == -1)
    xperror("setsockopt");
  if (bind(ftp->ctrl_lsn.sock, (struct sockaddr *)
	   &ftp->ctrl_lsn.sa, sizeof(ftp->ctrl_lsn.sa)) == -1)
    xperror("bind");
  if (listen(ftp->ctrl_lsn.sock, MAX_CLIENTS) == -1)
    xperror("listen");
}

/*
 * Executes the function associated with
 *  the given command
 */
void		exec_cmd(const char *cmd, t_ftp *ftp)
{
  int		i;

  i = 0;
  while (cmd && g_cmds[i].f != NULL)
    {
      if (strcasecmp(cmd, g_cmds[i].command) == 0)
	{
	  if (!g_cmds[i].auth || (g_cmds[i].auth && ftp->logged_in))
	    (*g_cmds[i].f)(strtok(NULL, " "), ftp);
	  else
	    dprintf(ftp->ctrl.sock, "530 User not logged in.\n");
	  break ;
	}
      i++;
    }
  if (cmd == NULL || g_cmds[i].f == NULL)
    dprintf(ftp->ctrl.sock, "500 Unrecognized command\n");
}

