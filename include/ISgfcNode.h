#pragma once

// Project includes
#include "ISgfcProperty.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

// C++ Standard Library includes
#include <memory>
#include <vector>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcNode interface provides access to the data of a single
  /// SGF node in a tree of SGF nodes. ISgfcNode also provides methods to
  /// navigate the game tree.
  class SGFCPLUSPLUS_EXPORT ISgfcNode
  {
  public:
    /// @brief Initializes a newly constructed ISgfcNode object.
    ISgfcNode();

    /// @brief Destroys and cleans up the ISgfcNode object.
    virtual ~ISgfcNode();

    /// @brief Returns the node's first child node. Returns @e nullptr if
    /// the node has no children.
    virtual std::shared_ptr<ISgfcNode> GetFirstChild() const = 0;

    /// @brief Returns the node's last child node. Returns @e nullptr if
    /// the node has no children.
    virtual std::shared_ptr<ISgfcNode> GetLastChild() const = 0;

    /// @brief Returns a collection of child nodes of the node. The collection
    /// is ordered, beginning with the first child node and ending with the
    /// last child node. The collection is empty if the node has no children.
    virtual std::vector<std::shared_ptr<ISgfcNode>> GetChildren() const = 0;

    /// @brief Returns true if the node has one or more children. Returns
    /// false if the node has no children.
    virtual bool HasChildren() const = 0;

    /// @brief Returns the node's next sibling node. Returns @e nullptr if
    /// the node has no next sibling node, i.e. if the node is the last child
    /// of its parent.
    virtual std::shared_ptr<ISgfcNode> GetNextSibling() const = 0;

    /// @brief Returns true if the node has a next sibling node. Returns false
    /// if the node has no next sibling node, i.e. if the node is the last child
    /// of its parent.
    virtual bool HasNextSibling() const = 0;

    /// @brief Returns the node's previous sibling node. Returns @e nullptr if
    /// the node has no previous sibling node, i.e. if the node is the first
    /// child of its parent.
    virtual std::shared_ptr<ISgfcNode> GetPreviousSibling() const = 0;

    /// @brief Returns true if the node has a previous sibling node. Returns
    /// false if the node has no previous sibling node, i.e. if the node is the
    /// first child of its parent.
    virtual bool HasPreviousSibling() const = 0;

    /// @brief Returns the node's parent node. Returns @e nullptr if the node
    /// has no parent node, i.e. if the node is the root node of a game tree.
    virtual std::shared_ptr<ISgfcNode> GetParent() const = 0;

    /// @brief Returns true if the node has a parent node. Returns false if the
    /// node has no parent node, i.e. if the node is the root node of a game
    /// tree.
    virtual bool HasParent() const = 0;

    /// @brief Returns true if the node is a descendant of @a node, i.e. if the
    /// node is anywhere below @a node in the game tree. Returns false if the
    /// node is not a descendant of @a node.
    ///
    /// @exception std::invalid_argument Is thrown if @a node is @e nullptr.
    virtual bool IsDescendantOf(std::shared_ptr<ISgfcNode> node) const = 0;

    /// @brief Returns true if the node is an ancestor of @a node, i.e. if the
    /// node is a direct or indirect parent of @a node. Returns false if the
    /// node is not an ancestor of @a node.
    ///
    /// @exception std::invalid_argument Is thrown if @a node is @e nullptr.
    virtual bool IsAncestorOf(std::shared_ptr<ISgfcNode> node) const = 0;

    /// @brief Returns the root node of the game tree that contains the node.
    /// Returns @e nullptr if the node is already the root node.
    virtual std::shared_ptr<ISgfcNode> GetRoot() const = 0;

    /// @brief Returns true if the node is the root node of a game tree. Returns
    /// false if the node is not the root node of a game tree.
    virtual bool IsRoot() const = 0;

    /// @brief Returns a collection with the properties of the node. The
    /// collection is empty if the node has no properties. The collection has
    /// no particular order.
    ///
    /// The SGF standard does not define an order in which properties have to
    /// appear within a node. In fact, it explicitly states that different
    /// applications may use different ordering, and that the order may change
    /// every time that the SGF data is saved.
    ///
    /// The SGF standard defines that only one of each property is allowed per
    /// node.
    virtual std::vector<std::shared_ptr<ISgfcProperty>> GetProperties() const = 0;

    /// @brief Sets the properties of the node to the collection @a properties.
    /// The collection may be empty. The order in which properties appear in
    /// the collection is irrelevant. No SgfcPropertyType may appear more than
    /// once in the collection.
    ///
    /// @exception std::invalid_argument Is thrown if @a properties contains
    /// @e nullptr elements or if an SgfcPropertyType appears more than once.
    virtual void SetProperties(std::vector<std::shared_ptr<ISgfcProperty>> properties) = 0;

    /// @brief Returns the property with the specified type @a propertyType if
    /// the node has such a property. Returns @e nullptr if the node has no
    /// such property.
    ///
    /// The SGF standard defines that only one of each property is allowed per
    /// node.
    virtual std::shared_ptr<ISgfcProperty> GetProperty(SgfcPropertyType propertyType) const = 0;
  };
}
