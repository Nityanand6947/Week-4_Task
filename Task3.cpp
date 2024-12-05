#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Control
{
    int id;       // UniqueID
    string type;  //"Button" or "Slider"
    string state; //"visibel" or "invisible" or "disabled"

    Control() : id(0), type(""), state("") {}

    Control(int a, string b, string c)
    {
        id = a;
        type = b;
        state = c;
    }
};

class HMI_Status
{
    vector<Control> dataInfo;
    vector<Control> backup;
   

public:
    void addControl(const Control &data)
    {
        dataInfo.push_back(data);
    }

    void showStatus()
    {
        for (auto ele : dataInfo)
        {
            cout << "ID: " << ele.id << ", ";
            cout << "Type: " << ele.type << ", ";
            cout << "State: " << ele.state << " " << endl;
        }
    }
    void backupData()
    {
        copy(dataInfo.begin(), dataInfo.end(), back_inserter(backup));
        for (auto ele : backup)
        {
            cout << "ID: " << ele.id << ", ";
            cout << "Type: " << ele.type << ", ";
            cout << "State: " << ele.state << " " << endl;
        }
    }
    void setDisabled()
    {
        //NOTE: fill function won't work with objects.
        // Control temp(0,"","diabled");
        // fill(dataInfo.begin(), dataInfo.end(), temp);

        
        for (auto ele : dataInfo)
        {
            ele.state = "disabled";

            cout << "ID: " << ele.id << ", ";
            cout << "Type: " << ele.type << ", ";
            cout << "State: " << ele.state << " " << endl;
        }
    }
    void transformInvisible(){
         vector<Control> change(dataInfo.size());
        transform(dataInfo.begin(),dataInfo.end(),change.begin(),[](Control& data){
            if(data.type == "Slider"){
            data.state = "invisible";
            }
            return data;
        });

        for (auto ele : change)
        {
            cout << "ID: " << ele.id << ", ";
            cout << "Type: " << ele.type << ", ";
            cout << "State: " << ele.state << " " << endl;
        }
    }
    void replaceData(){
        //NOTE: replace and replace_if will not directly work with objects 
        //It will only work with the direct values 
        for (auto ele : dataInfo)
        {
            if(ele.state == "disabled"){
                ele.state = "enabled";
            }
            cout << "ID: " << ele.id << ", ";
            cout << "Type: " << ele.type << ", ";
            cout << "State: " << ele.state << " " << endl;
        }
    }
    void unusedDataRemoval(){
        //NOTE: replace will not work here directly but replace_if will work
        auto tempData = remove_if(dataInfo.begin(),dataInfo.end(),[](Control& data){
            return data.state == "invisible";
        });

        dataInfo.erase(tempData,dataInfo.end());

        showStatus();
    }
    void reverseLayout(){
        reverse(dataInfo.begin(),dataInfo.end());
         for (auto ele : dataInfo)
        {
            cout << "ID: " << ele.id << ", ";
            cout << "Type: " << ele.type << ", ";
            cout << "State: " << ele.state << " " << endl;
        }
    }
    void dataPartioned(){
        partition(dataInfo.begin(),dataInfo.end(),[](Control& data){
            return data.state=="visible";
        });
         for (auto ele : dataInfo)
        {
            cout << "ID: " << ele.id << ", ";
            cout << "Type: " << ele.type << ", ";
            cout << "State: " << ele.state << " " << endl;
        }
    }

    
};
int main()
{
    HMI_Status hmi;
    hmi.addControl(Control(4, "Slider", "visible"));
    hmi.addControl(Control(5, "Slider", "disabled"));
    hmi.addControl(Control(1, "Button", "visible"));
    hmi.addControl(Control(7, "Slider", "disabled"));
    hmi.addControl(Control(2, "Button", "invisible"));
    hmi.addControl(Control(9, "Button", "visible"));
    hmi.addControl(Control(6, "Slider", "invisible"));
    hmi.addControl(Control(3, "Button", "disabled"));
    hmi.addControl(Control(8, "Slider", "visible"));

    // hmi.backupData();
    // hmi.setDisabled();
    // hmi.transformInvisible();
    // hmi.replaceData();
    // hmi.unusedDataRemoval();
    // hmi.reverseLayout();
    hmi.dataPartioned();
}