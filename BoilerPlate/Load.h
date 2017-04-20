#pragma once

#ifndef _LOAD_
#define _LOAD_

#include "ship.h"
#include <vector>
#include "dirent.h"
#include <string>
#include <fstream>
#include <sstream>
#include "Vector2.h"
#include "utilities.hpp"

using namespace std;


class Load
{
public:
	vector<ship> load();
};

#endif // !_LOAD_
