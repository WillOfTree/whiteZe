#include "common.h"


void TCommonMethod::_bind_methods() {}


/**
 * 将main分组节点赋值给m_main_group变量
 */
bool TCommonMethod::get_main_group_node(std::map<String, Node *> *b)
{
    Array a = get_tree()->get_nodes_in_group("main");
    
    for (int i=0; i < a.size(); i++) 
    {
        Node * temp = cast_to<Node>(a[i]);
        String temp_s = temp->get_name();
        (*b)[temp_s] = temp;
    }
};




