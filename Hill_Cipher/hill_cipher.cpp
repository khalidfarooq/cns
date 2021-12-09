#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> key_matrix(3);

int mod_26(int value)
{
	return value >= 0 ? (value % 26) : (26 - (abs(value) % 26));
}

vector<vector<int>> multiply_matrix(vector<vector<int>> a, int a_rows, int a_cols, vector<vector<int>> b, int b_rows, int b_cols)
{
	vector<vector<int>> resultant_matrix(a_rows, vector<int> (b_cols, 0));
	
	for(int i=0; i<a_rows; i++) {
		for(int j=0; j<b_cols; j++) {
			for(int k=0; k<b_rows; k++) {
				resultant_matrix[i][j] += a[i][k] * b[k][j];
			}
			resultant_matrix[i][j] = mod_26(resultant_matrix[i][j]);
		}
	}
	
	return resultant_matrix;
}

vector<vector<int>> generate_plain_text_matrix(string plain_text, int key_order)
{
	
	int rows, index = 0;
	
	rows = (plain_text.length()) / key_order;
	vector<vector<int>> plain_text_matrix(rows);
	
	for(int i=0; i<rows; i++) {
		plain_text_matrix[i] = vector<int>(key_order);
		for(int j=0; j<key_order; j++) {
			plain_text_matrix[i][j] = plain_text[index++] - 'a';
		}
		
	}
	
	// for debugging purpose
	for(int i=0; i<rows; i++) {
		for(int j=0; j<key_order; j++) {
			cout << plain_text_matrix[i][j] << "\t";
		}
		cout << endl;
	}
	
	return plain_text_matrix;
	
}

int calculate_determinant(vector<vector<int>> matrix, int order)
{
	int determinant_value = 0;
	
	if(order == 2) {
		determinant_value += (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]); 
	} else if(order == 3) {
		determinant_value += ((matrix[0][0]) * ((matrix[1][1] * matrix[2][2]) - (matrix[2][1] * matrix[1][2]))) - ((matrix[0][1]) * ((matrix[1][0] * matrix[2][2]) - (matrix[2][0] * matrix[1][2]))) + ((matrix[0][2]) * ((matrix[1][0] * matrix[2][1]) - (matrix[2][0] * matrix[1][1])));
	}
	
	return determinant_value;
	
}

int find_multiplicative_inverse(int r, int d)
{
	int i=0;
	int old_d;
	
	int p[100] = {0, 1};
	int q[100] = {0};
	
	while(r != 0) {
		q[i] = d/r;
		old_d = d;
		d = r;
		r = old_d % r;
		
		if(i > 1) {
			p[i] = mod_26(p[i-2] - (p[i-1] * q[i-2]));
		}
		i += 1;
	}
	
	if(i == 1) {
		return 1;
	}
	
	return p[i] = mod_26(p[i-2] - (p[i-1] * q[i-2]));
}

string hill_encrypt(string plain_text, int key_order)
{
	string cipher_text = "";
	int rows;
	
	vector <vector <int>> plain_text_matrix;
	vector <vector <int>> cipher_text_matrix;
	
	while(plain_text.length() % key_order != 0) {
		plain_text.push_back('x');
	}
	
	rows = (plain_text.length()) / key_order;
	
	plain_text_matrix = generate_plain_text_matrix(plain_text, key_order);
	cipher_text_matrix = multiply_matrix(plain_text_matrix, rows, key_order, key_matrix, key_order, key_order);
	
	for(int i=0; i<rows; i++) {
		for(int j=0; j<key_order; j++) {
			cipher_text += (cipher_text_matrix[i][j] + 'a');
		}
	}
	
	return cipher_text;
	
}

int main()
{
	string plain_text, cipher_text;
	int order_of_key;
	
	cout << "Enter plain text: ";
	getline(cin, plain_text);
	
	cout << "Enter order of the key matrix: ";
	cin >> order_of_key;
	
	cout << "Enter key matrix elements: " << endl;
	for(int i=0; i<order_of_key; i++) {
		key_matrix[i] = vector<int>(3);
		for(int j=0; j<order_of_key; j++) {
			cin >> key_matrix[i][j];
		}
	}
	
	cout << "Key Matrix: " << endl;
	for(int i=0; i<order_of_key; i++) {
		for(int j=0; j<order_of_key; j++) {
			cout << key_matrix[i][j] << "\t";
		}
		cout << endl;
	}
	
	cout << endl;
	
	cout << "Plain text matrix: " << endl;
	cipher_text = hill_encrypt(plain_text, order_of_key);
	cout << "Encrypted text: " <<cipher_text << endl;
	
	cout << calculate_determinant(key_matrix, order_of_key) << endl;
	
	
	return 0;
}