
#ifndef AbstractCell_h
#define AbstractCell_h

class AbstractCell{
	public:
		virtual bool readChar(char c) { return 0; }
		virtual void update(int neighbors, int* population) {}
		virtual bool isNeighbor() { return 0; }
};
#endif // AbstractCell_h