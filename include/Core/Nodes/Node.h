#pragma once
#include <memory>
#include <vector>
#include <string>

//class Node
//{
//    public:
//        Node(){};
//        std::weak_ptr<Node> getParent() const;
//        const std::vector<std::shared_ptr<Node>>& getChildren() const;
//        std::string Name;
//
//        void setParent(const Node& parent);
//        void addChild(Node& child);
//
//    private:
//        std::weak_ptr<Node> _parentNode;
//        std::vector<std::shared_ptr<Node>> _childNodes;
//};
//
//inline std::weak_ptr<Node> Node::getParent() const
//{
//    return _parentNode;
//}
//
//inline const std::vector<std::shared_ptr<Node>>& Node::getChildren() const
//{
//    return _childNodes;
//}
//
//inline void Node::setParent(const Node& parent)
//{
//    _parentNode = std::make_shared<Node>(parent);
//}
//
//inline void Node::addChild(Node& child)
//{
//    child.setParent(*this);
//    _childNodes.push_back(std::make_shared<Node>(child));
//}
