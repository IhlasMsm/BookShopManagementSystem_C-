#include <iostream>
#include <iomanip>
#include <cstring>
#include <limits>
#include <vector>

#define MAX_BOOKS 500

struct Book {
    char title[50];
    char author[30];
    float price;
    int copies;
};

struct BookOrder {
    char title[50];
    int quantity;
};

int numBooks = 0;
Book b[MAX_BOOKS];
std::vector<BookOrder> bookOrders;

void WelcomeMessage() {
    std::cout << "\n\n\n";
    std::cout << "\n\t\t********************************************************************************************\n";
    std::cout << "\n\t\t\t\t\tWelcome to Simple Book Management System\n";
    std::cout << "\n\t\t********************************************************************************************\n";
}

void showMenuOptions() {
    std::cout << "\n\n\t\tPlease select a menu option number:";
    std::cout << "\n\n\t\t1) Display this menu.";
    std::cout << "\n\t\t2) Show all available books.";
    std::cout << "\n\t\t3) Add a book to the book shop.";
    std::cout << "\n\t\t4) Search a book by title.";
    std::cout << "\n\t\t5) Display the total number of books.";
    std::cout << "\n\t\t6) Delete a book by title.";
    std::cout << "\n\t\t7) Order books.";
    std::cout << "\n\t\t8) View book orders.";
    std::cout << "\n\t\t9) Print quotation.";
    std::cout << "\n\t\t10) Add discount.";
    std::cout << "\n\t\t11) Exit from this book shop system.";
}

void addBook() {
    if (numBooks == MAX_BOOKS) {
        std::cout << "\n\t\tError: Book shop is full.\n";
    }
    else {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\n\t\t\tEnter book title: ";
        std::cin.getline(b[numBooks].title, 50);

        std::cout << "\t\t\tEnter book author: ";
        std::cin.getline(b[numBooks].author, 30);

        std::cout << "\t\t\tEnter book price: ";
        std::cin >> b[numBooks].price;

        std::cout << "\t\t\tEnter number of copies: ";
        std::cin >> b[numBooks].copies;

        numBooks++;
    }
}

void showBooks() {
    if (numBooks == 0) {
        std::cout << "\n\t\t\tThere are no books stored!!\n\n ";
    }
    else {
        std::cout << "\n\n\t\tList of books: ";
        for (int i = 0; i < numBooks; i++) {
            std::cout << "\n\t\t\tBook title: " << b[i].title;
            std::cout << "\t\t\tBook author: " << b[i].author;
            std::cout << "\t\t\tBook price: " << std::fixed << std::setprecision(2) << b[i].price;
            std::cout << "\n\t\t\tBook copies: " << b[i].copies << "\n";
        }
    }
}

void searchBook() {
    char title[50];
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n\n\t\tEnter book title to search: ";
    std::cin.getline(title, 50);

    int found = 0;

    for (int i = 0; i < numBooks; i++) {
        if (strcasecmp(b[i].title, title) == 0) {
            std::cout << "\n\t\t\tBook title: " << b[i].title;
            std::cout << "\t\t\tBook author: " << b[i].author;
            std::cout << "\t\t\tBook price: " << std::fixed << std::setprecision(2) << b[i].price;
            std::cout << "\n\t\t\tBook pages: " << b[i].copies;
            found = 1;
            break;
        }
    }

    if (!found) {
        std::cout << "\n\t\t\tBook not found.";
    }
}

void showNumberOfBooks() {
    std::cout << "\n\t\t\tNumber of books in the book shop: " << numBooks << "\n";
}

void deleteBook() {
    char title[50];
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n\n\t\tEnter book title to delete: ";
    std::cin.getline(title, 50);

    int found = 0;

    for (int i = 0; i < numBooks; i++) {
        if (strcasecmp(b[i].title, title) == 0) {
            found = 1;

            // Delete the book by shifting elements to the left
            for (int j = i; j < numBooks - 1; j++) {
                strcpy(b[j].title, b[j + 1].title);
                strcpy(b[j].author, b[j + 1].author);
                b[j].price = b[j + 1].price;
                b[j].copies = b[j + 1].copies;
            }

            numBooks--;
            std::cout << "\n\t\t\tBook deleted successfully.\n";
            break;
        }
    }

    if (!found) {
        std::cout << "\n\t\t\tBook not found. Deletion failed.\n";
    }
}

void orderBooks() {
    char title[50];
    int quantity;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n\n\t\tEnter book title to order: ";
    std::cin.getline(title, 50);

    int found = 0;

    for (int i = 0; i < numBooks; i++) {
        if (strcasecmp(b[i].title, title) == 0) {
            found = 1;

            std::cout << "\t\t\tEnter quantity: ";
            std::cin >> quantity;

            if (quantity > 0 && quantity <= b[i].copies) {
                BookOrder order;
                strcpy(order.title, title);
                order.quantity = quantity;
                bookOrders.push_back(order);

                std::cout << "\n\t\t\tOrder placed successfully.\n";
            }
            else {
                std::cout << "\n\t\t\tInvalid quantity. Order failed.\n";
            }
            break;
        }
    }

    if (!found) {
        std::cout << "\n\t\t\tBook not found. Order failed.\n";
    }
}

void viewBookOrders() {
    if (bookOrders.empty()) {
        std::cout << "\n\t\t\tNo book orders placed.\n";
    }
    else {
        std::cout << "\n\n\t\tList of book orders: ";
        for (const auto& order : bookOrders) {
            std::cout << "\n\t\t\tBook title: " << order.title;
            std::cout << "\t\t\tQuantity: " << order.quantity << "\n";
        }
    }
}

void printQuotation() {
    if (bookOrders.empty()) {
        std::cout << "\n\t\t\tNo book orders to generate a quotation.\n";
    }
    else {
        float totalCost = 0;
        std::cout << "\n\n\t\tQuotation:\n";

        for (const auto& order : bookOrders) {
            for (int i = 0; i < numBooks; i++) {
                if (strcasecmp(b[i].title, order.title) == 0) {
                    std::cout << "\n\t\t\tBook title: " << b[i].title;
                    std::cout << "\t\t\tQuantity: " << order.quantity;
                    std::cout << "\t\t\tPrice per copy: " << std::fixed << std::setprecision(2) << b[i].price;
                    std::cout << "\n\t\t\tTotal cost: " << std::fixed << std::setprecision(2) << (b[i].price * order.quantity);
                    totalCost += (b[i].price * order.quantity);
                    break;
                }
            }
        }

        std::cout << "\n\n\t\t\tTotal cost for all orders: " << std::fixed << std::setprecision(2) << totalCost << "\n";
    }
}

void addDiscount() {
    float discountPercentage;
    std::cout << "\n\t\t\tEnter discount percentage: ";
    std::cin >> discountPercentage;

    if (discountPercentage >= 0 && discountPercentage <= 100) {
        float discountFactor = 1 - (discountPercentage / 100);

        for (auto& order : bookOrders) {
            for (int i = 0; i < numBooks; i++) {
                if (strcasecmp(b[i].title, order.title) == 0) {
                    order.quantity = static_cast<int>(order.quantity * discountFactor);
                    break;
                }
            }
        }

        std::cout << "\n\t\t\tDiscount applied successfully.\n";
    }
    else {
        std::cout << "\n\t\t\tInvalid discount percentage.\n";
    }
}

void GoodByeMessage() {
    std::cout << "\n\n\t\t********************************************************************************************\n";
    std::cout << "\n\t\t\t\t\tThank You for using Simple Book Management System.\n";
    std::cout << "\n\t\t********************************************************************************************\n";
}

int authenticateUser() {
    char username[20];
    char password[20];

    std::cout << "\n\t\t\tEnter username: ";
    std::cin >> username;

    std::cout << "\t\t\tEnter password: ";
    std::cin >> password;

    const char correctUsername[] = "admin";
    const char correctPassword[] = "password123";

    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        return 1;
    }
    else {
        std::cout << "\n\t\t\tAuthentication failed. Invalid username or password.\n";
        return 0;
    }
}

int main() {
    int choice;
    int loggedIn = 0;

    WelcomeMessage();

    while (!loggedIn) {
        loggedIn = authenticateUser();
    }

    showMenuOptions();

    while (choice != 11) {
        std::cout << "\n\n\n\t\tEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            showMenuOptions();
            break;
        case 2:
            showBooks();
            break;
        case 3:
            addBook();
            break;
        case 4:
            searchBook();
            break;
        case 5:
            showNumberOfBooks();
            break;
        case 6:
            deleteBook();
            break;
        case 7:
            orderBooks();
            break;
        case 8:
            viewBookOrders();
            break;
        case 9:
            printQuotation();
            break;
        case 10:
            addDiscount();
            break;
        case 11:
            GoodByeMessage();
            break;
        default:
            std::cout << "\n\n\n\t\t\tINVALID INPUT!! Try again...";
        }
    }

    return 0;
}

