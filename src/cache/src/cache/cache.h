#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <map>
#include <queue>

#define PORT 2020 

using namespace std;

map<string, string> cacheMap;  
queue<string> cacheQueue;      

struct CacheEntry {
    string query;
    string response;
};

void iniciarCache(int memory_size);

#endifs
