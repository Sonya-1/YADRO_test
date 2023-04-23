#include "Club.h"

Club::Club() {}

Club::Club(info inf, vector<action> actions) {
	this->inf = inf;
	this->actions = actions;
	tables.resize(inf.computers + 1);
}

int Club::busy_tables() {
	int b_t = 0;
	for (int i = 0; i < tables.size(); i++) {
		if (tables[i] == 1) b_t++;
	}
	return b_t;
}

bool compare(client client1, client client2) {
	return (client1.name < client2.name);
}

void Club::remove_client(vector<client>& clients_vector, string client_name) {
	for (auto it = clients_vector.begin(); it != clients_vector.end();) {
		client cl = *it;
		if (cl.name == client_name) {
			it = clients_vector.erase(it);
			break;
		}
		++it;
	}
}

void Club::set_to_computer(string& client_name, int comp, action& curr_action) {
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

void Club::client_left_table(string& client_name, int time) {
	for (int i = 0; i < wp.size(); i++) {
		if (wp[i].client == client_name && wp[i].time_end == 0) {
			wp[i].time_end = time;
			return;
		}
	}
}

bool Club::client_in_club(string& client_name) {
	auto c = find_client(client_name);
	return c != NULL;
}

client* Club::find_client(string& client_name) {
	for (int i = 0; i < clients.size(); i++) {
		if (clients[i].name == client_name) {
			return &clients[i];
		}
	}
	return NULL;
}

void Club::client_came(action& curr_action) {

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

void Club::client_sat_table(action& curr_action) {
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

void Club::client_wait(action& curr_action) {
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

void Club::client_left(action& curr_action) {
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

void Club::close_club() {
	sort(clients.begin(), clients.end(), compare);

	for (int i = 0; i < clients.size(); i++) {
		cout << time_format(inf.time_end) << " 11 " << clients[i].name << endl;
		tables[clients[i].computer] = 0;
		client_left_table(clients[i].name, inf.time_end);
	}
}

void Club::count_revenue() {
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

void Club::club_work() {
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