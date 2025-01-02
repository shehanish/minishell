/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:10:15 by shkaruna          #+#    #+#             */
/*   Updated: 2025/01/02 13:01:10 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// Free the command list
void free_command_list(t_cmd *cmd_list) {
    t_cmd *temp;
    while (cmd_list) {
        temp = cmd_list;
        cmd_list = cmd_list->next;
        free(temp->command);
        for (int i = 0; temp->args && temp->args[i]; i++)
            free(temp->args[i]);
        free(temp->args);
        free(temp->input_file);
        free(temp->output_file);
        free(temp);
    }
}
// Free the token list
static void free_token_list(t_token *token_list) {
    t_token *temp;
    while (token_list) {
        temp = token_list;
        token_list = token_list->next;
        free(temp->value);
        free(temp);
    }
}

int main(int argc, char **argv, char **envp)
{
    t_cmd *cmd_list = NULL;
    t_shell shell;
    shell.env_list = env_init(envp);
    shell.last_exit_status = 0;
    t_token *token_list = NULL;
    char *line = NULL;
    char **args = NULL;
    (void)argc;
    (void)argv;
    
    token_list = NULL;
    
    set_signals_interactive();
    
    while (1)
    {
        line = readline("minishell> ");
        if (!line)
        {
            write(STDOUT_FILENO, "exit\n", 5);
            break;
        }

        if (line[0] != '\0')
        {
            add_history(line);
        }

        ft_lexing(line, &token_list, shell.env_list, &shell);
        
        if (!token_list)
        {
            free(line);
            continue;
        }
        if (!parse_quotes_in_tokens(token_list, shell.env_list))
        {
            printf("Error: Unclosed quote in the input\n");
            free_token_list(token_list);
            token_list = NULL;
            shell.last_exit_status = 1;
            continue;
        }
        args = ft_split(line, ' ');
        if (!args)
        {
            free(line);
            free_token_list(token_list);
            token_list = NULL;
            continue;
        }
        cmd_list = parse_pipeline(token_list);
        if (!cmd_list)
        {
            free(line);
            free(args);
            free_token_list(token_list);
            token_list = NULL;
            continue;
        }
        set_signals_noninteractive();
        ft_execute_main(cmd_list, &shell);
    
        free(line); // Free the `line` buffer
        line = NULL;
        free(args);
        free_token_list(token_list); // Free `args` array
        token_list = NULL;
        set_signals_interactive();
    }

    // Explicit cleanup for readline to avoid memory leaks
    rl_clear_history(); // Clears the history before exiting
    return 0;
}

