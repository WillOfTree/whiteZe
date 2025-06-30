#include "resource/piece_data.h"


void PieceData::_bind_methods() 
{
    /* 技能ID */
    ClassDB::bind_method(D_METHOD("set_piece_texture", "s"), &PieceData::set_piece_texture);
    ClassDB::bind_method(D_METHOD("get_piece_texture"), &PieceData::get_piece_texture);
    ClassDB::add_property("PieceData",
    	PropertyInfo(Variant::OBJECT, "Piece Texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"),
        "set_piece_texture",
        "get_piece_texture");

    /* 技能名称 */
    ClassDB::bind_method(D_METHOD("set_spawn_position", "s"), &PieceData::set_spawn_position);
    ClassDB::bind_method(D_METHOD("get_spawn_position"), &PieceData::get_spawn_position);
    ClassDB::add_property("PieceData",
    	PropertyInfo(Variant::VECTOR2, "Spawn Position"),
        "set_spawn_position",
        "get_spawn_position");

    // /* 伤害 */
    // ClassDB::bind_method(D_METHOD("set_harm", "s"), &PieceData::set_harm);
    // ClassDB::bind_method(D_METHOD("get_harm"), &PieceData::get_harm);
    // ClassDB::add_property("PieceData",
    // 	PropertyInfo(Variant::INT, "Harm"),
    //     "set_harm",
    //     "get_harm");
}


void PieceData::set_piece_texture(Ref<Texture2D> &a)
{
    _piece_texture = a;
};
Ref<Texture2D> PieceData::get_piece_texture()
{
    return _piece_texture;
};

void PieceData::set_spawn_position(Vector2 a)
{
    _spawn_position = a;
};
Vector2 PieceData::get_spawn_position()
{
    return _spawn_position;
};
