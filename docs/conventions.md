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
3. Function Name should be in Pascal Case
```CPP
void AddItem(const Entity& anEntity, const ItemType& value)
{
  anEntity.Add(value);
}
```
4. private member data in class should be prefixed with `m_`
```CPP
class Entity
{
private:
  m_Data,
  m_Top,
  m_Last
};
```
4. static member data in class should be prefixed with `s_`
```CPP
  ```CPP
class Entity
{
  static int s_RefCount = 0;
};
```