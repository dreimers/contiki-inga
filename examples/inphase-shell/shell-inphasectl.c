/*
 * Copyright (c) 2017, Institut für Betriebssysteme und Rechnerverbund
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *
 */

/**
 * \file
 *         inphasectl - Inphase control command
 * \author
 *         Dennis Reimers <dreimers@ibr.cs.tu-bs.de>
 */

#include "contiki.h"
#include "shell.h"
#include "inphasectl.h"

#include <stdio.h>
#include <string.h>
#define SHELL_OUTPUT_BUFFER_SIZE 512
char shell_output_buffer[SHELL_OUTPUT_BUFFER_SIZE];
/*---------------------------------------------------------------------------*/
PROCESS(shell_inphasectl_process, "inphasectl");
SHELL_COMMAND(inphasectl_command,
	      "inphasectl",
	      "inphasectl <cmd> [params]: control the inphase system",
	      &shell_inphasectl_process);
/*---------------------------------------------------------------------------*/

PROCESS_THREAD(shell_inphasectl_process, ev, data)
{

  static uint8_t ret = 0;
  static int16_t iterator = -1;
  PROCESS_BEGIN();

  shell_output_str(&inphasectl_command, ">>-- inphasectl --<<", "");
  printf("data: %s\n", data);

  if(data == NULL | strlen(data) == 0) {
    shell_output_str(&inphasectl_command,
	      "inphasectl <cmd> <params>: control the inphase system", "");
    PROCESS_EXIT();
  }

  do {
	  ret = command_input_handler(data, shell_output_buffer, &iterator);
	  shell_output_str(&inphasectl_command, shell_output_buffer, "");
  } while(ret == COMMAND_CONTINUE);

  memset(shell_output_buffer, 0, SHELL_OUTPUT_BUFFER_SIZE);

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
void
shell_inphasectl_init(void)
{
  shell_register_command(&inphasectl_command);
}
/*---------------------------------------------------------------------------*/
