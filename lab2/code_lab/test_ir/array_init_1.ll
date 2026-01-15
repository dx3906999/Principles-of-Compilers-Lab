[@0,0:3='void',<25>,1:0]
[@1,5:8='main',<28>,1:5]
[@2,9:9='(',<8>,1:9]
[@3,10:10=')',<9>,1:10]
[@4,12:12='{',<6>,2:0]
[@5,18:20='int',<24>,3:4]
[@6,22:22='x',<28>,3:8]
[@7,23:23='[',<4>,3:9]
[@8,24:24='-',<20>,3:10]
[@9,25:25='1',<29>,3:11]
[@10,26:26='+',<19>,3:12]
[@11,27:27='4',<29>,3:13]
[@12,28:28=']',<5>,3:14]
[@13,30:30='=',<3>,3:16]
[@14,32:32='{',<6>,3:18]
[@15,33:33='2',<29>,3:19]
[@16,34:34=',',<1>,3:20]
[@17,36:36='1',<29>,3:22]
[@18,37:37='}',<7>,3:23]
[@19,38:38=';',<2>,3:24]
[@20,44:53='output_var',<28>,4:4]
[@21,55:55='=',<3>,4:15]
[@22,57:57='x',<28>,4:17]
[@23,58:58='[',<4>,4:18]
[@24,59:59='0',<29>,4:19]
[@25,60:60=']',<5>,4:20]
[@26,61:61=';',<2>,4:21]
[@27,67:72='output',<28>,5:4]
[@28,73:73='(',<8>,5:10]
[@29,74:74=')',<9>,5:11]
[@30,75:75=';',<2>,5:12]
[@31,81:90='output_var',<28>,6:4]
[@32,92:92='=',<3>,6:15]
[@33,94:94='x',<28>,6:17]
[@34,95:95='[',<4>,6:18]
[@35,96:96='1',<29>,6:19]
[@36,97:97=']',<5>,6:20]
[@37,98:98=';',<2>,6:21]
[@38,104:109='output',<28>,7:4]
[@39,110:110='(',<8>,7:10]
[@40,111:111=')',<9>,7:11]
[@41,112:112=';',<2>,7:12]
[@42,118:127='output_var',<28>,8:4]
[@43,129:129='=',<3>,8:15]
[@44,131:131='x',<28>,8:17]
[@45,132:132='[',<4>,8:18]
[@46,133:133='2',<29>,8:19]
[@47,134:134=']',<5>,8:20]
[@48,135:135=';',<2>,8:21]
[@49,141:146='output',<28>,9:4]
[@50,147:147='(',<8>,9:10]
[@51,148:148=')',<9>,9:11]
[@52,149:149=';',<2>,9:12]
[@53,151:151='}',<7>,10:0]
[@54,186:185='<EOF>',<-1>,16:2]
(compUnit (funcDef void main ( ) (block { (blockItem (decl (varDecl (bType int) (varDef (array (unobcArray x [ (exp (exp - (exp (number 1))) + (exp (number 4))) ])) = { (exp (number 2)) , (exp (number 1)) }) ;))) (blockItem (stmt (lval output_var) = (exp (lval x [ (exp (number 0)) ])) ;)) (blockItem (stmt output ( ) ;)) (blockItem (stmt (lval output_var) = (exp (lval x [ (exp (number 1)) ])) ;)) (blockItem (stmt output ( ) ;)) (blockItem (stmt (lval output_var) = (exp (lval x [ (exp (number 2)) ])) ;)) (blockItem (stmt output ( ) ;)) })) <EOF>)

[+]SAFEC IR GEN BEGIN[+]
Module Name array_init_1.c
; ModuleID = 'array_init_1.c'
source_filename = "array_init_1.c"

@input_var = global i32 0
@output_var = global i32 0
@arg0 = global i32 0
@arg1 = global i32 0
@arg2 = global [17 x i8] c"SafeC IR Builder\00"

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
  %x = alloca [3 x i32], align 4
  store [3 x i32] zeroinitializer, ptr %x, align 4
  %0 = getelementptr inbounds [3 x i32], ptr %x, i32 0, i32 0
  store i32 2, ptr %0, align 4
  %1 = getelementptr inbounds [3 x i32], ptr %x, i32 0, i32 1
  store i32 1, ptr %1, align 4
  %2 = getelementptr inbounds [3 x i32], ptr %x, i32 0, i32 0
  %3 = load i32, ptr %2, align 4
  store i32 %3, ptr @output_var, align 4
  call void @output()
  %4 = getelementptr inbounds [3 x i32], ptr %x, i32 0, i32 1
  %5 = load i32, ptr %4, align 4
  store i32 %5, ptr @output_var, align 4
  call void @output()
  %6 = getelementptr inbounds [3 x i32], ptr %x, i32 0, i32 2
  %7 = load i32, ptr %6, align 4
  store i32 %7, ptr @output_var, align 4
  call void @output()
  ret void
}

[+]SAFEC IR GEN END[+]

[+]SAFEC EXECUTE BEGIN[+]
output:2
output:1
output:0

[+]SAFEC EXECUTE END[+]
