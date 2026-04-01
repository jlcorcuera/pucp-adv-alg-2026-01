#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool is_valid(int weight, int k, vector<int> order) {
    if (order.empty()) {
        return true;
    }
    for (int meat: order) {
        if (abs(meat - weight) <= k) {
            return true;
        }
    }
    return false;
}

bool build_order(int idx, int P, vector<int> t, int k, vector<int>& order, vector<int>& indexes) {
    if (P == 0) {
        return true;
    }
    for (int index = idx; index < t.size(); index++) {
        int weight = t[index];
        if (weight > P) {
            continue;
        }
        if (is_valid(weight, k, order)) {
            order.push_back(weight);
            indexes.push_back(index);
            if (build_order(index + 1, P - weight, t, k, order, indexes)) {
                return true;
            }
            order.pop_back();
            indexes.pop_back();
        }
    }
    return false;
}


int main() {
    int P = 15;
    vector<int> t = {2, 8, 9, 6, 7, 6};
    int k = 4;

    vector<vector<int>> orders;

    while (true) {
        vector<int> order;
        vector<int> indexes;
        if (build_order(0, P, t, k, order, indexes)) {
            orders.push_back(order);
            for (int index = indexes.size() - 1; index >= 0; index--) {
                t.erase(t.begin() + indexes[index]);
            }
        } else {
            break;
        }
    }
    cout << orders.size() << endl;
    for (vector order: orders) {
        cout << "Orden: " << endl;
        for (int i = 0; i < order.size(); i++) {
            cout << order[i] << " ";
        }
        cout << endl;
    }
    return 0;
}