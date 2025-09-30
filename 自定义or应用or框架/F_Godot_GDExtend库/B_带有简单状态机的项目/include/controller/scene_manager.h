// #ifndef __TInputManager_CPP_H__
// #define __TInputManager_CPP_H__

// #include "controller/controller_node.h"

// namespace godot
// {
// 	// class Input;
// }

// using namespace godot;

// class TSceneManager : public TControllerNode 
// {
//     GDCLASS(TSceneManager, TControllerNode)
    
// private:
//     String current_scene_path;
//     // String loading_scene_path;
//     bool is_loading = false;
    
//     // 场景加载队列
//     // Array scene_queue;
    
//     // 资源缓存
//     Dictionary resource_cache;
//     Node * current_scene_pointer = nullptr; //当前场景的指针
    
//     // 过渡场景路径
//     String transition_scene_path = "res://scenes/transition.tscn";
    
// protected:
//     static void _bind_methods();
    
// public:
//     virtual void initialize() override; // 初始方法，需要再外部访问
    
//     // 加载场景
//     void load_scene(String path_name, bool use_transition = true);
//     // 获取当前场景
//     Node* get_current_scene();
//     // 场景加载完成信号
//     void _on_scene_loaded(Ref<PackedScene> scene);

//     // 异步加载场景
//     // void load_scene_async(String path, bool use_transition = true);
//     // void _check_async_load();
//     // 预加载资源
//     // void preload_resources(Array resources);

//     void set_scene_path(Dictionary a);
//     Dictionary get_scene_path(); 
// };
// #endif