
ifneq (, $(shell which nix-shell 2> /dev/null))
SHELL := nix-shell
.SHELLFLAGS := --command
endif

.pio/build/digispark/firmware.hex: src/*.cpp
	platformio -f run

upload: .pio/build/digispark/firmware.hex
	micronucleus -c micronucleus --timeout 60 $<

clean:
	platformio -f run --target clean

program:
	platformio -f run --target program

uploadfs:
	platformio -f run --target uploadfs

update:
	platformio -f update
