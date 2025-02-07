/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:49:56 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/07 17:55:13 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// write
# include <unistd.h>
// read
# include <stdio.h>
// exit
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
// open, close
# include <fcntl.h>

void	show_error(char *error, int error_code);

#endif
