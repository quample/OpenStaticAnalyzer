/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2018 Department of Software Engineering - University of Szeged
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

#include "java/inc/java.h"
#include "java/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "java/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"
#include <sstream>


namespace columbus { namespace java { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace type { 
  NoType::NoType(NodeId _id, Factory *_factory) :
    Type(_id, _factory)
  {
  }

  NoType::~NoType() {
  }

  void NoType::clone(const NoType& other, bool tryOnVirtualParent) {
    type::Type::clone(other, false);

  }

  void NoType::prepareDelete(bool tryOnVirtualParent){
    type::Type::prepareDelete(false);
  }

  NodeKind NoType::getNodeKind() const {
    return ndkNoType;
  }

  bool NoType::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (type::Type::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool NoType::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (type::Type::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void NoType::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void NoType::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double NoType::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void NoType::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType NoType::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "type::NoType", strlen("type::NoType"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void NoType::sort(bool withVirtualBase /* = true */) {
    Type::sort(false);
  }

  void NoType::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Type::save(binIo,false);

  }

  void NoType::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Type::load(binIo,false);

  }


}


}}}
