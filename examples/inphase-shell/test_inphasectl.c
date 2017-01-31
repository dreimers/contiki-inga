#include <stdlib.h>
#include "inphasectl.h"

char *test_cmdline0 = "help";
char *test_cmdline1 = "set param1 1337";
char *test_cmdline2 = "set param2";
char *test_cmdline3 = "get param1";
char *test_cmdline4 = "status";
char *test_cmdline5 = "list-params";

#define ARRAY_LEN(var) (uint8_t)(sizeof(var)/sizeof(var[0]))
#define SHELL_OUTPUT_BUFFER_SIZE 512

int main(void)
{

	char buffer[256];
	char shell_output_buffer[SHELL_OUTPUT_BUFFER_SIZE];
	uint8_t ret = 0;
	int16_t iterator = -1;
	char *arg;
	char *args;
	uint8_t argc;
	int8_t index = -1;

	char *cmdlist[] = {test_cmdline0,
		test_cmdline1,
		test_cmdline2,
		test_cmdline3,
		test_cmdline4,
		test_cmdline5};


	for(uint8_t i=0;i<ARRAY_LEN(cmdlist);i++) {
		printf("[%d/%d] command: %s\n", i, ARRAY_LEN(cmdlist)-1, cmdlist[i]);
		strcpy(buffer, cmdlist[i]);

		/*args = strdup(cmdlist[i]);*/
		/*printf("[%d] args@%p: %s\n", i, args, args);*/
		/*while ((arg = strsep(&args, " "))) {*/
			/*printf("\t[%d] \targ@%p: %s\n", argc, arg, arg);*/
			/*printf("\t\targs@%p: %s\n", args, args);*/
			/*switch(argc) {*/
				/*case 0:*/
					/*index = find_command_index(arg);*/
					/*printf("\t\t\tcommand index: %d\n", index);*/
					/*break;*/
				/*case 1:*/
					/*index = find_param_index(arg);*/
					/*printf("\t\t\tparam index: %d\n", index);*/
					/*break;*/
				/*default:*/
					/*break;*/
			/*}*/
			/*argc++;*/
		/*}*/

		/*free(args);*/

		/*argc = 0;*/
		/*strcpy(buffer, cmdlist[i]);*/

		memset(shell_output_buffer, 0, SHELL_OUTPUT_BUFFER_SIZE);
		do {
			ret = command_input_handler(buffer, shell_output_buffer, &iterator);
			printf(">> %s", shell_output_buffer);
		} while(ret == COMMAND_CONTINUE);

		memset(shell_output_buffer, 0, SHELL_OUTPUT_BUFFER_SIZE);
		iterator = -1;
	}

	return 0;
}


