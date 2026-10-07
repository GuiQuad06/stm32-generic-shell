#include "handlers.h"

#include "shell.h"

#include <stdint.h>
#include <stdio.h>

/**
 *  Table of valid command strings, callback functions and help messages.
 *  This is used by the shell module.
 *
 */
shell_entry_t psCmdTable[] = {{"help", CMD_Help, " : Display list of commands"},
                              {"a", CMD_A, " : Placeholder A"},
                              {"b", CMD_B, " : Placeholder B"},
                              {"c", CMD_C, " : Placeholder C"},
                              {0, 0, 0}};

int CMD_Help(int argc, char *argv[])
{
    uint8_t idx = 0;

    printf("\nAvailable Commands:\n\n");

    /** Display strings until we run out of them. */
    while (psCmdTable[idx].pcCmd)
    {
        printf("%10s %s\n", psCmdTable[idx].pcCmd, psCmdTable[idx].pcHelp);
        idx++;
    }
    printf("\n");

    return (0);
}

int CMD_A(int argc, char *argv[])
{
    // Implementation of the A command
    return 0;
}

int CMD_B(int argc, char *argv[])
{
    // Implementation of the B command
    return 0;
}

int CMD_C(int argc, char *argv[])
{
    // Implementation of the C command
    return 0;
}
