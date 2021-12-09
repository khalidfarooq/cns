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


unsigned int s_boxes[8][64] = {
   {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
    0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
    4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
    15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13},

    {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
    3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
    0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
    13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9},

    {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
    13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
    13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
    1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12},

    {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
    13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
    10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
    3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14},

    {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
    14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
    4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
    11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3},

    {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
    10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
    9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
    4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13,},

    {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
    13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
    1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
    6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12},

    {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
    1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
    7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
    2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
};

string expansion_permute(string data)
{
	
	string res = "";
	
	for(int i=0; i<48; i++) {
		res += data[E[i] - 1];
	}
	
	return res;
}


int perm_table[] = {
    16, 7 , 20, 21, 29, 12, 28, 17,
    1 , 15, 23, 26, 5 , 18, 31, 10,
    2 , 8 , 24, 14, 32, 27, 3 , 9 ,
    19, 13, 30, 6 , 22, 11, 4 , 25 };


string s_box_substitution(string input)
{
	string res = "", s_input;
	int row, col;
	for(int i=0; i<8; i++) {
		s_input = input.substr(6*i, 6);
		row = bitset<2>(s_input.substr(0,1) + s_input.substr(5,1)).to_ulong();
		col = bitset<4>(s_input.substr(1,4)).to_ulong();
		res += bitset<4>(s_boxes[i][(row*16)+col]).to_string();
	}
	
	return res;
}

string permute(string input)
{
	string res = "";
	for(int i=0; i<32; i++) {
		res += input[perm_table[i]-1];
	}
	return res;
}

string XOR(string a, string b)
{
	string res = "";
	for(int i=0; i<a.length(); i++) {
		res += (a[i] == b[i]) ? "0" : "1";
	}
	
	return res;
}

int main()
{
	int round_i;
	
	unsigned long long hex_output, output_64_bit;
	
	string s_b_i, o_64_b, l_32, s_box_output, permuted_output, right_i;
	
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
	
	
	// cout << "Enter 48 Bit Input for S_Box: ";
	// cin >> hex >>s_box_input;
	// s_b_i = bitset<48>(s_box_input).to_string();
	// cout << s_b_i << endl;
	
	
	
	// cout << "Enter 64 Bit output of i-1 round of DES: ";
	// cin >> hex >> output_64_bit;
	// o_64_b = bitset<64>(output_64_bit).to_string();
	// cout << o_64_b << endl;
	
	
	l_32 = round_output.substr(0, 32);
	
	s_box_output = s_box_substitution(s_box_input);
	permuted_output = permute(s_box_output);
	
	right_i = XOR(permuted_output, l_32);
	
	cout << "32 Bit output of ith round of DES: " << right_i << endl;
	
	
	return 0;
}