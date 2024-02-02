#ifndef CUBE_H
#define CUBE_H

class Vector3_Float
{
public:
    float x, y, z;
    Vector3_Float()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }
    Vector3_Float(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
};

namespace cube
{
    class Creature
    {
    public:
        unsigned int field_0;
        unsigned int field_4;
        long long int GUID;
        long long unsigned int x, y, z; // 0x10 ~ 0x27
        char padding2[0x60];
        float physical_size; // 0x88
        char padding1[0xD4];
        Vector3_Float camera_offset;
        float HP;
        float MP;
        float block_power;
        float HP_multiplier;
        float attack_speed_multiplier;
        float damage_multiplier;
        float armor_multiplier;
        float resistance_multiplier;
        char field_18C;
        char field_18D;
        char field_18E;
        char field_18F;
        int level;
        int XP;
        long long parent_GUID;
    };
}
#endif