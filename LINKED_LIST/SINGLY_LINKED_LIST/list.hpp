#ifndef _LIST__HPP
#define _LIST__HPP

#include<iostream>
#include<cstdlib>

enum status{
    SUCCESS     = 1,
    TRUE        = 1,
    FALSE       = 0,
    LIST_DATA_NOT_FOUND = 2,
    LIST_EMPTY          = 3
};

typedef enum status status_t;
typedef int data_t;
typedef struct node node_t;
typedef node_t list_t;
typedef data_t len_t;

class node
{
    friend class singly_linked_list;
    private :
        int data;
        node* next;
    public :
        node(int _data = 0)
        {
            data = _data;
            next = nullptr;
        }
        data_t get_data()const;
        node_t* get_next()const;
};

class singly_linked_list
{
    
    private:
        list_t* p_list;
    public:
        singly_linked_list();
        singly_linked_list(const singly_linked_list& other);
        singly_linked_list& operator=(const singly_linked_list& other);
        singly_linked_list(singly_linked_list&& other)noexcept;
        singly_linked_list& operator=(singly_linked_list&& other);
        
        status_t insert_start(data_t new_data);
        status_t insert_end(data_t new_data);
        status_t insert_after(data_t existing_data , data_t new_data);
        status_t insert_before(data_t existing_data ,data_t new_data);
        
        status_t get_start(int& start_data)const;
        status_t get_end(int& end_data)const;
        
        status_t pop_start(int& start_data);
        status_t pop_end(int& end_data);
        status_t remove_start();
        status_t remove_end();
        status_t remove_data(data_t r_data);

        status_t find_data(data_t f_data)const;
        status_t is_list_empty()const;
        len_t get_list_length()const;
        void show_list(const char* msg = 0)const;
        friend std::ostream& operator<<(std::ostream& os , const singly_linked_list& other);
        ~singly_linked_list();
    private :
        node_t* get_node(data_t new_data)const;
        node_t* search_node(data_t s_data)const;
        
};


#endif