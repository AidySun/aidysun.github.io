---
layout: '../../layouts/MarkdownPost.astro'
title: '能否在 C++ 的构造函数中使用 this 指针'
pubDate: 2023-04-01
description: '构造函数没执行完，this不可以用？继承多态中父类能否用this指针触发多态调用？'
author: 'SZH'
tags: ["C++", "Development"]
theme: 'light'
featured: true
---

Simple answer is **yes**, with some attention in inheritance.

有人认为在构造函数中，对象的构造还没有完成，不能使用 this 指针。
其实
According to [Should you use the this pointer in the constructor?](https://isocpp.org/wiki/faq/ctors#using-this-in-ctors):

```text
Some people feel you should not use the this pointer in a constructor because the object is not fully formed yet. However you can use this in the constructor (in the {body} and even in the initialization list) if you are careful.

Here is something that always works: the {body} of a constructor (or a function called from the constructor) can reliably access the data members declared in a base class and/or the data members declared in the constructor’s own class. This is because all those data members are guaranteed to have been fully constructed by the time the constructor’s {body} starts executing.

```

Please pay attention to virtual functions:
```
The bottom line is this: even if the caller is constructing an object of a derived class, during the constructor of the base class, your object is not yet of that derived class. You have been warned.

Here is something that never works: the {body} of a constructor (or a function called from the constructor) cannot get down to a derived class by calling a virtual member function that is overridden in the derived class. If your goal was to get to the overridden function in the derived class, you won’t get what you want. Note that you won’t get to the override in the derived class independent of how you call the virtual member function: explicitly using the this pointer (e.g., this->method()), implicitly using the this pointer (e.g., method()), or even calling some other function that calls the virtual member function on your this object. 

```

```cpp
#include <iostream>

using namespace std;

class A {

public:
  A() {
    cout << "A() { \n";
    this->vf();
    this->f1();
    cout << "} \n";
  }

  ~A() {
    cout << "~A()\n";
  }

  virtual void vf() {
    cout << "  A's vf()\n";
  }

  void f1() {
    cout << "  A's f1()\n";
    vf();
  }
};

class B : public A {

public:
  B() {
    cout << "B() { \n";
    this->vf();
    this->f1();
    cout << "} \n";
  }
  
  ~B() {
    cout << "~B()\n";
  }

  virtual void vf() {
    cout << "  B's vf()\n";
  }

  void f1() {
    cout << "  B's f1()\n";
    vf();
  }
};

int main() {
  cout << "creat A a\n";
  A a;
  cout << "creat B b\n";
  B b;

  cout << "======\n";
  return 0;
}
```

output:

```
creat A a
A() { 
  A's vf()
  A's f1()
  A's vf()
} 
creat B b
A() { 
  A's vf() // 在B的构造过程中，父类A中的this调用的是A的virtual function 
  A's f1()
  A's vf() // 同样，在父类构造函数中间接调用的虚函数，也不会调用子类的虚函数
} 
B() { 
  B's vf()
  B's f1()
  B's vf()
} 
======
~B()
~A()
~A()
```
