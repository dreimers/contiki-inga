#include "inphasectl.h"

char *test_cmdline0 = "help";
char *test_cmdline1 = "set param1 1337";
char *test_cmdline2 = "get param1";
char *test_cmdline3 = "status";
char *test_cmdline4 = "list-params";

#define ARRAY_LEN(var) (sizeof(var)/sizeof(var[0]))
#define SHELL_OUTPUT_BUFFER_SIZE 512

int main(void)
{

	char buffer[256];
	char shell_output_buffer[SHELL_OUTPUT_BUFFER_SIZE];
	uint8_t ret = 0;
	int16_t iterator = -1;

	char *cmdlist[] = {test_cmdline0,
		test_cmdline1,
		test_cmdline2,
		test_cmdline3,
		test_cmdline4};

	for(int i=0;i<ARRAY_LEN(cmdlist);i++) {
		printf("[%d/%d] command: %s\n", i, ARRAY_LEN(cmdlist), cmdlist[i]);
		strcpy(buffer, cmdlist[i]);

		do {
			ret = command_input_handler(buffer, shell_output_buffer, &iterator);
			printf(">> %s", shell_output_buffer);
		} while(ret == COMMAND_CONTINUE);

		memset(shell_output_buffer, 0, SHELL_OUTPUT_BUFFER_SIZE);
		iterator = -1;
	}

	return 0;
}


