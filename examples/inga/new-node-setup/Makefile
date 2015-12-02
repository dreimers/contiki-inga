CONTIKI_PROJECT = inga-setup

TARGET=inga

# Preset default values
#EUI64 = 
#PAN_ADDR = 0x1337
PAN_ID = 0xABCD
RADIO_CHANNEL = 26
RADIO_TX_POWER = 0 

CFLAGS += -DDEBUG=1

CONTIKI = ../../..

ifndef MOTES
  $(error "MOTES undefinded. Please set to one device path")
endif

# Check environment values and set to defined default if not set
ifndef EUI64
  $(info "EUI64 is undefinded. Trying to calculate one with inga_tool")
  EUI64_FROM_USB = $(shell $(CONTIKI)/tools/inga/inga_tool/inga_tool -e -d $(MOTES) | cut -d":" -f2-)
  EUI64 = $(EUI64_FROM_USB)
  $(info "EUI64 will be set to $(EUI64)")
endif

ifndef PAN_ADDR
  $(info "PAN_ADDR is undefinded. Using last 2 bytes of EUI64($(EUI64))")
  PAN_ADDR = $(shell echo $(EUI64) | cut -d ":" -f7)
  PAN_ADDR := 0x$(PAN_ADDR)$(shell echo $(EUI64) | cut -d ":" -f8)
endif

# PAN_ADDR
ifdef PAN_ADDR
  $(info [inga-setup] PAN_ADDR will be set to $(PAN_ADDR))
  CFLAGS += -DINGA_CONF_PAN_ADDR=$(PAN_ADDR)
endif

# PANID
ifdef PAN_ID
  $(info [inga-setup] PAN_ID will be set to $(PAN_ID))
  CFLAGS += -DINGA_CONF_PAN_ID=$(PAN_ID)
endif

# RADIO CHANNEL
ifdef RADIO_CHANNEL
  $(info [inga-setup] RADIO_CHANNEL will be set to $(RADIO_CHANNEL))
  CFLAGS += -DINGA_CONF_RADIO_CHANNEL=$(RADIO_CHANNEL)
endif

# RADIO TX POWER
ifdef RADIO_TX_POWER
  $(info [inga-setup] RADIO_TX_POWER will be set to $(RADIO_TX_POWER))
  CFLAGS += -DINGA_CONF_RADIO_TX_POWER=$(RADIO_TX_POWER)
endif

# EUI64
ifdef EUI64
  CONF_EUI64 := $(shell echo $(EUI64) | sed 's/\([0-9a-fA-F]\{2\}\)/0x\1/g' | sed 's/:/,/g')
  $(info [inga-setup] EUI64 will be set to $(CONF_EUI64))
  CFLAGS += -DINGA_CONF_EUI64=$(CONF_EUI64)
endif

#$(info "CFLAGS: $(CFLAGS))

showeui64: test-single $(info [inga-setup] EUI64 calculated from USB serial number: $(EUI64_FROM_USB)) 

setup: test-single $(CONTIKI_PROJECT).upload

setup.jtag: test-single $(CONTIKI_PROJECT).jtag

setup.bang: test-single $(CONTIKI_PROJECT).bang

# tests for single MOTE
test-single: NR_OF_MOTES = $(shell echo $(MOTES) | wc -w)
test-single:
	@test ! $(NR_OF_MOTES) -eq 0 || (echo "*** At least one MOTE required. Specify with MOTES=<device>" && false)
	@test $(NR_OF_MOTES) -eq 1 || (echo "*** Only single MOTE allowed. Specify with MOTES=<device>" && false)

.FORCE:
$(OBJECTDIR)/contiki-inga-main.o: .FORCE

include $(CONTIKI)/Makefile.include
