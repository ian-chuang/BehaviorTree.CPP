/* Copyright (C) 2015-2018 Michele Colledanchise -  All Rights Reserved
 * Copyright (C) 2018-2020 Davide Faconti, Eurecat -  All Rights Reserved
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
*   to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
*   and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
*   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include <vector>
#include "behaviortree_cpp/tree_node.h"

namespace BT
{
class ControlNode : public TreeNode
{
protected:
  std::vector<TreeNode*> children_nodes_;

public:
  ControlNode(const std::string& name, const NodeConfig& config);

  virtual ~ControlNode() override = default;

  /// The method used to add nodes to the children vector
  void addChild(TreeNode* child);

  void insertChildAfter(TreeNode* child, TreeNode* sibling);

  size_t childrenCount() const;

  const std::vector<TreeNode*>& children() const;

  const TreeNode* child(size_t index) const
  {
    return children().at(index);
  }

  virtual void halt() override;

  /// same as resetChildren()
  void haltChildren();

  [[deprecated("deprecated: please use explicitly haltChildren() or haltChild(i)")]] void
  haltChildren(size_t first);

  void haltChild(size_t i);

  virtual NodeType type() const override final
  {
    return NodeType::CONTROL;
  }

  /// Set the status of all children to IDLE.
  /// also send a halt() signal to all RUNNING children
  void resetChildren();
};
}   // namespace BT
