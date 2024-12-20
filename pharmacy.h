#ifndef PHARMACY_H
#define PHARMACY_H
typedef struct pharmacy
{
    int medicineId;
    char medicineName[100];
    float medicineCost;
    int medicineStockQuantity;
    char medicineType[20];// tablet/injection
    char medicineDosage[100];
    struct pharmacy *next;
}pharmacy;


enum PharmacyMenuOption
{
    ADD_NEW_MEDICINE = 1,
    UPDATE_MEDICINE_DETAILS,
    DISPLAY_AVAILABLE_MEDICINES,
    SEARCH_MEDICINE_BY_ID,
    SEARCH_MEDICINE_BY_NAME,
    CHECK_STOCK,
    EXIT_PHARMACY_MANAGEMENT
};
enum MedicineDetailOption
{

    UPDATE_MEDICINE_NAME=1,
    UPDATE_MEDICINE_COST,
    UPDATE_MEDICINE_STOCK,
    UPDATE_MEDICINE_TYPE,
    UPDATE_MEDICINE_DOSAGE
};
void  loginAsPharmacyManagementUser();
void addMedicine();
void updateMedicineDetails();
void displayMedicineDetails();
void searchByMedicineId();
void searchByMedicineName();
void checkMedicineStock();

#endif // PHARMACY_H

