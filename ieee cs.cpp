#include <iostream>
#include <string>

using namespace std;

class School {
    private:
        struct Student {
            string id;
            string name;
            int age;
            string yearSem;
            string stream;
        };

        struct Class {
            string streamName;
            Student students[100];
            int studentCount;
        };

        Class classes[10];
        int classCount;

        string toLowerCase(string str) {
            for (char &ch : str) {
                ch = tolower(ch);
            }
            return str;
        }

    public:
        School() {
            classCount = 0;
        }

        void addClass() {
            if (classCount < 10) {
                string streamName;
                cout << "Enter class/stream name (e.g., BTech EXTC, BTI CE): ";
                cin.ignore();
                getline(cin, streamName);

                for (int i = 0; i < classCount; i++) {
                    if (toLowerCase(classes[i].streamName) == toLowerCase(streamName)) {
                        cout << "Class already exists.\n";
                        return;
                    }
                }

                classes[classCount].streamName = streamName;
                classes[classCount].studentCount = 0;
                classCount++;
                cout << "Class added successfully!\n";
            } else {
                cout << "Cannot add more classes, limit reached.\n";
            }
        }

        void addStudent() {
            if (classCount == 0) {
                cout << "No classes available. Please add a class first.\n";
                return;
            }

            cout << "\nAvailable streams:\n";
            for (int i = 0; i < classCount; i++) {
                cout << (i + 1) << ". " << classes[i].streamName << "\n";
            }

            int choice;
            cout << "Select a stream by number: ";
            cin >> choice;

            if (choice < 1 || choice > classCount) {
                cout << "Invalid choice.\n";
                return;
            }

            string stream = classes[choice - 1].streamName;

            if (classes[choice - 1].studentCount < 100) {
                cout << "Enter student ID (15 alphanumeric characters): ";
                cin >> classes[choice - 1].students[classes[choice - 1].studentCount].id;
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, classes[choice - 1].students[classes[choice - 1].studentCount].name);
                cout << "Enter student age: ";
                cin >> classes[choice - 1].students[classes[choice - 1].studentCount].age;
                cout << "Enter year and semester in 'year - sem' format (e.g., 2 - 1): ";
                cin.ignore();
                getline(cin, classes[choice - 1].students[classes[choice - 1].studentCount].yearSem);
                classes[choice - 1].students[classes[choice - 1].studentCount].stream = stream;
                classes[choice - 1].studentCount++;
                cout << "Student added successfully to class " << stream << "!\n";
            } else {
                cout << "Cannot add more students, class is full.\n";
            }
        }

        void displayStudents() {
            if (classCount == 0) {
                cout << "No classes available.\n";
                return;
            }

            for (int i = 0; i < classCount; i++) {
                cout << "\nClass/Stream: " << classes[i].streamName;
                if (classes[i].studentCount == 0) {
                    cout << "\nNo students in this class.\n";
                } else {
                    for (int j = 0; j < classes[i].studentCount; j++) {
                        cout << "\nStudent ID: " << classes[i].students[j].id;
                        cout << "\nName: " << classes[i].students[j].name;
                        cout << "\nAge: " << classes[i].students[j].age;
                        cout << "\nYear-Semester: " << classes[i].students[j].yearSem;
                        cout << "\nStream: " << classes[i].students[j].stream << "\n";
                    }
                }
            }
        }

        void displayStudentsOfStream() {
            if (classCount == 0) {
                cout << "No classes available.\n";
                return;
            }

            cout << "\nAvailable streams:\n";
            for (int i = 0; i < classCount; i++) {
                cout << (i + 1) << ". " << classes[i].streamName << "\n";
            }

            int choice;
            cout << "Select a stream by number: ";
            cin >> choice;

            if (choice < 1 || choice > classCount) {
                cout << "Invalid choice.\n";
                return;
            }

            cout << "\nStudents in " << classes[choice - 1].streamName << " stream:\n";
            if (classes[choice - 1].studentCount == 0) {
                cout << "No students in this stream.\n";
            } else {
                for (int i = 0; i < classes[choice - 1].studentCount; i++) {
                    cout << "\nStudent ID: " << classes[choice - 1].students[i].id;
                    cout << "\nName: " << classes[choice - 1].students[i].name;
                    cout << "\nAge: " << classes[choice - 1].students[i].age;
                    cout << "\nYear-Semester: " << classes[choice - 1].students[i].yearSem;
                    cout << "\nStream: " << classes[choice - 1].students[i].stream << "\n";
                }
            }
        }

        void updateStudent() {
            string id;
            cout << "Enter student ID to update: ";
            cin >> id;

            for (int i = 0; i < classCount; i++) {
                for (int j = 0; j < classes[i].studentCount; j++) {
                    if (toLowerCase(classes[i].students[j].id) == toLowerCase(id)) {
                        int updateChoice;
                        cout << "\nSelect detail to update:";
                        cout << "\n1. Name";
                        cout << "\n2. Age";
                        cout << "\n3. Year-Semester";
                        cout << "\n4. Course/Stream";
                        cout << "\nEnter choice: ";
                        cin >> updateChoice;

                        switch (updateChoice) {
                            case 1:
                                cout << "Enter new name: ";
                                cin.ignore();
                                getline(cin, classes[i].students[j].name);
                                cout << "Name updated successfully!\n";
                                break;
                            case 2:
                                cout << "Enter new age: ";
                                cin >> classes[i].students[j].age;
                                cout << "Age updated successfully!\n";
                                break;
                            case 3:
                                cout << "Enter new year and semester in 'year - sem' format (e.g., 2 - 1): ";
                                cin.ignore();
                                getline(cin, classes[i].students[j].yearSem);
                                cout << "Year-Semester updated successfully!\n";
                                break;
                            case 4: {
                                string newClass;
                                cout << "Enter new class/stream (e.g., BTech EXTC, BTI CE): ";
                                cin.ignore();
                                getline(cin, newClass);

                                bool classFound = false;
                                for (int k = 0; k < classCount; k++) {
                                    if (toLowerCase(classes[k].streamName) == toLowerCase(newClass)) {
                                        if (classes[k].studentCount < 100) {
                                            classes[k].students[classes[k].studentCount++] = classes[i].students[j];
                                            classes[k].students[classes[k].studentCount - 1].stream = newClass;

                                            for (int m = j; m < classes[i].studentCount - 1; m++) {
                                                classes[i].students[m] = classes[i].students[m + 1];
                                            }
                                            classes[i].studentCount--;
                                            cout << "Class updated and student moved successfully!\n";
                                            classFound = true;
                                        } else {
                                            cout << "Cannot move student. Target class is full.\n";
                                        }
                                        break;
                                    }
                                }
                                if (!classFound) {
                                    cout << "Class not found. Please add the class first.\n";
                                }
                                break;
                            }
                            default:
                                cout << "Invalid choice. No update made.\n";
                        }
                        return;
                    }
                }
            }
            cout << "Student ID not found.\n";
        }

        void deleteStudent() {
            string id;
            cout << "Enter student ID to delete: ";
            cin >> id;

            for (int i = 0; i < classCount; i++) {
                for (int j = 0; j < classes[i].studentCount; j++) {
                    if (toLowerCase(classes[i].students[j].id) == toLowerCase(id)) {
                        for (int k = j; k < classes[i].studentCount - 1; k++) {
                            classes[i].students[k] = classes[i].students[k + 1];
                        }
                        classes[i].studentCount--;
                        cout << "Student deleted successfully!\n";
                        return;
                    }
                }
            }
            cout << "Student ID not found.\n";
        }
};

int main() {
    School school;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Class\n";
        cout << "2. Add Student\n";
        cout << "3. Display Students\n";
        cout << "4. Display Students of a Specific Stream\n";
        cout << "5. Update Student\n";
        cout << "6. Delete Student\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                school.addClass();
                break;
            case 2:
                school.addStudent();
                break;
            case 3:
                school.displayStudents();
                break;
            case 4:
                school.displayStudentsOfStream();
                break;
            case 5:
                school.updateStudent();
                break;
            case 6:
                school.deleteStudent();
                break;
            case 7:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
