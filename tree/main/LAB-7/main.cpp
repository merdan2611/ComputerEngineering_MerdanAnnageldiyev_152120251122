#include <iostream>
#include <fstream>
using namespace std;

struct Sensor {
    int sensor_id;
    float hot;
};

int main(){
    Sensor temp;
    cout << "Enter your student id: ";
    long long id;
    cin >> id;
    int n = id % 50;
    int e = n % 100;
    fstream file;
    file.open("sensors.bin", ios::in | ios::out | ios::binary);
    file.seekg( n * sizeof(temp));
    file.read ((char *)&temp , sizeof(temp));
    int old_val = temp.hot;
    int new_val = e + old_val;
    file.seekg( n * sizeof(temp));
    file.write((char*)&temp , sizeof(temp));
    temp.hot = e;
    file.close();
    fstream file2;
    file.open("152120251122_Quiz5.txt", ios::out);
    file << "Number: " << id << endl;
    file << "Sensor INdex Used in the Process: " << e<< endl;
    file << "First Temp: " << old_val << " -> " << "New Temp: " << new_val;


    




    return 0;
}