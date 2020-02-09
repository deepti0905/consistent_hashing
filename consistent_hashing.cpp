#include "crypto51_crc.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;
// This code will not compile
// This is for my reference only
long getHash(string& key) {
  string command="crc32 "+key+" >  output";
  system(command);
  //Read output file and capture in a long value
  long value;
  return value;
}

//Class to signify a server
class Server {
 public:
  Server(){
  } 
  Server(string& ip) { ipAddress = ip; }
  string toString() { return ipAddress; }

 private:
  string ipAddress;
};

class ConsistentHashing {
 public:
  map<long, Server> hashring;
  int num_of_virtual_nodes;
  ConsistentHashing(){
  }

  // We would need to set the number of virtual servers allowed per server
  void Add(Server& s) {
    for (int i = 0; i < num_of_virtual_nodes; ++i) {
      hashring[stol(s.toString() + std::to_string(i))] = s;
    }
  }
  //Remove a server from the hashring, this will remove virtual nodes as well
  void Remove(Server& s) {
    for (int i = 0; i < num_of_virtual_nodes; ++i) {
      hashring.erase(hashring.find(stol(s.toString() + std::to_string(i))));
    }
  }
  //Try to find if the key fits directly to any server, if not we find the lower bound
  // point just greater than the concerned key
  // if we end up not finding, move to the begining of the loop
  Server get(string& key) {
    long hashPos = getHash(key);
    if (hashring.find(hashPos) == hashring.end()) {
      map<long, Server>::iterator iter = hashring.lower_bound(hashPos);
      hashPos = iter == hashring.end() ? hashring.begin()->first : iter->first;
    }
    return hashring[hashPos];
  }
};
int main(int argc, char** argv) { return 0; }
