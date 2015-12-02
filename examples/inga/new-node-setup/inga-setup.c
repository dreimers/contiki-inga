/*
 * Copyright (c) 2015, TU Braunschweig
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
 * This file is part of the Contiki operating system.
 */

/**
 * \file
 *        INGA node setup
 *
 * \author
 *        Dennis Reimers <dreimers@ibr.cs.tu-bs.de>
 */

#include <stdio.h>

#include "contiki.h"
#include "lib/settings.h"

#define PRINTF printf

PROCESS(setup_process, "INGA setup process");
AUTOSTART_PROCESSES(&setup_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(setup_process, ev, data)
{
  PROCESS_BEGIN();
  PRINTF("Writing settings to EEPROM...\n");
#ifdef INGA_CONF_PAN_ADDR
  if (settings_set_uint16(SETTINGS_KEY_PAN_ADDR, (uint16_t) INGA_PAN_ADDR) == SETTINGS_STATUS_OK) {
    uint16_t settings_panaddr = settings_get_uint16(SETTINGS_KEY_PAN_ADDR, 0);
    PRINTF("[inga-setup] New PAN Addr:  0x%04X\n", settings_panaddr);
  } else {
    PRINTF("[inga-setup] Error: Failed writing PAN Addr to EEPROM\n");
  }
#endif /* INGA_CONF_PAN_ADDR */

#ifdef INGA_CONF_PAN_ID
  if (settings_set_uint16(SETTINGS_KEY_PAN_ID, (uint16_t) INGA_PAN_ID) == SETTINGS_STATUS_OK) {
    uint16_t settings_panid = settings_get_uint16(SETTINGS_KEY_PAN_ID, 0);
    PRINTF("[inga-setup] New PAN ID:   0x%04X\n", settings_panid);
  } else {
    PRINTF("[inga-setup] Error: Failed writing PanID to EEPROM\n");
  }
#endif /* INGA_CONF_PAN_ID */

#ifdef INGA_CONF_RADIO_CHANNEL
  if (settings_set_uint8(SETTINGS_KEY_CHANNEL, (uint8_t) INGA_RADIO_CHANNEL) == SETTINGS_STATUS_OK) {
    uint8_t settings_channel = settings_get_uint8(SETTINGS_KEY_CHANNEL, 0);
    PRINTF("[inga-setup] New channel:  %02d\n", settings_channel);
  } else {
    PRINTF("[inga-setup] Error: Failed writing channel to EEPROM\n");
  }
#endif /* INGA_CONF_RADIO_CHANNEL */

#ifdef INGA_CONF_RADIO_TX_POWER
  if (settings_set_uint8(SETTINGS_KEY_TXPOWER, (uint8_t) INGA_RADIO_TX_POWER) == SETTINGS_STATUS_OK) {
    uint8_t settings_txpower = settings_get_uint8(SETTINGS_KEY_TXPOWER, 0);
    PRINTF("[inga-setup] New TX power: %02d\n", settings_txpower);
  } else {
    PRINTF("[inga-setup] Error: Failed writing TX power to EEPROM\n");
  }
#endif /* INGA_CONF_RADIO_TX_POWER */

#ifdef INGA_CONF_EUI64
  uint8_t settings_eui64[8] = {INGA_CONF_EUI64};
  if (settings_set(SETTINGS_KEY_EUI64, settings_eui64, 8) == SETTINGS_STATUS_OK) {
    settings_get(SETTINGS_KEY_EUI64, 0, settings_eui64, sizeof (settings_eui64));
    PRINTF("[inga-setup] New EUI64: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n\r",
        settings_eui64[0],
        settings_eui64[1],
        settings_eui64[2],
        settings_eui64[3],
        settings_eui64[4],
        settings_eui64[5],
        settings_eui64[6],
        settings_eui64[7]);
  } else {
    PRINTF("[inga-setup] Error: failed writing EUI64 to EEPROM\n");
  }
#endif /* INGA_CONF_EUI64 */
  PRINTF("Setup done. Now reboot or flash another program\n");
  PROCESS_END();
}
