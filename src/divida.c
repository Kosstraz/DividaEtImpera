/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divida.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 04:05:30 by bama              #+#    #+#             */
/*   Updated: 2025/01/24 04:47:32 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DividaEtImpera.h"
#include <string.h>

static int	__file_size(int fd)
{
	struct stat	bufstat;
	fstat(fd, &bufstat);
	return (bufstat.st_size);
}

static unsigned long	hash_id(unsigned char file_name[32])
{
	struct timeval	tv;
	unsigned long	hash;

	gettimeofday(&tv, NULL);
	hash = file_name[0] + file_name[1] + file_name[4] * (2 * 2) - file_name[25];
	hash <<= (file_name[(tv.tv_sec * 1000 + tv.tv_usec / 1000) % 31]);
	hash ^= tv.tv_usec;
	return (hash);
}

static void	set_name(unsigned char name[32], char* filename)
{
	int	i = 0;
	while (filename[i] && i < 31)
	{
		name[i] = filename[i];
		++i;
	}
	while (i < 32)
		name[i++] = '\0';
}

/*static char*	dei_strjoin(char* str1, char* str2)
{
	int	i = 0;
	int	size1 = strlen(str1);
	int	size2 = strlen(str2);
	char*	new_str = malloc((size1 + size2 + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	while (*str1)
		new_str[i++] = *(str1)++;
	while (*str2)
		new_str[i++] = *(str2)++;
	new_str[i] = '\0';
	return (new_str);
}*/

static void	create_files(t_dei_header* header)
{
	unsigned char	i = 0;
	char*			div_name = NULL;

	while (i < header->total_parts)
	{
		div_name = malloc((sizeof(header->name) + 3 + 4 + 1) * sizeof(char));	// 3: for itoa() , 4: for ".dei" , 1: null-terminated
		if (div_name == NULL)
			exit(1);
		sprintf(div_name, "%s%d%s", header->name, i, ".dei");
		int	fd = open(div_name, O_WRONLY | O_CREAT, 0666);

		header->file_size = sizeof(t_dei_header);
		header->parts = i;
		write(fd, header, sizeof(t_dei_header));

		free(div_name);
		close(fd);
		++i;
	}
}

void	divida(int ac, char** av, const t_dei_options* options)
{
	(void)options;
	(void)ac;
	t_dei_header	header;
	t_dei			dee;
	char*			data;
	int				file_size;
	int				fd;

	dee.file = av[0];
	dee.parts_calculated = 3;	// <--
	fd = open(av[0], O_RDONLY);
	if (fd == -1)
		return ;
	file_size = __file_size(fd);
	data = mmap(NULL, file_size, PROT_READ, MAP_SHARED, fd, 0);
	if (data <= (char*)0)
		return ;

	header.size = sizeof(t_dei_header);
	header.total_parts = dee.parts_calculated; //auto - deduction with -in-bytes || -in-parts
	set_name(header.name, av[0]);
	header.hash_id = hash_id(header.name);
	create_files(&header);

	munmap(data, file_size);
	close(fd);
}
