#pragma once
#include "common.h"
#include "widget.h"
#include <vector>

class LayoutManager{
private:
    std::vector<Widget*> components;
public:
    void addComponent(Widget* component);
    void drawComponents();
};