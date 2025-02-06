#include "minishell.h"

int	main(int ac, char **av, char **ev)
{
	char	***tokens;
	char	*input;

	(void) ac;
	(void) av;
	(void) ev;
	tokens = NULL;
	input = NULL;
	while (1)
	{
		input = readline("> minishell: $ ");
		if (!ft_strncmp(input, "exit", ft_strlen(input)))
		{
			free(input);
			break ;
		}
		free(input);
	}
	return (0);
}
