#include "inphasectl.h"

const command_t available_commands[] = {
    {"help",           &command_help,     "Lists all available commands"},
    {"status",         &command_status,   "Shows status"},
    {"set",            &command_set,      "Set param to value"},
    {"get",            &command_get,      "Get value of param"},
    {"list-params",    &command_list,     "List all possible params"}
};

const parameter_t available_params[] = {
    {"param1",  &param_get_param1,   &param_set_param1,     "param1 description"},
    {"param2",  NULL,   NULL,     "param2 description"},
    {"param3",  NULL,   NULL,     "param3 description"},
    {"param4",  NULL,   NULL,     "param4 description"},
    {"param5",	NULL,   NULL,     "param5 description"}
};

uint16_t dummy_param1 = 0;

/** TODO: implement parameter callbacks **/
uint8_t param_get_param1 (char *args, char *out) {
	DBG("\t(dummy) get param1. args: %s (ignored)\n", args);
	/*sprintf(out, "%sparam1:%d\n", out, dummy_param1);*/
	sprintf(out, "%s%d", out, dummy_param1);

	return COMMAND_OK;
}

uint8_t param_set_param1 (char *args, char *out) {
	DBG("\t(dummy) set param1 to args: %s\n", args);

	if((args == NULL) | (strlen(args) == 0)) {
		sprintf(out, "%s%s", out, "no args given. Abort\n");
		return COMMAND_FAILED;
	} else {
		dummy_param1 = strtoul(args, NULL, 10);
		sprintf(out, "%s%s", out, "param 1 parameter set.\n");
	}

	return COMMAND_OK;
}

int8_t find_param_index(char *param) {
	for (uint16_t i = 0; i < PARAMS_COUNT; i++) {
		/* iterate all available parameters */
		if ( IS_PARAM(available_params[i], param)) {
			/* if matched, return index */
			return i;
		}
	}
	return -1;
}

int8_t find_command_index(char *command) {
	for (uint16_t i = 0; i < COMMAND_COUNT; i++) {
		/* iterate all available commands  */
		if ( IS_COMMAND(available_commands[i], command)) {
			/* if matched, return index */
			return i;
		}
	}
	return -1;
}

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
	DBG("called cmd_status [it=%d]\n", *(it));
	for (uint16_t i = 0; i < PARAMS_COUNT; i++) {
		/* iterate all available parameters */
		parameter_t param_to_get = available_params[i];
		sprintf(out, "%sparam: %s", 
			out, 
			param_to_get.param);
		sprintf(out, "%s value: ", out);
		if (param_to_get.param_get_func != NULL) {
			param_to_get.param_get_func(args, out);
			sprintf(out, "%s\n", out);
		} else {
			sprintf(out, "%snone\n", out);
		}
	}
	return COMMAND_OK;
}

uint16_t command_get(char *args, char *out, int16_t *it) {
	uint16_t ret = COMMAND_FAILED;

	DBG("called cmd_get [it=%d]\n", *(it));
	DBG("[args: %s]\n", args);
	char *param = strsep(&args, " ");

	int8_t param_index = find_param_index(param);
	DBG("[param: %s; param_index:%d]\n", param, param_index);
	if (param_index != -1) {
		DBG("parameter found: %s '%s' (%d): \n", 
				available_params[param_index].param,
				available_params[param_index].description,
				param_index);
		if (available_params[param_index].param_get_func !=NULL) {
			sprintf(out, "%s out: %s:", 
					out, 
					available_params[param_index].param);
			ret = available_params[param_index].param_get_func(args, out);
			sprintf(out, "%s\n", out);
		} else {
			sprintf(out, "%s err: no callback defined\n", out);
			ret = COMMAND_FAILED;
		}
	}
	DBG("[remaining args: %s]\n", args);

	DBG("<<cmd_get done\n\n");
	return ret;
}


uint16_t command_set(char *args, char *out, int16_t *it) {
	uint16_t ret = COMMAND_FAILED;

	DBG("called cmd_set [it=%d]\n", *(it));
	DBG("[args: %s]\n", args);
	char *param = strsep(&args, " ");

	int8_t param_index = find_param_index(param);
	DBG("[param: %s; param_index:%d]\n", param, param_index);
	if (param_index != -1) {
		DBG("parameter found: %s '%s' (%d): \n", 
				available_params[param_index].param,
				available_params[param_index].description,
				param_index);
		if (available_params[param_index].param_set_func !=NULL) {
			ret = available_params[param_index].param_set_func(args, out);
		} else {
			sprintf(out, "%s no callback defined\n", out);
			ret = COMMAND_FAILED;
		}
	}
	DBG("[remaining args: %s]\n", args);

	DBG("<<cmd_set done\n\n");
	return ret;
}

uint16_t command_list(char *args, char *out, int16_t *it) {
	sprintf(out, "cmd_list\n");

	for(int i=0; i < PARAMS_COUNT; i++) {
		sprintf(out, "%s%s: %s\n", out, available_params[i].param,
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
		sprintf(out, "%-16s\t\t%s\n", available_commands[*it].command,
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
