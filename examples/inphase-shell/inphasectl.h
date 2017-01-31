#ifndef INPHASECTL_H_
#define INPHASECTL_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define COMMAND_DEBUG           0
#if COMMAND_DEBUG
#define COMMAND_PRINTF(FORMAT,args...) printf(FORMAT,##args)
#else
#define COMMAND_PRINTF(...)
#endif

#if COMMAND_DEBUG
#define DBG(FORMAT,args...) printf("DBG:"FORMAT,##args)
#else
#define DBG(...)
#endif


#define COMMAND_CONTINUE 0
#define COMMAND_OK 1
#define COMMAND_FAILED 2

#define COMMAND_COUNT (sizeof(available_commands)/sizeof(available_commands[0]))
#define IS_COMMAND(x,y) (strncmp(x.command, y, strlen(x.command)) == 0)

#define PARAMS_COUNT (sizeof(available_params)/sizeof(available_params[0]))
#define IS_PARAM(x,y) (strncmp(x.param, y, strlen(x.param)) == 0)


uint16_t (*command_function) (char *, char *, int16_t *);
uint8_t (*param_function) (char *, char *);

/* Getter/Setter for parameters */
uint8_t param_get_param1 (char *args, char *out);
uint8_t param_set_param1 (char *args, char *out);

struct {
    char command[15];
    uint16_t (*command_function) (char *, char *, int16_t *);
    char description[40];
} typedef command_t;

struct {
    char param[15];
    uint8_t (*param_get_func) (char *, char *);
    uint8_t (*param_set_func) (char *, char *);
    char description[40];
} typedef parameter_t;

int8_t find_command_index(char *command);
int8_t find_param_index(char *param);

uint16_t command_input_handler(char *in, char *out, int16_t *it);

/* command function declarations */
uint16_t command_help(char *args, char *out, int16_t *it);
uint16_t command_status(char *args, char *out, int16_t *it);
uint16_t command_get(char *args, char *out, int16_t *it);
uint16_t command_set(char *args, char *out, int16_t *it);
uint16_t command_list(char *args, char *out, int16_t *it);

extern const command_t available_commands[];
extern const parameter_t available_params[];

#endif /* INPHASECTL_H_ */
