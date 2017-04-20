#include "utilities.hpp"
#include "Vector2.h"

using namespace std;

utilities::utilities()
{}

utilities::~utilities()
{}

vector<ship> utilities::explore(char *dir_name)
{
	vector<Vector2> copia;
	int liCount = 0;
	float l, m;
	string coma;
	dir = opendir(dir_name);
	if (!dir)
	{
		cout << "Directory was not found" << endl;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			string path = string(dir_name) + "/" + string(entry->d_name);
			file.open(path.c_str());
			if (file.good())
			{
				while (!file.eof())
				{
					vector<Vector2> Elementos;
					getline(file, readString);
					stringstream(readString) >> l >> coma >> m;//nuevo
					Elementos.push_back(Vector2 (l,m));//nuevo
					copia.push_back(Vector2(l,m)); //nuevo
				}
				//cout << "Para el model: " << entry->d_name << " se ha leido " << copia.size() << endl; //nuevo
				Ship.push_back(copia);
				copia.clear(); //nuevo
				//cout << "" << endl;
			}
			file.close();
			stat(path.c_str(), &info); //
			if (S_ISDIR(info.st_mode))
			{
				explore((char *)path.c_str());
			}
		}
	}
	return Ship;
	closedir(dir);
}