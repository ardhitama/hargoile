#ifndef ROUTE_H
#define ROUTE_H

class Route
{
public:
    Route();
    void simplify(unsigned int level);
    bool serialize();
    virtual ~Route();
};

void Route::simplify(unsigned int level)
{
    //
}

#endif // ROUTE_H
