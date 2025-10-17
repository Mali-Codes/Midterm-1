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
        if (!head) return; // if the list is empty we return

        Node* temp = head; // start at the head to find the value
        
        while (temp && temp->data != value) // walk through the list until we find the value or reach the end
            temp = temp->next;

        if (!temp) return;     // if we reached the end without finding the value, we return

        if (temp->prev)         // if there's a node before temp   
            temp->prev->next = temp->next; // update that node's next to skip temp
        else 
            head = temp->next;  // move the head ot the next node

        if (temp->next)
            temp->next->prev = temp->prev;  // if theres a node after temp update its prev to skip temp
        else // if temp is the tail
            tail = temp->prev;  //move tail back to the previous node

        delete temp;
    }

    // this function deletes a node at a specific position
    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;  // if the list is empty we return
            return;
        }
    
        if (pos == 1) { // if the position is 1 we pop the front with the pop front function       
            pop_front();
            return;
        }
    
        Node* temp = head;  // start at the head to find the position
    
        for (int i = 1; i < pos; i++){ // walk through the list to the position  
            if (!temp) {  // [going blockl by block for time] this one is if we reach the end before the position we return
                cout << "Position doesn't exist." << endl;   
                return;
            }
            else // move to the next node
                temp = temp->next;
        }
        if (!temp) { // if we reach the end without finding the position we return again
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) { // if we're at the end we pop the back with the pop back function
            pop_back();
            return;
        }
    // now were deleting a node that isnt the head or tail
        Node* tempPrev = temp->prev;  // save a pointer to the node before temp
        tempPrev->next = temp->next; // connect previous nothe to the next node
        temp->next->prev = tempPrev; // connect the next node back to the previous node
        delete temp;
    }

    void push_back(int v) { // this function adds a new node to the back of the list
        Node* newNode = new Node(v); // make a new node with the value passed in during the "call"
        if (!tail)
            head = tail = newNode; // if the list is empty set head and tail to the new node
        else { // add the new node to the end and connect the tail to the new node and set the new node's prev to the old tail
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode; //finally make the new node the new tail
        }
    }
    
    void push_front(int v) { // this function adds a new node to the front of the list
        Node* newNode = new Node(v); //makes a new node with the value passed in during the "call" like in above function
        if (!head) // if the list is empty set head and tail to the new node
            head = tail = newNode;
        else { // add the new node to the front and connect the head to the new node and set the new node's next to the old head
            newNode->next = head; //like the above function but reversed
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() { // this function removes the node at the front of the list

        if (!head) {
            cout << "List is empty." << endl; // if the list is empty we return
            return;
        }

        Node * temp = head; // save a pointer to the current head to delete later

        if (head->next) { // this block is if there is more than one node in the list move
            head = head->next; //the head to the next node and disconnect the old head
            head->prev = nullptr;
        }
        else
            head = tail = nullptr; // if there was only one node set head and tail to null pointers 
        delete temp; //free the memory of the old head
    }

    void pop_back() { // this function removes the node at the back of the list
        if (!tail) {
            cout << "List is empty." << endl; // if the list is empty we return
            return;
        }
        Node * temp = tail; // save a pointer to the current tail to delete later

        if (tail->prev) { // if there is more than one node in the list move 
            tail = tail->prev; //the tail to the previous node and disconnect the old tail
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;  // this block is the destructor to free all memory when the list goes out of scope
            head = head->next;
            delete temp;
        }
    }
    void print() { //this whole block is just to print the list from head to tail going front to back by nodes
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

    void print_reverse() { //this whole block is just to print the list from tail to head going back to front by nodes
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
        int index = 1; //start at 1 to print the first element
        // skip every other node
        // using theh print function as inspiration

        // modulo for even checking
        // use conditional if for odd
        while (current) {

            if (index % 2 == 1) {
                
                cout << current->data << " ";
                
            }
            current = current->next; // move to the next node
            index ++; // increment index
        }
        cout << endl;

    }
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