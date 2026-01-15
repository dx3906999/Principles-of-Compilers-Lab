#include "AstBuilder.h"

namespace antlrcpp {
antlrcpp::Any AstBuilder::visitCompUnit(SafeCParser::CompUnitContext* ctx) {
    auto result = new comp_unit_node;
    auto compile_units = ctx->children;

    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();

    // Ignore the last EOF in the for loop.
    for (auto i = 0; i < compile_units.size() - 1; i++) {
        if (auto decl =
                dynamic_cast<SafeCParser::DeclContext*>(compile_units[i])) {
            // global define
            auto global_def_stmt_n = visit(decl).as<stmt_node*>();
            auto var_def_stmt_n =
                dynamic_cast<var_def_stmt_node*>(global_def_stmt_n);
            result->comp_units.push_back(
                ptr<comp_unit_child_node>(var_def_stmt_n));

        } else if (auto func_def = dynamic_cast<SafeCParser::FuncDefContext*>(
                       compile_units[i])) {
            // function define
            auto func_def_n = visit(func_def).as<func_def_node*>();
            result->comp_units.push_back(ptr<comp_unit_child_node>(func_def_n));

        } else {
            // Error.
            log(compile_units[i]->getText());
            assert(0 && "Unknown Compile Unit.");
        }
    }
    return result;
}

antlrcpp::Any AstBuilder::visitDecl(SafeCParser::DeclContext* ctx) {

    if (auto const_decl = ctx->constDecl()) {
        return visit(const_decl);

    } else if (auto var_decl = ctx->varDecl()) {
        return visit(var_decl);

    } else {
        assert(0 && "Unknown DeclContext.");
    }
}

antlrcpp::Any AstBuilder::visitFuncDef(SafeCParser::FuncDefContext* ctx) {
    auto result = new func_def_node;

    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    result->name = ctx->Identifier()->getSymbol()->getText();
    result->body.reset(visit(ctx->block()).as<block_node*>());

    return result;
}

antlrcpp::Any AstBuilder::visitConstDecl(SafeCParser::ConstDeclContext* ctx) {
    auto result = new var_def_stmt_node;

    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();

    BType var_type;
    if (ctx->bType()->Int()) {
        var_type = BType::INT;
    } else {
        assert(0 && "Unknown bType.");
    }

    for (auto const_def : ctx->constDef()) {
        auto var_def_n = visit(const_def).as<var_def_node*>();

        var_def_n->btype = var_type;
        var_def_n->is_const = true;

        result->var_defs.push_back(ptr<var_def_node>(var_def_n));
    }

    return dynamic_cast<stmt_node*>(result);
}

antlrcpp::Any AstBuilder::visitConstDef(SafeCParser::ConstDefContext* ctx) {
    auto result = new var_def_node;

    if (auto array = ctx->array()) {
        // Array
        auto array_n = visit(array).as<var_def_node*>();
        delete (result);
        result = array_n;

        for (auto exp : ctx->exp()) {
            auto exp_n = visit(exp).as<expr_node*>();
            result->initializers.push_back(ptr<expr_node>(exp_n));
        }

        // Get array length.
        if (result->array_length == NULL && result->initializers.size() > 0) {
            auto length_n = new number_node;
            length_n->btype = BType::INT;
            length_n->number = result->initializers.size();
            if (result->is_obc) {
                length_n->line = array->obcArray()
                                     ->unobcArray()
                                     ->LeftBracket()
                                     ->getSymbol()
                                     ->getLine();
                length_n->pos = array->obcArray()
                                    ->unobcArray()
                                    ->LeftBracket()
                                    ->getSymbol()
                                    ->getCharPositionInLine();
            } else {
                length_n->line =
                    array->unobcArray()->LeftBracket()->getSymbol()->getLine();
                length_n->pos = array->unobcArray()
                                    ->LeftBracket()
                                    ->getSymbol()
                                    ->getCharPositionInLine();
            }
            result->array_length.reset(length_n);
        }

    } else if (ctx->Identifier()) {
        // Scalar
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();
        result->name = ctx->Identifier()->getSymbol()->getText();
        result->array_length = NULL;
        result->is_obc = false;

        auto exp_n = visit(ctx->exp(0)).as<expr_node*>();
        result->initializers.push_back(ptr<expr_node>(exp_n));
    } else {
        assert(0 && "Unknown ConstDef");
    }

    return result;
}

antlrcpp::Any AstBuilder::visitVarDecl(SafeCParser::VarDeclContext* ctx) {
    auto result = new var_def_stmt_node;

    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();

    BType var_type;
    if (ctx->bType()->Int()) {
        var_type = BType::INT;
    } else {
        assert(0 && "Unknown bType.");
    }

    for (auto var_def : ctx->varDef()) {
        auto var_def_n = visit(var_def).as<var_def_node*>();
        var_def_n->btype = var_type;
        var_def_n->is_const = false;

        result->var_defs.push_back(ptr<var_def_node>(var_def_n));
    }

    return dynamic_cast<stmt_node*>(result);
}

antlrcpp::Any AstBuilder::visitBType(SafeCParser::BTypeContext* ctx) {
    /* Nothing to do here. */
    return NULL;
}

antlrcpp::Any AstBuilder::visitVarDef(SafeCParser::VarDefContext* ctx) {
    auto result = new var_def_node;

    if (auto array = ctx->array()) {
        // Array
        auto array_n = visit(array).as<var_def_node*>();
        delete (result);
        result = array_n;

        if (ctx->Assign()) {
            for (auto exp : ctx->exp()) {
                auto exp_n = visit(exp).as<expr_node*>();
                result->initializers.push_back(ptr<expr_node>(exp_n));
            }
        }
        // Get array length.
        if (result->array_length == NULL && result->initializers.size() > 0) {
            auto length_n = new number_node;
            length_n->btype = BType::INT;
            length_n->number = result->initializers.size();
            if (result->is_obc) {
                length_n->line = array->obcArray()
                                     ->unobcArray()
                                     ->LeftBracket()
                                     ->getSymbol()
                                     ->getLine();
                length_n->pos = array->obcArray()
                                    ->unobcArray()
                                    ->LeftBracket()
                                    ->getSymbol()
                                    ->getCharPositionInLine();
            } else {
                length_n->line =
                    array->unobcArray()->LeftBracket()->getSymbol()->getLine();
                length_n->pos = array->unobcArray()
                                    ->LeftBracket()
                                    ->getSymbol()
                                    ->getCharPositionInLine();
            }
            result->array_length.reset(length_n);
        }

    } else if (ctx->Identifier()) {
        // Scalar
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();
        result->name = ctx->Identifier()->getSymbol()->getText();
        result->is_const = false;
        result->is_obc = false;

        result->array_length = NULL;

        if (ctx->Assign()) {
            auto exp_n = visit(ctx->exp(0)).as<expr_node*>();
            result->initializers.push_back(ptr<expr_node>(exp_n));
        }

    } else {
        assert(0 && "Unknown VarDef");
    }
    return result;
}

antlrcpp::Any AstBuilder::visitArray(SafeCParser::ArrayContext* ctx) {
    if (auto obc_array = ctx->obcArray()) {
        return visit(obc_array);
    } else if (auto unobc_array = ctx->unobcArray()) {
        return visit(unobc_array);
    } else {
        assert(0 && "Unknown Array");
    }
}

antlrcpp::Any AstBuilder::visitObcArray(SafeCParser::ObcArrayContext* ctx) {
    auto result = visitUnobcArray(ctx->unobcArray()).as<var_def_node*>();
    result->is_obc = true;
    return result;
}

antlrcpp::Any AstBuilder::visitUnobcArray(SafeCParser::UnobcArrayContext* ctx) {
    auto result = new var_def_node;

    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    result->name = ctx->Identifier()->getSymbol()->getText();
    result->array_length = NULL;
    result->is_obc = false;

    if (auto exp = ctx->exp()) {
        auto exp_n = visit(exp).as<expr_node*>();
        result->array_length = ptr<expr_node>(exp_n);
    }
    return result;
}

antlrcpp::Any AstBuilder::visitBlock(SafeCParser::BlockContext* ctx) {
    auto result = new block_node;

    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();

    for (auto block_item : ctx->blockItem()) {
        auto block_item_n = visit(block_item).as<stmt_node*>();
        result->body.push_back(ptr<stmt_node>(block_item_n));
    }
    return result;
}

antlrcpp::Any AstBuilder::visitBlockItem(SafeCParser::BlockItemContext* ctx) {
    if (ctx->decl()) {
        return visit(ctx->decl());
    } else if (ctx->stmt()) {
        return visit(ctx->stmt());
    } else {
        assert(0 && "Unknown blockItem.");
    }
}

antlrcpp::Any AstBuilder::visitStmt(SafeCParser::StmtContext* ctx) {
    if (ctx->lval()) {
        // Assign stmt
        auto result = new assign_stmt_node;

        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();

        auto lval_n = visit(ctx->lval()).as<lval_node*>();
        auto exp_n = visit(ctx->exp()).as<expr_node*>();
        result->target = ptr<lval_node>(lval_n);
        result->value = ptr<expr_node>(exp_n);

        return dynamic_cast<stmt_node*>(result);

    } else if (ctx->Identifier()) {
        // Call stmt
        auto result = new func_call_stmt_node;

        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();

        result->name = ctx->Identifier()->getSymbol()->getText();

        return dynamic_cast<stmt_node*>(result);

    } else if (ctx->block()) {
        // Inner block
        auto result = visit(ctx->block()).as<block_node*>();
        return dynamic_cast<stmt_node*>(result);

    } else if (ctx->If()) {
        // If stmt
        auto result = new if_stmt_node;

        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();

        auto cond = ctx->cond();
        auto if_body = ctx->stmt(0);
        result->cond.reset(visit(cond).as<cond_node*>());
        result->if_body.reset(visit(if_body).as<stmt_node*>());

        if (ctx->Else()) {
            auto else_body = ctx->stmt(1);
            result->else_body.reset(visit(else_body).as<stmt_node*>());
        }

        return dynamic_cast<stmt_node*>(result);

    } else if (ctx->While()) {
        // While stmt
        auto result = new while_stmt_node;

        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();

        auto cond = ctx->cond();
        auto while_body = ctx->stmt(0);
        result->cond.reset(visit(cond).as<cond_node*>());
        result->body.reset(visit(while_body).as<stmt_node*>());

        return dynamic_cast<stmt_node*>(result);

    } else if (ctx->SemiColon()) {
        // Empty stmt
        /* Nothing to do here */
        return NULL;
    } else {
        assert(0 && "Unknown stmt.");
    }
}

antlrcpp::Any AstBuilder::visitCond(SafeCParser::CondContext* ctx) {
    if (ctx->cond()) {
        return visit(ctx->cond());

    } else if (ctx->exp().size() == 2) {
        auto result = new cond_node;

        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();

        result->lhs.reset(visit(ctx->exp(0)).as<expr_node*>());
        result->rhs.reset(visit(ctx->exp(1)).as<expr_node*>());

        if (ctx->Equal()) {
            result->op = RelOp::EQUAL;
        } else if (ctx->NonEqual()) {
            result->op = RelOp::NON_EQUAL;
        } else if (ctx->Less()) {
            result->op = RelOp::LESS;
        } else if (ctx->Greater()) {
            result->op = RelOp::GREATER;
        } else if (ctx->LessEqual()) {
            result->op = RelOp::LESS_EQUAL;
        } else if (ctx->GreaterEqual()) {
            result->op = RelOp::GREATER_EQUAL;
        } else {
            assert(0 && "Unknown Relationship Operator.");
        }
        return result;
    } else {
        assert(0 && "Unknown Cond.");
    }
}

antlrcpp::Any AstBuilder::visitLval(SafeCParser::LvalContext* ctx) {
    auto result = new lval_node;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    result->name = ctx->Identifier()->getSymbol()->getText();
    if (auto index = ctx->exp()) {
        auto exp_n = visit(index).as<expr_node*>();
        result->array_index = ptr<expr_node>(exp_n);
    }
    return result;
}

antlrcpp::Any AstBuilder::visitNumber(SafeCParser::NumberContext* ctx) {
    auto result = new number_node;
    result->btype = BType::INT;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    auto num_str = ctx->IntConst()->getText();
    // Hex
    if (num_str.size() > 2 && num_str[0] == '0' &&
        (num_str[1] == 'x' || num_str[1] == 'X')) {
        result->number = std::stoi(num_str, 0, 16);
        // Dec
    } else {
        result->number = std::stoi(num_str, 0, 10);
    }
    return result;
}

antlrcpp::Any AstBuilder::visitExp(SafeCParser::ExpContext* ctx) {
    auto exps = ctx->exp();

    if (exps.size() == 2) {
        // exp op exp
        auto result = new binop_expr_node;
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();

        if (ctx->Plus()) {
            result->op = BinOp::PLUS;
        } else if (ctx->Minus()) {
            result->op = BinOp::MINUS;
        } else if (ctx->Multiply()) {
            result->op = BinOp::MULTIPLY;
        } else if (ctx->Divide()) {
            result->op = BinOp::DIVIDE;
        } else if (ctx->Modulo()) {
            result->op = BinOp::MODULO;
        }
        result->lhs.reset(visit(ctx->exp(0)).as<expr_node*>());
        result->rhs.reset(visit(ctx->exp(1)).as<expr_node*>());

        return dynamic_cast<expr_node*>(result);

    } else if (ctx->LeftParen() && ctx->RightParen()) {
        // LeftParen exp RightParen
        return visit(ctx->exp(0));

    } else if (exps.size() == 1) {
        // unaryop exp
        auto result = new unaryop_expr_node;
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();
        if (ctx->Plus()) {
            result->op = UnaryOp::PLUS;
        } else if (ctx->Minus()) {
            result->op = UnaryOp::MINUS;
        }
        result->rhs.reset(visit(ctx->exp(0)).as<expr_node*>());
        return dynamic_cast<expr_node*>(result);

    } else if (ctx->lval()) {
        auto result = visit(ctx->lval()).as<lval_node*>();
        return dynamic_cast<expr_node*>(result);

    } else if (ctx->number()) {
        auto result = visit(ctx->number()).as<number_node*>();
        return dynamic_cast<expr_node*>(result);

    } else {
        assert(0 && "Unkown exp.");
    }
}

ptr<ast_node> AstBuilder::operator()(antlr4::tree::ParseTree* ctx) {
    auto result = visit(ctx);

    if (result.is<ast_node*>())
        return ptr<ast_node>(result.as<ast_node*>());
    if (result.is<comp_unit_node*>())
        return ptr<ast_node>(result.as<comp_unit_node*>());
    if (result.is<comp_unit_child_node*>())
        return ptr<ast_node>(result.as<comp_unit_child_node*>());
    if (result.is<func_def_node*>())
        return ptr<ast_node>(result.as<func_def_node*>());
    if (result.is<expr_node*>())
        return ptr<ast_node>(result.as<expr_node*>());
    if (result.is<cond_node*>())
        return ptr<ast_node>(result.as<cond_node*>());
    if (result.is<binop_expr_node*>())
        return ptr<ast_node>(result.as<binop_expr_node*>());
    if (result.is<unaryop_expr_node*>())
        return ptr<ast_node>(result.as<unaryop_expr_node*>());
    if (result.is<lval_node*>())
        return ptr<ast_node>(result.as<lval_node*>());
    if (result.is<number_node*>())
        return ptr<ast_node>(result.as<number_node*>());
    if (result.is<stmt_node*>())
        return ptr<ast_node>(result.as<stmt_node*>());
    if (result.is<var_def_stmt_node*>())
        return ptr<ast_node>(result.as<var_def_stmt_node*>());
    if (result.is<assign_stmt_node*>())
        return ptr<ast_node>(result.as<assign_stmt_node*>());
    if (result.is<func_call_stmt_node*>())
        return ptr<ast_node>(result.as<func_call_stmt_node*>());
    if (result.is<block_node*>())
        return ptr<ast_node>(result.as<block_node*>());
    if (result.is<if_stmt_node*>())
        return ptr<ast_node>(result.as<if_stmt_node*>());
    if (result.is<while_stmt_node*>())
        return ptr<ast_node>(result.as<while_stmt_node*>());
    if (result.is<empty_stmt_node*>())
        return ptr<ast_node>(result.as<empty_stmt_node*>());

    return ptr<ast_node>(result.as<ast_node*>());
}
}  // namespace antlrcpp
