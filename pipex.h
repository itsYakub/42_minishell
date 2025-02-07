/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:49:56 by lwillis           #+#    #+#             */
/*   Updated: 2025/01/20 11:27:26 by lwillis          ###   ########.fr       */
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
int		do_cmd(char *cmd, char *envp[]);

#endif
