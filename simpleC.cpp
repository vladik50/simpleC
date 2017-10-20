#include <iostream>
using namespace std;
#include <string>
main (void){
float x;
float y;
float c;
std::string m;
//cin >> x;
//cin >> m;
//cin >> y;

cin >> x >> m >> y;

if(m=="-"){
  c=x-y;
cout << c << "\n";
}
else if(m=="+"){
  c=x+y;
cout << c << "\n";
}

else if(m=="*"){
  c=x*y;
cout << c << "\n";
}
else if(m=="/"){
  c=x/y;


try{
  if(x==0){
    throw 1;
  }

}
catch(int i){

cout << "Нельзя делить на ноль" << "\n";

}
try{
  if( y==0){
    throw 2;
  }

}

catch(int r){

cout << "Нельзя делить на ноль" << "\n";

}
if(x&&y!=0){
cout << c << "\n";
}
}
}
