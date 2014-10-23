require_relative '32bit.rb'

_out_file '..\Processor\test.bin'

  lw $_1, $_0, :writeport
  li $_2, :data
  
_ :loop
  #check, if current char is zero  
  lb  $_3, $_2, 0 # current char in $_3
  beq $_3, $_0, :die
  
  #increment the data pointer
  add $_2, $_2, $_0, 1
  
  #send the character
  sb  $_3, $_1, 0
  
  #wait until the character has been displayed
_ :wait_char
  lb  $_4, $_1, 0
  bne $_4, $_0, :wait_char
  
  #loop
  j   :loop  
  
_ :die
_break

_ :writeport
  _dw 0xb000_0000
_ :data
  _db ?H.ord
  _db ?e.ord
  _db ?l.ord
  _db ?l.ord
  _db ?o.ord
  _db ' '.ord
  _db ?w.ord
  _db ?o.ord
  _db ?r.ord
  _db ?l.ord
  _db ?d.ord
  _db ?!.ord
  _db ?\n.ord
  _db 0
  
_end