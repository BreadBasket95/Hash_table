
#include <vector>
#include <iostream>
#include "HashTable.h"

using namespace std;

int HashTable::hash_fn(string k) { // This function recieves a string and returns the indext
	int value = get_val(k);        // based on the hashing function used
	int index = value%num_cells;
	return index;
}

int HashTable::lin_probe(string k, int i) {
	return (hash_fn(k) + i) % num_cells;
}
int HashTable::quad_probe(string k, int i) {
	return (hash_fn(k) + c1*(i*i) + c2*i) % num_cells;
}
int HashTable::find_cell(string k) {
	int cell;
	if (col_res_type == 'l') {
		for (int i = 0; i < max_probes; i++) {
			cell = lin_probe(k, i);
			if (htable[cell].key == k)
				return cell;
			if (htable[cell].status == 0)
				return -1;
		}
		return -1;
	}
	else if (col_res_type == 'q') {
		for (int i = 0; i < max_probes; i++) {
			cell = quad_probe(k, i);
			if (htable[cell].key == k)
				return cell;
			if (htable[cell].status == 0)
				return -1;
		}
		return -1;
	}
	return -1;
}

bool HashTable::add_key(string key, int value){
	int cell = hash_fn(key);
	if (find_cell(key) != -1) { // This checks to see if the key value pair exists before adding it.
		htable[cell].key = key;	// if the key exists, it is overwritten. This prevents duplicates 
		htable[cell].value = value;
		htable[cell].status = 1;
		return true;
	}
	else{
		if (col_res_type == 'l') {  // Adds a key-value pair using linear probing
			for (int i = 0; i < max_probes; i++) { 
				cell = lin_probe(key, i);
				if (htable[cell].status != 1) {
					htable[cell].status = 1;
					htable[cell].key = key;
					htable[cell].value = value;
					num_keys++;
					return true;
				}
			}
			return false;
		}
		else if (col_res_type == 'q') { // Adds a key-value pair using quadratic probing
			for (int i = 0; i < max_probes; i++) {
				cell = quad_probe(key, i);
				if (htable[cell].status != 1) {
					htable[cell].status = 1;
					htable[cell].key = key;
					htable[cell].value = value;
					num_keys++;
					return true;
				}
			}
			return false;
		}
		else cout << "Invalid collision resolution type" << endl;
		return false;
	}
return false;
}
bool HashTable::remove_key(string key) {
	if (find_cell(key) != -1) { // Checks if the key to be deleted exists
		int index = find_cell(key);
		htable[index].status = -1; // Lazy deletion
		num_keys--;
		return true;
	}
	else return false;
}
void HashTable::erase_table() {
	htable.clear();
	num_keys = 0;
	for (int i = 0; i < num_cells; i++) { // This simply clears the table and repopulates it with new Pair Objects
		Pair object;
		htable.push_back(object);
	}
}
bool HashTable::resize_table(int new_size) {
	int original_size = num_cells; // Stores the original size of the table before resizing
	num_cells = new_size; 
	vector <Pair> temptable; // Temporary table, its a copy of the original table
	temptable = htable;
	htable.clear(); // clears the table in preparation for refilling
	htable.resize(new_size); 
	for (int i = 0; i < new_size; i++) { // populates the tables with empty key-value pairs
		Pair object;
		htable[i] = object;
	}
	for (int i = 0; i < original_size; i++) { // Loops through the original table
		if (temptable[i].status == 1) {  // Checks each cell for a valid key-value pair
			bool test = add_key(temptable[i].key, temptable[i].value); // Adds the key-value pair
			if(test == false){ // if add_key returns false, the table cannot be resized and it is reverted
				htable.clear();
				num_cells = original_size;
				htable.resize(num_cells);
				htable = temptable;
				temptable.clear();
				cout << "can't resize" << endl;
				return false;
			}
		}
	}
	return true;
}
bool HashTable::value(string key, int &value_to_find) {  // This functions searches the table for the specified key
	if (find_cell(key) == -1)					 // If the key-value pair exists in the table,
		return false;							 // it returns true and sets value_to_find to the value of the pair
	else {
		value_to_find = htable[find_cell(key)].value;
		return true;
	}
}
int HashTable::get_val(string val) {               // This function takes a string that will be used as a key
	int sum = 0;                                   // and returns the sum of the ASCII values of the string 
	for (unsigned int i = 0; val.size() > i; i++) {// for use in indexing
		sum += val[i];
	}
	return sum;
}
void HashTable::print_table() {
	for (int i = 0; i < num_cells; i++) {
		cout << "Index: " << i << " Key: " << htable[i].key << " Value: " << htable[i].value << " Status: " << htable[i].status << endl;
	}
}
