#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<string> stappen;
vector<string> inventory;
map<string, bool> itemsVerzameld = {
    {"fakkel", false},
    {"sleutel", false},
    {"touw", false}
};
int vorigeKamer = 0;

int main() {
    string richting;

    cout << "Welkom in het doolhof! Typ een kompasrichting (noord, oost, zuid, west) om te bewegen.\n";

    kamer1:
    vorigeKamer = 1;
    cout << "\nJe bent in kamer 1. Er is een deur naar het zuiden\n";
    cin >> richting;
    stappen.push_back(richting);
    if (richting == "zuid") goto kamer2;
    cout << "Ongeldige richting! Probeer opnieuw.\n";
    goto kamer1;

    kamer2:
    vorigeKamer = 2;
    cout << "\nJe bent in kamer 2. Je kunt naar het zuiden, noorden of oosten.\n";
    cin >> richting;
    stappen.push_back(richting);
    if (richting == "zuid") goto kamer5;
    if (richting == "oost") goto kamer3;
    if(richting == "noord") goto kamer1;
    cout << "Ongeldige richting! Probeer opnieuw.\n";
    goto kamer2;

    kamer3:
    vorigeKamer = 3;
    cout << "\nJe bent in kamer 3. Je kan verplaatsen naar het zuiden of westen.\n";
    if (!itemsVerzameld["touw"]) {
        inventory.emplace_back("touw");
        itemsVerzameld["touw"] = true;
        cout << "Je hebt een touw toegevoegd aan je inventory!\n";
    }
    cin >> richting;
    stappen.push_back(richting);
    if (richting == "west") goto kamer2;
    if (richting == "zuid") goto kamer4;
    cout << "Ongeldige richting! Probeer opnieuw.\n";
    goto kamer3;

    kamer4:
    cout << "\nJe bent in kamer 4. Je kunt naar het westen, noorden en zuiden.\n";
    if (!itemsVerzameld["fakkel"]) {
        cout << "Je hebt een fakkel nodig om hier door te kunnen gaan!\n";
        if (vorigeKamer == 3) goto kamer3;
        if (vorigeKamer == 5) goto kamer5;
    }
    vorigeKamer = 4;
    cin >> richting;
    stappen.push_back(richting);
    if (richting == "noord") goto kamer3;
    if (richting == "west") goto kamer5;
    if (richting == "zuid") goto kamer6;
    cout << "Ongeldige richting! Probeer opnieuw.\n";
    goto kamer4;

    kamer5:
    cout << "\nJe bent in kamer 5. Hier vind je een touw. Je kunt naar het noorden, westen en oosten.\n";
    if (!itemsVerzameld["touw"]) {
        cout << "Je hebt een touw nodig om hier doorheen te kunnen!\n";
        if (vorigeKamer == 2) goto kamer2;
        if (vorigeKamer == 4) goto kamer4;
        if (vorigeKamer == 7) goto kamer7;
    }if (!itemsVerzameld["fakkel"]) {
        inventory.emplace_back("fakkel");
        itemsVerzameld["fakkel"] = true;
        cout << "Je hebt een fakkel toegevoegd aan je inventory!\n";
    }
    vorigeKamer = 5;
    cin >> richting;
    stappen.push_back(richting);
    if (richting == "noord") goto kamer2;
    if (richting == "oost") goto kamer4;
    if (richting == "west") goto kamer7;
    cout << "Ongeldige richting! Probeer opnieuw.\n";
    goto kamer5;

    kamer6:
    vorigeKamer = 6;
    cout << "\nJe bent in kamer 6. Je kunt naar het noorden.\n";
    if (!itemsVerzameld["sleutel"]) {
        inventory.emplace_back("sleutel");
        itemsVerzameld["sleutel"] = true;
        cout << "Je hebt een sleutel toegevoegd aan je inventory!\n";
    }
    cin >> richting;
    stappen.push_back(richting);
    if(richting == "noord") goto kamer4;
    cout << "Ongeldige richting! Probeer opnieuw.\n";
    goto kamer6;

    kamer7:
    vorigeKamer = 7;
    cout << "\nJe bent in kamer 7. Je kunt naar het oosten en zuiden.\n";
    cin >> richting;
    stappen.push_back(richting);
    if(richting == "oost") goto kamer5;
    if(richting == "zuid") goto kamer8;
    cout << "Ongeldige richting! Probeer opnieuw.\n";
    goto kamer7;

    kamer8:
    cout << "\nJe bent in kamer 8. Je kunt naar het zuiden en het noorden.\n";
    if (!itemsVerzameld["sleutel"]) {
        cout << "Je hebt een touw nodig om hier doorheen te kunnen!\n";
        goto kamer7;
    }
    vorigeKamer = 8;
    cin >> richting;
    stappen.push_back(richting);
    if (richting == "noord") goto kamer7;
    if (richting == "zuid") goto eind;
    cout << "Ongeldige richting! Probeer opnieuw.\n";
    goto kamer8;

    eind:
    cout << "\nGefeliciteerd! Je hebt het doolhof voltooid.\n";
    cout << "Je hebt de volgende richtingen genomen: ";
    for (const string& stap : stappen) {
        cout << stap << " ";
    }
    cout << endl;

    return 0;
}
