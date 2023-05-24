#pragma once
#include "common.h"
#include <vector>

class Widget;

class LayoutManager{
private:
    std::vector<Widget*> components;
public:
    void addComponent(Widget* component);
    void drawComponents();
};