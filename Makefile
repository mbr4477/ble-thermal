TARGET := xenon

upload: compile
	particle usb dfu
	particle flash --usb firmware.bin

compile:
	particle compile $(TARGET) . --saveTo firmware.bin