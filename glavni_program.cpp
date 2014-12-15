#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iomanip>
#include "polje.h"
//#include "pokazivac.h"
using namespace std;
int vr_jed=0;
void timestamp () {
	int sat=vr_jed/3600;
	int min=(vr_jed%3600)/60;
	int sek=(vr_jed%3600)%60;
	cout<<"["<<sat/10<<sat%10<<":"<<min/10<<min%10<<":"<<sek/10<<sek%10<<"] ";
	}
void usluga (int i) {
	switch (i) {
		case 1: cout<<"posiljke";break;
		case 2: cout<<"racune";break;
		case 3: cout<<"lutriju";break;
		case 4: cout<<"Western Union";break;
		case 5: cout<<"Evotv";break;
		}
	}
void prioritet (int i) {
	switch (i) {
		case 1: cout<<"VIP";break;
		case 2:	cout<<"invalid";break;
		case 3: cout<<"trudnica";break;
		case 4: cout<<"umirovljenik";break;
		case 5: cout<<"obican";break;
		}
	}
struct tcetvorka {
	int ai,bi,ci,di;
	} *cetvorke=NULL;
telement osoba;
struct ttip {
	tcetvorka cetvorke;
	int broj;
	} *preostale_kombinacije=NULL;
void generiraj (int N) {
	for (int i=0;i<25;i++) {
		cetvorke[i].ai=10+rand()%491;
		cetvorke[i].bi=80+rand()%721;
		cetvorke[i].ci=1+i/5;
		cetvorke[i].di=1+i%5;
		}
	for (int i=25;i<N;i++) {
		cetvorke[i].ai=10+rand()%491;
		cetvorke[i].bi=80+rand()%721;
		cetvorke[i].ci=1+rand()%5;
		cetvorke[i].di=1+rand()%5;
		}
	}

int num_jarci=0;
telement *jarci;
int brojac=0;
telement prvi;
telement sljedeci;
telement *polje;

void ispis_reda () {
	osoba=FrontQ(red);
	if (memcmp(&prvi,&osoba,sizeof(telement))!=0 || brojac==0) {
		brojac++;
		DeQueueQ(red);
		EnQueueQ(osoba,red);
		cout<<setw(4)<<brojac<<". "<<setw(15)<<osoba.prezime<<setw(15)<<osoba.ime<<setw(4)<<osoba.spol<<setw(13)<<osoba.datum_rodj<<setw(15);
					switch(osoba.ci) {
						case 1: cout<<"VIP"<<setw(10);break;
						case 2:	cout<<"Invalid"<<setw(10);break;
						case 3: cout<<"Trudnica"<<setw(10);break;
						case 4: cout<<"Umirovljenik"<<setw(10);break;
						case 5: cout<<"Ostali"<<setw(10);
						}
					switch(osoba.di) {
						case 1: cout<<"Posiljke"<<endl;break;
						case 2: cout<<"Racuni"<<endl;break;
						case 3: cout<<"Lutrija"<<endl;break;
						case 4: cout<<"WUnion"<<endl;break;
						case 5: cout<<"Evotv"<<endl;
						}
		ispis_reda();
		}
	else
		return;
	}

bool trudnica_geht_raus (char izbor) {
	bool vrati=false;
	int N=0;
	while (IsEmptyQ(red)==false) {
		polje[N]=FrontQ(red);
		DeQueueQ(red);
		N++;
		}
	if (N!=0 && polje[N-1].ci==3 && polje[N-1].di==5) {
		N--;
		vrati=true;
		if (izbor=='O') {
			timestamp();
			osoba=polje[N];
			cout<<(osoba.spol=='M'?"Muskarac (":"Zena (");
			prioritet(osoba.ci);
			cout<<") "<<osoba.prezime<<" "<<osoba.ime<<" prijevremeno izlazi iz poste zbog 'prevelikog' broja ljudi koji cekaju oslobodjenje saltera za ";
			usluga(osoba.di);
			cout<<endl;
			}
		}
	if (vrati==true)
		if (N==0)
			cout<<"Nakon izlaska trudnice "<<polje[N].prezime<<" "<<polje[N].ime<<" koja je cekala zbog usluge Evotv nema nijedne osobe u redu.."<<endl;
		else
			cout<<"\nStanje glavnog reda nakon izlaska trudnice "<<polje[N].prezime<<" "<<polje[N].ime<<" koja je cekala zbog usluge Evotv: "<<endl;
	for (int i=0;i<N;i++) {
		EnQueueQ(polje[i],red);
		if (vrati==true) {
			osoba=polje[i];
			cout<<setw(4)<<i+1<<". "<<setw(15)<<osoba.prezime<<setw(15)<<osoba.ime<<setw(4)<<osoba.spol<<setw(13)<<osoba.datum_rodj<<setw(15);
			switch(osoba.ci) {
				case 1: cout<<"VIP"<<setw(10);break;
				case 2:	cout<<"Invalid"<<setw(10);break;
				case 3: cout<<"Trudnica"<<setw(10);break;
				case 4: cout<<"Umirovljenik"<<setw(10);break;
				case 5: cout<<"Ostali"<<setw(10);
				}
			switch(osoba.di) {
				case 1: cout<<"Posiljke"<<endl;break;
				case 2: cout<<"Racuni"<<endl;break;
				case 3: cout<<"Lutrija"<<endl;break;
				case 4: cout<<"WUnion"<<endl;break;
				case 5: cout<<"Evotv"<<endl;
				}
			}
		}
	return vrati;
	}

void sortiraj (char izbor) {
	int N=0;
	while (IsEmptyQ(red)==false) {
		polje[N]=FrontQ(red);
		DeQueueQ(red);
		N++;
		}
	bool kraj=false;
	for (int i=0;i<N-1 && !kraj;i++) {
		kraj=true;
		for (int j=N-1;j>i;j--)
			if (polje[j].ci<polje[j-1].ci) {
				if (izbor=='O') {
					timestamp();
					osoba=polje[j];
					telement osoba2=polje[j+1];
					cout<<(osoba.spol=='M'?"Muskarac (":"Zena (");
					prioritet(osoba.ci);
					cout<<") "<<osoba.prezime<<" "<<osoba.ime<<" je veceg prioriteta od  "<<(osoba2.spol=='M'?"muskarca (":"zene ( ");
					prioritet(osoba2.ci);
					cout<<") "<<osoba2.prezime<<" "<<osoba2.ime<<" pa ide na "<<(osoba.spol=='M'?"njegovo":"njezino")<<" mjesto"<<endl;
					}
				telement pomocna=polje[j];
				polje[j]=polje[j-1];
				polje[j-1]=pomocna;
				kraj=false;
				}
		}
	for (int i=0;i<N;i++)
		EnQueueQ(polje[i],red);
	}

telement salteri[5];
telement prazni;

void na_salter_preko_reda (char izbor) {
	int N=0;
	while (IsEmptyQ(red)==false) {
		polje[N]=FrontQ(red);
		DeQueueQ(red);
		N++;
		}
	for (int i=0;i<N;i++)
		if (memcmp(&salteri[polje[i].di-1],&prazni,sizeof(telement))==0) {
			salteri[polje[i].di-1]=polje[i];
			osoba=polje[i];
			timestamp();
			cout<<(osoba.spol=='M'?"Muskarac (":"Zena (");
			prioritet(osoba.ci);
			cout<<") "<<osoba.prezime<<" "<<osoba.ime<<" odlazi preko reda na slobodni salter za ";
			usluga(osoba.di);
			cout<<endl;
			}
		else
			EnQueueQ(polje[i],red);
	}

void dodaj_i_radi (int N) {
	char trudnice;
	do {
		cout<<"Da li zelite da trudnice izadju iz reda zbog 'prevelike' guzve? (D/N): ";
		cin.clear();
		cin.ignore();
		cin.get(trudnice);
		} while (trudnice!='D' && trudnice!='N');
	char simulacija;
	do {
		cout<<"Da li zelite realnu simulaciju ili obicnu? (R/O): ";
		cin.clear();
		cin.ignore();
		cin.get(simulacija);
		} while (simulacija!='R' && simulacija!='O');
	system("cls");
	memset(&prazni,0,sizeof(telement));
	memset(salteri,0,sizeof(salteri));
	int broj_preostalih_tokena=N*5;
	int broj_preostalih_ljudi=N*5;
	int dolazi_za=0;
	while (broj_preostalih_tokena>0) {
		if (dolazi_za==0 && broj_preostalih_ljudi>0) {
			if (vr_jed!=0) {
				if (simulacija=='O') {
					timestamp();
					cout<<(osoba.spol=='M'?"Muskarac (":"Zena (");
					prioritet(osoba.ci);
					cout<<") "<<osoba.prezime<<" "<<osoba.ime<<(osoba.spol=='M'?" rodjen ":" rodjena ")<<osoba.datum_rodj<<" ulazi u red cekajuci za ";
					usluga(osoba.di);
					cout<<endl;
					}
				EnQueueQ(sljedeci,red);
				sortiraj(simulacija);
				broj_preostalih_ljudi--;
				}

			if (broj_preostalih_ljudi>0) {
				int slucajni_broj;
				do {
					slucajni_broj=rand()%N;
					} while (preostale_kombinacije[slucajni_broj].broj==0);

				dolazi_za=preostale_kombinacije[slucajni_broj].cetvorke.ai;
				int i;
				int limit=3+rand()%11;
				for (i=0;i<limit;i++) {
					int prob=rand()%1000;
					if (prob<2)
						osoba.prezime[i]='F';
					else if (prob<17)
						osoba.prezime[i]='B';
					else if (prob<34)
						osoba.prezime[i]='G';
					else if (prob<59)
						osoba.prezime[i]='C';
					else if (prob<84)
						osoba.prezime[i]='Z';
					else if (prob<113)
						osoba.prezime[i]='P';
					else if (prob<146)
						osoba.prezime[i]='L';
					else if (prob<179)
						osoba.prezime[i]='M';
					else if (prob<214)
						osoba.prezime[i]='K';
					else if (prob<252)
						osoba.prezime[i]='V';
					else if (prob<291)
						osoba.prezime[i]='U';
					else if (prob<332)
						osoba.prezime[i]='D';
					else if (prob<381)
						osoba.prezime[i]='T';
					else if (prob<431)
						osoba.prezime[i]='J';
					else if (prob<482)
						osoba.prezime[i]='R';
					else if (prob<545)
						osoba.prezime[i]='N';
					else if (prob<608)
						osoba.prezime[i]='S';
					else if (prob<691)
						osoba.prezime[i]='E';
					else if (prob<783)
						osoba.prezime[i]='O';
					else if (prob<884)
						osoba.prezime[i]='I';
					else
						osoba.prezime[i]='A';
				
					if (i!=0)
						osoba.prezime[i]+=(char) 32;
					}
				osoba.prezime[i]='\0';
				limit=3+rand()%11;
				for (i=0;i<limit;i++) {
					int prob=rand()%1000;
					if (prob<2)
						osoba.ime[i]='F';
					else if (prob<17)
						osoba.ime[i]='B';
					else if (prob<34)
						osoba.ime[i]='G';
					else if (prob<59)
						osoba.ime[i]='C';
					else if (prob<84)
						osoba.ime[i]='Z';
					else if (prob<113)
						osoba.ime[i]='P';
					else if (prob<146)
						osoba.ime[i]='L';
					else if (prob<179)
						osoba.ime[i]='M';
					else if (prob<214)
						osoba.ime[i]='K';
					else if (prob<252)
						osoba.ime[i]='V';
					else if (prob<291)
						osoba.ime[i]='U';
					else if (prob<332)
						osoba.ime[i]='D';
					else if (prob<381)
						osoba.ime[i]='T';
					else if (prob<431)
						osoba.ime[i]='J';
					else if (prob<482)
						osoba.ime[i]='R';
					else if (prob<545)
						osoba.ime[i]='N';
					else if (prob<608)
						osoba.ime[i]='S';
					else if (prob<691)
						osoba.ime[i]='E';
					else if (prob<783)
						osoba.ime[i]='O';
					else if (prob<884)
						osoba.ime[i]='I';
					else
						osoba.ime[i]='A';
				
					if (i!=0)
						osoba.ime[i]+=(char) 32;
					}
				osoba.ime[i]='\0';
				if (rand()%2==0 && preostale_kombinacije[slucajni_broj].cetvorke.ci!=3)
					osoba.spol='M';
				else
					osoba.spol='Z';
				int broj;
				broj=1+rand()%12;
				osoba.datum_rodj[3]=broj/10;
				osoba.datum_rodj[4]=broj%10;
				osoba.datum_rodj[5]='.';
				osoba.datum_rodj[2]='.';
				osoba.datum_rodj[10]='.';
				osoba.datum_rodj[11]='\0';
				
				short izbor;
				if (preostale_kombinacije[slucajni_broj].cetvorke.ci==4) {
					bool stariji_il_mladji=rand()%10;
					if (stariji_il_mladji==true)
						izbor=0;
					else
						izbor=2;
					}
				else if (preostale_kombinacije[slucajni_broj].cetvorke.ci==3)
					izbor=2;
				else if (preostale_kombinacije[slucajni_broj].cetvorke.di==3)
					izbor=rand()%3;
				else {
					bool starija_neumirovljena=!(rand()%10);
					if (starija_neumirovljena==true)
						izbor=0;
					else
						izbor=1+rand()%3;
					}
				switch (izbor) {
					case 0:
						broj=1920+rand()%35;
						break;
					case 1:
					case 2:
						broj=1955+rand()%40;
						break;
					case 3:
						broj=1995+rand()%10;
					}
					
				int godina=broj;
				for (i=9;i>5;i--) {
					osoba.datum_rodj[i]=broj%10;
					broj/=10;
					}
				switch (osoba.datum_rodj[4]) {
					case 1:
						if (osoba.datum_rodj[3]==0)
							broj=1+rand()%31;
						else
							broj=1+rand()%30;
						break;
					case 2:
						if (osoba.datum_rodj[3]==0)
							if (godina%4==0)
								broj=1+rand()%29;
							else
								broj=1+rand()%28;
						else
							broj=1+rand()%31;
						break;
					case 3:
					case 5:
					case 7:
					case 8:
					case 0: broj=1+rand()%31;break;
					default: broj=1+rand()%30;
					}
				osoba.datum_rodj[0]=broj/10;
				osoba.datum_rodj[1]=broj%10;
	
				for (i=0;i<11;i++)
					if (osoba.datum_rodj[i]!='.')
						osoba.datum_rodj[i]+=48;
				
				osoba.ai=preostale_kombinacije[slucajni_broj].cetvorke.ai;
				osoba.bi=preostale_kombinacije[slucajni_broj].cetvorke.bi;
				osoba.ci=preostale_kombinacije[slucajni_broj].cetvorke.ci;
				osoba.di=preostale_kombinacije[slucajni_broj].cetvorke.di;
				
				char datum[][6] = {"0321", "0420", "0521", "0621", "0723", "0823", "0923", "1024", "1122", "1222", "0120", "0219"};
				bool iznimka;
				
				iznimka=true;
				char datum_osobe[]={osoba.datum_rodj[3],osoba.datum_rodj[4],osoba.datum_rodj[0],osoba.datum_rodj[1]};
				for (int i=0;i<12;i++) {
					if (strcmp(datum_osobe,datum[i])>=0 && strcmp(datum_osobe,datum[(i+1)%12])==-1) {
						iznimka=false;
						break;
						}
					}
				if (iznimka==true) {
					char god[4]={osoba.datum_rodj[6],osoba.datum_rodj[7],osoba.datum_rodj[8],osoba.datum_rodj[9]};
					if ((2014-atoi(god))<40)
						if (osoba.di==3)
							jarci[num_jarci++]=osoba;
					}
				sljedeci=osoba;
				preostale_kombinacije[slucajni_broj].broj--;
				}
			}

		if (simulacija=='R') {
			system("cls");
			if (broj_preostalih_ljudi==0)
				cout<<"Svih "<<N*5<<" osoba je uslo u postu..."<<endl;
			else
				cout<<"Sljedeca osoba stize za: "<<dolazi_za<<endl;
			cout<<"Salteri: "<<endl;
			cout<<"  1. Primopredaja posiljke: "<<setw(15)<<salteri[0].prezime<<setw(15)<<salteri[0].ime<<setw(4)<<salteri[0].spol<<setw(13)<<salteri[0].datum_rodj<<setw(4)<<salteri[0].bi<<endl;
			cout<<"  2. Placanje racuna:       "<<setw(15)<<salteri[1].prezime<<setw(15)<<salteri[1].ime<<setw(4)<<salteri[1].spol<<setw(13)<<salteri[1].datum_rodj<<setw(4)<<salteri[1].bi<<endl;
			cout<<"  3. Uplata lutrije:        "<<setw(15)<<salteri[2].prezime<<setw(15)<<salteri[2].ime<<setw(4)<<salteri[2].spol<<setw(13)<<salteri[2].datum_rodj<<setw(4)<<salteri[2].bi<<endl;
			cout<<"  4. Western Union:         "<<setw(15)<<salteri[3].prezime<<setw(15)<<salteri[3].ime<<setw(4)<<salteri[3].spol<<setw(13)<<salteri[3].datum_rodj<<setw(4)<<salteri[3].bi<<endl;
			cout<<"  5. Evotv:                 "<<setw(15)<<salteri[4].prezime<<setw(15)<<salteri[4].ime<<setw(4)<<salteri[4].spol<<setw(13)<<salteri[4].datum_rodj<<setw(4)<<salteri[4].bi<<endl;
			cout<<"\nRed ljudi: "<<endl;
			}
		
		if (trudnice=='D') {
			if (trudnica_geht_raus (simulacija)==true) {
				broj_preostalih_tokena--;
				system("pause");
				}
			}
			
		if (IsEmptyQ(red)==false) {
			brojac=0;
			prvi=FrontQ(red);

			if (simulacija=='R')
				ispis_reda();
	
			if (memcmp(&salteri[FrontQ(red).di-1],&prazni,sizeof(telement))==0) {
				osoba=FrontQ(red);
				if (simulacija=='O') {
					timestamp();
					cout<<(osoba.spol=='M'?"Muskarac (":"Zena (");
					prioritet(osoba.ci);
					cout<<") "<<osoba.prezime<<" "<<osoba.ime<<" odlazi iz reda na salter za ";
					usluga(osoba.di);
					cout<<endl;
					}
				memcpy(&salteri[FrontQ(red).di-1],&osoba,sizeof(telement));
				DeQueueQ(red);
				}
			
			na_salter_preko_reda (simulacija);
			}
					
		for (int i=0;i<5;i++)
			if (salteri[i].bi!=0) {
				salteri[i].bi--;
				if (salteri[i].bi==0) {
					if (simulacija=='O') {
						osoba=salteri[i];
						timestamp();
						cout<<(osoba.spol=='M'?"Muskarac (":"Zena (");
						prioritet(osoba.ci);
						cout<<") "<<osoba.prezime<<" "<<osoba.ime<<" odlazi van iz poste, te oslobadja salter za ";
						usluga(osoba.di);
						cout<<endl;
						}
					broj_preostalih_tokena--;
					}
				}
			else {
				memset(&salteri[i],0,sizeof(telement));
				}
		dolazi_za--;
		vr_jed++;
		}
		
	if (num_jarci==0)
		cout<<"\nU postu nije usla niti jedna osoba horoskopskog znaka 'Jarac' da je imala manje od 40 godine i izvrsila uplatu lutrije.."<<endl;
	else {
		cout<<"\nOsobe horoskopskog znaka 'Jarac' koje su bile u posti, imaju manje od 40 godina, te su izvrile uplatu lutrije:"<<endl;
		for (int i=0;i<num_jarci;i++) {
			osoba=jarci[i];
			cout<<setw(15)<<osoba.prezime<<setw(15)<<osoba.ime<<setw(4)<<osoba.spol<<setw(13)<<osoba.datum_rodj<<setw(10);
			switch(osoba.di) {
				case 1: cout<<"Posiljke"<<endl;break;
				case 2: cout<<"Racuni"<<endl;break;
				case 3: cout<<"Lutrija"<<endl;break;
				case 4: cout<<"WUnion"<<endl;break;
				case 5: cout<<"Evotv"<<endl;
				}
			}
		}
	}

int main () {
srand(time(0));
rand();
InitQ(red);
int N;
do {
	cout<<"Unesite koliko cetvorki zelite izgenerirati? (minimalno 25): ";
	cin>>N;
	} while (N<25);
cetvorke=new tcetvorka [N];
generiraj (N);
polje=new telement [N*5];
jarci=new telement [N*5];
preostale_kombinacije=new ttip[N];
for (int i=0;i<N;i++) {
	preostale_kombinacije[i].broj=5;
	preostale_kombinacije[i].cetvorke=cetvorke[i];
	}
delete [] cetvorke;
dodaj_i_radi(N);
system("pause");
delete [] polje;
delete [] jarci;
delete [] preostale_kombinacije;
return 0;
}
