// Generated from SafeCParser.g4 by ANTLR 4.9.3
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class SafeCParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.9.3", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		Comma=1, SemiColon=2, Assign=3, LeftBracket=4, RightBracket=5, LeftBrace=6, 
		RightBrace=7, LeftParen=8, RightParen=9, If=10, Else=11, While=12, Equal=13, 
		NonEqual=14, Less=15, Greater=16, LessEqual=17, GreaterEqual=18, Plus=19, 
		Minus=20, Multiply=21, Divide=22, Modulo=23, Int=24, Void=25, Obc=26, 
		Const=27, Identifier=28, IntConst=29, BlockComment=30, LineComment=31, 
		WhiteSpace=32;
	public static final int
		RULE_compUnit = 0, RULE_decl = 1, RULE_funcDef = 2, RULE_constDecl = 3, 
		RULE_constDef = 4, RULE_varDecl = 5, RULE_bType = 6, RULE_varDef = 7, 
		RULE_array = 8, RULE_obcArray = 9, RULE_unobcArray = 10, RULE_block = 11, 
		RULE_blockItem = 12, RULE_stmt = 13, RULE_cond = 14, RULE_lval = 15, RULE_number = 16, 
		RULE_exp = 17;
	private static String[] makeRuleNames() {
		return new String[] {
			"compUnit", "decl", "funcDef", "constDecl", "constDef", "varDecl", "bType", 
			"varDef", "array", "obcArray", "unobcArray", "block", "blockItem", "stmt", 
			"cond", "lval", "number", "exp"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "','", "';'", "'='", "'['", "']'", "'{'", "'}'", "'('", "')'", 
			"'if'", "'else'", "'while'", "'=='", "'!='", "'<'", "'>'", "'<='", "'>='", 
			"'+'", "'-'", "'*'", "'/'", "'%'", "'int'", "'void'", "'obc'", "'const'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "Comma", "SemiColon", "Assign", "LeftBracket", "RightBracket", 
			"LeftBrace", "RightBrace", "LeftParen", "RightParen", "If", "Else", "While", 
			"Equal", "NonEqual", "Less", "Greater", "LessEqual", "GreaterEqual", 
			"Plus", "Minus", "Multiply", "Divide", "Modulo", "Int", "Void", "Obc", 
			"Const", "Identifier", "IntConst", "BlockComment", "LineComment", "WhiteSpace"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "SafeCParser.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public SafeCParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	public static class CompUnitContext extends ParserRuleContext {
		public TerminalNode EOF() { return getToken(SafeCParser.EOF, 0); }
		public List<DeclContext> decl() {
			return getRuleContexts(DeclContext.class);
		}
		public DeclContext decl(int i) {
			return getRuleContext(DeclContext.class,i);
		}
		public List<FuncDefContext> funcDef() {
			return getRuleContexts(FuncDefContext.class);
		}
		public FuncDefContext funcDef(int i) {
			return getRuleContext(FuncDefContext.class,i);
		}
		public CompUnitContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_compUnit; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).enterCompUnit(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).exitCompUnit(this);
		}
	}

	public final CompUnitContext compUnit() throws RecognitionException {
		CompUnitContext _localctx = new CompUnitContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_compUnit);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(38); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				setState(38);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case Int:
				case Const:
					{
					setState(36);
					decl();
					}
					break;
				case Void:
					{
					setState(37);
					funcDef();
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				}
				setState(40); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << Int) | (1L << Void) | (1L << Const))) != 0) );
			setState(42);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class DeclContext extends ParserRuleContext {
		public ConstDeclContext constDecl() {
			return getRuleContext(ConstDeclContext.class,0);
		}
		public VarDeclContext varDecl() {
			return getRuleContext(VarDeclContext.class,0);
		}
		public DeclContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_decl; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).enterDecl(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).exitDecl(this);
		}
	}

	public final DeclContext decl() throws RecognitionException {
		DeclContext _localctx = new DeclContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_decl);
		try {
			setState(46);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Const:
				enterOuterAlt(_localctx, 1);
				{
				setState(44);
				constDecl();
				}
				break;
			case Int:
				enterOuterAlt(_localctx, 2);
				{
				setState(45);
				varDecl();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FuncDefContext extends ParserRuleContext {
		public TerminalNode Void() { return getToken(SafeCParser.Void, 0); }
		public TerminalNode Identifier() { return getToken(SafeCParser.Identifier, 0); }
		public TerminalNode LeftParen() { return getToken(SafeCParser.LeftParen, 0); }
		public TerminalNode RightParen() { return getToken(SafeCParser.RightParen, 0); }
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public FuncDefContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_funcDef; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).enterFuncDef(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).exitFuncDef(this);
		}
	}

	public final FuncDefContext funcDef() throws RecognitionException {
		FuncDefContext _localctx = new FuncDefContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_funcDef);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(48);
			match(Void);
			setState(49);
			match(Identifier);
			setState(50);
			match(LeftParen);
			setState(51);
			match(RightParen);
			setState(52);
			block();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ConstDeclContext extends ParserRuleContext {
		public TerminalNode Const() { return getToken(SafeCParser.Const, 0); }
		public BTypeContext bType() {
			return getRuleContext(BTypeContext.class,0);
		}
		public List<ConstDefContext> constDef() {
			return getRuleContexts(ConstDefContext.class);
		}
		public ConstDefContext constDef(int i) {
			return getRuleContext(ConstDefContext.class,i);
		}
		public TerminalNode SemiColon() { return getToken(SafeCParser.SemiColon, 0); }
		public List<TerminalNode> Comma() { return getTokens(SafeCParser.Comma); }
		public TerminalNode Comma(int i) {
			return getToken(SafeCParser.Comma, i);
		}
		public ConstDeclContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constDecl; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).enterConstDecl(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).exitConstDecl(this);
		}
	}

	public final ConstDeclContext constDecl() throws RecognitionException {
		ConstDeclContext _localctx = new ConstDeclContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_constDecl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(54);
			match(Const);
			setState(55);
			bType();
			setState(56);
			constDef();
			setState(61);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==Comma) {
				{
				{
				setState(57);
				match(Comma);
				setState(58);
				constDef();
				}
				}
				setState(63);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(64);
			match(SemiColon);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ConstDefContext extends ParserRuleContext {
		public TerminalNode Identifier() { return getToken(SafeCParser.Identifier, 0); }
		public TerminalNode Assign() { return getToken(SafeCParser.Assign, 0); }
		public List<ExpContext> exp() {
			return getRuleContexts(ExpContext.class);
		}
		public ExpContext exp(int i) {
			return getRuleContext(ExpContext.class,i);
		}
		public ArrayContext array() {
			return getRuleContext(ArrayContext.class,0);
		}
		public TerminalNode LeftBrace() { return getToken(SafeCParser.LeftBrace, 0); }
		public TerminalNode RightBrace() { return getToken(SafeCParser.RightBrace, 0); }
		public List<TerminalNode> Comma() { return getTokens(SafeCParser.Comma); }
		public TerminalNode Comma(int i) {
			return getToken(SafeCParser.Comma, i);
		}
		public ConstDefContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constDef; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).enterConstDef(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).exitConstDef(this);
		}
	}

	public final ConstDefContext constDef() throws RecognitionException {
		ConstDefContext _localctx = new ConstDefContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_constDef);
		int _la;
		try {
			setState(82);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,5,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(66);
				match(Identifier);
				setState(67);
				match(Assign);
				setState(68);
				exp(0);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(69);
				array();
				setState(70);
				match(Assign);
				setState(71);
				match(LeftBrace);
				setState(72);
				exp(0);
				setState(77);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==Comma) {
					{
					{
					setState(73);
					match(Comma);
					setState(74);
					exp(0);
					}
					}
					setState(79);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(80);
				match(RightBrace);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class VarDeclContext extends ParserRuleContext {
		public BTypeContext bType() {
			return getRuleContext(BTypeContext.class,0);
		}
		public List<VarDefContext> varDef() {
			return getRuleContexts(VarDefContext.class);
		}
		public VarDefContext varDef(int i) {
			return getRuleContext(VarDefContext.class,i);
		}
		public TerminalNode SemiColon() { return getToken(SafeCParser.SemiColon, 0); }
		public List<TerminalNode> Comma() { return getTokens(SafeCParser.Comma); }
		public TerminalNode Comma(int i) {
			return getToken(SafeCParser.Comma, i);
		}
		public VarDeclContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_varDecl; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).enterVarDecl(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).exitVarDecl(this);
		}
	}

	public final VarDeclContext varDecl() throws RecognitionException {
		VarDeclContext _localctx = new VarDeclContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_varDecl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(84);
			bType();
			setState(85);
			varDef();
			setState(90);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==Comma) {
				{
				{
				setState(86);
				match(Comma);
				setState(87);
				varDef();
				}
				}
				setState(92);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(93);
			match(SemiColon);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class BTypeContext extends ParserRuleContext {
		public TerminalNode Int() { return getToken(SafeCParser.Int, 0); }
		public BTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_bType; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).enterBType(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).exitBType(this);
		}
	}

	public final BTypeContext bType() throws RecognitionException {
		BTypeContext _localctx = new BTypeContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_bType);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(95);
			match(Int);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class VarDefContext extends ParserRuleContext {
		public TerminalNode Identifier() { return getToken(SafeCParser.Identifier, 0); }
		public ArrayContext array() {
			return getRuleContext(ArrayContext.class,0);
		}
		public TerminalNode Assign() { return getToken(SafeCParser.Assign, 0); }
		public List<ExpContext> exp() {
			return getRuleContexts(ExpContext.class);
		}
		public ExpContext exp(int i) {
			return getRuleContext(ExpContext.class,i);
		}
		public TerminalNode LeftBrace() { return getToken(SafeCParser.LeftBrace, 0); }
		public TerminalNode RightBrace() { return getToken(SafeCParser.RightBrace, 0); }
		public List<TerminalNode> Comma() { return getTokens(SafeCParser.Comma); }
		public TerminalNode Comma(int i) {
			return getToken(SafeCParser.Comma, i);
		}
		public VarDefContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_varDef; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).enterVarDef(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).exitVarDef(this);
		}
	}

	public final VarDefContext varDef() throws RecognitionException {
		VarDefContext _localctx = new VarDefContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_varDef);
		int _la;
		try {
			setState(115);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,8,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(97);
				match(Identifier);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(98);
				array();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(99);
				match(Identifier);
				setState(100);
				match(Assign);
				setState(101);
				exp(0);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(102);
				array();
				setState(103);
				match(Assign);
				setState(104);
				match(LeftBrace);
				setState(105);
				exp(0);
				setState(110);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==Comma) {
					{
					{
					setState(106);
					match(Comma);
					setState(107);
					exp(0);
					}
					}
					setState(112);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(113);
				match(RightBrace);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ArrayContext extends ParserRuleContext {
		public ObcArrayContext obcArray() {
			return getRuleContext(ObcArrayContext.class,0);
		}
		public UnobcArrayContext unobcArray() {
			return getRuleContext(UnobcArrayContext.class,0);
		}
		public ArrayContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_array; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).enterArray(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).exitArray(this);
		}
	}

	public final ArrayContext array() throws RecognitionException {
		ArrayContext _localctx = new ArrayContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_array);
		try {
			setState(119);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Obc:
				enterOuterAlt(_localctx, 1);
				{
				setState(117);
				obcArray();
				}
				break;
			case Identifier:
				enterOuterAlt(_localctx, 2);
				{
				setState(118);
				unobcArray();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ObcArrayContext extends ParserRuleContext {
		public TerminalNode Obc() { return getToken(SafeCParser.Obc, 0); }
		public UnobcArrayContext unobcArray() {
			return getRuleContext(UnobcArrayContext.class,0);
		}
		public ObcArrayContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_obcArray; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).enterObcArray(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).exitObcArray(this);
		}
	}

	public final ObcArrayContext obcArray() throws RecognitionException {
		ObcArrayContext _localctx = new ObcArrayContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_obcArray);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(121);
			match(Obc);
			setState(122);
			unobcArray();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class UnobcArrayContext extends ParserRuleContext {
		public TerminalNode Identifier() { return getToken(SafeCParser.Identifier, 0); }
		public TerminalNode LeftBracket() { return getToken(SafeCParser.LeftBracket, 0); }
		public TerminalNode RightBracket() { return getToken(SafeCParser.RightBracket, 0); }
		public ExpContext exp() {
			return getRuleContext(ExpContext.class,0);
		}
		public UnobcArrayContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_unobcArray; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).enterUnobcArray(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).exitUnobcArray(this);
		}
	}

	public final UnobcArrayContext unobcArray() throws RecognitionException {
		UnobcArrayContext _localctx = new UnobcArrayContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_unobcArray);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(124);
			match(Identifier);
			setState(125);
			match(LeftBracket);
			setState(127);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << LeftParen) | (1L << Plus) | (1L << Minus) | (1L << Identifier) | (1L << IntConst))) != 0)) {
				{
				setState(126);
				exp(0);
				}
			}

			setState(129);
			match(RightBracket);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class BlockContext extends ParserRuleContext {
		public TerminalNode LeftBrace() { return getToken(SafeCParser.LeftBrace, 0); }
		public TerminalNode RightBrace() { return getToken(SafeCParser.RightBrace, 0); }
		public List<BlockItemContext> blockItem() {
			return getRuleContexts(BlockItemContext.class);
		}
		public BlockItemContext blockItem(int i) {
			return getRuleContext(BlockItemContext.class,i);
		}
		public BlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_block; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).enterBlock(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).exitBlock(this);
		}
	}

	public final BlockContext block() throws RecognitionException {
		BlockContext _localctx = new BlockContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_block);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(131);
			match(LeftBrace);
			setState(135);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << SemiColon) | (1L << LeftBrace) | (1L << LeftParen) | (1L << If) | (1L << While) | (1L << Plus) | (1L << Minus) | (1L << Int) | (1L << Const) | (1L << Identifier) | (1L << IntConst))) != 0)) {
				{
				{
				setState(132);
				blockItem();
				}
				}
				setState(137);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(138);
			match(RightBrace);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class BlockItemContext extends ParserRuleContext {
		public DeclContext decl() {
			return getRuleContext(DeclContext.class,0);
		}
		public StmtContext stmt() {
			return getRuleContext(StmtContext.class,0);
		}
		public BlockItemContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_blockItem; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).enterBlockItem(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).exitBlockItem(this);
		}
	}

	public final BlockItemContext blockItem() throws RecognitionException {
		BlockItemContext _localctx = new BlockItemContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_blockItem);
		try {
			setState(142);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Int:
			case Const:
				enterOuterAlt(_localctx, 1);
				{
				setState(140);
				decl();
				}
				break;
			case SemiColon:
			case LeftBrace:
			case LeftParen:
			case If:
			case While:
			case Plus:
			case Minus:
			case Identifier:
			case IntConst:
				enterOuterAlt(_localctx, 2);
				{
				setState(141);
				stmt();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class StmtContext extends ParserRuleContext {
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public LvalContext lval() {
			return getRuleContext(LvalContext.class,0);
		}
		public TerminalNode Assign() { return getToken(SafeCParser.Assign, 0); }
		public ExpContext exp() {
			return getRuleContext(ExpContext.class,0);
		}
		public TerminalNode SemiColon() { return getToken(SafeCParser.SemiColon, 0); }
		public TerminalNode Identifier() { return getToken(SafeCParser.Identifier, 0); }
		public TerminalNode LeftParen() { return getToken(SafeCParser.LeftParen, 0); }
		public TerminalNode RightParen() { return getToken(SafeCParser.RightParen, 0); }
		public TerminalNode While() { return getToken(SafeCParser.While, 0); }
		public CondContext cond() {
			return getRuleContext(CondContext.class,0);
		}
		public List<StmtContext> stmt() {
			return getRuleContexts(StmtContext.class);
		}
		public StmtContext stmt(int i) {
			return getRuleContext(StmtContext.class,i);
		}
		public TerminalNode If() { return getToken(SafeCParser.If, 0); }
		public TerminalNode Else() { return getToken(SafeCParser.Else, 0); }
		public StmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).enterStmt(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).exitStmt(this);
		}
	}

	public final StmtContext stmt() throws RecognitionException {
		StmtContext _localctx = new StmtContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_stmt);
		int _la;
		try {
			setState(173);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,15,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(144);
				block();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(145);
				lval();
				setState(146);
				match(Assign);
				setState(147);
				exp(0);
				setState(148);
				match(SemiColon);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(150);
				match(Identifier);
				setState(151);
				match(LeftParen);
				setState(152);
				match(RightParen);
				setState(153);
				match(SemiColon);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(155);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << LeftParen) | (1L << Plus) | (1L << Minus) | (1L << Identifier) | (1L << IntConst))) != 0)) {
					{
					setState(154);
					exp(0);
					}
				}

				setState(157);
				match(SemiColon);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(158);
				match(While);
				setState(159);
				match(LeftParen);
				setState(160);
				cond();
				setState(161);
				match(RightParen);
				setState(162);
				stmt();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(164);
				match(If);
				setState(165);
				match(LeftParen);
				setState(166);
				cond();
				setState(167);
				match(RightParen);
				setState(168);
				stmt();
				setState(171);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,14,_ctx) ) {
				case 1:
					{
					setState(169);
					match(Else);
					setState(170);
					stmt();
					}
					break;
				}
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class CondContext extends ParserRuleContext {
		public TerminalNode LeftParen() { return getToken(SafeCParser.LeftParen, 0); }
		public CondContext cond() {
			return getRuleContext(CondContext.class,0);
		}
		public TerminalNode RightParen() { return getToken(SafeCParser.RightParen, 0); }
		public List<ExpContext> exp() {
			return getRuleContexts(ExpContext.class);
		}
		public ExpContext exp(int i) {
			return getRuleContext(ExpContext.class,i);
		}
		public TerminalNode Equal() { return getToken(SafeCParser.Equal, 0); }
		public TerminalNode NonEqual() { return getToken(SafeCParser.NonEqual, 0); }
		public TerminalNode Less() { return getToken(SafeCParser.Less, 0); }
		public TerminalNode Greater() { return getToken(SafeCParser.Greater, 0); }
		public TerminalNode LessEqual() { return getToken(SafeCParser.LessEqual, 0); }
		public TerminalNode GreaterEqual() { return getToken(SafeCParser.GreaterEqual, 0); }
		public CondContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_cond; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).enterCond(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).exitCond(this);
		}
	}

	public final CondContext cond() throws RecognitionException {
		CondContext _localctx = new CondContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_cond);
		int _la;
		try {
			setState(183);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,16,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(175);
				match(LeftParen);
				setState(176);
				cond();
				setState(177);
				match(RightParen);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(179);
				exp(0);
				setState(180);
				_la = _input.LA(1);
				if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << Equal) | (1L << NonEqual) | (1L << Less) | (1L << Greater) | (1L << LessEqual) | (1L << GreaterEqual))) != 0)) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(181);
				exp(0);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class LvalContext extends ParserRuleContext {
		public TerminalNode Identifier() { return getToken(SafeCParser.Identifier, 0); }
		public TerminalNode LeftBracket() { return getToken(SafeCParser.LeftBracket, 0); }
		public ExpContext exp() {
			return getRuleContext(ExpContext.class,0);
		}
		public TerminalNode RightBracket() { return getToken(SafeCParser.RightBracket, 0); }
		public LvalContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_lval; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).enterLval(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).exitLval(this);
		}
	}

	public final LvalContext lval() throws RecognitionException {
		LvalContext _localctx = new LvalContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_lval);
		try {
			setState(191);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,17,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(185);
				match(Identifier);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(186);
				match(Identifier);
				setState(187);
				match(LeftBracket);
				setState(188);
				exp(0);
				setState(189);
				match(RightBracket);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class NumberContext extends ParserRuleContext {
		public TerminalNode IntConst() { return getToken(SafeCParser.IntConst, 0); }
		public NumberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_number; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).enterNumber(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).exitNumber(this);
		}
	}

	public final NumberContext number() throws RecognitionException {
		NumberContext _localctx = new NumberContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_number);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(193);
			match(IntConst);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExpContext extends ParserRuleContext {
		public TerminalNode LeftParen() { return getToken(SafeCParser.LeftParen, 0); }
		public List<ExpContext> exp() {
			return getRuleContexts(ExpContext.class);
		}
		public ExpContext exp(int i) {
			return getRuleContext(ExpContext.class,i);
		}
		public TerminalNode RightParen() { return getToken(SafeCParser.RightParen, 0); }
		public TerminalNode Plus() { return getToken(SafeCParser.Plus, 0); }
		public TerminalNode Minus() { return getToken(SafeCParser.Minus, 0); }
		public LvalContext lval() {
			return getRuleContext(LvalContext.class,0);
		}
		public NumberContext number() {
			return getRuleContext(NumberContext.class,0);
		}
		public TerminalNode Multiply() { return getToken(SafeCParser.Multiply, 0); }
		public TerminalNode Divide() { return getToken(SafeCParser.Divide, 0); }
		public TerminalNode Modulo() { return getToken(SafeCParser.Modulo, 0); }
		public ExpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_exp; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).enterExp(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SafeCParserListener ) ((SafeCParserListener)listener).exitExp(this);
		}
	}

	public final ExpContext exp() throws RecognitionException {
		return exp(0);
	}

	private ExpContext exp(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		ExpContext _localctx = new ExpContext(_ctx, _parentState);
		ExpContext _prevctx = _localctx;
		int _startState = 34;
		enterRecursionRule(_localctx, 34, RULE_exp, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(204);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case LeftParen:
				{
				setState(196);
				match(LeftParen);
				setState(197);
				exp(0);
				setState(198);
				match(RightParen);
				}
				break;
			case Plus:
			case Minus:
				{
				setState(200);
				_la = _input.LA(1);
				if ( !(_la==Plus || _la==Minus) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(201);
				exp(5);
				}
				break;
			case Identifier:
				{
				setState(202);
				lval();
				}
				break;
			case IntConst:
				{
				setState(203);
				number();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			_ctx.stop = _input.LT(-1);
			setState(214);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,20,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(212);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,19,_ctx) ) {
					case 1:
						{
						_localctx = new ExpContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_exp);
						setState(206);
						if (!(precpred(_ctx, 4))) throw new FailedPredicateException(this, "precpred(_ctx, 4)");
						setState(207);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << Multiply) | (1L << Divide) | (1L << Modulo))) != 0)) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(208);
						exp(5);
						}
						break;
					case 2:
						{
						_localctx = new ExpContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_exp);
						setState(209);
						if (!(precpred(_ctx, 3))) throw new FailedPredicateException(this, "precpred(_ctx, 3)");
						setState(210);
						_la = _input.LA(1);
						if ( !(_la==Plus || _la==Minus) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(211);
						exp(4);
						}
						break;
					}
					} 
				}
				setState(216);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,20,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 17:
			return exp_sempred((ExpContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean exp_sempred(ExpContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 4);
		case 1:
			return precpred(_ctx, 3);
		}
		return true;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\"\u00dc\4\2\t\2\4"+
		"\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t"+
		"\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\3\2\3\2\6\2)\n\2\r\2\16\2*\3\2\3\2\3\3\3\3\5\3\61\n\3\3\4\3"+
		"\4\3\4\3\4\3\4\3\4\3\5\3\5\3\5\3\5\3\5\7\5>\n\5\f\5\16\5A\13\5\3\5\3\5"+
		"\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\7\6N\n\6\f\6\16\6Q\13\6\3\6\3\6\5"+
		"\6U\n\6\3\7\3\7\3\7\3\7\7\7[\n\7\f\7\16\7^\13\7\3\7\3\7\3\b\3\b\3\t\3"+
		"\t\3\t\3\t\3\t\3\t\3\t\3\t\3\t\3\t\3\t\7\to\n\t\f\t\16\tr\13\t\3\t\3\t"+
		"\5\tv\n\t\3\n\3\n\5\nz\n\n\3\13\3\13\3\13\3\f\3\f\3\f\5\f\u0082\n\f\3"+
		"\f\3\f\3\r\3\r\7\r\u0088\n\r\f\r\16\r\u008b\13\r\3\r\3\r\3\16\3\16\5\16"+
		"\u0091\n\16\3\17\3\17\3\17\3\17\3\17\3\17\3\17\3\17\3\17\3\17\3\17\5\17"+
		"\u009e\n\17\3\17\3\17\3\17\3\17\3\17\3\17\3\17\3\17\3\17\3\17\3\17\3\17"+
		"\3\17\3\17\5\17\u00ae\n\17\5\17\u00b0\n\17\3\20\3\20\3\20\3\20\3\20\3"+
		"\20\3\20\3\20\5\20\u00ba\n\20\3\21\3\21\3\21\3\21\3\21\3\21\5\21\u00c2"+
		"\n\21\3\22\3\22\3\23\3\23\3\23\3\23\3\23\3\23\3\23\3\23\3\23\5\23\u00cf"+
		"\n\23\3\23\3\23\3\23\3\23\3\23\3\23\7\23\u00d7\n\23\f\23\16\23\u00da\13"+
		"\23\3\23\2\3$\24\2\4\6\b\n\f\16\20\22\24\26\30\32\34\36 \"$\2\5\3\2\17"+
		"\24\3\2\25\26\3\2\27\31\2\u00e6\2(\3\2\2\2\4\60\3\2\2\2\6\62\3\2\2\2\b"+
		"8\3\2\2\2\nT\3\2\2\2\fV\3\2\2\2\16a\3\2\2\2\20u\3\2\2\2\22y\3\2\2\2\24"+
		"{\3\2\2\2\26~\3\2\2\2\30\u0085\3\2\2\2\32\u0090\3\2\2\2\34\u00af\3\2\2"+
		"\2\36\u00b9\3\2\2\2 \u00c1\3\2\2\2\"\u00c3\3\2\2\2$\u00ce\3\2\2\2&)\5"+
		"\4\3\2\')\5\6\4\2(&\3\2\2\2(\'\3\2\2\2)*\3\2\2\2*(\3\2\2\2*+\3\2\2\2+"+
		",\3\2\2\2,-\7\2\2\3-\3\3\2\2\2.\61\5\b\5\2/\61\5\f\7\2\60.\3\2\2\2\60"+
		"/\3\2\2\2\61\5\3\2\2\2\62\63\7\33\2\2\63\64\7\36\2\2\64\65\7\n\2\2\65"+
		"\66\7\13\2\2\66\67\5\30\r\2\67\7\3\2\2\289\7\35\2\29:\5\16\b\2:?\5\n\6"+
		"\2;<\7\3\2\2<>\5\n\6\2=;\3\2\2\2>A\3\2\2\2?=\3\2\2\2?@\3\2\2\2@B\3\2\2"+
		"\2A?\3\2\2\2BC\7\4\2\2C\t\3\2\2\2DE\7\36\2\2EF\7\5\2\2FU\5$\23\2GH\5\22"+
		"\n\2HI\7\5\2\2IJ\7\b\2\2JO\5$\23\2KL\7\3\2\2LN\5$\23\2MK\3\2\2\2NQ\3\2"+
		"\2\2OM\3\2\2\2OP\3\2\2\2PR\3\2\2\2QO\3\2\2\2RS\7\t\2\2SU\3\2\2\2TD\3\2"+
		"\2\2TG\3\2\2\2U\13\3\2\2\2VW\5\16\b\2W\\\5\20\t\2XY\7\3\2\2Y[\5\20\t\2"+
		"ZX\3\2\2\2[^\3\2\2\2\\Z\3\2\2\2\\]\3\2\2\2]_\3\2\2\2^\\\3\2\2\2_`\7\4"+
		"\2\2`\r\3\2\2\2ab\7\32\2\2b\17\3\2\2\2cv\7\36\2\2dv\5\22\n\2ef\7\36\2"+
		"\2fg\7\5\2\2gv\5$\23\2hi\5\22\n\2ij\7\5\2\2jk\7\b\2\2kp\5$\23\2lm\7\3"+
		"\2\2mo\5$\23\2nl\3\2\2\2or\3\2\2\2pn\3\2\2\2pq\3\2\2\2qs\3\2\2\2rp\3\2"+
		"\2\2st\7\t\2\2tv\3\2\2\2uc\3\2\2\2ud\3\2\2\2ue\3\2\2\2uh\3\2\2\2v\21\3"+
		"\2\2\2wz\5\24\13\2xz\5\26\f\2yw\3\2\2\2yx\3\2\2\2z\23\3\2\2\2{|\7\34\2"+
		"\2|}\5\26\f\2}\25\3\2\2\2~\177\7\36\2\2\177\u0081\7\6\2\2\u0080\u0082"+
		"\5$\23\2\u0081\u0080\3\2\2\2\u0081\u0082\3\2\2\2\u0082\u0083\3\2\2\2\u0083"+
		"\u0084\7\7\2\2\u0084\27\3\2\2\2\u0085\u0089\7\b\2\2\u0086\u0088\5\32\16"+
		"\2\u0087\u0086\3\2\2\2\u0088\u008b\3\2\2\2\u0089\u0087\3\2\2\2\u0089\u008a"+
		"\3\2\2\2\u008a\u008c\3\2\2\2\u008b\u0089\3\2\2\2\u008c\u008d\7\t\2\2\u008d"+
		"\31\3\2\2\2\u008e\u0091\5\4\3\2\u008f\u0091\5\34\17\2\u0090\u008e\3\2"+
		"\2\2\u0090\u008f\3\2\2\2\u0091\33\3\2\2\2\u0092\u00b0\5\30\r\2\u0093\u0094"+
		"\5 \21\2\u0094\u0095\7\5\2\2\u0095\u0096\5$\23\2\u0096\u0097\7\4\2\2\u0097"+
		"\u00b0\3\2\2\2\u0098\u0099\7\36\2\2\u0099\u009a\7\n\2\2\u009a\u009b\7"+
		"\13\2\2\u009b\u00b0\7\4\2\2\u009c\u009e\5$\23\2\u009d\u009c\3\2\2\2\u009d"+
		"\u009e\3\2\2\2\u009e\u009f\3\2\2\2\u009f\u00b0\7\4\2\2\u00a0\u00a1\7\16"+
		"\2\2\u00a1\u00a2\7\n\2\2\u00a2\u00a3\5\36\20\2\u00a3\u00a4\7\13\2\2\u00a4"+
		"\u00a5\5\34\17\2\u00a5\u00b0\3\2\2\2\u00a6\u00a7\7\f\2\2\u00a7\u00a8\7"+
		"\n\2\2\u00a8\u00a9\5\36\20\2\u00a9\u00aa\7\13\2\2\u00aa\u00ad\5\34\17"+
		"\2\u00ab\u00ac\7\r\2\2\u00ac\u00ae\5\34\17\2\u00ad\u00ab\3\2\2\2\u00ad"+
		"\u00ae\3\2\2\2\u00ae\u00b0\3\2\2\2\u00af\u0092\3\2\2\2\u00af\u0093\3\2"+
		"\2\2\u00af\u0098\3\2\2\2\u00af\u009d\3\2\2\2\u00af\u00a0\3\2\2\2\u00af"+
		"\u00a6\3\2\2\2\u00b0\35\3\2\2\2\u00b1\u00b2\7\n\2\2\u00b2\u00b3\5\36\20"+
		"\2\u00b3\u00b4\7\13\2\2\u00b4\u00ba\3\2\2\2\u00b5\u00b6\5$\23\2\u00b6"+
		"\u00b7\t\2\2\2\u00b7\u00b8\5$\23\2\u00b8\u00ba\3\2\2\2\u00b9\u00b1\3\2"+
		"\2\2\u00b9\u00b5\3\2\2\2\u00ba\37\3\2\2\2\u00bb\u00c2\7\36\2\2\u00bc\u00bd"+
		"\7\36\2\2\u00bd\u00be\7\6\2\2\u00be\u00bf\5$\23\2\u00bf\u00c0\7\7\2\2"+
		"\u00c0\u00c2\3\2\2\2\u00c1\u00bb\3\2\2\2\u00c1\u00bc\3\2\2\2\u00c2!\3"+
		"\2\2\2\u00c3\u00c4\7\37\2\2\u00c4#\3\2\2\2\u00c5\u00c6\b\23\1\2\u00c6"+
		"\u00c7\7\n\2\2\u00c7\u00c8\5$\23\2\u00c8\u00c9\7\13\2\2\u00c9\u00cf\3"+
		"\2\2\2\u00ca\u00cb\t\3\2\2\u00cb\u00cf\5$\23\7\u00cc\u00cf\5 \21\2\u00cd"+
		"\u00cf\5\"\22\2\u00ce\u00c5\3\2\2\2\u00ce\u00ca\3\2\2\2\u00ce\u00cc\3"+
		"\2\2\2\u00ce\u00cd\3\2\2\2\u00cf\u00d8\3\2\2\2\u00d0\u00d1\f\6\2\2\u00d1"+
		"\u00d2\t\4\2\2\u00d2\u00d7\5$\23\7\u00d3\u00d4\f\5\2\2\u00d4\u00d5\t\3"+
		"\2\2\u00d5\u00d7\5$\23\6\u00d6\u00d0\3\2\2\2\u00d6\u00d3\3\2\2\2\u00d7"+
		"\u00da\3\2\2\2\u00d8\u00d6\3\2\2\2\u00d8\u00d9\3\2\2\2\u00d9%\3\2\2\2"+
		"\u00da\u00d8\3\2\2\2\27(*\60?OT\\puy\u0081\u0089\u0090\u009d\u00ad\u00af"+
		"\u00b9\u00c1\u00ce\u00d6\u00d8";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}