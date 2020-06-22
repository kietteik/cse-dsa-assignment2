#include "processData.h"

enum CodeValue
{
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

	string *p;
	int n = ProcessData::split(line, p);
	// cout << p[0] << endl;
	if (n <= 0)
	{
		delete[] p;
		return -1;
	}
	int res = -1;
	// try
	// {
	switch (s_mapCodeValues[p[0]])
	{
	case insCode:
		res = this->insert(p, n);
		break;
	case updCode:
		res = this->update(p, n);
		break;
	case delCode:
		res = this->del(p, n);
		break;
	default:
		res = -1;
	}
	// }
	// catch (invalid_argument iax)
	// {
	// 	delete[] p;
	// 	return res;
	// }
	delete[] p;
	return res;
}

int ProcessData::insert(const string *sp, const int n)
{
	if (n > 6 || sp[1].length() > 3 || sp[2].length() > 3)
	{
		return -1;
	}
	Link<Exchange> *ptr = this->mainlist.findExch(sp[1], sp[2]);
	TimeUnit a;
	a.time = stoi(sp[3]);
	a.BP = stof(sp[4]);
	a.AP = stof(sp[5]);
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
	if (n != 6 || sp[1].length() > 3 || sp[2].length() > 3)
	{
		return -1;
	}
	Link<Exchange> *ptr = this->mainlist.findExch(sp[1], sp[2]);
	TimeUnit a;
	a.time = stoi(sp[3]);
	a.BP = stof(sp[4]);
	a.AP = stof(sp[5]);
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

//-----------------------PROCESS DATA-------------------------

//-----------------------LINKED LIST-------------------------

//-----------------------LINKED LIST-------------------------

//-----------------------AVL TREE----------------------------

//-----------------------AVL TREE----------------------------