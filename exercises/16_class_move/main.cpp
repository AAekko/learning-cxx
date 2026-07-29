#include "../exercise.h"

// READ: 左值右值（概念）<https://learn.microsoft.com/zh-cn/cpp/c-language/l-value-and-r-value-expressions?view=msvc-170>
// READ: 左值右值（细节）<https://zh.cppreference.com/w/cpp/language/value_category>
// READ: 关于移动语义 <https://learn.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170#move-semantics>
// READ: 如果实现移动构造 <https://learn.microsoft.com/zh-cn/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170>

// READ: 移动构造函数 <https://zh.cppreference.com/w/cpp/language/move_constructor>
// READ: 移动赋值 <https://zh.cppreference.com/w/cpp/language/move_assignment>
// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>
// 左值通常是有名字、可以继续使用的对象：DynFibonacci fib(12);这里的 fib 是左值。它有明确的名字和位置，可以多次使用：fib[5];fib[10];
// 右值通常表示临时值，或者即将被“搬走资源”的对象。例如：std::move(fib)。它把 fib 转换成一个可以被移动的右值。但要特别注意：std::move(fib)本身并没有移动任何东西。它只是告诉编译器：允许从 fib 中取走资源。真正转移资源的是移动构造函数或移动赋值运算符。
class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    // 构造函数 1
    DynFibonacci(int capacity): cache(new size_t[capacity]), cached(1) {    // 表示在运行时申请一个长度为 capacity 的数组
        cache[0] = 0;
        cache[1] = 1;
        ASSERT(capacity >= 2, "capacity should be at least 2")
    }

    // TODO: 实现移动构造器.接管 other 的缓存
    // DynFibonacci &&表示右值引用。other 就是即将被移动的原对象，这里对应 fib
    // 构造函数 2
    // 为什么构造函数都要和类名相同？        因为构造函数的任务就是创建和初始化这个类的对象！构造函数就是生产 DynFibonacci 产品的不同方法：生产方法虽然不同，但生产出来的都是 DynFibonacci，因此构造函数都叫 DynFibonacci。
    // 函数名字相同，参数不同。编译器通过“参数不同”来判断具体调用哪一个
    //          构造函数	                     参数	                 用途
    // DynFibonacci(int capacity)	        一个整数	           根据容量创建新对象
    // DynFibonacci(DynFibonacci&& other)	另一个对象	       移动另一个对象的资源
    DynFibonacci(DynFibonacci &&other) noexcept
        : cache(other.cache), cached(other.cached) {  // 让新对象也获得这个数组的地址。但是现在两个对象指向同一个数组，这是危险的。
        other.cache = nullptr;  // 所以马上执行other.cache = nullptr;最终，新对象 fib_ 接管了数组，原对象 fib 不再拥有数组。这就是资源所有权的转移。
        other.cached = 0;
    }


    // TODO: 实现移动赋值
    // 移动构造和移动赋值的区别是：DynFibonacci fib_ = std::move(fib)中fib_ 是一个正在创建的新对象，所以调用移动构造函数。   而：fib0 = std::move(fib1)中fib0 已经存在，所以调用移动赋值运算符。
    // NOTICE: ⚠ 注意移动到自身问题 ⚠
    // noexcept 表示这个函数承诺不会抛出异常。移动操作只是复制指针、修改指针和整数，正常情况下不会抛出异常。给移动构造和移动赋值加上 noexcept 也能让标准库更放心地使用移动操作。
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
    // 防止 fib0 = std::move(fib0)
    // &other是取得 other 的地址
    if (this != &other) {
        // 先释放自己原来的缓存
        delete[] cache;

        // 接管 other 的缓存
        cache = other.cache;
        cached = other.cached;

        // other 不再拥有缓存
        other.cache = nullptr;
        other.cached = 0;
    }

        return *this;
        // 例如：fib0 = std::move(fib1);this指向fib0，other表示fib1
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci(){
        delete[] cache;    // 注意cache是数组必须使用 delete[]，而不是普通的 delete
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t operator[](int i) {  
        // size_t 是 C/C++ 中一种专门用来表示“大小、数量、下标”的《非负整数》类型
        // 重载 operator[] 的目的，是让自定义的 DynFibonacci 对象可以像数组一样使用。如果不重载 operator[]，编译器不知道 fib[10] 是什么意思，因为 fib 不是数组，而是一个类对象。
        // 在这道题里，写成：fib[10]很符合直觉，意思就是“取得第 10 个斐波那契数”。
        // 当然也可以不重载，改成普通函数：size_t get(int i);然后调用：fib.get(10)。两种方法都能实现，只是 fib[10] 更像访问一个数列。
        ASSERT(i >= 0, "i should not be negative");
        for (; cached < i; ++cached) {
            cache[cached + 1] = cache[cached] + cache[cached - 1];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");  // 因此这个版本不能继续计算，只能读取已经缓存的结果，所以它先检查是否有缓存。
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache;  //cache 是一个指针。指针用作布尔值时：cache != nullptr  → true；cache == nullptr  → false
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci const fib_ = std::move(fib);  // 这里的 fib_ 是 const 对象。编译器会认为它不允许被修改，所以只能调用末尾带 const 的成员函数
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);
    fib0 = std::move(fib0);  //自己移动到自己会导致数据丢失
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
