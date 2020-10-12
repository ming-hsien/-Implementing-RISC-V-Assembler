#ifndef I_type_H
#define I_type_H

#include<iostream>
#include<string>
using namespace std;

class I_type {
	/*friend ostream &operator<<(ostream &output, const I_type &i) {//offset,rs1,func3,rd,opcode
		output << i.offset << i.rs1 << i.func3 << i.rd << i.opcode << endl;
		return output;
	}*/
	string change_binary_for_five_bits(string cb);
	string change_binary_for_twelve_bits(string cb);
	string load_type(string risc) {
		stringstream ss;
		string buffer;
		ss << risc;
		ss >> buffer;
		return buffer;
	}
	public:
		I_type(string r);

		void main_process();//process the rd,rs1,offset

		void setoffset(string buffer) { offset = buffer; }
		void setrs1(string buffer) { rs1 = buffer; }
		void setrd(string buffer) { rd = buffer; }

		string getoffset() { return offset; }
		string getrs1() { return rs1; }
		string getfunc3() { return func3; }
		string getrd() { return rd; }
		string getopcode() { return opcode; }
		string getriscv() { return riscv; }
	private:
		string offset;
		string rs1;
		string func3;
		string rd;
		string opcode;
		string riscv;
};
void I_type::main_process()
{
	string r = getriscv();
	string r1,os,rdd;
	if (getopcode() == "0000011") {
		for (int v = 0; v < r.size(); v++) {
			if (r[v] == 'x') {				
				v++;
				while (r[v] != ','&&r[v] != ' ') {
					rdd.push_back(r[v]);
					v++;
				}
				while (r[v] == ',' || r[v] == ' ')
					v++;
				while (r[v] != '(') {
					os.push_back(r[v]);
					v++;
				}
				while (r[v] == '(' || r[v] == 'x')
					v++;
				while (r[v] != ')') {
					r1.push_back(r[v]);
					v++;
				}
			}
		}
	}
	else if (getopcode() == "0010011"){
		for (int v = 0; v < r.size(); v++) {
			if(r[v] == 'x') {
				v++;
				while (r[v] != ','&&r[v] != ' ') {
					rdd.push_back(r[v]);
					v++;
				}
				while (r[v] == ',' || r[v] == ' ' || r[v] == 'x')
					v++;
				while (r[v] != 'x'&&r[v]!=','&&r[v]!=' ') {
					r1.push_back(r[v]);
					v++;
				}
				while (r[v] == ' '|| r[v] == ',')
					v++;
				while (v < r.size()) {
					os.push_back(r[v]);
					v++;
				}
			}
		}
	}
	setoffset(change_binary_for_twelve_bits(os));
	setrs1(change_binary_for_five_bits(r1));
	setrd(change_binary_for_five_bits(rdd));
}
I_type::I_type(string i) 
{
	riscv = i;
	string risc = load_type(i);
	if (risc == "lb" || risc == "lh" || risc == "lw"
		|| risc == "lbu" || risc == "lhu")
		opcode = "0000011";
	else
		opcode = "0010011";
	if (risc == "lb" || risc == "addi")
		func3 = "000";
	else if (risc == "lh")
		func3 = "001";
	else if (risc == "lw" || risc == "slti")
		func3 = "010";
	else if (risc == "lbu" || risc == "xori")
		func3 = "100";
	else if (risc == "lhu")
		func3 = "101";
	else if (risc == "sltiu")
		func3 = "011";
	else if (risc == "ori")
		func3 = "110";
	else if (risc == "andi")
		func3 = "111";
	rs1 = ""; rd = ""; offset = "";
}
string I_type::change_binary_for_five_bits(string cb) {
	int number = 0, c = 0;
	string binary[5];
	for (int i = 0; i < 5; i++) {
		binary[i] = "0";
	}
	for (int i = cb.size() - 1; i >= 0; i--) {
		number += pow(10, c)*(cb[i] - '0');
		c++;
	}
	c = 0;
	while (number > 0) {
		if (number % 2 == 1) {
			binary[c] = "1";
			number /= 2;
			c++;
		}
		else {
			number /= 2;
			c++;
		}
	}
	string re;
	for (int i = 4; i >= 0; i--) {
		re += binary[i];
	}
	return re;
}
string I_type::change_binary_for_twelve_bits(string cb) {
	int number = 0, c = 0;
	string binary[12];
	for (int i = 0; i < 12; i++) {
		binary[i] = "0";
	}
	for (int i = cb.size() - 1; i >= 0; i--) {
		number += pow(10, c)*(cb[i] - '0');
		c++;
	}
	
	c = 0;
	while (number > 0) {
		if (number % 2 == 1) {
			binary[c] = "1";
			number /= 2;
			c++;
		}
		else {
			number /= 2;
			c++;
		}
	}
	string re;
	for (int i = 11; i >= 0; i--) {
		re += binary[i];
	}
	return re;
}
#endif
