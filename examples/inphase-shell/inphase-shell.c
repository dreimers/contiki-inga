/*
 * Copyright (c) 2017, Institut für Betriebssysteme und Rechnerverbund.
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
 *         Inphase shell
 * \author
 *         Dennis Reimers <dreimers@ibr.cs.tu-bs.de>
 */

#include "contiki.h"
#include "shell.h"
#include "serial-shell.h"

#include "shell-inphasectl.h"

#include "dev/leds.h"
#include "dev/serial-line.h"
#include "dev/rs232.h"

#include <stdio.h>
#include <string.h>

/*---------------------------------------------------------------------------*/
PROCESS(inphase_shell_process, "inphase shell");
AUTOSTART_PROCESSES(&inphase_shell_process);
/*---------------------------------------------------------------------------*/

PROCESS_THREAD(inphase_shell_process, ev, data)
{
  PROCESS_BEGIN();

  /* use first usart for shell */
  rs232_set_input(RS232_PORT_0, serial_line_input_byte);
  serial_line_init();
  serial_shell_init();

  /* import some commands from contiki */
  shell_blink_init();
  shell_ps_init();
  shell_reboot_init();

  /* initilize inphasectl */
  shell_inphasectl_init();

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/