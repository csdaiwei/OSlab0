# 中断和异常处理函数的入口
# 中断处理函数会在IDT中为相应的中断/异常设置处理程序
# 中断/异常的行为参见i386手册
.globl vec0; vec0: pushl $0; jmp asm_do_irq
.globl vec1; vec1: pushl $1; jmp asm_do_irq
.globl vec2; vec2: pushl $2; jmp asm_do_irq
.globl vec3; vec3: pushl $3; jmp asm_do_irq
.globl vec4; vec4: pushl $4; jmp asm_do_irq
.globl vec5; vec5: pushl $5; jmp asm_do_irq
.globl vec6; vec6: pushl $6; jmp asm_do_irq
.globl vec7; vec7: pushl $7; jmp asm_do_irq
.globl vec8; vec8: pushl $8; jmp asm_do_irq
.globl vec9; vec9: pushl $9; jmp asm_do_irq
.globl vec10; vec10: pushl $10; jmp asm_do_irq
.globl vec11; vec11: pushl $11; jmp asm_do_irq
.globl vec12; vec12: pushl $12; jmp asm_do_irq
.globl vec13; vec13: pushl $13; jmp asm_do_irq

.globl irq0; irq0: pushl $1000; jmp asm_do_irq  #0号中断，将1000放到栈中，作为时钟中断的标志（中断号）
.globl irq1; irq1: pushl $1001; jmp asm_do_irq  #1号中断，将1001放到栈中，作为键盘中断的标志（中断号）

.globl irq_empty; irq_empty: pushl $-1; jmp asm_do_irq

# ！调用C编写的中断处理程序(见irq/irq_handle.c)！
.globl asm_do_irq
asm_do_irq:
	pushal						#堆栈指令，保护所有r32(8个通用寄存器)，到此已将中断之前的现场完全保存好了。

	pushl %esp					#将原esp位置的内容赋值到当前esp( = 原esp-4)位置，作为call irq_handle的参数。其实									是指向先前栈位置的指针，可以让irq_handle找到指针位置的8个GR和1个中断号
	call irq_handle

	addl $4, %esp				#esp+4,即恢复堆栈指针位置

	popal						#堆栈指令，恢复所有r32，恢复中断现场
	addl $4, %esp
	iret						#interrupt return
