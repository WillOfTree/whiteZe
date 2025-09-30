// #include "controller/scene_manager.h"

// #include <godot_cpp/classes/packed_scene.hpp>
// #include <godot_cpp/classes/resource_loader.hpp>

// using namespace godot;

// void TSceneManager::_bind_methods() {
//     // ClassDB::bind_method(D_METHOD("load_scene", "path", "use_transition"), &TSceneManager::load_scene, DEFVAL(true));
//     // ClassDB::bind_method(D_METHOD("load_scene_async", "path", "use_transition"), &TSceneManager::load_scene_async, DEFVAL(true));
//     // ClassDB::bind_method(D_METHOD("preload_resources", "resources"), &TSceneManager::preload_resources);
//     // ClassDB::bind_method(D_METHOD("get_current_scene"), &TSceneManager::get_current_scene);
//     // ClassDB::bind_method(D_METHOD("clear_cache"), &TSceneManager::clear_cache);
//     // ClassDB::bind_method(D_METHOD("_on_scene_loaded", "scene"), &TSceneManager::_on_scene_loaded);
    
//     // ADD_SIGNAL(MethodInfo("scene_changed", PropertyInfo(Variant::STRING, "new_scene")));
//     // ADD_SIGNAL(MethodInfo("loading_started"));
//     // ADD_SIGNAL(MethodInfo("loading_progress", PropertyInfo(Variant::FLOAT, "progress")));
//     // ADD_SIGNAL(MethodInfo("loading_completed"));

//     ClassDB::bind_method(D_METHOD("set_scene_path", "r"), &TSceneManager::set_scene_path);
//     ClassDB::bind_method(D_METHOD("get_scene_path"), &TSceneManager::get_scene_path);
//     ClassDB::add_property("TSceneManager",
//     	PropertyInfo(Variant::DICTIONARY, "Scene Path"),
//         "set_scene_path",
//         "get_scene_path");
// }


// /**
//  * 初始化方法
//  */
// void TSceneManager::initialize()
// {
    
// };


// /**
//  * 加载场景
//  */
// void TSceneManager::load_scene(String path_name, bool use_transition)
// {
//     is_loading = true;
//     String loading_scene_path;

//     if (resource_cache.has(path_name))
//     {
//         loading_scene_path = resource_cache[path_name];
//     }
//     else 
//     {
//         String err = "No have Path:" + path_name;
//         ERR_FAIL_MSG(err);
//     }
    
//     // emit_signal("loading_started");
    
//     if (use_transition && !transition_scene_path.is_empty()) {
//         // 加载过渡场景
//         // Ref<PackedScene> transition_scene = ResourceLoader::get_singleton()->load(transition_scene_path);
//         // if (transition_scene.is_valid()) {
//         //     Node* transition = transition_scene->instantiate();
//         //     add_child(transition);
//         // }
//     }

//     Ref<PackedScene> new_scene = ResourceLoader::get_singleton()->load(loading_scene_path);
//     // 同步加载主场景
//     _on_scene_loaded(new_scene);
// }


// /**
//  * 场景添加
//  */
// void TSceneManager::_on_scene_loaded(Ref<PackedScene> scene) 
// {
//     // 移除旧场景
//     Node * old_scene = get_current_scene();
//     if (old_scene) {
//         old_scene->queue_free();
//     }
    
//     // 实例化新场景
//     Node * new_scene = scene->instantiate();
//     add_child(new_scene);
    
//     // 更新当前场景路径
//     current_scene_pointer = new_scene;
// }


// /**
//  * 获取当前场景
//  */
// Node* TSceneManager::get_current_scene() 
// {
//     return current_scene_pointer;
// }


// /**
//  * 异步加载
//  */
// // void TSceneManager::load_scene_async(String path, bool use_transition) 
// // {
//     // if (is_loading) {
//     //     scene_queue.push_back(path);
//     //     return;
//     // }
    
//     // is_loading = true;
//     // loading_scene_path = path;
    
//     // emit_signal("loading_started");
    
//     // if (use_transition && !transition_scene_path.is_empty()) {
//     //     // 加载过渡场景
//     //     Ref<PackedScene> transition_scene = ResourceLoader::load(transition_scene_path);
//     //     if (transition_scene.is_valid()) {
//     //         Node* transition = transition_scene->instantiate();
//     //         add_child(transition);
//     //     }
//     // }
    
//     // // 异步加载主场景
//     // ResourceLoader::get_singleton()->load_threaded_request(path);
    
//     // // 每帧检查加载进度
//     // SceneTree* tree = get_tree();
//     // if (tree) {
//     //     tree->connect("process_frame", Callable(this, "_check_async_load"));
//     // }
// // }


// // void TSceneManager::_check_async_load() 
// // {
// //     float progress = 0;
// //     Error err = ResourceLoader::get_singleton()->load_threaded_get_status(loading_scene_path, &progress);
    
// //     emit_signal("loading_progress", progress);
    
// //     if (err == ERR_FILE_EOF) {
// //         // 加载完成
// //         Ref<PackedScene> scene = ResourceLoader::get_singleton()->load_threaded_get(loading_scene_path);
// //         _on_scene_loaded(scene);
        
// //         SceneTree* tree = get_tree();
// //         if (tree) {
// //             tree->disconnect("process_frame", Callable(this, "_check_async_load"));
// //         }
// //     }
// // }




// // void TSceneManager::preload_resources(Array resources) 
// // {
// //     for (int i = 0; i < resources.size(); i++) {
// //         String path = resources[i].operator String();
// //         if (!resource_cache.has(path)) {
// //             Ref<Resource> res = ResourceLoader::load(path);
// //             if (res.is_valid()) {
// //                 resource_cache[path] = res;
// //             }
// //         }
// //     }
// // }



// void TSceneManager::set_scene_path(Dictionary a)
// {
//     resource_cache = a;
// };
// Dictionary TSceneManager::get_scene_path()
// {
//     return resource_cache;
// }; 