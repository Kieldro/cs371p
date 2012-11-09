
#ifndef AbstractCell_h
#define AbstractCell_h

class AbstractCell{
	
    virtual void qux(){}
public:
    virtual bool update(int neighbors){}
};

#endif // AbstractCell_h