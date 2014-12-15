#include <iostream>
using namespace std;
struct telement {
	char prezime[14],ime[14],spol,datum_rodj[12];
	int ai,bi,ci,di;
	};
struct tred {
	telement element[10000];
	int celo,zacelje;
	};
tred red,brzi;
int AddOne (int n) {
	return (n+1)%10000;
	}
telement FrontQ(tred& red) {
	return red.element[red.celo];
	}
void EnQueueQ (telement& element,tred& red) {
	red.zacelje=AddOne(red.zacelje);
	red.element[red.zacelje]=element;
	}
void DeQueueQ (tred& red) {
	red.celo=AddOne(red.celo);
	}
bool IsEmptyQ (tred &red) {
	if (AddOne(red.zacelje)==red.celo)
		return true;
	return false;
	}
void InitQ (tred &red) {
	red.celo=0;
	red.zacelje=9999;
	}
