#pragma once

#include "base_env.h"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

namespace minizero::env {

class JointAction : public BaseAction {
public:
    JointAction() : BaseAction(), length_(0) { tokens_.fill(-1); }
    JointAction(int action_id, Player player) : BaseAction(action_id, player), length_(0) { tokens_.fill(-1); }

    JointAction(const std::vector<int>& tokens, Player player)
        : BaseAction(tokens.empty() ? -1 : tokens[0], player),
          length_(static_cast<int8_t>(tokens.size()))
    {
        assert(tokens.size() <= kMaxActionTokens);
        tokens_.fill(-1);
        std::copy(tokens.begin(), tokens.end(), tokens_.begin());
    }
    protected:
        int length_;
        int kMaxActionsTokens;
        std::array<int8_t, kMaxActionTokens> tokens_;
};

template <class Action>
class MultiAgentEnv : public BaseEnv<Action> {
public:
    MultiAgentEnv() = default;
    virtual ~MultiAgentEnv() = default;
};

template <class Action, class Env>
class MultiAgentEnvLoader : public BaseEnvLoader<Action, Env> {
public:
    MultiAgentEnvLoader() = default;
    virtual ~MultiAgentEnvLoader() = default;
};


} // namespace minizero::env
