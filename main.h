#define main_h

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

#define NA 20
#define AD 50
#define SIZE 50

using namespace std;

// END IS A POSITION AFTER THE LAST ONE

struct recip {   // (recipient) name + adress
    char name[NA];      // name
    char adress[AD];     // adress
    recip(): name("\0"),  adress("\0") {};
    recip(const char n[], const char a[]) {
        strcpy(name, n);
        strcpy(adress, a);
    };
    int operator ==(const recip& x) { return equal(*this, x);};
    friend ostream& operator <<(ostream& out, const recip& x) {
        return out << "Name: " << x.name << " Adress: " << x.adress << endl;};
    int equal(const recip& x, const recip& y);
};
int recip::equal(const recip& a, const recip& b) { // if a is equal b returns 0
    return (strcmp(a.name, b.name) == 0 && strcmp(a.adress, b.adress) == 0);
}

recip fic_x("null", "null"); // global fictitious object recip (0, 0)

namespace List1 {  // list on array

typedef int position;

class list {
public:
    void insert(recip x, position p); // insert element x in position p in list l
    position locate(recip& x); // return the position(digit)
    recip retrieve(position p); // return element on position p in list, if there is no object return fict. obj
    position next(position p); // returns position after p
    position previous(position p); // returns position before p
    void makenull() { n = 0;};  // making the list empty
    position first() const; // return the first element, if there is no elements - returns fictitious object
    position end() const { return n;}; // position after the last one
    void delete_x(position p);
    void printlist() const;
    ~list() { makenull();};
private:
    recip l[SIZE];
    int n = 0; // position after the last one(number of elements in list)
};

void list::insert(recip x, position p) { // inserts in position p in
    recip temp;
    int i;
    if (p <= n && p > -1) { // checking if position exsists in list
        //inserting smth
        for (i = p; i <= n; i++) { // addition new element
            temp = l[i + 1];
            l[i + 1] = l[i];
        }
        l[p] = x;
        n++;
    }
}
position list::locate(recip& x) { // return the number of position возвращает позицию первого пустого если элемента нет в списке
    int i;
    for (i = 0; i < n; i++) {
        //cout << "Name: " << l[i].name << " Adress: " << l[i].adress << endl;
        if (l[i] == x)
            return i;
    }
    return -1;
}
recip list::retrieve(position p) {
    return (p < n)?(l[p]):(fic_x);
}
int list::next(position p) { // returns position of next element, if it doesnt exists - returns -1
    if (p > -1 && p < n)
        return p + 1;
    return -1;
}
int list::previous(position p) { // returns position of previous element, if it doesnt exists - returns position of "end" element
    if (p > 0 && p <= n)
        return p - 1;
    return -1;
}
position list::first() const { // return the first element
    return (n > 0)?(0):(-1); // fictitious object
};
void list::delete_x(position p) {
    int i;
    if (p < n) {  // if position exsists in list
        for (i = p; i < n; i++)
            l[i] = l[i + 1];
        n--;
    }
};
void list::printlist() const {
    position p;
    for (p = 0; p < n; p++) {
        cout << "Name: " << l[p].name << " Adress: " << l[p].adress << endl;
    }
}
}

//-----------------------------------------------------------//
namespace List2 {  // list on linked list

struct recip_x {   // element of list (recipient + next)
    recip val;
    recip_x* next;
    recip_x(recip x, recip_x* h = NULL): val(x), next(h) {};
};
// global fictitious object (recip, link to recip)
recip_x fic_x(recip("null", "null"), &fic_x);
typedef recip_x* position;

class list {
public:
    void insert(recip x, position p);
    recip retrieve(position p); // return element on position p in list, if there is no object return fict. obj
    position locate(recip x); // return Position of element x in list l, return pointer
    position next(position p); // returns position after p
    position previous(position p); // returns position before p
    position end() const { return NULL; };
    void delete_x(position p); // deleting element in position p
    position first() const;
    void printlist() const;
    void makenull() { if (l != NULL) delete_list(); };  // making the list empty
    ~list() { makenull();};
    
private:
    recip_x* l = NULL; // pointer on the list
    void delete_list(); // deleting elements in list
    position search_position(recip x); // return position
    position check_position(position p); // if position exists returns pointer on previous
};

position list::check_position(position p) { // if position exists returns pointer on previous
    position n = l, prev = l;
    while (n != NULL) {
        if (n == p)
            return prev;
        prev = n;
        n = n->next;
    }
    if (NULL == p)
        return prev;
    return NULL; // if position doesnt exist in list
}
position list::search_position(recip x) { // search for element, returns object before the p
    position t = l;
    while (t != NULL) { // while not the end of list
        if (t->val == x)
            return t;
        t = t->next;
    }
    return NULL; //returns fic obj if there is no element in list
}
void list::insert(recip x, position p) { // inserts in position p in
    if (p == l)  // insert in head
        l = new recip_x(x, l);// insert in the first position
    else { // insert in other part of list
        position n = check_position(p);
        if (n != NULL) {
            cout << n->val.name << endl;
            position t = new recip_x(x, n->next);
            n->next = t;
        }
    }
}
recip list::retrieve(position p) { // return element on position p in list, if there is no object return fict. obj
    if (p == l) // if p is in the first position of list
        return l->val;
    position n = check_position(p);
    if (n == NULL)
        return fic_x.val;
    return n->next->val;
}
position list::next(position p) { // position p - pointer on recip_x, returns pointer on the next element
    if (p != NULL)
        return p->next;
    return fic_x.next;
}
position list::previous(position p) {
    if (p == l)
        return fic_x.next;
    position n = check_position(p);
    if (n == NULL)
        return fic_x.next;
    return n;
}
position list::locate(recip x) {
    position p = search_position(x);
    if (p != NULL)
        return p->next;
    return fic_x.next; // null position
}
position list::first() const {
    if (l != NULL)
        return l;
    return fic_x.next;
}
void list::delete_x(position p) { // deleting element in position p
    position n = check_position(p); // if the position exists in list, returns the previous
    if (n != NULL) {
        position t = n->next; // t - position of p in the current list
        if (p == n) {
            l = n->next;
            delete n;
        }
        else {
            n->next = p->next;
            delete t;
        }
    }
}
void list::printlist() const {
    position p = l;
    while (p != NULL) {
        cout << "Name:" << p->val.name << " Adress:" << p->val.adress << endl;
        p = p->next;
    }
}
void list::delete_list() {
    position p = l->next, n = l;
    while (p != NULL) {
        delete n;
        n = p;
        p = p->next;
    }
    delete n;
    l = NULL;
}
}

//-----------------------------------------------------------//
namespace List3 { // list on Doubly linked list
struct recip_x {
    recip val;
    recip_x* prev;
    recip_x* next;
    recip_x(recip x, recip_x* p = NULL, recip_x* n = NULL): val(x), prev(p), next(n) {};
};

typedef recip_x* position;
recip_x fic_x(recip("null", "null"), &fic_x, &fic_x);

class list {
public:
    void insert(recip x, position p); // insert element x in position p in list l
    position locate(recip x); // return Position of element x in list l, return pointer
    recip retrieve(position p); // return element on position p in list, if there is no object return fict. obj
    position next(position p); // return the next position
    position previous(position p); // return the previous position
    position end() const { return NULL;}; // end - the position of element after the last one
    void delete_x(position p); // deleting element in position p
    void makenull() { if (head != NULL) delete_list(); }; // making the list empty
    position first() const;
    void printlist() const;
    ~list() { makenull();};
private:
    //recip_x* l = NULL; // pointer on the list
    position head = NULL;
    position tail = NULL;
    void delete_list();
    position search_position(recip x); // searching position of element by its recip
    position check_position(position p);  // checking if the position exists in the list
};
position list::search_position(recip x) { // return the position of current element
    position t = head;
    while (t != NULL) {
        if (t->val == x)
            return t;
        t = t->next;
    }
    return NULL; // if there is no element returns nothing
}
position list::check_position(position p) {  // checking if the position exists in the list
    position t = head;
    while (t != NULL) {
        if (t == p)
            return p;
        t = t->next;
    }
    return NULL;
}
void list::insert(recip x, position p) {
    if (p == head) { // insert in head
        position temp = new recip_x(x, NULL, head);
        if (head != NULL)  // if the list isn't empty
            head->prev = temp;
        else
            tail = temp;
        head = temp;
    }
    else {
        if (p == NULL) { // insert st the end
            position temp = new recip_x(x, tail, NULL);
            tail->next = temp;
            tail = tail->next;
        }
        else {
            position temp = check_position(p);
            if (temp != NULL) { // insert in somewhere else
                position t = new recip_x(x, temp->prev, temp);
                (temp->prev)->next = t;
                temp->prev = t;
            }
        }
    }
}
position list::locate(recip x) { // return Position of element x in list l
    position t = search_position(x);
    return (t != NULL)?(t):(&fic_x);
}
recip list::retrieve(position p) {
    position t = check_position(p);
    return (t != NULL)?(t->val):(fic_x.val);
}
position list::next(position p) {
    if (p != NULL)
        return p->next;
    return fic_x.next;
}
position list::previous(position p) {
    if (p == NULL)
        return tail;
    position t = check_position(p);
    if (t != NULL)
        return t;
    return fic_x.next;
}
position list::first() const {
    if (head != NULL)
        return head;
    return fic_x.next;
}
void list::delete_x(position p) { // delete element p
    position t = check_position(p);
    if (t != NULL) { // if position exists
        if (t->prev != NULL) { // if not head
            (t->prev)->next = t->next;
            if (t->next == NULL) // if end
                tail = t->prev;
            else
                (t->next)->prev = t->prev;
            delete p;
        }
        else { //
            head = t->next;
            if (t->next == NULL)
                tail = NULL;
            else
                (t->next)->prev = NULL;
            delete t;
        }
    }
}
void list::printlist() const {
    position p = head;
    while (p != NULL) {
        cout << "Name:" << p->val.name << " Adress:" << p->val.adress << endl;
        p = p->next;
    }
}
void list::delete_list() {
    position p = head->next, n = head;
    while (p != NULL) {
        delete n;
        n = p;
        p = p->next;
    }
    delete n;
    head = NULL;
}
}
//-----------------------------------------------------------//
namespace List4 { // list on cursors
struct recip_x {
    recip_x(): next(-1) {};
    recip_x(recip x): val(x), next(-1) {};
    recip val;
    int next; // index of next element
};

typedef int position;
recip_x fic_x(recip("null", "null"));
// -1 = NULL
class list {
public:
    list() { init();}; // init head
    static void init();
    void insert(recip x, position p); // insert element x in position p in list l
    position locate(recip x); // return Position of element x in list l, return digit
    recip retrieve(position p); // return element on position p in list, if there is no object return fict. obj
    void delete_x(position p); // deleting element in position p
    position next(position p); //
    position previous(position p); //
    void makenull(); // making the list empty
    position first() const { return head;}; // returns the position of the first element in the list
    void printlist() const;
    position end() const { return -1;};
    ~list() { makenull();};
private:
    static recip_x l[SIZE]; //
    static position space; // beginning of free's list - the same for every list
    position head = -1; // the beginning of current list
    position search_position(recip x);
    position check_position(position p);
};

recip_x list::l[SIZE];
position list::space;

position list::search_position(recip x) { // return the position of current element
    position t = head;
    while (t != -1) {
        if (l[t].val == x)
            return t;
        t = l[t].next;
    }
    return -1; // if there is no element returns nothing
}
position list::check_position(position p) {  // if position exists in list
    position t = head, prev = head;
    while (prev != -1) {
        if (p == t)
            return prev;
        prev = t;
        t = l[t].next;
    }
    return -1;
}
void list::init() {
    int i;
    space = 0;
    for(i = 0; i < SIZE - 1; i++)
        l[i].next = i + 1;
    l[SIZE - 1].next = -1;
}
//recip_x l; // syntax recquirements - init of the list

void list::insert(recip x, position p) {
    // from the beginning of the current list
    if (head == -1) { // if the list is empty
        // put into the first place of space
        position temp = l[space].next;
        l[space].val = x;
        l[space].next = -1;
        head = space;
        space = temp;
    }
    else
        if (check_position(p) != -1) { // case when position is in list
            position temp = l[space].next;
            l[space].val = l[p].val;
            l[space].next = l[p].next;
            l[p].val = x;
            l[p].next = space;
            space = temp;
        }
}
position list::locate(recip x) {
    position t = search_position(x);
    return (t != -1)?(t):(fic_x.next);
}
recip list::retrieve(position p) {
    if (p == head)
        return l[p].val;
    position t = check_position(p); // returns position of the previous element
    if (t != -1) {
        t = l[t].next;
        return l[t].val;
    }
    return fic_x.val;
}
position list::next(position p) {
    if (p != -1)
        return l[p].next;
    return fic_x.next;
}
position list::previous(position p) {
    position t = check_position(p);
    return (t != -1)?(t):(fic_x.next);
}

void list::printlist() const {
    position p = head;
    while (p != -1) {
        cout << l[p].val;
        p = l[p].next;
    }
}

void list::delete_x(position p) {
    if (p == head) {
        head = l[head].next;
        l[p].next = space;
        space = p;
    }
    else {
        position temp = check_position(p); // prev to p
        l[temp].next = l[p].next;
        l[p].next = space;
        space = p;
    }
}
void list::makenull() {
    position i = space, j = head;
    space = head;
    while (l[j].next != -1)
        j = l[j].next;
    l[j].next = i;
    head = -1;
}
}
