#ifndef CLUB_H
#define CLUB_H

#define CLIENT_CAME 1
#define CLIENT_SAT_TABLE 2
#define CLIENT_WAIT 3
#define CLIENT_LEFT 4

#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <algorithm> 
using namespace std;

struct info {
	int computers = 0;
	int time_start = 0;
	int time_end = 0;
	int price = 0;
};

struct work_place {
	string client;
	int table = 0;
	int time_start = 0;
	int time_end = 0;
	int revenue = 0;
};

struct client {
	string name;
	int computer = 0;
	vector<int> table{ 0 };

	client(std::string n) {
		name = n;
	}
	client() {}

	client& operator=(const client& clt) {
		name = clt.name;
		computer = clt.computer;
		return *this;
	}
};

static string time_format(int time) {
	string time_string = "";
	int hour = time / 60;
	time_string += (hour < 10 ? "0" : "") + to_string(hour);
	time_string += ":";
	int minutes = time % 60;
	time_string += (minutes < 10 ? "0" : "") + to_string(minutes);
	return time_string;
}

struct action {
	int time = 0;
	int act = 0;
	string client_name;
	int computer = 0;

	void print_action() {
		cout << time_format(time) << " ";
		cout << act << " ";
		cout << client_name << " ";
		if (computer != 0) {
			cout << computer;
		}
		cout << endl;
	}
};

class Club {
public:
	info inf;
	vector<client> queue;
	vector<int> tables{ 0 };
	vector<client> clients;
	vector<work_place> wp;
	vector<action> actions;

	Club();
	Club(info inf, vector<action> actions);
	int busy_tables();
	void remove_client(vector<client>& clients_vector, string client_name);
	void set_to_computer(string& client_name, int comp, action& curr_action);
	void client_left_table(string& client_name, int time);
	bool client_in_club(string& client_name);
	client* find_client(string& client_name);
	void client_came(action& curr_action);
	void client_sat_table(action& curr_action);
	void client_wait(action& curr_action);
	void client_left(action& curr_action);
	void close_club();
	void count_revenue();
	void club_work();
};

#endif
