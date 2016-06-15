#ifndef XMLVISITOR_HPP
#define XMLVISITOR_HPP

#include <string>
#include <sstream>
#include <memory>
#include <QXmlStreamWriter>

#include "architecture.hpp"  // Node
#include "visitor.hpp"

class XmlVisitor : public Visitor {
    using Visitor::Visitor;  // inheriting Visitor's ctor

private:
    void startUp() override;
    //void beginNodes() override;
    void onNode(std::shared_ptr<const Node>) override;
    //void beginConnections() override;
    void onConnection(std::shared_ptr<const Connection>) override;
    void tearDown() override;

private:
    std::stringstream ss;
    QXmlStreamWriter stream;
    QString sXML;

    Architecture* _architecture;
};

#endif // XMLVISITOR_HPP
