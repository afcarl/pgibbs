#ifndef CORPUS_BASE_H__
#define CORPUS_BASE_H__

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "definitions.h"
#include "gng/symbol-set.h"

// TODO: fix
using namespace std;
using namespace gng;

// T is the representation of a single sentence
template < class Sent >
class CorpusBase : public vector< Sent > {

protected:
    SymbolSet<string,int> ids_; // a mapping from words to IDs

public:
    string getSymbol(int id) { return ids_.getSymbol(id); }

};

#endif