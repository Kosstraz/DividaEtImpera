/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DividaEtImpera.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:41:06 by bama              #+#    #+#             */
/*   Updated: 2025/01/24 04:43:19 by bama             ###   ########.fr       */
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

typedef struct	s_dei
{
	char*			file;
	unsigned int	bytes;
	unsigned int	parts_calculated;
}	t_dei;

typedef struct	s_dei_header
{
	unsigned char	name[32];	// Nom original du fichier (avec extension)
	unsigned long	hash_id;	// ID de hashage
	unsigned long	file_size;	// Taille du fichier
	unsigned long	size;		// Taille du header
	unsigned long	parts;		// Numéro de la partie (0/total_parts)
	unsigned char	total_parts;// Nombre de parties au total
}	t_dei_header;

void	divida(int ac, char** av, const t_dei_options* options);
void	impera(int ac, char** av, const t_dei_options* options);

#endif
