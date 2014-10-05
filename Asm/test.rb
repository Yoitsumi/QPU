require_relative '32bit.rb'

_out_file 'C:\Users\Kamil\Documents\visual studio 2013\Projects\ConsoleApplication2\ConsoleApplication2\test.bin'

  jal :subroutine
  _break
  
_ :subroutine
  li $_1, 50
  jr $ra
  
_end