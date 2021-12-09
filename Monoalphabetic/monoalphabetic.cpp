#include <bits/stdc++.h>

using namespace std;

string unique_string;

string read_from_file()
{
	ifstream fin;
	string text;
	
	fin.open("plaintext.txt");
	fin >> text;
	fin.close();
	
	return text;
}

void wrtie_to_file(string text)
{
	ofstream fout;
	fout.open("ciphertext.txt");
	fout << text;
	fout.close();
}

void permute(string a, int l, int r, vector<string> &keyspace)
{
	if(l == r) {
		keyspace.push_back(a);
	} else {
		for(int i=l; i<=r; i++) {
			swap(a[l], a[i]);
			permute(a, l+1, r, keyspace);
			swap(a[l], a[i]);
		}
	}
}

vector<string> generate_key_space(string text)
{
	set<char> unique_set;
	vector<string> keyspace;
	set<char> :: iterator itr;
	
	for(auto c : text) {
		unique_set.insert(c);
	}
	
	for(auto c : unique_set) {
		unique_string.push_back(c);
	}
	
	permute(unique_string, 0, unique_string.length()-1, keyspace);
	
	return keyspace;
	
}

string encrypt(string plain_text, string unique, string key)
{
	string cipher_text = "";
	
	for(char c : plain_text) {
		int index = unique.find(c);
		cipher_text += key[index];
	}
	return cipher_text;
}

void show_frequency(string plain_text, string cipher_text)
{
	map<char, int> p_map;
	map<char, int> c_map;
	
	for(char c : plain_text) {
		p_map[c]++;
		c_map[c]++;
	}
	
	cout << "Frequency\tPlaintext\tCipherText\n";
	for(int i=0; i<plain_text.length(); i++) {
		cout << (float)p_map[plain_text[i]]/plain_text.length() << "\t\t" << plain_text[i] << "\t\t" << cipher_text[i] << endl;
	}
}

int main()
{
	
	srand(time(NULL));
	
	string plain_text = read_from_file();
	vector<string> keyspace = generate_key_space(plain_text);
	
	for(string k : keyspace) {
		cout << k << " ";
	}
	
	cout << endl;
	
	string key = keyspace[rand() % keyspace.size()];
	cout << key << endl;
	
	string cipher_text = encrypt(plain_text, unique_string, key);
	cout << cipher_text << endl;
	
	show_frequency(plain_text, cipher_text);
	
	return 0;
	
}