#include <bits/stdc++.h>

using namespace std;

typedef struct
{
	int row;
	int col;
}POSITION;

vector<vector<char>> playfair_matrix(5);

string remove_duplicates(string data)
{

	int index = 0;
	string unique_string = "";
	bool flag = false;
	
	unique_string.push_back(data[0]);
	
	for(int i=1; i<data.length(); i++) {
		flag = false;
		for(auto c : unique_string) {
			if(c == data[i]) {
				flag = true;
			}
		}
		
		if(flag == false) {
			unique_string.push_back(data[i]);
		}
	}
	
	return unique_string;
	
}

string remove_spaces(string text)
{
	
	string res = "";
	
	for(auto c : text) {
		if(c != ' ') {
			res += c;
		}
	}
	
	return res;
	
}

void generate_playfair_matrix(string key)
{
	
	set<char> alphabets_set {'A','B','C','D','E','F','G','H','I','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	
	string unique_string = "";
	
	int row_index = 0, col_index = 0;
	
	unique_string = remove_duplicates(key);
	
	//remove the alphabets from aplhabets set based on the key
	for(auto c : unique_string) {
		if(alphabets_set.count(c)) {
			alphabets_set.erase(c);
		}
	}
	
	//Algorithm for inserting values to the matrix
	playfair_matrix[row_index] = vector<char>(5);
	for(auto v : unique_string) {
		if(col_index >= 5) {
			row_index+=1;
			col_index = 0;
			playfair_matrix[row_index] = vector<char>(5);
		}
		playfair_matrix[row_index][col_index] = v;
		col_index += 1;
		
	}
	for(auto v : alphabets_set) {
		if(col_index >= 5) {
			row_index+=1;
			col_index = 0;
			playfair_matrix[row_index] = vector<char>(5);
		}
		playfair_matrix[row_index][col_index] = v;
		col_index += 1;
	}
	
}

POSITION get_position(char ch)
{
	
	POSITION location;
	
	for(int i=0; i<5; i++) {
		for(int j=0; j<5; j++) {
			if(ch == playfair_matrix[i][j]) {
				location = {i, j};
				return location;
			}
		}
	}
	
	return location;
	
} 

void show_playfair_matrix()
{
	
	for(int i=0; i<5; i++) {
		for(int j=0; j<5; j++) {
			cout << playfair_matrix[i][j] << " ";
		}
		cout << endl;
	}
	
}

string modify_plaintext(string plain_text)
{
	
	string m1="", m2="", m3="";
	char ch;
	
	m1 = plain_text;
	
	for(int i=0; i<m1.length(); i++) {
		ch = m1[i];
		if(ch == m1[i+1]) {
			m2.push_back(ch);
			m2.push_back('x');
		} else {
			m2.push_back(ch);
		}
	}
	
	for(auto c : m2) {
		m3 += toupper(c);
	}
	
	while(m3.length() %2 != 0) {
		m3 += 'X';
	}
	
	return m3;
	
}

string playfair_encrypt(string plain_text)
{
	
	string cipher_text = "";
	int x1, x2, y1, y2;
	
	
	for(int i=0; i<plain_text.length(); i += 2) {
		
		POSITION p1 = get_position(plain_text[i]);
		POSITION p2 = get_position(plain_text[i+1]);
		x1 = p1.row;
		y1 = p1.col;
		x2 = p2.row;
		y2 = p2.col;
		
		if(x1 == x2) {
			cipher_text.append(1, playfair_matrix[x1][(y1+1)%5]);
			cipher_text.append(1, playfair_matrix[x2][(y2+1)%5]);
		} else if(y1 == y2) {
			cipher_text.append(1, playfair_matrix[(x1+1)%5][(y1)]);
			cipher_text.append(1, playfair_matrix[(x2+1)%5][(y2)]);
		} else {
			cipher_text.append(1, playfair_matrix[x1][y2]);
			cipher_text.append(1, playfair_matrix[x2][y1]);
		}
	}
	
	return cipher_text;
	
}

string playfair_decrypt(string cipher_text)
{
	
	string plain_text = "";
	int x1, x2, y1, y2;
	
	for(int i=0; i<cipher_text.length(); i += 2) {
		
		POSITION p1 = get_position(cipher_text[i]);
		POSITION p2 = get_position(cipher_text[i+1]);
		x1 = p1.row;
		y1 = p1.col;
		x2 = p2.row;
		y2 = p2.col;
		
		if(x1 == x2) {
			plain_text.append(1, playfair_matrix[x1][--y1 < 0 ? 4 : y1]);
			plain_text.append(1, playfair_matrix[x2][--y2 < 0 ? 4 : y2]);
		} else if(y1 == y2) {
			plain_text.append(1, playfair_matrix[--x1 < 0 ? 4 : x1][y1]);
			plain_text.append(1, playfair_matrix[--x2 < 0 ? 4 : x2][y2]);
		} else {
			plain_text.append(1, playfair_matrix[x1][y2]);
			plain_text.append(1, playfair_matrix[x2][y1]);
		}
	}
	
	return plain_text;
	
}

int main()
{
	
	int number_of_keys;
	
	string message, key, extra_line, plain_text;
	string modified_message, cipher_text, decrypted_text;
	
	cout << "Enter Plain text: ";
	getline(cin, message);
	
	cout << "Enter number of keys: ";
	cin >> number_of_keys;
	
	getline(cin, extra_line);
	
	while(--number_of_keys >= 0) {
		cout << "Enter Key: ";
		getline(cin, key);
		transform(key.begin(), key.end(), key.begin(), ::toupper);
		generate_playfair_matrix(key);
		show_playfair_matrix();
		
		cout << endl;
		
		plain_text = remove_spaces(message);
		modified_message = modify_plaintext(plain_text);
		cout << modified_message << endl;
		
		cipher_text = playfair_encrypt(modified_message);
		cout << cipher_text;
		
		cout << endl;
		
		decrypted_text = playfair_decrypt(cipher_text);
		cout << decrypted_text;
		
		cout << endl;
	}
	
	return 0;
	
}