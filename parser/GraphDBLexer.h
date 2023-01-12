
// Generated from GraphDB.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"




class  GraphDBLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, SPACES = 20, 
    K_where = 21, K_drop = 22, K_graphset = 23, K_graph = 24, K_schema = 25, 
    K_insert = 26, K_into = 27, K_as = 28, K_remove = 29, K_from = 30, K_update = 31, 
    K_at = 32, K_by = 33, K_set = 34, K_query = 35, K_difference = 36, K_proj = 37, 
    K_for = 38, K_product = 39, K_align = 40, K_to = 41, K_on = 42, K_reduce = 43, 
    K_select = 44, K_map = 45, K_union = 46, K_join = 47, K_intersect = 48, 
    K_maximal = 49, K_vertex = 50, K_edge = 51, K_and = 52, K_or = 53, K_arrow = 54, 
    K_not = 55, K_exist = 56, K_foreach = 57, K_equal = 58, K_complete = 59, 
    K_hasedge = 60, K_graphequal = 61, K_unique = 62, K_sizegeq = 63, K_graphinset = 64, 
    K_subgraph = 65, K_inducedsub = 66, K_connect = 67, K_clique = 68, K_tdensesub = 69, 
    K_create = 70, K_int = 71, K_integer = 72, K_float = 73, K_double = 74, 
    K_char = 75, K_string = 76, K_true = 77, K_false = 78, K_file = 79, 
    K_load = 80, INTEGER_NUMBER = 81, NOT_INTEGER_NUMBER = 82, NAME_STRING = 83, 
    LETTER = 84, SYMBOL = 85, CHAR = 86, TEXT = 87
  };

  GraphDBLexer(antlr4::CharStream *input);
  ~GraphDBLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

