#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// CLASS: Vehicle
class Vehicle {
private:
    string vehicleNumber;
    string vehicleType;
    int parkingSlot;

public:
    // Constructor
    Vehicle(string num, string type) : vehicleNumber(num), vehicleType(type), parkingSlot(-1) {}

    // Getter functions
    string getVehicleNumber() const {
        return vehicleNumber;
    }

    string getVehicleType() const {
        return vehicleType;
    }

    int getParkingSlot() const {
        return parkingSlot;
    }

    // Setter function
    void setParkingSlot(int slot) {
        parkingSlot = slot;
    }

    // Display vehicle details
    void displayInfo() const {
        cout << left << setw(20) << vehicleNumber << setw(15) << vehicleType << setw(15) << (parkingSlot == -1 ? "Not Parked" : to_string(parkingSlot)) << endl;
    }
};

//CLASS: ParkingLot 
class ParkingLot {
private:
    int totalSlots;
    vector<Vehicle*> vehicles;
    vector<bool> slotAvailability;

public:
    // Constructor
    ParkingLot(int slots) : totalSlots(slots), slotAvailability(slots, true) {}

    // Add vehicle to parking lot
    void parkVehicle(Vehicle* vehicle) {
        for (int i = 0; i < totalSlots; ++i) {
            if (slotAvailability[i]) {
                slotAvailability[i] = false;
                 // Assign parking slot (1-based index)
                vehicle->setParkingSlot(i + 1); 
                vehicles.push_back(vehicle);
                cout << "Vehicle " << vehicle->getVehicleNumber() << " parked at slot " << (i + 1) << ".\n";
                return;
            }
        }
        cout << "Parking lot is full! Unable to park the vehicle.\n";
    }

    // Remove vehicle from parking lot
    void removeVehicle(string vehicleNumber) {
        for (int i = 0; i < vehicles.size(); ++i) {
            if (vehicles[i]->getVehicleNumber() == vehicleNumber) {
                int slot = vehicles[i]->getParkingSlot();
                // Make the slot available
                slotAvailability[slot - 1] = true; 
                vehicles.erase(vehicles.begin() + i);
                cout << "Vehicle " << vehicleNumber << " has left the parking lot from slot " << slot << ".\n";
                return;
            }
        }
        cout << "Vehicle not found in the parking lot.\n";
    }

    // Display all vehicles
    void displayAllVehicles() const {
        cout << left << setw(20) << "Vehicle Number" << setw(15) << "Vehicle Type" << setw(15) << "Parking Slot" << endl;
        cout << "-------------------------------------------------------------\n";
        for (const auto& vehicle : vehicles) {
            vehicle->displayInfo();
        }
    }
};

// MAIN FUNCTION 
int main() {
    // A parking lot with 5 slots
    ParkingLot parkingLot(5);  

    int choice;
    string vehicleNumber, vehicleType;
    do {
        cout << "\n===== Vehicle Parking System =====\n";
        cout << "1. Park Vehicle\n";
        cout << "2. Remove Vehicle\n";
        cout << "3. Display All Vehicles\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Park a vehicle
                cout << "Enter vehicle number: ";
                cin >> vehicleNumber;
                cout << "Enter vehicle type (Car/Bike): ";
                cin >> vehicleType;
                {
                    Vehicle* newVehicle = new Vehicle(vehicleNumber, vehicleType);
                    parkingLot.parkVehicle(newVehicle);
                }
                break;

            case 2:
                // Remove a vehicle
                cout << "Enter vehicle number to remove: ";
                cin >> vehicleNumber;
                parkingLot.removeVehicle(vehicleNumber);
                break;

            case 3:
                // Display all vehicles
                parkingLot.displayAllVehicles();
                break;

            case 4:
                cout << "Exiting the system...\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
