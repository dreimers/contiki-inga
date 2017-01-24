#ifndef INPHASECTL_H_
#define INPHASECTL_H_

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define COMMAND_DEBUG           1
#if COMMAND_DEBUG
#define COMMAND_PRINTF(FORMAT,args...) printf(FORMAT,##args)
#else
#define COMMAND_PRINTF(...)
#endif

#define COMMAND_CONTINUE 0
#define COMMAND_OK 1
#define COMMAND_FAILED 2

#define COMMAND_COUNT (sizeof(available_commands)/sizeof(available_commands[0]))
#define IS_COMMAND(x,y) (strncmp(x.command, y, strlen(x.command)) == 0)


uint16_t (*command_function) (char *, char *, int16_t *);

struct {
    char command[15];
    uint16_t (*command_function) (char *, char *, int16_t *);
    char description[40];
} typedef command_t;

uint16_t command_input_handler(char *in, char *out, int16_t *it);

/* command function declarations */
uint16_t command_help(char *args, char *out, int16_t *it);
uint16_t command_status(char *args, char *out, int16_t *it);
uint16_t command_get(char *args, char *out, int16_t *it);
uint16_t command_set(char *args, char *out, int16_t *it);
uint16_t command_list(char *args, char *out, int16_t *it);

extern const command_t available_commands[];

#endif /* INPHASECTL_H_ */
