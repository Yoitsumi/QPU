require_relative '32bit.rb'

_out_file '..\Processor\test.bin'

  lw  $_1, $_0, :vga_address
  lw  $_2, $_0, :color
  lw  $_3, $_0, :pixels_to_write
  lw  $_4, $_0, :full_alpha
  lw  $_9, $_0, :_255
  li  $_10, 0   #R
  li  $_11, 0   #G
  li  $_12, 0   #B
  add $_3, $_3, $_1
  
_ :loop
  sw  $_2, $_1, 0
  add $_1, $_1, $_0, 4
  blt $_1, $_3, :loop
  
    
  lw  $_1, $_0, :vga_address
  
  #---R---#  
  add $_10, $_10, $_0, 16
  ble $_10, $_9, :dan
  
  li  $_10, 0
  #---G---#
  add $_11, $_11, $_0, 16
  ble $_11, $_9, :dan
  
  li  $_11, 0
  #---B---#
  add $_12, $_12, $_0, 16
  ble $_12, $_9, :dan
  
  li  $_11, 0
  
_ :dan
  li   $_2, 0
  shll $_8, $_10, $_0, 16
  bor  $_2, $_2, $_8, 0
  shll $_8, $_11, $_0, 8
  bor  $_2, $_2, $_8, 0
  bor  $_2, $_2, $_12, 0
  bor $_2, $_2, $_4, 0
  b   :loop
_break
  
_ :vga_address
_dw 0x1000
_ :color
_dw 0xff000000
_ :pixels_to_write
_dw 800*600*4
_ :full_alpha
_dw 0xff000000
_ :_255
_dw 0xff

_end