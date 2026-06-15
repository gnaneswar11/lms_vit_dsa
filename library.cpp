
/*
 * Copyright (c) 2026 Gnaneswar Bommu
 * All rights reserved.
 */

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <cassert>

using namespace std;

// -------------------- BOOK CLASS --------------------
class Book {
public:
    int id;
    string title;
    string author;
    bool issued;

    Book(int id, string title, string author)
        : id(id), title(title), author(author), issued(false) {}
};

// -------------------- LINKED LIST NODE --------------------
class BookNode {
public:
    shared_ptr<Book> book;
    BookNode* next;

    BookNode(shared_ptr<Book> b) : book(b), next(nullptr) {}
};

// -------------------- BST TREE --------------------
class TreeNode {
public:
    shared_ptr<Book> book;
    TreeNode* left;
    TreeNode* right;

    TreeNode(shared_ptr<Book> b) : book(b), left(nullptr), right(nullptr) {}
};

class BookBST {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, shared_ptr<Book> book) {
        if (!node) return new TreeNode(book);

        if (book->id < node->book->id)
            node->left = insert(node->left, book);
        else
            node->right = insert(node->right, book);

        return node;
    }

    shared_ptr<Book> search(TreeNode* node, int id) {
        if (!node) return nullptr;

        if (node->book->id == id)
            return node->book;

        if (id < node->book->id)
            return search(node->left, id);

        return search(node->right, id);
    }

public:
    BookBST() : root(nullptr) {}

    void insert(shared_ptr<Book> book) {
        root = insert(root, book);
    }

    shared_ptr<Book> search(int id) {
        return search(root, id);
    }
};

// -------------------- MOCK SQL DATABASE --------------------
class SQLDatabase {
private:
    unordered_map<int, shared_ptr<Book>> table;

public:
    void insert(shared_ptr<Book> book) {
        table[book->id] = book;
    }

    shared_ptr<Book> getBook(int id) {
        if (table.find(id) != table.end())
            return table[id];
        return nullptr;
    }

    int size() {
        return table.size();
    }
};

// -------------------- LIBRARY MANAGEMENT --------------------
class Library {
private:
    BookNode* head;
    BookBST bst;
    SQLDatabase db;

public:
    Library() : head(nullptr) {}

    void addBook(int id, string title, string author) {
        auto book = make_shared<Book>(id, title, author);

        // Linked List Insert
        BookNode* node = new BookNode(book);
        node->next = head;
        head = node;

        // BST Insert
        bst.insert(book);

        // Database Insert
        db.insert(book);
    }

    shared_ptr<Book> findBook(int id) {
        return bst.search(id);
    }

    void issueBook(int id) {
        auto book = findBook(id);

        if (book && !book->issued) {
            book->issued = true;
            cout << "Book Issued: " << book->title << endl;
        } else {
            cout << "Book unavailable." << endl;
        }
    }

    void returnBook(int id) {
        auto book = findBook(id);

        if (book && book->issued) {
            book->issued = false;
            cout << "Book Returned: " << book->title << endl;
        }
    }

    void displayBooks() {
        BookNode* temp = head;

        while (temp) {
            cout << temp->book->id << " | "
                 << temp->book->title << " | "
                 << temp->book->author << " | "
                 << (temp->book->issued ? "Issued" : "Available")
                 << endl;

            temp = temp->next;
        }
    }

    int databaseSize() {
        return db.size();
    }

    void load10kBooks() {
        for (int i = 1; i <= 10000; i++) {
            addBook(i, "Book_" + to_string(i), "Author_" + to_string(i));
        }
    }
};

// -------------------- MAIN --------------------
int main() {
    Library lib;

    cout << "Loading 10,000 books..." << endl;
    lib.load10kBooks();

    cout << "Database Size: " << lib.databaseSize() << endl;

    lib.issueBook(100);
    lib.returnBook(100);

    auto book = lib.findBook(9999);

    if (book) {
        cout << "Found Book: " << book->title << endl;
    }

    return 0;
}
