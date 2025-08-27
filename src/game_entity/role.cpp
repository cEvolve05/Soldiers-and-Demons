#include "role.h"
#include "activity.h"

role::role() {
    this->property = new int[roleProperty::COUNT]{5, 0};
    this->MaxProperty = new const int[roleProperty::COUNT]{5, INT_MAX};
    this->location = {0};
}

void role::setLocation(POINT location) {
    this->location = location;
    return;
}

void role::setImg(LPCTSTR pResType, LPCTSTR pResName, POINT size) {
    loadimage(&this->img, pResType, pResName, size.x, size.y);
    return;
}

void role::setImg(LPCTSTR pImgFile, POINT size) {
    loadimage(&this->img, pImgFile, size.x, size.y);
    return;
}

bool role::shiftProerty(roleProperty targetProperty, int shiftValue) {
    if (property[targetProperty] + shiftValue > MaxProperty[targetProperty]) {
        return false;
    }

    property[targetProperty] += shiftValue;

    return true;
}

void role::render() {
    activity::drawPngAlpha(this->location.x, this->location.y, &this->img);
    return;
}