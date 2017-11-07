////////////////////////////////////////////////////////////////////////////////
/// DISCLAIMER
///
/// Copyright 2014-2016 ArangoDB GmbH, Cologne, Germany
/// Copyright 2004-2014 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Max Neunhoeffer
////////////////////////////////////////////////////////////////////////////////

#ifndef ARANGOD_AQL_ENUMERATE_VIEW_BLOCK_H
#define ARANGOD_AQL_ENUMERATE_VIEW_BLOCK_H 1

#include "ExecutionBlock.h"
#include "Aql/ExecutionNode.h"
#include "Views/ViewIterator.h"
#include "VocBase/LogicalView.h"

namespace arangodb {
namespace aql {

class AqlItemBlock;

class ExecutionEngine;

class EnumerateViewBlock : public ExecutionBlock {
 public:
  EnumerateViewBlock(ExecutionEngine*, EnumerateViewNode const*);

  // here we release our docs from this collection
  int initializeCursor(AqlItemBlock* items, size_t pos) override;

  AqlItemBlock* getSome(size_t atLeast, size_t atMost) override final;

  // skip between atLeast and atMost returns the number actually skipped . . .
  // will only return less than atLeast if there aren't atLeast many
  // things to skip overall.
  size_t skipSome(size_t atLeast, size_t atMost) override final;

 private:
  void refreshIterator();

  std::unique_ptr<ViewIterator> _iter;
  ManagedDocumentResult _mmdr;
  bool _hasMore;
  bool _volatileState; // we have to recreate cached iterator when `reset` requested
};

}
}

#endif
