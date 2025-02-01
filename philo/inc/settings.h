/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:54:23 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/01 17:33:31 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# ifndef DEBUG
#  define DEBUG 0
# endif

// SETITNGS AND LIMITS
# define MAX_PHILOS			500
# define MAX_TIME_TO_DIE_MS	5000
# define MAX_EAT_TIME_MS	5000
# define MAX_SLEEP_TIME_MS	5000
# define MAX_MEAL_COUNT		5000
# define MAX_ARGUMENT_LEN	8

# define THREAD_START_DELAY		2		// 1/n of the eat time
# define MONITOR_FREQ_US	    1
# define FORK_HUNT_DELAY_US	    1
# define CUSTOM_SLEEP_PERIOD_US 100
# define DEATH_MSG_DELAY_MS		2

// macros functions are forbidden in this case
// # define STRINGIFY(x) #x
// # define TOSTRING(x) STRINGIFY(x)

// COLORS
# define RST			"\033[0m"
# define RED			"\033[0;31m"
# define GREEN			"\033[0;32m"
# define YELLOW			"\033[0;33m"
# define B_MAGENTA   	"\033[1;35m"   // Bold Magenta

// MESSAGES
# define MSG_WRONG_ARGUMENT_COUNT		"Please provide 4-5 arguments.\n"
# define MSG_TOO_MANY_PHILOS			\
				"Too many philos, keep the count under 200.\n"
# define MSG_ZERO_PHILOS				\
				"0 philos... how do you think this will work?"
# define MSG_ONE_OR_MORE_ARGS_WRONG 	"One or more arguments are wrong.\n"

// MESAGES - DEBUG
# define MSG_DEBUG_LEFT_FORK			"%lld >> %lld [%d] has taken a L fork\n"
# define MSG_DEBUG_RIGHT_FORK			"%lld >> %lld [%d] has taken a R fork\n"
# define MSG_DEBUG_EAT					\
				"%lld >> %lld [%d] is eating\t\tMeals count: %d\n"
# define MSG_DEBUG_SLEEP				\
				"%lld >> %lld [%d] is sleeping\n"
# define MSG_DEBUG_THINK				\
				"%lld >> %lld [%d] is thinking\n"
# define MSG_DEBUG_DIED					"%lld >> %lld [%d] died\n"
// MESSAGES - CLEAN
# define MSG_LEFT_FORK					"%lld %d has taken a fork\n"
# define MSG_RIGHT_FORK					"%lld %d has taken a fork\n"
# define MSG_EAT						"%lld %d is eating\n"
# define MSG_SLEEP						"%lld %d is sleeping\n"
# define MSG_THINK						"%lld %d is thinking\n"
# define MSG_DIED						"%lld %d died\n"

// ERROR CODES
# define MALLOC_FAIL			1
# define INVALID_INPUT			2
# define MEALS_REQUIRED_ZERO	3

#endif
