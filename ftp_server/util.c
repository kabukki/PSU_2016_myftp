/*
** util.c for  in /home/le-rou_c/docs/PSU_2016_myftp
** 
** Made by Lucien Le Roux
** Login   <le-rou_c@epitech.net>
** 
** Started on  Mon May  8 21:34:43 2017 Lucien Le Roux
** Last update Fri May 19 22:39:54 2017 Lucien Le Roux
*/

#include "server.h"

void		sighandler(int signum __attribute__((unused)))
{
  exit(EXIT_SUCCESS);
}

void		send_msg(int socket, const char *fmt, ...)
{
  va_list	args;

  va_start(args, fmt);
  vdprintf(socket, fmt, args);
  dprintf(socket, "\r\n");
  va_end(args);
}

/*
 * Executes the specified command
 *  and outputs it to fd.
 */
void		do_system(const char *cmd, int fd)
{
  int		oldfd;

  oldfd = dup(1);
  dup2(fd, 1);
  system(cmd);
  dup2(oldfd, 1);
}

/*
 * Establishes a connection on the data port
 * If PASV mode, accept
 * Else PORT, the server connects to the client
 */
int		open_data(t_ftp *ftp)
{
  if (ftp->data_lsn.sock != FD_NONE)
    {
      if ((ftp->data.sock = accept(ftp->data_lsn.sock, (struct sockaddr *)
                                   &ftp->data.sa, &ftp->sin_size)) == -1)
        return (1);
      if (getpeername(ftp->data.sock, (struct sockaddr *)
                      &ftp->data.sa, &ftp->sin_size) == -1)
        {
          mclose(&ftp->data.sock);
          return (1);
        }
    }
  else
    {
      if ((ftp->data.sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return (1);
      if (connect(ftp->data.sock, (struct sockaddr *)
		  &ftp->data.sa, ftp->sin_size) == -1)
        {
          mclose(&ftp->data.sock);
          return (1);
        }
    }
  return (0);
}

/*
 * Closes the connection on the data port
 *  as well as the listening data port, if any.
 */
void		close_data(t_ftp *ftp)
{
  if (ftp->data_lsn.sock != FD_NONE)
    {
      shutdown(ftp->data_lsn.sock, SHUT_RDWR);
      mclose(&ftp->data_lsn.sock);
      memset(&ftp->data_lsn.sa, 0, sizeof(ftp->data_lsn.sa));
    }
  if (ftp->data.sock != FD_NONE)
    {
      shutdown(ftp->data.sock, SHUT_RDWR);
      mclose(&ftp->data.sock);
      memset(&ftp->data.sa, 0, sizeof(ftp->data.sa));
    }
}
