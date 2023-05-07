#include "stack-vm.h"
#include <math.h>

/*
 * Instruction format
 * header: 2 bits
 * data: 30 bits
 *
 * header format:
 * 0 => positive integer
 * 1 => primitive instruction
 * 2 => negative integer
 * 3 => undefined
 * */

// functions
StackVM::StackVM() {
	memory.reserve(1000000);
}
i32 StackVM::getType(i32 instruction) {
	i32 type = 0xc0000000;
	type = (type & instruction) >> 30;
	return type;
}
i32 StackVM::getData(i32 instruction) {
	i32 data = 0x3fffffff;
	data = data & instruction;
	return data;
}
void StackVM::fetch() {
	pc++;
}
void StackVM::decode() {
	typ = getType(memory[pc]);
	dat = getData(memory[pc]);
}
void StackVM::execute() {
	if (typ == 0 || typ == 2) {
		sp++;
		memory[sp] = dat;
	} else {
		doPrimitive();
	}
}
void StackVM::doPrimitive() {
	switch (dat) {
		case 0: // halt
			std::cout << "halt" << std::endl;
			running = 0;
			break;
		case 1: // add
			std::cout << "\n1. add " << memory[sp - 1] << " " << memory[sp] << std::endl;
			memory[sp - 1] = memory[sp - 1] + memory[sp];
			sp--;
			break;
		case 2:// sub
			std::cout << "\n2. sub " << memory[sp - 1] << " " << memory[sp] << std::endl;
			memory[sp - 1] = memory[sp - 1] - memory[sp];
			sp--;
			break;
		case 3: // mul
			std::cout << "\n3. mul " << memory[sp - 1] << " " << memory[sp] << std::endl;
			memory[sp - 1] = memory[sp - 1] * memory[sp];
			sp--;

			break;
		case 4: // div
			std::cout << "\n4. div " << memory[sp - 1] << " " << memory[sp] << std::endl;
			memory[sp - 1] = memory[sp - 1] / memory[sp];
			sp--;
			break;
		case 5: // mod
            		std::cout << "\n5. mod " << memory[sp - 1] << " " << memory[sp] << std::endl;
            		memory[sp - 1] = memory[sp - 1] % memory[sp];
            		sp--;
            		break;
            	case 6: // square root
		    std::cout << "\n6. sqrt " << memory[sp] << std::endl;
		    memory[sp] = sqrt(memory[sp]);
		    break;

		case 7: // cube root
		    std::cout << "\n7. cbrt " << memory[sp] << std::endl;
		    memory[sp] = cbrt(memory[sp]);
		    break;

		case 8: // exponentiation
			std::cout << "\n8. pow " << memory[sp - 1] << " " << memory[sp] << std::endl;
			memory[sp - 1] = pow(memory[sp - 1], memory[sp]);
			sp--;
			break;

		case 9: // minimum of two values
		    std::cout << "\n9. min " << memory[sp - 1] << " " << memory[sp] << std::endl;
		    memory[sp - 1] = std::min(memory[sp - 1], memory[sp]);
		    sp--;
		    break;

		case 10: // maximum of two values
		    std::cout << "\n10. max " << memory[sp - 1] << " " << memory[sp] << std::endl;
		    memory[sp - 1] = std::max(memory[sp - 1], memory[sp]);
		    sp--;
		    break;

		case 11: // random number
		    std::cout << "\n11. rand" << std::endl;
		    memory[sp] = rand() %100;
		    break;
		    
		case 12: // bitwise and
		    std::cout << "\n12. and " << memory[sp - 1] << " " << memory[sp] << std::endl;
		    memory[sp - 1] = memory[sp - 1] & memory[sp];
		    sp--;
		    break;

		case 13: // bitwise or
		    std::cout << "\n13. or " << memory[sp - 1] << " " << memory[sp] << std::endl;
		    memory[sp - 1] = memory[sp - 1] | memory[sp];
		    sp--;
		    break;

		case 14: // bitwise xor
		    std::cout << "\n14. xor " << memory[sp - 1] << " " << memory[sp] << std::endl;
		    memory[sp - 1] = memory[sp - 1] ^ memory[sp];
		    sp--;
		    break;

		case 15: // bitwise not
		    std::cout << "\n15. not " << memory[sp] << std::endl;
		    memory[sp] = ~memory[sp];
		    break;

		case 16: // left shift
		    std::cout << "\n16. lshift " << memory[sp - 1] << " " << memory[sp] << std::endl;
		    memory[sp - 1] = memory[sp - 1] << memory[sp];
		    sp--;
		    break;
		
		case 17: // right shift
		    std::cout << "\n17. rshift " << memory[sp - 1] << " " << memory[sp] << std::endl;
		    memory[sp - 1] = memory[sp - 1] >> memory[sp];
		    sp--;
		    break;

		case 18:
		    std::cout << "\n18. negate " << memory[sp] << std::endl;
		    memory[sp] = -memory[sp];
		    break;

		case 19: // less than
		    std::cout << "\n19. lt " << memory[sp - 1] << " " << memory[sp] << std::endl;
		    memory[sp - 1] = memory[sp - 1] < memory[sp];
		    sp--;
		    break;

		case 20: // less than or equal to
		    std::cout << "\n20. le " << memory[sp - 1] << " " << memory[sp] << std::endl;
		    memory[sp - 1] = memory[sp - 1] <= memory[sp];
		    sp--;
		    break;

		case 21: // greater than
		    std::cout << "\n21. gt " << memory[sp - 1] << " " << memory[sp] << std::endl;
		    memory[sp - 1] = memory[sp - 1] > memory[sp];
		    sp--;
		    break;

		case 22: // greater than or equal to
		    std::cout << "\n22. ge " << memory[sp - 1] << " " << memory[sp] << std::endl;
		    memory[sp - 1] = memory[sp - 1] >= memory[sp];
		    sp--;
		    break;

		case 23: // equal to
		    std::cout << "\n23. eq " << memory[sp - 1] << " " << memory[sp] << std::endl;
		    memory[sp - 1] = memory[sp - 1] == memory[sp];
		    sp--;
		    break;

		case 24: // not equal to
		    std::cout << "\n24. neq " << memory[sp - 1] << " " << memory[sp] << std::endl;
		    memory[sp - 1] = memory[sp - 1] != memory[sp];
		    sp--;
		    break;

		case 25:
		    std::cout << "\n25. swap " << memory[sp] << " " << memory[sp - 1] << std::endl;
		    std::swap(memory[sp], memory[sp - 1]);
		    break;
		    
		case 26: //increment
		    std::cout << "\n26. increment " << memory[sp] << std::endl;
		    memory[sp] += 1;
		    break;

		case 27: // decrement
		    std::cout << "\n27. decrement " << memory[sp] << std::endl;
		    memory[sp] -= 1;
		    break;

		case 28: // test bit
		    std::cout << "\n28. test_bit " << memory[sp - 1] << " " << memory[sp] << std::endl;
		    if (memory[sp - 1] & (1 << memory[sp])) {
			memory[sp - 1] = 1;
		    } else {
			memory[sp - 1] = 0;
		    }
		    sp--;
		    break;

		case 29: // clear bit
		    std::cout << "\n29. clear_bit " << memory[sp - 1] << " " << memory[sp] << std::endl;
		    memory[sp - 1] &= ~(1 << memory[sp]);
		    sp--;
		    break;

		case 30: // set bit
		    std::cout << "\n30. set_bit " << memory[sp - 1] << " " << memory[sp] << std::endl;
		    memory[sp - 1] |= (1 << memory[sp]);
		    sp--;
		    break;
		    
		case 31:
		    std::cout << "\n31. pop " << memory[sp] << std::endl;
		    sp--;
		    break;

		case 32:
		    std::cout << "\n32. even " << memory[sp] << std::endl;
		    memory[sp] = (memory[sp] % 2 == 0) ? 1 : 0;
		    break;

		case 33:
		    std::cout << "\n33. odd " << memory[sp] << std::endl;
		    memory[sp] = (memory[sp] % 2 != 0) ? 1 : 0;
		    break;
		
	}
}

void StackVM::run() {
	pc -= 1;
	while (running == 1) {
		fetch();
		decode();
		execute();
		std::cout << "tos: " << memory[sp] << std::endl;
	}
}
void StackVM::loadProgram(std::vector<i32> prog) {
	for (i32 i = 0; i < prog.size(); i++) {
		memory[pc + i] = prog[i];
	}	
}


