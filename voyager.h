#ifndef func
#define func
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

class voyager
{
private:
	vector <vector<int>> matrix;
	vector <vector<int>> output_matrix;
	vector <pair<int,int>> way;
	vector <pair<int,int>> min_route;
	vector <vector<int>> diff_way;
	vector <int> big_values;
	size_t min_way = 0;
	size_t lower_bracket =0;
	size_t diff_way_bracket=1;
	int size = 0;
	bool visit=0;

public:
	void input(const string& filename);
	void bowder_method();
	void greed();
	void set_ones(vector <vector<int>>& a, int size);
	void zero_finding(int min_t);
	void without_row_col(int col, int row);
	void write_file(const char* fname);
	void diff_way_org(int del_row, int del_col, int br_change);
	void execute_town(int del_col, int del_row);
	voyager& operator = (const voyager& a);
	
	
	voyager() {
		
	
	};
	~voyager(){}


};


#endif