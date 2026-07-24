#include "../exercise.h"

// READ: 枚举类型 <https://zh.cppreference.com/w/cpp/language/enum>

// `enum` 是 C 的兼容类型，本质上其对应类型的常量。
// 在 `enum` 中定义标识符等价于定义 constexpr 常量，
// 这些标识符不需要前缀，可以直接引用。
// 因此 `enum` 定义会污染命名空间。
// 如果没有手动指定数值，枚举会从 0 开始递增
enum ColorEnum : unsigned char {     //“: unsigned char”表示这个枚举使用 unsigned char 作为底层存储类型。enum ColorEnum的意思是定义了一个名为 ColorEnum 的类型，定义以后，ColorEnum 就可以像 int、double 一样放在变量名前面
//ColorEnum这个类型规定了变量用于表示颜色，其可用的枚举成员包括：COLOR_RED，COLOR_GREEN，COLOR_YELLOW，COLOR_BLUE。虽然这些枚举成员的底层是整数，但它们不只是普通整数，而是 ColorEnum 类型的值
//int number = 31;                   （int 类型）
//ColorEnum color = COLOR_RED;       （ColorEnum 类型）！虽然二者都可能保存数值 31，但含义不同：number 表示一个普通数字。color 表示一种颜色。
    COLOR_RED = 31, //31
    COLOR_GREEN,    //32
    COLOR_YELLOW,   //33
    COLOR_BLUE,     //34
};

// 有作用域枚举型是 C++ 引入的类型安全枚举。
// 其内部标识符需要带前缀引用，如 `Color::Red`。即Color加俩冒号。
// 作用域枚举型可以避免命名空间污染，并提供类型安全保证。
enum class Color : int {
    Red = COLOR_RED,
    Green,
    Yellow,
    Blue,
};

ColorEnum convert_by_pun(Color c) {
    // READ: <https://zh.cppreference.com/w/cpp/language/union>
    // `union` 表示在同一内存位置存储的不同类型的值。写入一个成员后，通常只能读取刚刚写入的成员！这块内存是他们共用的，所以写入一个成员会挤掉之前的成员。
    // 其常见用法是实现类型双关转换，即将一种类型的值转换为另一种无关类型的值。
    // 但这种写法实际上仅在 C 语言良定义，在 C++ 中是未定义行为。
    // 这是比较少见的 C++ 不与 C 保持兼容的特性。
    // READ: 类型双关 <https://tttapa.github.io/Pages/Programming/Cpp/Practices/type-punning.html>
    union TypePun {        //union 的大小通常等于其最大成员的大小。这段代码定义了一种名为 TypePun 的新类型，类似于定义 struct。区别在于，struct 的成员拥有各自的内存，而 union 的成员共用同一块内存。
        ColorEnum e;
        Color c;
    };                     //注意，定义类、结构体或联合体后都需要这个分号。

    TypePun pun;           //TypePun 是类型，pun 是变量名。所以这里是创建一个类型为 TypePun、名字为 pun 的变量。此时可以通过 . 访问它的成员！
    // TODO: 补全类型双关转换
    pun.c = c; 
    return pun.e;         //这就是“类型双关”：写入时把内存看作一种类型，读取时又把它看作另一种类型。因为pun是TypePun类型的变量
}

int main(int argc, char **argv) {
    ASSERT(convert_by_pun(Color::Red) == COLOR_RED, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Green) == COLOR_GREEN, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Yellow) == COLOR_YELLOW, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Blue) == COLOR_BLUE, "Type punning conversion");
    return 0;
}
