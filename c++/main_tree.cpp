#include <iostream>
#include <vector>
#include <tree.h>

// constructor test
void constructor_test() {

    std::cout << "--- Testing the constructors and destructors --- " << std::endl;
    std::cout << std::endl;
    {
        std::cout << "-- Test with integers --" << std::endl;
        std::pair<int,int> p{1,1};
        std::cout << std::endl;
        std::cout << "Tree<int,int> tree_int calls:" << std::endl;
        Tree<int,int> tree_int;
        std::cout << std::endl;
        std::cout << "tree_int.insert(p = {1,1});" << std::endl;
        tree_int.insert(p);
        std::cout << std::endl;
        std::cout << "Printing the tree (put to operator) " << std::endl;
        std::cout << tree_int << std::endl;
        std::cout << std::endl;
        std::cout << "Clearing the tree" << std::endl;
        tree_int.clear();
        std::cout << std::endl;
        p = {2,2};
        std::cout << "tree_int.insert(p={2,2})" << std::endl;
        tree_int.insert(p);
        std::cout << "Printing the tree (put to operator) " << std::endl;
        std::cout << tree_int << std::endl;
        std::cout << std::endl;
        std::cout << "Clearing the tree" << std::endl;
        tree_int.clear();
        std::cout << std::endl;
        std::cout << "Printing the tree (put to operator) " << std::endl;
        std::cout << tree_int << std::endl;
        std::vector<int> v{5,6,8,4,1,9,11};
        std::cout << "Inserting v={5,6,8,4,1,9,11} in tree_int" << std::endl;
        for(unsigned int j=0; j< v.size(); j++) {
            p = {v[j], v[j]};
            tree_int.insert(p);
        }
        std::cout << std::endl;
        std::cout << "Printing the tree (put to operator) " << std::endl;
        std::cout << tree_int << std::endl;
        std::cout << std::endl;
        #ifdef debug
        std::cout << "Calling the destructor (out of scope)" << std::endl;
        #endif

    }

    {
        std::cout << std::endl;
        std::cout << "-- Test with chars --" << std::endl;
        std::vector<char> chars{'t','r','h','i','a','c','l','j','n','m','f','b','k','d','o','q','g','e','s','p'};
        std::cout << "Tree<char, double> tree_char calls: " << std::endl;
        Tree<char, double> tree_char;
        std::pair<char,double> p;
        std::cout << std::endl;
        std::cout << "Inserting the alphabet in this order: " << std::endl;
        for(unsigned int i=0; i<chars.size(); i++) {
            std::cout << chars[i] << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
        for(unsigned int i=0; i<chars.size(); i++) {
            p = {chars[i], (double) i};
            tree_char.insert(p);
        }
        std::cout << std::endl;
        std::cout << "Printing the tree (put to operator) " << std::endl;
        std::cout << tree_char << std::endl;
        std::cout << std::endl;
        #ifdef debug
        std::cout << "Calling the destructor (out of scope)" << std::endl;
        #endif

    } // test char

    {
        std::cout << std::endl;
        std::cout << "-- Test with strings --" << std::endl;
        std::cout << "Tree<string, double> tree_string calls: " << std::endl;
        Tree<std::string, std::string> tree_string;
        std::cout << std::endl;
        std::cout << "Inserting:" << "{cause, everything, a, good, i'd,  well, grade, like, hopefully, works}" << std::endl;
        std::vector<std::string> v{"cause", "everything", "a", "good", "i'd",  "well", "grade", "like", "hopefully", "works"};

        std::pair<std::string,std::string> p;
        for(unsigned int i=0; i<v.size(); i++) {
            p = {v[i], " "};
            tree_string.insert(p);
        }
        std::cout << std::endl;
        std::cout << "Printing the tree (put to operator) " << std::endl;
        std::cout << tree_string << std::endl;
        std::cout << std::endl;
        #ifdef debug
        std::cout << "Calling the destructor (out of scope)" << std::endl;
        #endif
    } // test string

} // constructor_test

// copy move test
void copymove_test() {
    std::cout << std::endl;
    std::cout << "--- Testing the copy and move semantics --- " << std::endl;
    std::cout << std::endl;
    std::pair<int,int> p;


    {
        std::cout << "Tree<int,int> tree_int calls: " << std::endl;
        Tree<int,int> tree_int;
        std::cout << "Inserting v={5,6,8,4,1,9,11} in tree_int" << std::endl;
        std::vector<int> v= {5,6,8,4,1,9,11};
        for(unsigned int j=0; j< v.size(); j++) {
            p = {v[j], v[j]};
            tree_int.insert(p);
        }
        std::cout << std::endl;
        std::cout << "Printing the tree (put to operator) " << std::endl;
        std::cout << tree_int << std::endl;
        std::cout<< std::endl;
        std::cout << "-- Copy constructor --" << std::endl;
        std::cout << std::endl;
        std::cout << "Tree<int,int> tree_int2 = tree_int calls" << std::endl;
        Tree<int,int> tree_int2 = tree_int;
        std::cout << std::endl;
        std::cout << "Printing tree_int2 (put to operator) " << std::endl;
        std::cout << tree_int2 << std::endl;
        std::cout << std::endl;
        std::cout << "Clearing the tree " << std::endl;
        tree_int.clear();
        std::cout << std::endl;
        std::cout << "Printing tree_int (put to operator) " << std::endl;
        std::cout << tree_int << std::endl;
        std::cout << std::endl;
        std::cout << "Printing tree_int2 (put to operator) " << std::endl;
        std::cout << tree_int2 << std::endl;
        std::cout << std::endl;

        std::cout << "-- Copy assignment --" << std::endl;
        std::cout << "Tree<int,int> tree_int3;" << std::endl;
        Tree<int,int> tree_int3;
        std::cout << std::endl;
        std::cout << "Inserting v={5,6,8,4,1,9,11} in tree_int" << std::endl;
        for(unsigned int j=0; j< v.size(); j++) {
            p = {v[j], v[j]};
            tree_int.insert(p);
        }
        std::cout << std::endl;
        std::cout << "tree_int3 = tree_int calls: " << std::endl;
        tree_int3 = tree_int;
        std::cout << std::endl;
        std::cout << "Printing tree_int3 (put to operator) " << std::endl;
        std::cout << tree_int3 << std::endl;
        std::cout << "Clearing tree_int: " << std::endl;
        tree_int.clear();
        std::cout << std::endl;
        std::cout << "Printing the tree_int (put to operator) " << std::endl;
        std::cout << tree_int << std::endl;
        std::cout << std::endl;
        std::cout << "Printing the tree_int3 (put to operator) " << std::endl;;
        std::cout << tree_int3 << std::endl;
        #ifdef debug
        std::cout << "Calling the destructor (out of scope)" << std::endl;
        #endif
    }
    std::cout << std::endl;
    std::cout << "-- Move contructor --" << std::endl;
    std::cout << std::endl;
    std::cout << "Tree<int,int> tree_int calls: " << std::endl;
    Tree<int,int> tree_int;
    std::cout << std::endl;
    std::cout << "Inserting v{5,6,8,4,1,9,11} in tree_int:" << std::endl;
    std::vector<int> v{5,6,8,4,1,9,11};
    for(unsigned int j=0; j< v.size(); j++) {
        p = {v[j], v[j]};
        tree_int.insert(p);
    }
    std::cout << std::endl;
    std::cout << "Printing the tree_int (put to operator) " << std::endl;;
    std::cout << tree_int << std::endl;
    std::cout << std::endl;
    std::cout << "Tree<int,int> tree_int4{std::move(tree_int)} calls: " << std::endl;
    Tree<int,int> tree_int4{std::move(tree_int)};
    std::cout << std::endl;
    std::cout << "Printing the tree_int4 (put to operator) " << std::endl;;
    std::cout << tree_int4 << std::endl;
    std::cout << std::endl;
    std::cout << "Clearing tree_int " << std::endl;
    tree_int.clear();
    std::cout << std::endl;
    std::cout << "Printing the tree_int (put to operator) " << std::endl;;
    std::cout << tree_int << std::endl;
    std::cout << "Printing the tree_int4 (put to operator) " << std::endl;;
    std::cout << tree_int4 << std::endl;
    std::cout << std::endl;

    {
        std::cout << "-- Move assignment --" << std::endl;
        std::pair<int,int> p1{2,2};
        std::cout << "Tree<int,int> tree_int2 calls: " << std::endl;
        Tree<int,int> tree_int2;
        std::cout << std::endl;
        std::cout << "Tree<int,int> tree_int2 = Tree<int,int>{p1} calls: " << std::endl;
        tree_int2 = Tree<int,int> {p1};
        std::cout << std::endl;
        std::cout << "Printing the tree_int2 (put to operator) " << std::endl;;
        std::cout << tree_int2 << std::endl;
        std::cout << std::endl;
        #ifdef debug
        std::cout << "Calling the destructor (out of scope)" << std::endl;
        #endif
    }
    std::cout << std::endl;
    #ifdef debug
    std::cout << "Calling the destructor (out of scope)" << std::endl;
    #endif
} // copymove_test


// balance test
void balance_test() {
    std::cout << std::endl;
    std::cout << "--- Balance testing ---" << std::endl;
    std::cout << std::endl;
    {
        std::pair<int,int> p;
        std::cout << "Tree<int,int> tree_int calls: " << std::endl;
        Tree<int,int> tree_int;
        std::cout << std::endl;
        std::cout << "Inserting numbers from 1 to 50 backwards..." << std::endl;
        unsigned int size=50;
        for(unsigned int j=size; j > 0; j--) {
            p = {j, j};
            tree_int.insert(p);
        }
        std::cout << "Is the tree balanced? " << ((tree_int.is_balanced() == 1) ? "Yes" : "No");
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "Balancing tree:"<< std::endl;
        tree_int.balance();
        std::cout << "Is the tree balanced?  " << ((tree_int.is_balanced() == 1) ? "Yes" : "No");
        std::cout << std::endl;
        std::cout << std::endl;
        #ifdef debug
        std::cout << "Calling the destructor (out of scope)" << std::endl;
        #endif
    }
} // balance_test


// find test
void find_test() {
    std::cout << std::endl;
    std::cout << "--- Testing of the find function --- " << std::endl;
    std::cout << std::endl;
    std::pair<int,int> p;
    std::cout << "Tree<int,int> tree_int calls: " << std::endl;
    Tree<int,int> tree_int;
    std::cout << std::endl;
    std::vector<int> v{5,6,8,4,1,9,11};
    std::cout << "Inserting v{5,6,8,4,1,9,11} in tree_int" << std::endl;
    for(unsigned int j=0; j< v.size(); j++) {
        p = {v[j], v[j]};
        tree_int.insert(p);
    }
    std::cout << std::endl;
    std::cout << "Printing the tree_int (put to operator) " << std::endl;
    std::cout<< tree_int << std::endl;
    std::cout << std::endl;
    Tree<int,int>::Iterator it = tree_int.begin(), end = tree_int.end();
    std::cout << "Looking for elements present in the tree:" << std::endl;
    for(unsigned int j=0; j<v.size(); j++) {
        std::cout << "Looking for: " << v[j] << std::endl;
        it = tree_int.find( v[j] );
        if(it == nullptr)
            std::cout << "The tree is empty" << std::endl;
        else if((it != end)||((*it).first ==v[j]))
            std::cout << "Key found! " << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Now looking for an element not present in the tree: 124" << std::endl;
    it = tree_int.find(124);
    std::cout << std::endl;
    std::cout << "Now using the iterator to modify the value associated to the " << std::endl;
    std::cout << "it = tree_int.find(5);" << std::endl;
    it = tree_int.find(9);
    std::cout << "(*it).second = 1000;" << std::endl;
    // here we have to decide what to do
    //(*it).first = 1000;
    tree_int.find(11);
    //tree_int.modify(5,1000);
    // up to here
    std::cout << std::endl;
    std::cout << "Printing the tree_int (put to operator) " << std::endl;
    std::cout << tree_int << std::endl;
    std::cout << std::endl;
    std::cout << "Find a key and eliminate it (key = 6)" << std::endl;
    tree_int.remove(6);
    std::cout << std::endl;
    std::cout << "Printing the tree_int (put to operator) " << std::endl;
    std::cout << tree_int << std::endl;
    std::cout << std::endl;

    std::cout << "-- Testing ConstIterator --" << std::endl;
    Tree<int,int>::ConstIterator itc = tree_int.cbegin(), endc = tree_int.cend();

    std::cout << std::endl;


    for(unsigned int  j=0; j<v.size(); j++) {
        std::cout << "Looking for: " << v[j] << std::endl;
        itc = tree_int.cfind(v[j]);
        if(itc == nullptr)
            std::cout << "The tree is empty" << std::endl;
        else if((itc != endc)||((*itc).first ==v[j]))
            std::cout << "Key found! " << std::endl;

    }

    std::cout << std::endl;
    std::cout << "Now looking for an element not present in the tree: 124" << std::endl;
    itc = tree_int.cfind(124);
    std::cout << std::endl;
    std::cout << "The const iterator cannot modify the second element of the pair" << std::endl;
    std::cout << std::endl;
    std::cout << "itc = tree_int.find(5);" << std::endl;
    itc = tree_int.cfind(5);
    std::cout << "(*itc).second = 1000 would produce compile error " << std::endl;
    //(*itc).first = 1000;
    std::cout << std::endl;
    std::cout << tree_int[13] << std::endl;
    std::cout << tree_int << std::endl;
    #ifdef debug
    std::cout << "Calling the destructor (out of scope)" << std::endl;
    #endif
}// find_test

int main() {

    constructor_test();
    copymove_test();
    balance_test();
    find_test();
    return 0;
}
