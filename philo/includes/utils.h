/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiteri <lspiteri@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 22:35:09 by lspiteri          #+#    #+#             */
/*   Updated: 2025/12/10 22:35:18 by lspiteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int		ft_atoi(const char *str);
long	get_time_us(void);
long	get_time_ms(void);
void	*ft_memset(void *b0, int c, size_t len);

void	psleep(long t_start, long t, long p);
# ifndef P
#  define P 125
# endif

#endif
