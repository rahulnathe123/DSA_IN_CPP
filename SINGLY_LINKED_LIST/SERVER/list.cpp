#include "list.hpp"
#include "IList.hpp"
singly_linked_list::singly_linked_list()
{
    p_list = get_node(0);
}

singly_linked_list::singly_linked_list(const singly_linked_list& other)
{
    this->p_list = get_node(0);
    node_t* tail = p_list;
    for(node_t* run = other.p_list->next;run!=nullptr;run = run->next)
    {
        tail->next = get_node(run->data);
        tail = tail->next;
    }

}

singly_linked_list::singly_linked_list(singly_linked_list&& other)noexcept
{
    p_list = other.p_list;
    other.p_list = nullptr;
}

singly_linked_list& singly_linked_list::operator=(singly_linked_list&& other)
{
    if(this==&other)
    {
        return *this;
    }
    if(this->p_list->next != nullptr)
    {
        node_t* run = nullptr;
        node_t* run_next = nullptr;

        run = p_list;
        while(run)
        {
            run_next = run->next;
            delete run;
            run = run_next;
        }
    }
    p_list = other.p_list;
    other.p_list  = nullptr;
    return *this;
}

singly_linked_list& singly_linked_list::operator=(const singly_linked_list& other)
{
    if(this == &other)
    {
        return *this;
    }

    if(this->p_list->next!=nullptr)
    {
        node_t* run = nullptr;
        node_t* run_next = nullptr;
        run = p_list->next;
        while(run)
        {
            run_next = run->next;
            delete run;
            run = run_next;
        }
        p_list->next = nullptr;
    }
    node_t* tail = p_list;
    for(node_t* run = other.p_list->next;run != nullptr;run = run->next)
    {
        tail->next = get_node(run->data);
        tail = tail->next;
    }
    return *this;
}

singly_linked_list::~singly_linked_list()
{
    if(p_list == nullptr) 
        return;
    node_t* run = nullptr;
    node_t* run_next = nullptr;
    run = p_list;
    while(run)
    {
        run_next = run->next;
        delete run;
        run = run_next;
    }
    p_list = nullptr;
    std::cout<<"\nList Destroyed SuccessFully\n";
}
status_t singly_linked_list::insert_start(data_t new_data)
{
    node_t* new_node = get_node(new_data);
    new_node->next = p_list->next;
    p_list->next = new_node;
    return SUCCESS;
}

status_t singly_linked_list::insert_end(data_t new_data)
{
    node_t* new_node = get_node(new_data);
    node_t* run = nullptr;
    run = this->p_list;
    while(run->next)
    {
        run = run->next;
    }
    run->next = new_node;
    return SUCCESS;
}

status_t singly_linked_list::insert_after(data_t existing_data , data_t new_data)
{
    node_t* existing_node = nullptr;
    node_t* new_node = nullptr;

    existing_node = search_node(existing_data);
    if(existing_node == nullptr)
    {
        return (LIST_DATA_NOT_FOUND);
    }
    new_node = get_node(new_data);
    new_node->next = existing_node->next;
    existing_node->next = new_node;
    return (SUCCESS);
}

status_t singly_linked_list::insert_before(data_t existing_data , data_t new_data)
{
    node_t* existing_node = nullptr;
    node_t* new_node = nullptr;
    node_t* run = nullptr;
    node_t* previous_run = nullptr;

    run = p_list->next;
    previous_run = p_list;
    while(run)
    {
        if(run->data == existing_data)
        {
            break;
        }
        previous_run = run;
        run = run->next;
    }
    existing_node = run;
    if(existing_node == nullptr)
    {
        return (LIST_DATA_NOT_FOUND);
    }
    new_node = get_node(new_data);
    new_node->next = existing_node;
    previous_run->next = new_node;
    return (SUCCESS);
}

status_t singly_linked_list::get_start(data_t& start_data)const
{
    if(is_list_empty())
    {
        return (LIST_EMPTY);
    }
    start_data = p_list->next->data;
    return (SUCCESS);
}

status_t singly_linked_list::get_end(data_t& end_data)const
{
    node_t* run = nullptr;
    if(is_list_empty())
    {
        return (LIST_EMPTY);
    }

    run = p_list->next;
    while(run->next)
    {
        run = run->next;
    }
    end_data = run->data;
    return (SUCCESS);
}

status_t singly_linked_list::pop_start(data_t & start_data)
{
    node_t* delete_node = nullptr;
    node_t* delete_previous = nullptr;
    node_t* delete_next = nullptr;
    if(is_list_empty())
    {
        return (LIST_EMPTY);
    }
    start_data = p_list->next->data;
    delete_previous = p_list;
    delete_node = p_list->next;
    delete_next = p_list->next->next;
    delete delete_node;
    delete_previous->next = delete_next;
    return (SUCCESS);
}

status_t singly_linked_list::pop_end(data_t& end_data)
{
    node_t* run = nullptr;
    node_t* run_previous = nullptr;

    if(is_list_empty())
    {
        return (LIST_EMPTY);
    }
    run = p_list->next;
    run_previous = p_list;
    while(run->next)
    {
        run_previous = run;
        run = run->next;
    }
    end_data = run->data;
    run_previous->next = nullptr;
    delete run;
    run = nullptr;
    return (SUCCESS);
}
status_t singly_linked_list::remove_start()
{
    node_t* delete_node = nullptr;
    node_t* delete_previous = nullptr;
    node_t* delete_next = nullptr;

    if(is_list_empty())
    {
        return (LIST_EMPTY);
    }
    delete_node = p_list->next;
    delete_previous = p_list;
    delete_next = p_list->next->next;

    delete_previous->next = delete_next;
    delete delete_node;
    delete_node = nullptr;
    return (SUCCESS);
}

status_t singly_linked_list::remove_end()
{
    node_t* run = nullptr;
    node_t* run_previous = nullptr;
    if(is_list_empty())
    {
        return (LIST_EMPTY);
    }
    run = p_list->next;
    run_previous= p_list;
    while(run->next)
    {
        run_previous = run;
        run = run->next;
    }
    run_previous->next = nullptr;
    delete run;
    run = nullptr;
    return (SUCCESS);
}

status_t singly_linked_list::remove_data(data_t r_data)
{
    node_t* run = nullptr;
    node_t* run_previous = nullptr;
    
    run = p_list->next;
    run_previous = p_list;
    while(run)
    {
        if(run->data == r_data)
        {
            break;
        }
        run_previous = run;
        run = run->next;
    }
    if(run == nullptr)
    {
        return (LIST_DATA_NOT_FOUND);
    }
    run_previous->next = run->next;
    delete run;
    run = nullptr;
    return (SUCCESS);
}

status_t singly_linked_list::find_data(data_t f_data)const
{
    node_t* run = nullptr;
    run = p_list->next;
    while(run)
    {
        if(run->data == f_data)
        {
            return (TRUE);
        }
        run = run->next;
    }
    return FALSE;
}

status_t singly_linked_list::is_list_empty()const
{
    if(p_list->next == nullptr)
    {
        return TRUE;
    }
    return FALSE;
}

len_t singly_linked_list::get_list_length()const
{
    node_t* run = nullptr;
    run = p_list->next;
    int  len = 0;
    while(run)
    {
        len+=1;
        run = run->next;
    }
    return len;
}

void singly_linked_list::show_list(const std::string& msg)const
{
    node_t* run = nullptr;
    if(msg != "")
    {
        std::cout<<msg<<std::endl;
    }
    std::cout<<"\n[START] -> ";
    run = p_list->next;
    while(run)
    {   
        std::cout<<run->data<<" -> ";
        run = run->next;
    }
    std::cout<<"[END]\n"<<std::endl;
}

node_t* singly_linked_list:: get_node(data_t new_data)const
{
    return new node_t(new_data);
}

node_t* singly_linked_list::search_node(data_t s_data)const
{
    node_t* run = nullptr;
    run = p_list->next;
    while(run)
    {
        if(run->data == s_data)
        {
            return (run);
        }
        run = run->next;
    }
    return nullptr;

}

// std::ostream& operator<<(std::ostream& os , const singly_linked_list& other)
// {
//     node_t* run = nullptr;
//     os<<"\n[START] -> ";

//     run = other.p_list->get_next();
//     while(run)
//     {   
//         os<<run->get_data()<<" -> ";
//         run = run->get_next();
//     }
//     os<<"[END]\n"<<std::endl;
//     return os;
// }

// data_t node::get_data()const{
//     return this->data;
// }

// node_t* node::get_next()const{
//     return this->next;
// }


IList* IList::getListInstance()
{
    return new singly_linked_list();
}