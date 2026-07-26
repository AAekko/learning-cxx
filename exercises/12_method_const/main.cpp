#include "../exercise.h"

// READ: 有 cv 限定符的成员函数 <https://zh.cppreference.com/w/cpp/language/member_functions>
// Fibonacci是该类型的结构体的名字
struct Fibonacci {
    int numbers[11];
    // TODO: 修改方法签名和实现，使测试通过
    // constexpr 变量隐含 const，所以 FIB 是常量对象。常量对象只能调用 const 成员函数，因此 get 后面需要加 const。末尾的 const 修饰成员函数，表示函数中的 this 指向常量对象，不能修改对象的普通成员
    constexpr int get(int i) const{
        return numbers[i];
    }
};

int main(int argc, char **argv) {
    Fibonacci constexpr FIB{{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55}}; //FIB就是类型为Fibonacci的结构体
    ASSERT(FIB.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << FIB.get(10) << std::endl;
    return 0;
}
