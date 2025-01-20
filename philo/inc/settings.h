/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:54:23 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/20 11:44:43 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
#define SETTINGS_H

// SETITNGS AND LIMITS
# define MAX_PHILOS			200
# define MAX_TIME_TO_DIE_MS	5000
# define MAX_EAT_TIME_MS	5000
# define MAX_SLEEP_TIME_MS	5000
# define MAX_MEAL_COUNT		5000
# define MAX_ARGUMENT_LEN	8

# ifndef DEBUG
#  define DEBUG 0
# endif
# define MONITOR_FREQ_US	    10
# define THREAD_START_DELAY_US	600
# define FORK_HUNT_DELAY_US	    100
# define CUSTOM_SLEEP_PERIOD_US 500

// macros functions are forbidden in this case
// # define STRINGIFY(x) #x
// # define TOSTRING(x) STRINGIFY(x)

// COLORS
# define RESET	"\033[0m"
# define RED	"\033[0;31m"
# define GREEN	"\033[0;32m"
# define YELLOW	"\033[0;33m"
# define B_MAGENTA   "\033[1;35m"   // Bold Magenta


// MESSAGES
# define MSG_WRONG_ARGUMENT_COUNT		"Please provide 4-5 arguments.\n"
# define MSG_TOO_MANY_PHILOS			"Too many philosophers, keep the count under 200.\n"
# define MSG_ZERO_PHILOS				"0 philos... how do you think this will work?"
# define MSG_ONE_OR_MORE_ARGS_WRONG 	"One or more arguments are wrong.\n"

// ERROR CODES
# define MALLOC_FAIL			1
# define INVALID_INPUT			2
# define MEALS_REQUIRED_ZERO	3

#endif
