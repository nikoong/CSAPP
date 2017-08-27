
4_4.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <rsum>:
   0:	b8 00 00 00 00       	mov    $0x0,%eax
   5:	48 85 f6             	test   %rsi,%rsi
   8:	7e 15                	jle    1f <rsum+0x1f>
   a:	53                   	push   %rbx
   b:	48 89 fb             	mov    %rdi,%rbx
   e:	48 83 ee 01          	sub    $0x1,%rsi
  12:	48 8d 7f 08          	lea    0x8(%rdi),%rdi
  16:	e8 00 00 00 00       	callq  1b <rsum+0x1b>
  1b:	48 03 03             	add    (%rbx),%rax
  1e:	5b                   	pop    %rbx
  1f:	f3 c3                	repz retq 
