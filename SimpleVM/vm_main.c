#include <stdio.h>
#include <defs.h>

int __cdecl decrypt(signed int a1, char a2);
int __cdecl dereference();
int __cdecl save_EAX();
int __cdecl pop();
int __cdecl vm_set_ip_to_cmd_plus_sp();
int __cdecl vm_xor();
int __cdecl vm_cmp();
int __cdecl vm_save_to_mem();
int __cdecl vm_jne();
int __cdecl vm_jmp();
int __cdecl vm_what_the_hell();
signed int __cdecl vm_start();

char vm[] = {0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x45, 0x45, 0x0C4, 0x0C4, 0x4, 0x4, 0x65, 0x44, 0x0E4, 0x8, 0x0C4, 0x4, 0x0E4, 0x44, 0x0E4, 0x25, 0x0E4, 0x4, 0x0E4, 0x25, 0x44, 0x44, 0x0E4, 0x0C8, 0x0C4, 0x24, 0x0E4, 0x44, 0x0E4, 0x44, 0x0E4, 0x24, 0x0E4, 0x25, 0x44, 0x44, 0x0E4, 0x0A6, 0x0C4, 0x44, 0x0E4, 0x44, 0x0E4, 0x0C0, 0x0E4, 0x44, 0x0E4, 0x25, 0x44, 0x44, 0x0E4, 0x0E4, 0x0C4, 0x64, 0x0E4, 0x44, 0x0E4, 0x0A1, 0x0E4, 0x64, 0x0E4, 0x25, 0x44, 0x44, 0x0E4, 0x8D, 0x0C4, 0x84, 0x0E4, 0x44, 0x0E4, 0x40, 0x0E4, 0x84, 0x0E4, 0x25, 0x44, 0x44, 0x0E4, 0x68, 0x0C4, 0x0A4, 0x0E4, 0x44, 0x0E4, 0x0E4, 0x0E4, 0x0A4, 0x0E4, 0x25, 0x44, 0x44, 0x0E4, 0x0B, 0x0C4, 0x0C4, 0x0E4, 0x44, 0x0E4, 0x6, 0x0E4, 0x0C4, 0x0E4, 0x25, 0x44, 0x44, 0x4, 0x24, 0x65, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4};

#define vm_zf (vm[8])
#define vm_ip (vm[9])
#define vm_sp (vm[10])

int vm_ECX;
int pop_;
int vm_EBX;
int vm_EAX;

void main()
{
	int i;
	char KEY[7+1] = "id3*ndh";

	for ( i = 0; i <= 199; ++i )
		vm[i] = decrypt((unsigned __int8)vm[i], 3);

	for ( i = 0; i <= 199; ++i )
		vm[i] ^= 0x20u;

	vm[0] = KEY[0];
	vm[1] = KEY[1];
	vm[2] = KEY[2];
	vm[3] = KEY[3];
	vm[4] = KEY[4];
	vm[5] = KEY[5];
	vm[6] = KEY[6];

	for ( i = 0; i <= 199; ++i )
		vm[i] ^= 0x10u;

	vm_start();
}

int __cdecl decrypt(signed int a1, char a2)
{
	return (a1 << a2) | (a1 >> (8 - a2));
}

int __cdecl dereference()
{
	unsigned __int8 v0; // ST0F_1@1
	int result; // eax@1

	v0 = vm[pop_] ^ 0x10;
	result = v0;
	pop_ = v0;
	return result;
}

int __cdecl save_EAX()
{
	int result; // eax@1

	result = pop_;
	vm[pop_] = vm_EAX ^ 0x10;
	return result;
}

int __cdecl pop()
{
	int result; // eax@1

	pop_ = (unsigned __int8)(vm[(unsigned __int8)(vm_ip ^ 0x10)] ^ 0x10);
	result = (unsigned __int8)((vm_ip ^ 0x10) + 1) ^ 0x10;
	vm_ip = ((vm_ip ^ 0x10) + 1) ^ 0x10;
	return result;
}

int __cdecl vm_set_ip_to_cmd_plus_sp()
{
	int result; // eax@1

	result = (unsigned __int8)((_BYTE)pop_ + (vm_sp ^ 0x10)) ^ 0x10;
	vm_ip = ((_BYTE)pop_ + (vm_sp ^ 0x10)) ^ 0x10;
	return result;
}

int __cdecl vm_xor()
{
	vm_EAX = pop_;
	vm_ECX = vm_EBX;
	pop();
	printf("[%02x]=%02x, ", pop_, vm[pop_] ^ 0x10);
	vm_ECX = pop_;
	pop();
	printf("[%02x]=%02x", pop_, vm[pop_] ^ 0x10);
	dereference();
	vm_EBX = pop_;
	pop_ = vm_ECX;
	dereference();
	pop_ ^= vm_EBX;
	vm_EAX = pop_;
	pop_ = vm_ECX;
	return save_EAX();
}

int __cdecl vm_cmp()
{
	pop();
	printf("[%02x]=%02x, ", pop_, vm[pop_] ^ 0x10);
	dereference();
	vm_EAX = pop_;
	pop();
	printf("[%02x]=%02x", pop_, vm[pop_] ^ 0x10);
	dereference();

	vm_EBX = pop_;
	vm_EAX = vm_EAX == vm_EBX;
	pop_ = 8;
	return save_EAX();
}

int __cdecl vm_save_to_mem()
{ // mov [op1], op2
	pop();
	printf("[%02x]=%02x, ", pop_, vm[pop_] ^ 0x10);
	vm_EAX = pop_;
	pop();
	printf("%02x", pop_);
	vm_EBX = pop_;
	pop_ = vm_EAX;
	vm_EAX = vm_EBX;
	return save_EAX();
}

int __cdecl vm_jne()
{
	int result; // eax@1

	vm_EAX = pop_;
	pop();
	printf("%02x", pop_);
	vm_EAX = pop_;                              // EAX = op1
	pop_ = 8;
	dereference();                   // cmd = zf
	result = pop_;
	//if ( !pop_ )                                // if !zf
	//{
	//	pop_ = vm_EAX;
	//	result = vm_set_ip_to_cmd_plus_sp();
	//}
	return result;
}

int __cdecl vm_jmp()
{
	pop();
	printf("%02x", pop_);
	return vm_set_ip_to_cmd_plus_sp();
}

//----- (08048C22) --------------------------------------------------------
int __cdecl vm_what_the_hell()
{
	int result; // eax@1

	pop_ = 0;
	dereference();                   // EAX = [0]
	vm_EAX = pop_;
	pop_ = 1;
	dereference();
	vm_EBX = pop_;                              // EBX = [1]
	pop_ = vm_EAX;                              // cmd = [0]
	result = vm_EBX;
	vm_EAX = vm_EBX;                              // EAX = [1]
	return result;
}
// 804B190: using guessed type int pop_;
// 804B194: using guessed type int vm_EBX;
// 804B198: using guessed type int vm_EAX;

//----- (08048C6D) --------------------------------------------------------
signed int __cdecl vm_start()
{
	signed int result; // eax@7

	while ( 2 )
	{
		printf("\n");
		pop();
		switch ( pop_ )
		{
		case 2:
			printf("0x%02x : mov ", (vm_ip^0x10)-1);
			vm_save_to_mem();                       // mov [op1], op2
			continue;
		case 6:
			printf("0x%02x : xor ", (vm_ip^0x10)-1);
			vm_xor();                     // mov [op1], op1
			continue;
		case 7:
			printf("0x%02x : cmp ", (vm_ip^0x10)-1);
			vm_cmp();                               // cmp [op1], [op2]
			continue;
		case 9:
			printf("0x%02x : jne sp+", (vm_ip^0x10)-1);
			vm_jne();                               // jne op+sp
			continue;
		case 10:
			printf("0x%02x : jmp sp+", (vm_ip^0x10)-1);
			vm_jmp();                               // jmp op+sp
			continue;
		case 11:
			printf("0x%02x : mistery", (vm_ip^0x10)-1);
			vm_what_the_hell();                     // ???
			result = 1;
			break;
		default:
			result = 0;
			break;
		}
		break;
	}
	return result;
}