#include "voyager.h"

void voyager::input(const string& filename) {
    std::ifstream inf(filename);
    if (!inf)
        throw "invalid fileName";

    std::string str;
    std::getline(inf, str);
    size = atoi(str.c_str());
    if (size < 0)
        throw "invalid size";

    while (std::getline(inf, str)) {
        stringstream buf(str);
        vector<int> tmp;

        while (buf.rdbuf()->in_avail() != 0) {
            int len;
            buf >> len;
            tmp.push_back(len);
        }

        matrix.push_back(tmp);
        tmp.clear();
    }
    set_ones(matrix, size);
    output_matrix = matrix;

    return;

}



void voyager::without_row_col(int row, int col) {
    
    for (auto i = 0; i < size + 1; i++) {
        for (auto j = 0; j < size + 1; j++) {  
            if (matrix[0][j] == col && i == 0) { 
                col = j;
                break;
            }
        }
    }

    for (int i = 0; i < size + 1; i++) {
        int row_size = matrix[i].size();
        for (auto j = matrix[i].begin(); j != matrix[i].end(); j++) {
            if (j == matrix[i].begin()+col) {
                matrix[i].erase(matrix[i].begin() + col);
                break;
            }
        }
    }
    for (auto i =0; i < size+1; i++) {
        if (matrix[i][0] == row) {
            matrix.erase(matrix.begin() + i);
            break;
        }
    }
    size--;
    return;
}
void voyager::diff_way_org(int del_row, int del_col, int br_change)  {
    diff_way = matrix;
    diff_way[0][0] = br_change;
    diff_way_bracket = lower_bracket;
    for (auto i = 1; i < size + 1; i++) {
        for (auto j = 1; j < size + 1; j++) {
            if (diff_way[i][0] == del_row && diff_way[0][j] == del_col) {
                diff_way[i][j] = -1;
                break;
            }
        }
    }
}
void voyager::execute_town(int del_col, int del_row){
    for (auto i = 1; i < size + 1; i++) {
        for (auto j = 1; j < size + 1; j++) {
            if (matrix[i][0] == del_col && matrix[0][j] == del_row) {
                matrix[i][j] = -1;
                break;
            }
        }
    }
}


void voyager::zero_finding(int min_t) {
    int max_sum = -1;
    int min_row = 10000;
    int min_col = 10000;
    int del_col;
    int del_row;
    int flag = 1;
    

    while (flag!=0) {
        for (auto i = 1; i < size + 1; i++) {
            for (auto j = 1; j < size + 1; j++) {
                if (matrix[i][j] == 0) {
                    for (auto z = 1; z < size + 1; z++)
                        if ((matrix[z][j] >= 0) && (z != i) && (matrix[z][j] < min_row)) min_row = matrix[z][j];
                    for (auto e = 1; e < size + 1; e++)
                        if ((matrix[i][e] >= 0) && (e != j) && (matrix[i][e] < min_col)) min_col = matrix[i][e];
                    if (min_col + min_row > max_sum) {
                        max_sum = min_col + min_row;
                        del_col = matrix[0][j];
                        del_row = matrix[i][0];
                    }
                }
                min_row = 10000;
                min_col = 10000;
            }

        }
        if (lower_bracket == min_t) { 
            flag = 2;
            if (!visit) {
                diff_way_org(del_row, del_col, lower_bracket + max_sum);
                visit = 1;
            }
        }

        if (lower_bracket + min_t > lower_bracket + max_sum && flag==1) {           
            lower_bracket += max_sum;
            flag ++;       
            big_values.push_back(lower_bracket + min_t);
            max_sum = -1;
            execute_town(del_row, del_col);
           

        }
        else {
            execute_town(del_col, del_row);
            big_values.push_back(lower_bracket + max_sum);
            if (flag != 2) { 
                lower_bracket += min_t; 
               
            }
            break;
        }
        del_col = 0;
        del_row = 0;
    }
    way.push_back(make_pair(del_row, del_col));
    without_row_col(del_row, del_col);
    
    
    return;
}

void voyager::set_ones(vector <vector<int>>& a, int size){
    for (int i = 0; i < size + 1; i++) {
        for (int j = 0; j < size + 1; j++)
            if (i == j) a[i][j] = -1;
    }
    return;
}

int row_min(vector<int>& row) {
    int min = 10000;
    for (int i = 1; i < row.size(); i++) {
        if (row[i] >= 0 && row[i] < min) min = row[i];
    }
    return min;
}

int min_in_col(vector <vector<int>>& matrix, int size){
    int min_col = 10000;
    int row_col_sum=0;
        for (int i = 1; i < size + 1; i++) {
             for (int j = 1; j < size + 1; j++)
        if (matrix[j][i] != -1 && matrix[j][i] < min_col)min_col = matrix[j][i];
             for (int j = 1; j < size + 1; j++) {
        if (matrix[j][i] != -1)matrix[j][i] -= min_col;
             }

            row_col_sum += min_col;
            min_col = 10000;
        }
      return  row_col_sum;
}
int min_in_row(vector <vector<int>>& matrix, int size) {
    int row_sum = 0;
    int min_i = 0;
        for (int i = 1; i < size + 1; i++) {
            min_i = row_min(matrix[i]);
            for (auto j = matrix[i].begin() + 1; j < matrix[i].end(); j++) {
            if (*j != -1) *j -= min_i;
        }
        row_sum += min_i;
    }
        return row_sum;
}
void voyager::bowder_method() {

    while(size!=1){
        int row_col_sum = 0;
        row_col_sum += min_in_row(matrix, size);
        row_col_sum += min_in_col(matrix, size);

        if(lower_bracket==0)
        lower_bracket = row_col_sum;
        if (lower_bracket == diff_way_bracket && !visit)
            row_col_sum = 0;
        zero_finding(row_col_sum);
        
    }

    way.push_back(make_pair(matrix[size][0], matrix[0][size]));
    min_way = lower_bracket;
    min_route = way;
    way.clear();
    for (auto  i : big_values) {
        if (i < min_way) {
            matrix = diff_way;
            lower_bracket = diff_way_bracket;
            size = diff_way.size() - 1;
            visit = 0;
            bowder_method();
        }
    }
 
    return;
}

void voyager::greed(){
    set_ones(matrix, size);
    
    output_matrix = matrix;
    int del_col=0;
    int del_row=0;
    int back_i;
    int back_j;
    int del_i;
    while (size != 1) {
        int min = 10000;
        if (del_row == 0) {
            for (int i = 1; i < size + 1; i++) {
                for (int j = 1; j < size + 1; j++) {
                    if (matrix[i][j] < min && matrix[i][j] != -1) {
                        min = matrix[i][j];
                        del_row = matrix[i][0];
                        del_col = matrix[0][j];
                    }
                }
            }
        }
        else {
            del_row = del_col;
            for (int i = 1; i < size + 1; i++)
                if (matrix[i][0] == del_row)del_i = i;

            for (int j = 1; j < size + 1; j++) {
                if (matrix[del_i][j] != -1 && matrix[del_i][j] < min) {
                    del_col = matrix[0][j];
                    min = matrix[del_i][j];
                }
            }
        }
        way.push_back(make_pair(del_row, del_col));
        for (auto i = 1; i < size + 1; i++) {
            for (auto j = 1; j < size + 1; j++) {
                if (matrix[i][0] == del_col && matrix[0][j] == del_row) {

                    matrix[i][j] = -1;
                    break;
                }
            }
        }
        without_row_col(del_row, del_col);
    }
    way.push_back(make_pair(matrix[size][0], matrix[0][size]));

}


void voyager::write_file(const char* fname){

    ofstream out(fname);
    if (!out)
        throw "invalid fileName";
    
    bool flag;
    out << "digraph {\n";
    for (int i = 1; i <output_matrix.size(); i++) {
        for (int j = 1; j < output_matrix[i].size(); j++) {
            if (i != j) {
                bool flag = 1;
                for( pair<int,int> ways : min_route){
                    if (ways.first == i && ways.second == output_matrix[0][j]) {
                        out << i << "->" << output_matrix[0][j] << "[label=" << output_matrix[i][j] << ' ' << "color=Red" << "];" << "\n";
                        flag = 0;
                    }
                }
                if(flag)
                out << i << "->" << output_matrix[0][j] << "[label=" << output_matrix[i][j] << ' ' << "color=green" << "];" << "\n";
            }
        }
    }
    out << "}\n";
    out.close();
}

voyager& voyager::operator = (const voyager& a) {
    for (int i = 0; i < size + 1; i++) {
        for (int j = 0; j < size + 1; j++) {
            matrix[i][j]= a.matrix[i][j];
        }
    }
    size = a.size;
    return *this;
}
