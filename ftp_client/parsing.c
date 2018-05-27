/*
** parsing.c for  in /home/le-rou_c/docs/PSU_2016_myftp
** 
** Made by Lucien Le Roux
** Login   <le-rou_c@epitech.net>
** 
** Started on  Wed May 10 15:15:13 2017 Lucien Le Roux
** Last update Wed May 10 16:30:28 2017 Lucien Le Roux
*/

#include "client.h"

/*
 * (IP1,IP2,IP3,IP4,P1,P2)
 */
int		parse_addr(char *str)
{
  char		buf[256];
  char		*tmp;
  int		i;

  if (!str)
    return -1;
  i = 0;
  memcpy(buf, str, 255);
  tmp = &buf[1];
  while (i <= 3)
    {
      if (!(tmp = strchr(tmp, ',')))
	return -1;
      *tmp = (i == 3 ? 0 : '.');
      tmp++;
      i++;
    }
  printf("%s\n", buf + 1);
  return (inet_addr(&buf[1]));
}

/*
 * (IP1,IP2,IP3,IP4,P1,P2)
 */
int		parse_port(char *str)
{
  char		buf[256];
  char		*tmp;
  int		p1;
  int		p2;
  int		i;

  i = 0;
  memcpy(buf, str, 255);
  tmp = &buf[1];
  printf("[%s]\n", tmp);
  while (i <= 5)
    {
      printf("[%s]\n", tmp);
      if (!(tmp = strchr(tmp, ',')))
	return -1;
      tmp++;
      if (i == 4)
	p1 = atoi(tmp + 1);
      else if (i == 5)
	p2 = atoi(tmp + 1);
      i++;
    }
  if (p1 <= 0 || p2 <= 0)
    return (-1);
  return (htons(p1 * 256 + p2));
}
