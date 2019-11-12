#include "Tmsg.h"
#include <iostream>

using namespace std;

int main() {
  for (int i = 0; i < 10; i++) {
    cout << i;
  }
  Tmsg m;
  m.message_term();
  return 0;
}
