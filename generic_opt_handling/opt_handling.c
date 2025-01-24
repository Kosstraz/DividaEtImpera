/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:57:20 by bama              #+#    #+#             */
/*   Updated: 2025/01/24 04:04:28 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opt_handling.h"
#include <string.h>
#include <stdlib.h>

#define OPTH_ALL_FOUND	-2
#define OPTH_NOT_FOUND	-1

static int	check_word_corresponding(const char* word, char** ioptions, int flag)
{
	int	i = 0;
	if (flag == OPTH_FLAG_ALL)
		if (!strcmp(word, "all"))
			return (OPTH_ALL_FOUND);
	while (ioptions[i])
	{
		if (!strcmp(word, ioptions[i++]))
			return (i - 1);
	}
	return (OPTH_NOT_FOUND);
}

static int	check_byte_corresponding(char byte, char* foptions, int flag)
{
	int	i = 0;
	if (flag == OPTH_FLAG_ALL)
		if (byte == 'a')
			return (OPTH_ALL_FOUND);
	while (foptions[i])
		if (byte == foptions[i++])
			return (i - 1);
	return (OPTH_NOT_FOUND);
}

int	options_handling(int ac, const char** av, char** ioptions, char* foptions, void* buffer, int bufsize, int flag)
{
	if (!av || !ioptions || !foptions || !buffer || ac < 1)
		return (OPTH_NO_ARGS);
	int	i = 0;
	int	opt_count = 0;
	int	all_is_found = 0;

	while (i < ac && av[i])
	{
		int	val;
		if (av[i][0] != '-')
			return (opt_count);
		else if (!all_is_found)
		{
			if (av[i][1] == '-')
			{
				
				val = check_word_corresponding(&av[i][2], ioptions, flag);
				if (val == OPTH_NOT_FOUND)
					return ((-i) - 2);
				else if (val != OPTH_ALL_FOUND)
				{
					*((char*)(buffer + val)) = 1;
					++opt_count;
				}
				else
				{
					++opt_count;
					memset(buffer, 1, bufsize);
					all_is_found = 1;
				}
			}
			else
			{
				int	j = 1;
				while (av[i][j])
				{
					val = check_byte_corresponding(av[i][j++], foptions, flag);
					if (val == OPTH_NOT_FOUND)
						return ((-i) - 2);
					else if (val != OPTH_ALL_FOUND)
					{
						*((char*)(buffer + val)) = 1;
						++opt_count;
					}
					else
					{
						++opt_count;
						memset(buffer, 1, bufsize);
						all_is_found = 1;
					}
				}
			}
		}
		++i;
	}
	return (opt_count);
}
