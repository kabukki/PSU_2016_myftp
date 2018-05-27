/*
** gnl.c for  in /home/le-rou_c/docs/PSU_2016_myftp
** 
** Made by Lucien Le Roux
** Login   <le-rou_c@epitech.net>
** 
** Started on  Thu May 18 17:42:20 2017 Lucien Le Roux
** Last update Thu May 18 18:23:48 2017 Lucien Le Roux
*/

#include "server.h"

ssize_t		mgetline(FILE *fp, char **line)
{
  size_t	n;
  size_t	len;
  ssize_t	bytes;

  len = 0;
  if ((bytes = getline(line, &len, fp)) != -1)
    {
      n = strcspn(*line, "\r\n");
      if (n != strlen(*line))
	(*line)[n] = 0;
    }
  return (bytes);
}
