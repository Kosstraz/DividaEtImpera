/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 04:05:30 by bama              #+#    #+#             */
/*   Updated: 2025/01/24 18:44:26 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DividaEtImpera.h"
#include <string.h>

static void	unlink_all(t_dei_impera* impera)
{
	int	i = 0;
	while (i < impera->total_parts)
		unlink(impera->file_names[i++]);
}

static void	create_parent_file(unsigned char parent_file_name[32], t_dei_impera* impera)
{
	impera->fd = open((char*)parent_file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (impera->fd == -1)
	{
		printf("Cant create parent file\n");
		exit(1);
	}
	else
		printf("Parent file created\n");
}

static void	mmap_file(char* file, t_dei_impera* impera, int first)
{
	t_dei_header*	header;

	impera->subfd = open(file, O_RDONLY);
	if (impera->subfd == -1)
	{
		printf("Cant open\n");
		exit(1);
	}
	header = (t_dei_header*)mmap(NULL, sizeof(t_dei_header), PROT_READ, MAP_SHARED, impera->subfd, 0);
	if (header <= (t_dei_header*)0)
	{
		write(2, "mmap failed\n", strlen("mmap failed\n"));
		exit(1);
	}
	char*	data = mmap(NULL, header->file_size + sizeof(t_dei_header), PROT_READ, MAP_SHARED, impera->subfd, 0);
	char*	data_tmp = data;
	data += sizeof(t_dei_header);
	if (data <= (char*)0)
	{
		write(2, "mmap failed\n", strlen("mmap failed\n"));
		exit(1);
	}
	if (first)
	{
		impera->name_format = (unsigned char*)strdup((char*)header->name);
		impera->total_parts = header->total_parts;
		impera->hash_id = header->hash_id;
		create_parent_file(header->name, impera);
		impera->ff.buffer = malloc((header->file_size + 1) * sizeof(char));
		memcpy(impera->ff.buffer, data, header->file_size);
		impera->ff.buffer[header->file_size] = '\0';
		impera->ff.index = header->index;
		impera->ff.size = header->file_size;
	}
	else
		write(impera->fd, data, header->file_size);
	munmap(data_tmp, header->file_size);
	munmap(header, sizeof(t_dei_header));
	close(impera->subfd);
}

void	impera(int ac, char** av, const t_dei_options* options)
{
	(void)options;
	if (ac > 1)
	{
		printf("Please put just one file\n");
		exit(ac);
	}
	t_dei_impera	impera;
	char*			fname = av[0];
	int				i = 0;

	mmap_file(av[0], &impera, 1);
	while (i < impera.total_parts)
	{
		if (impera.ff.buffer && impera.ff.index == i)
			write(impera.fd, impera.ff.buffer, impera.ff.size);
		else
		{
			fname = malloc(32 * sizeof(char));
			fname[sprintf(fname, "%s%d%s", impera.name_format, i, ".dei")] = '\0';
			printf("extract\t%s\n", fname);
			mmap_file(fname, &impera, 0);
			free(fname);
		}
		++i;
	}
	close(impera.fd);
	//unlink_all(&impera);
}
