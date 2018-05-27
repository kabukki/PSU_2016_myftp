/*
** parsing.c for  in /home/le-rou_c/docs/PSU_2016_myftp
** 
** Made by Lucien Le Roux
** Login   <le-rou_c@epitech.net>
** 
** Started on  Wed May 17 17:40:58 2017 Lucien Le Roux
** Last update Wed May 17 18:21:36 2017 Lucien Le Roux
*/

#include "server.h"

/*
 * Get address from string
 *  in format (1,2,3,4,5,6)
 */
struct sockaddr_in	get_addr(char *s)
{
  struct sockaddr_in	sin;

  printf("Getting sockaddr from: %s\n", s);
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = translate_address(s);
  sin.sin_port = htons(translate_port(s));
  return (sin);
}

int			translate_port(char *s)
{
  int			p1;
  int			p2;
  int			n;

  n = 0;
  printf("Translating port from: '%s'\n", s);
  while (*s && n < 4)
    {
      while (*s && *s != ',')
	s++;
      s++;
      n++;
    }
  sscanf(s, "%d,%d", &p1, &p2);
  return (p1 * 256 + p2);
}

int			translate_address(char *s)
{
  struct sockaddr_in	sin;
  char			addr[1024];
  char			*p;
  int			n;

  n = 0;
  p = addr;
  printf("Translating address from: '%s'\n", s);
  memcpy(addr, s, strlen(s));
  while (*p && n < 4)
    {
      while (*p && *p != ',')
	p++;
      *p++ = (n == 3 ? 0 : '.');
      n++;
    }
  inet_aton(addr, &sin.sin_addr);
  return (sin.sin_addr.s_addr);
}
