#include "clang/StaticAnalyzer/Core/Checker.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h"
#include "clang/StaticAnalyzer/Checkers/BuiltinCheckerRegistration.h"
#include "Taint.h"

using namespace clang;
using namespace ento;

namespace {
  class BranchConditionExtractor : public Checker<check::BranchCondition, check::BeginFunction> {

  public:
    void checkBranchCondition(const Stmt *Condition, CheckerContext &Ctx) const;
    void checkBeginFunction(CheckerContext &Ctx) const;

  };
} // end anonymous namespace

void BranchConditionExtractor::checkBranchCondition(const Stmt *Condition,
                                                    CheckerContext &Ctx) const {

}

void BranchConditionExtractor::checkBeginFunction(CheckerContext &Ctx) const {
  const LocationContext *LCtx = Ctx.getLocationContext();
  const auto * FD = dyn_cast_or_null<FunctionDecl>(LCtx->getDecl());
  if (!FD) {
    return;
  }

  // TODO: These function names should be read in from some source.
  if (FD->getIdentifier()->getName() != "foo") {
    return;
  }

  // TODO: The parameter index should not be hardcoded.
  if (FD->getParamDecl(0)) {}


}

void ento::registerBranchConditionExtractor(CheckerManager &mgr) {
  mgr.registerChecker<BranchConditionExtractor>();
}

bool ento::shouldRegisterBranchConditionExtractor(const CheckerManager &mgr) {
  return true;
}
