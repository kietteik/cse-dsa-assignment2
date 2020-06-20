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
    main->process("INS BCD BCD 8 2.2 3.3");
    main->process("INS BCD BCD 9 2.2 3.3");
    cout << main->process("INS BCD BCD 9 9.9 3.3") << endl;
    main->process("INS NZD USD 12 2.2 4.4");
    main->process("INS NZD USD 13 2.2 4.4");
    main->process("INS NZD USD 14 2.2 4.4");
    main->process("INS NZD USD 15 2.2 4.4");
    main->process("INS NZD USD 16 2.2 4.4");
    main->process("INS NZD USD 17 2.2 4.4");
    main->process("INS NZD USD 17 2.3 4.4");
    cout << main->process("INS NZD USD 17 2.4 4.4") << endl;

    Link<Exchange> *ptr = main->mainlist.findExch("NZD", "USD");
    cout << "NZD: USD\n";
    ptr->data.tree.printTreeStructure();
    ptr = main->mainlist.findExch("BCD", "BCD");
    cout << "BCD: BCD\n";
    ptr->data.tree.printTreeStructure();

    main->mainlist.traverse(printExchange);
}