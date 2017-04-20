#include "Load.h"

vector<ship> Load::load()
{
	vector<ship> copy;
	utilities file;
	copy = file.explore((char *)"Models");
	return copy;
}