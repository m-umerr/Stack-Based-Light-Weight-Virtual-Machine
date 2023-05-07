#include <iostream>
#include <fstream>
#include "lexer.h"

typedef uint32_t i32;

using namespace std;

// functions
vector<i32> compileToInstructions(strings s);
bool isInteger(string s);
bool isPrimimitive(string s);
i32 mapToNumber(string s); 

int main(int argc, char *argv[]) {
	// check for input errors
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " <sasm-filename>" << endl;
		exit(1);
	}

	// read input file
	ifstream infile;
	infile.open(argv[1]);
	if (!infile.is_open()) {
		cout << "Error: could not open [" << argv[1] << "]" << endl;
		exit(1);
	}
	string line;
	string contents;
	while (getline(infile, line)) {
		contents += line + "\n";
	}
	infile.close();

	// parse file
	Lexer lexer;
	strings lexemes = lexer.lex(contents);

	// compile to binary
	vector<i32> instructions = compileToInstructions(lexemes);

	// write to binary file
	ofstream ofile;
	ofile.open("out.bin", ios::binary);
	for (i32 i = 0; i < instructions.size(); i++) {
		ofile.write(reinterpret_cast<char *>(&instructions[i]), sizeof(i32));
	}
	ofile.close();
	return 0;
}

vector<i32> compileToInstructions(strings s) {
	vector<i32> instructions;
	for (i32 i = 0; i < s.size(); i++) {
		if (isInteger(s[i])) {
			instructions.push_back(stoi(s[i]));
		} else {
			i32 instruction = mapToNumber(s[i]);
			if (instruction != -1) {
				instructions.push_back(instruction);
			} else {
				cout << "Error: Invalid instruction [" << s[i] << "]" << endl;
			}
		}
	}
	instructions.push_back(0x40000000);
	return instructions;
}
bool isInteger(string s) {
	for (i32 i = 0; i < s.length(); i++) {
		if (!isdigit(s[i])) {
			return false;
		}
	}
	return true;
}
i32 mapToNumber(string s) {
	if (s == "+") {
		return 0x40000001;
	} else if (s == "-") {
		return 0x40000002;
	} else if (s == "*") {
		return 0x40000003;
	} else if (s == "/") {
		return 0x40000004;
	} else if (s == "|") {
		return 0x40000005;
	} else if (s == "sqrt") {
		return 0x40000006;
	} else if (s == "cbrt") {
		return 0x40000007;
	} else if (s == "pow") {
		return 0x40000008;
	} else if (s == "min") {
		return 0x40000009;
	} else if (s == "max") {
		return 0x4000000A;
	} else if (s == "rand") {
		return 0x4000000B;
	} else if (s == "and") {
		return 0x4000000C;
	} else if (s == "or") {
		return 0x4000000D;
	} else if (s == "xor") {
		return 0x4000000E;
	} else if (s == "not") {
		return 0x4000000F;
	} else if (s == "lshift") {
		return 0x40000010;
	} else if (s == "rshift") {
		return 0x40000011;
	} else if (s == "neg") {
		return 0x40000012;
	} else if (s == "lt") {
		return 0x40000013;
	} else if (s == "le") {
		return 0x40000014;
	} else if (s == "gt") {
		return 0x40000015;
	} else if (s == "ge") {
		return 0x40000016;
	} else if (s == "eq") {
		return 0x40000017;
	} else if (s == "neq") {
		return 0x40000018;
	} else if (s == "swap") {
		return 0x40000019;
	} else if (s == "inc") {
		return 0x4000001A;
	} else if (s == "dec") {
		return 0x4000001B;
	} else if (s == "testbit") {
		return 0x4000001C;
	} else if (s == "clrbit") {
		return 0x4000001D;
	} else if (s == "sbit") {
		return 0x4000001E;
	} else if (s == "pop") {
		return 0x4000001F;
	} else if (s == "even") {
		return 0x40000020;
	} else if (s == "odd") {
		return 0x40000021;
	} 
	
	return -1; // invalid instruction
}
