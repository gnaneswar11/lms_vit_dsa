
#include <iostream>
#include <cassert>
#include "library.cpp"

using namespace std;

void testAddBook() {
    Library lib;
    lib.addBook(1, "C++", "Bjarne");

    auto book = lib.findBook(1);

    assert(book != nullptr);
    assert(book->title == "C++");

    cout << "testAddBook Passed" << endl;
}

void testIssueBook() {
    Library lib;
    lib.addBook(2, "DSA", "Author");

    lib.issueBook(2);

    auto book = lib.findBook(2);

    assert(book->issued == true);

    cout << "testIssueBook Passed" << endl;
}

void testReturnBook() {
    Library lib;
    lib.addBook(3, "OS", "Author");

    lib.issueBook(3);
    lib.returnBook(3);

    auto book = lib.findBook(3);

    assert(book->issued == false);

    cout << "testReturnBook Passed" << endl;
}

void test10kBooks() {
    Library lib;
    lib.load10kBooks();

    assert(lib.databaseSize() == 10000);

    auto book = lib.findBook(9876);

    assert(book != nullptr);

    cout << "test10kBooks Passed" << endl;
}

int main() {
    testAddBook();
    testIssueBook();
    testReturnBook();
    test10kBooks();

    cout << "All Unit Tests Passed Successfully!" << endl;

    return 0;
}
