#include<iostream>
#include<string>
#include<sstream>
#include<math.h>
#include<vector>
#include<queue>
#include<map>

#include "R_type.h"
#include "I_type.h"
#include "S_type.h"
#include "SB_type.h"
using namespace std;

int main()
{
	
	vector<string>v;
	queue<string>q;
	string s1;	
	map<string,int>m;
	map<string,int>::iterator iter;
	string s2, s3, s4;
	int ofset = 0;
	while (getline(cin, s1)) {
		stringstream ss;
		if (s1 == "0")
			break;
		q.push(s1);
		if (s1[0] != ' ') {
			ss << s1;
			ss >> s4 >> s2 >> s3;
			s4.pop_back();
			m[s4] = ofset;
		}
		ofset += 4;
	}
	while (q.size()!=0) {
		s1 = q.front();
		if (s1.size() < 5) {
			break;
		}
		if (s1[0] == ' ') {
			stringstream ss;
			ss << s1;
			ss >> s2 >> s3;
			if (s2 == "sb" || s2 == "sh" || s2 == "sw" || s2 == "sd") {
				ss>> s4;
				s1 = s2 + ' ' + s3 + s4;
			}
		}
		else {
			stringstream ss;
			ss << s1;
			ss >> s4 >> s2 >> s3;
			if (s2 == "sb" || s2 == "sh" || s2 == "sw" || s2 == "sd") {
				ss >> s4;
				s1 = s2 + ' ' + s3 + s4;
			}
			else
				s1 = s2 +' '+ s3;
		}
		
		if (s2 == "add"|| s2 == "sub"|| s2 == "sli"|| s2 == "slt"
			|| s2 == "sltu"|| s2 == "xor"|| s2 == "srl"
			|| s2 == "sra"|| s2 == "or"|| s2 == "and") 
		{
			//cout << s1 << endl;
			R_type r(s1);
			r.main_process();
			string buffer;
			buffer = r.getfunc7() + r.getrs2() + r.getrs1() + r.getfunc3() + r.getrd() + r.getopcode();
			v.push_back(buffer);
		}
		else if (s2 == "lb"|| s2 == "lh"|| s2 == "lw"|| s2 == "lbu"|| s2 == "lhu"
			|| s2 == "addi"|| s2 == "slti"|| s2 == "sltiu"
			|| s2 == "xori"|| s2 == "ori"|| s2 == "andi")
		{
			//cout << s1 << endl;
			I_type i(s1);
			i.main_process();
			string buffer;
			buffer = i.getoffset() + i.getrs1() + i.getfunc3() + i.getrd() + i.getopcode();
			v.push_back(buffer);
		}
		else if (s2=="sb"|| s2 == "sh"|| s2 == "sw"||s2=="sd")
		{
			//cout << s1 << endl;
			S_type s(s1);
			s.main_process();
			string buffer;
			buffer = s.getoffset2() + s.getrs2() + s.getrs1() + s.getfunc3() + s.getoffset1() + s.getopcode();
			v.push_back(buffer);
		}
		else if (s2 == "beq" || s2 == "bne" || s2 == "blt" || s2 == "bge" || s2 == "bltu" || s2 == "bgeu"||s2 == "jal") {
			//cout << s1 << endl;
			string s;
			for (int i = 0; i < s3.size(); i++) {
				if (s3[i] == ','&&s3[i + 1] != 'x') {
					i++;
					while (i < s3.size()) {
						s += s3[i];
						i++;
					}
				}
			}
			iter = m.find(s);
			if (iter != m.end()) {
				int p = iter->second;
				SB_type sb(s1, p);
				sb.set();
				v.push_back(sb.getall());
			}
		}
		q.pop();
	}
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << endl;
	}
	system("pause");
}