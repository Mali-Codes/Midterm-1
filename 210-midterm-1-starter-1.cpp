#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// Heres the doubly linked list class definition
class DoublyLinkedList {
private:    // These are private members not to be accessed directly outside the class
    struct Node { //this is makinga a node structure thats going to hold the data and the pointers to the next and previous nodes
        int data; // this is an integer to hold the data
        Node* prev; //this is a pointer to the pprevious node 
        Node* next; //this is a pointer to the next node 
        Node(int val, Node* p = nullptr, Node* n = nullptr) { //this is a constructor for the node structure so its like the blueprint for new nodes
            data = val; //this is setting the data to the value passed in (int data was declared above))
            prev = p; //Similarly, this is setting the prev pointer to the p pointer passed in (Node* prev was declared above)
            next = n; //Finally this is setting the next pointer to be the n pointer passed in the constructor like the last two
        }
    };

    Node* head;  //this is a pointer to the head (front) of the list
    Node* tail; //this is a pointer to the tail (back) of the list
    //with all these done we can now make the public functions to manipulate the list and do linked list magic

    //public members can be accessed outside the class we will be doing things to the list with this part (setters and getters go here)
public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; } //this is the constructor to set head and tail to null pointers, it's making/initializing an empty list

    // here it starts getting fun, we now get to manipulat the list with these functions

    // this block is the function to insert a new node after giving a position
    void insert_after(int value, int position) {        //it takes in a value to insert after the given position
        if (position < 0) {     // if the position is less than 0 we cant insert it so we return
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value); //this is making a new node with the value passed in
        if (!head) {  //if there isnt the head (first node) then we set head and tail to the new node and return
            head = tail = newNode;
            return;
        }

        Node* temp = head;  // start at the head of the list to find the position
        for (int i = 0; i < position && temp; ++i) //walking through the list to find the position
            temp = temp->next;  //move to the next node

        if (!temp) { // catches if the positon is greater than the size of the list
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode; // clean up memory
            return;
        }

        // Now we insert the new node after the found position
        newNode->next = temp->next;  // new node's next points is to whatever was after temp
        newNode->prev = temp; // new node's prev points back to temp
        if (temp->next)   //if there's a node after temp (we're not at the end)  
            temp->next->prev = newNode;  //update that node's prev to point back to the new node
        else // if we are at the end of the list
            tail = newNode; // update tail to be the new node
        temp->next = newNode; // finally connect temp to the new node
    }

    void delete_val(int value) {  //this function deletes the first node with the given value
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    void every_other_method() {
        Node* current = head;
        int index = 0; //start at 0
        // skip every other node
        // using theh print function as inspiration

        // modulo for even checking
        // use conditional if for odd
        while (current) {

            if (index %1 == 0) {
                
                cout << current->data << " ";
                current = current->next; // move to the next node
                index ++; // increment index
            }
        }
        cout << endl;

    };
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS << "\n";  // dummy statement to avoid compiler warning

    DoublyLinkedList list;
    
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);
    list.push_back(50);

    cout << "++++ Original List ++++" << endl;
    list.print();

    cout << "++++ Every other element ++++:" << endl;
    list.every_other_method();
    
    return 0;
}