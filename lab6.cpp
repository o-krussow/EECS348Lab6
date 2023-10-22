/*
 * Owen Krussow
 * EECS 348 Lab 6
 * Matrices from scratch
 * Oct 22nd, 2023
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define N 100

using namespace std;


void printmatrix(string** matrix, int num_rows) { // This function takes in a pointer to a matrix and the number of rows, and prints the matrix
	for (int i = 0; i < num_rows; i++) { //Loop through the rows
		for (int j = 0; j < N; j++) { //Doesn't really matter if we loop through more columns that don't exist, nothing prints
			cout << matrix[i][j] << '\t'; //Print elements of matrix seperated by tabs.
		}
		cout << endl; //Print newline once we're done with row.
	}
}

void addmatrix(string** matrix1, string** matrix2, int num_rows, int num_cols) { //This function takes in two matrices, the number of rows and columns, and adds the two matrices and prints the result.
	string** matrix3 = new string*[N]; //Making new matrix to store the result in.

	for (int i = 0; i < num_rows; i++) { //Looping through rows
		matrix3[i] = new string[N]; //Setting the current row of new matrix to be array of dynamically allocated strings.
		for (int j = 0; j < num_cols; j++) { //Looping through columns
			matrix3[i][j] = to_string(stoi(matrix1[i][j]) + stoi(matrix2[i][j])); //Adding the ith and jth rows/columns of matrix 1 and 2 and putting the result in matrix3.
		}
	}
	printmatrix(matrix3, num_rows); //Printing the result
}

void submatrix(string** matrix1, string** matrix2, int num_rows, int num_cols) { //This function takes in two matrices and subtracts matrix2 from matrix1.
	string** matrix3 = new string*[N]; //Making new matrix to store the result in.

	for (int i = 0; i < num_rows; i++) { //Looping through the rows
		matrix3[i] = new string[N]; //Setting the current row of the new matrix to be an array of dynamically allocated strings.
		for (int j = 0; j < num_cols; j++) { //Looping through columns
			matrix3[i][j] = to_string(stoi(matrix1[i][j]) - stoi(matrix2[i][j])); //Subtracting each element from each matrix and putting the result in matrix3.
		}
	}
	printmatrix(matrix3, num_rows); //Printing the result
}

string* get_row(string** matrix, int req_row, int num_cols) { //This function takes in a matrix, a requested row, and the number of columns in the matrix, and returns the requested row in the form of an array.
	string* row = new string[N]; //Making the row array

	for (int i = 0; i < num_cols; i++) { //Looping through the number of columns, since that's how many elements we have in the row.
		row[i] = matrix[req_row][i]; //Setting ith element of row variable to be ith element from the row of matrix.
	}

	return row; //Return the row
}

string* get_col(string** matrix, int req_col, int num_rows) { //This function takes in a matrix, a requested col, and the number of rows in the matrix, and returns the requested col in the form of an array.
	string* col = new string[N]; //Making the col array

	for (int i = 0; i < num_rows; i++) { //Looping through number of rows
		col[i] = matrix[i][req_col]; //Setting ith element of col variable to be the ith element from the col of the matrix.
	}

	return col; //Returning the col array.
}

int dot_product(string* m1, string* m2, int num_rows) { //This function takes in two "vectors" (but really, two arrays of strings) and finds the dot product of them.
	int sum = 0; //Sum of the dot product

	for (int i = 0; i < num_rows; i++) { //Looping through num_rows, doesn't matter if it's num_rows or num_cols because they need to match up between matrix 1 and 2 anyways to be allowed to do multiplication.
		sum += (stoi(m1[i]) * stoi(m2[i])); //Multiplying ith elements of m1 and m2, and adding the result to sum.
	}
	return sum; //Returning the dot product/sum
}

void multmatrix(string** matrix1, string** matrix2, int num_rows, int num_cols) { //Takes in two matrices to multiply together.
	string** matrix3 = new string*[N]; //Make new matrix

	string* curr_row; //To store current row and column to make things more readable.
	string* curr_col;

	for (int i = 0; i < num_rows; i++) { //Loop through each corresponding element of new matrix.
		matrix3[i] = new string[N]; //Setting current row of new matrix to be an array of dynamically allocated strings.
		for (int j = 0; j < num_cols; j++) { //Looping through columns
			curr_row = get_row(matrix1, i, num_cols); //Getting the current row from matrix1
			curr_col = get_col(matrix2, j, num_rows); //Getting the current col from matrix2

			matrix3[i][j] = to_string(dot_product(curr_row, curr_col, num_rows)); //Setting the current element of the new matrix to be the dot product of our current row and column.
		}
	}
	printmatrix(matrix3, num_rows); //Now we print the result
}

string** get_matrix(string filename, int* num_rows, int* num_cols) { //This function takes in a filename, and pointers to keep track of num_rows and num_cols for the matrix read in.
	fstream file(filename, ios::in); //Make a file stream for input

	string line; //Current line as string
	string arr_line[N]; //Current line in the form of an array of strings.
	string** matrix = new string*[N]; //Making our 2d matrix that we will eventually return.
	int inner_counter; //Inner counter, ends up keeping track of num_cols
	int outer_counter = 0; //Ends up keeping track of num_rows

	while (getline(file, line)) { //While we're able to keep reading in lines, keep reading them in.
		stringstream ss(line); //Create a string stream for the purpose of splitting the elements by spaces.
		string word; //String for the current "word"/element of matrix.
		inner_counter = 0; //Resetting the inner counter to 0 for every row of file.
		while (ss >> word) { //Piping next word from stream into word variable so we get rid of all the spaces.
			arr_line[inner_counter] = word; //Adding this word to the arr_line variable
			inner_counter++;
		}

		if (inner_counter > 1) { //Check to make sure that there was more than one element on the line, because we don't care about the first line of the file since we're finding that information internally.
			matrix[outer_counter] = new string[N]; //Initializing each row of matrix with array of dynamically allocated strings.

			for (int i = 0; i < sizeof(arr_line)/sizeof(arr_line[0]); i++) { //Loop through the arr_line variable.
				matrix[outer_counter][i] = arr_line[i]; //Set the current element in outer_counter row to current element in arr_line variable.
			}

			outer_counter++; //Increment row/outer_counter.
		}
	}
	file.close(); //Close the file to be polite

	*num_rows = outer_counter; //Dereference num_rows and num_cols and set them equal to outer and inner counter so we can keep track for the rest of this program.
	*num_cols = inner_counter;

	return matrix; //Return the matrix from the file.
}

int main() {
	
	int num_rows; //Make num_row and num_col variables to keep track.
	int num_cols;

	//Making our two matrices to operate on.
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






