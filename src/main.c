/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:43:08 by bama              #+#    #+#             */
/*   Updated: 2025/01/24 04:33:57 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DividaEtImpera.h"

int	main(int ac, const char** av)
{
	t_dei_options	options = {0};
	int				option_count;
	option_count = options_handling(--ac, ++av, (char*[]){DIVIDA, IMPERA, BYTES, PARTS, NULL}, (char[]){C_DIVIDA, C_IMPERA, C_BYTES, C_PARTS, '\0'}, &options, sizeof(t_dei_options), OPTH_FLAG_ALL);
	if (option_count < 0)
		return (option_count);
	else if (ac - option_count <= 0)
		return (1);
	if (options.divida)
		divida(ac - option_count, (char**)(av + option_count), &options);
	else if (options.impera)
		impera(ac - option_count, (char**)(av + option_count), &options);
	return (0);
}
