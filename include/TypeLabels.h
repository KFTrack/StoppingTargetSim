// Ed Callaghan
// Forward mapping from typenames to string labels
// This is the mechanism upon which ``type-iteration'' rests, hacky as it is

#ifndef TYPELABELS_H
#define TYPELABELS_H

#include <TTree.h>
#include <string>

std::string GetTypeCode(std::string label);

template<typename T>
std::string GetTypeLabel();

#endif
