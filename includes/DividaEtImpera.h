/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DividaEtImpera.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:41:06 by bama              #+#    #+#             */
/*   Updated: 2025/01/24 18:43:39 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIVIDAETIMPERA_H
#define DIVIDAETIMPERA_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include "generic_opt_handling/opt_handling.h"

# define DIVIDA		"divida"
# define C_DIVIDA	'd'

# define IMPERA		"impera"
# define C_IMPERA	'i'

# define BYTES		"in-bytes"
# define C_BYTES	'b'

# define PARTS		"in-parts"
# define C_PARTS	'p'

typedef struct	s_dei_options
{
	char	divida;
	char	impera;
	char	bytes;
	char	parts;
}	t_dei_options;

typedef struct	s_dei_ff_info
{
	char*			buffer;
	unsigned char	index;
	unsigned long	size;
}	t_dei_ff_info;

typedef struct	s_dei_impera
{
	unsigned long	hash_id;
	unsigned char	total_parts;
	unsigned char*	name_format;
	char**			file_names;
	int				fd;
	int				subfd;
	t_dei_ff_info	ff; // if the file passed in arg is not the first part, it will be stocked in this buffer
}	t_dei_impera;

typedef struct	s_dei
{
	char*			file;
	unsigned int	bytes;
	unsigned long	total_file_size;
	float			parts_calculated;
}	t_dei;

typedef struct	s_dei_header
{
	unsigned char	name[32];	// Nom original du fichier (avec extension)
	unsigned long	hash_id;	// ID de hashage
	unsigned long	file_size;	// Taille du fichier
	unsigned long	total_file_size;	// Taille du fichier apres reunion
	unsigned long	size;		// Taille du header
	unsigned long	index;		// Index de la partie (0/total_parts)
	unsigned char	total_parts;// Nombre de parties au total
}	t_dei_header;

void	divida(int ac, char** av, const t_dei_options* options);
void	impera(int ac, char** av, const t_dei_options* options);

#endif
