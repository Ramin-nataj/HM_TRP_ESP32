# HM_TRP_ESP32
Arduino code communication to HM-TRP RF Module By ESP32

There are three hardware supported serial interfaces on the ESP32 known as UART0, UART1 and UART2. Like all peripherals, the pins for the UARTs can be logically mapped to any of the available pins on the ESP32. However, the UARTs can also have direct access which marginally improves performance. The pin mapping table for this hardware assistance is as follows.

UART	RX IO	TX IO	CTS	RTS
UART0	GPIO3	GPIO1	N/A	N/A
UART1	GPIO9	GPIO10	GPIO6	GPIO11
UART2	GPIO16	GPIO17	GPIO8	GPIO7


![images](https://github.com/Ramin-nataj/HM_TRP_ESP32/assets/42840850/4daa3375-4654-4105-a3fd-4979274bd11a)
