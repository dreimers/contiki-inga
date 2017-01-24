#include "inphasectl.h"

const command_t available_commands[] = {
    {"help",           &command_help,     "\t\tLists all available commands\r\n"},
    {"status",         &command_status,       "\t\tShows status\r\n"},
    {"set",            &command_set,          "\t\tSet param to value\r\n"},
    {"get",            &command_get,          "\t\tGet value of param\r\n"},
    {"list-params",    &command_list,          "\t\tList all possible params\r\n"}
};

const parameter_t available_params[] = {
    {"param1",  BOTH,   NULL,     "\t\tparam1 description\r\n"},
    {"param2",  GET,    NULL,     "\t\tparam2 description\r\n"},
    {"param3",  SET,    NULL,     "\t\tparam3 description\r\n"},
    {"param4",  BOTH,   NULL,     "\t\tparam4 description\r\n"},
    {"param5",	NONE,   NULL,     "\t\tparam5 description\r\n"}
};

uint16_t command_input_handler(char *in, char *out, int16_t *it) {
	/* CAUTION: input is expected to be terminated */

	char *command = NULL;
	char *args = NULL;

	uint16_t input_length = strlen(in);
	uint16_t command_length = 0;

	if (strcmp(in, "")) {
		/* command not empty */

		/* split buffer and args */
		for (int i = 0; i <= input_length; i++) {
			/* get command */
			if (!command) {
				if (in[i] == ' ' || in[i] == 0 || in[i] == '\n') {
					/* found space or end of string */
					command_length = i;
					command = in;
				}
			} else {
				/* found command, are there args? */
				if (!args) {
					/* skip leading spaces */
					if (in[i] != ' ') {
						if (in[i+1] != 0) {
							args = &in[i];
						}
					}
				}
			}
		}

		/* check if command exists */
		for (uint16_t i = 0; i < COMMAND_COUNT; i++) {
			/* iterate all available commands */
			if ( IS_COMMAND(available_commands[i], command) &&
					strlen(available_commands[i].command) == command_length ) {
				/* if matched, call function */
				return (*available_commands[i].command_function)(args, out, it);
			}
		}

		/* not matched with any available command */
		sprintf(out, "command not found!\r\n");
		return COMMAND_FAILED;
	}
	else {
		/* command was empty */
		return COMMAND_OK;
	}
}

uint16_t command_status(char *args, char *out, int16_t *it) {
	sprintf(out, "cmd_status\n");
	return COMMAND_OK;
}

uint16_t command_get(char *args, char *out, int16_t *it) {
	sprintf(out, "cmd_get\n");
	return COMMAND_OK;
}

uint16_t command_set(char *args, char *out, int16_t *it) {
	sprintf(out, "cmd_set\n");
	return COMMAND_OK;
}

uint16_t command_list(char *args, char *out, int16_t *it) {
	sprintf(out, "cmd_list\n");

	for(int i=0; i < PARAMS_COUNT; i++) {
		sprintf(out, "%s%s%s\n", out, available_params[i].param,
				available_params[i].description);
	}

	return COMMAND_OK;
}

uint16_t command_help(char *args, char *out, int16_t *it) {
	if (*it == -1) {
		/* loop was not initialized, set var to start */
		*it = 0;
		return COMMAND_CONTINUE;
	} else if (*it < COMMAND_COUNT) {
		/* is still in range */
		sprintf(out, "%s%s", available_commands[*it].command,
				available_commands[*it].description);
		*it = *it + 1;

		if (*it == sizeof(available_commands) / sizeof(command_t)) {
			/* loop will be done, this prevents double output of last line */
			return COMMAND_OK;
		} else {
			/* not done yet, function has to be called again */
			return COMMAND_CONTINUE;
		}
	}
	else {
		return COMMAND_OK;
	}
}
