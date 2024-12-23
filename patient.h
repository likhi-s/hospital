#ifndef PATIENT_H
#define PATIENT_H

typedef struct patient
{
    int patientId;
    char patientName[50];
    char patientGender[10];
    int patientAge;
    char patientAddress[100];
    char patientContactNumber[15];
    char patientEmergencyContactNumber[15];
    struct patient *next;
} patient;


enum PatientManagementMenu
{
    REGISTER_PATIENT = 1,
    UPDATE_PATIENT_DETAILS,
    DISPLAY_AVAILABLE_PATIENTS,
    SEARCH_PATIENT_BY_ID,
    SEARCH_PATIENT_BY_NAME,
    SORT_BY_PATIENT_ID,
    EXIT_PATIENT_MANAGEMENT
} ;
enum PatientUpdateDetail
{
    UPDATE_PATIENT_NAME=1,
    UPDATE_PATIENT_GENDER,
    UPDATE_PATIENT_AGE,
    UPDATE_PATIENT_ADDRESS,
    UPDATE_PATIENT_CONTACT_NUMBER,
    UPDATE_PATIENT_EMERGENCY_CONTACT_NUMBER
};



void loginAsPatientManagementUser();
void registerPatient();
void displayPatientDetails();
void searchByPatientId();
void searchByPatientName();
void updatePatientDetails();
//void saveData();
//void loadPatientsFromFile();
#endif // PATIENT_H
