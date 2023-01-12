
// Generated from GraphDB.g4 by ANTLR 4.7.2


#include "GraphDBListener.h"
#include "GraphDBVisitor.h"

#include "GraphDBParser.h"


using namespace antlrcpp;
using namespace antlr4;

GraphDBParser::GraphDBParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

GraphDBParser::~GraphDBParser() {
  delete _interpreter;
}

std::string GraphDBParser::getGrammarFileName() const {
  return "GraphDB.g4";
}

const std::vector<std::string>& GraphDBParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& GraphDBParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- StatementContext ------------------------------------------------------------------

GraphDBParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::DmlStatementContext* GraphDBParser::StatementContext::dmlStatement() {
  return getRuleContext<GraphDBParser::DmlStatementContext>(0);
}

GraphDBParser::DdlStatementContext* GraphDBParser::StatementContext::ddlStatement() {
  return getRuleContext<GraphDBParser::DdlStatementContext>(0);
}


size_t GraphDBParser::StatementContext::getRuleIndex() const {
  return GraphDBParser::RuleStatement;
}

void GraphDBParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void GraphDBParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


antlrcpp::Any GraphDBParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::StatementContext* GraphDBParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 0, GraphDBParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(228);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GraphDBParser::T__1:
      case GraphDBParser::K_insert:
      case GraphDBParser::K_remove:
      case GraphDBParser::K_update:
      case GraphDBParser::K_select:
      case GraphDBParser::NAME_STRING: {
        enterOuterAlt(_localctx, 1);
        setState(222);
        dmlStatement();
        setState(223);
        match(GraphDBParser::T__0);
        break;
      }

      case GraphDBParser::K_drop:
      case GraphDBParser::K_create:
      case GraphDBParser::K_load: {
        enterOuterAlt(_localctx, 2);
        setState(225);
        ddlStatement();
        setState(226);
        match(GraphDBParser::T__0);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DmlStatementContext ------------------------------------------------------------------

GraphDBParser::DmlStatementContext::DmlStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::InsertStatContext* GraphDBParser::DmlStatementContext::insertStat() {
  return getRuleContext<GraphDBParser::InsertStatContext>(0);
}

GraphDBParser::RemoveStatContext* GraphDBParser::DmlStatementContext::removeStat() {
  return getRuleContext<GraphDBParser::RemoveStatContext>(0);
}

GraphDBParser::UpdateStatContext* GraphDBParser::DmlStatementContext::updateStat() {
  return getRuleContext<GraphDBParser::UpdateStatContext>(0);
}

GraphDBParser::QueryStatContext* GraphDBParser::DmlStatementContext::queryStat() {
  return getRuleContext<GraphDBParser::QueryStatContext>(0);
}


size_t GraphDBParser::DmlStatementContext::getRuleIndex() const {
  return GraphDBParser::RuleDmlStatement;
}

void GraphDBParser::DmlStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDmlStatement(this);
}

void GraphDBParser::DmlStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDmlStatement(this);
}


antlrcpp::Any GraphDBParser::DmlStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitDmlStatement(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::DmlStatementContext* GraphDBParser::dmlStatement() {
  DmlStatementContext *_localctx = _tracker.createInstance<DmlStatementContext>(_ctx, getState());
  enterRule(_localctx, 2, GraphDBParser::RuleDmlStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(234);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GraphDBParser::K_insert: {
        enterOuterAlt(_localctx, 1);
        setState(230);
        insertStat();
        break;
      }

      case GraphDBParser::K_remove: {
        enterOuterAlt(_localctx, 2);
        setState(231);
        removeStat();
        break;
      }

      case GraphDBParser::K_update: {
        enterOuterAlt(_localctx, 3);
        setState(232);
        updateStat();
        break;
      }

      case GraphDBParser::T__1:
      case GraphDBParser::K_select:
      case GraphDBParser::NAME_STRING: {
        enterOuterAlt(_localctx, 4);
        setState(233);
        queryStat(0);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InsertStatContext ------------------------------------------------------------------

GraphDBParser::InsertStatContext::InsertStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::InsertGsetStatContext* GraphDBParser::InsertStatContext::insertGsetStat() {
  return getRuleContext<GraphDBParser::InsertGsetStatContext>(0);
}

GraphDBParser::InsertGStatContext* GraphDBParser::InsertStatContext::insertGStat() {
  return getRuleContext<GraphDBParser::InsertGStatContext>(0);
}


size_t GraphDBParser::InsertStatContext::getRuleIndex() const {
  return GraphDBParser::RuleInsertStat;
}

void GraphDBParser::InsertStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInsertStat(this);
}

void GraphDBParser::InsertStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInsertStat(this);
}


antlrcpp::Any GraphDBParser::InsertStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitInsertStat(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::InsertStatContext* GraphDBParser::insertStat() {
  InsertStatContext *_localctx = _tracker.createInstance<InsertStatContext>(_ctx, getState());
  enterRule(_localctx, 4, GraphDBParser::RuleInsertStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(238);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(236);
      insertGsetStat();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(237);
      insertGStat();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RemoveStatContext ------------------------------------------------------------------

GraphDBParser::RemoveStatContext::RemoveStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::RemoveGsetStatContext* GraphDBParser::RemoveStatContext::removeGsetStat() {
  return getRuleContext<GraphDBParser::RemoveGsetStatContext>(0);
}

GraphDBParser::RemoveGStatContext* GraphDBParser::RemoveStatContext::removeGStat() {
  return getRuleContext<GraphDBParser::RemoveGStatContext>(0);
}


size_t GraphDBParser::RemoveStatContext::getRuleIndex() const {
  return GraphDBParser::RuleRemoveStat;
}

void GraphDBParser::RemoveStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRemoveStat(this);
}

void GraphDBParser::RemoveStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRemoveStat(this);
}


antlrcpp::Any GraphDBParser::RemoveStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitRemoveStat(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::RemoveStatContext* GraphDBParser::removeStat() {
  RemoveStatContext *_localctx = _tracker.createInstance<RemoveStatContext>(_ctx, getState());
  enterRule(_localctx, 6, GraphDBParser::RuleRemoveStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(242);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(240);
      removeGsetStat();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(241);
      removeGStat();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InsertGsetStatContext ------------------------------------------------------------------

GraphDBParser::InsertGsetStatContext::InsertGsetStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::InsertGsetStatContext::K_insert() {
  return getToken(GraphDBParser::K_insert, 0);
}

tree::TerminalNode* GraphDBParser::InsertGsetStatContext::K_into() {
  return getToken(GraphDBParser::K_into, 0);
}

tree::TerminalNode* GraphDBParser::InsertGsetStatContext::K_graphset() {
  return getToken(GraphDBParser::K_graphset, 0);
}

GraphDBParser::GsidContext* GraphDBParser::InsertGsetStatContext::gsid() {
  return getRuleContext<GraphDBParser::GsidContext>(0);
}

GraphDBParser::GidListContext* GraphDBParser::InsertGsetStatContext::gidList() {
  return getRuleContext<GraphDBParser::GidListContext>(0);
}


size_t GraphDBParser::InsertGsetStatContext::getRuleIndex() const {
  return GraphDBParser::RuleInsertGsetStat;
}

void GraphDBParser::InsertGsetStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInsertGsetStat(this);
}

void GraphDBParser::InsertGsetStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInsertGsetStat(this);
}


antlrcpp::Any GraphDBParser::InsertGsetStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitInsertGsetStat(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::InsertGsetStatContext* GraphDBParser::insertGsetStat() {
  InsertGsetStatContext *_localctx = _tracker.createInstance<InsertGsetStatContext>(_ctx, getState());
  enterRule(_localctx, 8, GraphDBParser::RuleInsertGsetStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(244);
    match(GraphDBParser::K_insert);
    setState(245);
    match(GraphDBParser::K_into);
    setState(246);
    match(GraphDBParser::K_graphset);
    setState(247);
    gsid();
    setState(248);
    match(GraphDBParser::T__1);
    setState(249);
    gidList();
    setState(250);
    match(GraphDBParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InsertGStatContext ------------------------------------------------------------------

GraphDBParser::InsertGStatContext::InsertGStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::InsertGStatContext::K_insert() {
  return getToken(GraphDBParser::K_insert, 0);
}

GraphDBParser::GraphContext* GraphDBParser::InsertGStatContext::graph() {
  return getRuleContext<GraphDBParser::GraphContext>(0);
}

tree::TerminalNode* GraphDBParser::InsertGStatContext::K_into() {
  return getToken(GraphDBParser::K_into, 0);
}

std::vector<tree::TerminalNode *> GraphDBParser::InsertGStatContext::K_graph() {
  return getTokens(GraphDBParser::K_graph);
}

tree::TerminalNode* GraphDBParser::InsertGStatContext::K_graph(size_t i) {
  return getToken(GraphDBParser::K_graph, i);
}

std::vector<GraphDBParser::GidContext *> GraphDBParser::InsertGStatContext::gid() {
  return getRuleContexts<GraphDBParser::GidContext>();
}

GraphDBParser::GidContext* GraphDBParser::InsertGStatContext::gid(size_t i) {
  return getRuleContext<GraphDBParser::GidContext>(i);
}

tree::TerminalNode* GraphDBParser::InsertGStatContext::K_file() {
  return getToken(GraphDBParser::K_file, 0);
}

GraphDBParser::FilenamelistContext* GraphDBParser::InsertGStatContext::filenamelist() {
  return getRuleContext<GraphDBParser::FilenamelistContext>(0);
}


size_t GraphDBParser::InsertGStatContext::getRuleIndex() const {
  return GraphDBParser::RuleInsertGStat;
}

void GraphDBParser::InsertGStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInsertGStat(this);
}

void GraphDBParser::InsertGStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInsertGStat(this);
}


antlrcpp::Any GraphDBParser::InsertGStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitInsertGStat(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::InsertGStatContext* GraphDBParser::insertGStat() {
  InsertGStatContext *_localctx = _tracker.createInstance<InsertGStatContext>(_ctx, getState());
  enterRule(_localctx, 10, GraphDBParser::RuleInsertGStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(272);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(252);
      match(GraphDBParser::K_insert);
      setState(253);
      graph();
      setState(254);
      match(GraphDBParser::K_into);
      setState(255);
      match(GraphDBParser::K_graph);
      setState(256);
      gid();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(258);
      match(GraphDBParser::K_insert);
      setState(259);
      match(GraphDBParser::K_file);
      setState(260);
      filenamelist();
      setState(261);
      match(GraphDBParser::K_into);
      setState(262);
      match(GraphDBParser::K_graph);
      setState(263);
      gid();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(265);
      match(GraphDBParser::K_insert);
      setState(266);
      match(GraphDBParser::K_graph);
      setState(267);
      gid();
      setState(268);
      match(GraphDBParser::K_into);
      setState(269);
      match(GraphDBParser::K_graph);
      setState(270);
      gid();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GraphNameItemContext ------------------------------------------------------------------

GraphDBParser::GraphNameItemContext::GraphNameItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::GraphContext* GraphDBParser::GraphNameItemContext::graph() {
  return getRuleContext<GraphDBParser::GraphContext>(0);
}

tree::TerminalNode* GraphDBParser::GraphNameItemContext::K_as() {
  return getToken(GraphDBParser::K_as, 0);
}

GraphDBParser::GidContext* GraphDBParser::GraphNameItemContext::gid() {
  return getRuleContext<GraphDBParser::GidContext>(0);
}


size_t GraphDBParser::GraphNameItemContext::getRuleIndex() const {
  return GraphDBParser::RuleGraphNameItem;
}

void GraphDBParser::GraphNameItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGraphNameItem(this);
}

void GraphDBParser::GraphNameItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGraphNameItem(this);
}


antlrcpp::Any GraphDBParser::GraphNameItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitGraphNameItem(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::GraphNameItemContext* GraphDBParser::graphNameItem() {
  GraphNameItemContext *_localctx = _tracker.createInstance<GraphNameItemContext>(_ctx, getState());
  enterRule(_localctx, 12, GraphDBParser::RuleGraphNameItem);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(279);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GraphDBParser::T__1: {
        enterOuterAlt(_localctx, 1);
        setState(274);
        graph();
        setState(275);
        match(GraphDBParser::K_as);
        setState(276);
        gid();
        break;
      }

      case GraphDBParser::NAME_STRING: {
        enterOuterAlt(_localctx, 2);
        setState(278);
        gid();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GraphNameListContext ------------------------------------------------------------------

GraphDBParser::GraphNameListContext::GraphNameListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::GraphNameItemContext* GraphDBParser::GraphNameListContext::graphNameItem() {
  return getRuleContext<GraphDBParser::GraphNameItemContext>(0);
}

GraphDBParser::GraphNameListContext* GraphDBParser::GraphNameListContext::graphNameList() {
  return getRuleContext<GraphDBParser::GraphNameListContext>(0);
}


size_t GraphDBParser::GraphNameListContext::getRuleIndex() const {
  return GraphDBParser::RuleGraphNameList;
}

void GraphDBParser::GraphNameListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGraphNameList(this);
}

void GraphDBParser::GraphNameListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGraphNameList(this);
}


antlrcpp::Any GraphDBParser::GraphNameListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitGraphNameList(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::GraphNameListContext* GraphDBParser::graphNameList() {
  GraphNameListContext *_localctx = _tracker.createInstance<GraphNameListContext>(_ctx, getState());
  enterRule(_localctx, 14, GraphDBParser::RuleGraphNameList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(286);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(281);
      graphNameItem();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(282);
      graphNameItem();
      setState(283);
      match(GraphDBParser::T__3);
      setState(284);
      graphNameList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RemoveGsetStatContext ------------------------------------------------------------------

GraphDBParser::RemoveGsetStatContext::RemoveGsetStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::RemoveGsetStatContext::K_remove() {
  return getToken(GraphDBParser::K_remove, 0);
}

tree::TerminalNode* GraphDBParser::RemoveGsetStatContext::K_from() {
  return getToken(GraphDBParser::K_from, 0);
}

tree::TerminalNode* GraphDBParser::RemoveGsetStatContext::K_graphset() {
  return getToken(GraphDBParser::K_graphset, 0);
}

GraphDBParser::GsidContext* GraphDBParser::RemoveGsetStatContext::gsid() {
  return getRuleContext<GraphDBParser::GsidContext>(0);
}

GraphDBParser::GidListContext* GraphDBParser::RemoveGsetStatContext::gidList() {
  return getRuleContext<GraphDBParser::GidListContext>(0);
}


size_t GraphDBParser::RemoveGsetStatContext::getRuleIndex() const {
  return GraphDBParser::RuleRemoveGsetStat;
}

void GraphDBParser::RemoveGsetStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRemoveGsetStat(this);
}

void GraphDBParser::RemoveGsetStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRemoveGsetStat(this);
}


antlrcpp::Any GraphDBParser::RemoveGsetStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitRemoveGsetStat(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::RemoveGsetStatContext* GraphDBParser::removeGsetStat() {
  RemoveGsetStatContext *_localctx = _tracker.createInstance<RemoveGsetStatContext>(_ctx, getState());
  enterRule(_localctx, 16, GraphDBParser::RuleRemoveGsetStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(288);
    match(GraphDBParser::K_remove);
    setState(289);
    match(GraphDBParser::K_from);
    setState(290);
    match(GraphDBParser::K_graphset);
    setState(291);
    gsid();
    setState(292);
    match(GraphDBParser::T__1);
    setState(293);
    gidList();
    setState(294);
    match(GraphDBParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RemoveGStatContext ------------------------------------------------------------------

GraphDBParser::RemoveGStatContext::RemoveGStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::RemoveGStatContext::K_remove() {
  return getToken(GraphDBParser::K_remove, 0);
}

GraphDBParser::VertexInfoContext* GraphDBParser::RemoveGStatContext::vertexInfo() {
  return getRuleContext<GraphDBParser::VertexInfoContext>(0);
}

GraphDBParser::EdgeInfoContext* GraphDBParser::RemoveGStatContext::edgeInfo() {
  return getRuleContext<GraphDBParser::EdgeInfoContext>(0);
}

tree::TerminalNode* GraphDBParser::RemoveGStatContext::K_from() {
  return getToken(GraphDBParser::K_from, 0);
}

tree::TerminalNode* GraphDBParser::RemoveGStatContext::K_graph() {
  return getToken(GraphDBParser::K_graph, 0);
}

std::vector<GraphDBParser::GidContext *> GraphDBParser::RemoveGStatContext::gid() {
  return getRuleContexts<GraphDBParser::GidContext>();
}

GraphDBParser::GidContext* GraphDBParser::RemoveGStatContext::gid(size_t i) {
  return getRuleContext<GraphDBParser::GidContext>(i);
}

tree::TerminalNode* GraphDBParser::RemoveGStatContext::K_file() {
  return getToken(GraphDBParser::K_file, 0);
}

GraphDBParser::FilenamelistContext* GraphDBParser::RemoveGStatContext::filenamelist() {
  return getRuleContext<GraphDBParser::FilenamelistContext>(0);
}


size_t GraphDBParser::RemoveGStatContext::getRuleIndex() const {
  return GraphDBParser::RuleRemoveGStat;
}

void GraphDBParser::RemoveGStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRemoveGStat(this);
}

void GraphDBParser::RemoveGStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRemoveGStat(this);
}


antlrcpp::Any GraphDBParser::RemoveGStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitRemoveGStat(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::RemoveGStatContext* GraphDBParser::removeGStat() {
  RemoveGStatContext *_localctx = _tracker.createInstance<RemoveGStatContext>(_ctx, getState());
  enterRule(_localctx, 18, GraphDBParser::RuleRemoveGStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(319);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(296);
      match(GraphDBParser::K_remove);
      setState(297);
      match(GraphDBParser::T__1);
      setState(298);
      vertexInfo();
      setState(299);
      match(GraphDBParser::T__3);
      setState(300);
      edgeInfo();
      setState(301);
      match(GraphDBParser::T__2);
      setState(302);
      match(GraphDBParser::K_from);
      setState(303);
      match(GraphDBParser::K_graph);
      setState(304);
      gid();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(306);
      match(GraphDBParser::K_remove);
      setState(307);
      match(GraphDBParser::K_file);
      setState(308);
      filenamelist();
      setState(309);
      match(GraphDBParser::K_from);
      setState(310);
      match(GraphDBParser::K_graph);
      setState(311);
      gid();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(313);
      match(GraphDBParser::K_remove);
      setState(314);
      gid();
      setState(315);
      match(GraphDBParser::K_from);
      setState(316);
      match(GraphDBParser::K_graph);
      setState(317);
      gid();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UpdateStatContext ------------------------------------------------------------------

GraphDBParser::UpdateStatContext::UpdateStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::UpdateStatContext::K_update() {
  return getToken(GraphDBParser::K_update, 0);
}

GraphDBParser::GsidContext* GraphDBParser::UpdateStatContext::gsid() {
  return getRuleContext<GraphDBParser::GsidContext>(0);
}

tree::TerminalNode* GraphDBParser::UpdateStatContext::K_at() {
  return getToken(GraphDBParser::K_at, 0);
}

GraphDBParser::GidContext* GraphDBParser::UpdateStatContext::gid() {
  return getRuleContext<GraphDBParser::GidContext>(0);
}

tree::TerminalNode* GraphDBParser::UpdateStatContext::K_by() {
  return getToken(GraphDBParser::K_by, 0);
}

tree::TerminalNode* GraphDBParser::UpdateStatContext::K_set() {
  return getToken(GraphDBParser::K_set, 0);
}

GraphDBParser::AttributeNameContext* GraphDBParser::UpdateStatContext::attributeName() {
  return getRuleContext<GraphDBParser::AttributeNameContext>(0);
}

GraphDBParser::ValueContext* GraphDBParser::UpdateStatContext::value() {
  return getRuleContext<GraphDBParser::ValueContext>(0);
}


size_t GraphDBParser::UpdateStatContext::getRuleIndex() const {
  return GraphDBParser::RuleUpdateStat;
}

void GraphDBParser::UpdateStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUpdateStat(this);
}

void GraphDBParser::UpdateStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUpdateStat(this);
}


antlrcpp::Any GraphDBParser::UpdateStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitUpdateStat(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::UpdateStatContext* GraphDBParser::updateStat() {
  UpdateStatContext *_localctx = _tracker.createInstance<UpdateStatContext>(_ctx, getState());
  enterRule(_localctx, 20, GraphDBParser::RuleUpdateStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(321);
    match(GraphDBParser::K_update);
    setState(322);
    gsid();
    setState(323);
    match(GraphDBParser::K_at);
    setState(324);
    gid();
    setState(325);
    match(GraphDBParser::K_by);
    setState(326);
    match(GraphDBParser::K_set);
    setState(327);
    attributeName();
    setState(328);
    match(GraphDBParser::T__4);
    setState(329);
    value();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NameGraphContext ------------------------------------------------------------------

GraphDBParser::NameGraphContext::NameGraphContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::NameGraphContext::K_as() {
  return getToken(GraphDBParser::K_as, 0);
}

GraphDBParser::GsidContext* GraphDBParser::NameGraphContext::gsid() {
  return getRuleContext<GraphDBParser::GsidContext>(0);
}


size_t GraphDBParser::NameGraphContext::getRuleIndex() const {
  return GraphDBParser::RuleNameGraph;
}

void GraphDBParser::NameGraphContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNameGraph(this);
}

void GraphDBParser::NameGraphContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNameGraph(this);
}


antlrcpp::Any GraphDBParser::NameGraphContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitNameGraph(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::NameGraphContext* GraphDBParser::nameGraph() {
  NameGraphContext *_localctx = _tracker.createInstance<NameGraphContext>(_ctx, getState());
  enterRule(_localctx, 22, GraphDBParser::RuleNameGraph);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(334);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GraphDBParser::K_as: {
        enterOuterAlt(_localctx, 1);
        setState(331);
        match(GraphDBParser::K_as);
        setState(332);
        gsid();
        break;
      }

      case GraphDBParser::T__2:
      case GraphDBParser::T__3:
      case GraphDBParser::T__5:
      case GraphDBParser::T__8:
      case GraphDBParser::T__12:
      case GraphDBParser::K_where:
      case GraphDBParser::K_align:
      case GraphDBParser::K_reduce:
      case GraphDBParser::K_join:
      case GraphDBParser::K_maximal: {
        enterOuterAlt(_localctx, 2);

        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GraphContext ------------------------------------------------------------------

GraphDBParser::GraphContext::GraphContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::VertexInfoContext* GraphDBParser::GraphContext::vertexInfo() {
  return getRuleContext<GraphDBParser::VertexInfoContext>(0);
}

GraphDBParser::EdgeInfoContext* GraphDBParser::GraphContext::edgeInfo() {
  return getRuleContext<GraphDBParser::EdgeInfoContext>(0);
}

GraphDBParser::AttributeInfoContext* GraphDBParser::GraphContext::attributeInfo() {
  return getRuleContext<GraphDBParser::AttributeInfoContext>(0);
}


size_t GraphDBParser::GraphContext::getRuleIndex() const {
  return GraphDBParser::RuleGraph;
}

void GraphDBParser::GraphContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGraph(this);
}

void GraphDBParser::GraphContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGraph(this);
}


antlrcpp::Any GraphDBParser::GraphContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitGraph(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::GraphContext* GraphDBParser::graph() {
  GraphContext *_localctx = _tracker.createInstance<GraphContext>(_ctx, getState());
  enterRule(_localctx, 24, GraphDBParser::RuleGraph);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(350);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(336);
      match(GraphDBParser::T__1);
      setState(337);
      vertexInfo();
      setState(338);
      match(GraphDBParser::T__3);
      setState(339);
      edgeInfo();
      setState(340);
      match(GraphDBParser::T__3);
      setState(341);
      attributeInfo();
      setState(342);
      match(GraphDBParser::T__2);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(344);
      match(GraphDBParser::T__1);
      setState(345);
      vertexInfo();
      setState(346);
      match(GraphDBParser::T__3);
      setState(347);
      edgeInfo();
      setState(348);
      match(GraphDBParser::T__2);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GraphItemContext ------------------------------------------------------------------

GraphDBParser::GraphItemContext::GraphItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::GraphContext* GraphDBParser::GraphItemContext::graph() {
  return getRuleContext<GraphDBParser::GraphContext>(0);
}

GraphDBParser::GidContext* GraphDBParser::GraphItemContext::gid() {
  return getRuleContext<GraphDBParser::GidContext>(0);
}


size_t GraphDBParser::GraphItemContext::getRuleIndex() const {
  return GraphDBParser::RuleGraphItem;
}

void GraphDBParser::GraphItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGraphItem(this);
}

void GraphDBParser::GraphItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGraphItem(this);
}


antlrcpp::Any GraphDBParser::GraphItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitGraphItem(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::GraphItemContext* GraphDBParser::graphItem() {
  GraphItemContext *_localctx = _tracker.createInstance<GraphItemContext>(_ctx, getState());
  enterRule(_localctx, 26, GraphDBParser::RuleGraphItem);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(354);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GraphDBParser::T__1: {
        enterOuterAlt(_localctx, 1);
        setState(352);
        graph();
        break;
      }

      case GraphDBParser::NAME_STRING: {
        enterOuterAlt(_localctx, 2);
        setState(353);
        gid();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GraphListContext ------------------------------------------------------------------

GraphDBParser::GraphListContext::GraphListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::GraphItemContext* GraphDBParser::GraphListContext::graphItem() {
  return getRuleContext<GraphDBParser::GraphItemContext>(0);
}

GraphDBParser::GraphListContext* GraphDBParser::GraphListContext::graphList() {
  return getRuleContext<GraphDBParser::GraphListContext>(0);
}


size_t GraphDBParser::GraphListContext::getRuleIndex() const {
  return GraphDBParser::RuleGraphList;
}

void GraphDBParser::GraphListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGraphList(this);
}

void GraphDBParser::GraphListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGraphList(this);
}


antlrcpp::Any GraphDBParser::GraphListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitGraphList(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::GraphListContext* GraphDBParser::graphList() {
  GraphListContext *_localctx = _tracker.createInstance<GraphListContext>(_ctx, getState());
  enterRule(_localctx, 28, GraphDBParser::RuleGraphList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(361);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(356);
      graphItem();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(357);
      graphItem();
      setState(358);
      match(GraphDBParser::T__3);
      setState(359);
      graphList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GraphsetContext ------------------------------------------------------------------

GraphDBParser::GraphsetContext::GraphsetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::GraphListContext* GraphDBParser::GraphsetContext::graphList() {
  return getRuleContext<GraphDBParser::GraphListContext>(0);
}


size_t GraphDBParser::GraphsetContext::getRuleIndex() const {
  return GraphDBParser::RuleGraphset;
}

void GraphDBParser::GraphsetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGraphset(this);
}

void GraphDBParser::GraphsetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGraphset(this);
}


antlrcpp::Any GraphDBParser::GraphsetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitGraphset(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::GraphsetContext* GraphDBParser::graphset() {
  GraphsetContext *_localctx = _tracker.createInstance<GraphsetContext>(_ctx, getState());
  enterRule(_localctx, 30, GraphDBParser::RuleGraphset);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(363);
    match(GraphDBParser::T__5);
    setState(364);
    graphList();
    setState(365);
    match(GraphDBParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VertexInfoContext ------------------------------------------------------------------

GraphDBParser::VertexInfoContext::VertexInfoContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::VidListContext* GraphDBParser::VertexInfoContext::vidList() {
  return getRuleContext<GraphDBParser::VidListContext>(0);
}


size_t GraphDBParser::VertexInfoContext::getRuleIndex() const {
  return GraphDBParser::RuleVertexInfo;
}

void GraphDBParser::VertexInfoContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVertexInfo(this);
}

void GraphDBParser::VertexInfoContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVertexInfo(this);
}


antlrcpp::Any GraphDBParser::VertexInfoContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitVertexInfo(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::VertexInfoContext* GraphDBParser::vertexInfo() {
  VertexInfoContext *_localctx = _tracker.createInstance<VertexInfoContext>(_ctx, getState());
  enterRule(_localctx, 32, GraphDBParser::RuleVertexInfo);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(373);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(367);
      match(GraphDBParser::T__5);
      setState(368);
      match(GraphDBParser::T__6);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(369);
      match(GraphDBParser::T__5);
      setState(370);
      vidList();
      setState(371);
      match(GraphDBParser::T__6);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EdgeInfoContext ------------------------------------------------------------------

GraphDBParser::EdgeInfoContext::EdgeInfoContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::EdgeListContext* GraphDBParser::EdgeInfoContext::edgeList() {
  return getRuleContext<GraphDBParser::EdgeListContext>(0);
}


size_t GraphDBParser::EdgeInfoContext::getRuleIndex() const {
  return GraphDBParser::RuleEdgeInfo;
}

void GraphDBParser::EdgeInfoContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEdgeInfo(this);
}

void GraphDBParser::EdgeInfoContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEdgeInfo(this);
}


antlrcpp::Any GraphDBParser::EdgeInfoContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitEdgeInfo(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::EdgeInfoContext* GraphDBParser::edgeInfo() {
  EdgeInfoContext *_localctx = _tracker.createInstance<EdgeInfoContext>(_ctx, getState());
  enterRule(_localctx, 34, GraphDBParser::RuleEdgeInfo);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(381);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(375);
      match(GraphDBParser::T__5);
      setState(376);
      match(GraphDBParser::T__6);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(377);
      match(GraphDBParser::T__5);
      setState(378);
      edgeList();
      setState(379);
      match(GraphDBParser::T__6);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EdgeListContext ------------------------------------------------------------------

GraphDBParser::EdgeListContext::EdgeListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::EdgeContext* GraphDBParser::EdgeListContext::edge() {
  return getRuleContext<GraphDBParser::EdgeContext>(0);
}

GraphDBParser::LidContext* GraphDBParser::EdgeListContext::lid() {
  return getRuleContext<GraphDBParser::LidContext>(0);
}

GraphDBParser::EidContext* GraphDBParser::EdgeListContext::eid() {
  return getRuleContext<GraphDBParser::EidContext>(0);
}

GraphDBParser::EdgeListContext* GraphDBParser::EdgeListContext::edgeList() {
  return getRuleContext<GraphDBParser::EdgeListContext>(0);
}


size_t GraphDBParser::EdgeListContext::getRuleIndex() const {
  return GraphDBParser::RuleEdgeList;
}

void GraphDBParser::EdgeListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEdgeList(this);
}

void GraphDBParser::EdgeListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEdgeList(this);
}


antlrcpp::Any GraphDBParser::EdgeListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitEdgeList(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::EdgeListContext* GraphDBParser::edgeList() {
  EdgeListContext *_localctx = _tracker.createInstance<EdgeListContext>(_ctx, getState());
  enterRule(_localctx, 36, GraphDBParser::RuleEdgeList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(411);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(383);
      edge();
      setState(384);
      match(GraphDBParser::T__7);
      setState(385);
      lid();
      setState(386);
      match(GraphDBParser::T__8);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(388);
      eid();
      setState(389);
      match(GraphDBParser::T__4);
      setState(390);
      edge();
      setState(391);
      match(GraphDBParser::T__7);
      setState(392);
      lid();
      setState(393);
      match(GraphDBParser::T__8);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(395);
      edge();
      setState(396);
      match(GraphDBParser::T__7);
      setState(397);
      lid();
      setState(398);
      match(GraphDBParser::T__8);
      setState(399);
      match(GraphDBParser::T__3);
      setState(400);
      edgeList();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(402);
      eid();
      setState(403);
      match(GraphDBParser::T__4);
      setState(404);
      edge();
      setState(405);
      match(GraphDBParser::T__7);
      setState(406);
      lid();
      setState(407);
      match(GraphDBParser::T__8);
      setState(408);
      match(GraphDBParser::T__3);
      setState(409);
      edgeList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EdgeContext ------------------------------------------------------------------

GraphDBParser::EdgeContext::EdgeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::VidTupleContext* GraphDBParser::EdgeContext::vidTuple() {
  return getRuleContext<GraphDBParser::VidTupleContext>(0);
}


size_t GraphDBParser::EdgeContext::getRuleIndex() const {
  return GraphDBParser::RuleEdge;
}

void GraphDBParser::EdgeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEdge(this);
}

void GraphDBParser::EdgeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEdge(this);
}


antlrcpp::Any GraphDBParser::EdgeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitEdge(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::EdgeContext* GraphDBParser::edge() {
  EdgeContext *_localctx = _tracker.createInstance<EdgeContext>(_ctx, getState());
  enterRule(_localctx, 38, GraphDBParser::RuleEdge);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(413);
    vidTuple();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttributeInfoContext ------------------------------------------------------------------

GraphDBParser::AttributeInfoContext::AttributeInfoContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::NodeAttributeInfoContext* GraphDBParser::AttributeInfoContext::nodeAttributeInfo() {
  return getRuleContext<GraphDBParser::NodeAttributeInfoContext>(0);
}

GraphDBParser::EdgeAttributeInfoContext* GraphDBParser::AttributeInfoContext::edgeAttributeInfo() {
  return getRuleContext<GraphDBParser::EdgeAttributeInfoContext>(0);
}


size_t GraphDBParser::AttributeInfoContext::getRuleIndex() const {
  return GraphDBParser::RuleAttributeInfo;
}

void GraphDBParser::AttributeInfoContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttributeInfo(this);
}

void GraphDBParser::AttributeInfoContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttributeInfo(this);
}


antlrcpp::Any GraphDBParser::AttributeInfoContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitAttributeInfo(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::AttributeInfoContext* GraphDBParser::attributeInfo() {
  AttributeInfoContext *_localctx = _tracker.createInstance<AttributeInfoContext>(_ctx, getState());
  enterRule(_localctx, 40, GraphDBParser::RuleAttributeInfo);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(425);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(415);
      match(GraphDBParser::T__1);
      setState(416);
      nodeAttributeInfo();
      setState(417);
      match(GraphDBParser::T__3);
      setState(418);
      edgeAttributeInfo();
      setState(419);
      match(GraphDBParser::T__2);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(421);
      match(GraphDBParser::T__1);
      setState(422);
      nodeAttributeInfo();
      setState(423);
      match(GraphDBParser::T__2);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NodeAttributeInfoContext ------------------------------------------------------------------

GraphDBParser::NodeAttributeInfoContext::NodeAttributeInfoContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::NodeAttributeListContext* GraphDBParser::NodeAttributeInfoContext::nodeAttributeList() {
  return getRuleContext<GraphDBParser::NodeAttributeListContext>(0);
}


size_t GraphDBParser::NodeAttributeInfoContext::getRuleIndex() const {
  return GraphDBParser::RuleNodeAttributeInfo;
}

void GraphDBParser::NodeAttributeInfoContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNodeAttributeInfo(this);
}

void GraphDBParser::NodeAttributeInfoContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNodeAttributeInfo(this);
}


antlrcpp::Any GraphDBParser::NodeAttributeInfoContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitNodeAttributeInfo(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::NodeAttributeInfoContext* GraphDBParser::nodeAttributeInfo() {
  NodeAttributeInfoContext *_localctx = _tracker.createInstance<NodeAttributeInfoContext>(_ctx, getState());
  enterRule(_localctx, 42, GraphDBParser::RuleNodeAttributeInfo);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(433);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(427);
      match(GraphDBParser::T__5);
      setState(428);
      match(GraphDBParser::T__6);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(429);
      match(GraphDBParser::T__5);
      setState(430);
      nodeAttributeList();
      setState(431);
      match(GraphDBParser::T__6);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NodeAttributeListContext ------------------------------------------------------------------

GraphDBParser::NodeAttributeListContext::NodeAttributeListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::NodeAttributeItemContext* GraphDBParser::NodeAttributeListContext::nodeAttributeItem() {
  return getRuleContext<GraphDBParser::NodeAttributeItemContext>(0);
}

GraphDBParser::NodeAttributeListContext* GraphDBParser::NodeAttributeListContext::nodeAttributeList() {
  return getRuleContext<GraphDBParser::NodeAttributeListContext>(0);
}


size_t GraphDBParser::NodeAttributeListContext::getRuleIndex() const {
  return GraphDBParser::RuleNodeAttributeList;
}

void GraphDBParser::NodeAttributeListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNodeAttributeList(this);
}

void GraphDBParser::NodeAttributeListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNodeAttributeList(this);
}


antlrcpp::Any GraphDBParser::NodeAttributeListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitNodeAttributeList(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::NodeAttributeListContext* GraphDBParser::nodeAttributeList() {
  NodeAttributeListContext *_localctx = _tracker.createInstance<NodeAttributeListContext>(_ctx, getState());
  enterRule(_localctx, 44, GraphDBParser::RuleNodeAttributeList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(440);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(435);
      nodeAttributeItem();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(436);
      nodeAttributeItem();
      setState(437);
      match(GraphDBParser::T__3);
      setState(438);
      nodeAttributeList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NodeAttributeItemContext ------------------------------------------------------------------

GraphDBParser::NodeAttributeItemContext::NodeAttributeItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::VidContext* GraphDBParser::NodeAttributeItemContext::vid() {
  return getRuleContext<GraphDBParser::VidContext>(0);
}

GraphDBParser::AttrEqItemListContext* GraphDBParser::NodeAttributeItemContext::attrEqItemList() {
  return getRuleContext<GraphDBParser::AttrEqItemListContext>(0);
}


size_t GraphDBParser::NodeAttributeItemContext::getRuleIndex() const {
  return GraphDBParser::RuleNodeAttributeItem;
}

void GraphDBParser::NodeAttributeItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNodeAttributeItem(this);
}

void GraphDBParser::NodeAttributeItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNodeAttributeItem(this);
}


antlrcpp::Any GraphDBParser::NodeAttributeItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitNodeAttributeItem(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::NodeAttributeItemContext* GraphDBParser::nodeAttributeItem() {
  NodeAttributeItemContext *_localctx = _tracker.createInstance<NodeAttributeItemContext>(_ctx, getState());
  enterRule(_localctx, 46, GraphDBParser::RuleNodeAttributeItem);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(451);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(442);
      vid();
      setState(443);
      match(GraphDBParser::T__9);
      setState(444);
      match(GraphDBParser::T__10);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(446);
      vid();
      setState(447);
      match(GraphDBParser::T__9);
      setState(448);
      attrEqItemList();
      setState(449);
      match(GraphDBParser::T__10);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EdgeAttributeInfoContext ------------------------------------------------------------------

GraphDBParser::EdgeAttributeInfoContext::EdgeAttributeInfoContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::EdgeAttributeListContext* GraphDBParser::EdgeAttributeInfoContext::edgeAttributeList() {
  return getRuleContext<GraphDBParser::EdgeAttributeListContext>(0);
}


size_t GraphDBParser::EdgeAttributeInfoContext::getRuleIndex() const {
  return GraphDBParser::RuleEdgeAttributeInfo;
}

void GraphDBParser::EdgeAttributeInfoContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEdgeAttributeInfo(this);
}

void GraphDBParser::EdgeAttributeInfoContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEdgeAttributeInfo(this);
}


antlrcpp::Any GraphDBParser::EdgeAttributeInfoContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitEdgeAttributeInfo(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::EdgeAttributeInfoContext* GraphDBParser::edgeAttributeInfo() {
  EdgeAttributeInfoContext *_localctx = _tracker.createInstance<EdgeAttributeInfoContext>(_ctx, getState());
  enterRule(_localctx, 48, GraphDBParser::RuleEdgeAttributeInfo);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(459);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(453);
      match(GraphDBParser::T__5);
      setState(454);
      match(GraphDBParser::T__6);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(455);
      match(GraphDBParser::T__5);
      setState(456);
      edgeAttributeList();
      setState(457);
      match(GraphDBParser::T__6);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EdgeAttributeListContext ------------------------------------------------------------------

GraphDBParser::EdgeAttributeListContext::EdgeAttributeListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::EdgeAttributeItemContext* GraphDBParser::EdgeAttributeListContext::edgeAttributeItem() {
  return getRuleContext<GraphDBParser::EdgeAttributeItemContext>(0);
}

GraphDBParser::EdgeAttributeListContext* GraphDBParser::EdgeAttributeListContext::edgeAttributeList() {
  return getRuleContext<GraphDBParser::EdgeAttributeListContext>(0);
}


size_t GraphDBParser::EdgeAttributeListContext::getRuleIndex() const {
  return GraphDBParser::RuleEdgeAttributeList;
}

void GraphDBParser::EdgeAttributeListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEdgeAttributeList(this);
}

void GraphDBParser::EdgeAttributeListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEdgeAttributeList(this);
}


antlrcpp::Any GraphDBParser::EdgeAttributeListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitEdgeAttributeList(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::EdgeAttributeListContext* GraphDBParser::edgeAttributeList() {
  EdgeAttributeListContext *_localctx = _tracker.createInstance<EdgeAttributeListContext>(_ctx, getState());
  enterRule(_localctx, 50, GraphDBParser::RuleEdgeAttributeList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(466);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(461);
      edgeAttributeItem();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(462);
      edgeAttributeItem();
      setState(463);
      match(GraphDBParser::T__3);
      setState(464);
      edgeAttributeList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EdgeAttributeItemContext ------------------------------------------------------------------

GraphDBParser::EdgeAttributeItemContext::EdgeAttributeItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::EidContext* GraphDBParser::EdgeAttributeItemContext::eid() {
  return getRuleContext<GraphDBParser::EidContext>(0);
}

GraphDBParser::EdgeContext* GraphDBParser::EdgeAttributeItemContext::edge() {
  return getRuleContext<GraphDBParser::EdgeContext>(0);
}

GraphDBParser::AttrEqItemListContext* GraphDBParser::EdgeAttributeItemContext::attrEqItemList() {
  return getRuleContext<GraphDBParser::AttrEqItemListContext>(0);
}


size_t GraphDBParser::EdgeAttributeItemContext::getRuleIndex() const {
  return GraphDBParser::RuleEdgeAttributeItem;
}

void GraphDBParser::EdgeAttributeItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEdgeAttributeItem(this);
}

void GraphDBParser::EdgeAttributeItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEdgeAttributeItem(this);
}


antlrcpp::Any GraphDBParser::EdgeAttributeItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitEdgeAttributeItem(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::EdgeAttributeItemContext* GraphDBParser::edgeAttributeItem() {
  EdgeAttributeItemContext *_localctx = _tracker.createInstance<EdgeAttributeItemContext>(_ctx, getState());
  enterRule(_localctx, 52, GraphDBParser::RuleEdgeAttributeItem);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(486);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(468);
      eid();
      setState(469);
      match(GraphDBParser::T__9);
      setState(470);
      match(GraphDBParser::T__10);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(472);
      edge();
      setState(473);
      match(GraphDBParser::T__9);
      setState(474);
      match(GraphDBParser::T__10);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(476);
      eid();
      setState(477);
      match(GraphDBParser::T__9);
      setState(478);
      attrEqItemList();
      setState(479);
      match(GraphDBParser::T__10);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(481);
      edge();
      setState(482);
      match(GraphDBParser::T__9);
      setState(483);
      attrEqItemList();
      setState(484);
      match(GraphDBParser::T__10);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QueryStatContext ------------------------------------------------------------------

GraphDBParser::QueryStatContext::QueryStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GraphDBParser::QueryStatContext *> GraphDBParser::QueryStatContext::queryStat() {
  return getRuleContexts<GraphDBParser::QueryStatContext>();
}

GraphDBParser::QueryStatContext* GraphDBParser::QueryStatContext::queryStat(size_t i) {
  return getRuleContext<GraphDBParser::QueryStatContext>(i);
}

tree::TerminalNode* GraphDBParser::QueryStatContext::K_select() {
  return getToken(GraphDBParser::K_select, 0);
}

GraphDBParser::NameGraphContext* GraphDBParser::QueryStatContext::nameGraph() {
  return getRuleContext<GraphDBParser::NameGraphContext>(0);
}

GraphDBParser::ReduceWordContext* GraphDBParser::QueryStatContext::reduceWord() {
  return getRuleContext<GraphDBParser::ReduceWordContext>(0);
}

GraphDBParser::MaximalWordContext* GraphDBParser::QueryStatContext::maximalWord() {
  return getRuleContext<GraphDBParser::MaximalWordContext>(0);
}

GraphDBParser::ProjectConditionContext* GraphDBParser::QueryStatContext::projectCondition() {
  return getRuleContext<GraphDBParser::ProjectConditionContext>(0);
}

GraphDBParser::FromConditionContext* GraphDBParser::QueryStatContext::fromCondition() {
  return getRuleContext<GraphDBParser::FromConditionContext>(0);
}

GraphDBParser::AlignConditionListContext* GraphDBParser::QueryStatContext::alignConditionList() {
  return getRuleContext<GraphDBParser::AlignConditionListContext>(0);
}

GraphDBParser::WhereConditionContext* GraphDBParser::QueryStatContext::whereCondition() {
  return getRuleContext<GraphDBParser::WhereConditionContext>(0);
}

GraphDBParser::MapConditionContext* GraphDBParser::QueryStatContext::mapCondition() {
  return getRuleContext<GraphDBParser::MapConditionContext>(0);
}

GraphDBParser::GsidContext* GraphDBParser::QueryStatContext::gsid() {
  return getRuleContext<GraphDBParser::GsidContext>(0);
}

GraphDBParser::MultipleOperatorContext* GraphDBParser::QueryStatContext::multipleOperator() {
  return getRuleContext<GraphDBParser::MultipleOperatorContext>(0);
}


size_t GraphDBParser::QueryStatContext::getRuleIndex() const {
  return GraphDBParser::RuleQueryStat;
}

void GraphDBParser::QueryStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterQueryStat(this);
}

void GraphDBParser::QueryStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitQueryStat(this);
}


antlrcpp::Any GraphDBParser::QueryStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitQueryStat(this);
  else
    return visitor->visitChildren(this);
}


GraphDBParser::QueryStatContext* GraphDBParser::queryStat() {
   return queryStat(0);
}

GraphDBParser::QueryStatContext* GraphDBParser::queryStat(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  GraphDBParser::QueryStatContext *_localctx = _tracker.createInstance<QueryStatContext>(_ctx, parentState);
  GraphDBParser::QueryStatContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 54;
  enterRecursionRule(_localctx, 54, GraphDBParser::RuleQueryStat, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(504);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GraphDBParser::T__1: {
        setState(489);
        match(GraphDBParser::T__1);
        setState(490);
        queryStat(0);
        setState(491);
        match(GraphDBParser::T__2);
        break;
      }

      case GraphDBParser::K_select: {
        setState(493);
        match(GraphDBParser::K_select);
        setState(494);
        nameGraph();
        setState(495);
        reduceWord();
        setState(496);
        maximalWord();
        setState(497);
        projectCondition();
        setState(498);
        fromCondition();
        setState(499);
        alignConditionList();
        setState(500);
        whereCondition();
        setState(501);
        mapCondition();
        break;
      }

      case GraphDBParser::NAME_STRING: {
        setState(503);
        gsid();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(512);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<QueryStatContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleQueryStat);
        setState(506);

        if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
        setState(507);
        multipleOperator();
        setState(508);
        queryStat(5); 
      }
      setState(514);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- MultipleOperatorContext ------------------------------------------------------------------

GraphDBParser::MultipleOperatorContext::MultipleOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::MultipleOperatorContext::K_intersect() {
  return getToken(GraphDBParser::K_intersect, 0);
}

tree::TerminalNode* GraphDBParser::MultipleOperatorContext::K_union() {
  return getToken(GraphDBParser::K_union, 0);
}


size_t GraphDBParser::MultipleOperatorContext::getRuleIndex() const {
  return GraphDBParser::RuleMultipleOperator;
}

void GraphDBParser::MultipleOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultipleOperator(this);
}

void GraphDBParser::MultipleOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultipleOperator(this);
}


antlrcpp::Any GraphDBParser::MultipleOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitMultipleOperator(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::MultipleOperatorContext* GraphDBParser::multipleOperator() {
  MultipleOperatorContext *_localctx = _tracker.createInstance<MultipleOperatorContext>(_ctx, getState());
  enterRule(_localctx, 56, GraphDBParser::RuleMultipleOperator);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(515);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << GraphDBParser::T__11)
      | (1ULL << GraphDBParser::K_union)
      | (1ULL << GraphDBParser::K_intersect))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProjectConditionContext ------------------------------------------------------------------

GraphDBParser::ProjectConditionContext::ProjectConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::SchemaNameListContext* GraphDBParser::ProjectConditionContext::schemaNameList() {
  return getRuleContext<GraphDBParser::SchemaNameListContext>(0);
}

tree::TerminalNode* GraphDBParser::ProjectConditionContext::K_for() {
  return getToken(GraphDBParser::K_for, 0);
}

GraphDBParser::LidListContext* GraphDBParser::ProjectConditionContext::lidList() {
  return getRuleContext<GraphDBParser::LidListContext>(0);
}


size_t GraphDBParser::ProjectConditionContext::getRuleIndex() const {
  return GraphDBParser::RuleProjectCondition;
}

void GraphDBParser::ProjectConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProjectCondition(this);
}

void GraphDBParser::ProjectConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProjectCondition(this);
}


antlrcpp::Any GraphDBParser::ProjectConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitProjectCondition(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::ProjectConditionContext* GraphDBParser::projectCondition() {
  ProjectConditionContext *_localctx = _tracker.createInstance<ProjectConditionContext>(_ctx, getState());
  enterRule(_localctx, 58, GraphDBParser::RuleProjectCondition);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(522);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(517);
      schemaNameList();
      setState(518);
      match(GraphDBParser::K_for);
      setState(519);
      lidList();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(521);
      match(GraphDBParser::T__12);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FromConditionContext ------------------------------------------------------------------

GraphDBParser::FromConditionContext::FromConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::FromConditionContext::K_from() {
  return getToken(GraphDBParser::K_from, 0);
}

GraphDBParser::OperatorGSetContext* GraphDBParser::FromConditionContext::operatorGSet() {
  return getRuleContext<GraphDBParser::OperatorGSetContext>(0);
}

GraphDBParser::OperationStatementContext* GraphDBParser::FromConditionContext::operationStatement() {
  return getRuleContext<GraphDBParser::OperationStatementContext>(0);
}


size_t GraphDBParser::FromConditionContext::getRuleIndex() const {
  return GraphDBParser::RuleFromCondition;
}

void GraphDBParser::FromConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFromCondition(this);
}

void GraphDBParser::FromConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFromCondition(this);
}


antlrcpp::Any GraphDBParser::FromConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitFromCondition(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::FromConditionContext* GraphDBParser::fromCondition() {
  FromConditionContext *_localctx = _tracker.createInstance<FromConditionContext>(_ctx, getState());
  enterRule(_localctx, 60, GraphDBParser::RuleFromCondition);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(528);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(524);
      match(GraphDBParser::K_from);
      setState(525);
      operatorGSet();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(526);
      match(GraphDBParser::K_from);
      setState(527);
      operationStatement();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AlignConditionListContext ------------------------------------------------------------------

GraphDBParser::AlignConditionListContext::AlignConditionListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::AlignConditionContext* GraphDBParser::AlignConditionListContext::alignCondition() {
  return getRuleContext<GraphDBParser::AlignConditionContext>(0);
}

GraphDBParser::AlignConditionListContext* GraphDBParser::AlignConditionListContext::alignConditionList() {
  return getRuleContext<GraphDBParser::AlignConditionListContext>(0);
}


size_t GraphDBParser::AlignConditionListContext::getRuleIndex() const {
  return GraphDBParser::RuleAlignConditionList;
}

void GraphDBParser::AlignConditionListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAlignConditionList(this);
}

void GraphDBParser::AlignConditionListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAlignConditionList(this);
}


antlrcpp::Any GraphDBParser::AlignConditionListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitAlignConditionList(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::AlignConditionListContext* GraphDBParser::alignConditionList() {
  AlignConditionListContext *_localctx = _tracker.createInstance<AlignConditionListContext>(_ctx, getState());
  enterRule(_localctx, 62, GraphDBParser::RuleAlignConditionList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(534);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GraphDBParser::K_align: {
        enterOuterAlt(_localctx, 1);
        setState(530);
        alignCondition();
        setState(531);
        alignConditionList();
        break;
      }

      case GraphDBParser::K_where: {
        enterOuterAlt(_localctx, 2);

        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AlignConditionContext ------------------------------------------------------------------

GraphDBParser::AlignConditionContext::AlignConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::AlignConditionContext::K_align() {
  return getToken(GraphDBParser::K_align, 0);
}

std::vector<GraphDBParser::LidContext *> GraphDBParser::AlignConditionContext::lid() {
  return getRuleContexts<GraphDBParser::LidContext>();
}

GraphDBParser::LidContext* GraphDBParser::AlignConditionContext::lid(size_t i) {
  return getRuleContext<GraphDBParser::LidContext>(i);
}

tree::TerminalNode* GraphDBParser::AlignConditionContext::K_on() {
  return getToken(GraphDBParser::K_on, 0);
}

GraphDBParser::AttrEqItemListUncertainContext* GraphDBParser::AlignConditionContext::attrEqItemListUncertain() {
  return getRuleContext<GraphDBParser::AttrEqItemListUncertainContext>(0);
}


size_t GraphDBParser::AlignConditionContext::getRuleIndex() const {
  return GraphDBParser::RuleAlignCondition;
}

void GraphDBParser::AlignConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAlignCondition(this);
}

void GraphDBParser::AlignConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAlignCondition(this);
}


antlrcpp::Any GraphDBParser::AlignConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitAlignCondition(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::AlignConditionContext* GraphDBParser::alignCondition() {
  AlignConditionContext *_localctx = _tracker.createInstance<AlignConditionContext>(_ctx, getState());
  enterRule(_localctx, 64, GraphDBParser::RuleAlignCondition);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(536);
    match(GraphDBParser::K_align);
    setState(537);
    lid();
    setState(538);
    match(GraphDBParser::T__3);
    setState(539);
    lid();
    setState(540);
    match(GraphDBParser::T__3);
    setState(541);
    lid();
    setState(542);
    match(GraphDBParser::K_on);
    setState(543);
    attrEqItemListUncertain();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FilenamelistContext ------------------------------------------------------------------

GraphDBParser::FilenamelistContext::FilenamelistContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::FilenameContext* GraphDBParser::FilenamelistContext::filename() {
  return getRuleContext<GraphDBParser::FilenameContext>(0);
}

GraphDBParser::FilenamelistContext* GraphDBParser::FilenamelistContext::filenamelist() {
  return getRuleContext<GraphDBParser::FilenamelistContext>(0);
}


size_t GraphDBParser::FilenamelistContext::getRuleIndex() const {
  return GraphDBParser::RuleFilenamelist;
}

void GraphDBParser::FilenamelistContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFilenamelist(this);
}

void GraphDBParser::FilenamelistContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFilenamelist(this);
}


antlrcpp::Any GraphDBParser::FilenamelistContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitFilenamelist(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::FilenamelistContext* GraphDBParser::filenamelist() {
  FilenamelistContext *_localctx = _tracker.createInstance<FilenamelistContext>(_ctx, getState());
  enterRule(_localctx, 66, GraphDBParser::RuleFilenamelist);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(550);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(545);
      filename();
      setState(546);
      match(GraphDBParser::T__3);
      setState(547);
      filenamelist();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(549);
      filename();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhereConditionContext ------------------------------------------------------------------

GraphDBParser::WhereConditionContext::WhereConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::WhereConditionContext::K_where() {
  return getToken(GraphDBParser::K_where, 0);
}

GraphDBParser::FirstOrderStatContext* GraphDBParser::WhereConditionContext::firstOrderStat() {
  return getRuleContext<GraphDBParser::FirstOrderStatContext>(0);
}

tree::TerminalNode* GraphDBParser::WhereConditionContext::K_file() {
  return getToken(GraphDBParser::K_file, 0);
}

GraphDBParser::FilenamelistContext* GraphDBParser::WhereConditionContext::filenamelist() {
  return getRuleContext<GraphDBParser::FilenamelistContext>(0);
}


size_t GraphDBParser::WhereConditionContext::getRuleIndex() const {
  return GraphDBParser::RuleWhereCondition;
}

void GraphDBParser::WhereConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhereCondition(this);
}

void GraphDBParser::WhereConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhereCondition(this);
}


antlrcpp::Any GraphDBParser::WhereConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitWhereCondition(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::WhereConditionContext* GraphDBParser::whereCondition() {
  WhereConditionContext *_localctx = _tracker.createInstance<WhereConditionContext>(_ctx, getState());
  enterRule(_localctx, 68, GraphDBParser::RuleWhereCondition);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(557);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(552);
      match(GraphDBParser::K_where);
      setState(553);
      firstOrderStat(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(554);
      match(GraphDBParser::K_where);
      setState(555);
      match(GraphDBParser::K_file);
      setState(556);
      filenamelist();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MapConditionContext ------------------------------------------------------------------

GraphDBParser::MapConditionContext::MapConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::MapConditionContext::K_map() {
  return getToken(GraphDBParser::K_map, 0);
}

GraphDBParser::OperatorGSetContext* GraphDBParser::MapConditionContext::operatorGSet() {
  return getRuleContext<GraphDBParser::OperatorGSetContext>(0);
}

tree::TerminalNode* GraphDBParser::MapConditionContext::K_by() {
  return getToken(GraphDBParser::K_by, 0);
}

GraphDBParser::GsidContext* GraphDBParser::MapConditionContext::gsid() {
  return getRuleContext<GraphDBParser::GsidContext>(0);
}


size_t GraphDBParser::MapConditionContext::getRuleIndex() const {
  return GraphDBParser::RuleMapCondition;
}

void GraphDBParser::MapConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMapCondition(this);
}

void GraphDBParser::MapConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMapCondition(this);
}


antlrcpp::Any GraphDBParser::MapConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitMapCondition(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::MapConditionContext* GraphDBParser::mapCondition() {
  MapConditionContext *_localctx = _tracker.createInstance<MapConditionContext>(_ctx, getState());
  enterRule(_localctx, 70, GraphDBParser::RuleMapCondition);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(567);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(559);
      match(GraphDBParser::K_map);
      setState(560);
      match(GraphDBParser::T__7);
      setState(561);
      operatorGSet();
      setState(562);
      match(GraphDBParser::T__8);
      setState(563);
      match(GraphDBParser::K_by);
      setState(564);
      gsid();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);

      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReduceWordContext ------------------------------------------------------------------

GraphDBParser::ReduceWordContext::ReduceWordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::ReduceWordContext::K_reduce() {
  return getToken(GraphDBParser::K_reduce, 0);
}


size_t GraphDBParser::ReduceWordContext::getRuleIndex() const {
  return GraphDBParser::RuleReduceWord;
}

void GraphDBParser::ReduceWordContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReduceWord(this);
}

void GraphDBParser::ReduceWordContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReduceWord(this);
}


antlrcpp::Any GraphDBParser::ReduceWordContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitReduceWord(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::ReduceWordContext* GraphDBParser::reduceWord() {
  ReduceWordContext *_localctx = _tracker.createInstance<ReduceWordContext>(_ctx, getState());
  enterRule(_localctx, 72, GraphDBParser::RuleReduceWord);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(571);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GraphDBParser::K_reduce: {
        enterOuterAlt(_localctx, 1);
        setState(569);
        match(GraphDBParser::K_reduce);
        break;
      }

      case GraphDBParser::T__5:
      case GraphDBParser::T__12:
      case GraphDBParser::K_maximal: {
        enterOuterAlt(_localctx, 2);

        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MaximalWordContext ------------------------------------------------------------------

GraphDBParser::MaximalWordContext::MaximalWordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::MaximalWordContext::K_maximal() {
  return getToken(GraphDBParser::K_maximal, 0);
}


size_t GraphDBParser::MaximalWordContext::getRuleIndex() const {
  return GraphDBParser::RuleMaximalWord;
}

void GraphDBParser::MaximalWordContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMaximalWord(this);
}

void GraphDBParser::MaximalWordContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMaximalWord(this);
}


antlrcpp::Any GraphDBParser::MaximalWordContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitMaximalWord(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::MaximalWordContext* GraphDBParser::maximalWord() {
  MaximalWordContext *_localctx = _tracker.createInstance<MaximalWordContext>(_ctx, getState());
  enterRule(_localctx, 74, GraphDBParser::RuleMaximalWord);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(575);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GraphDBParser::K_maximal: {
        enterOuterAlt(_localctx, 1);
        setState(573);
        match(GraphDBParser::K_maximal);
        break;
      }

      case GraphDBParser::T__5:
      case GraphDBParser::T__12: {
        enterOuterAlt(_localctx, 2);

        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OperationStatementContext ------------------------------------------------------------------

GraphDBParser::OperationStatementContext::OperationStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::ProductStatementContext* GraphDBParser::OperationStatementContext::productStatement() {
  return getRuleContext<GraphDBParser::ProductStatementContext>(0);
}

GraphDBParser::JoinStatementContext* GraphDBParser::OperationStatementContext::joinStatement() {
  return getRuleContext<GraphDBParser::JoinStatementContext>(0);
}


size_t GraphDBParser::OperationStatementContext::getRuleIndex() const {
  return GraphDBParser::RuleOperationStatement;
}

void GraphDBParser::OperationStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOperationStatement(this);
}

void GraphDBParser::OperationStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOperationStatement(this);
}


antlrcpp::Any GraphDBParser::OperationStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitOperationStatement(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::OperationStatementContext* GraphDBParser::operationStatement() {
  OperationStatementContext *_localctx = _tracker.createInstance<OperationStatementContext>(_ctx, getState());
  enterRule(_localctx, 76, GraphDBParser::RuleOperationStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(579);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(577);
      productStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(578);
      joinStatement();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OperatorGSetContext ------------------------------------------------------------------

GraphDBParser::OperatorGSetContext::OperatorGSetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::GsidContext* GraphDBParser::OperatorGSetContext::gsid() {
  return getRuleContext<GraphDBParser::GsidContext>(0);
}

GraphDBParser::GraphsetContext* GraphDBParser::OperatorGSetContext::graphset() {
  return getRuleContext<GraphDBParser::GraphsetContext>(0);
}

GraphDBParser::NameGraphContext* GraphDBParser::OperatorGSetContext::nameGraph() {
  return getRuleContext<GraphDBParser::NameGraphContext>(0);
}

GraphDBParser::QueryStatContext* GraphDBParser::OperatorGSetContext::queryStat() {
  return getRuleContext<GraphDBParser::QueryStatContext>(0);
}


size_t GraphDBParser::OperatorGSetContext::getRuleIndex() const {
  return GraphDBParser::RuleOperatorGSet;
}

void GraphDBParser::OperatorGSetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOperatorGSet(this);
}

void GraphDBParser::OperatorGSetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOperatorGSet(this);
}


antlrcpp::Any GraphDBParser::OperatorGSetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitOperatorGSet(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::OperatorGSetContext* GraphDBParser::operatorGSet() {
  OperatorGSetContext *_localctx = _tracker.createInstance<OperatorGSetContext>(_ctx, getState());
  enterRule(_localctx, 78, GraphDBParser::RuleOperatorGSet);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(591);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(581);
      gsid();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(582);
      graphset();
      setState(583);
      nameGraph();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(585);
      match(GraphDBParser::T__1);
      setState(586);
      graphset();
      setState(587);
      nameGraph();
      setState(588);
      match(GraphDBParser::T__2);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(590);
      queryStat(0);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SchemaNameItemContext ------------------------------------------------------------------

GraphDBParser::SchemaNameItemContext::SchemaNameItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::AttributeNameListContext* GraphDBParser::SchemaNameItemContext::attributeNameList() {
  return getRuleContext<GraphDBParser::AttributeNameListContext>(0);
}


size_t GraphDBParser::SchemaNameItemContext::getRuleIndex() const {
  return GraphDBParser::RuleSchemaNameItem;
}

void GraphDBParser::SchemaNameItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSchemaNameItem(this);
}

void GraphDBParser::SchemaNameItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSchemaNameItem(this);
}


antlrcpp::Any GraphDBParser::SchemaNameItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitSchemaNameItem(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::SchemaNameItemContext* GraphDBParser::schemaNameItem() {
  SchemaNameItemContext *_localctx = _tracker.createInstance<SchemaNameItemContext>(_ctx, getState());
  enterRule(_localctx, 80, GraphDBParser::RuleSchemaNameItem);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(600);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(593);
      match(GraphDBParser::T__5);
      setState(594);
      match(GraphDBParser::T__6);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(595);
      match(GraphDBParser::T__5);
      setState(596);
      attributeNameList();
      setState(597);
      match(GraphDBParser::T__6);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(599);
      match(GraphDBParser::T__12);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SchemaNameListContext ------------------------------------------------------------------

GraphDBParser::SchemaNameListContext::SchemaNameListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::SchemaNameItemContext* GraphDBParser::SchemaNameListContext::schemaNameItem() {
  return getRuleContext<GraphDBParser::SchemaNameItemContext>(0);
}

GraphDBParser::SchemaNameListContext* GraphDBParser::SchemaNameListContext::schemaNameList() {
  return getRuleContext<GraphDBParser::SchemaNameListContext>(0);
}


size_t GraphDBParser::SchemaNameListContext::getRuleIndex() const {
  return GraphDBParser::RuleSchemaNameList;
}

void GraphDBParser::SchemaNameListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSchemaNameList(this);
}

void GraphDBParser::SchemaNameListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSchemaNameList(this);
}


antlrcpp::Any GraphDBParser::SchemaNameListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitSchemaNameList(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::SchemaNameListContext* GraphDBParser::schemaNameList() {
  SchemaNameListContext *_localctx = _tracker.createInstance<SchemaNameListContext>(_ctx, getState());
  enterRule(_localctx, 82, GraphDBParser::RuleSchemaNameList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(607);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(602);
      schemaNameItem();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(603);
      schemaNameItem();
      setState(604);
      match(GraphDBParser::T__3);
      setState(605);
      schemaNameList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProductStatementContext ------------------------------------------------------------------

GraphDBParser::ProductStatementContext::ProductStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GraphDBParser::OperatorGSetContext *> GraphDBParser::ProductStatementContext::operatorGSet() {
  return getRuleContexts<GraphDBParser::OperatorGSetContext>();
}

GraphDBParser::OperatorGSetContext* GraphDBParser::ProductStatementContext::operatorGSet(size_t i) {
  return getRuleContext<GraphDBParser::OperatorGSetContext>(i);
}


size_t GraphDBParser::ProductStatementContext::getRuleIndex() const {
  return GraphDBParser::RuleProductStatement;
}

void GraphDBParser::ProductStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProductStatement(this);
}

void GraphDBParser::ProductStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProductStatement(this);
}


antlrcpp::Any GraphDBParser::ProductStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitProductStatement(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::ProductStatementContext* GraphDBParser::productStatement() {
  ProductStatementContext *_localctx = _tracker.createInstance<ProductStatementContext>(_ctx, getState());
  enterRule(_localctx, 84, GraphDBParser::RuleProductStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(609);
    operatorGSet();
    setState(610);
    match(GraphDBParser::T__3);
    setState(611);
    operatorGSet();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- JoinStatementContext ------------------------------------------------------------------

GraphDBParser::JoinStatementContext::JoinStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GraphDBParser::OperatorGSetContext *> GraphDBParser::JoinStatementContext::operatorGSet() {
  return getRuleContexts<GraphDBParser::OperatorGSetContext>();
}

GraphDBParser::OperatorGSetContext* GraphDBParser::JoinStatementContext::operatorGSet(size_t i) {
  return getRuleContext<GraphDBParser::OperatorGSetContext>(i);
}

tree::TerminalNode* GraphDBParser::JoinStatementContext::K_join() {
  return getToken(GraphDBParser::K_join, 0);
}


size_t GraphDBParser::JoinStatementContext::getRuleIndex() const {
  return GraphDBParser::RuleJoinStatement;
}

void GraphDBParser::JoinStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterJoinStatement(this);
}

void GraphDBParser::JoinStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitJoinStatement(this);
}


antlrcpp::Any GraphDBParser::JoinStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitJoinStatement(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::JoinStatementContext* GraphDBParser::joinStatement() {
  JoinStatementContext *_localctx = _tracker.createInstance<JoinStatementContext>(_ctx, getState());
  enterRule(_localctx, 86, GraphDBParser::RuleJoinStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(613);
    operatorGSet();
    setState(614);
    match(GraphDBParser::K_join);
    setState(615);
    operatorGSet();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueContext ------------------------------------------------------------------

GraphDBParser::ValueContext::ValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::ValueContext::INTEGER_NUMBER() {
  return getToken(GraphDBParser::INTEGER_NUMBER, 0);
}

tree::TerminalNode* GraphDBParser::ValueContext::NOT_INTEGER_NUMBER() {
  return getToken(GraphDBParser::NOT_INTEGER_NUMBER, 0);
}

tree::TerminalNode* GraphDBParser::ValueContext::TEXT() {
  return getToken(GraphDBParser::TEXT, 0);
}


size_t GraphDBParser::ValueContext::getRuleIndex() const {
  return GraphDBParser::RuleValue;
}

void GraphDBParser::ValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValue(this);
}

void GraphDBParser::ValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValue(this);
}


antlrcpp::Any GraphDBParser::ValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitValue(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::ValueContext* GraphDBParser::value() {
  ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, getState());
  enterRule(_localctx, 88, GraphDBParser::RuleValue);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(617);
    _la = _input->LA(1);
    if (!(((((_la - 81) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 81)) & ((1ULL << (GraphDBParser::INTEGER_NUMBER - 81))
      | (1ULL << (GraphDBParser::NOT_INTEGER_NUMBER - 81))
      | (1ULL << (GraphDBParser::TEXT - 81)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EntIdContext ------------------------------------------------------------------

GraphDBParser::EntIdContext::EntIdContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::VidContext* GraphDBParser::EntIdContext::vid() {
  return getRuleContext<GraphDBParser::VidContext>(0);
}

GraphDBParser::EidContext* GraphDBParser::EntIdContext::eid() {
  return getRuleContext<GraphDBParser::EidContext>(0);
}


size_t GraphDBParser::EntIdContext::getRuleIndex() const {
  return GraphDBParser::RuleEntId;
}

void GraphDBParser::EntIdContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEntId(this);
}

void GraphDBParser::EntIdContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEntId(this);
}


antlrcpp::Any GraphDBParser::EntIdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitEntId(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::EntIdContext* GraphDBParser::entId() {
  EntIdContext *_localctx = _tracker.createInstance<EntIdContext>(_ctx, getState());
  enterRule(_localctx, 90, GraphDBParser::RuleEntId);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(621);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(619);
      vid();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(620);
      eid();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VidListContext ------------------------------------------------------------------

GraphDBParser::VidListContext::VidListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::VidContext* GraphDBParser::VidListContext::vid() {
  return getRuleContext<GraphDBParser::VidContext>(0);
}

GraphDBParser::LidContext* GraphDBParser::VidListContext::lid() {
  return getRuleContext<GraphDBParser::LidContext>(0);
}

GraphDBParser::VidListContext* GraphDBParser::VidListContext::vidList() {
  return getRuleContext<GraphDBParser::VidListContext>(0);
}


size_t GraphDBParser::VidListContext::getRuleIndex() const {
  return GraphDBParser::RuleVidList;
}

void GraphDBParser::VidListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVidList(this);
}

void GraphDBParser::VidListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVidList(this);
}


antlrcpp::Any GraphDBParser::VidListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitVidList(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::VidListContext* GraphDBParser::vidList() {
  VidListContext *_localctx = _tracker.createInstance<VidListContext>(_ctx, getState());
  enterRule(_localctx, 92, GraphDBParser::RuleVidList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(635);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(623);
      vid();
      setState(624);
      match(GraphDBParser::T__7);
      setState(625);
      lid();
      setState(626);
      match(GraphDBParser::T__8);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(628);
      vid();
      setState(629);
      match(GraphDBParser::T__7);
      setState(630);
      lid();
      setState(631);
      match(GraphDBParser::T__8);
      setState(632);
      match(GraphDBParser::T__3);
      setState(633);
      vidList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GidListContext ------------------------------------------------------------------

GraphDBParser::GidListContext::GidListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::GidContext* GraphDBParser::GidListContext::gid() {
  return getRuleContext<GraphDBParser::GidContext>(0);
}

GraphDBParser::GidListContext* GraphDBParser::GidListContext::gidList() {
  return getRuleContext<GraphDBParser::GidListContext>(0);
}


size_t GraphDBParser::GidListContext::getRuleIndex() const {
  return GraphDBParser::RuleGidList;
}

void GraphDBParser::GidListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGidList(this);
}

void GraphDBParser::GidListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGidList(this);
}


antlrcpp::Any GraphDBParser::GidListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitGidList(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::GidListContext* GraphDBParser::gidList() {
  GidListContext *_localctx = _tracker.createInstance<GidListContext>(_ctx, getState());
  enterRule(_localctx, 94, GraphDBParser::RuleGidList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(642);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(637);
      gid();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(638);
      gid();
      setState(639);
      match(GraphDBParser::T__3);
      setState(640);
      gidList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LidListContext ------------------------------------------------------------------

GraphDBParser::LidListContext::LidListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::LidContext* GraphDBParser::LidListContext::lid() {
  return getRuleContext<GraphDBParser::LidContext>(0);
}

GraphDBParser::LidListContext* GraphDBParser::LidListContext::lidList() {
  return getRuleContext<GraphDBParser::LidListContext>(0);
}


size_t GraphDBParser::LidListContext::getRuleIndex() const {
  return GraphDBParser::RuleLidList;
}

void GraphDBParser::LidListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLidList(this);
}

void GraphDBParser::LidListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLidList(this);
}


antlrcpp::Any GraphDBParser::LidListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitLidList(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::LidListContext* GraphDBParser::lidList() {
  LidListContext *_localctx = _tracker.createInstance<LidListContext>(_ctx, getState());
  enterRule(_localctx, 96, GraphDBParser::RuleLidList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(649);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(644);
      lid();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(645);
      lid();
      setState(646);
      match(GraphDBParser::T__3);
      setState(647);
      lidList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VidTupleContext ------------------------------------------------------------------

GraphDBParser::VidTupleContext::VidTupleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GraphDBParser::VidContext *> GraphDBParser::VidTupleContext::vid() {
  return getRuleContexts<GraphDBParser::VidContext>();
}

GraphDBParser::VidContext* GraphDBParser::VidTupleContext::vid(size_t i) {
  return getRuleContext<GraphDBParser::VidContext>(i);
}


size_t GraphDBParser::VidTupleContext::getRuleIndex() const {
  return GraphDBParser::RuleVidTuple;
}

void GraphDBParser::VidTupleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVidTuple(this);
}

void GraphDBParser::VidTupleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVidTuple(this);
}


antlrcpp::Any GraphDBParser::VidTupleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitVidTuple(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::VidTupleContext* GraphDBParser::vidTuple() {
  VidTupleContext *_localctx = _tracker.createInstance<VidTupleContext>(_ctx, getState());
  enterRule(_localctx, 98, GraphDBParser::RuleVidTuple);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(651);
    match(GraphDBParser::T__1);
    setState(652);
    vid();
    setState(653);
    match(GraphDBParser::T__3);
    setState(654);
    vid();
    setState(655);
    match(GraphDBParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VidTupleListContext ------------------------------------------------------------------

GraphDBParser::VidTupleListContext::VidTupleListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::VidTupleContext* GraphDBParser::VidTupleListContext::vidTuple() {
  return getRuleContext<GraphDBParser::VidTupleContext>(0);
}

GraphDBParser::VidTupleListContext* GraphDBParser::VidTupleListContext::vidTupleList() {
  return getRuleContext<GraphDBParser::VidTupleListContext>(0);
}


size_t GraphDBParser::VidTupleListContext::getRuleIndex() const {
  return GraphDBParser::RuleVidTupleList;
}

void GraphDBParser::VidTupleListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVidTupleList(this);
}

void GraphDBParser::VidTupleListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVidTupleList(this);
}


antlrcpp::Any GraphDBParser::VidTupleListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitVidTupleList(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::VidTupleListContext* GraphDBParser::vidTupleList() {
  VidTupleListContext *_localctx = _tracker.createInstance<VidTupleListContext>(_ctx, getState());
  enterRule(_localctx, 100, GraphDBParser::RuleVidTupleList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(662);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(657);
      vidTuple();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(658);
      vidTuple();
      setState(659);
      match(GraphDBParser::T__3);
      setState(660);
      vidTupleList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttrEqItemContext ------------------------------------------------------------------

GraphDBParser::AttrEqItemContext::AttrEqItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::AttributeNameContext* GraphDBParser::AttrEqItemContext::attributeName() {
  return getRuleContext<GraphDBParser::AttributeNameContext>(0);
}

GraphDBParser::ValueContext* GraphDBParser::AttrEqItemContext::value() {
  return getRuleContext<GraphDBParser::ValueContext>(0);
}


size_t GraphDBParser::AttrEqItemContext::getRuleIndex() const {
  return GraphDBParser::RuleAttrEqItem;
}

void GraphDBParser::AttrEqItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttrEqItem(this);
}

void GraphDBParser::AttrEqItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttrEqItem(this);
}


antlrcpp::Any GraphDBParser::AttrEqItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitAttrEqItem(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::AttrEqItemContext* GraphDBParser::attrEqItem() {
  AttrEqItemContext *_localctx = _tracker.createInstance<AttrEqItemContext>(_ctx, getState());
  enterRule(_localctx, 102, GraphDBParser::RuleAttrEqItem);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(664);
    attributeName();
    setState(665);
    match(GraphDBParser::T__4);
    setState(666);
    value();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttrEqItemListContext ------------------------------------------------------------------

GraphDBParser::AttrEqItemListContext::AttrEqItemListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::AttrEqItemContext* GraphDBParser::AttrEqItemListContext::attrEqItem() {
  return getRuleContext<GraphDBParser::AttrEqItemContext>(0);
}

GraphDBParser::AttrEqItemListContext* GraphDBParser::AttrEqItemListContext::attrEqItemList() {
  return getRuleContext<GraphDBParser::AttrEqItemListContext>(0);
}


size_t GraphDBParser::AttrEqItemListContext::getRuleIndex() const {
  return GraphDBParser::RuleAttrEqItemList;
}

void GraphDBParser::AttrEqItemListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttrEqItemList(this);
}

void GraphDBParser::AttrEqItemListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttrEqItemList(this);
}


antlrcpp::Any GraphDBParser::AttrEqItemListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitAttrEqItemList(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::AttrEqItemListContext* GraphDBParser::attrEqItemList() {
  AttrEqItemListContext *_localctx = _tracker.createInstance<AttrEqItemListContext>(_ctx, getState());
  enterRule(_localctx, 104, GraphDBParser::RuleAttrEqItemList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(673);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(668);
      attrEqItem();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(669);
      attrEqItem();
      setState(670);
      match(GraphDBParser::T__3);
      setState(671);
      attrEqItemList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttributeNameListContext ------------------------------------------------------------------

GraphDBParser::AttributeNameListContext::AttributeNameListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::AttributeNameContext* GraphDBParser::AttributeNameListContext::attributeName() {
  return getRuleContext<GraphDBParser::AttributeNameContext>(0);
}

GraphDBParser::AttributeNameListContext* GraphDBParser::AttributeNameListContext::attributeNameList() {
  return getRuleContext<GraphDBParser::AttributeNameListContext>(0);
}


size_t GraphDBParser::AttributeNameListContext::getRuleIndex() const {
  return GraphDBParser::RuleAttributeNameList;
}

void GraphDBParser::AttributeNameListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttributeNameList(this);
}

void GraphDBParser::AttributeNameListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttributeNameList(this);
}


antlrcpp::Any GraphDBParser::AttributeNameListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitAttributeNameList(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::AttributeNameListContext* GraphDBParser::attributeNameList() {
  AttributeNameListContext *_localctx = _tracker.createInstance<AttributeNameListContext>(_ctx, getState());
  enterRule(_localctx, 106, GraphDBParser::RuleAttributeNameList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(680);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(675);
      attributeName();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(676);
      attributeName();
      setState(677);
      match(GraphDBParser::T__3);
      setState(678);
      attributeNameList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttrEqItemUncertainContext ------------------------------------------------------------------

GraphDBParser::AttrEqItemUncertainContext::AttrEqItemUncertainContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GraphDBParser::AttributeNameContext *> GraphDBParser::AttrEqItemUncertainContext::attributeName() {
  return getRuleContexts<GraphDBParser::AttributeNameContext>();
}

GraphDBParser::AttributeNameContext* GraphDBParser::AttrEqItemUncertainContext::attributeName(size_t i) {
  return getRuleContext<GraphDBParser::AttributeNameContext>(i);
}


size_t GraphDBParser::AttrEqItemUncertainContext::getRuleIndex() const {
  return GraphDBParser::RuleAttrEqItemUncertain;
}

void GraphDBParser::AttrEqItemUncertainContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttrEqItemUncertain(this);
}

void GraphDBParser::AttrEqItemUncertainContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttrEqItemUncertain(this);
}


antlrcpp::Any GraphDBParser::AttrEqItemUncertainContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitAttrEqItemUncertain(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::AttrEqItemUncertainContext* GraphDBParser::attrEqItemUncertain() {
  AttrEqItemUncertainContext *_localctx = _tracker.createInstance<AttrEqItemUncertainContext>(_ctx, getState());
  enterRule(_localctx, 108, GraphDBParser::RuleAttrEqItemUncertain);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(682);
    attributeName();
    setState(683);
    match(GraphDBParser::T__4);
    setState(684);
    attributeName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttrEqItemListUncertainContext ------------------------------------------------------------------

GraphDBParser::AttrEqItemListUncertainContext::AttrEqItemListUncertainContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::AttrEqItemUncertainContext* GraphDBParser::AttrEqItemListUncertainContext::attrEqItemUncertain() {
  return getRuleContext<GraphDBParser::AttrEqItemUncertainContext>(0);
}

GraphDBParser::AttrEqItemListUncertainContext* GraphDBParser::AttrEqItemListUncertainContext::attrEqItemListUncertain() {
  return getRuleContext<GraphDBParser::AttrEqItemListUncertainContext>(0);
}


size_t GraphDBParser::AttrEqItemListUncertainContext::getRuleIndex() const {
  return GraphDBParser::RuleAttrEqItemListUncertain;
}

void GraphDBParser::AttrEqItemListUncertainContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttrEqItemListUncertain(this);
}

void GraphDBParser::AttrEqItemListUncertainContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttrEqItemListUncertain(this);
}


antlrcpp::Any GraphDBParser::AttrEqItemListUncertainContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitAttrEqItemListUncertain(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::AttrEqItemListUncertainContext* GraphDBParser::attrEqItemListUncertain() {
  AttrEqItemListUncertainContext *_localctx = _tracker.createInstance<AttrEqItemListUncertainContext>(_ctx, getState());
  enterRule(_localctx, 110, GraphDBParser::RuleAttrEqItemListUncertain);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(691);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(686);
      attrEqItemUncertain();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(687);
      attrEqItemUncertain();
      setState(688);
      match(GraphDBParser::T__3);
      setState(689);
      attrEqItemListUncertain();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CompareOperatorContext ------------------------------------------------------------------

GraphDBParser::CompareOperatorContext::CompareOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t GraphDBParser::CompareOperatorContext::getRuleIndex() const {
  return GraphDBParser::RuleCompareOperator;
}

void GraphDBParser::CompareOperatorContext::copyFrom(CompareOperatorContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- LTContext ------------------------------------------------------------------

GraphDBParser::LTContext::LTContext(CompareOperatorContext *ctx) { copyFrom(ctx); }

void GraphDBParser::LTContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLT(this);
}
void GraphDBParser::LTContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLT(this);
}

antlrcpp::Any GraphDBParser::LTContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitLT(this);
  else
    return visitor->visitChildren(this);
}
//----------------- GTEContext ------------------------------------------------------------------

GraphDBParser::GTEContext::GTEContext(CompareOperatorContext *ctx) { copyFrom(ctx); }

void GraphDBParser::GTEContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGTE(this);
}
void GraphDBParser::GTEContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGTE(this);
}

antlrcpp::Any GraphDBParser::GTEContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitGTE(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NEQContext ------------------------------------------------------------------

GraphDBParser::NEQContext::NEQContext(CompareOperatorContext *ctx) { copyFrom(ctx); }

void GraphDBParser::NEQContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNEQ(this);
}
void GraphDBParser::NEQContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNEQ(this);
}

antlrcpp::Any GraphDBParser::NEQContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitNEQ(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LTEContext ------------------------------------------------------------------

GraphDBParser::LTEContext::LTEContext(CompareOperatorContext *ctx) { copyFrom(ctx); }

void GraphDBParser::LTEContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLTE(this);
}
void GraphDBParser::LTEContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLTE(this);
}

antlrcpp::Any GraphDBParser::LTEContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitLTE(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EQContext ------------------------------------------------------------------

GraphDBParser::EQContext::EQContext(CompareOperatorContext *ctx) { copyFrom(ctx); }

void GraphDBParser::EQContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEQ(this);
}
void GraphDBParser::EQContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEQ(this);
}

antlrcpp::Any GraphDBParser::EQContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitEQ(this);
  else
    return visitor->visitChildren(this);
}
//----------------- GTContext ------------------------------------------------------------------

GraphDBParser::GTContext::GTContext(CompareOperatorContext *ctx) { copyFrom(ctx); }

void GraphDBParser::GTContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGT(this);
}
void GraphDBParser::GTContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGT(this);
}

antlrcpp::Any GraphDBParser::GTContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitGT(this);
  else
    return visitor->visitChildren(this);
}
GraphDBParser::CompareOperatorContext* GraphDBParser::compareOperator() {
  CompareOperatorContext *_localctx = _tracker.createInstance<CompareOperatorContext>(_ctx, getState());
  enterRule(_localctx, 112, GraphDBParser::RuleCompareOperator);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(699);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GraphDBParser::T__10: {
        _localctx = dynamic_cast<CompareOperatorContext *>(_tracker.createInstance<GraphDBParser::GTContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(693);
        match(GraphDBParser::T__10);
        break;
      }

      case GraphDBParser::T__9: {
        _localctx = dynamic_cast<CompareOperatorContext *>(_tracker.createInstance<GraphDBParser::LTContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(694);
        match(GraphDBParser::T__9);
        break;
      }

      case GraphDBParser::T__13: {
        _localctx = dynamic_cast<CompareOperatorContext *>(_tracker.createInstance<GraphDBParser::GTEContext>(_localctx));
        enterOuterAlt(_localctx, 3);
        setState(695);
        match(GraphDBParser::T__13);
        break;
      }

      case GraphDBParser::T__14: {
        _localctx = dynamic_cast<CompareOperatorContext *>(_tracker.createInstance<GraphDBParser::LTEContext>(_localctx));
        enterOuterAlt(_localctx, 4);
        setState(696);
        match(GraphDBParser::T__14);
        break;
      }

      case GraphDBParser::T__4: {
        _localctx = dynamic_cast<CompareOperatorContext *>(_tracker.createInstance<GraphDBParser::EQContext>(_localctx));
        enterOuterAlt(_localctx, 5);
        setState(697);
        match(GraphDBParser::T__4);
        break;
      }

      case GraphDBParser::T__15: {
        _localctx = dynamic_cast<CompareOperatorContext *>(_tracker.createInstance<GraphDBParser::NEQContext>(_localctx));
        enterOuterAlt(_localctx, 6);
        setState(698);
        match(GraphDBParser::T__15);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CalculateOperatorContext ------------------------------------------------------------------

GraphDBParser::CalculateOperatorContext::CalculateOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t GraphDBParser::CalculateOperatorContext::getRuleIndex() const {
  return GraphDBParser::RuleCalculateOperator;
}

void GraphDBParser::CalculateOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCalculateOperator(this);
}

void GraphDBParser::CalculateOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCalculateOperator(this);
}


antlrcpp::Any GraphDBParser::CalculateOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitCalculateOperator(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::CalculateOperatorContext* GraphDBParser::calculateOperator() {
  CalculateOperatorContext *_localctx = _tracker.createInstance<CalculateOperatorContext>(_ctx, getState());
  enterRule(_localctx, 114, GraphDBParser::RuleCalculateOperator);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(701);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << GraphDBParser::T__11)
      | (1ULL << GraphDBParser::T__12)
      | (1ULL << GraphDBParser::T__16)
      | (1ULL << GraphDBParser::T__17))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicFlagBiContext ------------------------------------------------------------------

GraphDBParser::LogicFlagBiContext::LogicFlagBiContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::LogicFlagBiContext::K_and() {
  return getToken(GraphDBParser::K_and, 0);
}

tree::TerminalNode* GraphDBParser::LogicFlagBiContext::K_or() {
  return getToken(GraphDBParser::K_or, 0);
}

tree::TerminalNode* GraphDBParser::LogicFlagBiContext::K_arrow() {
  return getToken(GraphDBParser::K_arrow, 0);
}


size_t GraphDBParser::LogicFlagBiContext::getRuleIndex() const {
  return GraphDBParser::RuleLogicFlagBi;
}

void GraphDBParser::LogicFlagBiContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicFlagBi(this);
}

void GraphDBParser::LogicFlagBiContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicFlagBi(this);
}


antlrcpp::Any GraphDBParser::LogicFlagBiContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitLogicFlagBi(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::LogicFlagBiContext* GraphDBParser::logicFlagBi() {
  LogicFlagBiContext *_localctx = _tracker.createInstance<LogicFlagBiContext>(_ctx, getState());
  enterRule(_localctx, 116, GraphDBParser::RuleLogicFlagBi);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(703);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << GraphDBParser::K_and)
      | (1ULL << GraphDBParser::K_or)
      | (1ULL << GraphDBParser::K_arrow))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicFlagNotContext ------------------------------------------------------------------

GraphDBParser::LogicFlagNotContext::LogicFlagNotContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::LogicFlagNotContext::K_not() {
  return getToken(GraphDBParser::K_not, 0);
}


size_t GraphDBParser::LogicFlagNotContext::getRuleIndex() const {
  return GraphDBParser::RuleLogicFlagNot;
}

void GraphDBParser::LogicFlagNotContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicFlagNot(this);
}

void GraphDBParser::LogicFlagNotContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicFlagNot(this);
}


antlrcpp::Any GraphDBParser::LogicFlagNotContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitLogicFlagNot(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::LogicFlagNotContext* GraphDBParser::logicFlagNot() {
  LogicFlagNotContext *_localctx = _tracker.createInstance<LogicFlagNotContext>(_ctx, getState());
  enterRule(_localctx, 118, GraphDBParser::RuleLogicFlagNot);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(705);
    match(GraphDBParser::K_not);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FirstOrderStatContext ------------------------------------------------------------------

GraphDBParser::FirstOrderStatContext::FirstOrderStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::FirstOrderUnitContext* GraphDBParser::FirstOrderStatContext::firstOrderUnit() {
  return getRuleContext<GraphDBParser::FirstOrderUnitContext>(0);
}

GraphDBParser::BracketLeftContext* GraphDBParser::FirstOrderStatContext::bracketLeft() {
  return getRuleContext<GraphDBParser::BracketLeftContext>(0);
}

std::vector<GraphDBParser::FirstOrderStatContext *> GraphDBParser::FirstOrderStatContext::firstOrderStat() {
  return getRuleContexts<GraphDBParser::FirstOrderStatContext>();
}

GraphDBParser::FirstOrderStatContext* GraphDBParser::FirstOrderStatContext::firstOrderStat(size_t i) {
  return getRuleContext<GraphDBParser::FirstOrderStatContext>(i);
}

GraphDBParser::BracketRightContext* GraphDBParser::FirstOrderStatContext::bracketRight() {
  return getRuleContext<GraphDBParser::BracketRightContext>(0);
}

GraphDBParser::LogicFlagNotContext* GraphDBParser::FirstOrderStatContext::logicFlagNot() {
  return getRuleContext<GraphDBParser::LogicFlagNotContext>(0);
}

tree::TerminalNode* GraphDBParser::FirstOrderStatContext::K_true() {
  return getToken(GraphDBParser::K_true, 0);
}

tree::TerminalNode* GraphDBParser::FirstOrderStatContext::K_false() {
  return getToken(GraphDBParser::K_false, 0);
}

GraphDBParser::LogicFlagBiContext* GraphDBParser::FirstOrderStatContext::logicFlagBi() {
  return getRuleContext<GraphDBParser::LogicFlagBiContext>(0);
}


size_t GraphDBParser::FirstOrderStatContext::getRuleIndex() const {
  return GraphDBParser::RuleFirstOrderStat;
}

void GraphDBParser::FirstOrderStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFirstOrderStat(this);
}

void GraphDBParser::FirstOrderStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFirstOrderStat(this);
}


antlrcpp::Any GraphDBParser::FirstOrderStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitFirstOrderStat(this);
  else
    return visitor->visitChildren(this);
}


GraphDBParser::FirstOrderStatContext* GraphDBParser::firstOrderStat() {
   return firstOrderStat(0);
}

GraphDBParser::FirstOrderStatContext* GraphDBParser::firstOrderStat(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  GraphDBParser::FirstOrderStatContext *_localctx = _tracker.createInstance<FirstOrderStatContext>(_ctx, parentState);
  GraphDBParser::FirstOrderStatContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 120;
  enterRecursionRule(_localctx, 120, GraphDBParser::RuleFirstOrderStat, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(718);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
    case 1: {
      setState(708);
      firstOrderUnit();
      break;
    }

    case 2: {
      setState(709);
      bracketLeft();
      setState(710);
      firstOrderStat(0);
      setState(711);
      bracketRight();
      break;
    }

    case 3: {
      setState(713);
      logicFlagNot();
      setState(714);
      firstOrderStat(3);
      break;
    }

    case 4: {
      setState(716);
      match(GraphDBParser::K_true);
      break;
    }

    case 5: {
      setState(717);
      match(GraphDBParser::K_false);
      break;
    }

    }
    _ctx->stop = _input->LT(-1);
    setState(726);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<FirstOrderStatContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleFirstOrderStat);
        setState(720);

        if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
        setState(721);
        logicFlagBi();
        setState(722);
        firstOrderStat(5); 
      }
      setState(728);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- FirstOrderUnitContext ------------------------------------------------------------------

GraphDBParser::FirstOrderUnitContext::FirstOrderUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::FuncStatContext* GraphDBParser::FirstOrderUnitContext::funcStat() {
  return getRuleContext<GraphDBParser::FuncStatContext>(0);
}

GraphDBParser::ExistStatContext* GraphDBParser::FirstOrderUnitContext::existStat() {
  return getRuleContext<GraphDBParser::ExistStatContext>(0);
}

GraphDBParser::ForeachStatContext* GraphDBParser::FirstOrderUnitContext::foreachStat() {
  return getRuleContext<GraphDBParser::ForeachStatContext>(0);
}

GraphDBParser::CompareValStatContext* GraphDBParser::FirstOrderUnitContext::compareValStat() {
  return getRuleContext<GraphDBParser::CompareValStatContext>(0);
}


size_t GraphDBParser::FirstOrderUnitContext::getRuleIndex() const {
  return GraphDBParser::RuleFirstOrderUnit;
}

void GraphDBParser::FirstOrderUnitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFirstOrderUnit(this);
}

void GraphDBParser::FirstOrderUnitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFirstOrderUnit(this);
}


antlrcpp::Any GraphDBParser::FirstOrderUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitFirstOrderUnit(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::FirstOrderUnitContext* GraphDBParser::firstOrderUnit() {
  FirstOrderUnitContext *_localctx = _tracker.createInstance<FirstOrderUnitContext>(_ctx, getState());
  enterRule(_localctx, 122, GraphDBParser::RuleFirstOrderUnit);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(733);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GraphDBParser::K_vertex:
      case GraphDBParser::K_edge:
      case GraphDBParser::K_equal:
      case GraphDBParser::K_complete:
      case GraphDBParser::K_hasedge:
      case GraphDBParser::K_graphequal:
      case GraphDBParser::K_unique:
      case GraphDBParser::K_sizegeq:
      case GraphDBParser::K_graphinset:
      case GraphDBParser::K_subgraph:
      case GraphDBParser::K_inducedsub:
      case GraphDBParser::K_connect:
      case GraphDBParser::K_clique:
      case GraphDBParser::K_tdensesub: {
        enterOuterAlt(_localctx, 1);
        setState(729);
        funcStat();
        break;
      }

      case GraphDBParser::K_exist: {
        enterOuterAlt(_localctx, 2);
        setState(730);
        existStat();
        break;
      }

      case GraphDBParser::K_foreach: {
        enterOuterAlt(_localctx, 3);
        setState(731);
        foreachStat();
        break;
      }

      case GraphDBParser::T__1:
      case GraphDBParser::K_true:
      case GraphDBParser::K_false:
      case GraphDBParser::INTEGER_NUMBER:
      case GraphDBParser::NOT_INTEGER_NUMBER:
      case GraphDBParser::NAME_STRING:
      case GraphDBParser::TEXT: {
        enterOuterAlt(_localctx, 4);
        setState(732);
        compareValStat();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExistStatContext ------------------------------------------------------------------

GraphDBParser::ExistStatContext::ExistStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::ExistStatContext::K_exist() {
  return getToken(GraphDBParser::K_exist, 0);
}

GraphDBParser::VarListContext* GraphDBParser::ExistStatContext::varList() {
  return getRuleContext<GraphDBParser::VarListContext>(0);
}

GraphDBParser::FirstOrderStatContext* GraphDBParser::ExistStatContext::firstOrderStat() {
  return getRuleContext<GraphDBParser::FirstOrderStatContext>(0);
}


size_t GraphDBParser::ExistStatContext::getRuleIndex() const {
  return GraphDBParser::RuleExistStat;
}

void GraphDBParser::ExistStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExistStat(this);
}

void GraphDBParser::ExistStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExistStat(this);
}


antlrcpp::Any GraphDBParser::ExistStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitExistStat(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::ExistStatContext* GraphDBParser::existStat() {
  ExistStatContext *_localctx = _tracker.createInstance<ExistStatContext>(_ctx, getState());
  enterRule(_localctx, 124, GraphDBParser::RuleExistStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(735);
    match(GraphDBParser::K_exist);
    setState(736);
    varList();
    setState(737);
    match(GraphDBParser::T__1);
    setState(738);
    firstOrderStat(0);
    setState(739);
    match(GraphDBParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForeachStatContext ------------------------------------------------------------------

GraphDBParser::ForeachStatContext::ForeachStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::ForeachStatContext::K_foreach() {
  return getToken(GraphDBParser::K_foreach, 0);
}

GraphDBParser::VarListContext* GraphDBParser::ForeachStatContext::varList() {
  return getRuleContext<GraphDBParser::VarListContext>(0);
}

GraphDBParser::FirstOrderStatContext* GraphDBParser::ForeachStatContext::firstOrderStat() {
  return getRuleContext<GraphDBParser::FirstOrderStatContext>(0);
}


size_t GraphDBParser::ForeachStatContext::getRuleIndex() const {
  return GraphDBParser::RuleForeachStat;
}

void GraphDBParser::ForeachStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForeachStat(this);
}

void GraphDBParser::ForeachStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForeachStat(this);
}


antlrcpp::Any GraphDBParser::ForeachStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitForeachStat(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::ForeachStatContext* GraphDBParser::foreachStat() {
  ForeachStatContext *_localctx = _tracker.createInstance<ForeachStatContext>(_ctx, getState());
  enterRule(_localctx, 126, GraphDBParser::RuleForeachStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(741);
    match(GraphDBParser::K_foreach);
    setState(742);
    varList();
    setState(743);
    match(GraphDBParser::T__1);
    setState(744);
    firstOrderStat(0);
    setState(745);
    match(GraphDBParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CompareStatContext ------------------------------------------------------------------

GraphDBParser::CompareStatContext::CompareStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::CompareUnitContext* GraphDBParser::CompareStatContext::compareUnit() {
  return getRuleContext<GraphDBParser::CompareUnitContext>(0);
}

GraphDBParser::BracketLeftContext* GraphDBParser::CompareStatContext::bracketLeft() {
  return getRuleContext<GraphDBParser::BracketLeftContext>(0);
}

std::vector<GraphDBParser::CompareStatContext *> GraphDBParser::CompareStatContext::compareStat() {
  return getRuleContexts<GraphDBParser::CompareStatContext>();
}

GraphDBParser::CompareStatContext* GraphDBParser::CompareStatContext::compareStat(size_t i) {
  return getRuleContext<GraphDBParser::CompareStatContext>(i);
}

GraphDBParser::BracketRightContext* GraphDBParser::CompareStatContext::bracketRight() {
  return getRuleContext<GraphDBParser::BracketRightContext>(0);
}

tree::TerminalNode* GraphDBParser::CompareStatContext::K_true() {
  return getToken(GraphDBParser::K_true, 0);
}

tree::TerminalNode* GraphDBParser::CompareStatContext::K_false() {
  return getToken(GraphDBParser::K_false, 0);
}

GraphDBParser::CalculateOperatorContext* GraphDBParser::CompareStatContext::calculateOperator() {
  return getRuleContext<GraphDBParser::CalculateOperatorContext>(0);
}


size_t GraphDBParser::CompareStatContext::getRuleIndex() const {
  return GraphDBParser::RuleCompareStat;
}

void GraphDBParser::CompareStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompareStat(this);
}

void GraphDBParser::CompareStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompareStat(this);
}


antlrcpp::Any GraphDBParser::CompareStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitCompareStat(this);
  else
    return visitor->visitChildren(this);
}


GraphDBParser::CompareStatContext* GraphDBParser::compareStat() {
   return compareStat(0);
}

GraphDBParser::CompareStatContext* GraphDBParser::compareStat(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  GraphDBParser::CompareStatContext *_localctx = _tracker.createInstance<CompareStatContext>(_ctx, parentState);
  GraphDBParser::CompareStatContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 128;
  enterRecursionRule(_localctx, 128, GraphDBParser::RuleCompareStat, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(755);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GraphDBParser::INTEGER_NUMBER:
      case GraphDBParser::NOT_INTEGER_NUMBER:
      case GraphDBParser::NAME_STRING:
      case GraphDBParser::TEXT: {
        setState(748);
        compareUnit();
        break;
      }

      case GraphDBParser::T__1: {
        setState(749);
        bracketLeft();
        setState(750);
        compareStat(0);
        setState(751);
        bracketRight();
        break;
      }

      case GraphDBParser::K_true: {
        setState(753);
        match(GraphDBParser::K_true);
        break;
      }

      case GraphDBParser::K_false: {
        setState(754);
        match(GraphDBParser::K_false);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(763);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<CompareStatContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleCompareStat);
        setState(757);

        if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
        setState(758);
        calculateOperator();
        setState(759);
        compareStat(5); 
      }
      setState(765);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- CompareUnitContext ------------------------------------------------------------------

GraphDBParser::CompareUnitContext::CompareUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::ValueContext* GraphDBParser::CompareUnitContext::value() {
  return getRuleContext<GraphDBParser::ValueContext>(0);
}

GraphDBParser::AttributeNameContext* GraphDBParser::CompareUnitContext::attributeName() {
  return getRuleContext<GraphDBParser::AttributeNameContext>(0);
}


size_t GraphDBParser::CompareUnitContext::getRuleIndex() const {
  return GraphDBParser::RuleCompareUnit;
}

void GraphDBParser::CompareUnitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompareUnit(this);
}

void GraphDBParser::CompareUnitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompareUnit(this);
}


antlrcpp::Any GraphDBParser::CompareUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitCompareUnit(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::CompareUnitContext* GraphDBParser::compareUnit() {
  CompareUnitContext *_localctx = _tracker.createInstance<CompareUnitContext>(_ctx, getState());
  enterRule(_localctx, 130, GraphDBParser::RuleCompareUnit);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(768);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GraphDBParser::INTEGER_NUMBER:
      case GraphDBParser::NOT_INTEGER_NUMBER:
      case GraphDBParser::TEXT: {
        enterOuterAlt(_localctx, 1);
        setState(766);
        value();
        break;
      }

      case GraphDBParser::NAME_STRING: {
        enterOuterAlt(_localctx, 2);
        setState(767);
        attributeName();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CompareValStatContext ------------------------------------------------------------------

GraphDBParser::CompareValStatContext::CompareValStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GraphDBParser::CompareStatContext *> GraphDBParser::CompareValStatContext::compareStat() {
  return getRuleContexts<GraphDBParser::CompareStatContext>();
}

GraphDBParser::CompareStatContext* GraphDBParser::CompareValStatContext::compareStat(size_t i) {
  return getRuleContext<GraphDBParser::CompareStatContext>(i);
}

GraphDBParser::CompareOperatorContext* GraphDBParser::CompareValStatContext::compareOperator() {
  return getRuleContext<GraphDBParser::CompareOperatorContext>(0);
}


size_t GraphDBParser::CompareValStatContext::getRuleIndex() const {
  return GraphDBParser::RuleCompareValStat;
}

void GraphDBParser::CompareValStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompareValStat(this);
}

void GraphDBParser::CompareValStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompareValStat(this);
}


antlrcpp::Any GraphDBParser::CompareValStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitCompareValStat(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::CompareValStatContext* GraphDBParser::compareValStat() {
  CompareValStatContext *_localctx = _tracker.createInstance<CompareValStatContext>(_ctx, getState());
  enterRule(_localctx, 132, GraphDBParser::RuleCompareValStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(770);
    compareStat(0);
    setState(771);
    compareOperator();
    setState(772);
    compareStat(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncStatContext ------------------------------------------------------------------

GraphDBParser::FuncStatContext::FuncStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::FuncNameContext* GraphDBParser::FuncStatContext::funcName() {
  return getRuleContext<GraphDBParser::FuncNameContext>(0);
}

GraphDBParser::ObjectListContext* GraphDBParser::FuncStatContext::objectList() {
  return getRuleContext<GraphDBParser::ObjectListContext>(0);
}


size_t GraphDBParser::FuncStatContext::getRuleIndex() const {
  return GraphDBParser::RuleFuncStat;
}

void GraphDBParser::FuncStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncStat(this);
}

void GraphDBParser::FuncStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncStat(this);
}


antlrcpp::Any GraphDBParser::FuncStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitFuncStat(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::FuncStatContext* GraphDBParser::funcStat() {
  FuncStatContext *_localctx = _tracker.createInstance<FuncStatContext>(_ctx, getState());
  enterRule(_localctx, 134, GraphDBParser::RuleFuncStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(783);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(774);
      funcName();
      setState(775);
      match(GraphDBParser::T__1);
      setState(776);
      objectList();
      setState(777);
      match(GraphDBParser::T__2);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(779);
      funcName();
      setState(780);
      match(GraphDBParser::T__1);
      setState(781);
      match(GraphDBParser::T__2);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncNameContext ------------------------------------------------------------------

GraphDBParser::FuncNameContext::FuncNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::FuncNameContext::K_equal() {
  return getToken(GraphDBParser::K_equal, 0);
}

tree::TerminalNode* GraphDBParser::FuncNameContext::K_vertex() {
  return getToken(GraphDBParser::K_vertex, 0);
}

tree::TerminalNode* GraphDBParser::FuncNameContext::K_edge() {
  return getToken(GraphDBParser::K_edge, 0);
}

tree::TerminalNode* GraphDBParser::FuncNameContext::K_complete() {
  return getToken(GraphDBParser::K_complete, 0);
}

tree::TerminalNode* GraphDBParser::FuncNameContext::K_unique() {
  return getToken(GraphDBParser::K_unique, 0);
}

tree::TerminalNode* GraphDBParser::FuncNameContext::K_hasedge() {
  return getToken(GraphDBParser::K_hasedge, 0);
}

tree::TerminalNode* GraphDBParser::FuncNameContext::K_sizegeq() {
  return getToken(GraphDBParser::K_sizegeq, 0);
}

tree::TerminalNode* GraphDBParser::FuncNameContext::K_graphequal() {
  return getToken(GraphDBParser::K_graphequal, 0);
}

tree::TerminalNode* GraphDBParser::FuncNameContext::K_graphinset() {
  return getToken(GraphDBParser::K_graphinset, 0);
}

tree::TerminalNode* GraphDBParser::FuncNameContext::K_subgraph() {
  return getToken(GraphDBParser::K_subgraph, 0);
}

tree::TerminalNode* GraphDBParser::FuncNameContext::K_inducedsub() {
  return getToken(GraphDBParser::K_inducedsub, 0);
}

tree::TerminalNode* GraphDBParser::FuncNameContext::K_connect() {
  return getToken(GraphDBParser::K_connect, 0);
}

tree::TerminalNode* GraphDBParser::FuncNameContext::K_clique() {
  return getToken(GraphDBParser::K_clique, 0);
}

tree::TerminalNode* GraphDBParser::FuncNameContext::K_tdensesub() {
  return getToken(GraphDBParser::K_tdensesub, 0);
}


size_t GraphDBParser::FuncNameContext::getRuleIndex() const {
  return GraphDBParser::RuleFuncName;
}

void GraphDBParser::FuncNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncName(this);
}

void GraphDBParser::FuncNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncName(this);
}


antlrcpp::Any GraphDBParser::FuncNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitFuncName(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::FuncNameContext* GraphDBParser::funcName() {
  FuncNameContext *_localctx = _tracker.createInstance<FuncNameContext>(_ctx, getState());
  enterRule(_localctx, 136, GraphDBParser::RuleFuncName);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(785);
    _la = _input->LA(1);
    if (!(((((_la - 50) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 50)) & ((1ULL << (GraphDBParser::K_vertex - 50))
      | (1ULL << (GraphDBParser::K_edge - 50))
      | (1ULL << (GraphDBParser::K_equal - 50))
      | (1ULL << (GraphDBParser::K_complete - 50))
      | (1ULL << (GraphDBParser::K_hasedge - 50))
      | (1ULL << (GraphDBParser::K_graphequal - 50))
      | (1ULL << (GraphDBParser::K_unique - 50))
      | (1ULL << (GraphDBParser::K_sizegeq - 50))
      | (1ULL << (GraphDBParser::K_graphinset - 50))
      | (1ULL << (GraphDBParser::K_subgraph - 50))
      | (1ULL << (GraphDBParser::K_inducedsub - 50))
      | (1ULL << (GraphDBParser::K_connect - 50))
      | (1ULL << (GraphDBParser::K_clique - 50))
      | (1ULL << (GraphDBParser::K_tdensesub - 50)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ObjectContext ------------------------------------------------------------------

GraphDBParser::ObjectContext::ObjectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::ParaItemContext* GraphDBParser::ObjectContext::paraItem() {
  return getRuleContext<GraphDBParser::ParaItemContext>(0);
}

GraphDBParser::IndexIntContext* GraphDBParser::ObjectContext::indexInt() {
  return getRuleContext<GraphDBParser::IndexIntContext>(0);
}


size_t GraphDBParser::ObjectContext::getRuleIndex() const {
  return GraphDBParser::RuleObject;
}

void GraphDBParser::ObjectContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterObject(this);
}

void GraphDBParser::ObjectContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitObject(this);
}


antlrcpp::Any GraphDBParser::ObjectContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitObject(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::ObjectContext* GraphDBParser::object() {
  ObjectContext *_localctx = _tracker.createInstance<ObjectContext>(_ctx, getState());
  enterRule(_localctx, 138, GraphDBParser::RuleObject);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(793);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(787);
      paraItem();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(788);
      paraItem();
      setState(789);
      match(GraphDBParser::T__7);
      setState(790);
      indexInt();
      setState(791);
      match(GraphDBParser::T__8);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ObjectListContext ------------------------------------------------------------------

GraphDBParser::ObjectListContext::ObjectListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::ObjectContext* GraphDBParser::ObjectListContext::object() {
  return getRuleContext<GraphDBParser::ObjectContext>(0);
}

GraphDBParser::ObjectListContext* GraphDBParser::ObjectListContext::objectList() {
  return getRuleContext<GraphDBParser::ObjectListContext>(0);
}


size_t GraphDBParser::ObjectListContext::getRuleIndex() const {
  return GraphDBParser::RuleObjectList;
}

void GraphDBParser::ObjectListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterObjectList(this);
}

void GraphDBParser::ObjectListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitObjectList(this);
}


antlrcpp::Any GraphDBParser::ObjectListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitObjectList(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::ObjectListContext* GraphDBParser::objectList() {
  ObjectListContext *_localctx = _tracker.createInstance<ObjectListContext>(_ctx, getState());
  enterRule(_localctx, 140, GraphDBParser::RuleObjectList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(800);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(795);
      object();
      setState(796);
      match(GraphDBParser::T__3);
      setState(797);
      objectList();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(799);
      object();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarListContext ------------------------------------------------------------------

GraphDBParser::VarListContext::VarListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::VariableNameContext* GraphDBParser::VarListContext::variableName() {
  return getRuleContext<GraphDBParser::VariableNameContext>(0);
}

GraphDBParser::VarListContext* GraphDBParser::VarListContext::varList() {
  return getRuleContext<GraphDBParser::VarListContext>(0);
}


size_t GraphDBParser::VarListContext::getRuleIndex() const {
  return GraphDBParser::RuleVarList;
}

void GraphDBParser::VarListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarList(this);
}

void GraphDBParser::VarListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarList(this);
}


antlrcpp::Any GraphDBParser::VarListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitVarList(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::VarListContext* GraphDBParser::varList() {
  VarListContext *_localctx = _tracker.createInstance<VarListContext>(_ctx, getState());
  enterRule(_localctx, 142, GraphDBParser::RuleVarList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(807);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(802);
      variableName();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(803);
      variableName();
      setState(804);
      match(GraphDBParser::T__3);
      setState(805);
      varList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BracketLeftContext ------------------------------------------------------------------

GraphDBParser::BracketLeftContext::BracketLeftContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t GraphDBParser::BracketLeftContext::getRuleIndex() const {
  return GraphDBParser::RuleBracketLeft;
}

void GraphDBParser::BracketLeftContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBracketLeft(this);
}

void GraphDBParser::BracketLeftContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBracketLeft(this);
}


antlrcpp::Any GraphDBParser::BracketLeftContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitBracketLeft(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::BracketLeftContext* GraphDBParser::bracketLeft() {
  BracketLeftContext *_localctx = _tracker.createInstance<BracketLeftContext>(_ctx, getState());
  enterRule(_localctx, 144, GraphDBParser::RuleBracketLeft);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(809);
    match(GraphDBParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BracketRightContext ------------------------------------------------------------------

GraphDBParser::BracketRightContext::BracketRightContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t GraphDBParser::BracketRightContext::getRuleIndex() const {
  return GraphDBParser::RuleBracketRight;
}

void GraphDBParser::BracketRightContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBracketRight(this);
}

void GraphDBParser::BracketRightContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBracketRight(this);
}


antlrcpp::Any GraphDBParser::BracketRightContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitBracketRight(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::BracketRightContext* GraphDBParser::bracketRight() {
  BracketRightContext *_localctx = _tracker.createInstance<BracketRightContext>(_ctx, getState());
  enterRule(_localctx, 146, GraphDBParser::RuleBracketRight);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(811);
    match(GraphDBParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DdlStatementContext ------------------------------------------------------------------

GraphDBParser::DdlStatementContext::DdlStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::CreateSchemaStatContext* GraphDBParser::DdlStatementContext::createSchemaStat() {
  return getRuleContext<GraphDBParser::CreateSchemaStatContext>(0);
}

GraphDBParser::CreateGsetStatContext* GraphDBParser::DdlStatementContext::createGsetStat() {
  return getRuleContext<GraphDBParser::CreateGsetStatContext>(0);
}

GraphDBParser::LoadGsetStatContext* GraphDBParser::DdlStatementContext::loadGsetStat() {
  return getRuleContext<GraphDBParser::LoadGsetStatContext>(0);
}

GraphDBParser::CreateGStatContext* GraphDBParser::DdlStatementContext::createGStat() {
  return getRuleContext<GraphDBParser::CreateGStatContext>(0);
}

GraphDBParser::LoadGStatContext* GraphDBParser::DdlStatementContext::loadGStat() {
  return getRuleContext<GraphDBParser::LoadGStatContext>(0);
}

GraphDBParser::DropStatContext* GraphDBParser::DdlStatementContext::dropStat() {
  return getRuleContext<GraphDBParser::DropStatContext>(0);
}


size_t GraphDBParser::DdlStatementContext::getRuleIndex() const {
  return GraphDBParser::RuleDdlStatement;
}

void GraphDBParser::DdlStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDdlStatement(this);
}

void GraphDBParser::DdlStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDdlStatement(this);
}


antlrcpp::Any GraphDBParser::DdlStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitDdlStatement(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::DdlStatementContext* GraphDBParser::ddlStatement() {
  DdlStatementContext *_localctx = _tracker.createInstance<DdlStatementContext>(_ctx, getState());
  enterRule(_localctx, 148, GraphDBParser::RuleDdlStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(819);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(813);
      createSchemaStat();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(814);
      createGsetStat();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(815);
      loadGsetStat();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(816);
      createGStat();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(817);
      loadGStat();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(818);
      dropStat();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateSchemaStatContext ------------------------------------------------------------------

GraphDBParser::CreateSchemaStatContext::CreateSchemaStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::CreateSchemaStatContext::K_create() {
  return getToken(GraphDBParser::K_create, 0);
}

tree::TerminalNode* GraphDBParser::CreateSchemaStatContext::K_schema() {
  return getToken(GraphDBParser::K_schema, 0);
}

GraphDBParser::SchemaidContext* GraphDBParser::CreateSchemaStatContext::schemaid() {
  return getRuleContext<GraphDBParser::SchemaidContext>(0);
}

GraphDBParser::SchemaStatementContext* GraphDBParser::CreateSchemaStatContext::schemaStatement() {
  return getRuleContext<GraphDBParser::SchemaStatementContext>(0);
}

tree::TerminalNode* GraphDBParser::CreateSchemaStatContext::K_file() {
  return getToken(GraphDBParser::K_file, 0);
}

GraphDBParser::FilenameContext* GraphDBParser::CreateSchemaStatContext::filename() {
  return getRuleContext<GraphDBParser::FilenameContext>(0);
}


size_t GraphDBParser::CreateSchemaStatContext::getRuleIndex() const {
  return GraphDBParser::RuleCreateSchemaStat;
}

void GraphDBParser::CreateSchemaStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCreateSchemaStat(this);
}

void GraphDBParser::CreateSchemaStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCreateSchemaStat(this);
}


antlrcpp::Any GraphDBParser::CreateSchemaStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitCreateSchemaStat(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::CreateSchemaStatContext* GraphDBParser::createSchemaStat() {
  CreateSchemaStatContext *_localctx = _tracker.createInstance<CreateSchemaStatContext>(_ctx, getState());
  enterRule(_localctx, 150, GraphDBParser::RuleCreateSchemaStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(830);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(821);
      match(GraphDBParser::K_create);
      setState(822);
      match(GraphDBParser::K_schema);
      setState(823);
      schemaid();
      setState(824);
      schemaStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(826);
      match(GraphDBParser::K_create);
      setState(827);
      match(GraphDBParser::K_schema);
      setState(828);
      match(GraphDBParser::K_file);
      setState(829);
      filename();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SchemaStatementContext ------------------------------------------------------------------

GraphDBParser::SchemaStatementContext::SchemaStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::SchemaNodeListContext* GraphDBParser::SchemaStatementContext::schemaNodeList() {
  return getRuleContext<GraphDBParser::SchemaNodeListContext>(0);
}

GraphDBParser::SchemaEdgeListContext* GraphDBParser::SchemaStatementContext::schemaEdgeList() {
  return getRuleContext<GraphDBParser::SchemaEdgeListContext>(0);
}


size_t GraphDBParser::SchemaStatementContext::getRuleIndex() const {
  return GraphDBParser::RuleSchemaStatement;
}

void GraphDBParser::SchemaStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSchemaStatement(this);
}

void GraphDBParser::SchemaStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSchemaStatement(this);
}


antlrcpp::Any GraphDBParser::SchemaStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitSchemaStatement(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::SchemaStatementContext* GraphDBParser::schemaStatement() {
  SchemaStatementContext *_localctx = _tracker.createInstance<SchemaStatementContext>(_ctx, getState());
  enterRule(_localctx, 152, GraphDBParser::RuleSchemaStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(832);
    match(GraphDBParser::T__5);
    setState(833);
    schemaNodeList();
    setState(834);
    match(GraphDBParser::T__3);
    setState(835);
    schemaEdgeList();
    setState(836);
    match(GraphDBParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SchemaNodeListContext ------------------------------------------------------------------

GraphDBParser::SchemaNodeListContext::SchemaNodeListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::SchemaNodeContext* GraphDBParser::SchemaNodeListContext::schemaNode() {
  return getRuleContext<GraphDBParser::SchemaNodeContext>(0);
}

GraphDBParser::SchemaNodeListContext* GraphDBParser::SchemaNodeListContext::schemaNodeList() {
  return getRuleContext<GraphDBParser::SchemaNodeListContext>(0);
}


size_t GraphDBParser::SchemaNodeListContext::getRuleIndex() const {
  return GraphDBParser::RuleSchemaNodeList;
}

void GraphDBParser::SchemaNodeListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSchemaNodeList(this);
}

void GraphDBParser::SchemaNodeListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSchemaNodeList(this);
}


antlrcpp::Any GraphDBParser::SchemaNodeListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitSchemaNodeList(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::SchemaNodeListContext* GraphDBParser::schemaNodeList() {
  SchemaNodeListContext *_localctx = _tracker.createInstance<SchemaNodeListContext>(_ctx, getState());
  enterRule(_localctx, 154, GraphDBParser::RuleSchemaNodeList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(843);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(838);
      schemaNode();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(839);
      schemaNode();
      setState(840);
      match(GraphDBParser::T__3);
      setState(841);
      schemaNodeList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SchemaEdgeListContext ------------------------------------------------------------------

GraphDBParser::SchemaEdgeListContext::SchemaEdgeListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::SchemaEdgeContext* GraphDBParser::SchemaEdgeListContext::schemaEdge() {
  return getRuleContext<GraphDBParser::SchemaEdgeContext>(0);
}

GraphDBParser::SchemaEdgeListContext* GraphDBParser::SchemaEdgeListContext::schemaEdgeList() {
  return getRuleContext<GraphDBParser::SchemaEdgeListContext>(0);
}


size_t GraphDBParser::SchemaEdgeListContext::getRuleIndex() const {
  return GraphDBParser::RuleSchemaEdgeList;
}

void GraphDBParser::SchemaEdgeListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSchemaEdgeList(this);
}

void GraphDBParser::SchemaEdgeListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSchemaEdgeList(this);
}


antlrcpp::Any GraphDBParser::SchemaEdgeListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitSchemaEdgeList(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::SchemaEdgeListContext* GraphDBParser::schemaEdgeList() {
  SchemaEdgeListContext *_localctx = _tracker.createInstance<SchemaEdgeListContext>(_ctx, getState());
  enterRule(_localctx, 156, GraphDBParser::RuleSchemaEdgeList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(850);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(845);
      schemaEdge();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(846);
      schemaEdge();
      setState(847);
      match(GraphDBParser::T__3);
      setState(848);
      schemaEdgeList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SchemaNodeContext ------------------------------------------------------------------

GraphDBParser::SchemaNodeContext::SchemaNodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::LabelNameContext* GraphDBParser::SchemaNodeContext::labelName() {
  return getRuleContext<GraphDBParser::LabelNameContext>(0);
}

GraphDBParser::SchemaAttrListContext* GraphDBParser::SchemaNodeContext::schemaAttrList() {
  return getRuleContext<GraphDBParser::SchemaAttrListContext>(0);
}


size_t GraphDBParser::SchemaNodeContext::getRuleIndex() const {
  return GraphDBParser::RuleSchemaNode;
}

void GraphDBParser::SchemaNodeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSchemaNode(this);
}

void GraphDBParser::SchemaNodeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSchemaNode(this);
}


antlrcpp::Any GraphDBParser::SchemaNodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitSchemaNode(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::SchemaNodeContext* GraphDBParser::schemaNode() {
  SchemaNodeContext *_localctx = _tracker.createInstance<SchemaNodeContext>(_ctx, getState());
  enterRule(_localctx, 158, GraphDBParser::RuleSchemaNode);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(852);
    labelName();
    setState(853);
    match(GraphDBParser::T__1);
    setState(854);
    schemaAttrList();
    setState(855);
    match(GraphDBParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SchemaAttrListContext ------------------------------------------------------------------

GraphDBParser::SchemaAttrListContext::SchemaAttrListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::LabelNameContext* GraphDBParser::SchemaAttrListContext::labelName() {
  return getRuleContext<GraphDBParser::LabelNameContext>(0);
}

GraphDBParser::TypeNameContext* GraphDBParser::SchemaAttrListContext::typeName() {
  return getRuleContext<GraphDBParser::TypeNameContext>(0);
}

GraphDBParser::SchemaAttrListContext* GraphDBParser::SchemaAttrListContext::schemaAttrList() {
  return getRuleContext<GraphDBParser::SchemaAttrListContext>(0);
}


size_t GraphDBParser::SchemaAttrListContext::getRuleIndex() const {
  return GraphDBParser::RuleSchemaAttrList;
}

void GraphDBParser::SchemaAttrListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSchemaAttrList(this);
}

void GraphDBParser::SchemaAttrListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSchemaAttrList(this);
}


antlrcpp::Any GraphDBParser::SchemaAttrListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitSchemaAttrList(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::SchemaAttrListContext* GraphDBParser::schemaAttrList() {
  SchemaAttrListContext *_localctx = _tracker.createInstance<SchemaAttrListContext>(_ctx, getState());
  enterRule(_localctx, 160, GraphDBParser::RuleSchemaAttrList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(865);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(857);
      labelName();
      setState(858);
      typeName();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(860);
      labelName();
      setState(861);
      typeName();
      setState(862);
      match(GraphDBParser::T__3);
      setState(863);
      schemaAttrList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SchemaEdgeContext ------------------------------------------------------------------

GraphDBParser::SchemaEdgeContext::SchemaEdgeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::LabelNameContext* GraphDBParser::SchemaEdgeContext::labelName() {
  return getRuleContext<GraphDBParser::LabelNameContext>(0);
}

GraphDBParser::EdgeLinkageListContext* GraphDBParser::SchemaEdgeContext::edgeLinkageList() {
  return getRuleContext<GraphDBParser::EdgeLinkageListContext>(0);
}

GraphDBParser::SchemaAttrListContext* GraphDBParser::SchemaEdgeContext::schemaAttrList() {
  return getRuleContext<GraphDBParser::SchemaAttrListContext>(0);
}


size_t GraphDBParser::SchemaEdgeContext::getRuleIndex() const {
  return GraphDBParser::RuleSchemaEdge;
}

void GraphDBParser::SchemaEdgeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSchemaEdge(this);
}

void GraphDBParser::SchemaEdgeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSchemaEdge(this);
}


antlrcpp::Any GraphDBParser::SchemaEdgeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitSchemaEdge(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::SchemaEdgeContext* GraphDBParser::schemaEdge() {
  SchemaEdgeContext *_localctx = _tracker.createInstance<SchemaEdgeContext>(_ctx, getState());
  enterRule(_localctx, 162, GraphDBParser::RuleSchemaEdge);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(867);
    labelName();
    setState(868);
    match(GraphDBParser::T__7);
    setState(869);
    edgeLinkageList();
    setState(870);
    match(GraphDBParser::T__8);
    setState(871);
    match(GraphDBParser::T__1);
    setState(872);
    schemaAttrList();
    setState(873);
    match(GraphDBParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EdgeLinkageListContext ------------------------------------------------------------------

GraphDBParser::EdgeLinkageListContext::EdgeLinkageListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GraphDBParser::LabelNameContext *> GraphDBParser::EdgeLinkageListContext::labelName() {
  return getRuleContexts<GraphDBParser::LabelNameContext>();
}

GraphDBParser::LabelNameContext* GraphDBParser::EdgeLinkageListContext::labelName(size_t i) {
  return getRuleContext<GraphDBParser::LabelNameContext>(i);
}

GraphDBParser::EdgeLinkageListContext* GraphDBParser::EdgeLinkageListContext::edgeLinkageList() {
  return getRuleContext<GraphDBParser::EdgeLinkageListContext>(0);
}


size_t GraphDBParser::EdgeLinkageListContext::getRuleIndex() const {
  return GraphDBParser::RuleEdgeLinkageList;
}

void GraphDBParser::EdgeLinkageListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEdgeLinkageList(this);
}

void GraphDBParser::EdgeLinkageListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEdgeLinkageList(this);
}


antlrcpp::Any GraphDBParser::EdgeLinkageListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitEdgeLinkageList(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::EdgeLinkageListContext* GraphDBParser::edgeLinkageList() {
  EdgeLinkageListContext *_localctx = _tracker.createInstance<EdgeLinkageListContext>(_ctx, getState());
  enterRule(_localctx, 164, GraphDBParser::RuleEdgeLinkageList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(885);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(875);
      labelName();
      setState(876);
      match(GraphDBParser::T__11);
      setState(877);
      labelName();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(879);
      labelName();
      setState(880);
      match(GraphDBParser::T__11);
      setState(881);
      labelName();
      setState(882);
      match(GraphDBParser::T__3);
      setState(883);
      edgeLinkageList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LabelNameContext ------------------------------------------------------------------

GraphDBParser::LabelNameContext::LabelNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::LabelNameContext::NAME_STRING() {
  return getToken(GraphDBParser::NAME_STRING, 0);
}


size_t GraphDBParser::LabelNameContext::getRuleIndex() const {
  return GraphDBParser::RuleLabelName;
}

void GraphDBParser::LabelNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLabelName(this);
}

void GraphDBParser::LabelNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLabelName(this);
}


antlrcpp::Any GraphDBParser::LabelNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitLabelName(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::LabelNameContext* GraphDBParser::labelName() {
  LabelNameContext *_localctx = _tracker.createInstance<LabelNameContext>(_ctx, getState());
  enterRule(_localctx, 166, GraphDBParser::RuleLabelName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(887);
    match(GraphDBParser::NAME_STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeNameContext ------------------------------------------------------------------

GraphDBParser::TypeNameContext::TypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::DataTypeContext* GraphDBParser::TypeNameContext::dataType() {
  return getRuleContext<GraphDBParser::DataTypeContext>(0);
}


size_t GraphDBParser::TypeNameContext::getRuleIndex() const {
  return GraphDBParser::RuleTypeName;
}

void GraphDBParser::TypeNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeName(this);
}

void GraphDBParser::TypeNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeName(this);
}


antlrcpp::Any GraphDBParser::TypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitTypeName(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::TypeNameContext* GraphDBParser::typeName() {
  TypeNameContext *_localctx = _tracker.createInstance<TypeNameContext>(_ctx, getState());
  enterRule(_localctx, 168, GraphDBParser::RuleTypeName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(889);
    dataType();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SchemaItemContext ------------------------------------------------------------------

GraphDBParser::SchemaItemContext::SchemaItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::SchemaTypeListContext* GraphDBParser::SchemaItemContext::schemaTypeList() {
  return getRuleContext<GraphDBParser::SchemaTypeListContext>(0);
}

GraphDBParser::SchemaidContext* GraphDBParser::SchemaItemContext::schemaid() {
  return getRuleContext<GraphDBParser::SchemaidContext>(0);
}


size_t GraphDBParser::SchemaItemContext::getRuleIndex() const {
  return GraphDBParser::RuleSchemaItem;
}

void GraphDBParser::SchemaItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSchemaItem(this);
}

void GraphDBParser::SchemaItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSchemaItem(this);
}


antlrcpp::Any GraphDBParser::SchemaItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitSchemaItem(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::SchemaItemContext* GraphDBParser::schemaItem() {
  SchemaItemContext *_localctx = _tracker.createInstance<SchemaItemContext>(_ctx, getState());
  enterRule(_localctx, 170, GraphDBParser::RuleSchemaItem);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(896);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GraphDBParser::T__5: {
        enterOuterAlt(_localctx, 1);
        setState(891);
        match(GraphDBParser::T__5);
        setState(892);
        schemaTypeList();
        setState(893);
        match(GraphDBParser::T__6);
        break;
      }

      case GraphDBParser::NAME_STRING: {
        enterOuterAlt(_localctx, 2);
        setState(895);
        schemaid();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateGsetStatContext ------------------------------------------------------------------

GraphDBParser::CreateGsetStatContext::CreateGsetStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::CreateGsetStatContext::K_create() {
  return getToken(GraphDBParser::K_create, 0);
}

tree::TerminalNode* GraphDBParser::CreateGsetStatContext::K_graphset() {
  return getToken(GraphDBParser::K_graphset, 0);
}

GraphDBParser::GsidContext* GraphDBParser::CreateGsetStatContext::gsid() {
  return getRuleContext<GraphDBParser::GsidContext>(0);
}

GraphDBParser::GidListContext* GraphDBParser::CreateGsetStatContext::gidList() {
  return getRuleContext<GraphDBParser::GidListContext>(0);
}

GraphDBParser::SchemaItemContext* GraphDBParser::CreateGsetStatContext::schemaItem() {
  return getRuleContext<GraphDBParser::SchemaItemContext>(0);
}


size_t GraphDBParser::CreateGsetStatContext::getRuleIndex() const {
  return GraphDBParser::RuleCreateGsetStat;
}

void GraphDBParser::CreateGsetStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCreateGsetStat(this);
}

void GraphDBParser::CreateGsetStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCreateGsetStat(this);
}


antlrcpp::Any GraphDBParser::CreateGsetStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitCreateGsetStat(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::CreateGsetStatContext* GraphDBParser::createGsetStat() {
  CreateGsetStatContext *_localctx = _tracker.createInstance<CreateGsetStatContext>(_ctx, getState());
  enterRule(_localctx, 172, GraphDBParser::RuleCreateGsetStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(898);
    match(GraphDBParser::K_create);
    setState(899);
    match(GraphDBParser::K_graphset);
    setState(900);
    gsid();
    setState(901);
    match(GraphDBParser::T__1);
    setState(902);
    gidList();
    setState(903);
    match(GraphDBParser::T__2);
    setState(904);
    schemaItem();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateGStatContext ------------------------------------------------------------------

GraphDBParser::CreateGStatContext::CreateGStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::CreateGStatContext::K_create() {
  return getToken(GraphDBParser::K_create, 0);
}

tree::TerminalNode* GraphDBParser::CreateGStatContext::K_graph() {
  return getToken(GraphDBParser::K_graph, 0);
}

GraphDBParser::GidContext* GraphDBParser::CreateGStatContext::gid() {
  return getRuleContext<GraphDBParser::GidContext>(0);
}

GraphDBParser::SchemaItemContext* GraphDBParser::CreateGStatContext::schemaItem() {
  return getRuleContext<GraphDBParser::SchemaItemContext>(0);
}

GraphDBParser::CreateGFileStatContext* GraphDBParser::CreateGStatContext::createGFileStat() {
  return getRuleContext<GraphDBParser::CreateGFileStatContext>(0);
}

GraphDBParser::CreateGForStatContext* GraphDBParser::CreateGStatContext::createGForStat() {
  return getRuleContext<GraphDBParser::CreateGForStatContext>(0);
}


size_t GraphDBParser::CreateGStatContext::getRuleIndex() const {
  return GraphDBParser::RuleCreateGStat;
}

void GraphDBParser::CreateGStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCreateGStat(this);
}

void GraphDBParser::CreateGStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCreateGStat(this);
}


antlrcpp::Any GraphDBParser::CreateGStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitCreateGStat(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::CreateGStatContext* GraphDBParser::createGStat() {
  CreateGStatContext *_localctx = _tracker.createInstance<CreateGStatContext>(_ctx, getState());
  enterRule(_localctx, 174, GraphDBParser::RuleCreateGStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(906);
    match(GraphDBParser::K_create);
    setState(907);
    match(GraphDBParser::K_graph);
    setState(908);
    gid();
    setState(909);
    schemaItem();
    setState(910);
    createGFileStat();
    setState(911);
    createGForStat();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateGFileStatContext ------------------------------------------------------------------

GraphDBParser::CreateGFileStatContext::CreateGFileStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::CreateGFileStatContext::K_from() {
  return getToken(GraphDBParser::K_from, 0);
}

tree::TerminalNode* GraphDBParser::CreateGFileStatContext::K_file() {
  return getToken(GraphDBParser::K_file, 0);
}

GraphDBParser::FilenamelistContext* GraphDBParser::CreateGFileStatContext::filenamelist() {
  return getRuleContext<GraphDBParser::FilenamelistContext>(0);
}


size_t GraphDBParser::CreateGFileStatContext::getRuleIndex() const {
  return GraphDBParser::RuleCreateGFileStat;
}

void GraphDBParser::CreateGFileStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCreateGFileStat(this);
}

void GraphDBParser::CreateGFileStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCreateGFileStat(this);
}


antlrcpp::Any GraphDBParser::CreateGFileStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitCreateGFileStat(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::CreateGFileStatContext* GraphDBParser::createGFileStat() {
  CreateGFileStatContext *_localctx = _tracker.createInstance<CreateGFileStatContext>(_ctx, getState());
  enterRule(_localctx, 176, GraphDBParser::RuleCreateGFileStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(917);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GraphDBParser::K_from: {
        enterOuterAlt(_localctx, 1);
        setState(913);
        match(GraphDBParser::K_from);
        setState(914);
        match(GraphDBParser::K_file);
        setState(915);
        filenamelist();
        break;
      }

      case GraphDBParser::T__0:
      case GraphDBParser::K_for: {
        enterOuterAlt(_localctx, 2);

        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateGForStatContext ------------------------------------------------------------------

GraphDBParser::CreateGForStatContext::CreateGForStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::CreateGForStatContext::K_for() {
  return getToken(GraphDBParser::K_for, 0);
}

GraphDBParser::GsidContext* GraphDBParser::CreateGForStatContext::gsid() {
  return getRuleContext<GraphDBParser::GsidContext>(0);
}


size_t GraphDBParser::CreateGForStatContext::getRuleIndex() const {
  return GraphDBParser::RuleCreateGForStat;
}

void GraphDBParser::CreateGForStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCreateGForStat(this);
}

void GraphDBParser::CreateGForStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCreateGForStat(this);
}


antlrcpp::Any GraphDBParser::CreateGForStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitCreateGForStat(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::CreateGForStatContext* GraphDBParser::createGForStat() {
  CreateGForStatContext *_localctx = _tracker.createInstance<CreateGForStatContext>(_ctx, getState());
  enterRule(_localctx, 178, GraphDBParser::RuleCreateGForStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(922);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GraphDBParser::K_for: {
        enterOuterAlt(_localctx, 1);
        setState(919);
        match(GraphDBParser::K_for);
        setState(920);
        gsid();
        break;
      }

      case GraphDBParser::T__0: {
        enterOuterAlt(_localctx, 2);

        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LoadGsetStatContext ------------------------------------------------------------------

GraphDBParser::LoadGsetStatContext::LoadGsetStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::LoadGsetStatContext::K_load() {
  return getToken(GraphDBParser::K_load, 0);
}

tree::TerminalNode* GraphDBParser::LoadGsetStatContext::K_graphset() {
  return getToken(GraphDBParser::K_graphset, 0);
}

GraphDBParser::GsidContext* GraphDBParser::LoadGsetStatContext::gsid() {
  return getRuleContext<GraphDBParser::GsidContext>(0);
}


size_t GraphDBParser::LoadGsetStatContext::getRuleIndex() const {
  return GraphDBParser::RuleLoadGsetStat;
}

void GraphDBParser::LoadGsetStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLoadGsetStat(this);
}

void GraphDBParser::LoadGsetStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLoadGsetStat(this);
}


antlrcpp::Any GraphDBParser::LoadGsetStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitLoadGsetStat(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::LoadGsetStatContext* GraphDBParser::loadGsetStat() {
  LoadGsetStatContext *_localctx = _tracker.createInstance<LoadGsetStatContext>(_ctx, getState());
  enterRule(_localctx, 180, GraphDBParser::RuleLoadGsetStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(924);
    match(GraphDBParser::K_load);
    setState(925);
    match(GraphDBParser::K_graphset);
    setState(926);
    gsid();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LoadGStatContext ------------------------------------------------------------------

GraphDBParser::LoadGStatContext::LoadGStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::LoadGStatContext::K_load() {
  return getToken(GraphDBParser::K_load, 0);
}

tree::TerminalNode* GraphDBParser::LoadGStatContext::K_graph() {
  return getToken(GraphDBParser::K_graph, 0);
}

GraphDBParser::GidContext* GraphDBParser::LoadGStatContext::gid() {
  return getRuleContext<GraphDBParser::GidContext>(0);
}


size_t GraphDBParser::LoadGStatContext::getRuleIndex() const {
  return GraphDBParser::RuleLoadGStat;
}

void GraphDBParser::LoadGStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLoadGStat(this);
}

void GraphDBParser::LoadGStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLoadGStat(this);
}


antlrcpp::Any GraphDBParser::LoadGStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitLoadGStat(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::LoadGStatContext* GraphDBParser::loadGStat() {
  LoadGStatContext *_localctx = _tracker.createInstance<LoadGStatContext>(_ctx, getState());
  enterRule(_localctx, 182, GraphDBParser::RuleLoadGStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(928);
    match(GraphDBParser::K_load);
    setState(929);
    match(GraphDBParser::K_graph);
    setState(930);
    gid();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DropStatContext ------------------------------------------------------------------

GraphDBParser::DropStatContext::DropStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::DropGsetStatContext* GraphDBParser::DropStatContext::dropGsetStat() {
  return getRuleContext<GraphDBParser::DropGsetStatContext>(0);
}

GraphDBParser::DropGStatContext* GraphDBParser::DropStatContext::dropGStat() {
  return getRuleContext<GraphDBParser::DropGStatContext>(0);
}

GraphDBParser::DropSchemaStatContext* GraphDBParser::DropStatContext::dropSchemaStat() {
  return getRuleContext<GraphDBParser::DropSchemaStatContext>(0);
}


size_t GraphDBParser::DropStatContext::getRuleIndex() const {
  return GraphDBParser::RuleDropStat;
}

void GraphDBParser::DropStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDropStat(this);
}

void GraphDBParser::DropStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDropStat(this);
}


antlrcpp::Any GraphDBParser::DropStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitDropStat(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::DropStatContext* GraphDBParser::dropStat() {
  DropStatContext *_localctx = _tracker.createInstance<DropStatContext>(_ctx, getState());
  enterRule(_localctx, 184, GraphDBParser::RuleDropStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(935);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 64, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(932);
      dropGsetStat();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(933);
      dropGStat();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(934);
      dropSchemaStat();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DropGsetStatContext ------------------------------------------------------------------

GraphDBParser::DropGsetStatContext::DropGsetStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::DropGsetStatContext::K_drop() {
  return getToken(GraphDBParser::K_drop, 0);
}

tree::TerminalNode* GraphDBParser::DropGsetStatContext::K_graphset() {
  return getToken(GraphDBParser::K_graphset, 0);
}

GraphDBParser::GsidContext* GraphDBParser::DropGsetStatContext::gsid() {
  return getRuleContext<GraphDBParser::GsidContext>(0);
}


size_t GraphDBParser::DropGsetStatContext::getRuleIndex() const {
  return GraphDBParser::RuleDropGsetStat;
}

void GraphDBParser::DropGsetStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDropGsetStat(this);
}

void GraphDBParser::DropGsetStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDropGsetStat(this);
}


antlrcpp::Any GraphDBParser::DropGsetStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitDropGsetStat(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::DropGsetStatContext* GraphDBParser::dropGsetStat() {
  DropGsetStatContext *_localctx = _tracker.createInstance<DropGsetStatContext>(_ctx, getState());
  enterRule(_localctx, 186, GraphDBParser::RuleDropGsetStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(937);
    match(GraphDBParser::K_drop);
    setState(938);
    match(GraphDBParser::K_graphset);
    setState(939);
    gsid();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DropGStatContext ------------------------------------------------------------------

GraphDBParser::DropGStatContext::DropGStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::DropGStatContext::K_drop() {
  return getToken(GraphDBParser::K_drop, 0);
}

tree::TerminalNode* GraphDBParser::DropGStatContext::K_graph() {
  return getToken(GraphDBParser::K_graph, 0);
}

GraphDBParser::GidContext* GraphDBParser::DropGStatContext::gid() {
  return getRuleContext<GraphDBParser::GidContext>(0);
}


size_t GraphDBParser::DropGStatContext::getRuleIndex() const {
  return GraphDBParser::RuleDropGStat;
}

void GraphDBParser::DropGStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDropGStat(this);
}

void GraphDBParser::DropGStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDropGStat(this);
}


antlrcpp::Any GraphDBParser::DropGStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitDropGStat(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::DropGStatContext* GraphDBParser::dropGStat() {
  DropGStatContext *_localctx = _tracker.createInstance<DropGStatContext>(_ctx, getState());
  enterRule(_localctx, 188, GraphDBParser::RuleDropGStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(941);
    match(GraphDBParser::K_drop);
    setState(942);
    match(GraphDBParser::K_graph);
    setState(943);
    gid();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DropSchemaStatContext ------------------------------------------------------------------

GraphDBParser::DropSchemaStatContext::DropSchemaStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::DropSchemaStatContext::K_drop() {
  return getToken(GraphDBParser::K_drop, 0);
}

tree::TerminalNode* GraphDBParser::DropSchemaStatContext::K_schema() {
  return getToken(GraphDBParser::K_schema, 0);
}

GraphDBParser::SchemaidContext* GraphDBParser::DropSchemaStatContext::schemaid() {
  return getRuleContext<GraphDBParser::SchemaidContext>(0);
}


size_t GraphDBParser::DropSchemaStatContext::getRuleIndex() const {
  return GraphDBParser::RuleDropSchemaStat;
}

void GraphDBParser::DropSchemaStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDropSchemaStat(this);
}

void GraphDBParser::DropSchemaStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDropSchemaStat(this);
}


antlrcpp::Any GraphDBParser::DropSchemaStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitDropSchemaStat(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::DropSchemaStatContext* GraphDBParser::dropSchemaStat() {
  DropSchemaStatContext *_localctx = _tracker.createInstance<DropSchemaStatContext>(_ctx, getState());
  enterRule(_localctx, 190, GraphDBParser::RuleDropSchemaStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(945);
    match(GraphDBParser::K_drop);
    setState(946);
    match(GraphDBParser::K_schema);
    setState(947);
    schemaid();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SchemaTypeListContext ------------------------------------------------------------------

GraphDBParser::SchemaTypeListContext::SchemaTypeListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::LidContext* GraphDBParser::SchemaTypeListContext::lid() {
  return getRuleContext<GraphDBParser::LidContext>(0);
}

GraphDBParser::SchemaAttributeItemContext* GraphDBParser::SchemaTypeListContext::schemaAttributeItem() {
  return getRuleContext<GraphDBParser::SchemaAttributeItemContext>(0);
}

GraphDBParser::SchemaTypeListContext* GraphDBParser::SchemaTypeListContext::schemaTypeList() {
  return getRuleContext<GraphDBParser::SchemaTypeListContext>(0);
}


size_t GraphDBParser::SchemaTypeListContext::getRuleIndex() const {
  return GraphDBParser::RuleSchemaTypeList;
}

void GraphDBParser::SchemaTypeListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSchemaTypeList(this);
}

void GraphDBParser::SchemaTypeListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSchemaTypeList(this);
}


antlrcpp::Any GraphDBParser::SchemaTypeListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitSchemaTypeList(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::SchemaTypeListContext* GraphDBParser::schemaTypeList() {
  SchemaTypeListContext *_localctx = _tracker.createInstance<SchemaTypeListContext>(_ctx, getState());
  enterRule(_localctx, 192, GraphDBParser::RuleSchemaTypeList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(961);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(949);
      lid();
      setState(950);
      match(GraphDBParser::T__9);
      setState(951);
      schemaAttributeItem();
      setState(952);
      match(GraphDBParser::T__10);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(954);
      lid();
      setState(955);
      match(GraphDBParser::T__9);
      setState(956);
      schemaAttributeItem();
      setState(957);
      match(GraphDBParser::T__10);
      setState(958);
      match(GraphDBParser::T__3);
      setState(959);
      schemaTypeList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SchemaAttributeItemContext ------------------------------------------------------------------

GraphDBParser::SchemaAttributeItemContext::SchemaAttributeItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::AttrItemContext* GraphDBParser::SchemaAttributeItemContext::attrItem() {
  return getRuleContext<GraphDBParser::AttrItemContext>(0);
}

GraphDBParser::SchemaAttributeItemContext* GraphDBParser::SchemaAttributeItemContext::schemaAttributeItem() {
  return getRuleContext<GraphDBParser::SchemaAttributeItemContext>(0);
}


size_t GraphDBParser::SchemaAttributeItemContext::getRuleIndex() const {
  return GraphDBParser::RuleSchemaAttributeItem;
}

void GraphDBParser::SchemaAttributeItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSchemaAttributeItem(this);
}

void GraphDBParser::SchemaAttributeItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSchemaAttributeItem(this);
}


antlrcpp::Any GraphDBParser::SchemaAttributeItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitSchemaAttributeItem(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::SchemaAttributeItemContext* GraphDBParser::schemaAttributeItem() {
  SchemaAttributeItemContext *_localctx = _tracker.createInstance<SchemaAttributeItemContext>(_ctx, getState());
  enterRule(_localctx, 194, GraphDBParser::RuleSchemaAttributeItem);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(968);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(963);
      attrItem();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(964);
      attrItem();
      setState(965);
      match(GraphDBParser::T__3);
      setState(966);
      schemaAttributeItem();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttrItemContext ------------------------------------------------------------------

GraphDBParser::AttrItemContext::AttrItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GraphDBParser::AttributeNameContext* GraphDBParser::AttrItemContext::attributeName() {
  return getRuleContext<GraphDBParser::AttributeNameContext>(0);
}

GraphDBParser::DataTypeContext* GraphDBParser::AttrItemContext::dataType() {
  return getRuleContext<GraphDBParser::DataTypeContext>(0);
}


size_t GraphDBParser::AttrItemContext::getRuleIndex() const {
  return GraphDBParser::RuleAttrItem;
}

void GraphDBParser::AttrItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttrItem(this);
}

void GraphDBParser::AttrItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttrItem(this);
}


antlrcpp::Any GraphDBParser::AttrItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitAttrItem(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::AttrItemContext* GraphDBParser::attrItem() {
  AttrItemContext *_localctx = _tracker.createInstance<AttrItemContext>(_ctx, getState());
  enterRule(_localctx, 196, GraphDBParser::RuleAttrItem);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(970);
    attributeName();
    setState(971);
    match(GraphDBParser::T__18);
    setState(972);
    dataType();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DataTypeContext ------------------------------------------------------------------

GraphDBParser::DataTypeContext::DataTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::DataTypeContext::K_int() {
  return getToken(GraphDBParser::K_int, 0);
}

tree::TerminalNode* GraphDBParser::DataTypeContext::K_integer() {
  return getToken(GraphDBParser::K_integer, 0);
}

tree::TerminalNode* GraphDBParser::DataTypeContext::K_float() {
  return getToken(GraphDBParser::K_float, 0);
}

tree::TerminalNode* GraphDBParser::DataTypeContext::K_double() {
  return getToken(GraphDBParser::K_double, 0);
}

tree::TerminalNode* GraphDBParser::DataTypeContext::K_char() {
  return getToken(GraphDBParser::K_char, 0);
}

tree::TerminalNode* GraphDBParser::DataTypeContext::K_string() {
  return getToken(GraphDBParser::K_string, 0);
}


size_t GraphDBParser::DataTypeContext::getRuleIndex() const {
  return GraphDBParser::RuleDataType;
}

void GraphDBParser::DataTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDataType(this);
}

void GraphDBParser::DataTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDataType(this);
}


antlrcpp::Any GraphDBParser::DataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitDataType(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::DataTypeContext* GraphDBParser::dataType() {
  DataTypeContext *_localctx = _tracker.createInstance<DataTypeContext>(_ctx, getState());
  enterRule(_localctx, 198, GraphDBParser::RuleDataType);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(974);
    _la = _input->LA(1);
    if (!(((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & ((1ULL << (GraphDBParser::K_int - 71))
      | (1ULL << (GraphDBParser::K_integer - 71))
      | (1ULL << (GraphDBParser::K_float - 71))
      | (1ULL << (GraphDBParser::K_double - 71))
      | (1ULL << (GraphDBParser::K_char - 71))
      | (1ULL << (GraphDBParser::K_string - 71)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttributeNameContext ------------------------------------------------------------------

GraphDBParser::AttributeNameContext::AttributeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::AttributeNameContext::NAME_STRING() {
  return getToken(GraphDBParser::NAME_STRING, 0);
}


size_t GraphDBParser::AttributeNameContext::getRuleIndex() const {
  return GraphDBParser::RuleAttributeName;
}

void GraphDBParser::AttributeNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttributeName(this);
}

void GraphDBParser::AttributeNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttributeName(this);
}


antlrcpp::Any GraphDBParser::AttributeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitAttributeName(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::AttributeNameContext* GraphDBParser::attributeName() {
  AttributeNameContext *_localctx = _tracker.createInstance<AttributeNameContext>(_ctx, getState());
  enterRule(_localctx, 200, GraphDBParser::RuleAttributeName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(976);
    match(GraphDBParser::NAME_STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GsidContext ------------------------------------------------------------------

GraphDBParser::GsidContext::GsidContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::GsidContext::NAME_STRING() {
  return getToken(GraphDBParser::NAME_STRING, 0);
}


size_t GraphDBParser::GsidContext::getRuleIndex() const {
  return GraphDBParser::RuleGsid;
}

void GraphDBParser::GsidContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGsid(this);
}

void GraphDBParser::GsidContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGsid(this);
}


antlrcpp::Any GraphDBParser::GsidContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitGsid(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::GsidContext* GraphDBParser::gsid() {
  GsidContext *_localctx = _tracker.createInstance<GsidContext>(_ctx, getState());
  enterRule(_localctx, 202, GraphDBParser::RuleGsid);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(978);
    match(GraphDBParser::NAME_STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GidContext ------------------------------------------------------------------

GraphDBParser::GidContext::GidContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::GidContext::NAME_STRING() {
  return getToken(GraphDBParser::NAME_STRING, 0);
}


size_t GraphDBParser::GidContext::getRuleIndex() const {
  return GraphDBParser::RuleGid;
}

void GraphDBParser::GidContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGid(this);
}

void GraphDBParser::GidContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGid(this);
}


antlrcpp::Any GraphDBParser::GidContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitGid(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::GidContext* GraphDBParser::gid() {
  GidContext *_localctx = _tracker.createInstance<GidContext>(_ctx, getState());
  enterRule(_localctx, 204, GraphDBParser::RuleGid);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(980);
    match(GraphDBParser::NAME_STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VidContext ------------------------------------------------------------------

GraphDBParser::VidContext::VidContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::VidContext::NAME_STRING() {
  return getToken(GraphDBParser::NAME_STRING, 0);
}


size_t GraphDBParser::VidContext::getRuleIndex() const {
  return GraphDBParser::RuleVid;
}

void GraphDBParser::VidContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVid(this);
}

void GraphDBParser::VidContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVid(this);
}


antlrcpp::Any GraphDBParser::VidContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitVid(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::VidContext* GraphDBParser::vid() {
  VidContext *_localctx = _tracker.createInstance<VidContext>(_ctx, getState());
  enterRule(_localctx, 206, GraphDBParser::RuleVid);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(982);
    match(GraphDBParser::NAME_STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EidContext ------------------------------------------------------------------

GraphDBParser::EidContext::EidContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::EidContext::NAME_STRING() {
  return getToken(GraphDBParser::NAME_STRING, 0);
}


size_t GraphDBParser::EidContext::getRuleIndex() const {
  return GraphDBParser::RuleEid;
}

void GraphDBParser::EidContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEid(this);
}

void GraphDBParser::EidContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEid(this);
}


antlrcpp::Any GraphDBParser::EidContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitEid(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::EidContext* GraphDBParser::eid() {
  EidContext *_localctx = _tracker.createInstance<EidContext>(_ctx, getState());
  enterRule(_localctx, 208, GraphDBParser::RuleEid);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(984);
    match(GraphDBParser::NAME_STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LidContext ------------------------------------------------------------------

GraphDBParser::LidContext::LidContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::LidContext::NAME_STRING() {
  return getToken(GraphDBParser::NAME_STRING, 0);
}


size_t GraphDBParser::LidContext::getRuleIndex() const {
  return GraphDBParser::RuleLid;
}

void GraphDBParser::LidContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLid(this);
}

void GraphDBParser::LidContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLid(this);
}


antlrcpp::Any GraphDBParser::LidContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitLid(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::LidContext* GraphDBParser::lid() {
  LidContext *_localctx = _tracker.createInstance<LidContext>(_ctx, getState());
  enterRule(_localctx, 210, GraphDBParser::RuleLid);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(986);
    match(GraphDBParser::NAME_STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FilenameContext ------------------------------------------------------------------

GraphDBParser::FilenameContext::FilenameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::FilenameContext::TEXT() {
  return getToken(GraphDBParser::TEXT, 0);
}


size_t GraphDBParser::FilenameContext::getRuleIndex() const {
  return GraphDBParser::RuleFilename;
}

void GraphDBParser::FilenameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFilename(this);
}

void GraphDBParser::FilenameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFilename(this);
}


antlrcpp::Any GraphDBParser::FilenameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitFilename(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::FilenameContext* GraphDBParser::filename() {
  FilenameContext *_localctx = _tracker.createInstance<FilenameContext>(_ctx, getState());
  enterRule(_localctx, 212, GraphDBParser::RuleFilename);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(988);
    match(GraphDBParser::TEXT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SchemaidContext ------------------------------------------------------------------

GraphDBParser::SchemaidContext::SchemaidContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::SchemaidContext::NAME_STRING() {
  return getToken(GraphDBParser::NAME_STRING, 0);
}


size_t GraphDBParser::SchemaidContext::getRuleIndex() const {
  return GraphDBParser::RuleSchemaid;
}

void GraphDBParser::SchemaidContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSchemaid(this);
}

void GraphDBParser::SchemaidContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSchemaid(this);
}


antlrcpp::Any GraphDBParser::SchemaidContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitSchemaid(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::SchemaidContext* GraphDBParser::schemaid() {
  SchemaidContext *_localctx = _tracker.createInstance<SchemaidContext>(_ctx, getState());
  enterRule(_localctx, 214, GraphDBParser::RuleSchemaid);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(990);
    match(GraphDBParser::NAME_STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableNameContext ------------------------------------------------------------------

GraphDBParser::VariableNameContext::VariableNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::VariableNameContext::NAME_STRING() {
  return getToken(GraphDBParser::NAME_STRING, 0);
}


size_t GraphDBParser::VariableNameContext::getRuleIndex() const {
  return GraphDBParser::RuleVariableName;
}

void GraphDBParser::VariableNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableName(this);
}

void GraphDBParser::VariableNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableName(this);
}


antlrcpp::Any GraphDBParser::VariableNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitVariableName(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::VariableNameContext* GraphDBParser::variableName() {
  VariableNameContext *_localctx = _tracker.createInstance<VariableNameContext>(_ctx, getState());
  enterRule(_localctx, 216, GraphDBParser::RuleVariableName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(992);
    match(GraphDBParser::NAME_STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IndexIntContext ------------------------------------------------------------------

GraphDBParser::IndexIntContext::IndexIntContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::IndexIntContext::INTEGER_NUMBER() {
  return getToken(GraphDBParser::INTEGER_NUMBER, 0);
}


size_t GraphDBParser::IndexIntContext::getRuleIndex() const {
  return GraphDBParser::RuleIndexInt;
}

void GraphDBParser::IndexIntContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIndexInt(this);
}

void GraphDBParser::IndexIntContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIndexInt(this);
}


antlrcpp::Any GraphDBParser::IndexIntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitIndexInt(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::IndexIntContext* GraphDBParser::indexInt() {
  IndexIntContext *_localctx = _tracker.createInstance<IndexIntContext>(_ctx, getState());
  enterRule(_localctx, 218, GraphDBParser::RuleIndexInt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(994);
    match(GraphDBParser::INTEGER_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParaItemContext ------------------------------------------------------------------

GraphDBParser::ParaItemContext::ParaItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GraphDBParser::ParaItemContext::INTEGER_NUMBER() {
  return getToken(GraphDBParser::INTEGER_NUMBER, 0);
}

tree::TerminalNode* GraphDBParser::ParaItemContext::NOT_INTEGER_NUMBER() {
  return getToken(GraphDBParser::NOT_INTEGER_NUMBER, 0);
}

tree::TerminalNode* GraphDBParser::ParaItemContext::TEXT() {
  return getToken(GraphDBParser::TEXT, 0);
}

tree::TerminalNode* GraphDBParser::ParaItemContext::NAME_STRING() {
  return getToken(GraphDBParser::NAME_STRING, 0);
}


size_t GraphDBParser::ParaItemContext::getRuleIndex() const {
  return GraphDBParser::RuleParaItem;
}

void GraphDBParser::ParaItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParaItem(this);
}

void GraphDBParser::ParaItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GraphDBListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParaItem(this);
}


antlrcpp::Any GraphDBParser::ParaItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GraphDBVisitor*>(visitor))
    return parserVisitor->visitParaItem(this);
  else
    return visitor->visitChildren(this);
}

GraphDBParser::ParaItemContext* GraphDBParser::paraItem() {
  ParaItemContext *_localctx = _tracker.createInstance<ParaItemContext>(_ctx, getState());
  enterRule(_localctx, 220, GraphDBParser::RuleParaItem);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(996);
    _la = _input->LA(1);
    if (!(((((_la - 81) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 81)) & ((1ULL << (GraphDBParser::INTEGER_NUMBER - 81))
      | (1ULL << (GraphDBParser::NOT_INTEGER_NUMBER - 81))
      | (1ULL << (GraphDBParser::NAME_STRING - 81))
      | (1ULL << (GraphDBParser::TEXT - 81)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool GraphDBParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 27: return queryStatSempred(dynamic_cast<QueryStatContext *>(context), predicateIndex);
    case 60: return firstOrderStatSempred(dynamic_cast<FirstOrderStatContext *>(context), predicateIndex);
    case 64: return compareStatSempred(dynamic_cast<CompareStatContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool GraphDBParser::queryStatSempred(QueryStatContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

bool GraphDBParser::firstOrderStatSempred(FirstOrderStatContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

bool GraphDBParser::compareStatSempred(CompareStatContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> GraphDBParser::_decisionToDFA;
atn::PredictionContextCache GraphDBParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN GraphDBParser::_atn;
std::vector<uint16_t> GraphDBParser::_serializedATN;

std::vector<std::string> GraphDBParser::_ruleNames = {
  "statement", "dmlStatement", "insertStat", "removeStat", "insertGsetStat", 
  "insertGStat", "graphNameItem", "graphNameList", "removeGsetStat", "removeGStat", 
  "updateStat", "nameGraph", "graph", "graphItem", "graphList", "graphset", 
  "vertexInfo", "edgeInfo", "edgeList", "edge", "attributeInfo", "nodeAttributeInfo", 
  "nodeAttributeList", "nodeAttributeItem", "edgeAttributeInfo", "edgeAttributeList", 
  "edgeAttributeItem", "queryStat", "multipleOperator", "projectCondition", 
  "fromCondition", "alignConditionList", "alignCondition", "filenamelist", 
  "whereCondition", "mapCondition", "reduceWord", "maximalWord", "operationStatement", 
  "operatorGSet", "schemaNameItem", "schemaNameList", "productStatement", 
  "joinStatement", "value", "entId", "vidList", "gidList", "lidList", "vidTuple", 
  "vidTupleList", "attrEqItem", "attrEqItemList", "attributeNameList", "attrEqItemUncertain", 
  "attrEqItemListUncertain", "compareOperator", "calculateOperator", "logicFlagBi", 
  "logicFlagNot", "firstOrderStat", "firstOrderUnit", "existStat", "foreachStat", 
  "compareStat", "compareUnit", "compareValStat", "funcStat", "funcName", 
  "object", "objectList", "varList", "bracketLeft", "bracketRight", "ddlStatement", 
  "createSchemaStat", "schemaStatement", "schemaNodeList", "schemaEdgeList", 
  "schemaNode", "schemaAttrList", "schemaEdge", "edgeLinkageList", "labelName", 
  "typeName", "schemaItem", "createGsetStat", "createGStat", "createGFileStat", 
  "createGForStat", "loadGsetStat", "loadGStat", "dropStat", "dropGsetStat", 
  "dropGStat", "dropSchemaStat", "schemaTypeList", "schemaAttributeItem", 
  "attrItem", "dataType", "attributeName", "gsid", "gid", "vid", "eid", 
  "lid", "filename", "schemaid", "variableName", "indexInt", "paraItem"
};

std::vector<std::string> GraphDBParser::_literalNames = {
  "", "';'", "'('", "')'", "','", "'='", "'{'", "'}'", "'['", "']'", "'<'", 
  "'>'", "'-'", "'*'", "'>='", "'<='", "'!='", "'+'", "'/'", "':'", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "'->'"
};

std::vector<std::string> GraphDBParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "SPACES", "K_where", "K_drop", "K_graphset", "K_graph", "K_schema", 
  "K_insert", "K_into", "K_as", "K_remove", "K_from", "K_update", "K_at", 
  "K_by", "K_set", "K_query", "K_difference", "K_proj", "K_for", "K_product", 
  "K_align", "K_to", "K_on", "K_reduce", "K_select", "K_map", "K_union", 
  "K_join", "K_intersect", "K_maximal", "K_vertex", "K_edge", "K_and", "K_or", 
  "K_arrow", "K_not", "K_exist", "K_foreach", "K_equal", "K_complete", "K_hasedge", 
  "K_graphequal", "K_unique", "K_sizegeq", "K_graphinset", "K_subgraph", 
  "K_inducedsub", "K_connect", "K_clique", "K_tdensesub", "K_create", "K_int", 
  "K_integer", "K_float", "K_double", "K_char", "K_string", "K_true", "K_false", 
  "K_file", "K_load", "INTEGER_NUMBER", "NOT_INTEGER_NUMBER", "NAME_STRING", 
  "LETTER", "SYMBOL", "CHAR", "TEXT"
};

dfa::Vocabulary GraphDBParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> GraphDBParser::_tokenNames;

GraphDBParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x59, 0x3e9, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 
    0x9, 0x22, 0x4, 0x23, 0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 
    0x25, 0x4, 0x26, 0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x4, 0x28, 0x9, 0x28, 
    0x4, 0x29, 0x9, 0x29, 0x4, 0x2a, 0x9, 0x2a, 0x4, 0x2b, 0x9, 0x2b, 0x4, 
    0x2c, 0x9, 0x2c, 0x4, 0x2d, 0x9, 0x2d, 0x4, 0x2e, 0x9, 0x2e, 0x4, 0x2f, 
    0x9, 0x2f, 0x4, 0x30, 0x9, 0x30, 0x4, 0x31, 0x9, 0x31, 0x4, 0x32, 0x9, 
    0x32, 0x4, 0x33, 0x9, 0x33, 0x4, 0x34, 0x9, 0x34, 0x4, 0x35, 0x9, 0x35, 
    0x4, 0x36, 0x9, 0x36, 0x4, 0x37, 0x9, 0x37, 0x4, 0x38, 0x9, 0x38, 0x4, 
    0x39, 0x9, 0x39, 0x4, 0x3a, 0x9, 0x3a, 0x4, 0x3b, 0x9, 0x3b, 0x4, 0x3c, 
    0x9, 0x3c, 0x4, 0x3d, 0x9, 0x3d, 0x4, 0x3e, 0x9, 0x3e, 0x4, 0x3f, 0x9, 
    0x3f, 0x4, 0x40, 0x9, 0x40, 0x4, 0x41, 0x9, 0x41, 0x4, 0x42, 0x9, 0x42, 
    0x4, 0x43, 0x9, 0x43, 0x4, 0x44, 0x9, 0x44, 0x4, 0x45, 0x9, 0x45, 0x4, 
    0x46, 0x9, 0x46, 0x4, 0x47, 0x9, 0x47, 0x4, 0x48, 0x9, 0x48, 0x4, 0x49, 
    0x9, 0x49, 0x4, 0x4a, 0x9, 0x4a, 0x4, 0x4b, 0x9, 0x4b, 0x4, 0x4c, 0x9, 
    0x4c, 0x4, 0x4d, 0x9, 0x4d, 0x4, 0x4e, 0x9, 0x4e, 0x4, 0x4f, 0x9, 0x4f, 
    0x4, 0x50, 0x9, 0x50, 0x4, 0x51, 0x9, 0x51, 0x4, 0x52, 0x9, 0x52, 0x4, 
    0x53, 0x9, 0x53, 0x4, 0x54, 0x9, 0x54, 0x4, 0x55, 0x9, 0x55, 0x4, 0x56, 
    0x9, 0x56, 0x4, 0x57, 0x9, 0x57, 0x4, 0x58, 0x9, 0x58, 0x4, 0x59, 0x9, 
    0x59, 0x4, 0x5a, 0x9, 0x5a, 0x4, 0x5b, 0x9, 0x5b, 0x4, 0x5c, 0x9, 0x5c, 
    0x4, 0x5d, 0x9, 0x5d, 0x4, 0x5e, 0x9, 0x5e, 0x4, 0x5f, 0x9, 0x5f, 0x4, 
    0x60, 0x9, 0x60, 0x4, 0x61, 0x9, 0x61, 0x4, 0x62, 0x9, 0x62, 0x4, 0x63, 
    0x9, 0x63, 0x4, 0x64, 0x9, 0x64, 0x4, 0x65, 0x9, 0x65, 0x4, 0x66, 0x9, 
    0x66, 0x4, 0x67, 0x9, 0x67, 0x4, 0x68, 0x9, 0x68, 0x4, 0x69, 0x9, 0x69, 
    0x4, 0x6a, 0x9, 0x6a, 0x4, 0x6b, 0x9, 0x6b, 0x4, 0x6c, 0x9, 0x6c, 0x4, 
    0x6d, 0x9, 0x6d, 0x4, 0x6e, 0x9, 0x6e, 0x4, 0x6f, 0x9, 0x6f, 0x4, 0x70, 
    0x9, 0x70, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 
    0x5, 0x2, 0xe7, 0xa, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 
    0x3, 0xed, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0xf1, 0xa, 0x4, 0x3, 
    0x5, 0x3, 0x5, 0x5, 0x5, 0xf5, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0x113, 0xa, 0x7, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x11a, 0xa, 0x8, 
    0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x121, 0xa, 
    0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x142, 0xa, 0xb, 0x3, 0xc, 
    0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 
    0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0x151, 0xa, 
    0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xe, 0x5, 0xe, 0x161, 0xa, 0xe, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0x165, 
    0xa, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 
    0x10, 0x16c, 0xa, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 
    0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 
    0x12, 0x178, 0xa, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0x180, 0xa, 0x13, 0x3, 0x14, 0x3, 0x14, 
    0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 
    0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 
    0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 
    0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 
    0x5, 0x14, 0x19e, 0xa, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x16, 0x3, 0x16, 
    0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 
    0x16, 0x3, 0x16, 0x5, 0x16, 0x1ac, 0xa, 0x16, 0x3, 0x17, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x5, 0x17, 0x1b4, 0xa, 0x17, 
    0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0x1bb, 
    0xa, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 
    0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x5, 0x19, 0x1c6, 0xa, 0x19, 
    0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x5, 
    0x1a, 0x1ce, 0xa, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 
    0x3, 0x1b, 0x5, 0x1b, 0x1d5, 0xa, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 
    0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 
    0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 
    0x3, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 0x1e9, 0xa, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 
    0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 
    0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 
    0x3, 0x1d, 0x5, 0x1d, 0x1fb, 0xa, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 
    0x3, 0x1d, 0x7, 0x1d, 0x201, 0xa, 0x1d, 0xc, 0x1d, 0xe, 0x1d, 0x204, 
    0xb, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 
    0x1f, 0x3, 0x1f, 0x5, 0x1f, 0x20d, 0xa, 0x1f, 0x3, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x5, 0x20, 0x213, 0xa, 0x20, 0x3, 0x21, 0x3, 0x21, 
    0x3, 0x21, 0x3, 0x21, 0x5, 0x21, 0x219, 0xa, 0x21, 0x3, 0x22, 0x3, 0x22, 
    0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 
    0x22, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x5, 0x23, 
    0x229, 0xa, 0x23, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 
    0x5, 0x24, 0x230, 0xa, 0x24, 0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 
    0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x5, 0x25, 0x23a, 0xa, 0x25, 
    0x3, 0x26, 0x3, 0x26, 0x5, 0x26, 0x23e, 0xa, 0x26, 0x3, 0x27, 0x3, 0x27, 
    0x5, 0x27, 0x242, 0xa, 0x27, 0x3, 0x28, 0x3, 0x28, 0x5, 0x28, 0x246, 
    0xa, 0x28, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 
    0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x5, 0x29, 0x252, 
    0xa, 0x29, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 
    0x2a, 0x3, 0x2a, 0x5, 0x2a, 0x25b, 0xa, 0x2a, 0x3, 0x2b, 0x3, 0x2b, 
    0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x5, 0x2b, 0x262, 0xa, 0x2b, 0x3, 0x2c, 
    0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 
    0x2d, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2f, 0x3, 0x2f, 0x5, 0x2f, 0x270, 
    0xa, 0x2f, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 
    0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 
    0x5, 0x30, 0x27e, 0xa, 0x30, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 
    0x3, 0x31, 0x5, 0x31, 0x285, 0xa, 0x31, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 
    0x3, 0x32, 0x3, 0x32, 0x5, 0x32, 0x28c, 0xa, 0x32, 0x3, 0x33, 0x3, 0x33, 
    0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x34, 0x3, 0x34, 0x3, 
    0x34, 0x3, 0x34, 0x3, 0x34, 0x5, 0x34, 0x299, 0xa, 0x34, 0x3, 0x35, 
    0x3, 0x35, 0x3, 0x35, 0x3, 0x35, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 
    0x36, 0x3, 0x36, 0x5, 0x36, 0x2a4, 0xa, 0x36, 0x3, 0x37, 0x3, 0x37, 
    0x3, 0x37, 0x3, 0x37, 0x3, 0x37, 0x5, 0x37, 0x2ab, 0xa, 0x37, 0x3, 0x38, 
    0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 
    0x39, 0x3, 0x39, 0x5, 0x39, 0x2b6, 0xa, 0x39, 0x3, 0x3a, 0x3, 0x3a, 
    0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x5, 0x3a, 0x2be, 0xa, 0x3a, 
    0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3d, 0x3, 0x3d, 0x3, 
    0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 
    0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x5, 0x3e, 0x2d1, 0xa, 0x3e, 
    0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x7, 0x3e, 0x2d7, 0xa, 0x3e, 
    0xc, 0x3e, 0xe, 0x3e, 0x2da, 0xb, 0x3e, 0x3, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 
    0x3, 0x3f, 0x5, 0x3f, 0x2e0, 0xa, 0x3f, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 
    0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 
    0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 0x42, 0x3, 0x42, 0x3, 0x42, 0x3, 0x42, 
    0x3, 0x42, 0x3, 0x42, 0x3, 0x42, 0x3, 0x42, 0x5, 0x42, 0x2f6, 0xa, 0x42, 
    0x3, 0x42, 0x3, 0x42, 0x3, 0x42, 0x3, 0x42, 0x7, 0x42, 0x2fc, 0xa, 0x42, 
    0xc, 0x42, 0xe, 0x42, 0x2ff, 0xb, 0x42, 0x3, 0x43, 0x3, 0x43, 0x5, 0x43, 
    0x303, 0xa, 0x43, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 0x3, 0x45, 
    0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 
    0x45, 0x3, 0x45, 0x5, 0x45, 0x312, 0xa, 0x45, 0x3, 0x46, 0x3, 0x46, 
    0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x5, 
    0x47, 0x31c, 0xa, 0x47, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 
    0x3, 0x48, 0x5, 0x48, 0x323, 0xa, 0x48, 0x3, 0x49, 0x3, 0x49, 0x3, 0x49, 
    0x3, 0x49, 0x3, 0x49, 0x5, 0x49, 0x32a, 0xa, 0x49, 0x3, 0x4a, 0x3, 0x4a, 
    0x3, 0x4b, 0x3, 0x4b, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 
    0x4c, 0x3, 0x4c, 0x5, 0x4c, 0x336, 0xa, 0x4c, 0x3, 0x4d, 0x3, 0x4d, 
    0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x3, 
    0x4d, 0x5, 0x4d, 0x341, 0xa, 0x4d, 0x3, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 
    0x3, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x3, 
    0x4f, 0x3, 0x4f, 0x5, 0x4f, 0x34e, 0xa, 0x4f, 0x3, 0x50, 0x3, 0x50, 
    0x3, 0x50, 0x3, 0x50, 0x3, 0x50, 0x5, 0x50, 0x355, 0xa, 0x50, 0x3, 0x51, 
    0x3, 0x51, 0x3, 0x51, 0x3, 0x51, 0x3, 0x51, 0x3, 0x52, 0x3, 0x52, 0x3, 
    0x52, 0x3, 0x52, 0x3, 0x52, 0x3, 0x52, 0x3, 0x52, 0x3, 0x52, 0x5, 0x52, 
    0x364, 0xa, 0x52, 0x3, 0x53, 0x3, 0x53, 0x3, 0x53, 0x3, 0x53, 0x3, 0x53, 
    0x3, 0x53, 0x3, 0x53, 0x3, 0x53, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 
    0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 
    0x5, 0x54, 0x378, 0xa, 0x54, 0x3, 0x55, 0x3, 0x55, 0x3, 0x56, 0x3, 0x56, 
    0x3, 0x57, 0x3, 0x57, 0x3, 0x57, 0x3, 0x57, 0x3, 0x57, 0x5, 0x57, 0x383, 
    0xa, 0x57, 0x3, 0x58, 0x3, 0x58, 0x3, 0x58, 0x3, 0x58, 0x3, 0x58, 0x3, 
    0x58, 0x3, 0x58, 0x3, 0x58, 0x3, 0x59, 0x3, 0x59, 0x3, 0x59, 0x3, 0x59, 
    0x3, 0x59, 0x3, 0x59, 0x3, 0x59, 0x3, 0x5a, 0x3, 0x5a, 0x3, 0x5a, 0x3, 
    0x5a, 0x5, 0x5a, 0x398, 0xa, 0x5a, 0x3, 0x5b, 0x3, 0x5b, 0x3, 0x5b, 
    0x5, 0x5b, 0x39d, 0xa, 0x5b, 0x3, 0x5c, 0x3, 0x5c, 0x3, 0x5c, 0x3, 0x5c, 
    0x3, 0x5d, 0x3, 0x5d, 0x3, 0x5d, 0x3, 0x5d, 0x3, 0x5e, 0x3, 0x5e, 0x3, 
    0x5e, 0x5, 0x5e, 0x3aa, 0xa, 0x5e, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f, 
    0x3, 0x5f, 0x3, 0x60, 0x3, 0x60, 0x3, 0x60, 0x3, 0x60, 0x3, 0x61, 0x3, 
    0x61, 0x3, 0x61, 0x3, 0x61, 0x3, 0x62, 0x3, 0x62, 0x3, 0x62, 0x3, 0x62, 
    0x3, 0x62, 0x3, 0x62, 0x3, 0x62, 0x3, 0x62, 0x3, 0x62, 0x3, 0x62, 0x3, 
    0x62, 0x3, 0x62, 0x5, 0x62, 0x3c4, 0xa, 0x62, 0x3, 0x63, 0x3, 0x63, 
    0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x5, 0x63, 0x3cb, 0xa, 0x63, 0x3, 0x64, 
    0x3, 0x64, 0x3, 0x64, 0x3, 0x64, 0x3, 0x65, 0x3, 0x65, 0x3, 0x66, 0x3, 
    0x66, 0x3, 0x67, 0x3, 0x67, 0x3, 0x68, 0x3, 0x68, 0x3, 0x69, 0x3, 0x69, 
    0x3, 0x6a, 0x3, 0x6a, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6c, 0x3, 0x6c, 0x3, 
    0x6d, 0x3, 0x6d, 0x3, 0x6e, 0x3, 0x6e, 0x3, 0x6f, 0x3, 0x6f, 0x3, 0x70, 
    0x3, 0x70, 0x3, 0x70, 0x2, 0x5, 0x38, 0x7a, 0x82, 0x71, 0x2, 0x4, 0x6, 
    0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 
    0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 
    0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e, 
    0x50, 0x52, 0x54, 0x56, 0x58, 0x5a, 0x5c, 0x5e, 0x60, 0x62, 0x64, 0x66, 
    0x68, 0x6a, 0x6c, 0x6e, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7a, 0x7c, 0x7e, 
    0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90, 0x92, 0x94, 0x96, 
    0x98, 0x9a, 0x9c, 0x9e, 0xa0, 0xa2, 0xa4, 0xa6, 0xa8, 0xaa, 0xac, 0xae, 
    0xb0, 0xb2, 0xb4, 0xb6, 0xb8, 0xba, 0xbc, 0xbe, 0xc0, 0xc2, 0xc4, 0xc6, 
    0xc8, 0xca, 0xcc, 0xce, 0xd0, 0xd2, 0xd4, 0xd6, 0xd8, 0xda, 0xdc, 0xde, 
    0x2, 0x9, 0x5, 0x2, 0xe, 0xe, 0x30, 0x30, 0x32, 0x32, 0x4, 0x2, 0x53, 
    0x54, 0x59, 0x59, 0x4, 0x2, 0xe, 0xf, 0x13, 0x14, 0x3, 0x2, 0x36, 0x38, 
    0x4, 0x2, 0x34, 0x35, 0x3c, 0x47, 0x3, 0x2, 0x49, 0x4e, 0x4, 0x2, 0x53, 
    0x55, 0x59, 0x59, 0x2, 0x3d8, 0x2, 0xe6, 0x3, 0x2, 0x2, 0x2, 0x4, 0xec, 
    0x3, 0x2, 0x2, 0x2, 0x6, 0xf0, 0x3, 0x2, 0x2, 0x2, 0x8, 0xf4, 0x3, 0x2, 
    0x2, 0x2, 0xa, 0xf6, 0x3, 0x2, 0x2, 0x2, 0xc, 0x112, 0x3, 0x2, 0x2, 
    0x2, 0xe, 0x119, 0x3, 0x2, 0x2, 0x2, 0x10, 0x120, 0x3, 0x2, 0x2, 0x2, 
    0x12, 0x122, 0x3, 0x2, 0x2, 0x2, 0x14, 0x141, 0x3, 0x2, 0x2, 0x2, 0x16, 
    0x143, 0x3, 0x2, 0x2, 0x2, 0x18, 0x150, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x160, 
    0x3, 0x2, 0x2, 0x2, 0x1c, 0x164, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x16b, 0x3, 
    0x2, 0x2, 0x2, 0x20, 0x16d, 0x3, 0x2, 0x2, 0x2, 0x22, 0x177, 0x3, 0x2, 
    0x2, 0x2, 0x24, 0x17f, 0x3, 0x2, 0x2, 0x2, 0x26, 0x19d, 0x3, 0x2, 0x2, 
    0x2, 0x28, 0x19f, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x1ab, 0x3, 0x2, 0x2, 0x2, 
    0x2c, 0x1b3, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x1ba, 0x3, 0x2, 0x2, 0x2, 0x30, 
    0x1c5, 0x3, 0x2, 0x2, 0x2, 0x32, 0x1cd, 0x3, 0x2, 0x2, 0x2, 0x34, 0x1d4, 
    0x3, 0x2, 0x2, 0x2, 0x36, 0x1e8, 0x3, 0x2, 0x2, 0x2, 0x38, 0x1fa, 0x3, 
    0x2, 0x2, 0x2, 0x3a, 0x205, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x20c, 0x3, 0x2, 
    0x2, 0x2, 0x3e, 0x212, 0x3, 0x2, 0x2, 0x2, 0x40, 0x218, 0x3, 0x2, 0x2, 
    0x2, 0x42, 0x21a, 0x3, 0x2, 0x2, 0x2, 0x44, 0x228, 0x3, 0x2, 0x2, 0x2, 
    0x46, 0x22f, 0x3, 0x2, 0x2, 0x2, 0x48, 0x239, 0x3, 0x2, 0x2, 0x2, 0x4a, 
    0x23d, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x241, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x245, 
    0x3, 0x2, 0x2, 0x2, 0x50, 0x251, 0x3, 0x2, 0x2, 0x2, 0x52, 0x25a, 0x3, 
    0x2, 0x2, 0x2, 0x54, 0x261, 0x3, 0x2, 0x2, 0x2, 0x56, 0x263, 0x3, 0x2, 
    0x2, 0x2, 0x58, 0x267, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x26b, 0x3, 0x2, 0x2, 
    0x2, 0x5c, 0x26f, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x27d, 0x3, 0x2, 0x2, 0x2, 
    0x60, 0x284, 0x3, 0x2, 0x2, 0x2, 0x62, 0x28b, 0x3, 0x2, 0x2, 0x2, 0x64, 
    0x28d, 0x3, 0x2, 0x2, 0x2, 0x66, 0x298, 0x3, 0x2, 0x2, 0x2, 0x68, 0x29a, 
    0x3, 0x2, 0x2, 0x2, 0x6a, 0x2a3, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x2aa, 0x3, 
    0x2, 0x2, 0x2, 0x6e, 0x2ac, 0x3, 0x2, 0x2, 0x2, 0x70, 0x2b5, 0x3, 0x2, 
    0x2, 0x2, 0x72, 0x2bd, 0x3, 0x2, 0x2, 0x2, 0x74, 0x2bf, 0x3, 0x2, 0x2, 
    0x2, 0x76, 0x2c1, 0x3, 0x2, 0x2, 0x2, 0x78, 0x2c3, 0x3, 0x2, 0x2, 0x2, 
    0x7a, 0x2d0, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x2df, 0x3, 0x2, 0x2, 0x2, 0x7e, 
    0x2e1, 0x3, 0x2, 0x2, 0x2, 0x80, 0x2e7, 0x3, 0x2, 0x2, 0x2, 0x82, 0x2f5, 
    0x3, 0x2, 0x2, 0x2, 0x84, 0x302, 0x3, 0x2, 0x2, 0x2, 0x86, 0x304, 0x3, 
    0x2, 0x2, 0x2, 0x88, 0x311, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x313, 0x3, 0x2, 
    0x2, 0x2, 0x8c, 0x31b, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x322, 0x3, 0x2, 0x2, 
    0x2, 0x90, 0x329, 0x3, 0x2, 0x2, 0x2, 0x92, 0x32b, 0x3, 0x2, 0x2, 0x2, 
    0x94, 0x32d, 0x3, 0x2, 0x2, 0x2, 0x96, 0x335, 0x3, 0x2, 0x2, 0x2, 0x98, 
    0x340, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x342, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x34d, 
    0x3, 0x2, 0x2, 0x2, 0x9e, 0x354, 0x3, 0x2, 0x2, 0x2, 0xa0, 0x356, 0x3, 
    0x2, 0x2, 0x2, 0xa2, 0x363, 0x3, 0x2, 0x2, 0x2, 0xa4, 0x365, 0x3, 0x2, 
    0x2, 0x2, 0xa6, 0x377, 0x3, 0x2, 0x2, 0x2, 0xa8, 0x379, 0x3, 0x2, 0x2, 
    0x2, 0xaa, 0x37b, 0x3, 0x2, 0x2, 0x2, 0xac, 0x382, 0x3, 0x2, 0x2, 0x2, 
    0xae, 0x384, 0x3, 0x2, 0x2, 0x2, 0xb0, 0x38c, 0x3, 0x2, 0x2, 0x2, 0xb2, 
    0x397, 0x3, 0x2, 0x2, 0x2, 0xb4, 0x39c, 0x3, 0x2, 0x2, 0x2, 0xb6, 0x39e, 
    0x3, 0x2, 0x2, 0x2, 0xb8, 0x3a2, 0x3, 0x2, 0x2, 0x2, 0xba, 0x3a9, 0x3, 
    0x2, 0x2, 0x2, 0xbc, 0x3ab, 0x3, 0x2, 0x2, 0x2, 0xbe, 0x3af, 0x3, 0x2, 
    0x2, 0x2, 0xc0, 0x3b3, 0x3, 0x2, 0x2, 0x2, 0xc2, 0x3c3, 0x3, 0x2, 0x2, 
    0x2, 0xc4, 0x3ca, 0x3, 0x2, 0x2, 0x2, 0xc6, 0x3cc, 0x3, 0x2, 0x2, 0x2, 
    0xc8, 0x3d0, 0x3, 0x2, 0x2, 0x2, 0xca, 0x3d2, 0x3, 0x2, 0x2, 0x2, 0xcc, 
    0x3d4, 0x3, 0x2, 0x2, 0x2, 0xce, 0x3d6, 0x3, 0x2, 0x2, 0x2, 0xd0, 0x3d8, 
    0x3, 0x2, 0x2, 0x2, 0xd2, 0x3da, 0x3, 0x2, 0x2, 0x2, 0xd4, 0x3dc, 0x3, 
    0x2, 0x2, 0x2, 0xd6, 0x3de, 0x3, 0x2, 0x2, 0x2, 0xd8, 0x3e0, 0x3, 0x2, 
    0x2, 0x2, 0xda, 0x3e2, 0x3, 0x2, 0x2, 0x2, 0xdc, 0x3e4, 0x3, 0x2, 0x2, 
    0x2, 0xde, 0x3e6, 0x3, 0x2, 0x2, 0x2, 0xe0, 0xe1, 0x5, 0x4, 0x3, 0x2, 
    0xe1, 0xe2, 0x7, 0x3, 0x2, 0x2, 0xe2, 0xe7, 0x3, 0x2, 0x2, 0x2, 0xe3, 
    0xe4, 0x5, 0x96, 0x4c, 0x2, 0xe4, 0xe5, 0x7, 0x3, 0x2, 0x2, 0xe5, 0xe7, 
    0x3, 0x2, 0x2, 0x2, 0xe6, 0xe0, 0x3, 0x2, 0x2, 0x2, 0xe6, 0xe3, 0x3, 
    0x2, 0x2, 0x2, 0xe7, 0x3, 0x3, 0x2, 0x2, 0x2, 0xe8, 0xed, 0x5, 0x6, 
    0x4, 0x2, 0xe9, 0xed, 0x5, 0x8, 0x5, 0x2, 0xea, 0xed, 0x5, 0x16, 0xc, 
    0x2, 0xeb, 0xed, 0x5, 0x38, 0x1d, 0x2, 0xec, 0xe8, 0x3, 0x2, 0x2, 0x2, 
    0xec, 0xe9, 0x3, 0x2, 0x2, 0x2, 0xec, 0xea, 0x3, 0x2, 0x2, 0x2, 0xec, 
    0xeb, 0x3, 0x2, 0x2, 0x2, 0xed, 0x5, 0x3, 0x2, 0x2, 0x2, 0xee, 0xf1, 
    0x5, 0xa, 0x6, 0x2, 0xef, 0xf1, 0x5, 0xc, 0x7, 0x2, 0xf0, 0xee, 0x3, 
    0x2, 0x2, 0x2, 0xf0, 0xef, 0x3, 0x2, 0x2, 0x2, 0xf1, 0x7, 0x3, 0x2, 
    0x2, 0x2, 0xf2, 0xf5, 0x5, 0x12, 0xa, 0x2, 0xf3, 0xf5, 0x5, 0x14, 0xb, 
    0x2, 0xf4, 0xf2, 0x3, 0x2, 0x2, 0x2, 0xf4, 0xf3, 0x3, 0x2, 0x2, 0x2, 
    0xf5, 0x9, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xf7, 0x7, 0x1c, 0x2, 0x2, 0xf7, 
    0xf8, 0x7, 0x1d, 0x2, 0x2, 0xf8, 0xf9, 0x7, 0x19, 0x2, 0x2, 0xf9, 0xfa, 
    0x5, 0xcc, 0x67, 0x2, 0xfa, 0xfb, 0x7, 0x4, 0x2, 0x2, 0xfb, 0xfc, 0x5, 
    0x60, 0x31, 0x2, 0xfc, 0xfd, 0x7, 0x5, 0x2, 0x2, 0xfd, 0xb, 0x3, 0x2, 
    0x2, 0x2, 0xfe, 0xff, 0x7, 0x1c, 0x2, 0x2, 0xff, 0x100, 0x5, 0x1a, 0xe, 
    0x2, 0x100, 0x101, 0x7, 0x1d, 0x2, 0x2, 0x101, 0x102, 0x7, 0x1a, 0x2, 
    0x2, 0x102, 0x103, 0x5, 0xce, 0x68, 0x2, 0x103, 0x113, 0x3, 0x2, 0x2, 
    0x2, 0x104, 0x105, 0x7, 0x1c, 0x2, 0x2, 0x105, 0x106, 0x7, 0x51, 0x2, 
    0x2, 0x106, 0x107, 0x5, 0x44, 0x23, 0x2, 0x107, 0x108, 0x7, 0x1d, 0x2, 
    0x2, 0x108, 0x109, 0x7, 0x1a, 0x2, 0x2, 0x109, 0x10a, 0x5, 0xce, 0x68, 
    0x2, 0x10a, 0x113, 0x3, 0x2, 0x2, 0x2, 0x10b, 0x10c, 0x7, 0x1c, 0x2, 
    0x2, 0x10c, 0x10d, 0x7, 0x1a, 0x2, 0x2, 0x10d, 0x10e, 0x5, 0xce, 0x68, 
    0x2, 0x10e, 0x10f, 0x7, 0x1d, 0x2, 0x2, 0x10f, 0x110, 0x7, 0x1a, 0x2, 
    0x2, 0x110, 0x111, 0x5, 0xce, 0x68, 0x2, 0x111, 0x113, 0x3, 0x2, 0x2, 
    0x2, 0x112, 0xfe, 0x3, 0x2, 0x2, 0x2, 0x112, 0x104, 0x3, 0x2, 0x2, 0x2, 
    0x112, 0x10b, 0x3, 0x2, 0x2, 0x2, 0x113, 0xd, 0x3, 0x2, 0x2, 0x2, 0x114, 
    0x115, 0x5, 0x1a, 0xe, 0x2, 0x115, 0x116, 0x7, 0x1e, 0x2, 0x2, 0x116, 
    0x117, 0x5, 0xce, 0x68, 0x2, 0x117, 0x11a, 0x3, 0x2, 0x2, 0x2, 0x118, 
    0x11a, 0x5, 0xce, 0x68, 0x2, 0x119, 0x114, 0x3, 0x2, 0x2, 0x2, 0x119, 
    0x118, 0x3, 0x2, 0x2, 0x2, 0x11a, 0xf, 0x3, 0x2, 0x2, 0x2, 0x11b, 0x121, 
    0x5, 0xe, 0x8, 0x2, 0x11c, 0x11d, 0x5, 0xe, 0x8, 0x2, 0x11d, 0x11e, 
    0x7, 0x6, 0x2, 0x2, 0x11e, 0x11f, 0x5, 0x10, 0x9, 0x2, 0x11f, 0x121, 
    0x3, 0x2, 0x2, 0x2, 0x120, 0x11b, 0x3, 0x2, 0x2, 0x2, 0x120, 0x11c, 
    0x3, 0x2, 0x2, 0x2, 0x121, 0x11, 0x3, 0x2, 0x2, 0x2, 0x122, 0x123, 0x7, 
    0x1f, 0x2, 0x2, 0x123, 0x124, 0x7, 0x20, 0x2, 0x2, 0x124, 0x125, 0x7, 
    0x19, 0x2, 0x2, 0x125, 0x126, 0x5, 0xcc, 0x67, 0x2, 0x126, 0x127, 0x7, 
    0x4, 0x2, 0x2, 0x127, 0x128, 0x5, 0x60, 0x31, 0x2, 0x128, 0x129, 0x7, 
    0x5, 0x2, 0x2, 0x129, 0x13, 0x3, 0x2, 0x2, 0x2, 0x12a, 0x12b, 0x7, 0x1f, 
    0x2, 0x2, 0x12b, 0x12c, 0x7, 0x4, 0x2, 0x2, 0x12c, 0x12d, 0x5, 0x22, 
    0x12, 0x2, 0x12d, 0x12e, 0x7, 0x6, 0x2, 0x2, 0x12e, 0x12f, 0x5, 0x24, 
    0x13, 0x2, 0x12f, 0x130, 0x7, 0x5, 0x2, 0x2, 0x130, 0x131, 0x7, 0x20, 
    0x2, 0x2, 0x131, 0x132, 0x7, 0x1a, 0x2, 0x2, 0x132, 0x133, 0x5, 0xce, 
    0x68, 0x2, 0x133, 0x142, 0x3, 0x2, 0x2, 0x2, 0x134, 0x135, 0x7, 0x1f, 
    0x2, 0x2, 0x135, 0x136, 0x7, 0x51, 0x2, 0x2, 0x136, 0x137, 0x5, 0x44, 
    0x23, 0x2, 0x137, 0x138, 0x7, 0x20, 0x2, 0x2, 0x138, 0x139, 0x7, 0x1a, 
    0x2, 0x2, 0x139, 0x13a, 0x5, 0xce, 0x68, 0x2, 0x13a, 0x142, 0x3, 0x2, 
    0x2, 0x2, 0x13b, 0x13c, 0x7, 0x1f, 0x2, 0x2, 0x13c, 0x13d, 0x5, 0xce, 
    0x68, 0x2, 0x13d, 0x13e, 0x7, 0x20, 0x2, 0x2, 0x13e, 0x13f, 0x7, 0x1a, 
    0x2, 0x2, 0x13f, 0x140, 0x5, 0xce, 0x68, 0x2, 0x140, 0x142, 0x3, 0x2, 
    0x2, 0x2, 0x141, 0x12a, 0x3, 0x2, 0x2, 0x2, 0x141, 0x134, 0x3, 0x2, 
    0x2, 0x2, 0x141, 0x13b, 0x3, 0x2, 0x2, 0x2, 0x142, 0x15, 0x3, 0x2, 0x2, 
    0x2, 0x143, 0x144, 0x7, 0x21, 0x2, 0x2, 0x144, 0x145, 0x5, 0xcc, 0x67, 
    0x2, 0x145, 0x146, 0x7, 0x22, 0x2, 0x2, 0x146, 0x147, 0x5, 0xce, 0x68, 
    0x2, 0x147, 0x148, 0x7, 0x23, 0x2, 0x2, 0x148, 0x149, 0x7, 0x24, 0x2, 
    0x2, 0x149, 0x14a, 0x5, 0xca, 0x66, 0x2, 0x14a, 0x14b, 0x7, 0x7, 0x2, 
    0x2, 0x14b, 0x14c, 0x5, 0x5a, 0x2e, 0x2, 0x14c, 0x17, 0x3, 0x2, 0x2, 
    0x2, 0x14d, 0x14e, 0x7, 0x1e, 0x2, 0x2, 0x14e, 0x151, 0x5, 0xcc, 0x67, 
    0x2, 0x14f, 0x151, 0x3, 0x2, 0x2, 0x2, 0x150, 0x14d, 0x3, 0x2, 0x2, 
    0x2, 0x150, 0x14f, 0x3, 0x2, 0x2, 0x2, 0x151, 0x19, 0x3, 0x2, 0x2, 0x2, 
    0x152, 0x153, 0x7, 0x4, 0x2, 0x2, 0x153, 0x154, 0x5, 0x22, 0x12, 0x2, 
    0x154, 0x155, 0x7, 0x6, 0x2, 0x2, 0x155, 0x156, 0x5, 0x24, 0x13, 0x2, 
    0x156, 0x157, 0x7, 0x6, 0x2, 0x2, 0x157, 0x158, 0x5, 0x2a, 0x16, 0x2, 
    0x158, 0x159, 0x7, 0x5, 0x2, 0x2, 0x159, 0x161, 0x3, 0x2, 0x2, 0x2, 
    0x15a, 0x15b, 0x7, 0x4, 0x2, 0x2, 0x15b, 0x15c, 0x5, 0x22, 0x12, 0x2, 
    0x15c, 0x15d, 0x7, 0x6, 0x2, 0x2, 0x15d, 0x15e, 0x5, 0x24, 0x13, 0x2, 
    0x15e, 0x15f, 0x7, 0x5, 0x2, 0x2, 0x15f, 0x161, 0x3, 0x2, 0x2, 0x2, 
    0x160, 0x152, 0x3, 0x2, 0x2, 0x2, 0x160, 0x15a, 0x3, 0x2, 0x2, 0x2, 
    0x161, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x162, 0x165, 0x5, 0x1a, 0xe, 0x2, 
    0x163, 0x165, 0x5, 0xce, 0x68, 0x2, 0x164, 0x162, 0x3, 0x2, 0x2, 0x2, 
    0x164, 0x163, 0x3, 0x2, 0x2, 0x2, 0x165, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x166, 
    0x16c, 0x5, 0x1c, 0xf, 0x2, 0x167, 0x168, 0x5, 0x1c, 0xf, 0x2, 0x168, 
    0x169, 0x7, 0x6, 0x2, 0x2, 0x169, 0x16a, 0x5, 0x1e, 0x10, 0x2, 0x16a, 
    0x16c, 0x3, 0x2, 0x2, 0x2, 0x16b, 0x166, 0x3, 0x2, 0x2, 0x2, 0x16b, 
    0x167, 0x3, 0x2, 0x2, 0x2, 0x16c, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x16d, 0x16e, 
    0x7, 0x8, 0x2, 0x2, 0x16e, 0x16f, 0x5, 0x1e, 0x10, 0x2, 0x16f, 0x170, 
    0x7, 0x9, 0x2, 0x2, 0x170, 0x21, 0x3, 0x2, 0x2, 0x2, 0x171, 0x172, 0x7, 
    0x8, 0x2, 0x2, 0x172, 0x178, 0x7, 0x9, 0x2, 0x2, 0x173, 0x174, 0x7, 
    0x8, 0x2, 0x2, 0x174, 0x175, 0x5, 0x5e, 0x30, 0x2, 0x175, 0x176, 0x7, 
    0x9, 0x2, 0x2, 0x176, 0x178, 0x3, 0x2, 0x2, 0x2, 0x177, 0x171, 0x3, 
    0x2, 0x2, 0x2, 0x177, 0x173, 0x3, 0x2, 0x2, 0x2, 0x178, 0x23, 0x3, 0x2, 
    0x2, 0x2, 0x179, 0x17a, 0x7, 0x8, 0x2, 0x2, 0x17a, 0x180, 0x7, 0x9, 
    0x2, 0x2, 0x17b, 0x17c, 0x7, 0x8, 0x2, 0x2, 0x17c, 0x17d, 0x5, 0x26, 
    0x14, 0x2, 0x17d, 0x17e, 0x7, 0x9, 0x2, 0x2, 0x17e, 0x180, 0x3, 0x2, 
    0x2, 0x2, 0x17f, 0x179, 0x3, 0x2, 0x2, 0x2, 0x17f, 0x17b, 0x3, 0x2, 
    0x2, 0x2, 0x180, 0x25, 0x3, 0x2, 0x2, 0x2, 0x181, 0x182, 0x5, 0x28, 
    0x15, 0x2, 0x182, 0x183, 0x7, 0xa, 0x2, 0x2, 0x183, 0x184, 0x5, 0xd4, 
    0x6b, 0x2, 0x184, 0x185, 0x7, 0xb, 0x2, 0x2, 0x185, 0x19e, 0x3, 0x2, 
    0x2, 0x2, 0x186, 0x187, 0x5, 0xd2, 0x6a, 0x2, 0x187, 0x188, 0x7, 0x7, 
    0x2, 0x2, 0x188, 0x189, 0x5, 0x28, 0x15, 0x2, 0x189, 0x18a, 0x7, 0xa, 
    0x2, 0x2, 0x18a, 0x18b, 0x5, 0xd4, 0x6b, 0x2, 0x18b, 0x18c, 0x7, 0xb, 
    0x2, 0x2, 0x18c, 0x19e, 0x3, 0x2, 0x2, 0x2, 0x18d, 0x18e, 0x5, 0x28, 
    0x15, 0x2, 0x18e, 0x18f, 0x7, 0xa, 0x2, 0x2, 0x18f, 0x190, 0x5, 0xd4, 
    0x6b, 0x2, 0x190, 0x191, 0x7, 0xb, 0x2, 0x2, 0x191, 0x192, 0x7, 0x6, 
    0x2, 0x2, 0x192, 0x193, 0x5, 0x26, 0x14, 0x2, 0x193, 0x19e, 0x3, 0x2, 
    0x2, 0x2, 0x194, 0x195, 0x5, 0xd2, 0x6a, 0x2, 0x195, 0x196, 0x7, 0x7, 
    0x2, 0x2, 0x196, 0x197, 0x5, 0x28, 0x15, 0x2, 0x197, 0x198, 0x7, 0xa, 
    0x2, 0x2, 0x198, 0x199, 0x5, 0xd4, 0x6b, 0x2, 0x199, 0x19a, 0x7, 0xb, 
    0x2, 0x2, 0x19a, 0x19b, 0x7, 0x6, 0x2, 0x2, 0x19b, 0x19c, 0x5, 0x26, 
    0x14, 0x2, 0x19c, 0x19e, 0x3, 0x2, 0x2, 0x2, 0x19d, 0x181, 0x3, 0x2, 
    0x2, 0x2, 0x19d, 0x186, 0x3, 0x2, 0x2, 0x2, 0x19d, 0x18d, 0x3, 0x2, 
    0x2, 0x2, 0x19d, 0x194, 0x3, 0x2, 0x2, 0x2, 0x19e, 0x27, 0x3, 0x2, 0x2, 
    0x2, 0x19f, 0x1a0, 0x5, 0x64, 0x33, 0x2, 0x1a0, 0x29, 0x3, 0x2, 0x2, 
    0x2, 0x1a1, 0x1a2, 0x7, 0x4, 0x2, 0x2, 0x1a2, 0x1a3, 0x5, 0x2c, 0x17, 
    0x2, 0x1a3, 0x1a4, 0x7, 0x6, 0x2, 0x2, 0x1a4, 0x1a5, 0x5, 0x32, 0x1a, 
    0x2, 0x1a5, 0x1a6, 0x7, 0x5, 0x2, 0x2, 0x1a6, 0x1ac, 0x3, 0x2, 0x2, 
    0x2, 0x1a7, 0x1a8, 0x7, 0x4, 0x2, 0x2, 0x1a8, 0x1a9, 0x5, 0x2c, 0x17, 
    0x2, 0x1a9, 0x1aa, 0x7, 0x5, 0x2, 0x2, 0x1aa, 0x1ac, 0x3, 0x2, 0x2, 
    0x2, 0x1ab, 0x1a1, 0x3, 0x2, 0x2, 0x2, 0x1ab, 0x1a7, 0x3, 0x2, 0x2, 
    0x2, 0x1ac, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x1ad, 0x1ae, 0x7, 0x8, 0x2, 0x2, 
    0x1ae, 0x1b4, 0x7, 0x9, 0x2, 0x2, 0x1af, 0x1b0, 0x7, 0x8, 0x2, 0x2, 
    0x1b0, 0x1b1, 0x5, 0x2e, 0x18, 0x2, 0x1b1, 0x1b2, 0x7, 0x9, 0x2, 0x2, 
    0x1b2, 0x1b4, 0x3, 0x2, 0x2, 0x2, 0x1b3, 0x1ad, 0x3, 0x2, 0x2, 0x2, 
    0x1b3, 0x1af, 0x3, 0x2, 0x2, 0x2, 0x1b4, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x1b5, 
    0x1bb, 0x5, 0x30, 0x19, 0x2, 0x1b6, 0x1b7, 0x5, 0x30, 0x19, 0x2, 0x1b7, 
    0x1b8, 0x7, 0x6, 0x2, 0x2, 0x1b8, 0x1b9, 0x5, 0x2e, 0x18, 0x2, 0x1b9, 
    0x1bb, 0x3, 0x2, 0x2, 0x2, 0x1ba, 0x1b5, 0x3, 0x2, 0x2, 0x2, 0x1ba, 
    0x1b6, 0x3, 0x2, 0x2, 0x2, 0x1bb, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x1bc, 0x1bd, 
    0x5, 0xd0, 0x69, 0x2, 0x1bd, 0x1be, 0x7, 0xc, 0x2, 0x2, 0x1be, 0x1bf, 
    0x7, 0xd, 0x2, 0x2, 0x1bf, 0x1c6, 0x3, 0x2, 0x2, 0x2, 0x1c0, 0x1c1, 
    0x5, 0xd0, 0x69, 0x2, 0x1c1, 0x1c2, 0x7, 0xc, 0x2, 0x2, 0x1c2, 0x1c3, 
    0x5, 0x6a, 0x36, 0x2, 0x1c3, 0x1c4, 0x7, 0xd, 0x2, 0x2, 0x1c4, 0x1c6, 
    0x3, 0x2, 0x2, 0x2, 0x1c5, 0x1bc, 0x3, 0x2, 0x2, 0x2, 0x1c5, 0x1c0, 
    0x3, 0x2, 0x2, 0x2, 0x1c6, 0x31, 0x3, 0x2, 0x2, 0x2, 0x1c7, 0x1c8, 0x7, 
    0x8, 0x2, 0x2, 0x1c8, 0x1ce, 0x7, 0x9, 0x2, 0x2, 0x1c9, 0x1ca, 0x7, 
    0x8, 0x2, 0x2, 0x1ca, 0x1cb, 0x5, 0x34, 0x1b, 0x2, 0x1cb, 0x1cc, 0x7, 
    0x9, 0x2, 0x2, 0x1cc, 0x1ce, 0x3, 0x2, 0x2, 0x2, 0x1cd, 0x1c7, 0x3, 
    0x2, 0x2, 0x2, 0x1cd, 0x1c9, 0x3, 0x2, 0x2, 0x2, 0x1ce, 0x33, 0x3, 0x2, 
    0x2, 0x2, 0x1cf, 0x1d5, 0x5, 0x36, 0x1c, 0x2, 0x1d0, 0x1d1, 0x5, 0x36, 
    0x1c, 0x2, 0x1d1, 0x1d2, 0x7, 0x6, 0x2, 0x2, 0x1d2, 0x1d3, 0x5, 0x34, 
    0x1b, 0x2, 0x1d3, 0x1d5, 0x3, 0x2, 0x2, 0x2, 0x1d4, 0x1cf, 0x3, 0x2, 
    0x2, 0x2, 0x1d4, 0x1d0, 0x3, 0x2, 0x2, 0x2, 0x1d5, 0x35, 0x3, 0x2, 0x2, 
    0x2, 0x1d6, 0x1d7, 0x5, 0xd2, 0x6a, 0x2, 0x1d7, 0x1d8, 0x7, 0xc, 0x2, 
    0x2, 0x1d8, 0x1d9, 0x7, 0xd, 0x2, 0x2, 0x1d9, 0x1e9, 0x3, 0x2, 0x2, 
    0x2, 0x1da, 0x1db, 0x5, 0x28, 0x15, 0x2, 0x1db, 0x1dc, 0x7, 0xc, 0x2, 
    0x2, 0x1dc, 0x1dd, 0x7, 0xd, 0x2, 0x2, 0x1dd, 0x1e9, 0x3, 0x2, 0x2, 
    0x2, 0x1de, 0x1df, 0x5, 0xd2, 0x6a, 0x2, 0x1df, 0x1e0, 0x7, 0xc, 0x2, 
    0x2, 0x1e0, 0x1e1, 0x5, 0x6a, 0x36, 0x2, 0x1e1, 0x1e2, 0x7, 0xd, 0x2, 
    0x2, 0x1e2, 0x1e9, 0x3, 0x2, 0x2, 0x2, 0x1e3, 0x1e4, 0x5, 0x28, 0x15, 
    0x2, 0x1e4, 0x1e5, 0x7, 0xc, 0x2, 0x2, 0x1e5, 0x1e6, 0x5, 0x6a, 0x36, 
    0x2, 0x1e6, 0x1e7, 0x7, 0xd, 0x2, 0x2, 0x1e7, 0x1e9, 0x3, 0x2, 0x2, 
    0x2, 0x1e8, 0x1d6, 0x3, 0x2, 0x2, 0x2, 0x1e8, 0x1da, 0x3, 0x2, 0x2, 
    0x2, 0x1e8, 0x1de, 0x3, 0x2, 0x2, 0x2, 0x1e8, 0x1e3, 0x3, 0x2, 0x2, 
    0x2, 0x1e9, 0x37, 0x3, 0x2, 0x2, 0x2, 0x1ea, 0x1eb, 0x8, 0x1d, 0x1, 
    0x2, 0x1eb, 0x1ec, 0x7, 0x4, 0x2, 0x2, 0x1ec, 0x1ed, 0x5, 0x38, 0x1d, 
    0x2, 0x1ed, 0x1ee, 0x7, 0x5, 0x2, 0x2, 0x1ee, 0x1fb, 0x3, 0x2, 0x2, 
    0x2, 0x1ef, 0x1f0, 0x7, 0x2e, 0x2, 0x2, 0x1f0, 0x1f1, 0x5, 0x18, 0xd, 
    0x2, 0x1f1, 0x1f2, 0x5, 0x4a, 0x26, 0x2, 0x1f2, 0x1f3, 0x5, 0x4c, 0x27, 
    0x2, 0x1f3, 0x1f4, 0x5, 0x3c, 0x1f, 0x2, 0x1f4, 0x1f5, 0x5, 0x3e, 0x20, 
    0x2, 0x1f5, 0x1f6, 0x5, 0x40, 0x21, 0x2, 0x1f6, 0x1f7, 0x5, 0x46, 0x24, 
    0x2, 0x1f7, 0x1f8, 0x5, 0x48, 0x25, 0x2, 0x1f8, 0x1fb, 0x3, 0x2, 0x2, 
    0x2, 0x1f9, 0x1fb, 0x5, 0xcc, 0x67, 0x2, 0x1fa, 0x1ea, 0x3, 0x2, 0x2, 
    0x2, 0x1fa, 0x1ef, 0x3, 0x2, 0x2, 0x2, 0x1fa, 0x1f9, 0x3, 0x2, 0x2, 
    0x2, 0x1fb, 0x202, 0x3, 0x2, 0x2, 0x2, 0x1fc, 0x1fd, 0xc, 0x6, 0x2, 
    0x2, 0x1fd, 0x1fe, 0x5, 0x3a, 0x1e, 0x2, 0x1fe, 0x1ff, 0x5, 0x38, 0x1d, 
    0x7, 0x1ff, 0x201, 0x3, 0x2, 0x2, 0x2, 0x200, 0x1fc, 0x3, 0x2, 0x2, 
    0x2, 0x201, 0x204, 0x3, 0x2, 0x2, 0x2, 0x202, 0x200, 0x3, 0x2, 0x2, 
    0x2, 0x202, 0x203, 0x3, 0x2, 0x2, 0x2, 0x203, 0x39, 0x3, 0x2, 0x2, 0x2, 
    0x204, 0x202, 0x3, 0x2, 0x2, 0x2, 0x205, 0x206, 0x9, 0x2, 0x2, 0x2, 
    0x206, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x207, 0x208, 0x5, 0x54, 0x2b, 0x2, 
    0x208, 0x209, 0x7, 0x28, 0x2, 0x2, 0x209, 0x20a, 0x5, 0x62, 0x32, 0x2, 
    0x20a, 0x20d, 0x3, 0x2, 0x2, 0x2, 0x20b, 0x20d, 0x7, 0xf, 0x2, 0x2, 
    0x20c, 0x207, 0x3, 0x2, 0x2, 0x2, 0x20c, 0x20b, 0x3, 0x2, 0x2, 0x2, 
    0x20d, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x20e, 0x20f, 0x7, 0x20, 0x2, 0x2, 
    0x20f, 0x213, 0x5, 0x50, 0x29, 0x2, 0x210, 0x211, 0x7, 0x20, 0x2, 0x2, 
    0x211, 0x213, 0x5, 0x4e, 0x28, 0x2, 0x212, 0x20e, 0x3, 0x2, 0x2, 0x2, 
    0x212, 0x210, 0x3, 0x2, 0x2, 0x2, 0x213, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x214, 
    0x215, 0x5, 0x42, 0x22, 0x2, 0x215, 0x216, 0x5, 0x40, 0x21, 0x2, 0x216, 
    0x219, 0x3, 0x2, 0x2, 0x2, 0x217, 0x219, 0x3, 0x2, 0x2, 0x2, 0x218, 
    0x214, 0x3, 0x2, 0x2, 0x2, 0x218, 0x217, 0x3, 0x2, 0x2, 0x2, 0x219, 
    0x41, 0x3, 0x2, 0x2, 0x2, 0x21a, 0x21b, 0x7, 0x2a, 0x2, 0x2, 0x21b, 
    0x21c, 0x5, 0xd4, 0x6b, 0x2, 0x21c, 0x21d, 0x7, 0x6, 0x2, 0x2, 0x21d, 
    0x21e, 0x5, 0xd4, 0x6b, 0x2, 0x21e, 0x21f, 0x7, 0x6, 0x2, 0x2, 0x21f, 
    0x220, 0x5, 0xd4, 0x6b, 0x2, 0x220, 0x221, 0x7, 0x2c, 0x2, 0x2, 0x221, 
    0x222, 0x5, 0x70, 0x39, 0x2, 0x222, 0x43, 0x3, 0x2, 0x2, 0x2, 0x223, 
    0x224, 0x5, 0xd6, 0x6c, 0x2, 0x224, 0x225, 0x7, 0x6, 0x2, 0x2, 0x225, 
    0x226, 0x5, 0x44, 0x23, 0x2, 0x226, 0x229, 0x3, 0x2, 0x2, 0x2, 0x227, 
    0x229, 0x5, 0xd6, 0x6c, 0x2, 0x228, 0x223, 0x3, 0x2, 0x2, 0x2, 0x228, 
    0x227, 0x3, 0x2, 0x2, 0x2, 0x229, 0x45, 0x3, 0x2, 0x2, 0x2, 0x22a, 0x22b, 
    0x7, 0x17, 0x2, 0x2, 0x22b, 0x230, 0x5, 0x7a, 0x3e, 0x2, 0x22c, 0x22d, 
    0x7, 0x17, 0x2, 0x2, 0x22d, 0x22e, 0x7, 0x51, 0x2, 0x2, 0x22e, 0x230, 
    0x5, 0x44, 0x23, 0x2, 0x22f, 0x22a, 0x3, 0x2, 0x2, 0x2, 0x22f, 0x22c, 
    0x3, 0x2, 0x2, 0x2, 0x230, 0x47, 0x3, 0x2, 0x2, 0x2, 0x231, 0x232, 0x7, 
    0x2f, 0x2, 0x2, 0x232, 0x233, 0x7, 0xa, 0x2, 0x2, 0x233, 0x234, 0x5, 
    0x50, 0x29, 0x2, 0x234, 0x235, 0x7, 0xb, 0x2, 0x2, 0x235, 0x236, 0x7, 
    0x23, 0x2, 0x2, 0x236, 0x237, 0x5, 0xcc, 0x67, 0x2, 0x237, 0x23a, 0x3, 
    0x2, 0x2, 0x2, 0x238, 0x23a, 0x3, 0x2, 0x2, 0x2, 0x239, 0x231, 0x3, 
    0x2, 0x2, 0x2, 0x239, 0x238, 0x3, 0x2, 0x2, 0x2, 0x23a, 0x49, 0x3, 0x2, 
    0x2, 0x2, 0x23b, 0x23e, 0x7, 0x2d, 0x2, 0x2, 0x23c, 0x23e, 0x3, 0x2, 
    0x2, 0x2, 0x23d, 0x23b, 0x3, 0x2, 0x2, 0x2, 0x23d, 0x23c, 0x3, 0x2, 
    0x2, 0x2, 0x23e, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x23f, 0x242, 0x7, 0x33, 
    0x2, 0x2, 0x240, 0x242, 0x3, 0x2, 0x2, 0x2, 0x241, 0x23f, 0x3, 0x2, 
    0x2, 0x2, 0x241, 0x240, 0x3, 0x2, 0x2, 0x2, 0x242, 0x4d, 0x3, 0x2, 0x2, 
    0x2, 0x243, 0x246, 0x5, 0x56, 0x2c, 0x2, 0x244, 0x246, 0x5, 0x58, 0x2d, 
    0x2, 0x245, 0x243, 0x3, 0x2, 0x2, 0x2, 0x245, 0x244, 0x3, 0x2, 0x2, 
    0x2, 0x246, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x247, 0x252, 0x5, 0xcc, 0x67, 
    0x2, 0x248, 0x249, 0x5, 0x20, 0x11, 0x2, 0x249, 0x24a, 0x5, 0x18, 0xd, 
    0x2, 0x24a, 0x252, 0x3, 0x2, 0x2, 0x2, 0x24b, 0x24c, 0x7, 0x4, 0x2, 
    0x2, 0x24c, 0x24d, 0x5, 0x20, 0x11, 0x2, 0x24d, 0x24e, 0x5, 0x18, 0xd, 
    0x2, 0x24e, 0x24f, 0x7, 0x5, 0x2, 0x2, 0x24f, 0x252, 0x3, 0x2, 0x2, 
    0x2, 0x250, 0x252, 0x5, 0x38, 0x1d, 0x2, 0x251, 0x247, 0x3, 0x2, 0x2, 
    0x2, 0x251, 0x248, 0x3, 0x2, 0x2, 0x2, 0x251, 0x24b, 0x3, 0x2, 0x2, 
    0x2, 0x251, 0x250, 0x3, 0x2, 0x2, 0x2, 0x252, 0x51, 0x3, 0x2, 0x2, 0x2, 
    0x253, 0x254, 0x7, 0x8, 0x2, 0x2, 0x254, 0x25b, 0x7, 0x9, 0x2, 0x2, 
    0x255, 0x256, 0x7, 0x8, 0x2, 0x2, 0x256, 0x257, 0x5, 0x6c, 0x37, 0x2, 
    0x257, 0x258, 0x7, 0x9, 0x2, 0x2, 0x258, 0x25b, 0x3, 0x2, 0x2, 0x2, 
    0x259, 0x25b, 0x7, 0xf, 0x2, 0x2, 0x25a, 0x253, 0x3, 0x2, 0x2, 0x2, 
    0x25a, 0x255, 0x3, 0x2, 0x2, 0x2, 0x25a, 0x259, 0x3, 0x2, 0x2, 0x2, 
    0x25b, 0x53, 0x3, 0x2, 0x2, 0x2, 0x25c, 0x262, 0x5, 0x52, 0x2a, 0x2, 
    0x25d, 0x25e, 0x5, 0x52, 0x2a, 0x2, 0x25e, 0x25f, 0x7, 0x6, 0x2, 0x2, 
    0x25f, 0x260, 0x5, 0x54, 0x2b, 0x2, 0x260, 0x262, 0x3, 0x2, 0x2, 0x2, 
    0x261, 0x25c, 0x3, 0x2, 0x2, 0x2, 0x261, 0x25d, 0x3, 0x2, 0x2, 0x2, 
    0x262, 0x55, 0x3, 0x2, 0x2, 0x2, 0x263, 0x264, 0x5, 0x50, 0x29, 0x2, 
    0x264, 0x265, 0x7, 0x6, 0x2, 0x2, 0x265, 0x266, 0x5, 0x50, 0x29, 0x2, 
    0x266, 0x57, 0x3, 0x2, 0x2, 0x2, 0x267, 0x268, 0x5, 0x50, 0x29, 0x2, 
    0x268, 0x269, 0x7, 0x31, 0x2, 0x2, 0x269, 0x26a, 0x5, 0x50, 0x29, 0x2, 
    0x26a, 0x59, 0x3, 0x2, 0x2, 0x2, 0x26b, 0x26c, 0x9, 0x3, 0x2, 0x2, 0x26c, 
    0x5b, 0x3, 0x2, 0x2, 0x2, 0x26d, 0x270, 0x5, 0xd0, 0x69, 0x2, 0x26e, 
    0x270, 0x5, 0xd2, 0x6a, 0x2, 0x26f, 0x26d, 0x3, 0x2, 0x2, 0x2, 0x26f, 
    0x26e, 0x3, 0x2, 0x2, 0x2, 0x270, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x271, 0x272, 
    0x5, 0xd0, 0x69, 0x2, 0x272, 0x273, 0x7, 0xa, 0x2, 0x2, 0x273, 0x274, 
    0x5, 0xd4, 0x6b, 0x2, 0x274, 0x275, 0x7, 0xb, 0x2, 0x2, 0x275, 0x27e, 
    0x3, 0x2, 0x2, 0x2, 0x276, 0x277, 0x5, 0xd0, 0x69, 0x2, 0x277, 0x278, 
    0x7, 0xa, 0x2, 0x2, 0x278, 0x279, 0x5, 0xd4, 0x6b, 0x2, 0x279, 0x27a, 
    0x7, 0xb, 0x2, 0x2, 0x27a, 0x27b, 0x7, 0x6, 0x2, 0x2, 0x27b, 0x27c, 
    0x5, 0x5e, 0x30, 0x2, 0x27c, 0x27e, 0x3, 0x2, 0x2, 0x2, 0x27d, 0x271, 
    0x3, 0x2, 0x2, 0x2, 0x27d, 0x276, 0x3, 0x2, 0x2, 0x2, 0x27e, 0x5f, 0x3, 
    0x2, 0x2, 0x2, 0x27f, 0x285, 0x5, 0xce, 0x68, 0x2, 0x280, 0x281, 0x5, 
    0xce, 0x68, 0x2, 0x281, 0x282, 0x7, 0x6, 0x2, 0x2, 0x282, 0x283, 0x5, 
    0x60, 0x31, 0x2, 0x283, 0x285, 0x3, 0x2, 0x2, 0x2, 0x284, 0x27f, 0x3, 
    0x2, 0x2, 0x2, 0x284, 0x280, 0x3, 0x2, 0x2, 0x2, 0x285, 0x61, 0x3, 0x2, 
    0x2, 0x2, 0x286, 0x28c, 0x5, 0xd4, 0x6b, 0x2, 0x287, 0x288, 0x5, 0xd4, 
    0x6b, 0x2, 0x288, 0x289, 0x7, 0x6, 0x2, 0x2, 0x289, 0x28a, 0x5, 0x62, 
    0x32, 0x2, 0x28a, 0x28c, 0x3, 0x2, 0x2, 0x2, 0x28b, 0x286, 0x3, 0x2, 
    0x2, 0x2, 0x28b, 0x287, 0x3, 0x2, 0x2, 0x2, 0x28c, 0x63, 0x3, 0x2, 0x2, 
    0x2, 0x28d, 0x28e, 0x7, 0x4, 0x2, 0x2, 0x28e, 0x28f, 0x5, 0xd0, 0x69, 
    0x2, 0x28f, 0x290, 0x7, 0x6, 0x2, 0x2, 0x290, 0x291, 0x5, 0xd0, 0x69, 
    0x2, 0x291, 0x292, 0x7, 0x5, 0x2, 0x2, 0x292, 0x65, 0x3, 0x2, 0x2, 0x2, 
    0x293, 0x299, 0x5, 0x64, 0x33, 0x2, 0x294, 0x295, 0x5, 0x64, 0x33, 0x2, 
    0x295, 0x296, 0x7, 0x6, 0x2, 0x2, 0x296, 0x297, 0x5, 0x66, 0x34, 0x2, 
    0x297, 0x299, 0x3, 0x2, 0x2, 0x2, 0x298, 0x293, 0x3, 0x2, 0x2, 0x2, 
    0x298, 0x294, 0x3, 0x2, 0x2, 0x2, 0x299, 0x67, 0x3, 0x2, 0x2, 0x2, 0x29a, 
    0x29b, 0x5, 0xca, 0x66, 0x2, 0x29b, 0x29c, 0x7, 0x7, 0x2, 0x2, 0x29c, 
    0x29d, 0x5, 0x5a, 0x2e, 0x2, 0x29d, 0x69, 0x3, 0x2, 0x2, 0x2, 0x29e, 
    0x2a4, 0x5, 0x68, 0x35, 0x2, 0x29f, 0x2a0, 0x5, 0x68, 0x35, 0x2, 0x2a0, 
    0x2a1, 0x7, 0x6, 0x2, 0x2, 0x2a1, 0x2a2, 0x5, 0x6a, 0x36, 0x2, 0x2a2, 
    0x2a4, 0x3, 0x2, 0x2, 0x2, 0x2a3, 0x29e, 0x3, 0x2, 0x2, 0x2, 0x2a3, 
    0x29f, 0x3, 0x2, 0x2, 0x2, 0x2a4, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x2a5, 0x2ab, 
    0x5, 0xca, 0x66, 0x2, 0x2a6, 0x2a7, 0x5, 0xca, 0x66, 0x2, 0x2a7, 0x2a8, 
    0x7, 0x6, 0x2, 0x2, 0x2a8, 0x2a9, 0x5, 0x6c, 0x37, 0x2, 0x2a9, 0x2ab, 
    0x3, 0x2, 0x2, 0x2, 0x2aa, 0x2a5, 0x3, 0x2, 0x2, 0x2, 0x2aa, 0x2a6, 
    0x3, 0x2, 0x2, 0x2, 0x2ab, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x2ac, 0x2ad, 0x5, 
    0xca, 0x66, 0x2, 0x2ad, 0x2ae, 0x7, 0x7, 0x2, 0x2, 0x2ae, 0x2af, 0x5, 
    0xca, 0x66, 0x2, 0x2af, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x2b0, 0x2b6, 0x5, 
    0x6e, 0x38, 0x2, 0x2b1, 0x2b2, 0x5, 0x6e, 0x38, 0x2, 0x2b2, 0x2b3, 0x7, 
    0x6, 0x2, 0x2, 0x2b3, 0x2b4, 0x5, 0x70, 0x39, 0x2, 0x2b4, 0x2b6, 0x3, 
    0x2, 0x2, 0x2, 0x2b5, 0x2b0, 0x3, 0x2, 0x2, 0x2, 0x2b5, 0x2b1, 0x3, 
    0x2, 0x2, 0x2, 0x2b6, 0x71, 0x3, 0x2, 0x2, 0x2, 0x2b7, 0x2be, 0x7, 0xd, 
    0x2, 0x2, 0x2b8, 0x2be, 0x7, 0xc, 0x2, 0x2, 0x2b9, 0x2be, 0x7, 0x10, 
    0x2, 0x2, 0x2ba, 0x2be, 0x7, 0x11, 0x2, 0x2, 0x2bb, 0x2be, 0x7, 0x7, 
    0x2, 0x2, 0x2bc, 0x2be, 0x7, 0x12, 0x2, 0x2, 0x2bd, 0x2b7, 0x3, 0x2, 
    0x2, 0x2, 0x2bd, 0x2b8, 0x3, 0x2, 0x2, 0x2, 0x2bd, 0x2b9, 0x3, 0x2, 
    0x2, 0x2, 0x2bd, 0x2ba, 0x3, 0x2, 0x2, 0x2, 0x2bd, 0x2bb, 0x3, 0x2, 
    0x2, 0x2, 0x2bd, 0x2bc, 0x3, 0x2, 0x2, 0x2, 0x2be, 0x73, 0x3, 0x2, 0x2, 
    0x2, 0x2bf, 0x2c0, 0x9, 0x4, 0x2, 0x2, 0x2c0, 0x75, 0x3, 0x2, 0x2, 0x2, 
    0x2c1, 0x2c2, 0x9, 0x5, 0x2, 0x2, 0x2c2, 0x77, 0x3, 0x2, 0x2, 0x2, 0x2c3, 
    0x2c4, 0x7, 0x39, 0x2, 0x2, 0x2c4, 0x79, 0x3, 0x2, 0x2, 0x2, 0x2c5, 
    0x2c6, 0x8, 0x3e, 0x1, 0x2, 0x2c6, 0x2d1, 0x5, 0x7c, 0x3f, 0x2, 0x2c7, 
    0x2c8, 0x5, 0x92, 0x4a, 0x2, 0x2c8, 0x2c9, 0x5, 0x7a, 0x3e, 0x2, 0x2c9, 
    0x2ca, 0x5, 0x94, 0x4b, 0x2, 0x2ca, 0x2d1, 0x3, 0x2, 0x2, 0x2, 0x2cb, 
    0x2cc, 0x5, 0x78, 0x3d, 0x2, 0x2cc, 0x2cd, 0x5, 0x7a, 0x3e, 0x5, 0x2cd, 
    0x2d1, 0x3, 0x2, 0x2, 0x2, 0x2ce, 0x2d1, 0x7, 0x4f, 0x2, 0x2, 0x2cf, 
    0x2d1, 0x7, 0x50, 0x2, 0x2, 0x2d0, 0x2c5, 0x3, 0x2, 0x2, 0x2, 0x2d0, 
    0x2c7, 0x3, 0x2, 0x2, 0x2, 0x2d0, 0x2cb, 0x3, 0x2, 0x2, 0x2, 0x2d0, 
    0x2ce, 0x3, 0x2, 0x2, 0x2, 0x2d0, 0x2cf, 0x3, 0x2, 0x2, 0x2, 0x2d1, 
    0x2d8, 0x3, 0x2, 0x2, 0x2, 0x2d2, 0x2d3, 0xc, 0x6, 0x2, 0x2, 0x2d3, 
    0x2d4, 0x5, 0x76, 0x3c, 0x2, 0x2d4, 0x2d5, 0x5, 0x7a, 0x3e, 0x7, 0x2d5, 
    0x2d7, 0x3, 0x2, 0x2, 0x2, 0x2d6, 0x2d2, 0x3, 0x2, 0x2, 0x2, 0x2d7, 
    0x2da, 0x3, 0x2, 0x2, 0x2, 0x2d8, 0x2d6, 0x3, 0x2, 0x2, 0x2, 0x2d8, 
    0x2d9, 0x3, 0x2, 0x2, 0x2, 0x2d9, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x2da, 0x2d8, 
    0x3, 0x2, 0x2, 0x2, 0x2db, 0x2e0, 0x5, 0x88, 0x45, 0x2, 0x2dc, 0x2e0, 
    0x5, 0x7e, 0x40, 0x2, 0x2dd, 0x2e0, 0x5, 0x80, 0x41, 0x2, 0x2de, 0x2e0, 
    0x5, 0x86, 0x44, 0x2, 0x2df, 0x2db, 0x3, 0x2, 0x2, 0x2, 0x2df, 0x2dc, 
    0x3, 0x2, 0x2, 0x2, 0x2df, 0x2dd, 0x3, 0x2, 0x2, 0x2, 0x2df, 0x2de, 
    0x3, 0x2, 0x2, 0x2, 0x2e0, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x2e1, 0x2e2, 0x7, 
    0x3a, 0x2, 0x2, 0x2e2, 0x2e3, 0x5, 0x90, 0x49, 0x2, 0x2e3, 0x2e4, 0x7, 
    0x4, 0x2, 0x2, 0x2e4, 0x2e5, 0x5, 0x7a, 0x3e, 0x2, 0x2e5, 0x2e6, 0x7, 
    0x5, 0x2, 0x2, 0x2e6, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x2e7, 0x2e8, 0x7, 0x3b, 
    0x2, 0x2, 0x2e8, 0x2e9, 0x5, 0x90, 0x49, 0x2, 0x2e9, 0x2ea, 0x7, 0x4, 
    0x2, 0x2, 0x2ea, 0x2eb, 0x5, 0x7a, 0x3e, 0x2, 0x2eb, 0x2ec, 0x7, 0x5, 
    0x2, 0x2, 0x2ec, 0x81, 0x3, 0x2, 0x2, 0x2, 0x2ed, 0x2ee, 0x8, 0x42, 
    0x1, 0x2, 0x2ee, 0x2f6, 0x5, 0x84, 0x43, 0x2, 0x2ef, 0x2f0, 0x5, 0x92, 
    0x4a, 0x2, 0x2f0, 0x2f1, 0x5, 0x82, 0x42, 0x2, 0x2f1, 0x2f2, 0x5, 0x94, 
    0x4b, 0x2, 0x2f2, 0x2f6, 0x3, 0x2, 0x2, 0x2, 0x2f3, 0x2f6, 0x7, 0x4f, 
    0x2, 0x2, 0x2f4, 0x2f6, 0x7, 0x50, 0x2, 0x2, 0x2f5, 0x2ed, 0x3, 0x2, 
    0x2, 0x2, 0x2f5, 0x2ef, 0x3, 0x2, 0x2, 0x2, 0x2f5, 0x2f3, 0x3, 0x2, 
    0x2, 0x2, 0x2f5, 0x2f4, 0x3, 0x2, 0x2, 0x2, 0x2f6, 0x2fd, 0x3, 0x2, 
    0x2, 0x2, 0x2f7, 0x2f8, 0xc, 0x6, 0x2, 0x2, 0x2f8, 0x2f9, 0x5, 0x74, 
    0x3b, 0x2, 0x2f9, 0x2fa, 0x5, 0x82, 0x42, 0x7, 0x2fa, 0x2fc, 0x3, 0x2, 
    0x2, 0x2, 0x2fb, 0x2f7, 0x3, 0x2, 0x2, 0x2, 0x2fc, 0x2ff, 0x3, 0x2, 
    0x2, 0x2, 0x2fd, 0x2fb, 0x3, 0x2, 0x2, 0x2, 0x2fd, 0x2fe, 0x3, 0x2, 
    0x2, 0x2, 0x2fe, 0x83, 0x3, 0x2, 0x2, 0x2, 0x2ff, 0x2fd, 0x3, 0x2, 0x2, 
    0x2, 0x300, 0x303, 0x5, 0x5a, 0x2e, 0x2, 0x301, 0x303, 0x5, 0xca, 0x66, 
    0x2, 0x302, 0x300, 0x3, 0x2, 0x2, 0x2, 0x302, 0x301, 0x3, 0x2, 0x2, 
    0x2, 0x303, 0x85, 0x3, 0x2, 0x2, 0x2, 0x304, 0x305, 0x5, 0x82, 0x42, 
    0x2, 0x305, 0x306, 0x5, 0x72, 0x3a, 0x2, 0x306, 0x307, 0x5, 0x82, 0x42, 
    0x2, 0x307, 0x87, 0x3, 0x2, 0x2, 0x2, 0x308, 0x309, 0x5, 0x8a, 0x46, 
    0x2, 0x309, 0x30a, 0x7, 0x4, 0x2, 0x2, 0x30a, 0x30b, 0x5, 0x8e, 0x48, 
    0x2, 0x30b, 0x30c, 0x7, 0x5, 0x2, 0x2, 0x30c, 0x312, 0x3, 0x2, 0x2, 
    0x2, 0x30d, 0x30e, 0x5, 0x8a, 0x46, 0x2, 0x30e, 0x30f, 0x7, 0x4, 0x2, 
    0x2, 0x30f, 0x310, 0x7, 0x5, 0x2, 0x2, 0x310, 0x312, 0x3, 0x2, 0x2, 
    0x2, 0x311, 0x308, 0x3, 0x2, 0x2, 0x2, 0x311, 0x30d, 0x3, 0x2, 0x2, 
    0x2, 0x312, 0x89, 0x3, 0x2, 0x2, 0x2, 0x313, 0x314, 0x9, 0x6, 0x2, 0x2, 
    0x314, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x315, 0x31c, 0x5, 0xde, 0x70, 0x2, 
    0x316, 0x317, 0x5, 0xde, 0x70, 0x2, 0x317, 0x318, 0x7, 0xa, 0x2, 0x2, 
    0x318, 0x319, 0x5, 0xdc, 0x6f, 0x2, 0x319, 0x31a, 0x7, 0xb, 0x2, 0x2, 
    0x31a, 0x31c, 0x3, 0x2, 0x2, 0x2, 0x31b, 0x315, 0x3, 0x2, 0x2, 0x2, 
    0x31b, 0x316, 0x3, 0x2, 0x2, 0x2, 0x31c, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x31d, 
    0x31e, 0x5, 0x8c, 0x47, 0x2, 0x31e, 0x31f, 0x7, 0x6, 0x2, 0x2, 0x31f, 
    0x320, 0x5, 0x8e, 0x48, 0x2, 0x320, 0x323, 0x3, 0x2, 0x2, 0x2, 0x321, 
    0x323, 0x5, 0x8c, 0x47, 0x2, 0x322, 0x31d, 0x3, 0x2, 0x2, 0x2, 0x322, 
    0x321, 0x3, 0x2, 0x2, 0x2, 0x323, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x324, 0x32a, 
    0x5, 0xda, 0x6e, 0x2, 0x325, 0x326, 0x5, 0xda, 0x6e, 0x2, 0x326, 0x327, 
    0x7, 0x6, 0x2, 0x2, 0x327, 0x328, 0x5, 0x90, 0x49, 0x2, 0x328, 0x32a, 
    0x3, 0x2, 0x2, 0x2, 0x329, 0x324, 0x3, 0x2, 0x2, 0x2, 0x329, 0x325, 
    0x3, 0x2, 0x2, 0x2, 0x32a, 0x91, 0x3, 0x2, 0x2, 0x2, 0x32b, 0x32c, 0x7, 
    0x4, 0x2, 0x2, 0x32c, 0x93, 0x3, 0x2, 0x2, 0x2, 0x32d, 0x32e, 0x7, 0x5, 
    0x2, 0x2, 0x32e, 0x95, 0x3, 0x2, 0x2, 0x2, 0x32f, 0x336, 0x5, 0x98, 
    0x4d, 0x2, 0x330, 0x336, 0x5, 0xae, 0x58, 0x2, 0x331, 0x336, 0x5, 0xb6, 
    0x5c, 0x2, 0x332, 0x336, 0x5, 0xb0, 0x59, 0x2, 0x333, 0x336, 0x5, 0xb8, 
    0x5d, 0x2, 0x334, 0x336, 0x5, 0xba, 0x5e, 0x2, 0x335, 0x32f, 0x3, 0x2, 
    0x2, 0x2, 0x335, 0x330, 0x3, 0x2, 0x2, 0x2, 0x335, 0x331, 0x3, 0x2, 
    0x2, 0x2, 0x335, 0x332, 0x3, 0x2, 0x2, 0x2, 0x335, 0x333, 0x3, 0x2, 
    0x2, 0x2, 0x335, 0x334, 0x3, 0x2, 0x2, 0x2, 0x336, 0x97, 0x3, 0x2, 0x2, 
    0x2, 0x337, 0x338, 0x7, 0x48, 0x2, 0x2, 0x338, 0x339, 0x7, 0x1b, 0x2, 
    0x2, 0x339, 0x33a, 0x5, 0xd8, 0x6d, 0x2, 0x33a, 0x33b, 0x5, 0x9a, 0x4e, 
    0x2, 0x33b, 0x341, 0x3, 0x2, 0x2, 0x2, 0x33c, 0x33d, 0x7, 0x48, 0x2, 
    0x2, 0x33d, 0x33e, 0x7, 0x1b, 0x2, 0x2, 0x33e, 0x33f, 0x7, 0x51, 0x2, 
    0x2, 0x33f, 0x341, 0x5, 0xd6, 0x6c, 0x2, 0x340, 0x337, 0x3, 0x2, 0x2, 
    0x2, 0x340, 0x33c, 0x3, 0x2, 0x2, 0x2, 0x341, 0x99, 0x3, 0x2, 0x2, 0x2, 
    0x342, 0x343, 0x7, 0x8, 0x2, 0x2, 0x343, 0x344, 0x5, 0x9c, 0x4f, 0x2, 
    0x344, 0x345, 0x7, 0x6, 0x2, 0x2, 0x345, 0x346, 0x5, 0x9e, 0x50, 0x2, 
    0x346, 0x347, 0x7, 0x9, 0x2, 0x2, 0x347, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x348, 
    0x34e, 0x5, 0xa0, 0x51, 0x2, 0x349, 0x34a, 0x5, 0xa0, 0x51, 0x2, 0x34a, 
    0x34b, 0x7, 0x6, 0x2, 0x2, 0x34b, 0x34c, 0x5, 0x9c, 0x4f, 0x2, 0x34c, 
    0x34e, 0x3, 0x2, 0x2, 0x2, 0x34d, 0x348, 0x3, 0x2, 0x2, 0x2, 0x34d, 
    0x349, 0x3, 0x2, 0x2, 0x2, 0x34e, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x34f, 0x355, 
    0x5, 0xa4, 0x53, 0x2, 0x350, 0x351, 0x5, 0xa4, 0x53, 0x2, 0x351, 0x352, 
    0x7, 0x6, 0x2, 0x2, 0x352, 0x353, 0x5, 0x9e, 0x50, 0x2, 0x353, 0x355, 
    0x3, 0x2, 0x2, 0x2, 0x354, 0x34f, 0x3, 0x2, 0x2, 0x2, 0x354, 0x350, 
    0x3, 0x2, 0x2, 0x2, 0x355, 0x9f, 0x3, 0x2, 0x2, 0x2, 0x356, 0x357, 0x5, 
    0xa8, 0x55, 0x2, 0x357, 0x358, 0x7, 0x4, 0x2, 0x2, 0x358, 0x359, 0x5, 
    0xa2, 0x52, 0x2, 0x359, 0x35a, 0x7, 0x5, 0x2, 0x2, 0x35a, 0xa1, 0x3, 
    0x2, 0x2, 0x2, 0x35b, 0x35c, 0x5, 0xa8, 0x55, 0x2, 0x35c, 0x35d, 0x5, 
    0xaa, 0x56, 0x2, 0x35d, 0x364, 0x3, 0x2, 0x2, 0x2, 0x35e, 0x35f, 0x5, 
    0xa8, 0x55, 0x2, 0x35f, 0x360, 0x5, 0xaa, 0x56, 0x2, 0x360, 0x361, 0x7, 
    0x6, 0x2, 0x2, 0x361, 0x362, 0x5, 0xa2, 0x52, 0x2, 0x362, 0x364, 0x3, 
    0x2, 0x2, 0x2, 0x363, 0x35b, 0x3, 0x2, 0x2, 0x2, 0x363, 0x35e, 0x3, 
    0x2, 0x2, 0x2, 0x364, 0xa3, 0x3, 0x2, 0x2, 0x2, 0x365, 0x366, 0x5, 0xa8, 
    0x55, 0x2, 0x366, 0x367, 0x7, 0xa, 0x2, 0x2, 0x367, 0x368, 0x5, 0xa6, 
    0x54, 0x2, 0x368, 0x369, 0x7, 0xb, 0x2, 0x2, 0x369, 0x36a, 0x7, 0x4, 
    0x2, 0x2, 0x36a, 0x36b, 0x5, 0xa2, 0x52, 0x2, 0x36b, 0x36c, 0x7, 0x5, 
    0x2, 0x2, 0x36c, 0xa5, 0x3, 0x2, 0x2, 0x2, 0x36d, 0x36e, 0x5, 0xa8, 
    0x55, 0x2, 0x36e, 0x36f, 0x7, 0xe, 0x2, 0x2, 0x36f, 0x370, 0x5, 0xa8, 
    0x55, 0x2, 0x370, 0x378, 0x3, 0x2, 0x2, 0x2, 0x371, 0x372, 0x5, 0xa8, 
    0x55, 0x2, 0x372, 0x373, 0x7, 0xe, 0x2, 0x2, 0x373, 0x374, 0x5, 0xa8, 
    0x55, 0x2, 0x374, 0x375, 0x7, 0x6, 0x2, 0x2, 0x375, 0x376, 0x5, 0xa6, 
    0x54, 0x2, 0x376, 0x378, 0x3, 0x2, 0x2, 0x2, 0x377, 0x36d, 0x3, 0x2, 
    0x2, 0x2, 0x377, 0x371, 0x3, 0x2, 0x2, 0x2, 0x378, 0xa7, 0x3, 0x2, 0x2, 
    0x2, 0x379, 0x37a, 0x7, 0x55, 0x2, 0x2, 0x37a, 0xa9, 0x3, 0x2, 0x2, 
    0x2, 0x37b, 0x37c, 0x5, 0xc8, 0x65, 0x2, 0x37c, 0xab, 0x3, 0x2, 0x2, 
    0x2, 0x37d, 0x37e, 0x7, 0x8, 0x2, 0x2, 0x37e, 0x37f, 0x5, 0xc2, 0x62, 
    0x2, 0x37f, 0x380, 0x7, 0x9, 0x2, 0x2, 0x380, 0x383, 0x3, 0x2, 0x2, 
    0x2, 0x381, 0x383, 0x5, 0xd8, 0x6d, 0x2, 0x382, 0x37d, 0x3, 0x2, 0x2, 
    0x2, 0x382, 0x381, 0x3, 0x2, 0x2, 0x2, 0x383, 0xad, 0x3, 0x2, 0x2, 0x2, 
    0x384, 0x385, 0x7, 0x48, 0x2, 0x2, 0x385, 0x386, 0x7, 0x19, 0x2, 0x2, 
    0x386, 0x387, 0x5, 0xcc, 0x67, 0x2, 0x387, 0x388, 0x7, 0x4, 0x2, 0x2, 
    0x388, 0x389, 0x5, 0x60, 0x31, 0x2, 0x389, 0x38a, 0x7, 0x5, 0x2, 0x2, 
    0x38a, 0x38b, 0x5, 0xac, 0x57, 0x2, 0x38b, 0xaf, 0x3, 0x2, 0x2, 0x2, 
    0x38c, 0x38d, 0x7, 0x48, 0x2, 0x2, 0x38d, 0x38e, 0x7, 0x1a, 0x2, 0x2, 
    0x38e, 0x38f, 0x5, 0xce, 0x68, 0x2, 0x38f, 0x390, 0x5, 0xac, 0x57, 0x2, 
    0x390, 0x391, 0x5, 0xb2, 0x5a, 0x2, 0x391, 0x392, 0x5, 0xb4, 0x5b, 0x2, 
    0x392, 0xb1, 0x3, 0x2, 0x2, 0x2, 0x393, 0x394, 0x7, 0x20, 0x2, 0x2, 
    0x394, 0x395, 0x7, 0x51, 0x2, 0x2, 0x395, 0x398, 0x5, 0x44, 0x23, 0x2, 
    0x396, 0x398, 0x3, 0x2, 0x2, 0x2, 0x397, 0x393, 0x3, 0x2, 0x2, 0x2, 
    0x397, 0x396, 0x3, 0x2, 0x2, 0x2, 0x398, 0xb3, 0x3, 0x2, 0x2, 0x2, 0x399, 
    0x39a, 0x7, 0x28, 0x2, 0x2, 0x39a, 0x39d, 0x5, 0xcc, 0x67, 0x2, 0x39b, 
    0x39d, 0x3, 0x2, 0x2, 0x2, 0x39c, 0x399, 0x3, 0x2, 0x2, 0x2, 0x39c, 
    0x39b, 0x3, 0x2, 0x2, 0x2, 0x39d, 0xb5, 0x3, 0x2, 0x2, 0x2, 0x39e, 0x39f, 
    0x7, 0x52, 0x2, 0x2, 0x39f, 0x3a0, 0x7, 0x19, 0x2, 0x2, 0x3a0, 0x3a1, 
    0x5, 0xcc, 0x67, 0x2, 0x3a1, 0xb7, 0x3, 0x2, 0x2, 0x2, 0x3a2, 0x3a3, 
    0x7, 0x52, 0x2, 0x2, 0x3a3, 0x3a4, 0x7, 0x1a, 0x2, 0x2, 0x3a4, 0x3a5, 
    0x5, 0xce, 0x68, 0x2, 0x3a5, 0xb9, 0x3, 0x2, 0x2, 0x2, 0x3a6, 0x3aa, 
    0x5, 0xbc, 0x5f, 0x2, 0x3a7, 0x3aa, 0x5, 0xbe, 0x60, 0x2, 0x3a8, 0x3aa, 
    0x5, 0xc0, 0x61, 0x2, 0x3a9, 0x3a6, 0x3, 0x2, 0x2, 0x2, 0x3a9, 0x3a7, 
    0x3, 0x2, 0x2, 0x2, 0x3a9, 0x3a8, 0x3, 0x2, 0x2, 0x2, 0x3aa, 0xbb, 0x3, 
    0x2, 0x2, 0x2, 0x3ab, 0x3ac, 0x7, 0x18, 0x2, 0x2, 0x3ac, 0x3ad, 0x7, 
    0x19, 0x2, 0x2, 0x3ad, 0x3ae, 0x5, 0xcc, 0x67, 0x2, 0x3ae, 0xbd, 0x3, 
    0x2, 0x2, 0x2, 0x3af, 0x3b0, 0x7, 0x18, 0x2, 0x2, 0x3b0, 0x3b1, 0x7, 
    0x1a, 0x2, 0x2, 0x3b1, 0x3b2, 0x5, 0xce, 0x68, 0x2, 0x3b2, 0xbf, 0x3, 
    0x2, 0x2, 0x2, 0x3b3, 0x3b4, 0x7, 0x18, 0x2, 0x2, 0x3b4, 0x3b5, 0x7, 
    0x1b, 0x2, 0x2, 0x3b5, 0x3b6, 0x5, 0xd8, 0x6d, 0x2, 0x3b6, 0xc1, 0x3, 
    0x2, 0x2, 0x2, 0x3b7, 0x3b8, 0x5, 0xd4, 0x6b, 0x2, 0x3b8, 0x3b9, 0x7, 
    0xc, 0x2, 0x2, 0x3b9, 0x3ba, 0x5, 0xc4, 0x63, 0x2, 0x3ba, 0x3bb, 0x7, 
    0xd, 0x2, 0x2, 0x3bb, 0x3c4, 0x3, 0x2, 0x2, 0x2, 0x3bc, 0x3bd, 0x5, 
    0xd4, 0x6b, 0x2, 0x3bd, 0x3be, 0x7, 0xc, 0x2, 0x2, 0x3be, 0x3bf, 0x5, 
    0xc4, 0x63, 0x2, 0x3bf, 0x3c0, 0x7, 0xd, 0x2, 0x2, 0x3c0, 0x3c1, 0x7, 
    0x6, 0x2, 0x2, 0x3c1, 0x3c2, 0x5, 0xc2, 0x62, 0x2, 0x3c2, 0x3c4, 0x3, 
    0x2, 0x2, 0x2, 0x3c3, 0x3b7, 0x3, 0x2, 0x2, 0x2, 0x3c3, 0x3bc, 0x3, 
    0x2, 0x2, 0x2, 0x3c4, 0xc3, 0x3, 0x2, 0x2, 0x2, 0x3c5, 0x3cb, 0x5, 0xc6, 
    0x64, 0x2, 0x3c6, 0x3c7, 0x5, 0xc6, 0x64, 0x2, 0x3c7, 0x3c8, 0x7, 0x6, 
    0x2, 0x2, 0x3c8, 0x3c9, 0x5, 0xc4, 0x63, 0x2, 0x3c9, 0x3cb, 0x3, 0x2, 
    0x2, 0x2, 0x3ca, 0x3c5, 0x3, 0x2, 0x2, 0x2, 0x3ca, 0x3c6, 0x3, 0x2, 
    0x2, 0x2, 0x3cb, 0xc5, 0x3, 0x2, 0x2, 0x2, 0x3cc, 0x3cd, 0x5, 0xca, 
    0x66, 0x2, 0x3cd, 0x3ce, 0x7, 0x15, 0x2, 0x2, 0x3ce, 0x3cf, 0x5, 0xc8, 
    0x65, 0x2, 0x3cf, 0xc7, 0x3, 0x2, 0x2, 0x2, 0x3d0, 0x3d1, 0x9, 0x7, 
    0x2, 0x2, 0x3d1, 0xc9, 0x3, 0x2, 0x2, 0x2, 0x3d2, 0x3d3, 0x7, 0x55, 
    0x2, 0x2, 0x3d3, 0xcb, 0x3, 0x2, 0x2, 0x2, 0x3d4, 0x3d5, 0x7, 0x55, 
    0x2, 0x2, 0x3d5, 0xcd, 0x3, 0x2, 0x2, 0x2, 0x3d6, 0x3d7, 0x7, 0x55, 
    0x2, 0x2, 0x3d7, 0xcf, 0x3, 0x2, 0x2, 0x2, 0x3d8, 0x3d9, 0x7, 0x55, 
    0x2, 0x2, 0x3d9, 0xd1, 0x3, 0x2, 0x2, 0x2, 0x3da, 0x3db, 0x7, 0x55, 
    0x2, 0x2, 0x3db, 0xd3, 0x3, 0x2, 0x2, 0x2, 0x3dc, 0x3dd, 0x7, 0x55, 
    0x2, 0x2, 0x3dd, 0xd5, 0x3, 0x2, 0x2, 0x2, 0x3de, 0x3df, 0x7, 0x59, 
    0x2, 0x2, 0x3df, 0xd7, 0x3, 0x2, 0x2, 0x2, 0x3e0, 0x3e1, 0x7, 0x55, 
    0x2, 0x2, 0x3e1, 0xd9, 0x3, 0x2, 0x2, 0x2, 0x3e2, 0x3e3, 0x7, 0x55, 
    0x2, 0x2, 0x3e3, 0xdb, 0x3, 0x2, 0x2, 0x2, 0x3e4, 0x3e5, 0x7, 0x53, 
    0x2, 0x2, 0x3e5, 0xdd, 0x3, 0x2, 0x2, 0x2, 0x3e6, 0x3e7, 0x9, 0x8, 0x2, 
    0x2, 0x3e7, 0xdf, 0x3, 0x2, 0x2, 0x2, 0x45, 0xe6, 0xec, 0xf0, 0xf4, 
    0x112, 0x119, 0x120, 0x141, 0x150, 0x160, 0x164, 0x16b, 0x177, 0x17f, 
    0x19d, 0x1ab, 0x1b3, 0x1ba, 0x1c5, 0x1cd, 0x1d4, 0x1e8, 0x1fa, 0x202, 
    0x20c, 0x212, 0x218, 0x228, 0x22f, 0x239, 0x23d, 0x241, 0x245, 0x251, 
    0x25a, 0x261, 0x26f, 0x27d, 0x284, 0x28b, 0x298, 0x2a3, 0x2aa, 0x2b5, 
    0x2bd, 0x2d0, 0x2d8, 0x2df, 0x2f5, 0x2fd, 0x302, 0x311, 0x31b, 0x322, 
    0x329, 0x335, 0x340, 0x34d, 0x354, 0x363, 0x377, 0x382, 0x397, 0x39c, 
    0x3a9, 0x3c3, 0x3ca, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

GraphDBParser::Initializer GraphDBParser::_init;
