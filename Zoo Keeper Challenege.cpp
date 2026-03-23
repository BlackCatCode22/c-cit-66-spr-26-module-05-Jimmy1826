#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <sstream>

using namespace std
class Animal {
public:
    string name;
    string species;
    string sex;
    int age;
    string season;
    string color;
    string weight;
    string origin;

    Animal(int a, string s, string sp, string seas, string col, string w, string o)
        : age(a), sex(s), species(sp), season(seas), color(col), weight(w), origin(o) {
        name = "Unnamed"; // Names can be loaded from animalNames.txt later
    }

    void display() {
        cout << name << " (" << species << "), " << age << " years old, " << sex
             << ", " << color << ", " << weight << " from " << origin << endl;
    }
};
struct Node {
    Animal* data;
    Node* next;
    Node(Animal* a) : data(a), next(nullptr) {}
};
class SpeciesList {
public:
    Node* head;
    string speciesName;

    SpeciesList(string name) : head(nullptr), speciesName(name) {}

    void addAnimal(Animal* a) {
        Node* newNode = new Node(a);
        newNode->next = head;
        head = newNode;
    }

    void displayList() {
        cout << "\n--- " << speciesName << "s ---" << endl;
        Node* current = head;
        while (current) {
            current->data->display();
            current = current->next;
        }
    }
};

int main() {
    ifstream inputFile("arrivingAnimals.txt");
    if (!inputFile) {
        cerr << "Error: Could not open arrivingAnimals.txt" << endl;
        return 1;
    }
    SpeciesList hyenas("Hyena"), lions("Lion"), tigers("Tiger"), bears("Bear");

    string line;
    while (getline(inputFile, line)) {
        // Example line: 4 year old male hyena, born in spring, tan color, 70 pounds, from Friguia Park, Tunisia
        stringstream ss(line);
        string temp, sex, species, season, color, weight, origin;
        int age;

        ss >> age;
        ss >> temp >> temp;
        ss >> sex;
        ss >> species;
        if (species.back() == ',') species.pop_back();

        getline(ss, season, ',');
        getline(ss, color, ',');
        getline(ss, weight, ',');
        getline(ss, origin);

        Animal* newAnimal = new Animal(age, sex, species, season, color, weight, origin);

        // Sort into appropriate species list
        if (species == "hyena") hyenas.addAnimal(newAnimal);
        else if (species == "lion") lions.addAnimal(newAnimal);
        else if (species == "tiger") tigers.addAnimal(newAnimal);
        else if (species == "bear") bears.addAnimal(newAnimal);
    }

    // Output the organized lists
    hyenas.displayList();
    lions.displayList();
    tigers.displayList();
    bears.displayList();

    inputFile.close();
    return 0;
}