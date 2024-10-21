#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <utility>
#include <vector>


// 직접 구현한 클래스가 없는 동안 아래 예제 코드를 실행 시키기 위해서
// C++ 표준 라이브러리의 vector 를 이용한다.
// 우리는 표준 라이브러리의 vector 중 일부 기능을 구현하는 것이 목표이다.
// 본인이 MyList 를 구현한 뒤에는 아래 줄을 주석 처리한다.
using MyList = std::vector<int>;

// 본인이 MyList 를 구현한 뒤에는 아래 줄을 주석에서 제거한다.
// #include "MyList.h"



////////////////////////////////////////////////////////////////////////
// 이 아래로는 코드를 건드리지 않는다.

using ReferenceVector = std::vector<int>;

const int MAX_INSERTION = 100 * 1000;
const int MAX_DELETION = 30 * 1000;


void selectionSort(MyList &v) {
  int n = v.size();

  for (int i = 0; i < n - 1; ++i) {
    int min_idx = i;

    for (int j = i + 1; j < n; ++j) {
      if (v[j] < v[min_idx]) {
        min_idx = j;
      }
    }

    std::swap(v[i], v[min_idx]);
  }
}


void selectionSort2(ReferenceVector &v) {
  int n = v.size();

  for (int i = 0; i < n - 1; ++i) {
    int min_idx = i;

    for (int j = i + 1; j < n; ++j) {
      if (v[j] < v[min_idx]) {
        min_idx = j;
      }
    }

    std::swap(v[i], v[min_idx]);
  }
}


int main() {
  MyList v;

  // 결과 비교를 위해 표준 라이브러리 vector 를 이용한다.
  ReferenceVector compare;

  srand(time(NULL));

  auto start = std::chrono::system_clock::now();
  for (int i = 0; i < MAX_INSERTION; ++i) {
    // 랜덤한 정수를 집어 넣는다.
    // 직접 구현한 vector 의 결과를 비교하기 위해서 표준 라이브러리의 vector 에 같은 값을 넣는다.
    int n = rand();
    v.push_back(n);
    compare.push_back(n);
  }

  for (int i = 0; i < MAX_DELETION; ++i) {
    // 집어 넣은 것 뒤의 것을 제거한다.
    v.pop_back();
    compare.pop_back();
  }

  if (v.size() != compare.size()) {
    std::cout << "Tried " << MAX_INSERTION << " insertions.\n";
    std::cout << "MyList has " << v.size() << " elements, while Reference Vector has " << compare.size() << "\n";
    return 1;
  }

  selectionSort(v);
  selectionSort2(compare);

  int nMismatched = 0;
  for (int i = 0; i < v.size(); ++i) {
    if (v[i] != compare[i]) {
      ++nMismatched;
    }
  }

  if (nMismatched > 0) {
    std::cout << nMismatched << " elements were wrong.\n";
    return 2;
  }

  auto end = std::chrono::system_clock::now();
  auto duration = end - start;

  std::cout << "Tests were completed. Elapsed " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << " msec\n";
  return 0;
}
