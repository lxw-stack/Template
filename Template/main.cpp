//
//  main.cpp
//  Template
//
//  Created by 李笑微 on 2023/2/21.
//

#include <iostream>
#include <typeinfo>
using namespace std;

//模版的实参推演
//T 包含了所有大的类型 返回值，所有形参的类型都取出来
template<typename T>
void func(T a){
    cout << typeid(T).name() << endl;
}
template<typename R, typename A1, typename A2>
void func2 (R (*a) (A1, A2)){
    cout << typeid(R).name() << endl;
    cout << typeid(A1).name() << endl;
    cout << typeid(A2).name() << endl;
}
template<typename R, typename T, typename A1, typename A2>
void func3 (R (T::*a) (A1, A2)){
    cout << typeid(R).name() << endl;
    cout << typeid(T).name() << endl;
    cout << typeid(A1).name() << endl;
    cout << typeid(A2).name() << endl;
}
int sum(int a, int b){return a+b;}
class Test{
public:
    int sum(int a, int b){return a+b;}
};
int main(int argc, const char * argv[]) {
    // insert code here...
    func(10);
    func("aaa");
    func(sum);//T函数指针类型
    func2(sum);
    func3(&Test::sum)
    return 0;
}


#if 0
//模版的完全特例化和非完全（部分）特例化
template<typename T>
class Vector{
public:
    Vector(){
        cout << "call Vector template init" <<endl;
    }
};
// 对char*类型提供的完全特例化版本
template<>
class Vector<char*>{
public:
    Vector(){
        cout << "call Vector<char*> init" <<endl;
    }
};
// 对指针类型提供的部分特例化版本
template<typename Ty>
class Vector<Ty*>{
public:
    Vector(){
        cout << "call Vector<Ty*> init" <<endl;
    }
};
// 针对函数指针类型（有返回值，有两个形参）提供的部分特例化版本
template<typename R, typename A1, typename A2>
class Vector<R(*)(A1, A2)>{
public:
    Vector(){
        cout << "call Vector<R(*)(A1, A2)> init" <<endl;
    }
};
// 针对函数类型（有一个返回值，有两个形参）提供的部分特例化版本
template<typename R, typename A1, typename A2>
class Vector<R(A1, A2)>{
public:
    Vector(){
        cout << "call Vector<R(A1, A2)> init" <<endl;
    }
};
int sum(int a, int b){return a+b;}
int main(int argc, const char * argv[]) {
    // insert code here...
    Vector<int> vec1;
    Vector<char*> vec2;
    Vector<int*> vec3;
    Vector<int(*)(int,int)> vec4;
    Vector<int(int,int)> vec5;//function
    
    //注意区分函数类型和函数指针类型
    typedef int(*PFUNC1)(int, int);
    PFUNC1 pfunc = sum;
    cout << pfunc(10, 20) << endl;
    
    typedef int PFUNC2(int, int);
    PFUNC2 *pfunc2 = sum;
    cout << (*pfunc)(10, 20) << endl;
    return 0;
}
#endif

#if 0
template<typename T>
bool compare(T a, T b){
    cout<<"template compare"<<endl;
    return a > b;
}
template<>
bool compare<const char*>(const char* a, const char* b){//完全特例化
    cout<<"compare<const char*>"<<endl;
    return strcmp(a,b) > 0;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    compare(10,20);//通过实参推演出形参int型，然后实例化处理整形的模版函数编译
    compare("aaa", "bbb");//T const char*,编译器比较的是字符串的地址大小，而不是字典序，所以需要特例化
    return 0;
}
#endif
