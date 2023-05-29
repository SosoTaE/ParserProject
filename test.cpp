#include <iostream>
#include "tools.h" 

using namespace std;

bool func(object data) {
    return data.get("code") == "DEF456";
}

datatype reduceCallBack(object data, datatype b) {
    datatype price = data.get("price");
    datatype result = price + b;
    return result;
}



int main() {
    objectVector products = readFileAndGetData("./productList.txt", 3);
    objectVector providers = readFileAndGetData("./providerList.txt", 3);
    objectVector filtered = products.filter(func);
    print(filtered);
    datatype c;
    c = 0;  
    datatype sum = filtered.reduce(reduceCallBack,c);
    string text = "Total cost of products:" + toString(sum);
    cout<<endl; 
    print(sum);
    writeFile("./filtered.txt", "w", "The list is filtered according to code:DEF456");
    writeFile("./filtered.txt", "a",filtered);
    writeFile("./filtered.txt", "a", text);

}