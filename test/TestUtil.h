#include <iostream>
#include "../src/Util.h"

void testUtil() {
  Util util;

  std::cout<<util.convertToTime(909000)<<"\n";
  std::cout<<util.getProgressBar("90");
}