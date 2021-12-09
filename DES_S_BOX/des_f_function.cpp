#include <bits/stdc++.h>

using namespace std;

vector<int> E = {
	32, 1 , 2 , 3 , 4 , 5 ,
	4 , 5 , 6 , 7 , 8 , 9 ,
	8 , 9 , 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32, 1 };

string expansion_permute(string data)
{
	
	string res = "";
	
	for(int i=0; i<48; i++) {
		res += data[E[i] - 1];
	}
	
	return res;
}

string XOR(string input_1, string input_2)
{
	
	string res = "";
	for(int i=0; i<input_1.length(); i++) {
		res += (input_1[i] == input_2[i]) ? "0" : "1";
	}
	
	return res;
}

int main()
{
	int round_i;
	
	unsigned long long hex_output;
	
	string round_output, ith_round_key;
	string right_half_32, expanded_right_half_48;
	string s_box_input;
	
	ifstream fin;
	
	cout << "Enter the round i: ";
	cin >> round_i;
	
	cout << "Enter the 64 bit output of round " << round_i-1 << ": ";
	cin >> hex >> hex_output;
	round_output = bitset<64>(hex_output).to_string();
	cout << "Round output: " << round_output << endl;
	
	fin.open("Keys.txt");
	for(int i=1; i<=round_i; i++) {
		fin >> ith_round_key;
	}
	
	cout << "Key for round " << round_i << ": " << ith_round_key << endl;
	
	right_half_32 = round_output.substr(32, 32);
	cout << "Right half of the round output: " << right_half_32 << endl;
	
	expanded_right_half_48 = expansion_permute(right_half_32);
	cout << "Right half after expansion using E: " << expanded_right_half_48 << endl;
	
	s_box_input = XOR(expanded_right_half_48, ith_round_key);
	cout << "Input for S-Box: " << s_box_input << endl;
	
	return 0;
	
}