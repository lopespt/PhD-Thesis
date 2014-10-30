#ifndef NODESTRING_HPP
#define NODESTRING_HPP

#include <QString>
class NodeString{
    public:
        char text[50];
        NodeString(){text[0]='\0';};
        NodeString(const QString& other){
            strcpy(text, other.toStdString().c_str());
        }

        NodeString& operator=(const QString& other){
            strcpy(text, other.toStdString().c_str());
            return *this;
        }
        bool operator<(const QString& other) const{
            return strcmp(text, other.toStdString().c_str()) < 0;
        }
        bool operator<(const NodeString& other)const{
            return strcmp(text, other.text)<0;
        }
        bool operator==(const NodeString& other) const{
            return !(*this < other || other < *this);
        }
};



#endif // NODESTRING_HPP
