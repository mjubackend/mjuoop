#include <iostream>

using namespace std;


class SmartPointer {
  private:
    int* ptr;

  public:
    SmartPointer(int* p) : ptr{p} {}

    ~SmartPointer() {
        delete ptr;
    }

    int& operator*() {
        return *ptr;
    }

    int* operator->() {
        return ptr;
    }

    SmartPointer(const SmartPointer&) = delete;
    SmartPointer& operator=(const SmartPointer&) = delete;

    SmartPointer(SmartPointer&& sp) : ptr{sp.ptr} {
        sp.ptr = nullptr;
    }

    SmartPointer& operator=(SmartPointer&& sp) {
        if (this != &sp) {
            delete ptr;
            ptr = sp.ptr;
            sp.ptr = nullptr;
        }
        return *this;
    }
};


int main() {
    SmartPointer sp(new int(42));

    std::cout << "Value: " << *sp << "\n";

    SmartPointer moved{move(sp)};

    std::cout << "Value2: " << *moved << "\n";

    return 0;
}
