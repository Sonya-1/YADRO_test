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

string time_format(int time) {
	string time_string = "";
	int hour = time / 60;
	time_string += (hour < 10 ? "0" : "") + to_string(hour);
	time_string += ":";
	int minutes = time % 60;
	if (minutes < 10) {
		time_string += "0" + to_string(minutes);
	}
	else {
		time_string += to_string(minutes);
	}
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

bool compare(client client1, client client2) {
	return (client1.name < client2.name);
}

class Club {
public:
	info inf;
	vector<client> queue;
	vector<int> tables{ 0 };
	vector<client> clients;
	vector<work_place> wp;
	vector<action> actions;

	Club(info inf, vector<action> actions) {
		this->inf = inf;
		this->actions = actions;
		tables.resize(inf.computers + 1);
	}

	int busy_tables() {
		int b_t = 0;
		for (int i = 0; i < tables.size(); i++) {
			if (tables[i] == 1) b_t++;
		}
		return b_t;
	}

	void remove_client(vector<client>& clients_vector, string client_name) {
		for (auto it = clients_vector.begin(); it != clients_vector.end();) {
			client cl = *it;
			if (cl.name == client_name) {
				it = clients_vector.erase(it);
				break;
			}
			++it;
		}
	}

	void set_to_computer(string& client_name, int comp, action& curr_action) {
		for (int i = 0; i < clients.size(); i++) {
			if (clients[i].name == client_name) {
				clients[i].computer = comp;
				work_place client_wp;
				client_wp.client = client_name;
				client_wp.table = comp;
				client_wp.time_start = curr_action.time;
				wp.push_back(client_wp);
			}
		}
	}

	void client_left_table(string& client_name, int time) {
		for (int i = 0; i < wp.size(); i++) {
			if (wp[i].client == client_name && wp[i].time_end == 0) {
				wp[i].time_end = time;
				return;
			}
		}
	}

	bool client_in_club(string& client_name) {
		auto c = find_client(client_name);
		return c != NULL;
	}

	client* find_client(string& client_name) {
		for (int i = 0; i < clients.size(); i++) {
			if (clients[i].name == client_name) {
				return &clients[i];
			}
		}
		return NULL;
	}

	void client_came(action& curr_action) {

		if (curr_action.time < inf.time_start) {
			cout << time_format(curr_action.time) << " 13 NotOpenYet" << endl;
			return;
		}
		if (client_in_club(curr_action.client_name)) {
			cout << time_format(curr_action.time) << " 13 YouShallNotPass" << endl;
			return;
		}
		clients.push_back(curr_action.client_name);
	}

	void client_sat_table(action& curr_action) {
		client* clt;

		if (client_in_club(curr_action.client_name)) {
			clt = find_client(curr_action.client_name);
		}
		else {
			cout << time_format(curr_action.time) << " 13 ClientUnknown" << endl;
			return;
		}
		if ((clt->computer == curr_action.computer) || (tables[curr_action.computer] == 1)) {
			cout << time_format(curr_action.time) << " 13 PlaceIsBusy" << endl;
			return;
		}
		if (clt->computer != 0) {
			tables[clt->computer] = 0;
			client_left_table(curr_action.client_name, curr_action.time);
			set_to_computer(curr_action.client_name, curr_action.computer, curr_action);
			tables[curr_action.computer] = 1;
			return;
		}
		set_to_computer(curr_action.client_name, curr_action.computer, curr_action);
		tables[curr_action.computer] = 1;
		remove_client(queue, curr_action.client_name);
	}

	void client_wait(action& curr_action) {
		queue.push_back(curr_action.client_name);

		if (busy_tables() < (tables.size() - 1)) {
			cout << time_format(curr_action.time) << " 13 ICanWaitNoLonger!" << endl;
			return;
		}
		if (queue.size() > (tables.size() - 1)) {
			cout << time_format(curr_action.time) << " 11 " << curr_action.client_name << endl;
			remove_client(queue, curr_action.client_name);
			remove_client(clients, curr_action.client_name);
			return;
		}
	}

	void client_left(action& curr_action) {
		client* clt;

		if (client_in_club(curr_action.client_name)) {
			clt = find_client(curr_action.client_name);
		}
		else {
			cout << time_format(curr_action.time) << " 13 ClientUnknown" << endl;
			return;
		}
		int comp = clt->computer;
		remove_client(clients, clt->name);
		tables[comp] = 0;
		client_left_table(curr_action.client_name, curr_action.time);

		if (queue.size() != 0) {
			set_to_computer(queue[0].name, comp, curr_action);
			tables[queue[0].computer] = 1; 
			cout << time_format(curr_action.time) << " 12 " << queue[0].name << " " << comp << endl;
			remove_client(queue, queue[0].name);
		}
	}

	void close_club() {
		sort(clients.begin(), clients.end(), compare);

		for (int i = 0; i < clients.size(); i++) {
			cout << time_format(inf.time_end) << " 11 " << clients[i].name << endl;
			tables[clients[i].computer] = 0;
			client_left_table(clients[i].name, inf.time_end);
		}

	}

	void count_revenue() {
		vector<int> wp_time(tables.size());
		int time = 0;
		int h = 0;
		int m = 0;

		for (int i = 0; i < wp.size(); i++) {
			time = wp[i].time_end - wp[i].time_start;
			h = time / 60;
			m = time % 60;
			tables[wp[i].table] += h * inf.price;

			if (m != 0) {
				tables[wp[i].table] += inf.price;
			}
			wp_time[wp[i].table] += time;
		}
		for (int i = 1; i < tables.size(); i++) {
			cout << i << " " << tables[i] << " " << time_format(wp_time[i]) << endl;;
		}
	}

	void club_work() {
		cout << time_format(inf.time_start) << endl;

		for (int i = 0; i < actions.size(); i++) {
			actions[i].print_action();

			if (actions[i].act == CLIENT_CAME) {
				client_came(actions[i]);
			}
			if (actions[i].act == CLIENT_SAT_TABLE) {
				client_sat_table(actions[i]);
			}
			if (actions[i].act == CLIENT_WAIT) {
				client_wait(actions[i]);
			}
			if (actions[i].act == CLIENT_LEFT) {
				client_left(actions[i]);
			}
		}
		close_club();
		cout << time_format(inf.time_end) << endl;
		count_revenue();
	}
};

#endif
