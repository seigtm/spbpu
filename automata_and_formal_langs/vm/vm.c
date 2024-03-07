#include <stdio.h>
#include <stdlib.h>
#include "vm.h"

void milan_error();

command vm_program[MAX_PROGRAM_SIZE];

int vm_memory[MAX_MEMORY_SIZE];
int vm_stack[MAX_STACK_SIZE];

unsigned int vm_stack_pointer = 0;
unsigned int vm_command_pointer = 0;

opcode_info opcodes_table[] = {
        {"NOP",      0},
        {"STOP",     0},
        {"LOAD",     1},
        {"STORE",    1},
        {"BLOAD",    1},
        {"BSTORE",   1},
        {"PUSH",     1},
        {"POP",      0},
        {"DUP",      0},
        {"INVERT",   0},
        {"ADD",      0},
        {"SUB",      0},
        {"MULT",     0},
        {"DIV",      0},
        {"COMPARE",  1},
        {"JUMP",     1},
        {"JUMP_YES", 1},
        {"JUMP_NO",  1},
        {"INPUT",    0},
        {"PRINT",    0}
};

int opcodes_table_size = sizeof(opcodes_table) / sizeof(opcode_info);

typedef enum {
        BAD_DATA_ADDRESS,
        BAD_CODE_ADDRESS,
        BAD_RELATION,
        STACK_OVERFLOW,
        STACK_EMPTY,
        DIVISION_BY_ZERO,
        BAD_INPUT,
        UNKNOWN_COMMAND
} runtime_error;

void vm_init()
{
        vm_stack_pointer = 0;
	vm_command_pointer = 0;
}

void vm_error(runtime_error error)
{
	opcode_info* info;

        switch(error) {
        case BAD_DATA_ADDRESS:
                fprintf(stderr, "Error: illegal data address\n");
                break;

        case BAD_CODE_ADDRESS:
                fprintf(stderr, "Error: illegal address in JUMP* instruction\n");
                break;

        case BAD_RELATION:
                fprintf(stderr, "Error: illegal comparison operator\n");
                break;

        case STACK_OVERFLOW:
                fprintf(stderr, "Error: stack overflow\n");
                break;

        case STACK_EMPTY:
                fprintf(stderr, "Error: stack is empty (no arguments are available)\n");
                break;

        case DIVISION_BY_ZERO:
                fprintf(stderr, "Error: division by zero\n");
                break;

        case BAD_INPUT:
                fprintf(stderr, "Error: illegal input\n");
                break;

        case UNKNOWN_COMMAND:
                fprintf(stderr, "Error: unknown command, unable to execute\n");
                break;

        default:
                fprintf(stderr, "Error: runtime error %d\n", error);
        }
	
	fprintf(stderr, "Code:\n\n");

        info = operation_info(vm_program[vm_command_pointer].operation);
	if(NULL == info) {
		fprintf(stderr, "%d\t(%d)\t\t%d\n", vm_command_pointer, 
			vm_program[vm_command_pointer].operation,
			vm_program[vm_command_pointer].arg);
	}
	else {
                if(info->need_arg) {
                        fprintf(stderr, "\t%d\t%s\t\t%d\n", vm_command_pointer, info->name,
                                vm_program[vm_command_pointer].arg);
                }
                else {
                        fprintf(stderr, "\t%d\t%s\n", vm_command_pointer, info->name);
                }
        }

        milan_error("VM error");
}

int vm_load(unsigned int address)
{
        if(address < MAX_MEMORY_SIZE) {
                return vm_memory[address];
        }
        else {
                vm_error(BAD_DATA_ADDRESS);
                return 0;
        }
}

void vm_store(unsigned int address, int word)
{
        if(address < MAX_MEMORY_SIZE) {
                vm_memory[address] = word;
        }
        else {
                vm_error(BAD_DATA_ADDRESS);
        }
}

int vm_read()
{
        int n;

	fprintf(stderr, "> "); fflush(stdout);
        if(scanf("%d", &n)) {
                return n;
        }
        else {
                vm_error(BAD_INPUT);
                return 0;
        }
}

void vm_write(int n)
{
        fprintf(stderr, "%d\n", n);
}

int vm_pop()
{
	if(vm_stack_pointer > 0) {
		return vm_stack[--vm_stack_pointer];
	}
	else {
		vm_error(STACK_EMPTY);
                return 0;
	}
}

void vm_push(int word)
{
	if(vm_stack_pointer < MAX_STACK_SIZE) {
		vm_stack[vm_stack_pointer++] = word;
	}
	else {
		vm_error(STACK_OVERFLOW);
	}
}

int vm_run_command()
{
	unsigned int index = vm_command_pointer;

        operation op = vm_program[index].operation;
        unsigned int arg = vm_program[index].arg;
        int data;

        switch(op) {
        case NOP:
                /* Ничего не делаем */
                break;

        case STOP:
                return 0;
                break;
                
        case LOAD:
                vm_push(vm_load(arg));
                break;

        case STORE:
                vm_store(arg, vm_pop());
                break;

        case BLOAD:
                vm_push(vm_load(arg + vm_pop()));
                break;

        case BSTORE:
                data = vm_pop();
                vm_store(arg + data, vm_pop());
                break;

        case PUSH:
                vm_push(arg);
                break;

        case POP:
                vm_pop();
                break;

        case DUP:
                data = vm_pop();
                vm_push(data);
                vm_push(data);
                break;

        case INVERT:
                vm_push(-vm_pop());
                break;

        case ADD:
                data = vm_pop();
                vm_push(vm_pop() + data);
                break;

        case SUB:
                data = vm_pop();
                vm_push(vm_pop() - data);
                break;

        case MULT:
                data = vm_pop();
                vm_push(vm_pop() * data);
                break;

        case DIV:
                data = vm_pop();
                if(0 == data) {
                        vm_error(DIVISION_BY_ZERO);
                }
                else {
                        vm_push(vm_pop() / data);
                }
                break;

        case COMPARE:
                data = vm_pop();
                switch(arg) {
                case EQ:
                        vm_push((vm_pop() == data) ? 1 : 0);
                        break;

                case NE:
                        vm_push((vm_pop() != data) ? 1 : 0);
                        break;

                case LT:
                        vm_push((vm_pop() < data) ? 1 : 0);
                        break;

                case GT:
                        vm_push((vm_pop() > data) ? 1 : 0);
                        break;

                case LE:
                        vm_push((vm_pop() <= data) ? 1 : 0);
                        break;

                case GE:
                        vm_push((vm_pop() >= data) ? 1 : 0);
                        break;

                default:
                        vm_error(BAD_RELATION);
                }
                break;

        case JUMP:
                if(arg < MAX_PROGRAM_SIZE) {
                        vm_command_pointer = arg;
                        return 1;
                }
                else {
                        vm_error(BAD_CODE_ADDRESS);
                }
                        
                break;

        case JUMP_YES:
                if(arg < MAX_PROGRAM_SIZE) {
                        data = vm_pop();
                        if(data) {
                                vm_command_pointer = arg;
                                return 1;
                        }
                }
                else {
                        vm_error(BAD_CODE_ADDRESS);
                }
                break;

        case JUMP_NO:
                if(arg < MAX_PROGRAM_SIZE) {
                        data = vm_pop();
                        if(!data) {
                                vm_command_pointer = arg;
                                return 1;
                        }
                }
                else {
                        vm_error(BAD_CODE_ADDRESS);
                }
                break;

        case INPUT:
                vm_push(vm_read());
                break;

        case PRINT:
		vm_write(vm_pop());
                break;

        default:
		vm_error(UNKNOWN_COMMAND);
        }

        ++vm_command_pointer;
        return 1;
}

void run()
{
	vm_command_pointer = 0;
	while(vm_command_pointer < MAX_PROGRAM_SIZE) {
		if(!vm_run_command())
			break;
	}
}

opcode_info* operation_info(operation op)
{
        return (op < opcodes_table_size) ? &opcodes_table[op] : NULL;
}

void put_command(unsigned int address, operation op, int arg)
{
        if(address < MAX_PROGRAM_SIZE) {
                vm_program[address].operation = op;
                vm_program[address].arg = arg;
        }
        else {
                milan_error("Illegal address in put_command()");
        }
}

void set_mem(unsigned int address, int value)
{
        vm_memory[address] = value;
}

