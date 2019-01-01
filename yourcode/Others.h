//
// Created by oxer on 18-12-9.
//

#ifndef PJ_OTHERS_H
#define PJ_OTHERS_H

struct Rect {
    Rect()  {}

    Rect(double a_minX, double a_minY, double a_maxX, double a_maxY)
    {
        min[0] = a_minX;
        min[1] = a_minY;

        max[0] = a_maxX;
        max[1] = a_maxY;
    }


    double min[2];
    double max[2];
};


#endif //PJ_OTHERS_H
