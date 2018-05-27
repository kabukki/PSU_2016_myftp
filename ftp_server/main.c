/*
** main.c for  in /home/le-rou_c/docs/PSU_2016_myftp
** 
** Made by Lucien Le Roux
** Login   <le-rou_c@epitech.net>
** 
** Started on  Mon May  8 21:26:08 2017 Lucien Le Roux
** Last update Fri May 19 22:47:24 2017 Lucien Le Roux
*/

#include "server.h"

const t_cmd		g_cmds[] = {
  {"ABOR", &cmd_abor, true}, {"ACCT", &cmd_acct, true},
  {"ALLO", &cmd_allo, true}, {"APPE", &cmd_appe, true},
  {"CWD", &cmd_cwd, true}, {"CDUP", &cmd_cdup, true},
  {"DELE", &cmd_dele, true}, {"HELP", &cmd_help, false},
  {"LIST", &cmd_list, true}, {"NLST", &cmd_nlst, true},
  {"NOOP", &cmd_noop, true}, {"MKD", &cmd_mkd, true},
  {"PASS", &cmd_pass, false}, {"PASV", &cmd_pasv, true},
  {"PORT", &cmd_port, true}, {"PWD", &cmd_pwd, true},
  {"QUIT", &cmd_quit, false}, {"RETR", &cmd_retr, true},
  {"RMD", &cmd_rmd, true}, {"RNFR", &cmd_rnfr, true},
  {"RNTO", &cmd_rnto, true}, {"STAT", &cmd_stat, true},
  {"SITE", &cmd_site, true}, {"STOR", &cmd_stor, true},
  {"SYST", &cmd_syst, true}, {"TYPE", &cmd_type, true},
  {"USER", &cmd_user, false},
  {NULL, NULL, false}
};

static void		usage(const char *bin)
{
  printf("Usage: %s port path\n", bin);
  exit(EXIT_FAILURE);
}

void			control(t_ftp *ftp)
{
  FILE			*fp;
  char			*buf;
  int			fd;

  buf = NULL;
  if ((fd = dup(ftp->ctrl.sock)) == -1)
    xperror("dup");
  if ((fp = fdopen(fd, "r")) == NULL)
    xperror("fdopen");
  while (mgetline(fp, &buf) > 0)
    {
      printf("%s: [%s]\n", inet_ntoa(ftp->ctrl.sa.sin_addr), buf);
      exec_cmd(strtok(buf, " "), ftp);
      free(buf);
    }
  free(buf);
  fclose(fp);
}

int			my_ftp(t_ftp *ftp)
{
  socklen_t		sin_size;

  sin_size = sizeof(ftp->ctrl.sa);
  while (1)
    {
      if ((ftp->ctrl.sock = accept(ftp->ctrl_lsn.sock, (struct sockaddr *)
				   &ftp->ctrl.sa, &sin_size)) == -1)
	xperror("accept");
      if (fork() == 0)
	{
	  printf("[+] New connection from %s:%d\n",
		 inet_ntoa(ftp->ctrl.sa.sin_addr),
		 ntohs(ftp->ctrl.sa.sin_port));
	  getsockname(ftp->ctrl.sock, (struct sockaddr *)
		      &ftp->ctrl_lsn.sa, &sin_size);
	  send_msg(ftp->ctrl.sock, "220 Connection established");
	  control(ftp);
	  close_server(ftp);
	  exit(EXIT_SUCCESS);
	}
      mclose(&ftp->ctrl.sock);
    }
}

int		main(int ac, char **av)
{
  t_ftp		ftp;

  if (ac != 3)
    usage(av[0]);
  if (access(av[2], F_OK) == -1)
    xperror("access");
  set_user_home("Anonymous", av[2]);
  printf("--- myFTP Server, RFC959-compliant ---\n");
  ftp.ctrl.sock = FD_NONE;
  setup_listener(&ftp, atoi(av[1]));
  ftp.data.sock = FD_NONE;
  ftp.data_lsn.sock = FD_NONE;
  ftp.sin_size = sizeof(struct sockaddr_in);
  ftp.type = ASCII;
  memset(ftp.user, 0, 256);
  memset(ftp.rename_buf, 0, 1024);
  ftp.logged_in = false;
  signal(SIGINT, sighandler);
  my_ftp(&ftp);
  close_server(&ftp);
  return (EXIT_SUCCESS);
}
