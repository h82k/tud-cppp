# tud-cpp-ucincludes

These files are required in order to use the peripherals of the SK-16FX board.
Include **mb96348hs.h** in your main program to use them.

Additionally, **start.asm** may be used to customise the initialisation of the board and **vector.c** may be used to implement interrupt handling.

## Flashing without setting the mode selection switch S1
Set UART_SCANNING in **start.asm** to ON to avoid setting the mode switch to PROG before flashing the board.
Instead, flashing is also possible when the mode selection switch is set to RUN.
