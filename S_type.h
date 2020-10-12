#ifndef S_type_H
#define S_type_H

#include<iostream>
#include<string>
using namespace std;

class S_type {
	/*friend ostream &operator<<(ostream &output, const S_type &i) {//offset2,rs2,rs1,func3,offset1,opcode
		output << i.offset2 << i.rs2 << i.rs1 << i.func3 << i.offset1 << i.opcode << endl;
		return output;
	}*/
	string change_binary_for_five_bits(string cb);
	void change_binary_for_twelve_bits(string cb);
	string load_type(string risc) {
		stringstream ss;
		string buffer;
		ss << risc;
		ss >> buffer;
		return buffer;
	}
public:
	S_type(string r);

	void main_process();//process the rs2,rs1,offset1,offset2

	void setoffset1(string buffer) { offset1 = buffer; }
	void setoffset2(string buffer) { offset2 = buffer; }
	void setrs1(string buffer) { rs1 = buffer; }
	void setrs2(string buffer) { rs2 = buffer; }

	string getoffset1() { return offset1; }
	string getoffset2() { return offset2; }
	string getrs1() { return rs1; }
	string getfunc3() { return func3; }
	string getrs2() { return rs2; }
	string getopcode() { return opcode; }
	string getriscv() { return riscv; }
private:
	string offset1;//simm[4:0]
	string offset2;//simm[11:5]
	string rs1;
	string func3;
	string rs2;
	string opcode;	
	string riscv;
};

void S_type::main_process()
{
	string r = getriscv();
	string r1, os, r2;
	
	for (int v = 0; v < r.size(); v++) {
		if (r[v] == 'x') {
			v++;
			while (r[v] != ','&&r[v] != ' ') {
				r2.push_back(r[v]);
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
		
	change_binary_for_twelve_bits(os);
	setrs1(change_binary_for_five_bits(r1));
	setrs2(change_binary_for_five_bits(r2));
}

S_type::S_type(string s)
{
	riscv = s;
	string risc = load_type(s);
	if (risc == "sb") {
		func3 = "000";
	}
	else if (risc == "sh") {
		func3 = "001";
	}
	else if (risc == "sw") {
		func3 = "010";
	}
	else if (risc == "sd") {
		func3 = "011";
	}
	opcode = "0100011";
	rs1 = ""; rs2 = ""; offset1 = ""; offset2 = "";
}

void S_type::change_binary_for_twelve_bits(string cb) {
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
	string bufferof1, bufferof2;
	for (int b = 7; b < 12; b++) {
		bufferof1.push_back(re[b]);
	}
	for (int b = 0; b < 7; b++) {
		bufferof2.push_back(re[b]);
	}
	setoffset1(bufferof1);
	setoffset2(bufferof2);
}
string S_type::change_binary_for_five_bits(string cb) {
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
