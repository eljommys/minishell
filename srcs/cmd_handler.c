/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 17:05:49 by marvin            #+#    #+#             */
/*   Updated: 2020/12/09 17:05:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ctrl_c_handler(char c, char *buff, int pos)
{
	if (c == 3)									//ETX(fin de texto)
	{
		while (pos-- > 0)
			ft_putstr_fd("\033[1D", 1);			////1D->Cursor Back 1 space
		write(1, "\n", 1);
		buff[0] = 0;
		return (1);
	}
	return (0);
}

static int	bs_handler(char c, char *buff, int *count, int *pos)
{
    int	x;
    int	i;

	if (c != 127)								//DEL(suprimir)
		return (0);
	x = *count;
	i = *pos;
	if (i > 2)
	{
		ft_putstr_fd("\033[1D\033[J", 1);		//1D->Cursor Back 1 space ; J->Erase in Display (clear from cursor to end of screen).
		i--;
	}
	buff[x] = 0;
	if (--x < 0)
		x = 0;
	*pos = i;
	*count = x;
	return (1);
}

static int	nl_handler(char c, char *buff, int pos)
{
	if (c == 13)								//CR(retorno de carro)
	{
		write(1, "\n", 1);
		buff[pos] = 0;
		return (1);
	}
	return (0);
}

static int	disable_keys(char c)
{
	if (c == 8)									//BS(retorceso)
		return (1);
	if (c == 27)								//ESC(escape)
	{
		if ((c = ft_getchar()) == '[')
		{
			ft_getchar();
			return (1);
		}
	}
	return (0);
}

int			cmd_handler(char *buff, int *x, int *i)
{
	char	c;

	c = ft_getchar();
	if (disable_keys(c))					//Ignora las teclas de retroceso y escape
		return (2);
	//write(1, &c, 1);
	buff[*x] = c;
	if (nl_handler(c, buff, *x))			//Comprueba retorno de carro
		return (1);
	if (bs_handler(c, buff, x, i))			//Comprueba la tecla suprimir
		return (2);
	if (c == 4 && *x == 0)					//Comprueba fin de trasmision (Ctrol + D sin texto en pantalla)
		logout();
	if (ctrl_c_handler(c, buff, *i))		//Comprueba fin de texto (Ctrl + C)
		return (1);
	if (c >= 32 && c <= 126)				//Comprueba que sea un caracter imprimible
	{
		*i += 1;
		*x += 1;
	}
	return (0);
}