#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;

static int hexdigit(char ch) {
	if ('0' <= ch && ch <= '9')
		return ch - '0';
	else if ('a' <= ch && ch <= 'f')
		return ch - 'a' + 10;
	else if ('A' <= ch && ch <= 'F')
		return ch - 'A' + 10;
	else
		return -1;
}

string HexToDecimal(string const &hex) {
	int h, l, tmp;
	char c;
	string ss = "";
	for (unsigned int i = 0; i < hex.length(); i++) {
		c = hex[i];
		h = hexdigit(c);
		if (h < 0) {
			cerr << "invalid hex character: `" << h << "'" << endl;
			exit(-1);
		}
		l = ss.length();
		for (int j = 0; j < l; j++) {
			tmp = h + 16 * (ss[j] - '0');
			h = tmp / 10;
			ss[j] = (tmp - 10 * h) + '0'; 
		}
		while (h != 0) {
			tmp = h / 10;
			ss += ((h - 10 * tmp) + '0');
			h = tmp;
		}
	}
	reverse(ss.begin(), ss.end());
	return ss;
}

int main(int argc, char *argv[]) {
	
	string hexnum(128, 'f');
	string decnum;
	decnum = HexToDecimal(hexnum);
	
	cout << "Decimal Form of 0x" << hexnum << " is " << decnum << endl;
	return 0;
}
