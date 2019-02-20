#include <iostream>
#include <memory>
#include <algorithm>
#include <iterator>

enum class method {left, right};

template <class TK, class TV>
// ! Tree class
class Tree {
    // Node structure
    struct Node {
          std::pair <const TK,TV> data;
          std::unique_ptr<Node> left;
          std::unique_ptr<Node> right;
          Node* parent;

          // ! Constructor
          Node(const TK& key, const TV& value, Node* leftPtr, Node* rightPtr, Node* node) : data{std::make_pair(key,value)}, left{leftPtr}, right{rightPtr}, parent{node} {
            #ifdef debug
            std::cout << "Node custom constructor" << '\n';
            #endif
          }
          // ! Second custom constructor (passing a pair)
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
          ~Node() noexcept{
              #ifdef debug
              std::cout << "Node default destructor" << '\n';
              #endif
            }
          // ! Get data function (not used)
          std::pair<const TK,TV>& get_data() noexcept {return data;}
          // ! Function to set the value associated with a key (not used)
          void set_value(const TV& v) {data.second = v;}
    };

    // ! Define pointer to root node
    std::unique_ptr<Node> root = nullptr;
    // ! Private insert function
    void insert(const TK& key, const TV& value, const std::unique_ptr<Node>& node);
    // ! Private build_tree function
    void build_tree(const std::vector<std::pair<TK,TV>>& vector, std::unique_ptr<Node>& node);
    // ! Copy tree function (copies the tree specified by the node passed)
    void copy_tree(const std::unique_ptr<Node>& node);
    // ! Clear recursive function (clears the subtree specified by the node passed)
    void clear(std::unique_ptr<Node>& node);
    // ! Recursively check if the tree is balanced
    int is_balanced(const std::unique_ptr<Node>& node) const noexcept;

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
    ~Tree() noexcept {
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
    void insert(const TK& key, const TV& value);
    // ! Public insert function (from pair)
    void insert(const std::pair<TK,TV>& p);
    // ! Balance function
    void balance();
    // ! Public clear function
    void clear();
    // ! Remove node specified by key function
    void remove(const TK& key);
    // !  Recursively check if the tree is balanced
    bool is_balanced() const noexcept;
    // ! Modify the value associated with the key
    void modify(const TK& key, const TV& value);
    // ! Check if the tree is empty
    bool is_empty() const noexcept;
    // ! Find function
    Iterator find(const TK& key);
    // ! Find function (start searching from specified node)
    Iterator find(const TK& key, const std::unique_ptr<Node>& node);
    // ! cFind function
    ConstIterator cfind(const TK& key) const;
    // ! cFind function (start searching from specified node)
    ConstIterator cfind(const TK& key, const std::unique_ptr<Node>& node) const;
    // ! Iterate throw items until first or last element
    Node* go(const method m = method::left) const;
    // ! Operator []
    TV& operator[](const TK& k);
    // ! Operator[] const version
    const TV& operator[](const TK& k) const;
    // ! Returns Iterator to first element
    Iterator begin(){
        if(root != nullptr)
            return Iterator{go(method::left)};
        else
            return Iterator{nullptr};
    }
    // ! Returns Iterator to past-the-last element
    Iterator end(){return Iterator{nullptr};}
    // ! Returns Iterator to first element (const version)
    ConstIterator begin() const{
        if(root != nullptr)
            return ConstIterator{go(method::left)};
        else
            return ConstIterator{nullptr};
    }
    // ! Returns Iterator to past-the-last element
    ConstIterator end() const {return ConstIterator{nullptr};}
    // ! Returns ConstIterator to first element
    ConstIterator cbegin() const{
        if(root != nullptr)
            return ConstIterator{go(method::left)};
        else
            return ConstIterator{nullptr};
    }
    // ! Returns ConstIterator to past-the-last element
    ConstIterator cend() const {return ConstIterator{nullptr};}
    // ! Overloading of put to operator
    template <class ot, class op>
    friend std::ostream& operator<<(std::ostream&, const Tree<ot,op>&);
};

// ! Define Iterator
template <class TK, class TV>
class Tree<TK,TV>::Iterator: public std::iterator<std::bidirectional_iterator_tag, std::pair<TK,TV>> {
    using Node = Tree<TK,TV>::Node;
    Node* current;

public:
    // ! Custom constructor
    Iterator(Node* n) : current{n} {}
    Iterator(const Iterator&) = default;
    // ! Access member data operator
    std::pair<const TK,TV>& operator*() const noexcept {return current->data;}
    // ! Access adress data operator
    Node* operator!() const noexcept {return current;}
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
            while((p!=nullptr)&&(p->data.first < current -> data.first)) {
              if(p->parent!=nullptr)
                p = p->parent;
              else{
                p = nullptr;
              }
            }
            current = p;
        }
        return *this;
    }
    // ! Operator -- overloading (not used)
    Iterator& operator--() {
        if(current -> left != nullptr) {
            Node* p;
            p = current->left.get();
            while( p->right != nullptr )
                p = p->right.get();
            current = p;
        }
        else
        {
            Node* p;
            p = current->parent;
            while((p!=nullptr)&&(p->data.first > current -> data.first)) {
              if(p->parent!=nullptr)
                p = p->parent;
              else{
                p = nullptr;
              }
            }
            current = p;
        }
        return *this;
    }
    // ! Comparison operator overloading
    bool operator==(const Iterator& other) {return this->current == other.current;}
    // ! Difference operator overloading
    bool operator!=(const Iterator& other) {return !((*this) == other.current);}
};

// Define ConstIterator class
template <class TK, class TV>
class Tree<TK,TV>::ConstIterator : public Tree<TK,TV>::Iterator {
public:
    using parent = Tree<TK,TV>::Iterator;
    using parent::Iterator;
    const std::pair<const TK,TV>& operator*() const{return parent::operator*();}
    const Node* operator!() const{return parent::operator!();}
};

// ! Body of overloaded put to (<<) operator
template <class TK, class TV>
std::ostream& operator<<(std::ostream& os, const Tree<TK,TV>& l) {
    // ! Check if tree is empty
    if(l.is_empty()) {
        os << "The tree is empty, nothing to print!" << std::endl;
    }
    else {
        class Tree<TK,TV>::ConstIterator it = l.cbegin();
        class Tree<TK,TV>::ConstIterator stop = l.cend();
        for(; it!=stop; ++it)
              os << (*it).first << " " << (*it).second << std::endl;
    }
    return os;
}
