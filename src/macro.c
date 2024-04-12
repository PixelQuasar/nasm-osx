#include <stdio.h>
#include <stdint.h>

FILE *get_stdin(void) { return stdin; }
FILE *get_stdout(void) { return stdout; }

// I/O functions easily callable from asm
// - Accept under-aligned stack
// - Return value (if any) in EAX
// - Up to three arguments in EAX, EDX, ECX
// - Preserve EBX, EBP, ESP, EDI, ESI
//
// Extends macro.c from SASM (usually /usr/share/sasm/NASM/macro.c)

#define IO_ATTR __attribute__((regparm(3),force_align_arg_pointer))

// Input facilities
// Read a 32-bit number using %d/%u/%x format, return value in EAX
IO_ATTR int32_t  io_get_dec(void);
IO_ATTR uint32_t io_get_udec(void);
IO_ATTR uint32_t io_get_hex(void);
IO_ATTR int64_t  io_get_long(void);
IO_ATTR uint64_t io_get_ulong(void);

// Read a character via getchar(), return value in EAX
IO_ATTR int32_t io_get_char(void);

// Read a string, 'buf' in EAX, 'size' in EDX
IO_ATTR void io_get_string(char *buf, int size);

// Output facilities

// Print a 32-bit number in EAX using %d/%u/%x format
IO_ATTR void io_print_dec(int32_t v);
IO_ATTR void io_print_udec(uint32_t v);
IO_ATTR void io_print_hex(uint32_t v);
IO_ATTR void io_print_long(int64_t v); // CUSTOM FUNCTION, NOT FROM SASM
IO_ATTR void io_print_ulong(uint64_t v); // CUSTOM FUNCTION, NOT FROM SASM

// Print a character in AL
IO_ATTR void io_print_char(char c);

// Print a string addressed by EAX
IO_ATTR void io_print_string(const char *s);

// Start a new line
IO_ATTR void io_newline(void);

IO_ATTR int32_t io_get_dec(void) {
	int32_t r;
	scanf("%d", &r);
	return r;
}

IO_ATTR uint32_t io_get_udec(void) {
	uint32_t r;
	scanf("%u", &r);
	return r;
}

IO_ATTR uint32_t io_get_hex(void) {
	uint32_t r;
	scanf("%x", &r);
	return r;
}

IO_ATTR int64_t io_get_long(void) {
	int64_t r;
	scanf("%lld", &r);
	return r;
}

IO_ATTR uint64_t io_get_ulong(void) {
	uint64_t r;
	scanf("%llu", &r);
	return r;
}

IO_ATTR int io_get_char(void) {
	return getchar();
}

IO_ATTR void io_get_string(char *buf, int32_t size) {
	fgets(buf, size, stdin);
}

IO_ATTR void io_print_dec(int32_t v) {
	printf("%d", v);
}

IO_ATTR void io_print_udec(uint32_t v) {
	printf("%u", v);
}

IO_ATTR void io_print_hex(uint32_t v) {
	printf("%x", v);
}

IO_ATTR void io_print_long(int64_t v) {
	printf("%lld", v);
}

IO_ATTR void io_print_ulong(uint64_t v) {
	printf("%llu", v);
}

IO_ATTR void io_print_char(char c) {
	putchar(c);
}

IO_ATTR void io_print_string(const char *s)
{
	fputs(s, stdout);
}

IO_ATTR void io_newline(void)
{
	putchar('\n');
}

__attribute__((constructor))
static void unbuffer_stdout(void)
{
	setbuf(stdout, 0);
}
