/*
*  ProjectTwo.cpp : This file contains the 'main' function.Program execution begins and ends there.
*  Daniel Schween
*  08-17-2024
*  CS 300 SNHU
*/

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <Windows.h>
#include <vector>

using namespace std;

const int GLOBAL_SLEEP_TIME = 5000; // constant for program to sleep after output
/*
* Struct to hold the course information
*/
struct Course {

    string courseId;
    string courseName;
    vector<string> prereqList; // Course prerequisites stored in a vector
};

/*
* Sorting method used to scan through and select specific course information
*/
class BinarySearchTree {

private:

    // Structures to hold and sort courses
    struct Node {
        Course course;
        Node* right;
        Node* left;

        // default constructor
        Node() {
            left = nullptr;
            right = nullptr;
        }

        // Initialize a node variable as a current course
        Node(Course currCourse) {
            course = currCourse;
            left = nullptr;
            right = nullptr;
        }
    };

    // Initialize a root node to iterate through the tree search
    Node* root;
    void inOrder(Node* node);
    int size = 0;

/**
*  Initialize variables used in Binary Search Tree sorting method
*/
public:
    BinarySearchTree();
    void InOrder();
    void Insert(Course aCourse);
    void Remove(string courseId);
    Course Search(string courseId);
    int Size();
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    this->root = nullptr;
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    inOrder(root);
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course thisCourse) {

    Node* currentNode = root;

    if (root == NULL) { // Root doesn't exist

        root = new Node(thisCourse); // Create new node

    }
    else {

        while (currentNode != NULL) { // Node exists

            if (thisCourse.courseId < currentNode->course.courseId) { // If true traverse new node to left

                if (currentNode->left == nullptr) {

                    currentNode->left = new Node(thisCourse);
                    currentNode = NULL;
                }
                else {

                    currentNode = currentNode->left; // CurrentNode to left is already true
                }
            }
            else {

                if (currentNode->right == nullptr) { // If all else is false, point and traverse to right 

                    currentNode->right = new Node(thisCourse); // New node to right of tree
                    currentNode = NULL;
                }
                else {

                    currentNode = currentNode->right; // All else is false, default current node to right of tree
                }
            }
        }
    }
    size++;
}

/**
 * Remove a Course
 */
void BinarySearchTree::Remove(string courseId) {
    Node* par = NULL;
    Node* curr = root;

    while (curr != NULL) {

        if (curr->course.courseId == courseId) {
            if (curr->left == NULL && curr->right == NULL) { // Logic if statement, no roots to left or right 
                if (par == NULL) {
                    root = nullptr; 
                }
                else if (par->left == curr) { // Root to left of tree node
                    par->left = NULL;
                }
                else {
                    par->right = NULL; // Root to right of tree node
                }
            }
            else if (curr->right == NULL) { // No root to the right
                if (par == NULL) {
                    root = curr->left; // Left root exists
                }
                else if (par->left == curr) {
                    par->left = curr->left;
                }
                else {
                    par->right = curr->left;
                }
            }
            else if (curr->left == NULL) {
                if (par == NULL) {
                    root = curr->right;
                }
                else if (par->left == curr) {
                    par->left = curr->right;
                }
                else {
                    par->right = curr->right;
                }
            }
            else {
                Node* suc = curr->right;

                while (suc->left != NULL) {
                    suc = suc->left;

                }
                // Remove current course
                Node successorData = Node(suc->course);
                Remove(suc->course.courseId);
                curr->course = successorData.course;
            }
            // Node found and removed
            return;
        }
        else if (curr->course.courseId < courseId) {
            par = curr;
            curr = curr->right;
        }
        else {
            par = curr;
            curr = curr->left;
        }
    }
    cout << "\nValue not found" << endl;
    return;
}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseId) {

    Course thisCourse;

    Node* currentNode = root;

    // Logic used to search for a course
    while (currentNode != NULL) {

        if (currentNode->course.courseId == courseId) {

            return currentNode->course;
        }
        else if (courseId < currentNode->course.courseId) {

            currentNode = currentNode->left;
        }
        else {

            currentNode = currentNode->right;
        }
    }

    // Course not found
    return thisCourse;
}

/*
* Method to help traverse through tree and print courseID and courseName
*/
void BinarySearchTree::inOrder(Node* node) {

    if (node == NULL) {

        return;
    }
    inOrder(node->left);

    // Print the node
    cout << node->course.courseId << ", " << node->course.courseName << endl;

    inOrder(node->right);
}

/*
*  Size of tree
*/
int BinarySearchTree::Size() {

    return size;
}

/*
* Split vector into course parameters ID, Name, and Prerequisite
*/
vector<string> Split(string lineFeed) {

    char delim = ',';

    lineFeed += delim; // Includes a delimiter at the end so last word is also read
    vector<string> lineTokens;
    string temp = "";
    for (int i = 0; i < lineFeed.length(); i++) // Iterate through the vector
    {
        if (lineFeed[i] == delim)
        {
            lineTokens.push_back(temp); // Store course parameters in a token
            temp = "";
            i++;
        }
        temp += lineFeed[i];
    }
    return lineTokens;
}

/*
* Function to load courses
*/
void loadCourses(string csvPath, BinarySearchTree* courseList) {
  
    // Create a data structure and add to the collection of courses 
    ifstream inFS; // ifstream to read file
    string line; // line feed 
    vector<string> stringTokens;
    csvPath = "CS300_ABCU_Academic_Advising_Program_Input.csv";
   

    inFS.open(csvPath); // Open the read file

    if (!inFS.is_open()) { // Small error handler
        cout << "Could not open file. Please check inputs. " << endl;
        return;
    }

    while (!inFS.eof()) {

        Course thisCourse; // Create a new struct for each "line"

        getline(inFS, line);
        stringTokens = Split(line); // Split the line into tokens via the delimiter

        if (stringTokens.size() < 2) { // Two tokens must exist

            cout << "\nError. Skipping line." << endl;
        }

        // Separate file data into 
        else {

            thisCourse.courseId = stringTokens.at(0);
            thisCourse.courseName = stringTokens.at(1);

            for (unsigned int i = 2; i < stringTokens.size(); i++) {

                thisCourse.prereqList.push_back(stringTokens.at(i));
            }

            // Push this course to the end
            courseList->Insert(thisCourse);
        }
    }

    inFS.close(); // Close the file
}

/*
* Course passed in to print courseID, courseName, and prereq
*/
void displayCourse(Course thisCourse) {

    cout << thisCourse.courseId << ", " << thisCourse.courseName << endl;
    cout << "Prerequisites: ";

    if (thisCourse.prereqList.empty()) {// If the list is empty then there are no prereq

        cout << "none" << endl;
    }
    else {

        for (unsigned int i = 0; i < thisCourse.prereqList.size(); i++) { // Iterate through prerequisite list

            cout << thisCourse.prereqList.at(i);

            if (thisCourse.prereqList.size() > 1 && i < thisCourse.prereqList.size() - 1) {// Put a comma for any elements greater than 1 to seperate parameters

                cout << ", ";
            }
        }
    }

    cout << endl;
}

/*
* Main function handling user input and output course parameters
*/
int main(int argc, char* argv[]) {

    // Process command line arguments
    string csvPath, thisCourseKey;

    // Load input csv file
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    case 3:
        csvPath = argv[1];
        thisCourseKey = argv[2];
        break;
    default:
        csvPath = "CS300_ABCU_Advising_Program_Input.csv";
    }

    // Define a table to hold all the courses
    BinarySearchTree* courseList = new BinarySearchTree();

    Course course;
    bool goodInput;
    int choice = 0;

    // Output menu selections
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Display All Courses" << endl;
        cout << "  3. Find Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";

        thisCourseKey = ""; // Clear the string        
        string anyKey = " "; // Clear the string
        choice = 0; // Clear the choice

        try {
            cin >> choice;

            if ((choice > 0 && choice < 5) || (choice == 9)) { // Limit the user menu inputs to good values
                goodInput = true;
            }
            else { // Throw error for catch
                goodInput = false;
                throw 1;
            }

            switch (choice) {
            case 1:

                // Load the courses
                loadCourses(csvPath, courseList);
                cout << courseList->Size() << " courses read" << endl;

                // Program sleeps for 5 seconds after outputting courses
                Sleep(GLOBAL_SLEEP_TIME);

                break;

            // Print course list in order
            case 2:
                courseList->InOrder();

                cout << "\nEnter \'y\' to continue..." << endl;

                cin >> anyKey;

                break;

            // Print specific course details
            case 3:

                cout << "\nWhat course do you want to know about? " << endl;
                cin >> thisCourseKey;

                course = courseList->Search(thisCourseKey);

                if (!course.courseId.empty()) {
                    displayCourse(course);
                }
                else {
                    cout << "\nCourse ID " << thisCourseKey << " not found." << endl;
                }

                // Program sleep after output
                Sleep(GLOBAL_SLEEP_TIME);

                break;

            // Exit program
            case 9:
                exit;
                break;

            default:

                throw 2;
            }
        }

        // Catch any input errors and try again
        catch (int err) {

            std::cout << "\nPlease check your input." << endl;

            // Sleep after error caught
            Sleep(GLOBAL_SLEEP_TIME);
        }

        // Clear the cin operator of extra input or any errors from bad input
        cin.clear();
        cin.ignore();

        // Clear the console and start a fresh menu
        system("cls");
    }

    cout << "Good bye." << endl;

    Sleep(GLOBAL_SLEEP_TIME); // Program sleep after console clears

    return 0;
} 

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu


