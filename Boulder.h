#ifndef BOULDER_H
#define	BOULDER_H
#include "Drawable.h"

class Boulder : public Drawable{
public:
    Boulder(float, float);
    Boulder(const Boulder& orig);
    void draw();
    virtual ~Boulder();
private:

};

#endif	/* BOULDER_H */