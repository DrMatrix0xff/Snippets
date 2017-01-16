/*
 * Module name: CommonSubstring.cpp
 * Create on Mon, Jan 16 2017
 *
 */


#include <iostream>
#include <string>

using namespace std;

struct Result {
    int count;
    int xi;
    int yi;

    Result () : count(0) {}
};

Result find_common_substring(const string &s1, const string &s2) {
    Result res;
    int count;

    for (int i = 0; i < static_cast<int>(s1.length()); i++) {
        for (int j = 0; j < static_cast<int>(s2.length()); j++) {
            count = 0;
            for (int k = i, l = j; (k >= 0) && (l >= 0) && (s1[k] == s2[l]); --k, --l) {
                count += 1;
            }
            if (count > res.count) {
                res.count = count;
                res.xi = i;
                res.yi = j;
            }
        }
    }
    return res;
}

int main(int argc, char *argv[]) {
    string ss1("abcdefg");
    string ss2("hijabcdcklmn");

    Result r;
    r = find_common_substring(ss1, ss2);

    cout << "count: " << r.count << endl;
    if (r.count > 0)
        cout << "common substring: " << ss1.substr(r.xi - r.count + 1, r.count) << endl;
    else
        cout << "no common substring" << endl;

    return 0;
}
