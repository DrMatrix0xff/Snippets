#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Result {
    int count;
    int position;
    Result () : count(0), position(0) { }
};

Result find_longest_sequence(const vector<int> &aa) {
    Result r;
    int len = static_cast<int>(aa.size());
    int l;
    for (int i = 0; i < len; i++) {
        l = 1;
        for (int j = i; j >= 1 && aa[j] > aa[j - 1]; j--) {
            l += 1;
        }
        if (l > r.count) {
            r.count = l;
            r.position = i;
        }
    }
    return r;
}

int main(int argc, char *argv[]) {
    int const N = 200;
    vector<int> array;
    int randy;
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        randy = 1 + (rand() & 0x1ff);
        array.push_back(randy);
    }
    
    Result res;
    res = find_longest_sequence(array);
    
    cout << "count: " << res.count << ", end position: " << res.position
    << endl;

    for (int i = (res.position - res.count + 1) == 0 ? 0 : (res.position - res.count); i <= (res.position == (N - 1) ? res.position : res.position + 1); i++) {
        cout << array[i] << " ";
    }
    cout << endl;
    
    return 0;
}
