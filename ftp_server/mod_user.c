/*
** mod_user.c for  in /home/le-rou_c/docs/PSU_2016_myftp
** 
** Made by Lucien Le Roux
** Login   <le-rou_c@epitech.net>
** 
** Started on  Mon May 15 11:17:26 2017 Lucien Le Roux
** Last update Fri May 19 21:24:02 2017 Lucien Le Roux
*/

#include "server.h"

/*
 * User module allowing to get/set user information,
 *  but not to add new users (need to recompile first).
 */

t_user		g_users[] = {
  {"Anonymous", "", "/tmp"},
  {NULL, NULL, NULL}
};

char		*get_user_pass(const char *name)
{
  return (get_user_info(name)->home);
}

char		*get_user_home(const char *name)
{
  return (get_user_info(name)->home);
}

void		set_user_pass(const char *name, char *pass)
{
  t_user	*info;

  info = get_user_info(name);
  if (info->name)
    info->pass = pass;
}

void		set_user_home(const char *name, char *home)
{
  t_user	*info;

  info = get_user_info(name);
  if (info->name)
    info->home = home;
}

t_user		*get_user_info(const char *name)
{
  size_t	i;

  i = 0;
  while (g_users[i].name != NULL)
    {
      if (strcmp(name, g_users[i].name) == 0)
	break ;
      i++;
    }
  return (&g_users[i]);
}
