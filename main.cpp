#include "main.h"

//-----------------------------------------------------------//

recip fic("null", "null");

using namespace List3; // particular adt for every structure

namespace Stack {  // stack using adt list
class stck {
public:
    void push(recip x) { l.insert(x, l.end());};
    recip pop();
    recip top() { return l.retrieve(l.previous(l.end()));};
    int empty() const { return (l.first() == l.end());};
    ~stck() { l.makenull();};
private:
    list l;
};

recip stck::pop() {
    if (!empty()) {
        recip x = l.retrieve(l.previous(l.end()));
        l.delete_x(l.previous(l.end()));
        return x;
    }
    return fic;
}
};

namespace Queue1 { // queue on array
class queue {
public:
    void enqueue(recip x); // add element
    recip dequeue(); // extract element from the head
    recip front() { return l[head];}; // return copy of the first element
    int full() { return (tail == SIZE);}; // true if the queue is full
    int empty() { return (tail == head);};// true if empty
    void makenull(); // make the list empty
    ~queue() { makenull();};
private:
    static recip l[SIZE];
    int head = 0, tail = 0;
};

recip queue::l[SIZE];

void queue::enqueue(recip x) {
    if (!full()) {
        if (empty()) {
            l[head] = x;
            tail++;
        }
        else
            l[tail++] = x;
    }
}
recip queue::dequeue() {
    if (empty())
        return fic;
    return (l[head++]);
}
void queue::makenull() {
    head = 0;
    tail = 0;
}
}

namespace Queue2 { // Circular linked list
struct node {
    recip val;
    node* next;
    node(recip x, node* n = NULL): val(x), next(n) {};
};
class queue {
public:
    void enqueue(recip x); // add element
    recip dequeue(); // extract element from the head
    recip front() { return ((tail != NULL)?((tail->next)->val):(fic));}; // return copy of the first element
    int full() { return false;}; // true if the queue is full
    int empty() { return (tail == NULL);};// true if empty
    void makenull(); // make the list empty
    ~queue() { makenull();};
private:
    node* tail = NULL;
};
void queue::enqueue(recip x) {
    node* p = new node(x);
    if (tail != NULL) {
        node* temp = tail->next;
        tail->next = p;
        tail = tail->next;
        tail->next = temp;
    }
    else {
        tail = p;
        tail->next = tail;
    }
}
recip queue::dequeue() { // extract element from the head
    if (tail != NULL) {
        node* p = tail->next;
        tail->next = p->next;
        recip x = p->val;
        delete p;
        return x;
    }
    return fic;
}
void queue::makenull() {
    node* p = tail->next;
    node* t = p->next;
    while (t != tail) {
        delete p;
        p = t;
        t = t->next;
    }
    tail = NULL;
}
}

namespace Queue3 { // stack adt list
class queue {
public:
    void enqueue(recip x); // add element in tail
    recip dequeue(); // extract element from the head
    recip front() { return l.retrieve(l.first());}; // return copy of the first element
    //int full() ; // true if the queue is full
    int empty() { return (l.first() == l.end());};// true if empty
    void makenull() { l.makenull();}; // make the list empty
    ~queue() { l.makenull();};
private:
    list l;
};

void queue::enqueue(recip x) {
    l.insert(x, l.end());
}
recip queue::dequeue() {
    recip x = l.retrieve(l.first());
    l.delete_x(l.first());
    return x;
}
}


namespace Mapping1 { // maping on linked list

typedef char domaintype [NA]; // key // char
typedef char rangetype [AD]; // value // char

struct node {
    node* next;
    recip n; // name & adress
    node(recip x = fic, node* p = NULL): n(x), next(p) {};
};

class mapping {
public:
    void makenull() ; // delete mapping
    void assign(domaintype d, rangetype r); // make a pair
    int compute(domaintype d, rangetype& r); // update value of r
    void print() const;
private:
    node* m = NULL;
    node* search(domaintype d);
};
node* mapping::search(domaintype d) { // searching for element with particular domain
    node* p = m;
    while (p != NULL) {
        if (strcmp(p->n.name,d) == 0) // if it is the right key
            return p;
        p = p->next;
    }
    return NULL;
}
void mapping::assign(domaintype d, rangetype r) {
    node* p = search(d);
    if (p == NULL) { // if there is no key "d" in the list, so let's put it in the head
        recip temp(d, r);
        m = new node(temp, m);
    }
    else // changing the value to "r"
        strcpy(p->n.adress, r);
}
int mapping::compute(domaintype d, rangetype& r) {
    node* p = search(d);
    if (p == NULL) // if there is no pair (d, r)
        return 0;
    strcpy(r, p->n.adress); // copying the value
    return 1;
}
void mapping::print() const {
    node* p = m;
    while (p != NULL) {
        cout << p->n;
        p = p->next;
    }
}
void mapping::makenull() {
    node* p = m->next, *prev = m;
    while (p != NULL) {
        delete prev;
        prev = p;
        p = p->next;
    }
    delete p;
    m = NULL;
}
}

namespace Mapping2 { // just Mapping

typedef char domaintype [NA]; // key // char
typedef char rangetype [AD]; // value // char

class mapping {
public:
    void makenull() { m.makenull();}; // delete mapping
    void assign(domaintype d, rangetype r); // make a pair
    int compute(domaintype d, rangetype& r); // update value of r
    void print() const { m.printlist();};
private:
    list m;
};
void mapping::assign(domaintype d, rangetype r) {
    recip temp(d, r);
    position cur = m.locate(temp);
    position fic_x = m.locate(fic);
    if (cur == fic_x)
        m.insert(temp, m.end());
    else
        m.insert(temp, cur);
}
int mapping::compute(domaintype d, rangetype& r) { // returns 1 if there is the searching element and
    recip temp(d, r);
    position fic_x = m.locate(fic);
    position cur = m.locate(temp);  // returns position of checking element
    if (fic_x == cur) // if the pair doesn't exist return 0
        return 0;
    else
        strcpy(r, m.retrieve(cur).adress);
    return 1;
}
}

//using namespace Stack;

using namespace Queue3;
//using namespace List3;

int main() {
     
    
    // for queue's
    queue q;
    recip r("Name1Surname1", "City");
    recip r2("Name2Surname12", "City2");
    recip r1("Name2333Surname1332", "City33332");
   
    q.enqueue(r2);
    cout << q.front() << endl;
    q.enqueue(r);
    cout << q.front() << endl;
    cout << q.dequeue() << endl;
    //q.makenull();
    q.enqueue(r1);
    cout << q.dequeue() << endl;
    cout << q.front() << endl;
    
    /*
    // for Stack
    stck s;
    recip r("Name1Surname1", "City");
    recip r1("Name2Surname12", "City2");
    recip r2("Name2333Surname1332", "City33332");
    // cout << r << endl;
    s.push(r2);
    s.push(r1);
    cout << s.pop() << endl;
    //cout << "ök" << endl;
    s.push(r);
    cout << s.top() << endl;
    //s.push(r);
    cout << s.pop() << endl;
    cout << s.pop() << endl;
    */
    return 0;
}
