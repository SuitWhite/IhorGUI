#include "IhorGUI/layoutmanager.h"

void LayoutManager::addComponent(Widget *widget){
    components.push_back(widget);
}

void LayoutManager::drawComponents(){
    for (const auto &elem: components){
        elem->draw();
    }
}