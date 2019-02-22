NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   0054   091D =   2333. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __lit_start
       0054  _font6x8
       027C  _music1
       0470  _music2
       06CC  _chinese_12_len
       06CD  _chinese_12
       0971  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0971   0101 =    257. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0971  __idata_start
       0A72  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0A72   1D6A =   7530. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0539  __start
       0539  __text_start
       055B  _exit
       055C  _delayus
       0569  _LCDInit
       0588  _LCDFull
       059F  _LCD_set_XY
       05AE  _LCD_write_char
       05C9  _LCD_write_english_string
       05DE  _LCD_write_byte
       05E9  _LCD_WriteCHchar
       060D  _LCD_DispCHstr
       0651  _timer1_init
       0654  _timer1_compa_isr
       082A  _delay_ms
       0839  _read_key
       08A1  _HC595_send_byte
       08BB  _port_init
       08D3  _timer0_init
       08DC  _timer0_ovf_isr
       09A5  _uart0_init
       09B0  _spi_init
       09B4  _init_devices
       09C4  _UARTSend
       09C8  _plane_left_move
       0A11  _plane_right_move
       0A58  _plane_is_die
       0A9D  _game_over
       0ACA  _main_menu
       0AF0  _sel1_menu
       0AFE  _sel1_menu_work
       0BD0  _sel2_menu
       0BE6  _sel2_menu_work
       0C63  _is_has_bullet
       0C6F  _plane_bullet_move
       0CB1  _plane_bullet_want_die
       100F  _sel3_menu
       103D  _sel3_menu_work
       115D  _main
       11CA  push_arg4
       11CC  push_arg2
       11CF  mod8u
       11D1  div8u
       11D2  xdiv8u
       11E7  empy16s
       11F7  pop_xgsetF0FC
       1202  push_xgsetF0FC
       1204  push_xgset30FC
       1206  push_xgset00FC
       1208  push_xgset003C
       120D  push_xgset300C
       1212  pop_xgset300C
       1217  push_xgsetF000
       121C  pop_xgsetF000
       1221  push_xgsetF00C
       1228  pop_xgsetF00C
       122F  push_xgset303C
       1236  pop_xgset303C
       123D  push_xgsetF03C
       1246  pop_xgsetF03C
       124F  neg32
       1258  lpm32
       126C  lsl8
       1272  fpint
       12A4  uint2fp
       12A6  int2fp
       12AF  ulong2fp
       12B1  long2fp
       12C8  fpdiv1
       12D1  fpdiv2
       12DB  fpdiv1x
       12E7  fpdiv2x
       1362  unpacks
       136A  tstR16_R19
       1372  unpacku
       138B  normalize_and_pack
       13C0  pack
       13D0  saveFPRegs
       13DF  restoreFPRegs
       13EE  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0101 =    257. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __data_start
       0060  _t
       0072  _d
       007B  _note_n
       007C  _int_n
       007E  _sound_flag
       007F  _flag
       0080  _music_sel
       0081  _led_7
       008F  _disp_buff_min_number
       0090  _disp_buff_sec_number
       0091  _disp_buff
       0095  _post
       0096  _time_10ms_count
       0097  _time_10ms_ok
       0098  _time_300ms_count
       0099  _time_300ms_ok
       009A  _time_1s_count
       009C  _time_1s_ok
       009D  _isflash
       009E  _flash_count
       009F  _layout0
       00A1  _layout1
       00A3  _layout2
       00A5  _layout3
       00A7  _layout4
       00A9  _layout5
       00AB  _plane_x
       00AC  _plane_y
       00AD  _plane_bullet_x
       00AE  _plane_bullet_y
       00AF  LCD.c:key_state
       0161  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0161   0001 =      1. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0161  __bss_start
       0161  LCD.c:key_time
       0162  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0028 =     40. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

D:\ICCV7 for AVR\lib\crtatmega.o	[ crtatmega.s ]
3310LCD.o	[ _3310LCD.c ]
LCD.o	[ LCD.c ]
chinese_12x12.o	[ chinese_12x12.c ]
<library>	[ asave.s, div8u.s, emul16s.s, gpop5.s, gpush.s, gpushx.s, gpushy.s, gpushz.s, gpusha.s, gpushb.s, lneg.s ]
[ lpm32.s, lsl8.s, fpint.s, int2fp.s, fpdiv_new.s, fputil.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x1e

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:0.512

