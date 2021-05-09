#include "lsys.h"



lsys::lsys()
{
	constAlpha = "+-FFFF&^_ =";
	alpha = "F";
	tAlpha = alpha + constAlpha;
	fromEvo = new std::string;
	toEvo = new std::string;
	//*fromEvo = "a[F][G]";
	//*fromEvo = "+F[-F+FFA][+F-FA]";
	*fromEvo = "F";
	begin = &fromEvo->at(0);
	end = &fromEvo->at(fromEvo->length()-1 );
	std::vector <std::tuple<std::string, std::string, std::string>>  ruleSet;
	std::unordered_map<char, std::vector<std::tuple<std::string, std::string, std::string>	> > rules;
	

	
	/*addrule('A', "[F[-F+FFA][+F-FA]]");
	ruleSet.clear();*/
	/*addrule('+', "F");
	
	ruleSet.clear();
	addrule('F', "+F");*/
	
	//addrule('F', "FFF[+F]");
	//addrule('F', "FF[+F]");

	//addrule('F', "F[+FF]");
	//addrule('a', "aa", "F", "");
	
	/*addrule('F', "a[F][G]", "a", "");
	addrule('F', "F", "", "");
	ruleSet.clear();
	addrule('G', "F", "a", "");
	addrule('G', "G", "", "");
	ruleSet.clear();
	addrule('a', "a", "", "");*/
	

}

void lsys::setSeed(std::string seed)
{
	*fromEvo = seed;
}

std::string *  lsys::getWord()
{
	return this->fromEvo;
}

std::string lsys::randomStr(std::string selection)
{
	std::string select = "";
	int braket= (rand() % 3)*2;
	for (int i = 0; i < (rand() % 7)+8; i++)
	{

		select += selection[rand() % selection.length()];

	}
	int place = rand() % select.length();
	for (int i = 0; i < braket; i++)
	{
	
		select.insert(place, (i % 2 == 0) ? "[" : "]");
		
		if (place < select.length())
		{
			place += (rand() % 4)+1;
		}
		if (place > select.length())
		{
			place = select.length()-1;
		}
	}

	return select;
}

void lsys::generateRandomRules()
{
	int numRules = 1;
	//int rightConLen = 1;
	int leftConLen = 1;
	
	for (char letter : alpha)
	{
		for (int i = 0; i < (rand() % numRules) + 1; i++) {
			std::string leftC = "";
			std::string rightC = "";

			int len = (rand() % leftConLen);
			for (int j = 0; j < len + 1; j++)
			{
				leftC += tAlpha[rand()%tAlpha.length()];
			}
			for (int j = 0; j < len + 1; j++)
			{
				rightC += tAlpha[rand() % tAlpha.length()];
			}

			//ruleSet.push_back(make_tuple(leftC, randomStr(tAlpha), rightC));
		}
		ruleSet.push_back(make_tuple("", randomStr(tAlpha), ""));
		this->rules[letter] = ruleSet;
		ruleSet.clear();
	}
}

void lsys::addrule(char For, std::string rule)
{
	ruleSet.push_back(make_tuple("", rule, ""));

	this->rules[For] = ruleSet;
	ruleSet.clear();
}
void lsys::addrule(char For, std::string rule, std::string left, std::string right)
{
	ruleSet.push_back(make_tuple(left, rule, right));
	this->rules[For] = ruleSet;
	//ruleSet.clear();
}
// aa vs a context problem

bool lsys::rightContext(char *look, std::string *test)
{
	int bC = 0;
	if (test->length() != 0 && look != this->end)
	{
		char *j = &test->front();
		for (char *i = look + 1; i != (look + test->length()); i++)
		{
			if (i == this->end)
			{
				return false;
			}

			if (*i == ']')
			{
				bC++;
			}
			if (*i == '[')
			{
				bC--;
			}
			
			
			if (bC == 0)
			{
				if (*i != *j || i == this->end || j == &(test->back()))
				{
					return false;
				}
				j++;
			}
		}
	}
	else if (test->length() == 0) { return true; }
	else { return false; }
	return true;
}


bool lsys::leftContext(char *look, std::string *test)
{
	int bC = 0;
	if (test->length() != 0 && look != this->begin) {
		char *j = &test->back();
		for (char* i = look - 1; i != (look - test->length() - 1); i--) {
			
			if ((i + 1) == this->begin)
			{
				return false;
			}
			if (*i == ']')
			{
				bC++;
			}
			if (*i == '[')
			{
				bC--;
			}
			if (bC == 0)
			{
				if (*i != *j || (i + 1) == this->begin || (j) == &test->front() - 1)
				{
					return false;
				}
				j--;
			}
		}
	}
	else if (test->length() == 0) { return true; }
	else { return false; }
	return true;
}


void lsys::evolve()
{
	for (char* stringPlace = &fromEvo->at(0); *stringPlace != '\0'; stringPlace++)
	{
		if (this->rules[*stringPlace].size() == 0)
		{
			//this->toEvo.append( *stringPlace);
			*toEvo += *stringPlace;
		}
		for (int i = 0; i < this->rules[*stringPlace].size(); i++)
		{
			if (
				std::get<1>(rules[*stringPlace].at(i)) != ""
				&& leftContext(stringPlace, &std::get<0>(this->rules[*stringPlace].at(i)))
				&& rightContext(stringPlace, &std::get<2>(this->rules[*stringPlace].at(i)))
				)
			{
				*toEvo += std::get<1>(rules[*stringPlace].at(i));
				//toEvo->append(std::get<1>(rules[*stringPlace].at(i)));
				break;
			}
			else if (std::get<1>(rules[*stringPlace].at(i)) == "")
			{
				*toEvo += *stringPlace;
				break;
			}
			else if (i == rules[*stringPlace].size())
			{
				*toEvo += *stringPlace;
				break;
			}
		}
		//*toEvo += '\0';
	}
}

void lsys::iterate(int iterates)
{
	for (int i = 0; i < iterates; i++) {
		evolve();

		delete this->fromEvo;
		this->fromEvo =this-> toEvo;
		this->toEvo = new std::string;
		this->begin = &fromEvo->at(0);
		this->end = &fromEvo->at(fromEvo->length() - 1);
	}
	/*generateRandomRules();
	evolve();

	delete this->fromEvo;
	this->fromEvo = toEvo;
	this->toEvo = new std::string;
	this->begin = &fromEvo->at(0);
	this->end = &fromEvo->at(fromEvo->length() - 1);*/
}

void lsys::randomSeed()
{
	std::string temp;
	for (int i = 0; i < rand() % 7; i++)
	{
		temp += tAlpha;
	}
	*fromEvo = tAlpha;
}

void lsys::printRules()
{
	for (auto letter : rules)
	{
		
		std::cout << "Rules for : " << std::get<0>(letter)<<"\n";
		for (auto rule : std::get<1>(letter))
		{
			std::cout << std::get<0>(rule) << " <  " << std::get<0>(letter) << "  > " << std::get<2>(rule) << "      ->" << std::get<1>(rule)<<"\n";
		}

	}
}
void lsys::setAlpha(std::string a) {
	alpha = a;
}

//written like I meant to obfuscate it
void lsys::findGrowthUpperBound() {
	growthupperBound = 0;
	int prev = 0;
	for (auto i = this->rules.begin(); i != this->rules.end(); i++)
	{
		for (auto j = i->second.begin(); j != i->second.end(); j++)
		{
			for (auto k = std::get<1>(*j).begin(); k != std::get<1>(*j).end(); k++)
			{
				if (*k == 'F')
					prev++;
			}
		}
		if (prev > growthupperBound)
		{
			growthupperBound = prev;
			prev = 0;
		}
	}
}
int lsys::getUpperBound() { return growthupperBound; }
lsys::~lsys()
{

}


Lsys::Lsys()
{
}
