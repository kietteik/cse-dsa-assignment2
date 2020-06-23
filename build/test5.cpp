#include "main.h"
#include "processData.h"

using namespace std;

int main(int argc, char **argv)
{
    ProcessData *main = new ProcessData();
    Exchange fst("ABC", "ABC");
    main->mainlist.append(fst);
    Exchange b("BCD", "BCD");
    main->mainlist.append(b);

    // string *sp;
    // string line = "INS NZD USD 12 2.2 4.4";
    // main->split(line, sp);
    // Link<Exchange> *ptr = main->mainlist.findExch(sp[1], sp[2]);
    // TimeUnit a;
    // a.time = stoi(sp[3]);
    // a.BP = stof(sp[4]);
    // a.AP = stof(sp[5]);
    // if (ptr != NULL)
    // {
    //     ptr->data.tree.insert(a);
    // }
    // else
    // {
    //     Exchange b(sp[1], sp[2]);
    //     main->mainlist.prepend(b);
    //     main->mainlist.head->data.tree.insert(a);
    // }
    main->process("INS BCD BCD 2 2.2 3.3");
    main->process("INS BCD BCD 3 2.2 3.3");
    main->process("INS BCD BCD 4 2.2 3.3");
    main->process("INS BCD BCD 5 2.2 3.3");
    main->process("INS BCD BCD 6 2.2 3.3");
    main->process("INS BCD BCD 7 2.2 3.3");
    main->process("INS BCD BCD 800 2.2 3.3");
    main->process("INS BCD BCD 900 2.2 3.3");
    cout << main->process("INS BCD BCD 90 9.9 3.3") << endl;
    main->process("INS NZD USD 12 2.2 4.4");
    main->process("INS NZD USD 13 2.2 4.4");
    main->process("INS NZD USD 14 2.2 4.4");
    main->process("INS NZD USD 15 2.2 4.4");
    main->process("INS NZD USD 16 2.2 4.4");
    main->process("INS NZD USD 17 2.2 4.4");
    main->process("INS NZD USD 17 2.3 4.4");
    cout << main->process("INS NZD USD 17 2.4 4.4") << endl;

    Link<Exchange> *ptr;
    // ptr = main->mainlist.findExch("NZD", "USD");
    // cout << "NZD: USD\n";
    // ptr->data.tree.printTreeStructure();
    // ptr = main->mainlist.findExch("BCD", "BCD");
    // cout << "BCD: BCD\n";
    // ptr->data.tree.printTreeStructure();

    // main->process("DEL NZD USD 12 14");
    // main->process("DEL NZD USD");
    // main->process("DEL BCD BCD");

    main->process("INS BCD BCD 3 2.2 3.3");
    main->process("INS BCD BCD 4 2.2 3.3");
    main->process("INS BCD BCD 5 2.2 3.3");
    main->process("INS BCD BCD 6 2.2 3.3");
    main->process("INS BCD BCD 7 2.2 3.3");
    main->process("UPD NZD USD 9 2.2 3.3");
    main->process("UPD BCD BCD 7 4.4 3.3");

    cout << "SL " << main->process("SL 100") << endl;
    cout << "MN: " << main->mainlist.mn;
    cout << "SD: " << main->process("SD 1000") << endl;
    cout << "SL " << main->process("SL 100") << endl;
    cout << "SD: " << main->process("CD") << endl;
    main->process("INS EUR USD 1101 1.102090 1.102150");
    main->process("INS EUR USD 1103 1.01284 1.01235");
    main->process("INS EUR USD 1107 1.101950 1.101980");
    main->process("UPD EUR USD 1108 1.01284 1.01235");

    cout << "OS PROCESS: " << main->process("OS EUR USD 1101 0.33 1123456") << endl;

    ptr = main->mainlist.findExch("EUR", "USD");
    cout << "EUR: USD\n";
    ptr->data.tree.printTreeStructure();

    // cout << "CB PROCESS: " << main->process("CB 1107 1123456") << endl;

    Node<TimeUnit> *temp;
    TimeUnit atime;
    atime.time = stoi("1101");
    temp = ptr->data.tree.findNearestTime(atime);
    if (temp == NULL)
    {
        return -1;
    }
    openDetail open;
    open.lot = 0.33;
    open.oMoney = temp->data.BP * open.lot * main->mainlist.mn * main->mainlist.lv;

    cout << (int)open.oMoney << endl;
    // main->mainlist.traverse(printExchange);
    delete main;
}