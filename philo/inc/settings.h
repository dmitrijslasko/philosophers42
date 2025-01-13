/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:54:23 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/13 18:32:57 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
#define SETTINGS_H

// SETITNGS AND LIMITS
# define MAX_PHILOS			200
# define MAX_TIME_TO_DIE_MS	2000
# define MAX_EAT_TIME_MS	2000
# define MAX_SLEEP_TIME_MS	2000
# define MAX_MEAL_COUNT		2000
# define MAX_ARGUMENT_LEN	8

# define EXTENDED_OUTPUT  	TRUE

// macros functions are forbidden in this case
// # define STRINGIFY(x) #x
// # define TOSTRING(x) STRINGIFY(x)

// COLORS
# define RESET	"\033[0m"
# define RED	"\033[0;31m"
# define GREEN	"\033[0;32m"
# define YELLOW	"\033[0;33m"

// MESSAGES
# define MSG_WRONG_ARGUMENT_COUNT	"Please provide 4-5 arguments.\n"
# define MSG_TOO_MANY_PHILOS			"Too many philosophers, keep the count under 200.\n"
# define MSG_ZERO_PHILOS				"0 philos... how do you think this will work?"

// ERROR CODES
# define MALLOC_FAIL	-1

#endif