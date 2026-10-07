#ifndef SHELL_H
#define SHELL_H

/* Constants */
/** Defines the value max input buffer size */
#define APP_INPUT_BUF_SIZE 32

/** Defines the value that is returned if the command is not found */
#define CMDLINE_BAD_CMD (-1)

/** Defines the value that is returned if there are too many arguments */
#define CMDLINE_TOO_MANY_ARGS (-2)

/** Defines the value that is returned if there are too few arguments */
#define CMDLINE_TOO_FEW_ARGS (-3)

/** Defines the value that is returned if an argument is invalid */
#define CMDLINE_INVALID_ARG (-4)

/** Defines the value that is returned if system status not OK */
#define CMDLINE_SYSTEM_STATUS_NOTOK (-5)

/** Defines the value that is returned if operation is not permitted */
#define CMDLINE_SYSTEM_EPERM (-6)

/** Command line function callback type */
typedef int (*pfnShell)(int argc, char *argv[]);

/** Structure for an entry in the command list table */
typedef struct
{
    /** A pointer to a string containing the name of the command */
    const char *pcCmd;

    /** A function pointer to the implementation of the command */
    pfnShell pfnCmd;

    /** A pointer to a string of brief help text for the command */
    const char *pcHelp;
} shell_entry_t;

/**
 * This is the command table that must be provided by the application. The last element
 * of the array must be a structure whose pcCmd field contains a NULL pointer.
 *
 */
extern shell_entry_t psCmdTable[];

/* function prototype */

/** Prototypes for the APIs */
int shell_process(char *pcShell);

#endif /* SHELL_H */