
#ifndef LINK_HPP
#define LINK_HPP
typedef unsigned long long int link_time;

class Link{
    
    private:
        link_time time;
        float weight;
        bool sameLabel;
        static float max_weight;
        
    public:
        link_time getTime() const;
        void setTime(link_time time);
        float getWeight() const;
        void setWeight(float weight);
        Link();
        Link(link_time t, float weight, bool sameLabel=false);
        Link operator+(float) const;
        Link& operator+=(float);
        bool isSameLabel() const;
        void isSameLabel(bool);

        

};


#endif
