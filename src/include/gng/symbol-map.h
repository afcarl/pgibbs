#ifndef GNG_SYMBOL_MAP_H__
#define GNG_SYMBOL_MAP_H__

#include "string.h"
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <iostream>

namespace gng {

template < class Key, class T, class Hash = std::hash<Key> >
class SymbolMap : public std::unordered_map< Key, T, Hash > {

protected:

    std::vector<T> nextKeys_;

public:
    SymbolMap() : std::unordered_map<Key,T,Hash>() { }

    T getId(const Key & sym, bool add = false) {
        typename SymbolMap<Key,T,Hash>::const_iterator it = this->find(sym);
        if(it != this->end())
            return it->second;
        else if(add) {
            T id;
            if(nextKeys_.size()) { 
                id = nextKeys_[nextKeys_.size()-1];
                nextKeys_.pop_back();
            }
            else
                id = this->size();
            insert(std::pair<Key,T>(sym,id));
            return id;
        }
        return -1;
    }
    
    void removeElements(const std::vector<T> & vec) {
        std::unordered_set<T> mySet;
        for(typename std::vector<T>::const_iterator it = vec.begin(); it != vec.end(); it++)
            mySet.insert(*it);
        std::vector<Key> removeKeys; removeKeys.reserve(vec.size());
        for(typename SymbolMap<Key,T,Hash>::const_iterator it = this->begin(); it != this->end(); it++) {
            if(mySet.find(it->second) != mySet.end()) {
                mySet.erase(it->second);
                removeKeys.push_back(it->first);
                nextKeys_.push_back(it->second);
            }
        }
        if(mySet.size())
            throw std::runtime_error("SymbolMap::removeElements attempted to remove non-existant symbol");
        for(int i = 0; i < (int)removeKeys.size(); i++)
            erase(removeKeys[i]);
    }

};

}

#endif
