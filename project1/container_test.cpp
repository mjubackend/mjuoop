#include <iostream>

#include "MyContainer.h"
#include "MyVector.h"
#include "MyList.h"

using namespace std;

void updateVectorElement(MyContainer &c, int update) {
  MyVector &v = dynamic_cast<MyVector &>(c);
  v[0] = update;
  cout << v[0] << "\n";
}

void updateListElement(MyContainer &c, int update) {
  MyList &l = dynamic_cast<MyList &>(c);
  l.back() = update;
  cout << l.back() << "\n";
}

int main() {
  MyContainer *v = MyContainer::Create(MyContainer::VECTOR);

  v->push_back(10);
  cout << v->size() << "\n";
  updateListElement(*v, 30);
  updateVectorElement(*v, 20);
  v->pop_back();

  MyContainer *l = MyContainer::Create(MyContainer::LIST);
  l->push_back(10);
  cout << l->size() << "\n";
  updateVectorElement(*l, 20);
  updateListElement(*l, 30);
  l->pop_back();
}
