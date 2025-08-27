#pragma once
#include "utils.h"
#include <string>

class role {
  public:
    /*struct roleData
    {
        int attack; //attack
        int magicAttack; //magic attack
        int healthPoints; //health points
        int recovery;
        int speed;
    }roleOriginData, roleCurrentData;*/
    std::wstring label;
    enum roleProperty {
        HealthPoint,
        Defence,
        COUNT // Last one
    };
    int* property;
    const int* MaxProperty;

    role();
    void setLocation(POINT location);
    void setImg(LPCTSTR pResType, LPCTSTR pResName, POINT size = {0});
    void setImg(LPCTSTR pImgFile, POINT size = {0});

    bool shiftProerty(roleProperty targetProperty, int shiftValue);

    void render();

    // role(POINT location, LPCTSTR pResType, LPCTSTR pResName, roleData INdata);
    // role(POINT location, LPCTSTR pResType, LPCTSTR pResName);
  private:
    POINT location;
    IMAGE img;
};