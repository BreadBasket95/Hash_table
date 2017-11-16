#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H
/*******************************************************************************
* Pair.h
*
* author: Marc Moore
* date created: 11/16/2017
* last updated: 11/16/2017
*
* This class creates a vector of pair objects, it supports two different
* collision resolution types, cell searching, and table clearing
*
*******************************************************************************/
#include "Pair.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class HashTable {
private:
	vector <Pair> htable;
	int num_cells = 0;  // the total number of cells for the table.
	int max_probes = 0; // The maximum number of probes any search will perfom
	char col_res_type;  // the collision resolution type, 'l' for linear probing, 'q' for quadratic probing
	int c1, c2;         // The coefficients for quadratic probing.
	int hash_fn(string);// The hash function returns the value of the string % table size
	int lin_probe(string, int); // linear probing resolution operator
	int quad_probe(string, int); // quadratic probing resolution operator
	int find_cell(string);   // Returns the index of the cell if it is found, returns -1 otherwise
	int num_keys;  // The counter to track the number of keys mapped to the table
public:
	HashTable(int size, char probe_type, int probes, int cOne, int cTwo) {
	num_cells = size;
	col_res_type = probe_type;
	max_probes = probes;
	if (probe_type == 'l') { // sets the coefficients to zero if linear probing is selected.
		c1 = 0;
		c2 = 0;
	}
	else { 
		c1 = cOne;
		c2 = cTwo;
	}
	htable.resize(num_cells);
	for (int i = 0; i < num_cells; i++) {
		
		Pair object;
		htable[i] = object;// this populates the table with pair objects 
		}
	}
	~HashTable() { // The destructor clears all the values in the table, and sets member variables to zero
		erase_table();
		num_cells = 0;
		max_probes = 0;
		col_res_type = '\0';
		c1 = 0;
		c2 = 0;
		num_keys = 0;
	}

	bool add_key(string, int);
	bool remove_key(string);
	void erase_table();
	bool resize_table(int);
	bool value(string, int &);
	int get_val(string);
	void print_table();
						
};

#endif