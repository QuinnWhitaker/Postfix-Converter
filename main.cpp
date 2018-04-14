#include <iostream>
#include <fstream>

using namespace std;

template <typename T> /// This Stack class store values in the template. Values can be pushed onto it using Push and popped off of it with Pop.
class Stack {
private:
    struct node { /// Nodes store two things, data, and whatever node is below it on the stack.
    node* below;
    T data;
    };

    node * top; /// What's currently at the top of the stack.
    int s; /// The current size of the stack.

public:
    Stack() { /// Constructor
        /// Pre: Stack is not initialized.
        /// Post: Stack is initialized, with the top being set to a null ptr and the size of the stack being 0.
        top = nullptr;
        s = 0;
    }

    ~Stack() { /// Destructor
        /// Pre: Stack is still allocated to memory.
        /// Post: All members of stack have been deallocated.

        /// Two temporary nodes are made to search the stack
        node *t1 = new node;
        node *t2 = new node;

        while(top != nullptr) {
            t1 = top;
            t2 = top->below;
            top = t2;
            delete t1;
        }
        delete t1;
        delete t2;
    }


    bool isEmpty() {
        /// Post: returns whether the stack has any nodes.
        return (s == 0);
    }

    int getSize() {
        /// Post: returns the size of the stack.
        return s;
    }

    T getTop() {
        /// Post: returns the value of the node on top of the stack.
        return top->data;
    }

    void Push(T data) {
        /// Pre: Data is given and not yet pushed onto the stack.
        /// Post: Data is inserted into a node, and the new node is added to the stack,
        /// adjusting size accordingly and setting it to the top node.
        node* newNode = new node;
        newNode->data = data;
        newNode->below = top;
        top = newNode;
        s++;
    }

    void PopVal() {
        /// Pre: All items are still on the stack.
        /// Post: The node on the top of the stack is removed from it. The size is decreased, and the top of the stack is changed to the next node.
        /// (This function does not return the data that was popped. See next function, Pop())
        if (s > 0) { /// If the stack contains any data, create a temporary node, set it to the top, set top to the value below it,
                /// then delete the temp node, and decrement the size of the stack.

            node *temp = new node;
            temp = top;
            top = top->below;
            delete temp;
            s--;
        }

    }

    T Pop() {
        /// Pre: All items are still on the stack.
        /// Post: The node on the top of the stack is removed from it. The size is decreased, the top of the stack is changed the the next node,
        /// and the removed node's data is returned in the function.
        T ret = top->data; /// To eventually be the return value.
        PopVal(); /// The top of the stack is popped and set to the next node.
        return ret; /// The data from the inital top of the stack is returned.
    }


};

bool isOperand(char c) {
    /// Pre: Takes a single character
    /// Post: Returns true if the character is alphabetical (A-Z), otherwise false

    const int a = 26; /// Alphabet size
    char alph[a] = {'A', 'B',
                    'C', 'D',
                    'E', 'F',
                    'G', 'H',
                    'I', 'J',
                    'K', 'L',
                    'M', 'N',
                    'O', 'P',
                    'Q', 'R',
                    'S', 'T',
                    'U', 'V',
                    'W', 'X',
                    'Y', 'Z',};

    for (int i = 0; i < a; i++) {
        if (c == alph[i]) return true; /// If a match is found throughout the alphabet, return true immediately.
    }
    return false; /// When the whole alphabet has been scanned and there was no match, return false.
}

bool isOperator(char c) {
    /// Pre: Takes a single character
    /// Post: Returns true if the character is one of these characters: +, -, *, or /, otherwise false

    const int u = 4; /// Number of different operator symbols
    char lib[u] = {'+', '-', '*', '/'};
    for (int i = 0; i < u; i++) {
        if (c == lib[i]) return true; /// If a match is found in the library of operators immediately return true.
    }
    return false; /// Otherwise return false;
}

int OperatorValue(char c) {
    /// Pre: Given a character, specifically an operand.
    /// Post: Returns the precedence value of the given char.
    if (c == '+' || c == '-') return 0;
    else if (c == '*' || c == '/') return 1;
    else if (c == '(') return 2; /// The left parenthesis has a higher precedence than all other operators.
}

bool isLessThan(char Op1, char Op2) {
    /// Pre: Given two operator characters.
    /// Post: returns true if the first operator is of lower precedence than the second operator. Otherwise false.
    int val1; /// Integer values are made to have comparative values for precedence.
    int val2;


    /// Each character is assigned a precedence value.
    val1 = OperatorValue(Op1);
    val2 = OperatorValue(Op2);

    /// Returns whether the first value is less than the second.
    return (val1 < val2);

}

int main()
{
    ifstream file("data.txt"); /// Reads the file "data.txt"

    char scan; /// To be changed to whichever is the currently scanned character.

    Stack<char> st; /// The stack, as depicted by a linked list.

    string psfx = "Postfix: "; /// Postfix string, to be printed each line.
    string infx = "Infix: "; /// Infix string

    while (file.get(scan)) { /// While there are still characters to scan in the file.
        if (isOperand(scan) || isOperator(scan) || scan == '(' || scan == ')' || scan == ';' || scan == '.') {
            infx += scan;
            infx += ' ';
        }

        if (isOperand(scan)) {
            psfx += scan;
            psfx += ' '; /// If the scanned character is an operand, write it to the postfix string.
        }
        else if (isOperator(scan)) { /// If the scanned character is an operator, do the following
            while (!st.isEmpty()) { /// While there are still objects on the stack,
                if (st.getTop() == '(' || isLessThan(st.getTop(), scan)) break; /// stop the process if the next character on the stack is a '('
                                                                                /// or if the next character on the stack has lower precedence
                                                                                /// than the currently scanned character.
                char c = st.Pop(); /// Pop the top of the stack, and repeat.
                psfx += c;
                psfx += ' ';
            }
            st.Push(scan); /// Regardless of if the above process occurred, push the scanned character onto the stack.
        }
        else if (scan == '(') st.Push(scan); /// if the character is a '(' push it onto the stack.
        else if (scan == ')') { /// if the character is a ')', then continuously pop the stack until the last popped character was a '('
                                /// or the stack is empty.
            while (!st.isEmpty()) {
                char c = st.Pop();
                if (c == '(') break;
                else {
                    psfx += c;
                    psfx += ' ';
                }
            }
        }
        else if (scan == ';' || scan == '.') { /// If the scanned character is a ';' then pop the rest of the stack and end the line.
            while (!st.isEmpty()) {
                char c = st.Pop();
                psfx += c;
                psfx += ' ';
            }
            cout << infx << endl;
            cout << endl;
            cout << psfx << endl;
            cout << endl;
            infx = "Infix: ";
            psfx = "Postfix: ";
            if (scan == '.') break;
        }
    }
    file.close();

}
