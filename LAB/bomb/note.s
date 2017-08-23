400e32:   e8 67 06 00 00          callq  40149e <read_line>
400e37:   48 89 c7                mov    %rax,%rdi
400e3a:   e8 a1 00 00 00          callq  400ee0 <phase_1>

read_line save the address of input in %rax,then copy it to %rdi,as the first argument of phase_1.


000000000040145c <read_six_numbers>:
  40145c:   48 83 ec 18             sub    $0x18,%rsp
  401460:   48 89 f2                mov    %rsi,%rdx
  401463:   48 8d 4e 04             lea    0x4(%rsi),%rcx
  401467:   48 8d 46 14             lea    0x14(%rsi),%rax
  40146b:   48 89 44 24 08          mov    %rax,0x8(%rsp)
  401470:   48 8d 46 10             lea    0x10(%rsi),%rax
  401474:   48 89 04 24             mov    %rax,(%rsp)
  401478:   4c 8d 4e 0c             lea    0xc(%rsi),%r9
  40147c:   4c 8d 46 08             lea    0x8(%rsi),%r8
  401480:   be c3 25 40 00          mov    $0x4025c3,%esi
  401485:   b8 00 00 00 00          mov    $0x0,%eax
  40148a:   e8 61 f7 ff ff          callq  400bf0 <__isoc99_sscanf@plt>
  40148f:   83 f8 05                cmp    $0x5,%eax
  401492:   7f 05                   jg     401499 <read_six_numbers+0x3d>
  401494:   e8 a1 ff ff ff          callq  40143a <explode_bomb>
  401499:   48 83 c4 18             add    $0x18,%rsp
  40149d:   c3                      retq  