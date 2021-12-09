#include <bits/stdc++.h>

using namespace std;

vector<vector<char>> generate_key_based_plain_text_matrix(string plain_text, int key_length, int rows)
{
	
	int index = 0;
	
	vector<vector<char>> text_matrix(rows);
	
	for(int i=0; i<rows; i++) {
		text_matrix[i] = vector<char>(key_length);
		for(int j=0; j<key_length; j++) {
			text_matrix[i][j] = plain_text[index];
			index+=1;
		}
	}
	
	return text_matrix;
	
}

vector<vector<char>> generate_key_based_cipher_text_matrix(string cipher_text, string key, int rows)
{
	
	int index = 0;
	
	vector<vector<char>> cipher_matrix(rows);
	
	for(int i=0; i<rows; i++) {
		cipher_matrix[i] = vector<char>(key.length());
	}
	
	for(int i=0; i<key.length(); i++) {
		for(int j=0; j<rows; j++) {
			cipher_matrix[j][key.find(i+'1')] = cipher_text[index++];
		}
	}
	
	return cipher_matrix;
	
}

void display_text_matrix(vector<vector<char>> text_matrix, int rows, int cols)
{
	
	for(int i=0; i<rows; i++) {
		for(int j=0; j<cols; j++) {
			cout << text_matrix[i][j] << " ";
		}
		cout << endl;
	}
}

string transposition_encrypt(string plain_text, string key)
{
	
	string cipher_text = "";
	int rows;
	
	vector<vector<char>> text_matrix;
	
	while(plain_text.length() % key.length() != 0) {
		plain_text.push_back('x');
	}
	
	rows = ceil((float)(plain_text.length() / key.length()));
	
	text_matrix = generate_key_based_plain_text_matrix(plain_text, key.length(), rows);
	
	for(int i=0; i< key.length(); i++) {
		for(int j=0; j<rows; j++) {
			cipher_text += text_matrix[j][key.find(i + '1')];
		}
	}
	
	display_text_matrix(text_matrix, rows, key.length());
	
	return cipher_text;

}

string transposition_decrypt(string cipher_text, string key)
{
	
	string de_cipher_text = "";
	
	int rows;
	
	vector <vector<char>> cipher_matrix;
	
	rows = (ceil)((float)(cipher_text.length() / key.length()));
	
	cipher_matrix = generate_key_based_cipher_text_matrix(cipher_text, key, rows);
	
	for(int i=0; i<rows; i++) {
		for(int j=0; j<key.length(); j++) {
			de_cipher_text += cipher_matrix[i][j];
		}
	}
	
	display_text_matrix(cipher_matrix, rows, key.length());
	
	return de_cipher_text;
}

int main()
{
	
	string plain_text, key, cipher_text, decrypted_text;
	
	cout << "Enter Plain Text: ";
	getline(cin, plain_text);
	
	cout << "Enter Key(Numbers only): ";
	getline(cin, key);
	
	cout << "Transposition Encryption: " << endl;
	cipher_text = transposition_encrypt(plain_text, key);
	cout << cipher_text;
	
	cout << endl;
	
	cout << "Transposition Decryption: " << endl;
	decrypted_text = transposition_decrypt(cipher_text, key);
	decrypted_text.erase(plain_text.length());
	cout << decrypted_text;
	
	cout << endl;
	
	return 0;
}