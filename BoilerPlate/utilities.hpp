#pragma once
#ifndef _UTILITIES_
#define _UTILITIES_
#include <string>
#include "dirent.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "Vector2.h"
#include "ship.h"

using namespace std;

class utilities
{
public: 
	utilities();
	~utilities();
	vector<ship> explore(char *dir_name);

private: 
		 DIR* dir;
		 struct dirent *entry;
		 struct stat info;
		 string readString;
		 fstream file;
		 vector<ship> Ship;
		 
};

#endif // !_UTILITIES_
