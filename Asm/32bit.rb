$OPCODE_MASK       = 0xf8000000;
$OPCODE_SHIFT      = 27;

$FUNCT_RRRI8_MASK  = 0x07800000;
$FUNCT_RRRI8_SHIFT = 23;
$DEST_RRRI8_MASK   = 0x007c0000;
$DEST_RRRI8_SHIFT  = 18;
$A_RRRI8_MASK      = 0x0003e000;
$A_RRRI8_SHIFT     = 13;
$B_RRRI8_MASK      = 0x00001f00;
$B_RRRI8_SHIFT     = 8;
$IMM_RRRI8_MASK    = 0x000000ff;
$IMM_RRRI8_SHIFT   = 0;

$IPR_MEM_MASK      = 0x04000000;
$DEST_MEM_MASK     = 0x03e00000;
$DEST_MEM_SHIFT    = 21;
$A_MEM_MASK        = 0x001f0000;
$A_MEM_SHIFT       = 16;
$IMM_MEM_MASK      = 0x0000ffff;
$IMM_MEM_SHIFT     = 0;

$F_B_MASK          = 0x07800000;
$F_B_SHIFT         = 23;
$A_B_MASK          = 0x007c0000;
$A_B_SHIFT         = 18;
$B_B_MASK          = 0x0003e000;
$B_B_SHIFT         = 13;
$IMM_B_MASK        = 0x00001fff;
$IMM_B_SHIFT       = 0;

$ADDR_J_MASK       = 0x07ffffff;
$ADDR_J_SHIFT      = 0;

$FUNCT_RR_MASK     = 0x07f00000;
$FUNCT_RR_SHIFT    = 20;
$AUX_RR_MASK       = 0x000ffc00;
$AUX_RR_SHIFT      = 10;
$A_RR_MASK         = 0x000003e0;
$A_RR_SHIFT        = 5;
$B_RR_MASK         = 0x0000001f;
$B_RR_SHIFT        = 0;


$OP_ARITH = 0x00;
$OP_LOGIC = 0x01;
$OP_LB    = 0x02;
$OP_LH    = 0x03;
$OP_LW    = 0x04;
$OP_SB    = 0x06;
$OP_SH    = 0x07;
$OP_SW    = 0x08;
$OP_B     = 0x0a;
$OP_J     = 0x0b;
$OP_JAL   = 0x0c;
$OP_RR    = 0x1f;


$ARITH_ADD  = 0x0;
$ARITH_SUB  = 0x1;
$ARITH_MUL  = 0x2;
$ARITH_DIV  = 0x3;
$ARITH_MULU = 0x6;
$ARITH_DIVU = 0x7;

$LOGIC_SHLL = 0x0;
$LOGIC_SHRL = 0x1;
$LOGIC_SHRA = 0x2;
$LOGIC_OR   = 0x4;
$LOGIC_AND  = 0x5;
$LOGIC_XOR  = 0x6;
$LOGIC_NOR  = 0x8;
$LOGIC_NAND = 0x9;
$LOGIC_XNOR = 0xa;

$B_EQ       = 0x0;
$B_NE       = 0x1;
$B_LT       = 0x2;
$B_LE       = 0x3;


$RR_JALR    = 0x01;

$labels = {}
$program = []
$pc = 0

$_0 = 0
$_1 = 1
$_2 = 2
$_3 = 3
$_4 = 4
$_5 = 5
$_6 = 6
$_7 = 7
$_8 = 8
$_9 = 9
$_10 = 10
$_11 = 11
$_12 = 12
$_13 = 13
$_14 = 14
$_15 = 15
$_16 = 16
$_17 = 17
$_18 = 18
$_19 = 19
$_20 = 20
$_21 = 21
$_22 = 22
$_23 = 23
$_24 = 24
$_25 = 25
$_26 = 26
$_27 = 27
$_28 = 28
$_29 = 29
$_30 = 30
$_31 = 31

$ra = 31

class ConsoleWriter
  
  def write i, size=4
    puts "0x#{i.to_s(16)}"
  end
  
end

class FileWriter
  
  attr_reader :file
  
  def initialize path
    @file = File.open path, 'wb'
  end
  
  def write i, size=4
    puts "0x#{i.to_s(16)}"
    @file.write case size
      when 1 then [i].pack('C')
      when 2 then [i].pack('S') 
      when 4 then [i].pack('L')
    end      
  end
  
end

$out = ConsoleWriter.new

def __flush
  loop do
    break if $program.size == 0
    break unless $program[0].ready?
    if $program[0].respond_to? :write
      $program[0].write      
    else
      $out.write $program[0].compile
    end
    $program.delete_at(0)
  end
end

def _out_file path
  $out = FileWriter.new path
end

def _end
  __flush
  if $out.is_a? FileWriter
    $out.file.flush
    $out.file.close
  end
  puts 'finished'
end

def _db dat
  $program << Dat.new(dat, 1)
  $pc += 1
end
def _dh dat
  $program << Dat.new(dat, 2)
  $pc += 2
end
def _dw dat
  $program << Dat.new(dat, 4);
  $pc += 4
end
def _break
  _dw 0xffffffff
end

def _l label
  $labels[label] = $pc;
end
def _ label
  _l label
end

class RRRI8
  
  def initialize op, f, d, a, b, imm    
    @op = op
    @f = f
    @d = d
    @a = a
    @b = b
    @imm = imm
  end
  
  def ready?
    @imm = $labels[@imm] if $labels[@imm]
    @imm.is_a? Fixnum
  end
  
  def compile    
    (@op << $OPCODE_SHIFT) |
    (@f  << $FUNCT_RRRI8_SHIFT) |
    (@d  << $DEST_RRRI8_SHIFT) |
    (@a  << $A_RRRI8_SHIFT) |
    (@b  << $B_RRRI8_SHIFT) |
    ((@imm << $IMM_RRRI8_SHIFT) & 0xff)
  end
  
end
class MEM
  
  def initialize op, pcr, d, a, imm
    @op = op
    @pcr = pcr
    @d = d
    @a = a
    @imm = imm
  end
  
  def ready?
    @imm = $labels[@imm] if $labels[@imm]
    @imm.is_a? Fixnum
  end
  
  def compile
    (@op << $OPCODE_SHIFT) |
    (@pcr? $IPR_MEM_MASK:0) |
    (@d  << $DEST_MEM_SHIFT)|
    (@a  << $A_MEM_SHIFT)   |
    ((@imm & 0xffff) << $IMM_MEM_SHIFT)
  end
    
end
class B
  
  def initialize pc, op, f, a, b, imm
    @pc = pc
    @op = op
    @f = f
    @a = a
    @b = b
    @imm = imm
  end
  
  def ready?
    @imm =  $labels[@imm] - (@pc+4) if $labels[@imm]
    @imm.is_a? Fixnum
  end
  
  def compile
    (@op << $OPCODE_SHIFT) |
    (@f  << $F_B_SHIFT) |
    (@a  << $A_B_SHIFT) |
    (@b  << $B_B_SHIFT) |
    ((@imm&0x1fff)<< $IMM_B_SHIFT)
  end
  
end
class J
  
  def initialize op, addr
    @op = op
    @addr = addr
  end
  
  def ready?
    @addr = $labels[@addr]>>2 if $labels[@addr]
    @addr.is_a? Fixnum
  end
  
  def compile
    (@op << $OPCODE_SHIFT) |
    ((@addr << $ADDR_J_SHIFT) & $ADDR_J_MASK)
  end
  
end
class RR
  
  def initialize op, f, aux, a, b
    @op = op
    @f = f
    @aux = aux
    @a = a
    @b = b    
  end
  
  def ready?
    true
  end
  
  def compile
    (@op << $OPCODE_SHIFT) |
    (@f  << $FUNCT_RR_SHIFT) |
    (@aux << $AUX_RR_SHIFT) |
    (@a  << $A_RR_SHIFT) |
    (@b  << $B_RR_SHIFT)
  end
  
end

class Dat
  
  def initialize dat, size
    @size = size
    @dat = dat
  end
  
  def ready?
    true
  end
  
  def write
    $out.write @dat, @size
  end
  
end

def add  d, a, b, imm=0
  $program << RRRI8.new($OP_ARITH, $ARITH_ADD, d, a, b, imm)
  $pc += 4
  __flush
end
def sub  d, a, b, imm=0
  $program << RRRI8.new($OP_ARITH, $ARITH_SUB, d, a, b, imm)
  $pc += 4
  __flush
end
def mul  d, a, b, imm=0
  $program << RRRI8.new($OP_ARITH, $ARITH_MUL, d, a, b, imm)
  $pc += 4
  __flush
end
def div  d, a, b, imm=0
  $program << RRRI8.new($OP_ARITH, $ARITH_DIV, d, a, b, imm)
  $pc += 4
  __flush
end
def mulu d, a, b, imm=0
  $program << RRRI8.new($OP_ARITH, $ARITH_MULU, d, a, b, imm)
  $pc += 4
  __flush
end
def divu d, a, b, imm=0
  $program << RRRI8.new($OP_ARITH, $ARITH_DIVU, d, a, b, imm)
  $pc += 4
  __flush
end


def li d, imm
  case imm
  when 0
    mov d, $_0
  when Symbol
    add d, $_0, $_0, imm
  when (-128..127)
    add d, $_0, $_0, imm
  end
end
def mov d, s
  add d, s, $_0
end

def shll d, a, b, imm=0
  $program << RRRI8.new($OP_LOGIC, $LOGIC_SHLL, d, a, b, imm)
  $pc += 4
  __flush
end
def shrl d, a, b, imm=0
  $program << RRRI8.new($OP_LOGIC, $LOGIC_SHRL, d, a, b, imm)
  $pc += 4
  __flush
end
def shra d, a, b, imm=0
  $program << RRRI8.new($OP_LOGIC, $LOGIC_SHRA, d, a, b, imm)
  $pc += 4
  __flush
end
def or d, a, b, imm=0
  $program << RRRI8.new($OP_LOGIC, $LOGIC_OR, d, a, b, imm)
  $pc += 4
  __flush
end
def and d, a, b, imm=0
  $program << RRRI8.new($OP_LOGIC, $LOGIC_AND, d, a, b, imm)
  $pc += 4
  __flush
end
def xor d, a, b, imm=0
  $program << RRRI8.new($OP_LOGIC, $LOGIC_XOR, d, a, b, imm)
  $pc += 4
  __flush
end
def nor d, a, b, imm=0
  $program << RRRI8.new($OP_LOGIC, $LOGIC_NOR, d, a, b, imm)
  $pc += 4
  __flush
end
def nand d, a, b, imm=0
  $program << RRRI8.new($OP_LOGIC, $LOGIC_NAND, d, a, b, imm)
  $pc += 4
  __flush
end
def xnor d, a, b, imm=0
  $program << RRRI8.new($OP_LOGIC, $LOGIC_SHRA, d, a, b, imm)
  $pc += 4
  __flush
end

def not d, a
  nor d, a, $_0, 0 
end

def lb d, a, imm
  $program << MEM.new($OP_LB, false, d, a, imm)
  $pc += 4
  __flush
end
def lbr d, a, imm
  $program << MEM.new($OP_LB, true, d, a, imm)
  $pc += 4
  __flush
end
def lh d, a, imm
  $program << MEM.new($OP_LH, false, d, a, imm)
  $pc += 4
  __flush
end
def lhr d, a, imm
  $program << MEM.new($OP_LH, true, d, a, imm)
  $pc += 4
  __flush
end
def lw d, a, imm
  $program << MEM.new($OP_LW, false, d, a, imm)
  $pc += 4
  __flush
end
def lwr d, a, imm
  $program << MEM.new($OP_LW, true, d, a, imm)
  $pc += 4
  __flush
end

def sb d, a, imm
  $program << MEM.new($OP_SB, false, d, a, imm)
  $pc += 4
  __flush
end
def sbr d, a, imm
  $program << MEM.new($OP_SB, true, d, a, imm)
  $pc += 4
  __flush
end
def sh d, a, imm
  $program << MEM.new($OP_SH, false, d, a, imm)
  $pc += 4
  __flush
end
def shr d, a, imm
  $program << MEM.new($OP_SH, true, d, a, imm)
  $pc += 4
  __flush
end
def sw d, a, imm
  $program << MEM.new($OP_SW, false, d, a, imm)
  $pc += 4
  __flush
end
def swr d, a, imm
  $program << MEM.new($OP_SW, true, d, a, imm)
  $pc += 4
  __flush
end

def beq a, b, imm
  $program << B.new($pc, $OP_B, $B_EQ, a, b, imm)
  puts $OP_B
  $pc += 4
  __flush
end
def bne a, b, imm
  $program << B.new($pc, $OP_B, $B_NE, a, b, imm)
  $pc += 4
  __flush
end
def blt a, b, imm
  $program << B.new($pc, $OP_B, $B_LT, a, b, imm)
  $pc += 4
  __flush
end
def ble a, b, imm
  $program << B.new($pc, $OP_B, $B_LE, a, b, imm)
  $pc += 4
  __flush
end

def b imm
  beq $_0, $_0, imm
end
def bgt a, b, imm
  blt b, a, imm
end
def bge a, b, imm
  ble b, a, imm
end

def j addr
  $program << J.new($OP_J, addr)
  $pc+=4
  __flush
end
def jal addr
  $program << J.new($OP_JAL, addr)
  $pc+=4
  __flush
end

def jalr d, r=$ra
  $program << RR.new($OP_RR, $RR_JALR, 0, d, r)
  $pc+=4
  __flush
end

def jr d
  jalr d, $_0
end