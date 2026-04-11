#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int N = 6;

void print_vector(vector<int> vec) {
    cout << "{";
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i != vec.size() - 1) {
            cout << ", ";
        }
    }
    cout << "}";
}

// version 1
bool solve_backtracking(int idx, vector<int> numbers, vector<int>& indexes, int total_sum) {
    if (total_sum == 0) {
        return true;
    }
    for (int index=idx; index<numbers.size(); index++) {
        int number = numbers[index];
        if (number > total_sum) {
            continue;
        }
        indexes.push_back(index);
        if (solve_backtracking(index+1, numbers, indexes, total_sum - number)) {
            return true;
        }
        indexes.pop_back();
    }
    return false;
}

// version 2
bool solve_backtracking_decision(int idx, vector<int> numbers, vector<int>& indexes, int total_sum) {
    if (total_sum == 0) {
        return true;
    }
    int number = numbers[idx];
    if (number <= total_sum) {
        indexes.push_back(idx);
        if (solve_backtracking(idx+1, numbers, indexes, total_sum - number)) {
            return true;
        }
        indexes.pop_back();

        if (solve_backtracking(idx+1, numbers, indexes, total_sum)) {
            return true;
        }
    }
    return false;
}


void solve(vector<int> numbers) {
    int sum = 0;
    for (auto number : numbers) {
        sum += number;
    }
    if (sum % 2 == 0) {
        vector<int> selected_indexes;
        solve_backtracking_decision(0, numbers, selected_indexes, sum / 2);
        vector<int> s1, s2 = numbers;
        for (auto index : selected_indexes) {
            s1.push_back(numbers[index]);
        }
        for (int i = selected_indexes.size() - 1; i >= 0 ; i--) {
            s2.erase(s2.begin() + selected_indexes[i]);
        }
        print_vector(s1);
        cout << " ";
        print_vector(s2);
    } else {
        cout << "It is not possible to find two subsets with the same sum of values.";
    }
}

int main() {
    vector<int> numbers = {3, 1, 4, 2, 5, 1};
    sort(numbers.begin(), numbers.end(), greater<int>());
    solve(numbers);
    return 0;
}