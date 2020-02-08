#include "crypto51_crc.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;
// This code will not compile
// This is for my reference only
long getHash(string& key) {
  CRC32 crc;
  crc.update(key);
  return crc.getValue();
}

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

  void Add(Server& s) {
    for (int i = 0; i < num_of_virtual_nodes; ++i) {
      hashring[stol(s.toString() + std::to_string(i))] = s;
    }
  }
  void Remove(Server& s) {
    for (int i = 0; i < num_of_virtual_nodes; ++i) {
      hashring.erase(hashring.find(stol(s.toString() + std::to_string(i))));
    }
  }
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
