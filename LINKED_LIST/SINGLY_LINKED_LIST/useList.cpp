#include <iostream>
#include <cassert>
#include "list.hpp"

void test_for_data_definition_statement(void);
void test_for_dynamic_allocation(void);

void print_line()
{
    std::cout << "\n------------------------------------------------------------\n";
}

void print_section(const std::string& title)
{
    std::cout << "\n==================== " << title << " ====================\n";
}

int main(void)
{
    print_section("STATIC OBJECT TEST");
    test_for_data_definition_statement();

    print_section("DYNAMIC OBJECT TEST");
    test_for_dynamic_allocation();

    print_section("ALL TESTS COMPLETED");
    return 0;
}

// ------------------------------------------------------------

void test_for_data_definition_statement(void)
{
    data_t start_data, end_data, length;
    singly_linked_list S;

    print_section("EMPTY LIST TEST");

    assert(S.is_list_empty() == TRUE);
    assert(S.get_start(start_data) == LIST_EMPTY);
    assert(S.get_end(end_data) == LIST_EMPTY);
    assert(S.pop_start(start_data) == LIST_EMPTY);
    assert(S.pop_end(end_data) == LIST_EMPTY);
    assert(S.remove_start() == LIST_EMPTY);
    assert(S.remove_end() == LIST_EMPTY);
    assert(S.get_list_length() == 0);

    std::cout << " Empty list assertions passed\n";
    print_line();

    std::cout << "List: " << S;
    print_line();

    // Insert at start
    print_section("INSERT AT START");
    for (data_t i = 1; i <= 5; i++)
        assert(S.insert_start(i * 100) == SUCCESS);

    std::cout << "After insert_start:\n" << S;
    print_line();

    // Insert at end
    print_section("INSERT AT END");
    for (data_t i = 1; i <= 5; i++)
        assert(S.insert_end(i * 1000) == SUCCESS);

    std::cout << "After insert_end:\n" << S;
    print_line();

    // Insert before/after
    print_section("INSERT BEFORE / AFTER");
    assert(S.insert_after(100, 1) == SUCCESS);
    assert(S.insert_before(100, -1) == SUCCESS);

    std::cout << "After insert operations:\n" << S;
    print_line();

    // Get start/end
    print_section("GET START & END");
    assert(S.get_start(start_data) == SUCCESS);
    assert(S.get_end(end_data) == SUCCESS);

    std::cout << "Start Data: " << start_data << "\n";
    std::cout << "End Data  : " << end_data << "\n";
    print_line();

    // Pop operations
    print_section("POP OPERATIONS");

    assert(S.pop_start(start_data) == SUCCESS);
    std::cout << "Popped Start: " << start_data << "\n" << S;

    assert(S.pop_end(end_data) == SUCCESS);
    std::cout << "Popped End  : " << end_data << "\n" << S;

    print_line();

    // Remove operations
    print_section("REMOVE OPERATIONS");

    assert(S.remove_start() == SUCCESS);
    std::cout << "After remove_start:\n" << S;

    assert(S.remove_end() == SUCCESS);
    std::cout << "After remove_end:\n" << S;

    print_line();

    // Search + length
    print_section("SEARCH & LENGTH");

    assert(S.find_data(100) == TRUE);
    std::cout << " 100 found in list\n";

    length = S.get_list_length();
    std::cout << "Length: " << length << "\n";

    print_line();

    // Copy constructor
    print_section("COPY CONSTRUCTOR");

    singly_linked_list S1(S);
    std::cout << "S1 (copy of S):\n" << S1;

    // Copy assignment
    print_section("COPY ASSIGNMENT");

    singly_linked_list S2;
    S2 = S;

    std::cout << "S2 (assigned from S):\n" << S2;
}

// ------------------------------------------------------------

void test_for_dynamic_allocation(void)
{
    data_t start_data, end_data, length;
    singly_linked_list* pS = new singly_linked_list();

    print_section("EMPTY LIST TEST (DYNAMIC)");

    assert(pS->is_list_empty() == TRUE);
    assert(pS->get_list_length() == 0);

    std::cout << " Empty dynamic list OK\n";
    std::cout << *pS;

    print_line();

    // Insert
    print_section("INSERT OPERATIONS");

    for (data_t i = 1; i <= 5; i++)
        pS->insert_start(i * 100);

    for (data_t i = 1; i <= 5; i++)
        pS->insert_end(i * 1000);

    std::cout << *pS;
    print_line();

    // Insert before/after
    pS->insert_after(100, 1);
    pS->insert_before(100, -1);

    std::cout << "After insert_before/after:\n" << *pS;
    print_line();

    // Pop + remove
    print_section("POP & REMOVE");

    pS->pop_start(start_data);
    pS->pop_end(end_data);

    std::cout << "After pop operations:\n" << *pS;

    pS->remove_start();
    pS->remove_end();

    std::cout << "After remove operations:\n" << *pS;

    print_line();

    // Length
    length = pS->get_list_length();
    std::cout << "Length: " << length << "\n";

    print_line();

    // Move semantics
    print_section("MOVE SEMANTICS");

    singly_linked_list* pS1 = new singly_linked_list(std::move(*pS));
    
    std::cout << "pS1 (moved):\n" << *pS1;

    delete pS1;   // should be nullptr-safe
    delete pS;
}