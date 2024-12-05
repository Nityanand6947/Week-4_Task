#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Control{
    int id;     //UniqueID
    string type; //"Button" or "Slider"
    string state; //"visibel" or "invisible" or "disabled"

    Control(int a,string b,string c){
        id = a;
        type = b;
        state = c;
    }
};

class HMI_Status{
    vector<Control> dataInfo;

    public:

    void addControl(const Control& data){
        dataInfo.push_back(data);
    }

    void showStatus(){
        for(auto ele:dataInfo){
            cout<<"ID: "<<ele.id<<", ";
            cout<<"Type: "<<ele.type<<", ";
            cout<<"State: "<<ele.state<<" "<<endl;
        }
    }

    void findById(int id){
        auto it = find_if(dataInfo.begin(),dataInfo.end(),[&](const Control& data){
            return data.id == id;
        });

        if(it!=dataInfo.end()){
            cout<<"Data found..."<<endl;
            cout<<"ID: "<<it->id<<", ";
            cout<<"Type: "<<it->type<<", ";
            cout<<"State: "<<it->state<<" "<<endl;
        }else{
            cout<<"\nRequired ID not available";
        }
    }
     void findByState(string state){
        auto it = find_if(dataInfo.begin(),dataInfo.end(),[&](const Control& data){
            return data.state == state;
        });

        if(it!=dataInfo.end()){
            cout<<"Data found..."<<endl;
            cout<<"ID: "<<it->id<<", ";
            cout<<"Type: "<<it->type<<", ";
            cout<<"State: "<<it->state<<" "<<endl;
        }else{
            cout<<"\nRequired state not available";
        }
    }
    void findAdjacent(){
        auto it = adjacent_find(dataInfo.begin(),dataInfo.end(),[](const Control& a,const Control& b){
            return a.state == b.state;
        });
        if(it!=dataInfo.end()){
            cout<<"Adjacent found:\n";
            cout<<"ID: "<<it->id<<", ";
            cout<<"State: "<<it->state<<endl;
        }else{
            cout<<"Adjacent not found"<<endl;
        }
        
    }
    void countSlider(){
        int count = 0;
        auto it = count_if(dataInfo.begin(),dataInfo.end(),[&](const Control& data){
            if(data.state == "disabled" && data.type == "Slider"){
                count++;
            }
            return count;
        });
        cout<<"The number of sliders that are disabled: "<<count<<endl;
    }
    /*
    NOTE:
    count and find will not work on custom conditions 
    */
};
int main(){
    HMI_Status hmi;
    hmi.addControl(Control(4,"Slider","visible"));
    hmi.addControl(Control(5,"Slider","disabled"));
    hmi.addControl(Control(1,"Button","visible"));
    hmi.addControl(Control(7,"Slider","disabled"));
    hmi.addControl(Control(2,"Button","invisible"));
    hmi.addControl(Control(6,"Slider","invisible"));
    hmi.addControl(Control(3,"Button","disabled"));

    //hmi.showStatus();
    // hmi.findById(6);
    // hmi.findByState("invisible");
    // hmi.findAdjacent();
    hmi.countSlider();
}