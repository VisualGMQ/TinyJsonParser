# JsonParser

使用纯C++11编写的Json解析器，将近600行，单头文件。

# 使用方法

## 头文件
```c++
#include "JsonParser.hpp"
```

## 解析Json

可以使用`JsonParser`类的构造函数，或者其`Parser()`方法：
```c++
string context;
//read json file to context;

JsonParser parser(context);
//或者
parser.Parse(context);
```

## 得到解析的结果

使用`JsonParser`类的`GetRoot()`方法可以得到最外层的`JsonObject`指针。
所有的Json对象都是`JsonObject`类型。

### JsonObject对象的使用

JsonObject对象有很多子类，分别是`IntJsonObj`，`FloatJsonObj`，`ObjectJsonObj`，`ArrayJsonObj`，`BoolJsonObj`，`NullJsonObj`。但是在使用的时候， `GetRoot()`函数返回的`JsonObject`对象会指向这些类的子类，隐藏内部细节。所以你只需要使用`JsonObject`对象即可。

通过`GetType()`来得到`JsonObjType`枚举的值，以判断JsonObject内部数据的类型，然后可以通过`SetXXX`和`ToXXX`来设置/得到相应项的值。对于值为null的JsonObject，会返回`nullptr`，并且不能设置值。
虽然可以设置值，但是由于这个库是json解析库，所以并不能将JsonObject对象写回文件（以后可能会增加此功能）。

对于数组和json对象，使用`GetElement()/GetValue()`来得到值。通过`GetSize()`来得到元素/键值对的个数。也可以通过`ToVector()/ToMap()`来直接获得内部数据。

使用`Print()`来打印出JsonObject的内容。

如果调用了和类型不符的`ToXXX/SetXXX`方法，或者对非数组，json对象调用`GetElement()/GetValue()`方法，会抛出`JsonParseException`异常，并在异常中说明出错原因。

JsonParse会自动回收内存，不要对得到的JsonObject进行delete。
