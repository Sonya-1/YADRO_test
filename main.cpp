#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <regex> 
#include "Club.h"
using namespace std;

bool check_time(string& time) {
	const regex pattern("^([01][0-9]|2[0-3]):[0-5][0-9]$");
	if (regex_match(time, pattern)) {
		return true;
	}
	else {
		return false;
	}
}

bool check_int(string& d) {
	const regex pattern("^[0-9]+$");
	if (regex_match(d, pattern)) {
		return true;
	}
	else {
		return false;
	}
}

int parse_time(string time) {
	string h;
	h.push_back(time.at(0));
	h.push_back(time.at(1));
	string m;
	m.push_back(time.at(3));
	m.push_back(time.at(4));
	return (stoi(h) * 60 + stoi(m));
}

void check_parse_action(string& act, action& action_struct, info& inf) {
	const regex pattern(R"(^(([01][0-9]|2[0-3]):([0-5][0-9]))\s([0-9])\s([-_a-z0-9]+)(\s([0-9]+))?$)");
	if (regex_match(act, pattern)) {
		smatch m;
		regex_search(act, m, pattern);
		action_struct.time = parse_time(m[1]);
		action_struct.act = stoi(m[4]);
		action_struct.client_name = m[5];
		if (m[7] != "") {
			if (stoi(m[7]) <= inf.computers) {
				action_struct.computer = stoi(m[7]);
			}
			else {
				throw (act);
			}
		}
	}
	else {
		throw (act);
	}
}

void read_file(string file_name, info& inf, vector<action>& actions) {
	ifstream input(file_name);

	if (!input.is_open()) {
		cout << "file can not be open" << endl;
		exit(1);
	}

	string comp;
	string time;
	string time1;
	string pr;

	input >> comp;
	if (check_int(comp)) {
		inf.computers = stoi(comp);
	}
	else {
		input.close();
		throw (comp);
	}

	input >> time;
	if (check_time(time)) {
		inf.time_start = parse_time(time);
	}
	else {
		input.close();
		throw (time);
	}

	input >> time1;
	if (check_time(time1)) {
		inf.time_end = parse_time(time1);
	}
	else {
		input.close();
		throw (time + time1);
	}
	
	input >> pr;
	if (check_int(pr)) {
		inf.price = stoi(pr);
	}
	else {
		input.close();
		throw (pr);
	}

	string act;
	int max_time = 0;
	while (getline(input, act)) {
		if (act != "") {
			action actn;
			try {
				check_parse_action(act, actn, inf);
			}
			catch (string& e) {
				cerr << e << endl;
				input.close();
				exit(1);
			}
			if (actn.time < max_time && max_time != 0) {
				input.close();
				throw (act);
			}
			else {
				max_time = actn.time;
			}

			actions.push_back(actn);
		}

	}
	input.close();
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
	    cout << "not enough arguments to call" << endl;
	    exit(1);
	}
	string filename = argv[1];
	info inf;
	vector<action> actions;
	
	try {
		read_file(filename, inf, actions);
	}
	catch (string& e) {
		cerr << e << endl;
		exit(1);
	}
	Club cl(inf, actions);
	cl.club_work();
	return 0;
}
