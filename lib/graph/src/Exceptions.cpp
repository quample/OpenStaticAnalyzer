/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
 *
 *  Licensed under Version 1.2 of the EUPL (the "Licence");
 *
 *  You may not use this work except in compliance with the Licence.
 *
 *  You may obtain a copy of the Licence in the LICENSE file or at:
 *
 *  https://joinup.ec.europa.eu/software/page/eupl
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the Licence for the specific language governing permissions and
 *  limitations under the Licence.
 */

#include "../inc/graph.h"
#include <string>

using namespace std;

namespace columbus {  namespace graph {

  GraphException::GraphException(const string &location, const string &message) :
    Exception(location, message)
  {
  }

  AlreadyExist::AlreadyExist(const string &location, const string &message) :
    GraphException(location, message)
  {

  }

  EdgeNotFound::EdgeNotFound(const string &location, const string &message) :
    GraphException(location, message)
  {
  }

  InvalidGetter::InvalidGetter(const string &location, const string &message) :
    GraphException(location, message)
  {
  }

  InvalidSetter::InvalidSetter(const string &location, const string &message) :
    GraphException(location, message)
  {
  }


  GraphInvalidIteratorException::GraphInvalidIteratorException(const string &location, const string &message) :
    GraphException(location, message)
  {
  }

  GraphNoSuchElementException::GraphNoSuchElementException(const string &location, const string &message) :
    GraphException(location, message)
  {
  }

  GraphSchemaException::GraphSchemaException(const string &location, const string &message) :
    GraphException(location, message)
  {
  }

    
}}