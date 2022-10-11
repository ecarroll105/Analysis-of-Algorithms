//Evan Carroll
//Analysis of Algorithms
//Prof. D'Antonio
//Homework 2 Question 5
//Libraries
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <algorithm>
//Preprocessor directives
using namespace std;
using namespace std::chrono;
//constant declarations
const int ARRAY_SIZE = 10000;
//Function Prototypes
void insertionSort(int array[], int arraySize);
void mergeSort(int array[], int p1, int r1);
int *merge(int array[], int p2, int q2, int r2);
void quickSort(int array[], int p, int r);
int partition(int array[], int p, int r);
//Main function
int main(){
	//variable creation
	int array1[ARRAY_SIZE]; //creating the array
	ifstream inputFile; //creating text file to read from
	int count = 0; //creating count variable for while loop
	//file reading and copying to array
	inputFile.open("Random10000.txt"); //Opening file
	while((count < ARRAY_SIZE) && (array1[count] >> inputFile)){ //while count is less than the array size and hasn't taken the data for the array location the while loop will continue
		count++; //incrementing count every time an element is added to the array
	}
	inputFile.close(); //closing the file
	//timing insertionSort
	auto start1 = system_clock::now(); //starting timer for clock
	insertionSort(array1, ARRAY_SIZE); //running insertion sort
	auto stop1 = system_clock::now(); //stopping the timer for clock
	auto elapsed1 = stop1 - start1; //calculating the elapsed time
	cout << "Time for Insertion Sort is: " << elapsed1 << " seconds." << endl;
	//timing mergeSort
	auto start2 = system_clock::now();
	mergeSort(array1, ARRAY_SIZE);
	auto stop2 = system_clock::now();
	auto elapsed2 = stop2 - start2;
	cout << "Time for Merge Sort is: " << elapsed2 << " seconds." << endl;
	//timing quickSort
	auto start3 = system_clock::now();
	quickSort(array1, ARRAY_SIZE);
	auto stop3 = system_clock::now();
	auto elapsed3 = stop3 - start3;
	cout << "Time for Quick Sort is: " << elapsed3 << " seconds." << endl;
	//if statement for the case that insertion sort is quickest
	if((elapsed1 > elapsed2) && (elapsed1 > elapsed3)){
		cout << "Insertion Sort is the quickest with " << elapsed1 << " seconds." << endl;
		if(elapsed2 > elapsed3){
			cout << "Merge Sort is the second quickest with " << elapsed2 << " seconds." << endl;
			cout << "Quick Sort is the slowest with " << elapsed3 << " seconds." << endl;
		}
		else{
			cout << "Quick Sort is the second quickest with " << elapsed3 << " seconds." << endl;
			cout << "Merge Sort is the slowest with " << elapsed2 << " seconds." << endl;
		}
	}
	//else if for the case that merge sort is quickest
	else if((elapsed2 > elapsed1) && (elapsed2 > elapsed3)){
		cout << "Merge Sort is the quickest with " << elapsed2 << " seconds." << endl;
		if(elapsed1 > elapsed3){
			cout << "Insertion Sort is the second quickest with " << elapsed1 << " seconds." << endl;
			cout << "Quick Sort is the slowest with " << elapsed3 << " seconds." << endl;
		}
		else{
			cout << "Quick Sort is the second quickest with " << elapsed3 << " seconds." << endl;
			cout << "Insertion Sort is the slowest with " << elapsed1 << " seconds." << endl;
		}
	}
	//else if for the case that quick sort is fastest
	else if((elapsed3 > elapsed1) && (elapsed3 > elapsed2)){
		cout << "Quick Sort is the quickest with " << elapsed3 << " seconds." << endl;
		if(elapsed1 > elapsed2){
			cout << "Insertion Sort is the second quickest with " << elapsed1 << " seconds." << endl;
			cout << "Merge Sort is the slowest with " << elapsed2 << " seconds." << endl;
		}
		else{
			cout << "Merge Sort is the second quickest with " << elapsed2 << " seconds." << endl;
			cout << "Insertion Sort is the slowest with " << elapsed1 << " seconds." << endl;
		}
	}
}
//Function Definitions
void insertionSort(int array[], int arraySize){
	ifstream inputFile;
	int count = 0;
	int key, j;
	for(int i = 0; i < arraySize; i++){
		key = array[i];
		j = i - 1;
		while((j >= 0) && (array[j] > key)){
			array[j + 1] = array[j];
			j = j - 1;
		}
		array[j + 1] = key;
	}
	inputFile.open("insertSorted.txt");    
    if(!inputFile)
    {
        cout << "Error opening input file" << endl;
        return 1;
    }
    else{
    	while((count < arraySize) && (inputFile >> array[count])
        count++;
	}
}
void mergeSort(int array[], int p, int r){
	ifstream inputFile;
	int count = 0;
	if(p < r){
		int q = (p + r)/2;
		mergeSort(array, p, q);
		mergeSort(array, (q + 1), r);
		array = merge(array, p, q , r);
	}
	else{
		cout << "Array is already sorted." << endl;
	}
	inputFile.open("mergeSorted.txt");    
    if(!inputFile)
    {
        cout << "Error opening input file" << endl;
        return 1;
    }
    else{
    	while((count < r) && (inputFile >> array[count])
        count++;
	}
}
int *merge(int array[], int p2, int q2, int r2){
	int auxArray[r2];
	int first = p2;
	int second = q2 + 1;
	int aux = p2;
	while((first <= q2) && (second <= r2)){
		if(array[first] <= array[second]){
			auxArray[aux] = array[first];
			first = first + 1;
		}
		else{
			auxArray[aux] = array[second];
			second = second + 1;
		}
		aux = aux + 1;
	}
	while(first <= q2){
		auxArray[aux] = array[first];
		first = first + 1;
		aux = aux + 1;
	}
	while(second <= r2){
		auxArray[aux] = array[second];
		second = second + 1;
		aux = aux + 1;
	}
	for(int i = p2; i < r2; i++){
		array[i] = auxArray[i];
	}
	return array;
}
void quickSort(int array[], int p, int r){
	ifstream inputFile;
	int count = 0;
	if(p < r){
		int q = partition(array, p , r);
		quickSort(array, p, (q-1));
		quickSort(array, (q+1), r);
	}
	inputFile.open("quickSorted.txt");    
    if(!inputFile)
    {
        cout << "Error opening input file" << endl;
        return 1;
    }
    else{
    	while((count < r) && (inputFile >> array[count])
        count++;
	}
}
int partition(int array[], int p, int r){
	int x, pos, i;
	pos = (p + (r - p)) / 2;
	swap(array[pos], array[r]);
	x = array[r];
	i = p - 1;
	for(int j = p; j = r - 1; j++){
		if(array[j] <= x){
			i = i + 1;
			swap(array[i], array[j]);
		}
	}
	swap(array[i + 1], array[r]);
	return pos;
}
