#pragma once
#include "Play.h"
#include "MainGame.h"

class GameObject
{
public:

    enum Type
    {
        OBJ_NONE = -1,
        OBJ_PLAYER = 0,
        OBJ_PLATFORM,
        OBJ_MOVING_PLATFORM,
        OBJ_DECAYING_PLATFORM,
        OBJ_ALL = 999
    };

    GameObject(Point2f pos);
    virtual ~GameObject();

    virtual void Update(GameState& gState) = 0;
    virtual void Draw(GameState& gState) const = 0;

    void SetPosition( const Point2f pos) { m_pos = pos; }
    Point2f GetPosition() const { return m_pos; };

    void SetVelocity(const Vector2f vel) { m_velocity = vel; }
    Vector2f GetVelocity() const { return m_velocity; };

    void SetWidth(const int width) { m_width = width; }
    int GetWidth() const { return m_width; }

    void SetHeight(const int Height) { m_height = Height; }
    int GetHeight() const { return m_height; }

    void SetType(const Type type) { m_type = type; }
    Type GetType() const { return m_type; }

    void SetCollidable(const bool collidable) { b_collidable = collidable; }
    bool IsCollidable() const { return b_collidable; }

    void SetDrawOrder(const int drawOrder) { m_drawOrder = drawOrder; }
    int GetDrawOrder() const { return m_drawOrder; };

    void SetUpdateOrder(const int updateOrder) { m_updateOrder = updateOrder; }
    int GetUpdateOrder() const { return m_updateOrder; };

    static int GetObjectCount(Type eType);
    static int GetObjectList(GameObject::Type eType, std::vector< GameObject* >& vList);

    static void UpdateAll(GameState& gState);
    static void DrawAll(GameState& gState);
    static void DestroyAll();

protected:

    static bool DrawOrder(const GameObject* a, const GameObject* b) { return a->m_drawOrder > b->m_drawOrder; }
    static bool UpdateOrder(const GameObject* a, const GameObject* b) { return a->m_updateOrder > b->m_updateOrder; }

    Type m_type{ OBJ_NONE };
    bool m_active{ true };
    bool b_collidable{ true };
    Point2f m_pos{ 0, 0 };
    Vector2f m_velocity{ 0, 0 };
    int spriteId{ -1 };
    int m_width{ 0 };
    int m_height{ 0 };

    int m_drawOrder{ 0 };
    int m_updateOrder{ 0 };

    static std::vector< GameObject* > s_vUpdateList;
    static std::vector< GameObject* > s_vDrawList;

};