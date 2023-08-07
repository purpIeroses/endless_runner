#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
}
CollisionManager::~CollisionManager()
{

}
bool CollisionManager::AABB(Collider one, Collider other)
{
    Vector2 one_half = { (float)one.rect.w * 0.5f, (float)one.rect.h * 0.5f };
    Vector2 one_center = {(float)one.rect.x + one.rect.w*0.5f, (float)one.rect.y + one.rect.h*0.5f };

    Vector2 other_half = { (float)other.rect.w * 0.5f, (float)other.rect.h * 0.5f };
    Vector2 other_center = { (float)other.rect.x + other.rect.w*0.5f, (float)other.rect.y + other.rect.h*0.5f };

    if (one_center.x + one_half.x >= other_center.x - other_half.x &&
        one_center.x - one_half.x <= other_center.x + other_half.x &&
        one_center.y + one_half.y >= other_center.y - other_half.y &&
        one_center.y - one_half.y <= other_center.y + other_half.y)
    {
        return true;
    }
    return false;
  /*  return (
            one_center.x + one_half.x >= other_center.x - other_half.x &&
            one_center.x - one_half.x <= other_center.x + other_half.x &&
            one_center.y + one_half.y >= other_center.y - other_half.y &&
            one_center.y - one_half.y <= other_center.y + other_half.y
           );*/
}