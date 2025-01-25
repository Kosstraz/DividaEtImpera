/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:43:08 by bama              #+#    #+#             */
/*   Updated: 2025/01/24 22:52:26 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "DividaEtImpera.h"

void	error_msg(const char* msg, ...)
{
	va_list va;
	va_start(va, msg);
	printf(msg, va);
	exit(0);
}

int	main(int ac, const char** av)
{
	t_dei_options	options = {0};
	int				option_count;
	option_count = options_handling(--ac, ++av, (char*[]){DIVIDA, IMPERA, BYTES, PARTS, NULL}, (char[]){C_DIVIDA, C_IMPERA, C_BYTES, C_PARTS, '\0'}, &options, sizeof(t_dei_options), OPTH_FLAG_ALL);
	//printf("options count %d\n", option_count);
	if (option_count < 0)
		error_msg("Nombre d'options insuffisant\n");
	else if ((options.bytes && options.parts))
		error_msg("Impossible de diviser par partie et par octets a la fois\n");
	else if (!options.bytes && !options.parts && !options.impera)
		error_msg("Impossible de diviser sans l'option -p (--in-parts) ou -b (--in-bytes)\n");
	else if (options.divida && options.impera)
		error_msg("Impossible de diviser et de reunir en meme temps\n");
	else if (options.impera && (options.bytes || options.parts))
		error_msg("La reunion doit se faire sans les options --in-bytes et --in-parts\n");
	else if (((options.parts || options.bytes) && ac - option_count <= 1) || ac - option_count <= 0)
		error_msg("Nombre d'arguments incorrecte, nom de fichier attendu (ou parametre d'options)\n");
	if (options.divida)
		divida(ac - option_count, (char**)(av + option_count), &options);
	else if (options.impera)
		impera(ac - option_count, (char**)(av + option_count), &options);
	return (0);
}
