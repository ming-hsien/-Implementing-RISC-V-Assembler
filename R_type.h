#ifndef R_type_H
#define R_type_H

#include<iostream>
#include<string>
#include<sstream>

using namespace std;

class R_type {
	/*friend ostream &operator<<(ostream &output, const R_type &r) {
		output << r.func7 << r.rs2 << r.rs1 << r.func3 << r.rd << r.opcode << endl;
		return output;
	}*/
	string change_binary_for_five_bits(string cb);
	string load_type(string risc) {
		stringstream ss;
		string buffer;
		ss << risc;
		ss >> buffer;
		return buffer;
	}
public:
	R_type(string r);
	
	void main_process();//process the rs1,rs2,rd

	void setrs2(string buffer) { rs2 = buffer; }
	void setrs1(string buffer) { rs1 = buffer; }
	void setrd(string buffer) { rd = buffer; }
	
	string getfunc7() {return func7; }
	string getrs2() { return rs2; }
	string getrs1() { return rs1; }
	string getfunc3() { return func3; }
	string getrd() { return rd; }
	string getopcode() { return opcode; }
	string getriscv() { return riscv; }
private:
	string func7;
	string rs2;
	string rs1;
	string func3;
	string rd;
	string opcode;
	string riscv;
};
//constructure
R_type::R_type(string r) {
	string risc = load_type(r);
	riscv = r;
	if (risc == "sub" || risc == "sra")
		func7 = "0100000";
	else
		func7 = "0000000";

	if (risc == "add" || risc == "sub")
		func3 = "000";
	else if (risc == "sll")
		func3 = "001";
	else if (risc == "slt")
		func3 = "010";
	else if (risc == "sltu")
		func3 = "011";
	else if (risc == "xor")
		func3 = "100";
	else if (risc == "srl" || risc == "sra")
		func3 = "101";
	else if (risc == "or")
		func3 = "110";
	else if (risc == "and")
		func3 = "111";
	opcode = "0110011";
	rs2 = ""; rs1 = ""; rd = "";
}

void R_type::main_process() {
	string no,m,r;
	stringstream ss;
	r = getriscv();
	ss << r;
	ss >> no >> m;
	string st[3]; int a = 0;
	for (int i = 0; i < m.size(); i++) {//cut the string m
		if (m[i] == 'x') {
			i++;
			while (m[i] != ','&&i < m.size()) {
				st[a].push_back(m[i]);
				i++;
			}
			a++;
		}
	}
	setrs1(change_binary_for_five_bits(st[1]));
	setrs2(change_binary_for_five_bits(st[0]));
	setrd(change_binary_for_five_bits(st[2]));
}

string R_type::change_binary_for_five_bits(string cb) {
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
#endif
