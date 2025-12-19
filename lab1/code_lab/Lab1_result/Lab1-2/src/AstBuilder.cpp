#include "AstBuilder.h"

namespace antlrcpp
{
    antlrcpp::Any AstBuilder::visitCompUnit(SafeCParser::CompUnitContext *ctx)
    {
        auto result = new comp_unit_node;
        auto compile_units = ctx->children;

        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();

        // Ignore the last EOF in the for loop.
        for (auto i = 0; i < compile_units.size() - 1; i++)
        {
            if (auto decl =
                    dynamic_cast<SafeCParser::DeclContext *>(compile_units[i]))
            {
                // Global define
                auto global_def_stmt_n = visit(decl).as<var_def_stmt_node *>();

                auto var_def_stmt_n =
                    dynamic_cast<var_def_stmt_node *>(global_def_stmt_n);
                result->comp_units.push_back(
                    ptr<comp_unit_child_node>(var_def_stmt_n));
            }
            else if (auto func_def = dynamic_cast<SafeCParser::FuncDefContext *>(
                         compile_units[i]))
            {
                // Function define
                auto func_def_n = visit(func_def).as<func_def_node *>();
                result->comp_units.push_back(ptr<comp_unit_child_node>(func_def_n));
            }
            else
            {
                // Error.
                log(compile_units[i]->getText());
                assert(0 && "Unknown Compile Unit.");
            }
        }
        return result;
    }

    antlrcpp::Any AstBuilder::visitDecl(SafeCParser::DeclContext *ctx)
    {

        if (auto const_decl = ctx->constDecl())
        {
            return visit(const_decl).as<var_def_stmt_node *>();
        }
        else if (auto var_decl = ctx->varDecl())
        {
            return visit(var_decl).as<var_def_stmt_node *>();
        }
        else
        {
            assert(0 && "Unknown DeclContext.");
        }
    }

    antlrcpp::Any AstBuilder::visitFuncDef(SafeCParser::FuncDefContext *ctx)
    {
        // TODO
        auto result = new func_def_node;
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();
        result->name = ctx->Identifier()->getSymbol()->getText();
        auto block_n = visit(ctx->block()).as<block_node *>();
        result->body.reset(block_n);
        return result;
    }

    antlrcpp::Any AstBuilder::visitConstDecl(SafeCParser::ConstDeclContext *ctx)
    {
        // TODO
        auto result = new var_def_stmt_node;
        auto const_defs = ctx->constDef();
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();

        for (auto const_def : const_defs)
        {
            auto const_def_n = visit(const_def).as<var_def_node *>();
            result->var_defs.push_back(ptr<var_def_node>(const_def_n));
        }
        return result;
    }

    antlrcpp::Any AstBuilder::visitConstDef(SafeCParser::ConstDefContext *ctx)
    {
        if (auto array = ctx->array())
        {
            // TODO: Array
            auto result = visit(array).as<var_def_node *>();
            result->is_const = true;
            // if (result->array_length == nullptr)
            // {
            //     // result->array_length = new number_node;
            //     auto number_len = new number_node;
            //     result->array_length = ptr<expr_node>(number_len);
            //     number_len->line = ctx->getStart()->getLine();
            //     number_len->pos = ctx->getStart()->getCharPositionInLine();
            //     number_len->btype = BType::INT;
            //     number_len->number = ctx->exp().size();
            // }
            if (auto arr_len = dynamic_cast<number_node *>(result->array_length.get()))
            {
                if (arr_len->number == -1)
                {
                    arr_len->number = ctx->exp().size();
                }
                
                
            }
            for (auto exp_ctx : ctx->exp())
            {
                result->initializers.push_back(
                    ptr<expr_node>(visit(exp_ctx).as<expr_node *>()));
            }
            return result;
        }
        else if (ctx->Identifier())
        {
            // TODO: Scalar
            auto result = new var_def_node;
            result->line = ctx->getStart()->getLine();
            result->pos = ctx->getStart()->getCharPositionInLine();
            result->name = ctx->Identifier()->getSymbol()->getText();
            result->is_const = true;
            result->btype = BType::INT;
            result->is_obc = false;
            result->array_length = nullptr;
            result->initializers.push_back(
                ptr<expr_node>(visit(ctx->exp(0)).as<expr_node *>()));
            return result;
        }
        else
        {
            assert(0 && "Unknown ConstDef");
        }
    }

    antlrcpp::Any AstBuilder::visitVarDecl(SafeCParser::VarDeclContext *ctx)
    {
        // TODO
        auto result = new var_def_stmt_node;
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();
        auto var_defs = ctx->varDef();
        for (auto var_def : var_defs)
        {
            auto var_def_n = visit(var_def).as<var_def_node *>();
            result->var_defs.push_back(ptr<var_def_node>(var_def_n));
        }
        return result;
    }

    antlrcpp::Any AstBuilder::visitBType(SafeCParser::BTypeContext *ctx)
    {
        /* Nothing to do here. */
        return NULL;
    }

    antlrcpp::Any AstBuilder::visitVarDef(SafeCParser::VarDefContext *ctx)
    {
        if (auto array = ctx->array())
        {
            // TODO: Array
            auto result = visit(array).as<var_def_node *>();

            if (ctx->exp().size() > 0)
            {
                // if (result->array_length == nullptr)
                // {
                //     auto number_len = new number_node;
                //     result->array_length = ptr<expr_node>(number_len);
                //     number_len->line = ctx->getStart()->getLine();
                //     number_len->pos = ctx->getStart()->getCharPositionInLine();
                //     number_len->btype = BType::INT;
                //     number_len->number = ctx->exp().size();
                // }
                if (auto arr_len = dynamic_cast<number_node *>(result->array_length.get()))
                {
                    if (arr_len->number == -1)
                    {
                        arr_len->number = ctx->exp().size();
                    }
                }

                for (auto exp_ctx : ctx->exp())
                {
                    result->initializers.push_back(
                        ptr<expr_node>(visit(exp_ctx).as<expr_node *>()));
                }
            }

            return result;
        }
        else if (ctx->Identifier())
        {
            // TODO: Scalar
            auto result = new var_def_node;
            result->line = ctx->getStart()->getLine();
            result->pos = ctx->getStart()->getCharPositionInLine();
            result->name = ctx->Identifier()->getSymbol()->getText();
            result->is_const = false;
            result->btype = BType::INT;
            result->is_obc = false;
            result->array_length = nullptr;
            if (ctx->exp().size() > 0)
            {
                result->initializers.push_back(
                    ptr<expr_node>(visit(ctx->exp(0)).as<expr_node *>()));
            }
            else
            {
                // No initializer
                result->initializers.clear();
            }
            return result;
        }
        else
        {
            assert(0 && "Unknown VarDef");
        }
    }

    antlrcpp::Any AstBuilder::visitArray(SafeCParser::ArrayContext *ctx)
    {
        // TODO
        if (auto obc_array = ctx->obcArray())
        {
            return visit(obc_array).as<var_def_node *>();
        }
        else if (auto unobc_array = ctx->unobcArray())
        {
            return visit(unobc_array).as<var_def_node *>();
        }
        else
        {
            assert(0 && "Unknown Array");
        }
    }

    antlrcpp::Any AstBuilder::visitObcArray(SafeCParser::ObcArrayContext *ctx)
    {
        // TODO
        auto result = visit(ctx->unobcArray()).as<var_def_node *>();
        result->is_obc = true;
        return result;
    }

    antlrcpp::Any AstBuilder::visitUnobcArray(SafeCParser::UnobcArrayContext *ctx)
    {
        // TODO
        auto result = new var_def_node;
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();
        result->name = ctx->Identifier()->getSymbol()->getText();
        result->is_const = false;
        result->btype = BType::INT;
        result->is_obc = false;
        // result->array_length = visit(ctx->exp()).as<expr_node*>();
        if (ctx->exp())
        {
            auto array_length_n = visit(ctx->exp()).as<expr_node *>();
            result->array_length.reset(array_length_n);
        }
        else
        {
            // result->array_length = nullptr;
            auto array_length_n = new number_node;
            array_length_n->line = ctx->getStart()->getLine();
            array_length_n->pos = ctx->getStart()->getCharPositionInLine()+result->name.size();
            array_length_n->btype = BType::INT;
            array_length_n->number = -1; // Unknown length
            result->array_length=ptr<expr_node>(array_length_n);
        }
        result->initializers.clear();
        return result;
    }

    antlrcpp::Any AstBuilder::visitBlock(SafeCParser::BlockContext *ctx)
    {
        auto result = new block_node;

        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();

        for (auto block_item : ctx->blockItem())
        {
            auto block_item_n = visit(block_item).as<stmt_node *>();
            result->body.push_back(ptr<stmt_node>(block_item_n));
        }
        return result;
    }

    antlrcpp::Any AstBuilder::visitBlockItem(SafeCParser::BlockItemContext *ctx)
    {
        // TODO
        if (auto decl = ctx->decl())
        {
            return dynamic_cast<stmt_node *>(visit(decl).as<var_def_stmt_node *>());
        }
        else if (auto stmt = ctx->stmt())
        {
            return visit(stmt).as<stmt_node *>();
        }
        else
        {
            assert(0 && "Unknown BlockItem.");
        }
    }

    antlrcpp::Any AstBuilder::visitStmt(SafeCParser::StmtContext *ctx)
    {
        // TODO
        if (auto block = ctx->block())
        {
            return dynamic_cast<stmt_node *>(visit(block).as<block_node *>());
        }
        else if (auto lval = ctx->lval())
        {
            auto result = new assign_stmt_node;
            result->line = ctx->getStart()->getLine();
            result->pos = ctx->getStart()->getCharPositionInLine();
            auto lval_n = visit(lval).as<lval_node *>();
            result->target.reset(lval_n);
            auto exp_n = visit(ctx->exp()).as<expr_node *>();
            result->value.reset(exp_n);
            return dynamic_cast<stmt_node *>(result);
        }
        else if (ctx->Identifier())
        {
            auto result = new func_call_stmt_node;
            result->line = ctx->getStart()->getLine();
            result->pos = ctx->getStart()->getCharPositionInLine();
            result->name = ctx->Identifier()->getSymbol()->getText();
            return dynamic_cast<stmt_node *>(result);
        }
        else if (ctx->While())
        {
            auto result = new while_stmt_node;
            result->line = ctx->getStart()->getLine();
            result->pos = ctx->getStart()->getCharPositionInLine();
            auto cond_n = visit(ctx->cond()).as<cond_node *>();
            result->cond.reset(cond_n);
            auto stmt_n = visit(ctx->stmt(0)).as<stmt_node *>();
            result->body.reset(stmt_n);
            return dynamic_cast<stmt_node *>(result);
        }
        else if (ctx->If())
        {
            auto result = new if_stmt_node;
            result->line = ctx->getStart()->getLine();
            result->pos = ctx->getStart()->getCharPositionInLine();
            auto cond_n = visit(ctx->cond()).as<cond_node *>();
            result->cond.reset(cond_n);
            auto if_body_n = visit(ctx->stmt(0)).as<stmt_node *>();
            result->if_body.reset(if_body_n);
            if (ctx->Else())
            {
                auto else_body_n = visit(ctx->stmt(1)).as<stmt_node *>();
                result->else_body.reset(else_body_n);
            }
            return dynamic_cast<stmt_node *>(result);
        }
        else if (ctx->SemiColon())
        {
            auto result = new empty_stmt_node;
            result->line = ctx->getStart()->getLine();
            result->pos = ctx->getStart()->getCharPositionInLine();
            return dynamic_cast<stmt_node *>(result);
        }
        else
        {
            assert(0 && "Unknown Stmt.");
        }
    }

    antlrcpp::Any AstBuilder::visitCond(SafeCParser::CondContext *ctx)
    {
        // TODO
        if (auto cond = ctx->cond())
        {
            return visit(cond).as<cond_node *>();
        }
        else if (ctx->exp().size() == 2)
        {
            auto result = new cond_node;
            result->line = ctx->getStart()->getLine();
            result->pos = ctx->getStart()->getCharPositionInLine();
            auto lhs_exp_n = visit(ctx->exp(0)).as<expr_node *>();
            result->lhs.reset(lhs_exp_n);
            auto rhs_exp_n = visit(ctx->exp(1)).as<expr_node *>();
            result->rhs.reset(rhs_exp_n);

            if (ctx->Equal())
            {
                result->op = RelOp::EQUAL;
            }
            else if (ctx->NonEqual())
            {
                result->op = RelOp::NON_EQUAL;
            }
            else if (ctx->Less())
            {
                result->op = RelOp::LESS;
            }
            else if (ctx->LessEqual())
            {
                result->op = RelOp::LESS_EQUAL;
            }
            else if (ctx->Greater())
            {
                result->op = RelOp::GREATER;
            }
            else if (ctx->GreaterEqual())
            {
                result->op = RelOp::GREATER_EQUAL;
            }
            return result;
        }
        else
        {
            assert(0 && "Unknown Cond.");
        }
    }

    antlrcpp::Any AstBuilder::visitLval(SafeCParser::LvalContext *ctx)
    {
        // TODO
        auto result = new lval_node;
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();
        result->name = ctx->Identifier()->getSymbol()->getText();
        if (ctx->exp())
        {
            auto array_index_n = visit(ctx->exp()).as<expr_node *>();
            result->array_index.reset(array_index_n);
        }
        else
        {
            result->array_index = nullptr;
        }
        return result;
    }

    antlrcpp::Any AstBuilder::visitNumber(SafeCParser::NumberContext *ctx)
    {
        auto result = new number_node;
        result->btype = BType::INT;
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();
        auto num_str = ctx->IntConst()->getText();

        if (num_str.size() > 2 && num_str[0] == '0' &&
            (num_str[1] == 'x' || num_str[1] == 'X'))
        {
            // Hex
            result->number = std::stoi(num_str, 0, 16);
        }
        else
        {
            // Dec
            result->number = std::stoi(num_str, 0, 10);
        }
        return result;
    }

    antlrcpp::Any AstBuilder::visitExp(SafeCParser::ExpContext *ctx)
    {
        auto exps = ctx->exp();

        if (exps.size() == 2)
        {
            // binary op
            auto result = new binop_expr_node;
            result->line = ctx->getStart()->getLine();
            result->pos = ctx->getStart()->getCharPositionInLine();

            if (ctx->Plus())
            {
                result->op = BinOp::PLUS;
            }
            else if (ctx->Minus())
            {
                result->op = BinOp::MINUS;
            }
            else if (ctx->Multiply())
            {
                result->op = BinOp::MULTIPLY;
            }
            else if (ctx->Divide())
            {
                result->op = BinOp::DIVIDE;
            }
            else if (ctx->Modulo())
            {
                result->op = BinOp::MODULO;
            }

            auto lhs_exp_n = visit(ctx->exp(0)).as<expr_node *>();
            auto rhs_exp_n = visit(ctx->exp(1)).as<expr_node *>();
            result->lhs.reset(lhs_exp_n);
            result->rhs.reset(rhs_exp_n);

            return dynamic_cast<expr_node *>(result);

            // TODO: Handle other exprs.
            // else if (...) {
        }
        else if (exps.size() == 1 && (ctx->Plus() || ctx->Minus()))
        {
            // unary op
            auto result = new unaryop_expr_node;
            result->line = ctx->getStart()->getLine();
            result->pos = ctx->getStart()->getCharPositionInLine();

            if (ctx->Plus())
            {
                result->op = UnaryOp::PLUS;
            }
            else if (ctx->Minus())
            {
                result->op = UnaryOp::MINUS;
            }

            auto rhs_exp_n = visit(ctx->exp(0)).as<expr_node *>();
            result->rhs.reset(rhs_exp_n);

            return dynamic_cast<expr_node *>(result);
        }
        else if (exps.size() == 1 && ctx->LeftParen() && ctx->RightParen())
        {
            return visit(exps[0]).as<expr_node *>();
        }
        else if (exps.size() == 0)
        {
            // primary exp
            if (auto lval = ctx->lval())
            {
                return dynamic_cast<expr_node *>(visit(lval).as<lval_node *>());
            }
            else if (auto number = ctx->number())
            {
                return dynamic_cast<expr_node *>(visit(number).as<number_node *>());
            }
            else if (ctx->LeftParen() && ctx->RightParen())
            {
                return visit(ctx->exp(0)).as<expr_node *>();
            }
        }
        else
        {
            assert(0 && "Unkown exp.");
        }
    }

    ptr<ast_node> AstBuilder::operator()(antlr4::tree::ParseTree *ctx)
    {
        auto result = visit(ctx);

        if (result.is<ast_node *>())
            return ptr<ast_node>(result.as<ast_node *>());
        if (result.is<comp_unit_node *>())
            return ptr<ast_node>(result.as<comp_unit_node *>());
        if (result.is<comp_unit_child_node *>())
            return ptr<ast_node>(result.as<comp_unit_child_node *>());
        if (result.is<func_def_node *>())
            return ptr<ast_node>(result.as<func_def_node *>());
        if (result.is<expr_node *>())
            return ptr<ast_node>(result.as<expr_node *>());
        if (result.is<cond_node *>())
            return ptr<ast_node>(result.as<cond_node *>());
        if (result.is<binop_expr_node *>())
            return ptr<ast_node>(result.as<binop_expr_node *>());
        if (result.is<unaryop_expr_node *>())
            return ptr<ast_node>(result.as<unaryop_expr_node *>());
        if (result.is<lval_node *>())
            return ptr<ast_node>(result.as<lval_node *>());
        if (result.is<number_node *>())
            return ptr<ast_node>(result.as<number_node *>());
        if (result.is<stmt_node *>())
            return ptr<ast_node>(result.as<stmt_node *>());
        if (result.is<var_def_stmt_node *>())
            return ptr<ast_node>(result.as<var_def_stmt_node *>());
        if (result.is<assign_stmt_node *>())
            return ptr<ast_node>(result.as<assign_stmt_node *>());
        if (result.is<func_call_stmt_node *>())
            return ptr<ast_node>(result.as<func_call_stmt_node *>());
        if (result.is<block_node *>())
            return ptr<ast_node>(result.as<block_node *>());
        if (result.is<if_stmt_node *>())
            return ptr<ast_node>(result.as<if_stmt_node *>());
        if (result.is<while_stmt_node *>())
            return ptr<ast_node>(result.as<while_stmt_node *>());
        if (result.is<empty_stmt_node *>())
            return ptr<ast_node>(result.as<empty_stmt_node *>());

        return ptr<ast_node>(result.as<ast_node *>());
    }
} // namespace antlrcpp
