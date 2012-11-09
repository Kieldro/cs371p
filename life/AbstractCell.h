
#ifndef AbstractCell_h
#define AbstractCell_h

class AbstractCell{
		virtual void qux(){}
	public:
		virtual bool readChar(char c){return 0;}
		virtual int update(int neighbors){return 0;}
		virtual bool isAlive() {return 0;}
		virtual void ageCell(int inc) {}
};
#endif // AbstractCell_h