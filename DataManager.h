#pragma once

#include <string>
#include <vector>

using namespace std;
struct MyInfo
{
	string Name;
	string IP;
	string Birthday;
	string Student_N;
	string Phone_N;
	string Fine;
	string Password;

};

struct People_DB
{
	string Name;
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
	MyInfo myinfo;
	People_DB RecvPeople;
	CalenderNotice RecvContents;
	bool FindMyInfo();
	string GetIpAddress();
	static DataManager *GetInstance();
	virtual ~DataManager() {
		instanceflag = false;
	}
	vector<People_DB>people_v;
	vector<CalenderNotice>calendernotice_v;
};

