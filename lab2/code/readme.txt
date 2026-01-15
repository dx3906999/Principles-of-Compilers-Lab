额外修改：
runtime/runtime.cpp:

diff ./lab2/resource/Lab2/Lab2/runtime/runtime.cpp ./lab2/code/runtime/runtime.cpp
62c62
<     {Type::getInt32PtrTy(module->getContext()), Type::getInt32PtrTy(module->getContext())},
---
>     {Type::getInt32PtrTy(module->getContext()), Type::getInt32PtrTy(module->getContext()), Type::getInt8PtrTy(module->getContext())},