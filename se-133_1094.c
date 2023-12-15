#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_MEMBERS 100
#define MAX_CLASSES 50
#define FILENAME "members.txt"

struct Member {
    int id;
    char name[50];
    char contact[15];
    char membershipType[20];
    int membershipStatus;
    double height;  // Added height for BMI calculation
    double weight;  // Added weight for BMI calculation
    double bmi;     // Added BMI
};

struct FitnessClass {
    int id;
    char className[50];
    char schedule[20];
    int maxCapacity;
    int currentAttendance;
    int trainerId;
};

// Function prototypes
void saveMembers(struct Member members[], int count);
void loadMembers(struct Member members[], int *count);
void saveClasses(struct FitnessClass classes[], int count);
void loadClasses(struct FitnessClass classes[], int *count);
void addMember(struct Member members[], int *count);
void displayMember(struct Member member);
void viewMembers(struct Member members[], int count);
void updateMembershipStatus(struct Member members[], int count);
void searchMember(struct Member members[], int count);
void generateReport(struct Member members[], int count);
void addFitnessClass(struct FitnessClass classes[], int *count);
void displayFitnessClass(struct FitnessClass fitnessClass);
void viewFitnessClasses(struct FitnessClass classes[], int count);
void enrollMember(struct Member members[], int memberCount, struct FitnessClass classes[], int classCount);
void simulatePayments(struct Member members[], int count);
void calculateBMI(struct Member *member);  // New function for BMI calculation

int main() {
    struct Member members[MAX_MEMBERS];
    int memberCount = 0;

    struct FitnessClass classes[MAX_CLASSES];
    int classCount = 0;

    // Load existing data from files
    loadMembers(members, &memberCount);
    loadClasses(classes, &classCount);

    int choice;
    do {
        printf("\n------ WELCOME TO ------\n");
        printf("\n------ Fayzu Gym Management System ------\n");
        printf("1. Member Management\n");
        printf("2. Fitness Class Management\n");
        printf("3. Enroll Member in Class\n");
        printf("4. Simulate Payments\n");
        printf("5. Calculate BMI\n");  // New option for BMI calculation
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Member Management
                do {
                    printf("\n------ Member Management ------\n");
                    printf("1. Add Member\n");
                    printf("2. View Members\n");
                    printf("3. Update Membership Status\n");
                    printf("4. Search Member\n");
                    printf("5. Generate Report\n");
                    printf("6. Back to Main Menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            addMember(members, &memberCount);
                            break;
                        case 2:
                            viewMembers(members, memberCount);
                            break;
                        case 3:
                            updateMembershipStatus(members, memberCount);
                            break;
                        case 4:
                            searchMember(members, memberCount);
                            break;
                        case 5:
                            generateReport(members, memberCount);
                            break;
                        case 6:
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                    }
                } while (choice != 6);
                break;

            case 2:
                // Fitness Class Management
                do {
                    printf("\n------ Fitness Class Management ------\n");
                    printf("1. Add Fitness Class\n");
                    printf("2. View Fitness Classes\n");
                    printf("3. Back to Main Menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            addFitnessClass(classes, &classCount);
                            break;
                        case 2:
                            viewFitnessClasses(classes, classCount);
                            break;
                        case 3:
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                    }
                } while (choice != 3);
                break;

            case 3:
                // Enroll Member in Class
                enrollMember(members, memberCount, classes, classCount);
                break;

            case 4:
                // Simulate Payments
                simulatePayments(members, memberCount);
                break;

            case 5:
                // Calculate BMI
                printf("\n------ BMI Calculation ------\n");
                viewMembers(members, memberCount);
                calculateBMI(members);
                break;

            case 6:
                // Exit
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    // Save data to files before exiting
    saveMembers(members, memberCount);
    saveClasses(classes, classCount);

    return 0;
}

void saveMembers(struct Member members[], int count) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %s %s %d %lf %lf %lf\n", members[i].id, members[i].name,
                members[i].contact, members[i].membershipType, members[i].membershipStatus, members[i].height, members[i].weight, members[i].bmi);
    }

    fclose(file);
}

void loadMembers(struct Member members[], int *count) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        // File doesn't exist, initialize count
        *count = 0;
        return;
    }

    while (fscanf(file, "%d %s %s %s %d %lf %lf %lf", &members[*count].id, members[*count].name,
                  members[*count].contact, members[*count].membershipType, &members[*count].membershipStatus,
                  &members[*count].height, &members[*count].weight, &members[*count].bmi) == 8) {
        (*count)++;
        if (*count >= MAX_MEMBERS) {
            printf("Warning: Maximum member limit reached.\n");
            break;
        }
    }

    fclose(file);
}

void saveClasses(struct FitnessClass classes[], int count) {
    FILE *file = fopen("classes.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %s %d %d %d\n", classes[i].id, classes[i].className,
                classes[i].schedule, classes[i].maxCapacity, classes[i].currentAttendance, classes[i].trainerId);
    }

    fclose(file);
}

void loadClasses(struct FitnessClass classes[], int *count) {
    FILE *file = fopen("classes.txt", "r");
    if (file == NULL) {
        // File doesn't exist, initialize count
        *count = 0;
        return;
    }

    while (fscanf(file, "%d %s %s %d %d %d", &classes[*count].id, classes[*count].className,
                  classes[*count].schedule, &classes[*count].maxCapacity, &classes[*count].currentAttendance, &classes[*count].trainerId) == 6) {
        (*count)++;
        if (*count >= MAX_CLASSES) {
            printf("Warning: Maximum class limit reached.\n");
            break;
        }
    }

    fclose(file);
}

void addMember(struct Member members[], int *count) {
    struct Member newMember;

    printf("Enter member name: ");
    scanf("%s", newMember.name);

    printf("Enter contact number: ");
    scanf("%s", newMember.contact);

    printf("Enter membership type: ");
    scanf("%s", newMember.membershipType);

    printf("Enter height (in meters): ");
    scanf("%lf", &newMember.height);

    printf("Enter weight (in kilograms): ");
    scanf("%lf", &newMember.weight);

    newMember.membershipStatus = 1; // Active by default

    newMember.id = *count + 1;

    calculateBMI(&newMember);  // Calculate BMI for the new member

    members[*count] = newMember;
    (*count)++;

    printf("Member added successfully!\n");
}

void calculateBMI(struct Member *member) {
    // BMI formula: weight (kg) / (height (m) * height (m))
    member->bmi = member->weight / (member->height * member->height);
    printf("BMI calculated: %.2lf\n", member->bmi);
}
void displayMember(struct Member member) {
    printf("ID: %d\n", member.id);
    printf("Name: %s\n", member.name);
    printf("Contact: %s\n", member.contact);
    printf("Membership Type: %s\n", member.membershipType);
    printf("Membership Status: %s\n", member.membershipStatus == 1 ? "Active" : "Inactive");
}

void viewMembers(struct Member members[], int count) {
    printf("------ All Members ------\n");
    for (int i = 0; i < count; i++) {
        displayMember(members[i]);
        printf("--------------------------\n");
    }
}

void updateMembershipStatus(struct Member members[], int count) {
    int memberId;
    printf("Enter member ID to update status: ");
    scanf("%d", &memberId);

    for (int i = 0; i < count; i++) {
        if (members[i].id == memberId) {
            members[i].membershipStatus = (members[i].membershipStatus == 1) ? 0 : 1;
            printf("Membership status updated successfully!\n");
            saveMembers(members, count); // Save changes to file
            return;
        }
    }

    printf("Member not found!\n");
}

void searchMember(struct Member members[], int count) {
    char searchName[50];
    printf("Enter member name to search: ");
    scanf("%s", searchName);

    for (int i = 0; i < count; i++) {
        if (strcmp(members[i].name, searchName) == 0) {
            displayMember(members[i]);
            return;
        }
    }

    printf("Member not found!\n");
}

void generateReport(struct Member members[], int count) {
    printf("------ Membership Report ------\n");
    printf("Total Members: %d\n", count);

    int activeMembers = 0;
    for (int i = 0; i < count; i++) {
        if (members[i].membershipStatus == 1) {
            activeMembers++;
        }
    }

    printf("Active Members: %d\n", activeMembers);
    printf("Inactive Members: %d\n", count - activeMembers);
    printf("-------------------------------\n");
}

void addFitnessClass(struct FitnessClass classes[], int *count) {
    struct FitnessClass newClass;

    printf("Enter class name: ");
    scanf("%s", newClass.className);

    printf("Enter class schedule: ");
    scanf("%s", newClass.schedule);

    printf("Enter maximum capacity: ");
    scanf("%d", &newClass.maxCapacity);

    printf("Enter trainer ID: ");
    scanf("%d", &newClass.trainerId);

    newClass.currentAttendance = 0;
    newClass.id = *count + 1;

    classes[*count] = newClass;
    (*count)++;

    printf("Fitness class added successfully!\n");
}

void displayFitnessClass(struct FitnessClass fitnessClass) {
    printf("ID: %d\n", fitnessClass.id);
    printf("Class Name: %s\n", fitnessClass.className);
    printf("Schedule: %s\n", fitnessClass.schedule);
    printf("Max Capacity: %d\n", fitnessClass.maxCapacity);
    printf("Current Attendance: %d\n", fitnessClass.currentAttendance);
    printf("Trainer ID: %d\n", fitnessClass.trainerId);
}

void viewFitnessClasses(struct FitnessClass classes[], int count) {
    printf("------ All Fitness Classes ------\n");
    for (int i = 0; i < count; i++) {
        displayFitnessClass(classes[i]);
        printf("--------------------------\n");
    }
}

void enrollMember(struct Member members[], int memberCount, struct FitnessClass classes[], int classCount) {
    int memberId, classId;

    printf("Enter member ID to enroll: ");
    scanf("%d", &memberId);

    printf("Enter fitness class ID: ");
    scanf("%d", &classId);

    if (memberId >= 1 && memberId <= memberCount && classId >= 1 && classId <= classCount) {
        // Valid member and class IDs
        struct Member *member = &members[memberId - 1];
        struct FitnessClass *fitnessClass = &classes[classId - 1];

        if (fitnessClass->currentAttendance < fitnessClass->maxCapacity) {
            // Enroll member in class
            fitnessClass->currentAttendance++;
            printf("Member %s enrolled in class %s successfully!\n", member->name, fitnessClass->className);
        } else {
            printf("Class %s is full. Enrollment failed.\n", fitnessClass->className);
        }
    } else {
        printf("Invalid member ID or fitness class ID. Enrollment failed.\n");
    }
}

void simulatePayments(struct Member members[], int count) {
    // Simulate a simple payment process (just marking as paid)
    int memberId;

    printf("Enter member ID to simulate payment: ");
    scanf("%d", &memberId);

    if (memberId >= 1 && memberId <= count) {
        // Valid member ID
        struct Member *member = &members[memberId - 1];
        member->membershipStatus = 1; // Mark as paid
        printf("Payment for member %s processed successfully!\n", member->name);
    } else {
        printf("Invalid member ID. Payment processing failed.\n");
    }
}