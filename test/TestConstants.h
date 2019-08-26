#include <iostream>
#include <cstdlib>
#include "../src/Constants.h"

using namespace std;

void testConstants() {
  int option = -1;
  while(option != 0) {
    cout<<"\n/proc system info:\n";
    cout<<"------------------\n";
    cout<<"\t0- exit\n";
    cout<<"\t1- base\n";
    cout<<"\t2- cmd\n";
    cout<<"\t3- status\n";
    cout<<"\t4- stat\n";
    cout<<"\t5- uptime\n";
    cout<<"\t6- meminfo\n";
    cout<<"\t7- version\n";
    std::cout<<"Pick an option: ";
    std::cin>>option;
    
    switch (option)
    {
      case 0:
        exit(0);
        break;
      case 1:
        cout<<"\n/proc:\n";
        std::system(("ls " + Path::basePath()).c_str());
        break;
      case 2:
        cout<<"\n/cmdline:\n";
        std::system(("cat " + Path::basePath() + Path::cmdPath()).c_str());
        break;
      case 3:
        cout<<"\n/status:\n";
        std::system(("cat " + Path::basePath() + Path::statusPath()).c_str());
        break;
      case 4:
        cout<<"\nstat:\n";
        std::system(("cat " + Path::basePath() + Path::statPath()).c_str());
        break;
      case 5:
        cout<<"\nuptime:\n";
        std::system(("cat " + Path::basePath() + Path::upTimePath()).c_str());
        break;
      case 6:
        cout<<"\nmeminfo:\n";
        std::system(("cat " + Path::basePath() + Path::memInfoPath()).c_str());
        break;
      case 7:
        cout<<"\nversion:\n";
        std::system(("cat " + Path::basePath() + Path::versionPath()).c_str());
        break;

      default:
        break;
    }
  }
}