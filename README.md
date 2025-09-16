# CCVM
My own custom virtual machine, bytecode format, and assembler

The virtual machine is named CCVM (code community virtual machine)
This VM runs an executable bytecode format named CCB (Code Community Bytecode)
This bytecode can be assembled from CCA (Code Community Assembly)

## Instruction map

### Mov instructions
 - 0x00 - MOV reg int
 - 0x01 - MOV reg reg
 - 0x02 - MOV mem int
 - 0x03 - MOV mem mem
 - 0x04 - MOV reg mem
 - 0x05 - MOV mem reg
 - 0x06 - PUSH int
 - 0x07 - PUSH reg
 - 0x08 - PUSH mem
 - 0x09 - DUP
 - 0x0A - POP reg
 - 0x0B - POP mem
 - 0x0C - POP

### Other instructions
 - 0xF0 - STOP
 - 0xFF - INT