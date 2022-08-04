all: main.c
	avr-gcc -mmcu=attiny24a -DF_CPU=8000000 -Wall -funsigned-char -Os -o main.elf -I. main.c bitbang_uart_tx.c
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex

flash: all
	avrdude -v -p t24 -c usbasp -U main.hex

clean:
	-rm main.elf main.hex