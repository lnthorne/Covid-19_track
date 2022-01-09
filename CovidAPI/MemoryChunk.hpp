//
//  MemoryChunk.hpp
//  CovidAPI
//
//  Created by Liam Thorne on 2022-01-06.
//

#ifndef MemoryChunk_h
#define MemoryChunk_h
#include <json.h>

class chunk {
public:
//    deafult constructor
    chunk() {
        _memory = NULL;
        _size = 0;
    }
    
//    constructor that takes itself as a param
    chunk(chunk* newChunk) {
        _memory = (*newChunk)._memory;
        _size = (*newChunk)._size;
    }
    
    ~chunk() {
        free(_memory);
    }
    
//    returns size of mem chunk
    size_t Size() {
        return _size;
    }
    
//    return mem itself
    char* Mem() {
        return _memory;
    }
    
//    Assigns memory to data
    void setNem(char* data) {
        _memory = data;
    }
    
//    Reassigns the size of the data
    void setSIze(size_t newSize) {
        _size += newSize;
    }
private:
    size_t _size;
    char *_memory;
};

#endif /* MemoryChunk_h */
