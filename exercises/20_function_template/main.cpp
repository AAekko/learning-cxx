#include "../exercise.h"

// READ: 函数模板 <https://zh.cppreference.com/w/cpp/language/function_template>
// TODO: 将这个函数模板化
template <typename T>   // 这里的 T 可以暂时理解成一个“类型占位符”,也就是说，我们先不规定 a 和 b 一定是什么类型，等调用函数时再由编译器判断。
T plus(T a, T b) {
    return a + b;
}

int main(int argc, char **argv) {
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");   // u 表示这个数字是 unsigned int，也就是无符号整数，无符号整数通常只表示非负数。

    // THINK: 浮点数何时可以判断 ==？何时必须判断差值？
    // 计算机使用二进制保存浮点数只能保存一个近似值，所以不要要求两个浮点数完全相等，而是检查它们的差值是否足够小
    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");    // 为什么 1.25 + 2.5 == 3.75 可以直接比较？因为这些数字都可以写成二进制能够精确表示的分数：1.25 = 1 + 1/4，2.5  = 2 + 1/2，3.75 = 3 + 3/4。其中 1/2、1/4 都能用二进制精确表示，所以这些数的加法通常可以直接用 == 判断。（2的整数次方）
    // TODO: 修改判断条件使测试通过
    // 0.1、0.2 无法用二进制浮点数精确表示，应判断误差
    ASSERT(std::abs(plus(0.1, 0.2) - 0.3) < 1e-12, "How to make this pass?");  // std::abs是标准库中的绝对值函数

    return 0;
}
