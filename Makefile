BOARD :=	adafruit_feather_m0
FIRMWARE :=	.pioenvs/$(BOARD)/firmware.bin
SOURCES :=					\
		include/feather/board.h		\
		include/feather/button.h	\
		include/feather/feather_m0.h	\
		include/feather/feather_m4.h	\
		include/feather/trigger.h	\
		include/feather/util.h		\
		include/feather/wing/adalogger.h\
		include/feather/wing/gps.h	\
		include/feather/wing/oled.h	\
		include/feather/wing/rfm95.h	\
		include/feather/wing/test.h	\
		include/feather/wing/wing.h	\
		src/button.cc			\
		src/feather_m0.cc		\
		src/feather_m4.cc		\
		src/trigger.cc			\
		src/util.cc			\
		src/wing_adalogger.cc		\
		src/wing.cc			\
		src/wing_gps.cc			\
		src/wing_oled.cc		\
		src/wing_rfm95.cc		\
		src/wing_test.cc

PIO :=	pio run -e $(BOARD)

$(FIRMWARE): $(SOURCES)
	$(PIO)

PHONY: all
all: $(FIRMWARE)

.PHONY: upload
upload: $(FIRMWARE)
	$(PIO) -t upload

.PHONY: monitor
monitor:
	$(PIO) -t monitor

.PHONY: deploy
deploy: $(FIRMWARE)
	$(PIO) -t upload && sleep 0.5 && $(PIO) -t monitor

.PHONY: clean
clean:
	$(PIO) -t clean

.PHONY: cloc
cloc:
	cloc include lib src

.PHONY: install
install:
	pio lib --global install $(PWD)

.PHONY: uninstall
uninstall:
	pio lib --global uninstall $(PWD)

.PHONY: test
test:
	(cd examples/calamity && pio run)
	(cd examples/lorabcn && pio run)
	(cd examples/loraspy && pio run)
	(cd examples/rtcgps && pio run)
