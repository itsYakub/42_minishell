/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:16:33 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/13 10:14:37 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free2d(void **arr)
{
	void	**acpy;

	acpy = arr;
	while (*acpy)
		free(*acpy++);
	if (arr)
		free(arr);
}
