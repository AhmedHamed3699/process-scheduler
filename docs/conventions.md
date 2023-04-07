# Conventions
this file will contain team conventions for this specific project

## 1. Naming Conventions
1. Mutable variable names should be in camel case
```CPP
int veryLongVariableName = 314;
```
2. Constants should be in uppercase
```CPP
#define PI  3.1465
const int LARGE_CONSTANT = 150;
```
3. Function Names classes, structs should be in Pascal Case
```CPP
void AddItem(const Entity& anEntity, const ItemType& value)
{
  anEntity.Add(value);
}
```
4. static member data in class should be prefixed with `s_`
```CPP
  ```CPP
class Entity
{
  static int s_RefCount = 0;
};
```
5. file name should be all in lower case separated by `-`
```
./dir
--/sample-folder
----/entity-class.cpp 
----/entity-class.h 
----/nvim.rc
```
6. output files sent by ref should be prefixed by `out`
```CPP
int FunctionWithManyReturns(int x, int y, int& outSum)
{
  outSum = x + y;
  return x * y;
}
```

## 2. Usage of classes and structs
you should a structs 
* when you want the data member to be public by default 
* when you want to represent a simple data structure like a mathematical vector
* you should avoid it when using inheritance
```CPP
struct Vec2D {
  double x,
  double y,
  double z

  Vec3D(int xCo, int yCo, int zCo) 
    :x(xCo), y(yCo), z(zCO)
  {  
  }
};
```

## 3. usage of enums
* you should write an enum when every trying to specify a state or a limited data set 
* if your enum is class specific you should write in the class to be bounded to its namespace
```CPP
class Process {
  enum ProcessState 
  {
    NEW = 0,
    RDY,
    RUN,
    BLK,
    TRM,
    ORPH
  }

  ProcessState state;

  void SetState(ProcessState stat)
  {
    if (stat == ProcessState::BLK)
      return;
    state = stat;
  }
}
