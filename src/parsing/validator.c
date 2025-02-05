/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:38:37 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/19 16:43:21 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bool validate_group()
// {
// }
// // Syntax Rules to Check in the AST
// // When constructing or validating the AST from the parsed tokens, you should enforce the following syntax rules:

// bool validate_pipe()
// {
// 	return true;
// // 1. **Pipeline Validity**:  
// //    - A pipeline must consist of valid commands connected by `'|'`.
// //    - A pipeline cannot start or end with `'|'`.
// }

// bool validate_command()
// {
// 	return true;
// // 2. **Command Validity**:  
// //    - A command must consist of a `<simple_command>` and an optional `<redirection_list>`.
// //    - `<simple_command>` must be either a `<builtin>`, an `<executable>`, or an `<assignment>`.
// }

// bool validate_redirection()
// {
// // 3. **Redirection Rules**:  
// //    - `<` and `<<` must be followed by a valid `<word>` (input file or delimiter).
// //    - `>` and `>>` must be followed by a valid `<word>` (output file).
// //    - Redirections cannot precede a pipeline operator.
// //   - Redirection misuse (e.g., multiple consecutive redirections without a target).
// 	return true;
// }

// bool validate_quotes()
// {
// // 5. **Quoting Rules**:  
// //    - Single quotes prevent interpretation of all special characters.
// //    - Double quotes allow `$` and `$?` expansion but escape other characters.
// //    - Quotes must be closed.
// //   - Unclosed quotes.
// 	return true;
// }

// // bool validate_variable()
// // {
// // 4. **Word and Variable Rules**:  
// //    - `<word>` must consist of valid letters, digits, or `_`.
// //    - `$<word>` must match a valid environment variable format.
// //    - `$?` is allowed as a special variable.
   
// // }
