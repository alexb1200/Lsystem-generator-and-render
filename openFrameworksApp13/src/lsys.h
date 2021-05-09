#pragma once
#include <string>
#include  <unordered_map>
#include <vector>
#include <tuple>
#include <iostream>
class lsys
{
	std::string * fromEvo;
	std::string * toEvo;
	std::unordered_map<char, std::vector<std::tuple<std::string, std::string, std::string>	> > rules;
	char * begin;
	char * end;

	std::string alpha;
	std::string constAlpha;
	std::string tAlpha;
	std::vector <std::tuple<std::string, std::string, std::string>>  ruleSet;
	
	int growthupperBound;

public:

	lsys();
	void setSeed(std::string seed);
	lsys(std::string set);
	void evolve();
	void iterate(int iterates);
	bool leftContext(char * const look, std::string * test);
	bool rightContext(char * const look, std::string * test);

	std::string randomStr(std::string selection);
	void setAlpha(std::string a);
	void findGrowthUpperBound();
	int getUpperBound();
	void generateRandomRules();

	void addrule(char For, std::string rule);
	void addrule(char For, std::string rule, std::string left, std::string right);
	std::string *  lsys::getWord();
	void addrule(std::string left, std::string focus, std::string right);
	void randomSeed();
	void printRules();
	~lsys();
};

class Lsys
{
public:
	Lsys();
	~Lsys();
};

