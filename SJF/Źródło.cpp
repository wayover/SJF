#include <iostream>
#include <vector>

struct pkt
{
	int x;
	int y;
	double kat = 0;
};

class sjf
{
private:
	std::vector<pkt>duze;
	std::vector<pkt>male;
	std::vector<pkt>obwod;
	int iled;
	int ilem;
	pkt max;

public:
	void dodajd(int x, int y);
	void dodajm(int x, int y);
	void setiled(int ile);
	void setilem(int ile);
	void setmax(int maxx, int maxy);
	void wypiszskrajny();
	void obliczkat();
	void sort();


	void otoczka();
	int strona(int a);


	void wypiszotoczka();
	void wypiszd();
	void wypiszm();
	void wypiszdsort();
};

void sjf::dodajd(int x, int y)
{
	pkt p;
	p.x = x;
	p.y = y;
	duze.push_back(p);
}

void sjf::dodajm(int x, int y)
{
	pkt p;
	p.x = x;
	p.y = y;
	male.push_back(p);
}

void sjf::setiled(int ile)
{
	iled = ile;
}


void sjf::setilem(int ile)
{
	ilem = ile;
}

void sjf::setmax(int maxx, int maxy)
{
	max.x = maxx;
	max.y = maxy;
}

void sjf::sort()
{
	for (int i = 0; i < iled; i++)
		for (int j = 1; j < iled - i; j++) //pêtla wewnêtrzna
			if (duze[j - 1].kat > duze[j].kat)
				//zamiana miejscami
				std::swap(duze[j - 1], duze[j]);
}

int sjf::strona(int a)
{
	int siz=obwod.size();
	pkt p1 = obwod[siz - 2];
	pkt p2  = obwod[siz - 1];
	pkt p3 = duze[a];
	int rt = p1.x*p2.y + p2.x*p3.y + p3.x*p1.y - p3.x*p2.y - p1.x*p3.y - p2.x*p1.y;
	return rt;
}

void sjf::otoczka()
{
	obwod.push_back(duze[0]);
	obwod.push_back(duze[1]);
	obwod.push_back(duze[2]);

	int str;
	for (int i = 3; i < iled; i++)
	{
		str= strona(i);
		if (str < 0)
		{
			obwod.pop_back();
			
			obwod.push_back(duze[i]);
		}
		if (str >= 0)
		{
			obwod.push_back(duze[i]);
		}
		//wypiszotoczka();
	}
}

void sjf::obliczkat()
{
	double tg;
	for (int i = 0; i < iled; i++)
	{
		if (max.x == duze[i].x &&max.y == duze[i].y)
		{
			duze[i].kat = -50;
		}
		else if (max.x > duze[i].x)
		{
			if (max.y != duze[i].y)
			{
				tg =(double) (duze[i].x-max.x) / (double)(max.y-duze[i].y);
				tg = tg + 20;
				duze[i].kat = tg;
			}
			else
			{
				duze[i].kat = 40;
			}
		}
		else if (max.x < duze[i].x)
		{
			if (max.y != duze[i].y)
			{
				tg = (double)( duze[i].y- max.y ) / (double)( duze[i].x-max.x);
				
				duze[i].kat = tg;
			}
			else
			{
				duze[i].kat = -1;
			}
		}
		else
		{
			tg = 19;
			duze[i].kat = tg;
		}
	}
}




void sjf::wypiszskrajny()
{
	std::cout << "skrajny: " << max.x << " " << max.y << std::endl;
}

void sjf::wypiszd()
{
	for (int i = 0; i < iled; i++)
	{
		std::cout << duze[i].x << "  " << duze[i].y << std::endl;
	}
	std::cout << std::endl << std::endl;
}


void sjf::wypiszm()
{

	for (int i = 0; i < ilem; i++)
	{
		std::cout << male[i].x << "  " << male[i].y << std::endl;
	}
	std::cout << std::endl << std::endl;
}



void sjf::wypiszdsort()
{
	for (int i = 0; i < iled; i++)
	{
		std::cout << duze[i].x << "  " << duze[i].y <<"  "<<duze[i].kat<< std::endl;
	}
	std::cout << std::endl << std::endl;
}


void sjf::wypiszotoczka()
{
	int siz = obwod.size();
	std::cout << std::endl <<"otoczka: "<< std::endl;
	for (int i = 0; i < siz; i++)
	{
		std::cout << obwod[i].x << "  " << obwod[i].y << std::endl;
	}
	std::cout << std::endl << std::endl;
}






int main()
{
	sjf s;

	int iled;
	int ilem;
	int x;
	int y;
	int maxx = -1;
	int maxy = -1;
	int temp = -1;
	std::cin >> iled;
	s.setiled(iled);
	for (int i = 0; i < iled; i++)
	{
		std::cin >> x;
		std::cin >> y;
		if (temp == -1)
		{
			s.setmax(x, y);
			maxx = x;
			maxy = y;
			temp = 0;
		}
		else if (y < maxy)
		{
			s.setmax(x, y);
			maxx = x;
			maxy = y;
		}
		else if (y == maxy)
		{
			if (x < maxx)
			{
				s.setmax(x, y);
				maxx = x;
				maxy = y;
			}
		}

		s.dodajd(x, y);
	}

	std::cin >> ilem;
	s.setilem(ilem);
	for (int i = 0; i < ilem; i++)
	{
		std::cin >> x;
		std::cin >> y;
		s.dodajm(x, y);
	}

	s.wypiszd();
	s.wypiszm();
	
	s.obliczkat();
	s.sort();
	s.wypiszdsort();
	s.wypiszskrajny();

	s.otoczka();
	s.wypiszotoczka();
	system("pause");

	return 0;
}