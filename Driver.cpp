#include "HashTable.h"
#include <iostream>
#include <string>

int main() {
	int size = 50;
	int probes = 50;
	int cOne = 1;
	int cTwo = 1;
	char probe_type = 'q';
	string keys[50] = { "Kobe","trace","cat","dad","crate","dog","tac","act","Jordan","baadbeef","7779311","racecar",
		"abcdef","abcef","abc","Jeffery","beefbaad","MakotoShishio","Bean","randerman","1024","2048","3072","4096",
		"5120","6144","7168","8192","9216","6441","6871","8912","2916","4028","Bryant","Michael",
		"has","been","reluctant","to","turn","over","information","optimistic","when","asked","\"dream job\"","Rams",
		"Kings","Blackhawks" };

	int values[50] = { 1,2,3,4,5,6,7,8,9,10,
		11,12,13,14,15,16,17,18,19,20,
		21,22,23,24,25,26,27,28,29,30,
		31,32,33,34,35,36,37,38,39,40,
		41,42,43,44,45,46,47,48,49,50 };

	HashTable table(size, probe_type, probes, cOne, cTwo);
	int i = 0;
	while ( i < size) {
		table.add_key(keys[i], values[i]);
		i++;
	}
	
	int val = 0;
	table.value("6441", val);
	cout << val;
	/*
	for (i = 0; i < size; i++) {
		int val = 0;
		table.value(keys[i], val);
		cout << val << endl;
	}

	
	table.resize_table(60);
	table.print_table();
	table.erase_table();
	table.print_table();
	*/
	system("pause");
	return 0;
}
