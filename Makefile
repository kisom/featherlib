BOARD :=	adafruit_feather_m0
FIRMWARE :=	.pioenvs/$(BOARD)/firmware.bin

PIO :=	pio run -e $(BOARD)

$(FIRMWARE):
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

.PHONY:
cloc:
	cloc include lib src
