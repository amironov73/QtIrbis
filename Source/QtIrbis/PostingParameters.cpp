// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

PostingParameters::PostingParameters()
    : listOfTerms(), database(), format(), term(), firstPosting(1),
      numberOfPostings(0) {
}
