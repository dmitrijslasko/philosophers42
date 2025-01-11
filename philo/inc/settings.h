// SETITNGS AND LIMITS
#define MAX_PHILOS  	200
#define EXTENDED_OUTPUT  TRUE

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// COLORS
#define GREEN   "\033[0;32m"
#define RED     "\033[0;31m"
#define YELLOW     "\033[0;33m"
#define RESET   "\033[0m"

// MESSAGES
#define MSG_WRONG_ARGUMENT_COUNT "Please provide 4-5 arguments.\n"
#define MSG_TOO_MANY_PHILOS "Too many philosophers, keep the count under " TOSTRING(MAX_PHILOS) ".\n"

// ERROR CODES
#define MALLOC_FAIL	-1
