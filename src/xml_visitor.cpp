#include <algorithm>
#include <string>
#include <iostream>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>


#include "xml_visitor.hpp"

#include "cognitive_function.hpp"

using namespace std;

void XmlVisitor::startUp() {
    //stream(&sXML);
    //stream.setAutoFormatting(true);
    //stream.writeStartDocument();
    //stream.writeStartElement("application");

    //<?xml-stylesheet type="text/xsl" href="application.xsl"?>
    //<application>
    //<name>scriptManagerTEST</name>

    ss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
    ss << "<?xml-stylesheet type=\"text/xsl\" href=\"application.xsl\"?>" << endl;
    ss << "<application>" << endl;
    ss << "<name>dreamTEST</name>" << endl;
    ss << endl;
}

void XmlVisitor::tearDown() {
    ss << "</application>" << endl;

    _content = ss.str();
}

void XmlVisitor::onNode(shared_ptr<const Node> node) {
    ss << "<module>" << endl;
    ss << "    <name>" << node->name() << "</name>" << endl;
    ss << "    <paramaters>--context components/" << node->name() << "/config</parameters>" << endl;
    ss << "    <node>dream1</node>" << endl;
    ss << "    <tag>" << node->name() << "</tag>" << endl;
    ss << "</module>" << endl;
    ss << endl;
}

void XmlVisitor::onConnection(shared_ptr<const Connection> connection) {
    ss << "<connection>" << endl;
    ss << "    <from>" << connection->from.port.lock()->name << "</from>" << endl;
    ss << "    <to>" << connection->to.port.lock()->name << "</to>" << endl;
    ss << "    <protocol>tcp</protocol>" << endl;
    ss << "</connection>" << endl;
    ss << endl;
}
