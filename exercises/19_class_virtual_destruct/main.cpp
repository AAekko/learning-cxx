#include "../exercise.h"

// READ: 静态字段 <https://zh.cppreference.com/w/cpp/language/static>
// READ: 虚析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

struct A {
    // TODO: 正确初始化静态字段
    inline static int num_a = 0;      // 普通成员变量属于某一个具体对象，而静态成员变量属于整个类，所有对象共同使用一份。例如：A a1;A a2;
                                      // a1 和 a2 不会各自拥有一份 num_a，而是共同使用：A::num_a
                                      // 这里使用 inline static，是因为从 C++17 开始，可以这样直接在类里面初始化静态成员变量
    A() {
        ++num_a;
    }
    virtual ~A() {
        --num_a;
    }

    virtual char name() const {        // name()是虚函数
        return 'A';
    }
};
struct B final : public A {            // final 表示不允许再创建一个类继承 B
    // TODO: 正确初始化静态字段
    inline static int num_b = 0;

    B() {
        ++num_b;
    }
    ~B() override {
        --num_b;
    }

    char name() const final {          // 这里重构了函数name()
        return 'B';
    }
};

int main(int argc, char **argv) {
    auto a = new A;                    // new A 会创建一个 A 对象，并调用 A 的构造函数：++num_a;此时：A::num_a = 1，B::num_b = 0
    auto b = new B;                    // 因为 B 继承自 A，创建 B 时的顺序是：先调用 A 的构造函数，再调用 B 的构造函数。因此：A::num_a 增加 1，B::num_b 增加 1
    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");

    delete a;                          // a 是普通的 A 对象，只调用 A 的析构函数
    delete b;                          // 销毁派生类对象的顺序与构造顺序相反：先调用 B 的析构函数，再调用 A 的析构函数
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");
    
    // 下面三种声明写法含义完全相同：A *ab; A* ab; A * ab;
    A *ab = new B;// 派生类指针可以随意转换为基类指针，右边创建的是一个 B 对象，但是左边使用的是 A* 指针。创建这个 B 对象时：先构造 A 部分：A::num_a 变成 1，再构造 B 部分：B::num_b 变成 1
    // A *ab表示：声明一个名为 ab 的变量，它的类型是“指向 A 的指针”，也就是 A*。 new B表示：在内存中创建一个 B 对象，并返回这个对象的地址。
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()");

    // TODO: 基类指针无法随意转换为派生类指针，补全正确的转换语句
    // 这里*ab是对指针解引用，得到 ab 指向的对象，其表达式类型是 A&
    // dynamic_cast<B &>(*ab)检查这个对象实际上是不是一个 B
    // bb.name()调用 B::name()，结果是：'B'。如果实际对象不是 B，例如：A *ab = new A;B &bb = dynamic_cast<B &>(*ab)引用形式的 dynamic_cast 会转换失败并抛出异常
    B &bb = dynamic_cast<B &>(*ab); // bb 是一个 B& 类型的引用
    // Tip：引用与指针的区别
    // 引用：B& bb = object;
    // bb.name();          // 使用点号
    // 指针：B* p = &object;
    // p->name();          // 使用箭头
    ASSERT(bb.name() == 'B', "Fill in the correct value for bb->name()");

    // TODO: ---- 以下代码不要修改，通过改正类定义解决编译问题 ----
    delete ab;// 通过指针可以删除指向的对象，即使是多态对象。ab 的指针类型是 A*，但实际指向的是 B 对象。如果 A 的析构函数不是虚函数，程序通过 A* 删除 B 对象时，就不能保证正确调用 B 的析构函数。这属于未定义行为。
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    return 0;
}
