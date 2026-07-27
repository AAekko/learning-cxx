#include "../exercise.h"

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>


class DynFibonacci {                                     // 内部零件，外部不能直接操作
    size_t *cache; // cache 是一个指针，它会指向一块"动态"创建的数组
    int cached;    // 下一个还没有计算的位置
    int capacity;  // 表示动态数组的容量

public:                                                  // 对外提供的操作方法
    // TODO: 实现动态设置容量的构造器,构造器会在对象创建时自动执行
    // capacity(capacity)这里看起来左右两边名字一样，但意思不同：成员变量 capacity(构造器参数 capacity).相当于：this->capacity = capacity;左边是对象自己的成员变量，右边是传进来的参数。
    DynFibonacci(int capacity): cache(new size_t[capacity]), cached(2),capacity(capacity) {
        ASSERT(capacity >= 2, "capacity should be at least 2");
        cache[0]= 0;
        cache[1]= 1;
    }

    // TODO: 实现复制构造器,复制构造器负责根据一个已有对象创建新对象!例如：DynFibonacci const fib_ = fib;这不是普通赋值，而是使用 fib 创建一个新的 fib_，因此会调用复制构造器。other 就代表被复制的对象，也就是这里的 fib!
    // 数组内容相同，但内存相互独立。这叫作“深拷贝”
    DynFibonacci(DynFibonacci const &other)
        : cache(new size_t[other.capacity]),
          cached(other.cached),
          capacity(other.capacity) {
        for (int i = 0; i < cached; ++i) {
            cache[i] = other.cache[i];
        }
    }


    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci(){
        delete[] cache;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    // NOTICE: 名字相同参数也相同，但 const 修饰不同的方法是一对重载方法，可以同时存在
    //         本质上，方法是隐藏了 this 参数的函数
    //         const 修饰作用在 this 上，因此它们实际上参数不同
    // 函数最后的 const 表示：这个方法不会修改对象的成员变量。即非 const 方法可以“查看并修改”；const 方法只能“查看”，不能改变对象！！！
    size_t get(int i) const {
        if (i < cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    DynFibonacci const fib_ = fib;                          // fib_ 是一个常量对象，不能调用可能修改对象的方法, 因此它会调用这个带 const 的版本. const 版本不会继续计算，只能读取已经缓存的结果。
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}
