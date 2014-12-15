#include <iostream>
using namespace std;
struct telement {
	char prezime[14],ime[14],spol,datum_rodj[12];
	int ai,bi,ci,di;
	};
struct tred {
	telement element;
	tred *sljedeci;
	};
struct tzaglavlje {
	tred *celo,*zacelje;
	};
tzaglavlje zaglavlje;
tred *red,*brzi;
telement FrontQ(tred *red) {
	return zaglavlje.celo->sljedeci->element;
	}
void EnQueueQ(telement element,tred *red) {
	zaglavlje.zacelje->sljedeci=new tred;
	zaglavlje.zacelje=zaglavlje.zacelje->sljedeci;
	zaglavlje.zacelje->element=element;
	}
void DeQueueQ (tred *red) {
	tred *trenutni=zaglavlje.celo;
	zaglavlje.celo=zaglavlje.celo->sljedeci;
	delete trenutni;
	}
bool IsEmptyQ(tred *red) {
	if (zaglavlje.celo==zaglavlje.zacelje)
		return true;
	return false;
	}
void InitQ(tred *&red) {
	red=new tred;
	zaglavlje.celo=red;
	zaglavlje.zacelje=red;
	}
