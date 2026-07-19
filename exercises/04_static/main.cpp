#include "../exercise.h"

// READ: `static` 关键字 <https://zh.cppreference.com/w/cpp/language/storage_duration>
// THINK: 这个函数的两个 `static` 各自的作用是什么？
// 第一个`static`保证这个函数是当前文件的“私有函数”，不加`static`的话这个函数可能对其他 .cpp 文件开放。
// 第二个`static`修饰的是函数内部的局部变量 static_ ，使得 static_ 成为局部静态变量 ，它具有两个重要特点：1.只在第一次执行到这行代码时初始化。 2.函数结束后不会被销毁，会记住上一次的值。
static int func(int param) {
    static int static_ = param;
    // std::cout << "static_ = " << static_ << std::endl;
    return static_++;    // return static_++ 会先返回当前值，再将它加一，所以依次返回 5、6、7、8、9。
}

int main(int argc, char **argv) {
    // TODO: 将下列 `?` 替换为正确的数字
    ASSERT(func(5) == 5, "static variable value incorrect");
    ASSERT(func(4) == 6, "static variable value incorrect");
    ASSERT(func(3) == 7, "static variable value incorrect");
    ASSERT(func(2) == 8, "static variable value incorrect");
    ASSERT(func(1) == 9, "static variable value incorrect");
    return 0;
}
