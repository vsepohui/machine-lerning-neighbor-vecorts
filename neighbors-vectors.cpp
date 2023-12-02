#include <iostream>
#include <map>
#include <vector>
#include <bits/stdc++.h> 

using namespace std; 




class Delta {
	public:
		int user;
		int delta;
		Delta (int u, int d) {
			this->user = u;
			this->delta = d;
		}
	
};

bool my_cmp (const Delta a, const Delta b) {
    return a.delta < b.delta;
}

int main () {

	std::map <int,std::map<int, int>> rates;
	std::map <int,std::map<int, int>> users_delta;

	
	// loading dataset
	int _user_id, _content_id, _rate;
	while (std::cin >> _user_id >> _content_id >> _rate) {
		rates[_user_id][_content_id] = _rate;
	}
	


	
	std::map <int, std::map<int, int>>::iterator user_1, user_2;
	std::map <int, int>::iterator content_id;
	
	for (user_1 = rates.begin(); user_1 != rates.end(); user_1++) {
		for (user_2 = rates.begin(); user_2 != rates.end(); user_2++) {
			if (user_1->first == user_2->first) {
				continue;
			}
			
			for (content_id = rates[user_1->first].begin(); content_id != rates[user_1->first].end(); content_id++) {
				if (rates[user_2->first][content_id->first]) {
					int r2 = rates[user_2->first][content_id->first];
					int r1 = rates[user_1->first][content_id->first];
					int delta = abs(r2 - r1);
					if (!users_delta[user_1->first][user_2->first]) {
						users_delta[user_1->first][user_2->first] = 0;
					}
					users_delta[user_1->first][user_2->first] += delta;
				}
			}
		}
	}
	

	// finding nearest neighbors
	std::map <int,std::vector<Delta>> neighbors;
	std::vector<Delta>::iterator ii;
	
	for (user_1 = users_delta.begin(); user_1 != users_delta.end(); user_1++) {
		for (user_2 = users_delta.begin(); user_2 != users_delta.end(); user_2++) {
			if (!users_delta[user_1->first][user_2->first]) {
				continue;
			}
			int a1 = (int)user_2->first;
			int a2  = users_delta[user_1->first][user_2->first];
			Delta *d = new Delta(a1, a2);
			
			neighbors[user_1->first].push_back(*d);
		}
		
		std::vector<Delta> v = neighbors[user_1->first];

		sort(v.begin(), v.end(), my_cmp);
		for (ii = v.begin(); ii != v.end(); ii++) {
			Delta d = *ii;
			cout << user_1->first << "\t" << d.user << "\t" << d.delta << "\n";
		}
	}
	
	

	

	
}


