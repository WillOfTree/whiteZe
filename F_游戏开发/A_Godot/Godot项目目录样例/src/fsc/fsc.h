/**********************************
/*  状态机，启动状态
/*
/*
/*/
#ifndef __TFSC_CPP_H__
#define __TFSC_CPP_H__


#include <godot_cpp/classes/Node.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <map>

using namespace godot;

class TBATSTATE;
class TMOVESTATE;
class TOTHERSTATE;

class TFSC : public Node
{
    
    GDCLASS(TFSC, Node);
    
public:
    enum GAMESTATE {
        MOVE, BAT, OTHER 
    };
    
    TFSC();
    ~TFSC();
    virtual void _ready();
    virtual void _process(double _delta);

    // 子类
    virtual void initiazlie();
    virtual void exit();
    virtual void update(double delta);

    // 状态切换方法
    void on_transition(String aim_state, String current_state);

protected:
    static void _bind_methods();

private:
    TBATSTATE * m_bat_state;
    TMOVESTATE* m_move_state;
    TOTHERSTATE* m_other_state;
    // 游戏状态集合
    std::map<String, TFSC *> m_game_state;
    
    TFSC * m_current_state; // 当前状态类

    
};


#endif