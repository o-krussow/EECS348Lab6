#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define N 100

using namespace std;

void printmatrix(string** matrix, int num_rows) {
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < N; j++) {
			cout << matrix[i][j] << '\t';
		}
		cout << endl;
	}
}

void addmatrix(string** matrix1, string** matrix2, int num_rows, int num_cols) {
	string** matrix3 = new string*[N];

	for (int i = 0; i < num_rows; i++) {
		matrix3[i] = new string[N];
		for (int j = 0; j < num_cols; j++) {
			matrix3[i][j] = to_string(stoi(matrix1[i][j]) + stoi(matrix2[i][j]));
		}
	}
	printmatrix(matrix3, num_rows);
}

void submatrix(string** matrix1, string** matrix2, int num_rows, int num_cols) {
	string** matrix3 = new string*[N];

	for (int i = 0; i < num_rows; i++) {
		matrix3[i] = new string[N];
		for (int j = 0; j < num_cols; j++) {
			matrix3[i][j] = to_string(stoi(matrix1[i][j]) - stoi(matrix2[i][j]));
		}
	}
	printmatrix(matrix3, num_rows);
}

string* get_row(string** matrix, int req_row, int num_cols) {
	string* row = new string[N];

	for (int i = 0; i < num_cols; i++) {
		row[i] = matrix[req_row][i];
	}

	return row;
}

string* get_col(string** matrix, int req_col, int num_rows) {
	string* col = new string[N];

	for (int i = 0; i < num_rows; i++) {
		col[i] = matrix[i][req_col];
	}

	return col;
}

int dot_product(string* m1, string* m2, int num_rows) {
	int sum = 0;

	for (int i = 0; i < num_rows; i++) {
		sum += (stoi(m1[i]) * stoi(m2[i]));
	}
	return sum;
}

void multmatrix(string** matrix1, string** matrix2, int num_rows, int num_cols) {
	string** matrix3 = new string*[N];

	string* curr_row;
	string* curr_col;

	for (int i = 0; i < num_rows; i++) {
		matrix3[i] = new string[N];
		for (int j = 0; j < num_cols; j++) {
			curr_row = get_row(matrix1, i, num_cols);
			curr_col = get_col(matrix2, j, num_rows);

			matrix3[i][j] = to_string(dot_product(curr_row, curr_col, num_rows));
		}
	}
	printmatrix(matrix3, num_rows);
}

string** get_matrix(string filename, int* num_rows, int* num_cols) {
	fstream file(filename, ios::in);

	string line;
	string arr_line[N];
	string** matrix = new string*[N];
	int inner_counter;
	int outer_counter = 0;

	while (getline (file, line)) {
		stringstream ss(line);
		string word;
		inner_counter = 0;
		while (ss >> word) {
			arr_line[inner_counter] = word;
			inner_counter++;
		}

		if (inner_counter > 1) {
			matrix[outer_counter] = new string[N];

			for (int i = 0; i < sizeof(arr_line)/sizeof(arr_line[0]); i++) {
				matrix[outer_counter][i] = arr_line[i];
			}

			outer_counter++;
		}
	}
	file.close();

	*num_rows = outer_counter;
	*num_cols = inner_counter;

	return matrix;
}

int main() {
	
	int num_rows;
	int num_cols;

	string** matrix1 = get_matrix("ma.txt", &num_rows, &num_cols);
	string** matrix2 = get_matrix("mb.txt", &num_rows, &num_cols);

	cout << "Owen Krussow" << endl;
	cout << "EECS 348 Lab 6" << endl;

	cout << "Matrix A:" << endl;
	printmatrix(matrix1, num_rows);

	cout << "Matrix B:" << endl;
	printmatrix(matrix2, num_rows);

	cout << "Matrix Sum (A+B):" << endl;
	addmatrix(matrix1, matrix2, num_rows, num_cols);

	cout << "Matrix Product (A*B):" << endl;
	multmatrix(matrix1, matrix2, num_rows, num_cols);

	cout << "Matrix Difference (A-B):" << endl;
	submatrix(matrix1, matrix2, num_rows, num_cols);


	return 0;
}






