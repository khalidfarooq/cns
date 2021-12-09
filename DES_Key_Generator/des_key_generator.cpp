#include <bits/stdc++.h>

using namespace std;

vector<int> perm_choice_one = {
   57, 49, 41, 33, 25, 17, 9 ,
   1 , 58, 50, 42, 34, 26, 18,
   10, 2 , 59, 51, 43, 35, 27,
   19, 11, 3 , 60, 52, 44, 36,
   63, 55, 47, 39, 31, 23, 15,
   7 , 62, 54, 46, 38, 30, 22,
   14, 6 , 61, 53, 45, 37, 29,
   21, 13, 5 , 28, 20, 12, 4 };

vector<int> perm_choice_two = {
   14, 17, 11, 24, 1 , 5 , 3 , 28,
   15, 6 , 21, 10, 23, 19, 12, 4 ,
   26, 8 , 16, 7 , 27, 20, 13, 2 ,
   41, 52, 31, 37, 47, 55, 30, 40,
   51, 45, 33, 48, 44, 49, 39, 56,
   34, 53, 46, 42, 50, 36, 29, 32 };

vector<int> left_shift_table = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

string first_permute(string data)
{
	
	string res = "";
	for(int i=0; i<56; i++) {
		res += data[perm_choice_one[i] - 1];
	}
	
	return res;
}

string second_permute(string data)
{
	
	string res = "";
	for(int i=0; i<48; i++) {
		res += data[perm_choice_two[i] - 1];
	}
	
	return res;
}

string rotate_sub_key(string key, int rot)
{
	
	return key.substr(rot, key.length()-1) + key.substr(0, rot);
}

list <string> generate_keys(string left_sub_key, string right_sub_key)
{
	
	ofstream fout;
	fout.open("Keys.txt");
	
	list <string> generated_keys;
	
	for(int i=0 ;i<16; i++) {
		left_sub_key = rotate_sub_key(left_sub_key, left_shift_table[i]);
		right_sub_key = rotate_sub_key(right_sub_key, left_shift_table[i]);
		
		generated_keys.push_back(second_permute(left_sub_key+right_sub_key));
		
		fout << second_permute(left_sub_key+right_sub_key) << endl;
	}
	
	return generated_keys;
	
}

int main()
{
	unsigned long long hex_key;
	string key;
	int count = 0;
	
	list <string> round_keys;
	
	cout << "Enter the 64 bit long hex key: ";
	cin >> hex >> hex_key;
	
	key = bitset<64>(hex_key).to_string();
	cout << key << endl;
	
	key = first_permute(key);
	cout << key << endl;
	
	round_keys = generate_keys(key.substr(0, 28), key.substr(28, 28));
	
	for(auto k : round_keys) {
		count++;
		cout << "Key " << count << "\t" << k << endl;
	}
	
	return 0;
	
}