#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ostream>
#include <istream>

using namespace std;

class datatype {
    public:
        string type;
        string key;
        string stringValue;
        double number;
    friend void print(datatype data);
    friend string toString(datatype data);

    datatype (): number(0), stringValue(""), type("undefined") {}

    bool operator<(datatype &a) {
        if (a.type == "number") {
            return number < a.number;
        }
        else {
            return stringValue < a.stringValue;
        }

        cerr<<"there were some error while comparison"<<endl;
        exit(1);
    }

    bool operator>(datatype &a) {
        if (a.type == "number") {
            return number > a.number;
        }
        else {
            return stringValue > a.stringValue;
        }

        cerr<<"there were some error while comparison"<<endl;
        exit(1);
    }

    bool operator>(double num) {
        if (type == "number") {
            return number > num;
        }
        cerr<<"there were some error while comparison"<<endl;
        exit(1);
    }

    bool operator<(double num) {
        if (type == "number") {
            return number < num;
        }
        cerr<<"there were some error while comparison"<<endl;
        exit(1);
    }

    bool operator==(double num) {
        if (type == "number") {
            return number == num;
        }
        cerr<<"there were some error while comparison"<<endl;
        exit(1);
    }

    bool operator<=(double num) {
        if (type == "number") {
            return number <= num;
        }
        cerr<<"there were some error while comparison"<<endl;
        exit(1);
    }

    bool operator>=(double num) {
        if (type == "number") {
            return number >= num;
        }
        cerr<<"there were some error while comparison"<<endl;
        exit(1);
    }

    //########################################################

    bool operator>(string str) {
        return stringValue > str;
        
        // cerr<<"there were some error while comparison"<<endl;
        // exit(1);
    }

    bool operator==(string str) {
        return stringValue == str;
        
        // cerr<<"there were some error while comparison"<<endl;
        // exit(1);
    }

    bool operator<(string str) {
        return stringValue < str;
        
        // cerr<<"there were some error while comparison"<<endl;
        // exit(1);
    }

    datatype operator+(datatype a) {
        if (a.type == type && a.type == "string") {
            stringValue += a.stringValue;
             a.stringValue = stringValue;
            return a;
        }
        else if (a.type == type && a.type == "number") {
            number += a.number;
            a.number = number;
            return a;
        }

        cerr<<"there are error"<<endl;
        exit(1);
    }

    datatype operator-(datatype a) {
        if (a.type == type && a.type == "number") {
            number -= a.number;
            a.number = number;
            return a;
        }

        cerr<<"there are error"<<endl;
        exit(1);
    }

    datatype operator*(datatype a) {
        if (a.type == type && a.type == "number") {
            number *= a.number;
            a.number = number;
            return a;
        }

        cerr<<"there are error"<<endl;
        exit(1);
    }

    datatype operator/(datatype a) {
        if (a.type == type && a.type == "number") {
            number /= a.number;
            a.number = number;
            return a;
        }

        cerr<<"there are error"<<endl;
        exit(1);
    }

    datatype& operator=(double newValue) {
        type = "number";
        number = newValue;
        return *this;
    }

    datatype& operator=(string newValue) {
        type = "string";
        stringValue = newValue;
        return *this;
    }

};

string removeZeroes(string str) {
    size_t dot = str.find(".");
    if (dot != string::npos) {
        size_t last = str.size() - 1;
        while (str[last] == '0') { 
            last--;


            if (str[last] == '.') {
                last--;
                break;
            }
        }

        return str.substr(0,last + 1);
    }

    return str; 
}

void print(datatype data) {
    if (data.type == "number") {
        cout<<data.number;
    }
    else if (data.type == "string")  {
        cout<<data.stringValue;
    } else {
        cout<<"undefined"<< endl;
    }

    
}

string  toString(datatype data) {
    if (data.type == "number") {
        return removeZeroes(to_string(data.number));
    }
    else if (data.type == "string") {
        return data.stringValue;
    }

    return "undefined";
}

class object {
    private:
        unsigned int length = 0;
        datatype* array;
        bool isNumber(string number) {
                bool dot = false;
                for (int i = 0;i < number.length();i++) {
                    if (!isdigit(number[i])) {
                        if (dot) {
                            return false;
                        }
                        
                        if (number[i] == '.' && i != number.length() - 1) {
                            dot = true;
                        }
                        else {
                            return false;
                        }

                    }
                }

                return true;
            }
    public:
        void set(string key, string each) {
            datatype properties;
            properties.key = key;
            if (isNumber(each)) {
                properties.type = "number";
                properties.number = atof(each.c_str());
            }
            else {
                properties.type = "string";
            }
            properties.stringValue = each;
            length++;
            datatype* new_array = new datatype[length];
            for (int i = 0;i < length - 1;i++) {
                if (array[i].key == key) {
                    array[i].stringValue = each;
                    if (isNumber(each)) {
                        array[i].number = atoi(each.c_str());
                    }
                    length--;
                    return;
                }
                new_array[i] = array[i];
            }

            new_array[length - 1] = properties;

            array = new_array;
        }

        void set(string key, int each) {
            datatype properties;
            properties.key = key;
            properties.type = "number";
            properties.number = each;
            properties.stringValue = to_string(each);
            length++;
            datatype* new_array = new datatype[length];
            for (int i = 0;i < length - 1;i++) {
                if (array[i].key == key) {
                    array[i].number = each;
                    array[i].type = "number";
                    length--;
                    return;
                }
                new_array[i] = array[i];
            }

            new_array[length - 1] = properties;

            array = new_array;
        }

        datatype get(string key) {
            for (int i = 0;i < length;i++) {
                if (array[i].key == key) {
                    return array[i];
                }
            }

            cerr<<"Key named "<<key<<" is not there"<<endl;

            exit(1);
        }

        void remove(string key) {
            datatype* new_array = new datatype[length - 1];
            bool founded = false;
            for (int i = 0,j = 0;i < length;i++) {
                if (array->key == key) {
                    founded = true;
                    continue;
                }
                new_array[j] = array[i];
                j++;
            }

            if (!founded) {
                return;
            }

            array = new_array;
            length--;
        }

        friend void print(object obj); 
        friend string toString(object data);
};

string toString(object data) {
    string str = "";
    for (int i = 0;i < data.length - 1;i++) {
        str += data.array[i].key + ":" + toString(data.array[i]) + " ";
    }

    str += data.array[data.length - 1].key + ":" + toString(data.array[data.length - 1]);

    return str;
}

void print(object obj) {
    cout<<"{"<<endl;
    for (int i = 0;i < obj.length;i++) {
        if (obj.array[i].type == "number") {
            cout<<"\t"<<obj.array[i].key<<":"<<obj.array[i].number<<endl;
        }
        else {
            cout<<"\t"<<obj.array[i].key<<":"<<obj.array[i].stringValue<<endl;
        }
    }
    cout<<"}"<<endl;
}

class objectVector; 

class products {
    public:
        virtual objectVector filter(bool func(object data)) = 0;
        virtual datatype reduce(datatype func(object data, datatype b), datatype c) = 0;
} ;   

class objectVector: public products { 
    private:
        unsigned int length = 0;
        object* array;
    public:
        unsigned int size() {
            return length;
        }
        void add(object one) {
            length++;
            object* new_array = new object[length];
            for (int i = 0;i < length - 1;i++) {
                new_array[i] = array[i];
            }

            new_array[length - 1] = one;

            array = new_array;
        }

        void remove(unsigned int index) {
            if (index >= length) {
                cerr<<"index "<<index<<" is out of range in objectVector"<<endl;
                exit(1);
            }
            object* new_array = new object[length - 1];
            for (int i = 0,j = 0;i < length;i++) {
                if (i == index) {
                    continue;
                }
                new_array[j] = array[i];
                j++;
            }

            array = new_array;
            length--;
        }

        object at(unsigned int index) {
            if (index >= length) {
                cerr<<"index is out of range in objectVector"<<endl;
                exit(1);
            }

            return array[index];
        }

        objectVector filter(bool func(object data)) {
            objectVector vec;
            for (int i = 0;i < length;i++) {
                if (func(array[i])) {
                    vec.add(array[i]);
                }
            }

            return vec;
        }

        void sort(string key, bool reverse = false) {
            if (reverse) {
                for (int i = 0;i < length;i++) {
                    for (int j = length - 1;j > i;j--) {
                        datatype one = array[j].get(key);
                        datatype two = array[j - 1].get(key);
                        if (one > two) {
                            object c = array[j];
                            array[j] = array[j - 1];
                            array[j - 1] = c;
                        }                    
                    }
                }

                return;
            }

            for (int i = 0;i < length;i++) {
                for (int j = 0;j < length - i - 1;j++) {
                    datatype one = array[j].get(key);
                    datatype two = array[j + 1].get(key);
                    if (one > two) {
                        object c = array[j];
                        array[j] = array[j + 1];
                        array[j + 1] = c;
                    }                    
                }
            }

        }

        int index(bool func(object data)) {
            for (int i = 0;i < length;i++) {
                if (func(array[i])) {
                    return i;
                }
            }

            return -1;
        }

        datatype reduce(datatype func(object data, datatype b), datatype c) {
            for (int i = 0;i < length;i++) {
                c = func(array[i], c);
            }
            return c;
        }

        friend void print(objectVector vec);

        friend void writeFile(string url, string operation,objectVector vec);

        friend void WriteObjectVectorInFile(objectVector data);
};

void writeFile(string url, string operation,objectVector vec) {
    ofstream fout;
    if (operation == "w") {
        fout.open(url);
    }
    else if (operation == "a") {
        fout.open(url,std::ios_base::app);
    }
    for (int i = 0;i < vec.length;i++) {
        string str = toString(vec.array[i]);
        fout<<str;
        fout<<endl;
    }         
}

void writeFile(string url, string operation,datatype data) {
    ofstream fout;
    if (operation == "w") {
        fout.open(url);
    }
    else if (operation == "a") {
        fout.open(url,std::ios_base::app);
    }
    if (data.type == "number") {
        fout<<data.number<<endl;
    } else if (data.type == "string") {
        fout<<data.stringValue<<endl;
    } else {
        fout<<"undefined"<<endl;
    }  

}

void writeFile(string url, string operation,string data) {
    ofstream fout;
    if (operation == "w") {
        fout.open(url);
    }
    else if (operation == "a") {
        fout.open(url,std::ios_base::app);
    }
   fout<<data<<endl;

}

void print(objectVector vec) {
    cout<<"["<<endl;
    for (int i = 0;i < vec.length;i++) {
        print(vec.array[i]);
    }
    cout<<"]"<<endl;
}

objectVector readFileAndGetData(string url, unsigned int n) {
            ifstream fin(url);
            string each;
            string* keys = new string[n];
            
            for (int i = 0;i < n;i++) {
                fin>>keys[i];
            }

            objectVector objVector;

            object obj;
            int index = 0;
            while (fin>>each)
            {
                obj.set(keys[index],each);
                index++;
                if (index == n) {
                    index = 0;
                    objVector.add(obj);
                    object new_obj;
                    obj = new_obj;
                }
            }

            return objVector;

        }

void WriteObjectVectorInFile(objectVector data) {
    for (int i = 0;i < data.length;i++) {
        cout<<data.array<<endl;
    }
}
