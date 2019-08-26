#include <iostream>
#include <string>
#include <vector>
#include "../src/ProcessContainer.h"

using std::cout;
using std::string;
using std::vector;

void testProcessContainer() {
  ProcessContainer processContainer;
  cout<<processContainer.printList()<<"\n->\n";
  for(string item : processContainer.getList()) {
    cout<<"item: "<<item<<"\n";
  }
}