
#include "NodeString.hpp"
#include <QString>

NodeString::NodeString(){
    text[0]='\0';
};

NodeString::NodeString(const QString& other){
    strcpy(text, other.toStdString().c_str());
}

NodeString& NodeString::operator=(const QString& other){
    strcpy(text, other.toStdString().c_str());
    return *this;
}

bool NodeString::operator<(const QString& other) const{
    return strcmp(text, other.toStdString().c_str()) < 0;
}

bool NodeString::operator<(const NodeString& other)const{
    return strcmp(text, other.text)<0;
}

bool NodeString::operator==(const NodeString& other) const{
    return !(*this < other || other < *this);
}



