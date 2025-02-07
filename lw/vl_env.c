/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vl_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:33:30 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/07 11:15:45 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// void	add_env_var(char *key, char *val, char *envp[])
// {
// 	int		i;
// 	int		count;
// 	char	**new_envp;
// 	int		key_len;

// 	count = -1;
// 	while (envp[++count]) ;	
		
// 	//free(envp);
// 	new_envp = malloc(sizeof(char *) * (count + 1));
// 	copy_vars(envp, new_envp);	
// 	key_len = ft_strlen(key);
// 	new_envp[0] = malloc(key_len + ft_strlen(val) + 2);
// 	i = 0;
// 	while (i < key_len)
// 	{
// 		new_envp[0][i] = key[i];
// 		i++;
// 	}
// 	new_envp[0][i++] = '=';
// 	while (i <= key_len + ft_strlen(val))
// 	{
// 		new_envp[0][i] = val[i - key_len - 1];
// 		i++;
// 	}
// 	new_envp[0][i] = '\0';
// 	envp = new_envp;
// }

// t_env	*env_var_node(char *str, t_env *env_vars)
// {
// 	t_env	*node;

// 	node = env_vars;
// 	while (node)
// 	{
// 		if (0 == ft_strncmp(str, node->var, ft_strlen(str)))
// 			return (node);
// 		node = node->next;
// 	}
// 	return (NULL);
// }

// char	*env_var(char *str, t_env *env_vars)
// {
// 	int	len;
// 	t_env	*node;

// 	node = env_vars;
// 	len = ft_strlen(str);
// 	while (node)
// 	{
// 		if (0 == ft_strncmp(str, node->var, len))
// 			return (ft_substr(node->var, len, ft_strlen(node->var)));
// 		node = node->next;
// 	}
// 	return (NULL);
// }

// static t_env	*create_node(char *var)
// {
// 	t_env	*node;

// 	node = malloc(sizeof(t_env));
// 	node->var = ft_strdup(var);
// 	node->next = NULL;
// 	return (node);
// }

// void	append_node(t_env **head, char *var)
// {
// 	t_env	*node;
// 	t_env	*last;

// 	node = create_node(var);
// 	if (!*head)
// 	{
// 		*head = node;
// 		return ;
// 	}
// 	last = *head;
// 	while (last->next)
// 		last = last->next;
// 	last->next = node;
// }

// void	init_env_vars(t_env **head, char *envp[])
// {
// 	int		i;
	
// 	i = -1;
// 	while (envp[++i])
// 		append_node(head, envp[i]);
// }
