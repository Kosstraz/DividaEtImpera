/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divida.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 04:05:30 by bama              #+#    #+#             */
/*   Updated: 2025/01/24 22:12:51 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DividaEtImpera.h"
#include <string.h>
#include <math.h>

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

static void	create_files(char* data, const t_dei* dei, t_dei_header* header, const t_dei_options* options)
{
	(void)options;
	unsigned int	bytes_writted = 0;
	unsigned char	i = 0;
	char*			div_name = NULL;

	while (i < header->total_parts)
	{
		div_name = malloc((sizeof(header->name) + 3 + 4 + 1) * sizeof(char));	// 3: for itoa() , 4: for ".dei" , 1: null-terminated
		if (div_name == NULL)
			exit(1);
		sprintf(div_name, "%s%d%s", header->name, i, ".dei");
		int	fd = open(div_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);

		header->index = i;
		if (i == (int)dei->parts_calculated - 1)
			header->file_size = (dei->total_file_size - ((dei->parts_calculated - 1) * (dei->bytes - sizeof(t_dei_header))));
		else
		{
			header->file_size = (dei->bytes);
			if (header->file_size > sizeof(t_dei_header))
				header->file_size -= sizeof(t_dei_header);
			else
				header->file_size = sizeof(t_dei_header) - header->file_size;
		}
		printf("Creating\t%s (%ld bytes)\n", div_name, header->file_size + sizeof(t_dei_header));

		write(fd, header, sizeof(t_dei_header));
		write(fd, &data[bytes_writted], header->file_size);
		bytes_writted += header->file_size;

		free(div_name);
		close(fd);
		++i;
	}
}

void	divida(int ac, char** av, const t_dei_options* options)
{
	(void)ac;
	t_dei_header	header;
	t_dei			dei;
	char*			data;
	int				file_size;
	int				fd;

	if (ac < 1)
	{
		printf("ac < 1\n");
		return ;
	}
	dei.file = av[1];
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		printf("fd %s\n", av[1]);
		return ;
	}
	file_size = __file_size(fd);
	data = mmap(NULL, file_size, PROT_READ, MAP_SHARED, fd, 0);
	if (data <= (char*)0)
	{
		printf("mmap\n");
		return ;
	}

	dei.total_file_size = file_size;
	if (options->parts)
	{
		dei.parts_calculated = atoi(av[0]);
		if (dei.parts_calculated <= 1 || dei.parts_calculated >= 255)
		{
			printf("Too much (or inferior/equal to 1) parts calculated, please increase bytes specified\n");
			munmap(data, file_size);
			close(fd);
			return ;
		}
		dei.bytes = (int)roundf((float)((float)dei.total_file_size / (float)dei.parts_calculated));
	}
	else
	{
		dei.bytes = atoi(av[0]);
		if (dei.bytes <= sizeof(t_dei_header))
		{
			printf("bytes must be greater than %ld bytes (and lower than UCHAR_MAX\n", sizeof(t_dei_header));
			munmap(data, file_size);
			close(fd);
			return ;
		}
		dei.parts_calculated = (float)file_size / ((float)dei.bytes - (float)sizeof(t_dei_header));
		if ((float)((float)dei.parts_calculated - (int)dei.parts_calculated) > 0.0f)
			dei.parts_calculated = (int)dei.parts_calculated + 1;
		if (dei.parts_calculated <= 0 || dei.parts_calculated >= 255)
		{
			printf("Too much parts calculated, please increase bytes specified\n");
			munmap(data, file_size);
			close(fd);
			return ;
		}
	}
	header.size = sizeof(t_dei_header);
	header.total_parts = dei.parts_calculated; //auto - deduction with -in-bytes || -in-parts
	header.total_file_size = dei.total_file_size;
	printf("Number of parts to be created: %hhu (total: %ld bytes)\n", header.total_parts, header.total_file_size);
	set_name(header.name, av[1]);
	header.hash_id = hash_id(header.name);
	create_files(data, &dei, &header, options);

	munmap(data, file_size);
	close(fd);
}
