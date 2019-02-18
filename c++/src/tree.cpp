#include <iostream>
#include <vector>
#include <tree.h>

// ! Public insert function
template <class TK, class TV>
void Tree<TK,TV>::insert(const TK key, const TV value) {
    if(root!=nullptr) {
        // If the root is not empty insert the pair
        insert(key, value, root);
    }
    else {
        // If the tree is empty create a root node
        root.reset(new Node{key, value, nullptr,nullptr,nullptr});
    }
}

// ! Public insert function from pair (might be useful)
template <class TK, class TV>
void Tree<TK,TV>::insert(const std::pair<TK,TV>& p) {
    insert(p.first,p.second);
}

// ! Private insert function
template <class TK, class TV>
void Tree<TK,TV>::insert(const TK key, const TV value, const std::unique_ptr<Node>& node) {
    // ! Go left if key is smaller
    if(key <= node -> get_data().first) {
        // Check nullity of pointer
        if (node -> left != nullptr) {
            insert(key, value, node->left);
        }
        else {
            // ! Create a new node
            node->left.reset(new Node{key, value, nullptr,nullptr,node.get()});
        }
    }
    else if(node->right!=nullptr) {
        // Subdivide the problem
        insert(key,value, node->right);
    }
    else{
      // ! Create a new node
      node->right.reset(new Node{key, value, nullptr,nullptr,node.get()});}
}

// ! Function that allows to modify the value associated with the key with a new value passed as attribute
template <class TK, class TV>
void Tree<TK,TV>::modify(const TK& key, const TV& value) {
    // Find the key
    ConstIterator it = cfind(key);
    ConstIterator end = this->cend();
    if((it==end)&&((*it).first != (*end).first))
        std::cout << "Key not present, impossible to modify" << std::endl;
    else {
        (!it)->set_value(value);
    }
}

// Function to remove a node given its key
template <class TK, class TV>
void Tree<TK,TV>::remove(const TK& key) {

    Node* node = root.get();
    // Loop until found (iteratively)
    while (node->get_data().first != key) {
        // Go left
        if(key<node->get_data().first) {
            node = node->left.get();
        }
        // or go right
        else if(key>node->get_data().first) {
            node = node->right.get();
        }
        else{
            // In case the key is not found
            break;}
    }
    // If found

    if(node->get_data().first == key) {
        std::unique_ptr<Node> left_branch{(node)->left.release()};
        std::unique_ptr<Node> right_branch{(node)->right.release()};
        if(node != root.get()) {
            if((node->parent->left!= nullptr)&&(node->parent->left->get_data().first == key)) {
                // Remove the node
                node->parent->left.reset();
            }
            else {
                // Remove the node
                node->parent->right.reset();
            }
        }
        else {
            // If got here it means that the node to be removed is the root node
            root.reset();
        }
        // Insert the branches
        copy_tree(left_branch);
        copy_tree(right_branch);
    }
    else {
        std::cout << "Key not found, impossibile to eliminate" << std::endl;
    }

}

// ! Private copy function
template <class TK, class TV>
void Tree<TK,TV>::copy_tree(const std::unique_ptr<Node> &node) {
    if(node != nullptr)
    {
        insert(node->get_data().first,node->get_data().second);
        copy_tree(node->left);
        copy_tree(node->right);
    }
}

// ! Public function to check if the tree is balanced
template <class TK, class TV>
bool Tree<TK,TV>::is_balanced() const{
  if(root!=nullptr)
    return (is_balanced(root)>-1);
  else{
    std::cout << "The tree is empty! Hence balanced" << std::endl;
    return true;
    }
  }

// ! Recursive function to check if each subtree specified by the node is balanced
template <class TK, class TV>
int Tree<TK,TV>::is_balanced(const std::unique_ptr<Node> & node) const{
 /*
  if the tree is balanced, return the height of the tree
  if the tree is not balanced, return -1
*/

  // Do not consider (return 0) if the algorithm arrived to a leaf
  if (node == nullptr)
      return 0;

  int left_height = is_balanced(node->left);
  // The tree is not balanced because the branches are not balanced
  if (left_height == -1)
      return -1;

  int right_height = is_balanced(node->right);
  // The tree is not balanced because the branches are not balanced
  if (right_height == -1)
      return -1;

  // The tree is not balanced (from definition)
  if (abs(left_height - right_height) > 1)
      return -1;
  // If got here then the tree is balanced, hence return its height (+1 is due to the subroot node)
  return ((left_height>right_height ? left_height : right_height) +1);
  }

// ! Public balance function
template <class TK, class TV>
void Tree<TK,TV>::balance() {

    // Need iterator to first and end nodes
    ConstIterator it = this->cbegin();
    ConstIterator stop = this ->cend();
    std::vector<std::pair<TK,TV>> data;
    // ! Collect all the data in a sorted fashion
    data.push_back(*it);
    do {
        ++it;
        data.push_back(*it);
    } while(it!=stop);
    // Build the tree based on the data just collected
    clear(root);
    build_tree(data, root) ;
}

// ! Function to build a tree given a vector of data and a starting node
template <class TK, class TV>
void Tree<TK,TV>::build_tree(const std::vector<std::pair<TK,TV>>& vector, std::unique_ptr<Node>& node) {

    // Index of element in the middle of the vector
    unsigned int midroot = std::distance(vector.begin(), vector.begin() + vector.size() / 2);

    // Check if root node exists (executes only once)
    if(node==nullptr) {
        node.reset(new Node{vector.at(midroot).first, vector.at(midroot).second, nullptr,nullptr,nullptr});
    }

    // ! Split the data in two vectors
    std::vector<std::pair<TK,TV>> left(vector.begin(), vector.begin()+midroot);
    std::vector<std::pair<TK,TV>> right(vector.begin()+midroot+1, vector.end());

    // Index of element in the middle of the left and right vector
    unsigned int midleft = std::distance(left.begin(), left.begin() + left.size() / 2);
    unsigned int midright = std::distance(right.begin(), right.begin() + right.size() / 2);

    // Much code duplication, there's probably a better implementation
    // Case in which the vector is non-empty
    if(left.size() > 1)
    {
        node -> left.reset(new Node{left.at(midleft).first, left.at(midleft).second, nullptr,nullptr,node.get()});
        build_tree(left, node->left);
    }
    // Case in which the vector has one element
    else if(left.size() > 0) {
        node -> left.reset(new Node{left.at(midleft).first, left.at(midleft).second, nullptr,nullptr,node.get()});
    }
    // Case in which the vector is non-empty
    if(right.size() > 1)
    {
        node -> right.reset(new Node{right.at(midright).first, right.at(midright).second, nullptr,nullptr,node.get()});
        build_tree(right, node->right);
    }
    // Case in which the vector has one element
    else if(right.size() > 0) {
        node -> right.reset(new Node{right.at(midright).first, right.at(midright).second, nullptr,nullptr,node.get()});
    }
}
// ! Function to clear a tree
template <class TK, class TV>
void Tree<TK,TV>::clear() {
    if(root!=nullptr)
        clear(root);
    else
        std::cout << "The tree is empty!" << std::endl;
}

// ! Private recursive clear function
template <class TK, class TV>
void Tree<TK,TV>::clear(std::unique_ptr<Node>& node) {

    if(node->left!=nullptr)
        clear(node->left);
    if(node->right!=nullptr)
        clear(node->right);
    // When the algorithm got to the leaf
    if((node->left==nullptr)&&(node->right==nullptr)) {
        #ifdef debug
        std::cout << "Being eliminated: " << node->get_data().first << '\n';
        #endif
        node.reset();
    }
}

// ! is_empty function
template <class TK, class TV>
bool Tree<TK,TV>::is_empty() const {
    if(root!=nullptr)
        return false;
    else
        return true;
}

// ! Find function
template <class TK, class TV>
class Tree<TK,TV>::Iterator Tree<TK,TV>::find(const TK& key){
    if(root == nullptr) {
        return Iterator{nullptr};
    }
    else {
        if(key == root->get_data().first)
            return Iterator{root.get()};
        else {
            return this->find(key, root);
        }
    }
}

template <class TK, class TV>
class Tree<TK,TV>::Iterator Tree<TK,TV>::find(const TK& key, const std::unique_ptr<Node>& node){
    static Iterator toReturn = Iterator{(*this).end()};
    // If the value is found, return an iterator to the node
    if(key == node->get_data().first) {
        //return Iterator{node.get()};
        toReturn = Iterator{node.get()};
    }
    // Look for the node
    else
     if(key < node-> get_data().first) {
        if (node->left != nullptr)
            // Going left
            find(key, node->left);
        else {
            std::cout << "Key not found, returning end()\n";
            //return Iterator{(*this).cend()};
            toReturn = Iterator{(*this).end()};
        }
    } else {
        if (node->right != nullptr)
            // Or going right
            find(key, node->right);
        else {
            std::cout << "Key not found, returning end()\n";
            //return Iterator{(*this).cend()};
            toReturn = Iterator{(*this).end()};
        }
    }
  return toReturn;
}

// Private cfind function
template <class TK, class TV>
class Tree<TK,TV>::ConstIterator Tree<TK,TV>::cfind(const TK& key) const {
    if(root == nullptr) {
        return ConstIterator{nullptr};
    }
    else {
        if(key == root->get_data().first)
            return ConstIterator{root.get()};
        else {
            return cfind(key, root);
        }
    }
}

// Recursive cfind function
template <class TK, class TV>
class Tree<TK,TV>::ConstIterator Tree<TK,TV>::cfind(const TK& key, const std::unique_ptr<Node>& node) const {
    static ConstIterator toReturn = ConstIterator{(*this).cend()};
    // If the value is found, return an iterator to the node
    if(key == node->get_data().first) {
        toReturn = ConstIterator{node.get()};
    }
    // Look for the node
    else if(key < node-> get_data().first) {
        if (node->left != nullptr)
            // Going left
            cfind(key, node->left);
        else {
            std::cout << "Key not found, returning end()\n";
            toReturn = ConstIterator{(*this).cend()};
        }
    } else {
        if (node->right != nullptr)
            // Or going right
            cfind(key, node->right);
        else {
            std::cout << "Key not found, returning end()\n";
            toReturn = ConstIterator{(*this).cend()};
        }
    }
    return toReturn;
}

// Iterate to the left or to the right depending on method
template <class TK, class TV>
class Tree<TK,TV>::Node* Tree<TK,TV>::go(const method m) const {

    Node* p;
    p = root.get();

    // Do according to case
    switch (m) {
    case method::left:
        while(p->left != nullptr) {
            p = p->left.get();
        }
        break;
    case method::right:
        while(p->right != nullptr) {
            p = p->right.get();
        }
        break;
    default:
        throw std::runtime_error{"unknown method\n"};
    };

    // Return pointer to node
    return p;
}

template <class TK, class TV>
TV& Tree<TK,TV>::operator[](const TK& k) {
  Iterator itc = this->find(k);
  Iterator endc = end();
  if((itc==endc)&&((!itc)->get_data().first != k)){
    insert(k,0);
    itc = this->find(k);
  }
  return (!itc)->get_data().second;

}
//TOBEASKEED!
/*
template <class TK, class TV>
const TV& Tree<TK,TV>::operator[](const TK& k){
  ConstIterator itc = this->cfind(k);
  ConstIterator endc = cend();
  if((itc==endc)&&((!itc)->get_data().first != k)){
    insert(k,0);
    itc = this->cfind(k);
  }
  return (!itc)->get_data().second;
}
*/

// Explicit templates
template class Tree<int,int>;
template class Tree<int,double>;
template class Tree<double,double>;
template class Tree<std::string, std::string>;
template class Tree<std::string, int>;
template class Tree<char, double>;
