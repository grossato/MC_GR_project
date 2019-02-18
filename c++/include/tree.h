#include <iostream>
#include <memory>
#include <algorithm>

enum class method {left, right};

template <class TK, class TV>
// ! Tree class
class Tree {
    // Node structure
    struct Node {
      private:
          TV value;
          TK key;
          std::pair <TK,TV> data;
      public:

          std::unique_ptr<Node> left;
          std::unique_ptr<Node> right;
          Node* parent;

          // ! Constructor
          Node(TK key, TV value, Node* leftPtr, Node* rightPtr, Node* node) : data{std::make_pair(key,value)}, left{leftPtr}, right{rightPtr}, parent{node} {
            #ifdef debug
            std::cout << "Node custom constructor" << '\n';
            #endif
          }

          // ! Second Node constructor (passing a pair)
          Node(const std::pair<TK,TV>& p): data{p}, left{nullptr}, right{nullptr}, parent{nullptr} {
              #ifdef debug
              std::cout << "Node custom constructor (from pair)" << '\n';
              #endif
          }
          // ! default constructor
          Node() {
              #ifdef debug
              std::cout << "Node default constructor" << '\n';
              #endif
          }
          // ! Destructor
          ~Node() {
              #ifdef debug
              std::cout << "Node default destructor" << '\n';
              #endif
            }

          // ! Get data function
          std::pair<TK,TV>& get_data() {return data;}
          // ! Function to set the value associated with a key
          void set_value(TV v) {value = v;}
    };

    // ! Define pointer to root node
    std::unique_ptr<Node> root = nullptr;
    // ! Private insert function
    void insert(const TK key, const TV value, const std::unique_ptr<Node>& node);
    // ! Private build_tree function
    void build_tree(const std::vector<std::pair<TK,TV>>& vector, std::unique_ptr<Node>& node);
    // ! Copy tree function (copies the tree specified by the node passed)
    void copy_tree(const std::unique_ptr<Node>& node);
    // ! Clear recursive function (clears the subtree specified by the node passed)
    void clear(std::unique_ptr<Node>& node);
    // ! Recursively check if the tree is balanced
    int is_balanced(const std::unique_ptr<Node>& node) const;

public:

    // ! Predeclare the classes Iterator and ConstIterator
    class Iterator;
    class ConstIterator;

    // ! Default tree constructor
    Tree() {
      #ifdef debug
      std::cout << "Tree default constructor" << '\n';
      #endif
    };
    // ! Default tree destructor
    ~Tree() {
      #ifdef debug
      std::cout << "Tree default destructor" << '\n';
      #endif
    };
    // ! Custom Tree constructor (from pair)
    Tree(const std::pair<TK,TV>& p): root{new Node{p}} {
      #ifdef debug
      std::cout << "Tree custom constructor (from pair)" << '\n';
      #endif
    };
    // ! Copy Constructor
    Tree(const Tree & v) {
        #ifdef debug
        std::cout << "Tree copy constructor" << '\n';
        #endif
        copy_tree(v.root);
    }
    // ! Copy assignment operator
    Tree& operator=(const Tree& v) {
        #ifdef debug
        std::cout << "Tree copy assignment" << '\n';
        #endif
        // check if they're not already the same
        if(this != &v)
        {
            // do I need to clear the tree?
            //clear(root);
            //root.reset(nullptr);
            copy_tree(v.root);
        }
        return *this;
    }
    // ! Move Constructor
    Tree(Tree&& v) noexcept :root {std::move(v.root)} {std::cout << "Tree move constructor" << '\n';}
    // ! Move assignment
    Tree& operator=(Tree&& v) noexcept {
      #ifdef debug
        std::cout << "Tree move assignment" << '\n';
      #endif
        root = std::move(v.root);
        return *this;}

    // ! Public insert function
    void insert(const TK key, const TV value);
    // ! Public insert function
    void insert(const std::pair<TK,TV>& p);
    // ! Balance function
    void balance();
    // ! Public clear function
    void clear();
    // ! Remove node function
    void remove(const TK& key);
    // !  Recursively check if the tree is balanced
    bool is_balanced() const;
    // ! Modify the value associated with the key
    void modify(const TK& key, const TV& value);
    // ! Check if the tree is empty
    bool is_empty() const;
    // ! Find function (starts searching from root)
    Iterator find(const TK& key);
    // ! Find function (start searching from specified node)
    Iterator find(const TK& key, const std::unique_ptr<Node>& node);
    // ! cFind function (starts searching from root)
    ConstIterator cfind(const TK& key) const;
    // ! cFind function (start searching from specified node)
    ConstIterator cfind(const TK& key, const std::unique_ptr<Node>& node) const;
    // ! Iterate throw items until first or last element
    Node* go(const method m = method::left) const;
    // ! Operator []
    TV& operator[](const TK& k);
    // ! Operator[] const version
    //const TV& operator[](const TK& k);

    // ! Returns Iterator to first element
    Iterator begin() {
        if(root != nullptr)
            return Iterator{go(method::left)};
        else
            return Iterator{nullptr};
    }
    // ! Returns iterator to root
    Iterator rootIterator() {
        if(root != nullptr)
            return Iterator{root.get()};
        else
            return Iterator{nullptr};
    }
    // ! Returns Iterator to last element
    Iterator end() {
        if(root != nullptr)
            return Iterator{go(method::right)};
        else
            return Iterator{nullptr};
    }
    // ! Returns ConstIterator to first element
    ConstIterator cbegin() const{
        if(root != nullptr)
            return ConstIterator{go(method::left)};
        else
            return ConstIterator{nullptr};
    }
    // ! Returns ConstIterator to last element
    ConstIterator crootIterator() const {
        if(root != nullptr)
            return ConstIterator{root.get()};
        else
            return ConstIterator{nullptr};
    }
    // ! Returns ConstIterator to root
    ConstIterator cend() const {
        if(root != nullptr)
            return ConstIterator{go(method::right)};
        else
            return ConstIterator{nullptr};
    }
    // ! Overloading of put to operator
    template <class ot, class op>
    friend std::ostream& operator<<(std::ostream&, const Tree<ot,op>&);
};

// ! Define Iterator
template <class TK, class TV>
class Tree<TK,TV>::Iterator {
    using Node = Tree<TK,TV>::Node;
    Node* current;

public:
    // ! Custom constructor
    Iterator(Node* n) : current{n} {}
    // ! Access member data operator
    std::pair<TK,TV> operator*() const{
      return current->get_data();
    }
    // ! Access adress data operator
    Node*& operator!() {
        return current;
    }
    // ! Operator ++ overloading
    Iterator& operator++() {
        if(current -> right != nullptr) {
            Node* p;
            p = current->right.get();
            while( p->left != nullptr )
                p = p->left.get();
            current = p;
        }
        else
        {
            Node* p;
            p = current->parent;
            while((p->get_data().first < current -> get_data().first)&&(p->parent!=nullptr)) {
                p = p->parent;
            }
            current = p;
        }
        return *this;
    }
    // ! Operator -- overloading
    Iterator& operator--() {
        if(current -> left != nullptr) {
            Node* p;
            p = current->left.get();
            while( p->right != nullptr )
                p = p->right.get();
            current = p;
        }
        else {
            Node* p;
            p = current->parent;
            while((p->get_data().first > current -> get_data().first)&&(p->parent!=nullptr)) {
                p = p->parent;
            }
            current = p;
        }
        return *this;
    }
    // ! Comparison operator overloading
    bool operator==(const Iterator& other) {
        return this->current == other.current;
    }
    // ! Difference operator overloading
    bool operator!=(const Iterator& other) {
        return !((*this) == other.current);
    }
};

// Define ConstIterator class
template <class TK, class TV>
class Tree<TK,TV>::ConstIterator : public Tree<TK,TV>::Iterator {
public:
    using parent = Tree<TK,TV>::Iterator;
    using parent::Iterator;
    const std::pair<TK,TV> operator*() const{
        return parent::operator*();
    }
};

// ! Body of overloaded put to (<<) operator
template <class TK, class TV>
std::ostream& operator<<(std::ostream& os, const Tree<TK,TV>& l) {
    // ! Check if tree is empty
    if(l.is_empty()) {
        os << "The tree is empty!" << std::endl;
    }
    else {
        auto it = l.cbegin();
        auto stop = l.cend();
        for(; it!=stop; ++it) {
            os << (!it)->get_data().first << " " << (!it)->get_data().second << std::endl;
        }
        os << (!it)->get_data().first << " " << (!it)->get_data().second << std::endl;
    }
    return os;
}
