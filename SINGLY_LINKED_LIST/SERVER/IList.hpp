#ifndef _ILIST__HPP
#define _ILIST__HPP


#include<iostream>
#include<cstdlib>
#include<cassert>

typedef enum status{
    SUCCESS     =  1,
    TRUE        =  1,
    FALSE       =  0,
    LIST_DATA_NOT_FOUND     = 2,
    LIST_EMPTY              = 3
}status_t;

typedef int data_t;
typedef int len_t;


class IList
{
    public:
        virtual status_t insert_start(data_t new_data) = 0;
        virtual status_t insert_end(data_t new_data) = 0;
        virtual status_t insert_before(data_t existing_data , data_t new_data) = 0;
        virtual status_t insert_after(data_t existing_data , data_t new_data) = 0;
        
        virtual status_t get_start(data_t& start_data)const = 0;
        virtual status_t get_end(data_t& end_data)const = 0;
        
        virtual status_t pop_start(data_t& start_data) = 0;
        virtual status_t pop_end(data_t& end_data) = 0;
        virtual status_t remove_start() = 0;
        virtual status_t remove_end() = 0;
        virtual status_t remove_data(data_t r_data) = 0;


        virtual status_t find_data(data_t f_data)const = 0;
        virtual status_t is_list_empty()const = 0;
        virtual len_t get_list_length()const = 0;
        virtual void show_list(const std::string& msg = "")const = 0;
        static IList* getListInstance();
        virtual ~IList(){};

};
#endif
