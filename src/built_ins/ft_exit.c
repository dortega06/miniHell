#include "../../includes/minishell.h"

static int check_exit_args(t_shell *msh)
{
    int i;
    char *arg;

    // msh->count_cmd_args debería incluir "exit" como el primer argumento.
    // Si hay más de 2 elementos en el array (ej: "exit" "123" "otro"), es > 2
    if (msh->count_cmd_args > 2)
        return (1); // Código especial para "too many arguments"

    arg = msh->cmd_args[1];

    if (arg)
    {
        i = 0;
        // Permitimos un signo '+' o '-' opcional al principio (como hace Bash)
        if (arg[0] == '+' || arg[0] == '-') {
            i++;
        }
        
        // Debe haber al menos un dígito después del signo (ej: "exit +") es inválido
        if (arg[i] == '\0') {
             // Bash lo considera un error numérico
             // Imprimimos el error a stderr
             fprintf(stderr, "exit: %s: numeric argument required\n", arg);
             return (255); // Usamos 255, el código de Bash para este error
        }

        while (arg[i])
        {
            if (!ft_isdigit(arg[i]))
            {
                // Imprimimos el error a stderr
                fprintf(stderr, "exit: %s: numeric argument required\n", arg);
                return (255); // Usamos 255
            }
            i++;
        }
        
        // Si todo es numérico (incluyendo el signo opcional), devolvemos el valor.
        // El valor de retorno debe ser tratado como (valor % 256) en ft_exit.
        return (ft_atoi(arg));
    }
    
    // Si no hay argumentos, devuelve 0 por defecto.
    return (0);
}

void	ft_exit_built(t_shell *msh)
{
	ft_putendl_fd("exit", 2);
	msh->exit_status = check_exit_args(msh);
	if (msh->exit_status != 1)
		exit(msh->exit_status);
	ft_putendl_fd("exit: too many arguments", 2);
}