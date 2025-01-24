/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_handling.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:57:28 by bama              #+#    #+#             */
/*   Updated: 2025/01/24 04:03:28 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPT_HANDLING_H
#define OPT_HANDLING_H

# define OPTH_FLAG_ALL	0x1

# define OPTH_NO_ARGS		-0x1

// If the parser arrives on a arg (in 'av') who is not an option, the function shall return.
// @param ac The number of elements in 'av'
// @param av The arguments list
// @param ioptions A list of strings that takes only the individuals options (ex: {"option1", "option2", "option3", NULL})   (like --option1 --option2 --option3)
// @param foptions A list of char that takes only the fast options (ex: {'o', 'd', 'u', '\0'})  (like -odu)
// @param flag If is OPTH_SET_ALL : --all & -a is automatically set
// @return The number of options parsed. But, if any error, it returns a negative number (-1, or <=-2), see OPTH_NO_ARGS(-1) and <=-2 is : "(-index) - 2"
// @note We assumes the buffer is a structures, or just simple buffer, that contains only char (1 byte data). A byte is one param, in the same order than 'ioptions'
int	options_handling(int ac, const char** av, char** ioptions, char* foptions, void* buffer, int bufsize, int flag);

#endif
