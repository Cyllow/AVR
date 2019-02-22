CC = iccavr
LIB = ilibw
CFLAGS =  -ID:\ICCV7 -Ifor -IAVR\include -e -D__ICC_VERSION=722 -DATMega16  -l -g -MLongJump -MHasMul -MEnhanced -Wf-const_is_flash -DCONST="" 
ASFLAGS = $(CFLAGS) 
LFLAGS =  -LD:\ICCV7 -Lfor -LAVR\lib -g -e:0x4000 -ucrtatmega.o -bfunc_lit:0x54.0x4000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:30 -beeprom:0.512 -fihx_coff -S2
FILES = 3310LCD.o LCD.o chinese_12x12.o 

AIRCRAFTWAR:	$(FILES)
	$(CC) -o AIRCRAFTWAR $(LFLAGS) @AIRCRAFTWAR.lk   -lcatmega
3310LCD.o: "D:\ICCV7 for AVR\include\iom16v.h" "D:\ICCV7 for AVR\include\macros.h" "D:\ICCV7 for AVR\include\AVRdef.h" .\ASCII_6x8.h .\3310LCD.h .\chinese_12x12.h
3310LCD.o:	3310LCD.c
	$(CC) -c $(CFLAGS) 3310LCD.c
LCD.o: "D:\ICCV7 for AVR\include\iom16v.h" "D:\ICCV7 for AVR\include\macros.h" "D:\ICCV7 for AVR\include\AVRdef.h" .\3310LCD.h
LCD.o:	LCD.c
	$(CC) -c $(CFLAGS) LCD.c
chinese_12x12.o: .\chinese_12x12.h
chinese_12x12.o:	chinese_12x12.c
	$(CC) -c $(CFLAGS) chinese_12x12.c
