#include <tree.h>
#include <iostream>
#include <vector>
#include <sys/time.h>
#include <map>
#include <chrono>

// ! Random generator function
std::vector<int> rand_generator(int size){
  // ! Final vector of random unrepeated values
  std::vector<int> a;
  std::vector<int>::iterator it;
  // Random generator
  std::mt19937 eng{std::random_device{}()};

  // ! set range
  int lower = 0;
  int higher = size*100;

  // ! Generate unrepeated numbers
  for (int i=0; i<size; i++) {
      int q = std::uniform_int_distribution<int> {lower, higher}(eng);
      do {
          q = std::uniform_int_distribution<int> {lower, higher}(eng);
          // ! check if already present
          it = std::find(a.begin(), a.end(), q);
      } while (it != a.end());
      // ! add number if not found
      a.push_back(q);
  }
  return a;
}

// Function to fill the tree
void fill_tree(Tree<int,int>& t, std::vector<int>& v){
      for (size_t i = 0; i < v.size(); i++) {
        // ! add the number to the tree (the value is set to 10)
        t.insert(v.at(i),10);
      }
}

// Function to fill the map
void fill_map(std::map<int, int>& map ,std::vector<int>& v){
      for (size_t i = 0; i < v.size(); i++) {
        // ! add the number to the map (the value is set to 10)
        map.insert(std::pair<int,int>(v.at(i),10));
      }
}

// Functon to calculate the standard deviation
double dev_func(std::vector<double> v, double ave)
{
    double E=0;
    double inverse = 1.0 / static_cast<double>(v.size());
    for(unsigned int i=0;i<v.size();i++)
    {
        E += pow(static_cast<double>(v[i]) - ave, 2);
    }
    return sqrt(inverse * E);
}

// Function to calculate average
double average_func(std::vector<double> v)
{
    double sum = 0;
    for(unsigned int i=0;i<v.size();i++)
    {
        sum+=v.at(i);
    }
    return sum/v.size();
}

int main(int argc, char * argv []){

  double average_tree, average_tree_bal, average_map;
  double dev_tree, dev_tree_bal, dev_map;
  std::vector<double> tree_vec;
  std::vector<double> tree_bal_vec;
  std::vector<double> map_vec;
  unsigned int n_av = 100000;
  int size;

  // ! Enter the size of the tree
   if( argc < 2 ){
    std::cerr<< "No size given. Program exit.\n"<<std::endl;
    exit(EXIT_FAILURE);
    }
  // ! Check size is sound
  size = atoi(argv[1]);
  if( size < 1 ){
    std::cerr<<"Error. Impossible tree size. Program exit.\n"<<std::endl;
    exit(EXIT_FAILURE);
    }

  std::vector<int> random_vect = rand_generator(size);
  
  // ! Define containers
  Tree<int,int> tree;
  std::map<int, int> map;

  // ! Fill the containers
  fill_tree(tree,random_vect);
  fill_map(map, random_vect);

  // ! the key used for searching is the size/2-th of the vector (no particular reason why)
  int key = random_vect.at(size/2);

  // search in the un_balanced tree
  for (size_t i = 0; i < n_av; i++) {
    auto start_tree = std::chrono::high_resolution_clock::now();
    tree.find(key);
    auto end_tree = std::chrono::high_resolution_clock::now();
    tree_vec.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end_tree-start_tree).count());
  }
  average_tree = average_func(tree_vec);
  dev_tree = dev_func(tree_vec,average_tree);

  // search in the balanced tree
  tree.balance();
  for (size_t i = 0; i < n_av; i++) {
    auto start_tree_bal = std::chrono::high_resolution_clock::now();
    tree.find(key);
    auto end_tree_bal = std::chrono::high_resolution_clock::now();
    tree_bal_vec.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end_tree_bal-start_tree_bal).count());
    }
  average_tree_bal = average_func(tree_bal_vec);;
  dev_tree_bal = dev_func(tree_bal_vec,average_tree_bal);


  // search in the map
  for (size_t i = 0; i < n_av; i++) {
    auto start_map = std::chrono::high_resolution_clock::now();
    map.find(key);
    auto end_map = std::chrono::high_resolution_clock::now();

    map_vec.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end_map-start_map).count());
    }
    average_map = average_func(map_vec);
    dev_map = dev_func(map_vec,average_map);

  //std::cout << "The un_balanced tree performs: ";
  std::cout << average_tree << ", " << dev_tree << ", ";
  //std::cout << "The balanced tree performs: ";
  std::cout << average_tree_bal << ", " << dev_tree_bal << ", ";
  //std::cout << "The map performs: ";
  std::cout << average_map << ", " << dev_map << "\n";

  return 0;
}
