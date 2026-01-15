
[+]SAFEC IR GEN BEGIN[+]
Module Name trick.c
; ModuleID = 'trick.c'
source_filename = "trick.c"

@input_var = global i32 0
@output_var = global i32 0
@arg0 = global i32 0
@arg1 = global i32 0
@arg2 = global [17 x i8] c"SafeC IR Builder\00"

declare void @input_impl(ptr)

declare void @output_impl(ptr)

declare void @obc_check_error_impl(ptr, ptr, ptr)

define void @input() {
entry:
  call void @input_impl(ptr @input_var)
  ret void
}

define void @output() {
entry:
  call void @output_impl(ptr @output_var)
  ret void
}

define void @obc_check_error() {
entry:
  call void @obc_check_error_impl(ptr @arg0, ptr @arg1, ptr @arg2)
  ret void
}

define void @main() {
entry:
  %x = alloca [8 x i32], align 4
  store [8 x i32] zeroinitializer, ptr %x, align 4
  %index = alloca i32, align 4
  %addr = alloca i32, align 4
  call void @input()
  %0 = load i32, ptr @input_var, align 4
  store i32 %0, ptr %index, align 4
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %1 = load i32, ptr %index, align 4
  %2 = icmp sge i32 %1, 0
  br i1 %2, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  call void @input()
  %3 = load i32, ptr @input_var, align 4
  store i32 %3, ptr %addr, align 4
  %4 = load i32, ptr %addr, align 4
  %5 = load i32, ptr %index, align 4
  %6 = getelementptr inbounds [8 x i32], ptr %x, i32 0, i32 %5
  store i32 %4, ptr %6, align 4
  call void @input()
  %7 = load i32, ptr @input_var, align 4
  store i32 %7, ptr %index, align 4
  br label %while.cond

while.end:                                        ; preds = %while.cond
  ret void
}

[+]SAFEC IR GEN END[+]

[+]SAFEC EXECUTE BEGIN[+]
