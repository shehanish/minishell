/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:22:26 by shkaruna          #+#    #+#             */
/*   Updated: 2024/12/16 18:19:30 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
#define SIGNALS_H

#include <signal.h>

extern volatile sig_atomic_t g_last_signal;

void signal_reset_prompt(int signo);
void ignore_sigquit(void);
void set_signals_interactive(void);
void signal_print_newline(int signo);
void set_signals_noninteractive(void);

#endif // SIGNALS_H