[Code](https://godbolt.org/z/To3WcbjxP)

注意：godbolt平台上使用的编译器为：x86-64 gcc 11.2

```C++
// Type your code here, or load an example.
int square(int num) {
    return 0;
}

int square() {
    return 0;
}

int square(int num, int num1) {
    return 0;
}
```

```Assembly
square(int):
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], edi
        mov     eax, 0
        pop     rbp
        ret
square():
        push    rbp
        mov     rbp, rsp
        mov     eax, 0
        pop     rbp
        ret
square(int, int):
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], edi
        mov     DWORD PTR [rbp-8], esi
        mov     eax, 0
        pop     rbp
        ret
```

对比两个函数汇编代码的区别，可以发现带int参数的函数，多了一条汇编指令：

> mov     DWORD PTR [rbp-4], edi

也就是将edi寄存器（传入int参数）内容复制到堆栈中，第三个函数类似。

进一步实验，验证多少个参数会使用寄存器传递参数，代码如下：

```C++
int square(int num0, int num1, int num2, int num3, int num4
, int num5, int num6, int num7) {
    return num0 + num1 + num2 + num3 + num4 + num5 + num6 + num7;
}
```

```Assembly
square(int, int, int, int, int, int, int, int):
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], edi
        mov     DWORD PTR [rbp-8], esi
        mov     DWORD PTR [rbp-12], edx
        mov     DWORD PTR [rbp-16], ecx
        mov     DWORD PTR [rbp-20], r8d
        mov     DWORD PTR [rbp-24], r9d
        mov     edx, DWORD PTR [rbp-4]
        mov     eax, DWORD PTR [rbp-8]
        add     edx, eax
        mov     eax, DWORD PTR [rbp-12]
        add     edx, eax
        mov     eax, DWORD PTR [rbp-16]
        add     edx, eax
        mov     eax, DWORD PTR [rbp-20]
        add     edx, eax
        mov     eax, DWORD PTR [rbp-24]
        add     edx, eax
        mov     eax, DWORD PTR [rbp+16]
        add     edx, eax
        mov     eax, DWORD PTR [rbp+24]
        add     eax, edx
        pop     rbp
        ret
```

由上面点汇编代码可以看到第7、8个参数是从堆栈的+16和+24位置读取，而一开始从寄存器复制到堆栈的只有前6个参数。

寄存器的使用猜测和CPU和编译器有关。

##### 疑问

* 为什么第7、8个参数是从+16和+24的位置读取

* 这里栈的增长方向

* rbp+0是指向什么
