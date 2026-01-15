[@0,0:3='void',<25>,1:0]
[@1,5:8='main',<28>,1:5]
[@2,9:9='(',<8>,1:9]
[@3,10:10=')',<9>,1:10]
[@4,12:12='{',<6>,2:0]
[@5,18:20='int',<24>,3:4]
[@6,22:24='obc',<26>,3:8]
[@7,26:26='x',<28>,3:12]
[@8,27:27='[',<4>,3:13]
[@9,28:29='10',<29>,3:14]
[@10,30:30=']',<5>,3:16]
[@11,32:32='=',<3>,3:18]
[@12,34:34='{',<6>,3:20]
[@13,35:35='0',<29>,3:21]
[@14,36:36=',',<1>,3:22]
[@15,38:38='1',<29>,3:24]
[@16,39:39=',',<1>,3:25]
[@17,41:41='2',<29>,3:27]
[@18,42:42=',',<1>,3:28]
[@19,44:44='3',<29>,3:30]
[@20,45:45=',',<1>,3:31]
[@21,47:47='4',<29>,3:33]
[@22,48:48=',',<1>,3:34]
[@23,50:50='5',<29>,3:36]
[@24,51:51=',',<1>,3:37]
[@25,53:53='6',<29>,3:39]
[@26,54:54=',',<1>,3:40]
[@27,56:56='7',<29>,3:42]
[@28,57:57=',',<1>,3:43]
[@29,59:59='8',<29>,3:45]
[@30,60:60='}',<7>,3:46]
[@31,61:61=';',<2>,3:47]
[@32,67:71='input',<28>,4:4]
[@33,72:72='(',<8>,4:9]
[@34,73:73=')',<9>,4:10]
[@35,74:74=';',<2>,4:11]
[@36,80:89='output_var',<28>,5:4]
[@37,91:91='=',<3>,5:15]
[@38,93:93='x',<28>,5:17]
[@39,94:94='[',<4>,5:18]
[@40,95:103='input_var',<28>,5:19]
[@41,104:104=']',<5>,5:28]
[@42,105:105=';',<2>,5:29]
[@43,111:116='output',<28>,6:4]
[@44,117:117='(',<8>,6:10]
[@45,118:118=')',<9>,6:11]
[@46,119:119=';',<2>,6:12]
[@47,121:121='}',<7>,7:0]
[@48,362:361='<EOF>',<-1>,32:2]
(compUnit (funcDef void main ( ) (block { (blockItem (decl (varDecl (bType int) (varDef (array (obcArray obc (unobcArray x [ (exp (number 10)) ]))) = { (exp (number 0)) , (exp (number 1)) , (exp (number 2)) , (exp (number 3)) , (exp (number 4)) , (exp (number 5)) , (exp (number 6)) , (exp (number 7)) , (exp (number 8)) }) ;))) (blockItem (stmt input ( ) ;)) (blockItem (stmt (lval output_var) = (exp (lval x [ (exp (lval input_var)) ])) ;)) (blockItem (stmt output ( ) ;)) })) <EOF>)

[+]SAFEC IR GEN BEGIN[+]
Module Name array_init_2.c
; ModuleID = 'array_init_2.c'
source_filename = "array_init_2.c"

@input_var = global i32 0
@output_var = global i32 0
@arg0 = global i32 0
@arg1 = global i32 0
@arg2 = global [17 x i8] c"SafeC IR Builder\00"
@0 = private unnamed_addr constant [2 x i8] c"x\00", align 1

declare void @input_impl(ptr)

declare void @output_impl(ptr)

declare void @obc_check_error_impl(ptr, ptr)

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
  %x = alloca [10 x i32], align 4
  store [10 x i32] zeroinitializer, ptr %x, align 4
  %0 = getelementptr inbounds [10 x i32], ptr %x, i32 0, i32 0
  store i32 0, ptr %0, align 4
  %1 = getelementptr inbounds [10 x i32], ptr %x, i32 0, i32 1
  store i32 1, ptr %1, align 4
  %2 = getelementptr inbounds [10 x i32], ptr %x, i32 0, i32 2
  store i32 2, ptr %2, align 4
  %3 = getelementptr inbounds [10 x i32], ptr %x, i32 0, i32 3
  store i32 3, ptr %3, align 4
  %4 = getelementptr inbounds [10 x i32], ptr %x, i32 0, i32 4
  store i32 4, ptr %4, align 4
  %5 = getelementptr inbounds [10 x i32], ptr %x, i32 0, i32 5
  store i32 5, ptr %5, align 4
  %6 = getelementptr inbounds [10 x i32], ptr %x, i32 0, i32 6
  store i32 6, ptr %6, align 4
  %7 = getelementptr inbounds [10 x i32], ptr %x, i32 0, i32 7
  store i32 7, ptr %7, align 4
  %8 = getelementptr inbounds [10 x i32], ptr %x, i32 0, i32 8
  store i32 8, ptr %8, align 4
  call void @input()
  %9 = load i32, ptr @input_var, align 4
  %10 = icmp slt i32 %9, 0
  %11 = icmp sge i32 %9, 10
  %12 = or i1 %10, %11
  br i1 %12, label %obc.fail, label %obc.cont

obc.fail:                                         ; preds = %entry
  store i32 5, ptr @arg0, align 4
  store i32 17, ptr @arg1, align 4
  store ptr @0, ptr @arg2, align 8
  call void @obc_check_error()
  ret void

obc.cont:                                         ; preds = %entry
  %13 = getelementptr inbounds [10 x i32], ptr %x, i32 0, i32 %9
  %14 = load i32, ptr %13, align 4
  store i32 %14, ptr @output_var, align 4
  call void @output()
  ret void
}

[+]SAFEC IR GEN END[+]

[+]SAFEC EXECUTE BEGIN[+]
input:output:0

[+]SAFEC EXECUTE END[+]
