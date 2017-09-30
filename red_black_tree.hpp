#include "node.hpp"
using namespace std;

typename<class T>
class red_black_tree {
  private:
    node<T>* root;
    unsigned int size;
  public:
    red_back_tree();

    find(T target);
    insert(T data);
    remove(T data);
}
