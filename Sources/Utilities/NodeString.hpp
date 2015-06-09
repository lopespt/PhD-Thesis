#ifndef NODESTRING_HPP
#define NODESTRING_HPP

class QString;

class NodeString {
public:
    char text[50];

    NodeString();

    NodeString(const QString &other);

    NodeString &operator=(const QString &other);

    bool operator<(const QString &other) const;

    bool operator<(const NodeString &other) const;

    bool operator==(const NodeString &other) const;
};


#endif // NODESTRING_HPP
