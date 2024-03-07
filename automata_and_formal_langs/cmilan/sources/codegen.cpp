#include "codegen.h"

void Command::print(int address, ostream& os) {
    os << address << ":\t";
    switch(instruction_) {
        case NOP:
            os << "NOP";
            break;

        case STOP:
            os << "STOP";
            break;

        case LOAD:
            os << "LOAD\t" << arg_;
            break;

        case STORE:
            os << "STORE\t" << arg_;
            break;

        case BLOAD:
            os << "BLOAD\t" << arg_;
            break;

        case BSTORE:
            os << "BSTORE\t" << arg_;
            break;

        case PUSH:
            os << "PUSH\t" << arg_;
            break;

        case POP:
            os << "POP";
            break;

        case DUP:
            os << "DUP";
            break;

        case ADD:
            os << "ADD";
            break;

        case SUB:
            os << "SUB";
            break;

        case MULT:
            os << "MULT";
            break;

        case DIV:
            os << "DIV";
            break;

        case INVERT:
            os << "INVERT";
            break;

        case COMPARE:
            os << "COMPARE\t" << arg_;
            break;

        case JUMP:
            os << "JUMP\t" << arg_;
            break;

        case JUMP_YES:
            os << "JUMP_YES\t" << arg_;
            break;

        case JUMP_NO:
            os << "JUMP_NO\t" << arg_;
            break;

        case INPUT:
            os << "INPUT";
            break;

        case PRINT:
            os << "PRINT";
            break;
    }

    os << endl;
}

void CodeGen::emit(Instruction instruction) {
    commandBuffer_.push_back(Command(instruction));
}

void CodeGen::emit(Instruction instruction, int arg) {
    commandBuffer_.push_back(Command(instruction, arg));
}

void CodeGen::emitAt(int address, Instruction instruction) {
    commandBuffer_[address] = Command(instruction);
}

void CodeGen::emitAt(int address, Instruction instruction, int arg) {
    commandBuffer_[address] = Command(instruction, arg);
}

int CodeGen::getCurrentAddress() {
    return commandBuffer_.size();
}

int CodeGen::reserve() {
    emit(NOP);
    return commandBuffer_.size() - 1;
}

void CodeGen::flush() {
    int count = commandBuffer_.size();
    for(int address = 0; address < count; ++address) {
        commandBuffer_[address].print(address, output_);
    }
    output_.flush();
}
