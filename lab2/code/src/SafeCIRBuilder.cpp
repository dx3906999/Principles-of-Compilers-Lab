#include "SafeCIRBuilder.h"
#include <llvm/IR/Verifier.h>

// For lval and rval identification.
// Expect the function f to return an rval.
#define EXPECT_RVAL(f)               \
    val_type_stack.push(FLAG::RVAL); \
    f;                               \
    val_type_stack.pop();
// Expect the function f to return an lval.
#define EXPECT_LVAL(f)               \
    val_type_stack.push(FLAG::LVAL); \
    f;                               \
    val_type_stack.pop();
// Is current expected to return an lval.
#define IS_EXPECT_LVAL() val_type_stack.top() == FLAG::LVAL

SafeCIRBuilder::SafeCIRBuilder(llvm::LLVMContext &ctx)
    : context(ctx), builder(ctx) {}

SafeCIRBuilder::~SafeCIRBuilder() {}

void SafeCIRBuilder::obc_check(llvm::Value *index, int array_length,
                               int node_line, int node_pos, std::string name)
{
    // Insert code to check if index is in [0, length).
    // If not in range, call obc_check_error to report error.
    // Basic logic:
    //          ... (current insert point)
    //          cmp = index < 0 || index >= length
    //          br cmp, check_fail, check_success
    //      check_fail bb:
    //          call obc_check(node_line, node_pos, name)
    //          ret void
    //      check_success bb:
    //          ... (next insert point here)

    // TODO: Implement.

    auto *fail_bb = llvm::BasicBlock::Create(context, "obc.fail", current_function);
    auto *cont_bb = llvm::BasicBlock::Create(context, "obc.cont", current_function);

    llvm::Value *idx32 = builder.CreateIntCast(index, builder.getInt32Ty(), true);
    auto *lt0 = builder.CreateICmpSLT(idx32, builder.getInt32(0));
    auto *ge_len = builder.CreateICmpSGE(idx32, builder.getInt32(array_length));
    auto *oob = builder.CreateOr(lt0, ge_len);
    builder.CreateCondBr(oob, fail_bb, cont_bb);

    builder.SetInsertPoint(fail_bb);
    // Call obc_check_error to report error:
    llvm::Value *arg0_val = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), node_line);
    llvm::Value *arg1_val = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), node_pos);
    llvm::Value *arg2_val = llvm::ConstantDataArray::getString(context, name);
    llvm::Value *arg0_ptr = lookup_variable("arg0").val_ptr;
    llvm::Value *arg1_ptr = lookup_variable("arg1").val_ptr;
    llvm::Value *arg2_ptr = lookup_variable("arg2").val_ptr;
    llvm::Function *check_err = functions["obc_check_error"];
    builder.CreateStore(arg0_val, arg0_ptr);
    builder.CreateStore(arg1_val, arg1_ptr);
    builder.CreateStore(arg2_val, arg2_ptr);
    builder.CreateCall(check_err, {});

    builder.CreateRetVoid();

    builder.SetInsertPoint(cont_bb);

    return;
}

void SafeCIRBuilder::visit(comp_unit_node &node)
{
    for (auto comp_unit : node.comp_units)
    {
        if (auto global_var_decl =
                std::dynamic_pointer_cast<var_def_stmt_node>(comp_unit))
        {

            cur_scope = FLAG::GLOBAL_SCOPE;
            global_var_decl->accept(*this);
        }
        else if (auto global_func_def =
                     std::dynamic_pointer_cast<func_def_node>(comp_unit))
        {

            global_func_def->accept(*this);
        }
    }
}

void SafeCIRBuilder::visit(comp_unit_child_node &node)
{
    // Nothing to do here.
    return;
}

void SafeCIRBuilder::visit(global_def_node &node)
{
    // Nothing to do here.
    return;
}

void SafeCIRBuilder::visit(func_def_node &node)
{
    current_function = llvm::Function::Create(
        llvm::FunctionType::get(llvm::Type::getVoidTy(context), {}, false),
        llvm::GlobalValue::LinkageTypes::ExternalLinkage, node.name,
        module.get());
    functions[node.name] = current_function;
    auto entry = llvm::BasicBlock::Create(context, "entry", current_function);
    builder.SetInsertPoint(entry);
    bb_count = 0;
    auto body = node.body;
    body->accept(*this);
    if (builder.GetInsertBlock() && !builder.GetInsertBlock()->getTerminator())
    {
        builder.CreateRetVoid();
    }
}

void SafeCIRBuilder::visit(block_node &node)
{
    enter_scope();
    for (auto stmt : node.body)
    {
        cur_scope = FLAG::BLOCK_SCOPE;
        if (auto var_def_statement =
                std::dynamic_pointer_cast<var_def_stmt_node>(stmt))
        {
            var_def_statement->accept(*this);
        }
        else if (auto var_define =
                     std::dynamic_pointer_cast<var_def_node>(stmt))
        {
            var_define->accept(*this);
        }
        else if (auto assign_statement =
                     std::dynamic_pointer_cast<assign_stmt_node>(stmt))
        {
            assign_statement->accept(*this);
        }
        else if (auto func_call_statement =
                     std::dynamic_pointer_cast<func_call_stmt_node>(stmt))
        {
            func_call_statement->accept(*this);
        }
        else if (auto block =
                     std::dynamic_pointer_cast<block_node>(stmt))
        {
            block->accept(*this);
        }
        else if (auto if_statement =
                     std::dynamic_pointer_cast<if_stmt_node>(stmt))
        {
            if_statement->accept(*this);
        }
        else if (auto while_statement =
                     std::dynamic_pointer_cast<while_stmt_node>(stmt))
        {
            while_statement->accept(*this);
        }
        else if (auto empty_statement =
                     std::dynamic_pointer_cast<empty_stmt_node>(stmt))
        {
            empty_statement->accept(*this);
        }
        cur_scope = FLAG::GLOBAL_SCOPE;
    }
    exit_scope();
}

void SafeCIRBuilder::visit(stmt_node &node)
{
    // Nothing to do here.
}

void SafeCIRBuilder::visit(var_def_stmt_node &node)
{
    for (auto var_defs : node.var_defs)
    {
        var_defs->accept(*this);
    }
}

void SafeCIRBuilder::visit(func_call_stmt_node &node)
{
    if (functions.count(node.name) == 0)
    {
        std::cerr << node.line << ":" << node.pos << ": function " << node.name
                  << " is not declared" << std::endl;
        error_flag = true;
        return;
    }
    builder.CreateCall(functions[node.name], {});
}

void SafeCIRBuilder::visit(empty_stmt_node &node)
{
    // Nothing to do here.
}

void SafeCIRBuilder::visit(expr_node &node)
{
    // Nothing to do here.
}

void SafeCIRBuilder::visit(cond_node &node)
{
    // TODO: handle condition expression.
    llvm::Value *lhs_val;
    llvm::Value *rhs_val;
    EXPECT_RVAL(node.lhs->accept(*this));
    get_result_as_value(&lhs_val);
    EXPECT_RVAL(node.rhs->accept(*this));
    get_result_as_value(&rhs_val);

    llvm::Value *cond_val;
    switch (node.op)
    {
    case RelOp::EQUAL:
        cond_val = builder.CreateICmpEQ(lhs_val, rhs_val);
        break;
    case RelOp::NON_EQUAL:
        cond_val = builder.CreateICmpNE(lhs_val, rhs_val);
        break;
    case RelOp::LESS:
        cond_val = builder.CreateICmpSLT(lhs_val, rhs_val);
        break;
    case RelOp::LESS_EQUAL:
        cond_val = builder.CreateICmpSLE(lhs_val, rhs_val);
        break;
    case RelOp::GREATER:
        cond_val = builder.CreateICmpSGT(lhs_val, rhs_val);
        break;
    case RelOp::GREATER_EQUAL:
        cond_val = builder.CreateICmpSGE(lhs_val, rhs_val);
        break;

    default:
        break;
    }

    set_value_result(cond_val);
}

void SafeCIRBuilder::visit(number_node &node)
{
    set_int_result(node.number);
}

void SafeCIRBuilder::visit(binop_expr_node &node)
{
    // TODO: handle binary operation.
    /*
        Visit lhs and rhs, there can be 2 cases:
        1. If lhs and rhs are both constant, we can calculate the result directly and provide a
          constant result to the parent node:
            for example: "1+2" -> set_int_result(1+2)
        2. If lhs and rhs are not both constant, build an instruction for the binary op:
            for example: "a+1" -> %res = add %a, 1; set_value_result(res)
            for example: "a+b" -> %res = add %a, %b; set_value_result(res)
    */
    int lhs_int, rhs_int;
    bool lhs_is_int = false, rhs_is_int = false;
    llvm::Value *lhs_val = nullptr;
    llvm::Value *rhs_val = nullptr;

    EXPECT_RVAL(node.lhs->accept(*this));
    lhs_is_int = get_int_result(lhs_int);
    if (!lhs_is_int)
    {
        get_result_as_value(&lhs_val);
    }

    EXPECT_RVAL(node.rhs->accept(*this));
    rhs_is_int = get_int_result(rhs_int);
    if (!rhs_is_int)
    {
        get_result_as_value(&rhs_val);
    }

    if (lhs_is_int && rhs_is_int)
    {
        int res = 0;
        switch (node.op)
        {
        case BinOp::PLUS:
            res = lhs_int + rhs_int;
            break;
        case BinOp::MINUS:
            res = lhs_int - rhs_int;
            break;
        case BinOp::MULTIPLY:
            res = lhs_int * rhs_int;
            break;
        case BinOp::DIVIDE:
            res = lhs_int / rhs_int;
            break;
        case BinOp::MODULO:
            res = lhs_int % rhs_int;
            break;
        }
        set_int_result(res);
        return;
    }

    if (lhs_is_int)
    {
        lhs_val = builder.getInt32(lhs_int);
    }
    if (rhs_is_int)
    {
        rhs_val = builder.getInt32(rhs_int);
    }

    llvm::Value *res_val = nullptr;
    switch (node.op)
    {
    case BinOp::PLUS:
        res_val = builder.CreateAdd(lhs_val, rhs_val);
        break;
    case BinOp::MINUS:
        res_val = builder.CreateSub(lhs_val, rhs_val);
        break;
    case BinOp::MULTIPLY:
        res_val = builder.CreateMul(lhs_val, rhs_val);
        break;
    case BinOp::DIVIDE:
        res_val = builder.CreateSDiv(lhs_val, rhs_val);
        break;
    case BinOp::MODULO:
        res_val = builder.CreateSRem(lhs_val, rhs_val);
        break;
    }
    set_value_result(res_val);
}

void SafeCIRBuilder::visit(unaryop_expr_node &node)
{
    // TODO: handle unary operation.
    EXPECT_RVAL(node.rhs->accept(*this));

    int rhs_int;
    if (get_int_result(rhs_int))
    {
        switch (node.op)
        {
        case UnaryOp::PLUS:
            set_int_result(rhs_int);
            return;
        case UnaryOp::MINUS:
            set_int_result(-rhs_int);
            return;
        }
    }

    llvm::Value *rhs_val = nullptr;
    get_result_as_value(&rhs_val);
    llvm::Value *res_val = nullptr;
    switch (node.op)
    {
    case UnaryOp::PLUS:
        res_val = rhs_val;
        break;
    case UnaryOp::MINUS:
        res_val = builder.CreateNeg(rhs_val);
        break;
    }
    set_value_result(res_val);
}

void SafeCIRBuilder::visit(lval_node &node)
{
    auto name = node.name;
    VarInfo var_info = lookup_variable(name);
    if (!var_info.is_valid())
    {
        std::cerr << node.line << ":" << node.pos << ": variable '" << name
                  << "' is not declared" << std::endl;
        error_flag = true;
        return;
    }

    /*
        Use IS_EXPECT_LVAL() to check if the parent node expects an lval or an rval. And
          the parent must use EXPECT_LVAL() or EXPECT_RVAL() properly.
        If lval is expected, we can directly return the lval of the variable:
            for example: in "%a = 1" and we are visiting "%a",
            we can return the llvm::Value* of %a.
        If rval is expected, we need to load the value of the variable and return the loaded value.
            for example: in "1 + *%a" and we are visiting "%a",
            we need to return the loaded value of %a, create "%tmp = load %a" and then set_value_result(%tmp).
    */

    if (!var_info.is_array)
    {
        // TODO: handle scalar lval
        if (IS_EXPECT_LVAL())
        {
            set_value_result(var_info.val_ptr);
        }
        else
        {
            auto *loaded = builder.CreateLoad(builder.getInt32Ty(), var_info.val_ptr);
            set_value_result(loaded);
        }
    }
    else
    {
        // TODO: handle array lval and call obc_check to insert obc check code for obc array.
        if (!node.array_index)
        {
            std::cerr << node.line << ":" << node.pos << ": array index missing for '" << name << "'" << std::endl;
            error_flag = true;
            return;
        }

        EXPECT_RVAL(node.array_index->accept(*this));
        llvm::Value *idx_val = nullptr;
        get_result_as_value(&idx_val);
        auto *idx32 = builder.CreateIntCast(idx_val, builder.getInt32Ty(), true);

        if (var_info.is_obc)
        {
            obc_check(idx32, var_info.array_length, node.line, node.pos, name);
        }

        auto *arr_type = llvm::ArrayType::get(builder.getInt32Ty(), var_info.array_length);
        auto *elem_ptr = builder.CreateInBoundsGEP(arr_type, var_info.val_ptr,
                                                   {builder.getInt32(0), idx32});

        if (IS_EXPECT_LVAL())
        {
            set_value_result(elem_ptr);
        }
        else
        {
            auto *loaded = builder.CreateLoad(builder.getInt32Ty(), elem_ptr);
            set_value_result(loaded);
        }
        return;
    }
}

void SafeCIRBuilder::visit(var_def_node &node)
{
    std::string name = node.name;
    bool is_const = node.is_const;
    bool is_obc = node.is_obc;
    ptr<expr_node> array_length = node.array_length;
    ptr_vector<expr_node> initializers = node.initializers;

    if (cur_scope == FLAG::GLOBAL_SCOPE)
    { // global define
        llvm::GlobalVariable *global_variable;

        if (!array_length)
        { // not an array
            // TODO: create and declare global scalar
            llvm::Constant *init = llvm::ConstantInt::get(builder.getInt32Ty(), 0);
            if (!initializers.empty())
            {
                EXPECT_RVAL(initializers[0]->accept(*this));
                int init_int;
                if (!get_int_result(init_int))
                {
                    std::cerr << node.line << ":" << node.pos << ": global init must be const" << std::endl;
                    error_flag = true;
                    return;
                }
                init = llvm::ConstantInt::get(builder.getInt32Ty(), init_int);
            }
            global_variable = new llvm::GlobalVariable(*module, builder.getInt32Ty(), is_const,
                                                       llvm::GlobalValue::ExternalLinkage, init, name);
            if (!declare_variable(name, global_variable, is_const, false, false, 0))
            {
                std::cerr << node.line << ":" << node.pos << ": variable '" << name
                          << "' is declared more than one times" << std::endl;
                error_flag = true;
                return;
            }
        }
        else
        { // is an array
            // TODO: create and declare global array
            EXPECT_RVAL(array_length->accept(*this));
            int len_const;
            if (!get_int_result(len_const))
            {
                std::cerr << node.line << ":" << node.pos << ": array length must be const" << std::endl;
                error_flag = true;
                return;
            }
            if (len_const <= 0)
            {
                std::cerr << node.line << ":" << node.pos << ": size of array '" << name << "' is not positive" << std::endl;
                error_flag = true;
                return;
            }
            if (static_cast<int>(initializers.size()) > len_const)
            {
                std::cerr << node.line << ":" << node.pos << ": excess elements in the initializer of array '" << name << "'" << std::endl;
                error_flag = true;
                return;
            }
            auto *arr_type = llvm::ArrayType::get(builder.getInt32Ty(), len_const);
            std::vector<llvm::Constant *> elems;
            elems.reserve(len_const);
            for (int i = 0; i < len_const; ++i)
            {
                if (i < static_cast<int>(initializers.size()))
                {
                    EXPECT_RVAL(initializers[i]->accept(*this));
                    int v;
                    if (!get_int_result(v))
                    {
                        std::cerr << node.line << ":" << node.pos << ": array init must be const" << std::endl;
                        error_flag = true;
                        return;
                    }
                    elems.push_back(llvm::ConstantInt::get(builder.getInt32Ty(), v));
                }
                else
                {
                    elems.push_back(llvm::ConstantInt::get(builder.getInt32Ty(), 0));
                }
            }
            auto *init_arr = llvm::ConstantArray::get(arr_type, elems);
            global_variable = new llvm::GlobalVariable(*module, arr_type, is_const,
                                                       llvm::GlobalValue::ExternalLinkage, init_arr, name);
            if (!declare_variable(name, global_variable, is_const, true, is_obc, len_const))
            {
                std::cerr << node.line << ":" << node.pos << ": variable '" << name
                          << "' is declared more than one times" << std::endl;
                error_flag = true;
                return;
            }
        }
    }
    else
    { // local define
        llvm::Value *local_variable;

        if (!array_length)
        { // not an array
            // TODO: create and declare local scalar
            local_variable = builder.CreateAlloca(builder.getInt32Ty(), nullptr, name);
            if (!initializers.empty())
            {
                EXPECT_RVAL(initializers[0]->accept(*this));
                llvm::Value *init_v;
                get_result_as_value(&init_v);
                builder.CreateStore(init_v, local_variable);
            }
            if (!declare_variable(name, local_variable, is_const, false, false, 0))
            {
                std::cerr << node.line << ":" << node.pos << ": variable '" << name
                          << "' is declared more than one times" << std::endl;
                error_flag = true;
                return;
            }
        }
        else
        { // is an array
            // TODO: create and declare local array
            EXPECT_RVAL(array_length->accept(*this));
            int len_const;
            if (!get_int_result(len_const))
            {
                std::cerr << node.line << ":" << node.pos << ": array length must be const" << std::endl;
                error_flag = true;
                return;
            }
            if (len_const <= 0)
            {
                std::cerr << node.line << ":" << node.pos << ": size of array '" << name << "' is not positive" << std::endl;
                error_flag = true;
                return;
            }
            if (static_cast<int>(initializers.size()) > len_const)
            {
                std::cerr << node.line << ":" << node.pos << ": excess elements in the initializer of array '" << name << "'" << std::endl;
                error_flag = true;
                return;
            }
            auto *arr_ty = llvm::ArrayType::get(builder.getInt32Ty(), len_const);
            local_variable = builder.CreateAlloca(arr_ty, nullptr, name);
            auto *zero_init = llvm::ConstantAggregateZero::get(arr_ty);
            builder.CreateStore(zero_init, local_variable);
            for (int i = 0; i < static_cast<int>(initializers.size()) && i < len_const; ++i)
            {
                EXPECT_RVAL(initializers[i]->accept(*this));
                llvm::Value *init_v;
                get_result_as_value(&init_v);
                auto *elem_ptr = builder.CreateInBoundsGEP(arr_ty, local_variable,
                                                           {builder.getInt32(0), builder.getInt32(i)});
                builder.CreateStore(init_v, elem_ptr);
            }
            if (!declare_variable(name, local_variable, is_const, true, is_obc, len_const))
            {
                std::cerr << node.line << ":" << node.pos << ": variable '" << name
                          << "' is declared more than one times" << std::endl;
                error_flag = true;
                return;
            }
        }
    }
}

void SafeCIRBuilder::visit(assign_stmt_node &node)
{
    // TODO: get target's rval and store at value's lval.
    VarInfo target_info;
    target_info = lookup_variable(node.target->name);
    if (target_info.is_const)
    {
        std::cerr << node.line << ":" << node.pos << ": assignment of read-only variable '"
                  << node.target->name << "'" << std::endl;
        error_flag = true;
        return;
    }
    llvm::Value *value_val;
    llvm::Value *target_ptr;
    EXPECT_RVAL(node.value->accept(*this));
    get_result_as_value(&value_val);
    EXPECT_LVAL(node.target->accept(*this));
    get_value_result(&target_ptr);
    builder.CreateStore(value_val, target_ptr);
}

void SafeCIRBuilder::visit(if_stmt_node &node)
{
    // TODO: implement if-else statement.
    auto cond_basic_block = llvm::BasicBlock::Create(context, "if.cond", current_function);
    auto if_basic_block = llvm::BasicBlock::Create(context, "if.body", current_function);
    auto else_basic_block = node.else_body ? llvm::BasicBlock::Create(context, "else.body", current_function) : nullptr;
    auto end_basic_block = llvm::BasicBlock::Create(context, "if.end", current_function);
    builder.CreateBr(cond_basic_block);

    builder.SetInsertPoint(cond_basic_block);
    EXPECT_RVAL(node.cond->accept(*this));
    llvm::Value *cond_val;
    get_result_as_value(&cond_val);
    if (!cond_val->getType()->isIntegerTy(1))
    {
        cond_val = builder.CreateICmpNE(cond_val, builder.getInt32(0));
    }
    builder.CreateCondBr(cond_val, if_basic_block, else_basic_block ? else_basic_block : end_basic_block);

    builder.SetInsertPoint(if_basic_block);
    if (node.if_body)
    {
        node.if_body->accept(*this);
    }
    auto *cur_bb = builder.GetInsertBlock();
    if (cur_bb && !cur_bb->getTerminator())
    {
        builder.CreateBr(end_basic_block);
    }

    if (else_basic_block)
    {
        builder.SetInsertPoint(else_basic_block);
        if (node.else_body)
        {
            node.else_body->accept(*this);
        }
        cur_bb = builder.GetInsertBlock();
        if (cur_bb && !cur_bb->getTerminator())
        {
            builder.CreateBr(end_basic_block);
        }
    }

    builder.SetInsertPoint(end_basic_block);
}

void SafeCIRBuilder::visit(while_stmt_node &node)
{
    // TODO: implement while statement.
    auto cond_basic_block = llvm::BasicBlock::Create(context, "while.cond", current_function);
    auto body_basic_block = llvm::BasicBlock::Create(context, "while.body", current_function);
    auto end_basic_block = llvm::BasicBlock::Create(context, "while.end", current_function);

    builder.CreateBr(cond_basic_block);

    builder.SetInsertPoint(cond_basic_block);
    EXPECT_RVAL(node.cond->accept(*this));
    llvm::Value *cond_val;
    get_result_as_value(&cond_val);
    if (!cond_val->getType()->isIntegerTy(1))
    {
        cond_val = builder.CreateICmpNE(cond_val, builder.getInt32(0));
    }
    builder.CreateCondBr(cond_val, body_basic_block, end_basic_block);

    builder.SetInsertPoint(body_basic_block);
    if (node.body)
    {
        node.body->accept(*this);
    }

    auto *cur_bb = builder.GetInsertBlock();
    if (cur_bb && !cur_bb->getTerminator())
    {
        builder.CreateBr(cond_basic_block);
    }

    builder.SetInsertPoint(end_basic_block);
}

void SafeCIRBuilder::log(std::string info)
{
    if (debug)
    {
        std::cerr << info << std::endl;
    }
};

void SafeCIRBuilder::build(std::string name, std::shared_ptr<ast_node> node)
{
    // Initialize environment.
    module = std::make_unique<llvm::Module>(name, context);
    runtime = std::make_unique<runtime_info>(module.get());

    // global
    enter_scope();
    for (auto t : runtime->get_language_symbols())
    {
        llvm::GlobalValue *val;
        std::string name;
        bool is_function;
        bool is_const;
        bool is_array;
        bool is_obc;
        int array_length;
        std::tie(name, val, is_function, is_const, is_array, is_obc,
                 array_length) = t;
        if (is_function)
            functions[name] = static_cast<llvm::Function *>(val);
        else
            declare_variable(name, val, is_const, is_array, is_obc,
                             array_length);
    }

    cur_scope = FLAG::GLOBAL_SCOPE;
    error_flag = false;

    // Start building by starting iterate over the syntax tree.
    node->accept(*this);

    // if (llvm::verifyModule(*module, &llvm::errs())) {
    //     std::cerr << "IR verification failed." << std::endl;
    //     error_flag = true;
    // }

    // Finish by clear IRBuilder's insertion point and moving away built module.
    builder.ClearInsertionPoint();
    exit_scope();

    if (error_flag)
    {
        module.release();
        runtime.release();
    }
}

std::unique_ptr<llvm::Module> SafeCIRBuilder::get_module()
{
    return std::move(module);
}

std::unique_ptr<runtime_info> SafeCIRBuilder::get_runtime_info()
{
    return std::move(runtime);
}

void SafeCIRBuilder::enter_scope()
{
    scoped_variables.emplace_back();
    scoped_variables.back().scope_type = cur_scope;
    cur_scope = FLAG::BLOCK_SCOPE;
}

void SafeCIRBuilder::exit_scope()
{
    scoped_variables.pop_back();
    cur_scope = scoped_variables.back().scope_type;
}

SafeCIRBuilder::VarInfo SafeCIRBuilder::lookup_variable(std::string name)
{
    // TODO: find the nearest decalred variable `name`
    for (auto it = scoped_variables.rbegin(); it != scoped_variables.rend(); ++it)
    {
        auto found = it->variable_map.find(name);
        if (found != it->variable_map.end())
        {
            return found->second;
        }
    }
    return VarInfo();
}

bool SafeCIRBuilder::declare_variable(std::string name, llvm::Value *var_ptr,
                                      bool is_const, bool is_array, bool is_obc,
                                      int array_length)
{
    if (scoped_variables.back().variable_map.count(name))
    {
        return false;
    }
    scoped_variables.back().variable_map[name] =
        VarInfo(var_ptr, is_const, is_array, is_obc, array_length);
    return true;
}

void SafeCIRBuilder::set_int_result(int val)
{
    has_int_result = true;
    int_result = val;
}

bool SafeCIRBuilder::get_int_result(int &val)
{
    if (has_int_result)
    {
        val = int_result;
        has_int_result = false;
        return true;
    }
    else
    {
        return false;
    }
}

void SafeCIRBuilder::set_value_result(llvm::Value *val)
{
    has_value_result = true;
    value_result = val;
}

bool SafeCIRBuilder::get_value_result(llvm::Value **val)
{
    if (has_value_result)
    {
        *val = value_result;
        has_value_result = false;
        return true;
    }
    else
    {
        return false;
    }
}

bool SafeCIRBuilder::get_result_as_value(llvm::Value **val)
{
    if (has_value_result)
    {
        *val = value_result;
        has_value_result = false;
        return true;
    }
    else if (has_int_result)
    {
        *val = builder.getInt32(int_result);
        has_int_result = false;
        return true;
    }
    else
    {
        return false;
    }
}
