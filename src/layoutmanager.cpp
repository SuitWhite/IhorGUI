#include "IhorGUI/layoutmanager.h"
#include "IhorGUI/widget.h"

void LayoutManager::addComponent(Widget *widget){
    components.push_back(widget);
}

void LayoutManager::drawComponents(){
    for (const auto &elem: components){
        elem->draw();
    }
}

void LayoutManager::clearComponents(){
    components.clear();
}