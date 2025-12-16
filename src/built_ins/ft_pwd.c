#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		printf("%s\n", pwd);
        return (EXIT_SUCCESS);
	}
	else
		printf("error pwd");
	return (EXIT_FAILURE);
}
