// Project includes
#include "SgfcNode.h"
#include "SgfcTreeBuilder.h"

// C++ Standard Library includes
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcTreeBuilder::SgfcTreeBuilder(std::weak_ptr<ISgfcGame> game)
    : game(game)
  {
  }

  SgfcTreeBuilder::~SgfcTreeBuilder()
  {
  }

  std::weak_ptr<ISgfcGame> SgfcTreeBuilder::GetGame() const
  {
    return this->game;
  }

  void SgfcTreeBuilder::SetFirstChild(
    std::shared_ptr<ISgfcNode> node,
    std::shared_ptr<ISgfcNode> child) const
  {
    if (node == nullptr)
      throw std::invalid_argument("SetFirstChild failed: Node argument is null");

    if (node == child)
      throw std::invalid_argument("SetFirstChild failed: Child is equal to node");

    std::shared_ptr<ISgfcNode> oldFirstChild = node->GetFirstChild();
    if (oldFirstChild == child)
      return;  // child is already at the correct position

    if (child != nullptr && child->IsAncestorOf(node))
      throw std::invalid_argument("SetFirstChild failed: Child is ancestor of node");

    if (oldFirstChild != nullptr)
    {
      // Modifies not only oldFirstChild, but also node: node->firstChild
      // becomes something else, possibly nullptr (if node had only one child).
      RemoveNodeFromCurrentLocation(oldFirstChild);

      // child may have become node->firstChild if child was node's second child
      // before we invoked RemoveNodeFromCurrentLocation(). If that is the case
      // then the goal is already achieved.
      if (node->GetFirstChild() == child)
        return;
    }

    if (child != nullptr)
    {
      RemoveNodeFromCurrentLocation(child);
    }

    auto newParent = node;
    auto newNextSibling = node->GetFirstChild();
    InsertNodeAtNewLocation(child, newParent, newNextSibling);
  }

  void SgfcTreeBuilder::AppendChild(
    std::shared_ptr<ISgfcNode> node,
    std::shared_ptr<ISgfcNode> child) const
  {
    if (node == nullptr)
      throw std::invalid_argument("AppendChild failed: Node argument is null");

    if (child == nullptr)
      throw std::invalid_argument("AppendChild failed: Child argument is null");

    if (node == child)
      throw std::invalid_argument("AppendChild failed: Child is equal to node");

    if (child->GetParent() == node && child->GetNextSibling() == nullptr)
      return;  // child is already at the correct position

    if (child->IsAncestorOf(node))
      throw std::invalid_argument("AppendChild failed: Child is ancestor of node");

    RemoveNodeFromCurrentLocation(child);

    auto newParent = node;
    std::shared_ptr<ISgfcNode> newNextSibling = nullptr;
    InsertNodeAtNewLocation(child, newParent, newNextSibling);
  }

  void SgfcTreeBuilder::InsertChild(
    std::shared_ptr<ISgfcNode> node,
    std::shared_ptr<ISgfcNode> child,
    std::shared_ptr<ISgfcNode> referenceChild) const
  {
    if (node == nullptr)
      throw std::invalid_argument("InsertChild failed: Node argument is null");

    if (child == nullptr)
      throw std::invalid_argument("InsertChild failed: Child argument is null");

    if (node == child)
      throw std::invalid_argument("InsertChild failed: Child is equal to node");

    if (referenceChild != nullptr && referenceChild->GetParent() != node)
      throw std::invalid_argument("InsertChild failed: Reference child is not a child of node");

    if (child->GetParent() == node && child->GetNextSibling() == referenceChild)
      return;  // child is already at the correct position

    if (child->IsAncestorOf(node))
      throw std::invalid_argument("InsertChild failed: Child is ancestor of node");

    RemoveNodeFromCurrentLocation(child);

    auto newParent = node;
    auto newNextSibling = referenceChild;  // can be nullptr
    InsertNodeAtNewLocation(child, newParent, newNextSibling);
  }

  void SgfcTreeBuilder::RemoveChild(
    std::shared_ptr<ISgfcNode> node,
    std::shared_ptr<ISgfcNode> child) const
  {
    if (node == nullptr)
      throw std::invalid_argument("RemoveChild failed: Node argument is null");

    if (child == nullptr)
      throw std::invalid_argument("RemoveChild failed: Child argument is null");

    if (child->GetParent() != node)
      throw std::invalid_argument("RemoveChild failed: Child is not a child of node");

    RemoveNodeFromCurrentLocation(child);
  }

  void SgfcTreeBuilder::ReplaceChild(
    std::shared_ptr<ISgfcNode> node,
    std::shared_ptr<ISgfcNode> newChild,
    std::shared_ptr<ISgfcNode> oldChild) const
  {
    if (node == nullptr)
      throw std::invalid_argument("ReplaceChild failed: Node argument is null");

    if (newChild == nullptr)
      throw std::invalid_argument("ReplaceChild failed: NewChild argument is null");

    if (oldChild == nullptr)
      throw std::invalid_argument("ReplaceChild failed: OldChild argument is null");

    if (node == newChild)
      throw std::invalid_argument("ReplaceChild failed: NewChild is equal to node");

    if (oldChild->GetParent() != node)
      throw std::invalid_argument("ReplaceChild failed: OldChild is not a child of node");

    if (newChild == oldChild)
      return;  // newChild is already at the correct position

    if (newChild->IsAncestorOf(node))
      throw std::invalid_argument("ReplaceChild failed: NewChild is ancestor of node");

    RemoveNodeFromCurrentLocation(newChild);

    auto newParent = node;
    auto newNextSibling = oldChild;
    InsertNodeAtNewLocation(newChild, newParent, newNextSibling);

    RemoveNodeFromCurrentLocation(oldChild);
  }

  void SgfcTreeBuilder::SetNextSibling(
    std::shared_ptr<ISgfcNode> node,
    std::shared_ptr<ISgfcNode> nextSibling) const
  {
    if (node == nullptr)
      throw std::invalid_argument("SetNextSibling failed: Node argument is null");

    if (node->IsRoot())
      throw std::invalid_argument("SetNextSibling failed: Node is root node of game tree");

    if (node == nextSibling)
      throw std::invalid_argument("SetNextSibling failed: NextSibling is equal to node");

    auto oldNextSibling = node->GetNextSibling();
    if (oldNextSibling == nextSibling)
      return;  // nextSibling is already at the correct position

    if (nextSibling == nullptr)
    {
      // oldNextSibling can't be nullptr, otherwise we would have already
      // returned control to the caller
      RemoveNodeFromCurrentLocation(oldNextSibling);
    }
    else
    {
      if (nextSibling->IsAncestorOf(node))
        throw std::invalid_argument("SetNextSibling failed: NextSibling is ancestor of node");

      RemoveNodeFromCurrentLocation(nextSibling);

      auto newParent = node->GetParent();  // can't be nullptr, we checked for root node
      auto newNextSibling = node->GetNextSibling();  // may be nullptr
      InsertNodeAtNewLocation(nextSibling, newParent, newNextSibling);
    }
  }

  void SgfcTreeBuilder::SetParent(
    std::shared_ptr<ISgfcNode> node,
    std::shared_ptr<ISgfcNode> parent) const
  {
    if (node == nullptr)
      throw std::invalid_argument("SetParent failed: Node argument is null");

    if (node == parent)
      throw std::invalid_argument("SetParent failed: Parent is equal to node");

    if (node->GetParent() == parent)
      return;  // node is already at the correct position

    if (parent != nullptr && parent->IsDescendantOf(node))
      throw std::invalid_argument("SetParent failed: Parent is descendant of node");

    RemoveNodeFromCurrentLocation(node);

    if (parent != nullptr)
    {
      auto newParent = parent;
      std::shared_ptr<ISgfcNode> newNextSibling = nullptr;
      InsertNodeAtNewLocation(node, newParent, newNextSibling);
    }
  }

  /// @brief Removes @a node from its current location in the game tree and
  /// relinks the game tree to fill the gap.
  ///
  /// When control returns to the caller, @a node has no parent and no next
  /// sibling but retains its first child.
  ///
  /// The implementation of this method assumes that all involved node objects
  /// are instances of SgfcNode. The implementation uses special setter methods
  /// defined in the SgfcNode class, which are not available in the ISgfcNode
  /// interface, to manipulate the involved nodes'
  /// parent / first child / next sibling relationships.
  void SgfcTreeBuilder::RemoveNodeFromCurrentLocation(
    std::shared_ptr<ISgfcNode> node) const
  {
    if (node->IsRoot())
      return;

    SgfcNode* nodeImplementation = static_cast<SgfcNode*>(node.get());

    auto parentNode = nodeImplementation->GetParent();
    SgfcNode* parentNodeImplementation = static_cast<SgfcNode*>(parentNode.get());

    if (parentNodeImplementation->GetFirstChild() == node)
    {
      parentNodeImplementation->SetFirstChild(nodeImplementation->GetNextSibling());
    }
    else
    {
      auto previousSiblingNode = node->GetPreviousSibling();
      SgfcNode* previousSiblingNodeImplementation = static_cast<SgfcNode*>(previousSiblingNode.get());
      previousSiblingNodeImplementation->SetNextSibling(nodeImplementation->GetNextSibling());
    }

    nodeImplementation->SetParent(nullptr);
    // Important: This must happen after we have re-linked the original
    // next sibling, otherwise the next sibling would become deallocated.
    nodeImplementation->SetNextSibling(nullptr);
  }

  /// @brief Inserts @a node at the location in the game tree that is defined
  /// by @a newParent and @a newNextSibling.
  ///
  /// This method expects that RemoveNodeFromCurrentLocation() has been
  /// previously invoked with @a node, i.e. that @a node is currently not
  /// anywhere in the game tree.
  ///
  /// The implementation of this method assumes that all involved node objects
  /// are instances of SgfcNode. The implementation uses special setter methods
  /// defined in the SgfcNode class, which are not available in the ISgfcNode
  /// interface, to manipulate the involved nodes'
  /// parent / first child / next sibling relationships.
  void SgfcTreeBuilder::InsertNodeAtNewLocation(
    std::shared_ptr<ISgfcNode> node,
    std::shared_ptr<ISgfcNode> newParent,
    std::shared_ptr<ISgfcNode> newNextSibling) const
  {
    SgfcNode* nodeImplementation = static_cast<SgfcNode*>(node.get());

    SgfcNode* newParentNodeImplementation = static_cast<SgfcNode*>(newParent.get());

    if (newParentNodeImplementation->GetFirstChild() == newNextSibling)
    {
      newParentNodeImplementation->SetFirstChild(node);
    }
    else
    {
      std::shared_ptr<ISgfcNode> previousSiblingNode;

      // newNextSibling is nullptr if node should be added as the last
      // child to parent
      if (newNextSibling == nullptr)
        previousSiblingNode = newParentNodeImplementation->GetLastChild();
      else
        previousSiblingNode = newNextSibling->GetPreviousSibling();

      SgfcNode* previousSiblingNodeImplementation = static_cast<SgfcNode*>(previousSiblingNode.get());
      previousSiblingNodeImplementation->SetNextSibling(node);
    }

    nodeImplementation->SetParent(newParent);
    nodeImplementation->SetNextSibling(newNextSibling);
  }
}
