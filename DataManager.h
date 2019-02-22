#pragma once

#include <string>
#include <vector>

using namespace std;

struct People_DB
{
	string name;
	string IP;
	string Birthday;
	string Student_N;
	string Phone_N;
	string Fine;
	string Password;

};

struct CalenderNotice
{
	string Date;
	string Who;
	string Contents_Type;
	string Public_Type;
	string Main_Contents;

};


class DataManager
{

private:

	DataManager(){};
	static bool instanceflag;
	static DataManager* instance;

	 

public:
	People_DB RecvPeople;
	CalenderNotice RecvContents;
	static DataManager *GetInstance();
	virtual ~DataManager() {
		instanceflag = false;
	}
	vector<People_DB>people_v;
	vector<CalenderNotice>calendernotice_v;
};

