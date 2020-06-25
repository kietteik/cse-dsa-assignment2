#include "processData.h"

enum CodeValue
{
	rejectZero,
	sdCode,
	cdCode,
	slCode,
	insCode,
	delCode,
	updCode,
	obCode,
	cbCode,
	osCode,
	csCode
};

static map<string, CodeValue> s_mapCodeValues = {
	{"SD", sdCode},
	{"CD", cdCode},
	{"SL", slCode},
	{"INS", insCode},
	{"DEL", delCode},
	{"UPD", updCode},
	{"OB", obCode},
	{"CB", cbCode},
	{"OS", osCode},
	{"CS", csCode}};

//
//-----------------------utilities-------------------------
void printInt(int &data)
{
	cout << data << " ";
}

void printNSpace(int n)
{
	for (int i = 0; i < n - 1; i++)
		cout << " ";
}

void printInteger(int &n)
{
	cout << n << " ";
}
void printExchange(Exchange &n)
{
	cout << n.BC << ": " << n.QC << endl;
}

bool isDigitString(string a)
{
	for (size_t i = 0; i < a.length(); i++)
	{
		if (!isdigit(a[i]) && a[i] != '\0')
			return false;
	}
	return true;
}

//-----------------------utilities-------------------------

//-----------------------PROCESS DATA-------------------------
ProcessData::ProcessData()
{
}
ProcessData::~ProcessData()
{
}
int ProcessData::split(string line, string *&sp)
{
	sp = new string[MAXSIZECODE];
	const string SEP = " ";
	size_t pos, lastpos = 0, idx = 0;
	do
	{
		pos = line.find(SEP, lastpos);
		sp[idx] = line.substr(lastpos, pos - lastpos);
		lastpos = pos + 1;
		idx++;
	} while (pos != string::npos);
	return idx;
}

int ProcessData::process(string line)
{
	// cout << line << endl;
	if (line.length() < 2)
	{
		return -1;
	}
	if (!isalpha(line[line.length() - 1]) && !isdigit(line[line.length() - 1]))
		line = line.substr(0, line.length() - 1);
	string *p;
	int n;
	n = ProcessData::split(line, p);
	// cout << p[0] << ": " << p[0].length() << endl;
	// cout << n << endl;
	if (n <= 0 || p[0].length() == 1)
	{
		delete[] p;
		return -1;
	}
	int res = -1;
	try
	{
		switch (s_mapCodeValues[p[0]])
		{
		case sdCode:
			res = this->sd(p, n);
			break;
		case cdCode:
			res = this->cd(p, n);
			break;
		case slCode:
			res = this->sl(p, n);
			break;
		case insCode:
			res = this->insert(p, n);
			break;
		case updCode:
			res = this->update(p, n);
			break;
		case delCode:
			res = this->del(p, n);
			break;
		case obCode:
			res = this->ob(p, n);
			break;
		case cbCode:
			res = this->cb(p, n);
			break;
		case osCode:
			res = this->os(p, n);
			break;
		case csCode:
			res = this->cs(p, n);
			break;
		default:
			res = -1;
		}
	}
	catch (invalid_argument iax)
	{
		delete[] p;
		return res;
	}
	delete[] p;
	return res;
}

int ProcessData::insert(const string *sp, const int n)
{
	if (n != 6 || sp[1].length() > 3 || sp[2].length() > 3)
	{
		return -1;
	}
	if (sp[1] != "USD" && sp[2] != "USD")
		return -1;
	Link<Exchange> *ptr = this->mainlist.findExch(sp[1], sp[2]);
	TimeUnit a;
	a.time = stoi(sp[3]);
	a.BP = stod(sp[4]);
	a.AP = stod(sp[5]);
	if (ptr != NULL)
	{
		ptr->data.tree.insert(a);
		return ptr->data.tree.root->data.time;
	}
	else
	{
		Exchange b(sp[1], sp[2]);
		this->mainlist.prepend(b);
		this->mainlist.head->data.tree.insert(a);
		return this->mainlist.head->data.tree.root->data.time;
	}
}

int ProcessData::del(const string *sp, const int n)
{
	if (n > 5 || n < 3 || sp[1].length() > 3 || sp[2].length() > 3)
	{
		// cout << "validin";
		return -1;
	}
	Link<Exchange> *ptr = this->mainlist.findExch(sp[1], sp[2]);
	if (ptr == NULL)
	{
		// cout << "ptr is null";
		return -1;
	}
	else
	{
		if (ptr->data.tree.root == NULL)
		{
			// cout << "root is null";
			return -1;
		}
		else if (n == 5)
		{
			if (sp[3] > sp[4])
				return -1;
			TimeUnit a;
			a.time = stoi(sp[3]);
			TimeUnit b;
			b.time = stoi(sp[4]);
			while (ptr->data.tree.checkTimeRangeTrav(a, b))
			{
				ptr->data.tree.removeInRange(a, b);
			}
			if (ptr->data.tree.root == NULL)
			{
				return 1;
			}
			return ptr->data.tree.root->data.time;
		}
		else if (n == 4)
		{
			TimeUnit a;
			a.time = stoi(sp[3]);
			ptr->data.tree.removeInRange(a, a);
			if (ptr->data.tree.root == NULL)
			{
				return 1;
			}
			return ptr->data.tree.root->data.time;
		}
		else
		{
			ptr->data.tree.~AVL();
			return 1;
		}
	}
}

int ProcessData::update(const string *sp, const int n)
{
	if (n != 6 || sp[1].length() != 3 || sp[2].length() != 3 || !isDigitString(sp[3]))
	{
		return -1;
	}
	Link<Exchange> *ptr = this->mainlist.findExch(sp[1], sp[2]);
	TimeUnit a;
	a.time = stoi(sp[3]);
	a.BP = stod(sp[4]);
	a.AP = stod(sp[5]);
	if (ptr == NULL)
	{
		return -1;
	}
	else if (ptr->data.tree.checkTimeRangeTrav(a, a))
	{
		ptr->data.tree.insert(a);
		return ptr->data.tree.root->data.time;
	}
	else
	{
		return -1;
	}
}

int ProcessData::sd(const string *sp, const int n)
{
	if (n != 2 || !isDigitString(sp[1]))
	{
		return -1;
	}
	if (!this->mainlist.firstSet)
	{
		this->mainlist.mn = stoi(sp[1]);
		this->mainlist.firstSet = true;
		return 1;
	}
	// else if (this->mainlist.mn <= 0)
	// {
	// 	return -1;
	// }
	//3.3.2 contraint
	// else if (this->mainlist.mn < stoi(sp[1]) && this->mainlist.openTradeList.empty())
	// {
	// 	return -1;
	// }
	else
	{
		this->mainlist.mn = stoi(sp[1]);
		return 1;
	}
}

int ProcessData::cd(const string *sp, const int n)
{
	return this->mainlist.mn > 0 ? mainlist.mn + EP : mainlist.mn - EP;
}

int ProcessData::sl(const string *sp, const int n)
{
	// cout << "sl called\n";
	if (n != 2 || !isDigitString(sp[1]))
	{
		return -1;
	}
	//not include negative mn
	if (this->mainlist.mn)
	{
		this->mainlist.lv = stoi(sp[1]);
		return mainlist.mn * mainlist.lv;
	}
	else
	{
		return -1;
	}
}

int ProcessData::ob(const string *sp, const int n)
{
	if (n != 6 || sp[1].length() != 3 || sp[2].length() != 3 || !isDigitString(sp[3]))
	{
		return -1;
	}
	if (mainlist.mn <= 0)
	{
		return -1;
	}
	int id = stoi(sp[5]);
	if (this->mainlist.openTradeList.count(id))
	{
		return -1;
	}
	else
	{
		//find Exch
		Link<Exchange> *ptr;
		ptr = this->mainlist.findExch(sp[1], sp[2]);
		if (ptr == NULL)
		{
			return -1;
		}
		//find time in tree
		Node<TimeUnit> *temp;
		TimeUnit atime;
		atime.time = stoi(sp[3]);
		temp = ptr->data.tree.findNearestTime(atime);
		if (temp == NULL)
		{
			return -1;
		}
		openDetail open;
		open.time = atime.time;
		open.QC = ptr->data.QC;
		open.BC = ptr->data.BC;
		open.isOpenBuy = true;
		open.lot = stod(sp[4]);
		open.oMoney = temp->data.AP * open.lot * 100000;
		if (open.oMoney > mainlist.mn * mainlist.lv)
		{
			return -1;
		}
		mainlist.openTradeList.insert({id, open});

		cout << "os id: " << id << " profit: " << open.oMoney << endl;

		if (open.QC == "USD")
		{
			return myround(open.oMoney);
		}
		else
		{
			return myround(open.oMoney / temp->data.AP);
		}
	}
}
int ProcessData::os(const string *sp, const int n)
{
	if (n != 6 || sp[1].length() != 3 || sp[2].length() != 3 || !isDigitString(sp[3]))
	{
		return -1;
	}
	if (mainlist.mn <= 0)
	{
		return -1;
	}
	int id = stoi(sp[5]);
	if (this->mainlist.openTradeList.count(id))
	{
		return -1;
	}
	else
	{
		//find Exch
		Link<Exchange> *ptr;
		ptr = this->mainlist.findExch(sp[1], sp[2]);
		if (ptr == NULL)
		{
			return -1;
		}
		//find time in tree
		Node<TimeUnit> *temp;
		TimeUnit atime;
		atime.time = stoi(sp[3]);
		temp = ptr->data.tree.findNearestTime(atime);
		if (temp == NULL)
		{
			return -1;
		}
		openDetail open;
		open.time = atime.time;
		open.QC = ptr->data.QC;
		open.BC = ptr->data.BC;
		open.isOpenBuy = false;
		open.lot = stod(sp[4]);
		open.oMoney = temp->data.BP * open.lot * 100000;
		if (open.oMoney > mainlist.mn * mainlist.lv)
		{
			return -1;
		}
		mainlist.openTradeList.insert({id, open});
		cout << "os id: " << id << " profit: " << open.oMoney << endl;
		if (open.QC == "USD")
		{
			return myround(open.oMoney);
		}
		else
		{
			return myround(open.oMoney / temp->data.AP);
		}
	}
}

int ProcessData::cb(const string *sp, const int n)
{
	if (n != 3 || (!isDigitString(sp[1])) || (!isDigitString(sp[2])))
	{
		return -1;
	}
	int id = stoi(sp[2]);
	Node<TimeUnit> *temp;
	TimeUnit atime;
	atime.time = stoi(sp[1]);
	if (!this->mainlist.openTradeList.count(id))
	{
		return -1;
	}
	else if (atime.time < this->mainlist.openTradeList[id].time || this->mainlist.openTradeList[id].isOpenBuy)
		return -1;
	else
	{
		openDetail open = this->mainlist.openTradeList[id];
		double profit = cbProfit(stoi(sp[1]), open);
		this->mainlist.openTradeList.erase(id);
		cout << "cb id: " << id << " profit: " << profit << endl;
		if (mainlist.mn <= 0)
		{
			map<int, openDetail>::iterator itr;
			for (itr = this->mainlist.openTradeList.begin(); itr != this->mainlist.openTradeList.end(); ++itr)
			{
				// cout << "id: " << itr->first << endl;
				double calprofit;
				if (itr->second.isOpenBuy)
					calprofit = csProfit(atime.time, itr->second);
				else
					calprofit = cbProfit(atime.time, itr->second);
				// cout << "profit: " << calprofit << endl;
				// cout << "mn: " << mainlist.mn << endl;
			}
			this->mainlist.openTradeList.clear();
		}
		return myround(profit);
	}
}
int ProcessData::cs(const string *sp, const int n)
{
	if (n != 3 || !isDigitString(sp[1]) || !isDigitString(sp[2]))
	{
		return -1;
	}
	int id = stoi(sp[2]);
	Node<TimeUnit> *temp;
	TimeUnit atime;
	atime.time = stoi(sp[1]);
	if (!this->mainlist.openTradeList.count(id))
	{
		return -1;
	}
	else if (atime.time < this->mainlist.openTradeList[id].time || !this->mainlist.openTradeList[id].isOpenBuy)
	{
		return -1;
	}
	else
	{
		openDetail open = this->mainlist.openTradeList[id];
		double profit = csProfit(stoi(sp[1]), open);
		this->mainlist.openTradeList.erase(id);
		cout << "cs id: " << id << " profit: " << profit << endl;

		if (mainlist.mn <= 0)
		{
			map<int, openDetail>::iterator itr;
			for (itr = this->mainlist.openTradeList.begin(); itr != this->mainlist.openTradeList.end(); ++itr)
			{
				double calprofit;
				if (itr->second.isOpenBuy)
					calprofit = csProfit(atime.time, itr->second);
				else
					calprofit = cbProfit(atime.time, itr->second);
				// this->mainlist.openTradeList.erase(itr->first);
			}
			this->mainlist.openTradeList.clear();
		}
		return myround(profit);
	}
}

double ProcessData::csProfit(int time, openDetail open)
{
	Link<Exchange> *ptr;
	ptr = this->mainlist.findExch(open.BC, open.QC);
	if (ptr == NULL)
	{
		return -1;
	}
	Node<TimeUnit> *temp;
	TimeUnit atime;
	atime.time = time;
	temp = ptr->data.tree.findNearestTime(atime);
	if (temp == NULL)
	{
		return -1;
	}
	double profit = (temp->data.BP * open.lot * 100000) - open.oMoney;
	// cout << "cs lot: " << open.lot << " cs BP: " << temp->data.BP << " cs oMoney: " << open.oMoney << " profit: " << profit << endl;
	if (open.QC != "USD")
	{
		profit /= temp->data.AP;
	}
	mainlist.mn += profit;
	cout << "money: " << mainlist.mn << endl;
	return profit;
}
double ProcessData::cbProfit(int time, openDetail open)
{
	Link<Exchange> *ptr;
	ptr = this->mainlist.findExch(open.BC, open.QC);
	if (ptr == NULL)
	{
		return -1;
	}
	Node<TimeUnit> *temp;
	TimeUnit atime;
	atime.time = time;
	temp = ptr->data.tree.findNearestTime(atime);
	if (temp == NULL)
	{
		return -1;
	}
	double profit = open.oMoney - (temp->data.AP * open.lot * 100000);
	if (open.QC != "USD")
	{
		profit /= temp->data.AP;
	}
	mainlist.mn += profit;
	cout << "money: " << mainlist.mn << endl;
	return profit;
}

int ProcessData::myround(double a)
{
	if (abs(a - (int)(a > 0 ? a + EP : a - EP)) < EP)
	{
		return (int)(a > 0 ? a + EP : a - EP);
	}
	else
		return a > 0 ? (int)ceil(a) : (int)floor(a);
}

//-----------------------PROCESS DATA-------------------------

//-----------------------LINKED LIST-------------------------

//-----------------------LINKED LIST-------------------------

//-----------------------AVL TREE----------------------------

//-----------------------AVL TREE----------------------------