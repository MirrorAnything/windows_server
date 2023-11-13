//
// Created by meepojia on 2023/11/13.
//

#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

const int MOUSE_MOVE = 1;




struct Event{
    int type;

    double mouse_x;
    double mouse_y;
    void MouseMove();
};

#endif //MOUSE_EVENT_H
