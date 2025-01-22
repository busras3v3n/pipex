/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busras3v3n@proton.me>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:13:48 by busseven          #+#    #+#             */
/*   Updated: 2024/11/09 17:21:03 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

int	ft_printf(const char *s, ...);
int	ft_print_char(char c);
int	ft_print_str(char *s);
int	ft_print_nbr(int i);
int	ft_print_hex(unsigned int i, char s);
int	ft_print_ptr(void *p);
int	ft_print_unbr(unsigned int n, int fd);
int	ft_print_percent(void);

#endif