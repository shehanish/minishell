/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:21:40 by shkaruna          #+#    #+#             */
/*   Updated: 2024/12/16 18:18:43 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

volatile sig_atomic_t g_last_signal = 0;

void signal_reset_prompt(int signo)
{
    if (signo == SIGINT)
    {
        g_last_signal = 130; // Set exit status for Ctrl+C
        write(STDOUT_FILENO, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void ignore_sigquit(void)
{
    signal(SIGQUIT, SIG_IGN);
}

void set_signals_interactive(void)
{
    ignore_sigquit();
    signal(SIGINT, signal_reset_prompt);
}

void signal_print_newline(int signo)
{
    if (signo == SIGINT)
    {
        g_last_signal = 130; // Set exit status for Ctrl+C in non-interactive mode
    }
    else if (signo == SIGQUIT)
    {
        g_last_signal = 131; // Set exit status for Ctrl+\ in non-interactive mode
        write(STDOUT_FILENO, "Quit: 3\n", 8);
    }
}

void set_signals_noninteractive(void)
{
    signal(SIGINT, signal_print_newline);
    signal(SIGQUIT, signal_print_newline);
}
