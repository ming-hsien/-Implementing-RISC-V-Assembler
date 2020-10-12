#ifndef SB_type_H
#define SB_type_H

#include<iostream>
#include<string>
#include<sstream>

using namespace std;

class SB_type {
	string change_binary_for_five_bits(string cb);

public:
	SB_type(string r,int offset);

	void setrs2(string buffer) { rs2 = buffer; }
	void setrs1(string buffer) { rs1 = buffer; }
	void setall(string buffer) {
		all =  buffer;
	}
	void set();//¦X¨Ö

	string getrs2() { return rs2; }
	string getrs1() { return rs1; }
	string getfunc3() { return func3; }
	string getopcode() { return opcode; }
	string getriscv() { return riscv; }
	string getall() {
		return all;
	}
	int getofset() {
		return ofset;
	}
private:
	string rs2;//or rd(jal)
	string rs1;
	string func3;
	string opcode;
	string riscv;
	string all;
	int ofset;
};
//constructure
SB_type::SB_type(string r,int offset) {
	stringstream ss;
	string b1, b2;
	ss << r;
	ss >> b1 >> b2;
	riscv = r;
	if (b1 == "beq") {
		func3 = "000";
	}
	else if (b1 == "bne") {
		func3 = "001";
	}
	else if (b1 == "blt") {
		func3 = "100";
	}
	else if (b1 == "bge") {
		func3 = "101";
	}
	else if (b1 == "bltu") {
		func3 = "110";
	}
	else if (b1 == "bgeu") {
		func3 = "111";
	}
	else if (b1 == "jal") {
		func3 = "";
	}
	if (b1 != "jal") {
		opcode = "1100011";
	}
	else {
		opcode = "1101111";
	}
	ofset = offset;
	all = "";
	if (b1 != "jal") {
		string r1, r2;
		for (int i = 0; i < b2.size(); i++) {
			if (b2[i] == 'x') {
				i++;
				while (b2[i] != ',') {
					r1 += b2[i];
					i++;
				}
				i++;
				i++;
				while (b2[i] != ',') {
					r2 += b2[i];
					i++;
				}
				i = b2.size();
			}
		}
		rs2 = change_binary_for_five_bits(r2);
		rs1 = change_binary_for_five_bits(r1);
	}
	else {
		string rd;
		for (int i = 0; i < b2.size(); i++) {
			if (b2[i] == 'x') {
				i++;
				while (b2[i] != ',') {
					rd += b2[i];
					i++;
				}
				i = b2.size();
			}
		}
		rs2 = change_binary_for_five_bits(rd);
		rs1 = "";
	}

	
}
void SB_type::set() {
	stringstream ss;
	string b1, b2;
	ss << getriscv();
	ss >> b1 >> b2;

	if (b1 != "jal") {
		int cb = getofset();
		string binary[13];
		for (int i = 0; i < 13; i++) {
			binary[i] = "0";
		}
		int c = 0;
		while (cb > 0) {
			if (cb % 2 == 1) {
				binary[c] = "1";
				cb /= 2;
				c++;
			}
			else {
				cb /= 2;
				c++;
			}
		}
		string a;
		a = binary[12];
		for (int i = 10; i >= 5; i--) {
			a += binary[i];
		}
		a = a + getrs2() + getrs1() + getfunc3();
		for (int i = 4; i >= 1; i--) {
			a += binary[i];
		}
		a += binary[11];
		a += getopcode();
		setall(a);
	}
	else {
		string a,rd = getrs2();
		int of = getofset();
		int cb = getofset();
		string binary[21];
		for (int i = 0; i < 21; i++) {
			binary[i] = "0";
		}
		int c = 0;
		while (cb > 0) {
			if (cb % 2 == 1) {
				binary[c] = "1";
				cb /= 2;
				c++;
			}
			else {
				cb /= 2;
				c++;
			}
		}
		a = binary[20];
		for (int i = 10; i >= 1; i--) {
			a += binary[i];
		}
		a += binary[11];
		for (int i = 19; i >= 12; i--) {
			a += binary[i];
		}
		a += rd;
		a += getopcode();
		setall(a);
	}

}
string SB_type::change_binary_for_five_bits(string cb) {
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

