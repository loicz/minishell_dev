/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihzhang <yihzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:04:05 by yihzhang          #+#    #+#             */
/*   Updated: 2026/03/25 18:20:45 by yihzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//Compares up to n characters of two strings, returning 0 if they are an exact match and -1 if they differ or if either string is NULL.
int	ft_strncmp(char *line, char *str, int n)
{
	int	i;

	if (!line || !str)
		return (-1);
	i = 0;
	while (line[i] && (i < n) && line[i] == str[i])
		i++;
	if (i == n)
		return (0);
	return (-1);
}

//Calculates and return the number of characters in a string.returns 0 if the provided pointer is NULL.
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

//Allocates fresh memory using malloc and returns an exact duplicate of the given string.
char	*ft_strdup(char *str)
{
	char	*dup;
	int		i;

	if (!str)
		return (NULL);
	dup = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

//Allocates fresh memory and duplicates up to n characters from a string, safely handling the cut if the original string is shorter than n
char	*ft_strndup(char *str, int n)
{
	char	*dup;
	int		i;
	int		len;
	int		dup_size;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (n > len)
		dup_size = len;
	else
		dup_size = n;
	dup = malloc(sizeof(char) * (dup_size + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < dup_size)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
