#pragma once

#include "ma_env.h"
#include <string>
#include <vector>

namespace minizero::env::switch4 {

const std::string kSwitch4Name = "switch4";
const int kSwitch4NameAgents = 2;
const int kMaxActionTokens = 8;
const int kSwitch4BoardLength = 7;
const int kSwitch4BoardHeight = 7;


typedef JointAction<kSwitch4NumPlayer> Switch4Action;

class Switch4Env : public MultiAgentEnv<Switch4Action> {
public:
    Switch4() : BaseBoardEnv<Switch4Action>(kSwitch4BoardSize) { reset(); }

    void reset() override;
    bool act(const Switch4Action& action) override;
    bool act(const std::vector<std::string>& action_string_args) override;
    std::vector<Switch4Action> getLegalActions() const override;
    bool isLegalAction(const Switch4Action& action) const override;
    bool isTerminal() const override;
    float getReward() const override { return 0.0f; }
    float getEvalScore(bool is_resign = false) const override;
    std::vector<float> getFeatures(utils::Rotation rotation = utils::Rotation::kRotationNone) const override;
    std::vector<float> getActionFeatures(const Switch4Action& action, utils::Rotation rotation = utils::Rotation::kRotationNone) const override;
    inline int getNumInputChannels() const override { return 4; }
    inline int getPolicySize() const override { return getBoardSize() * getBoardSize(); }
    std::string toString() const override;
    inline std::string name() const override { return kSwitch4Name; }
    inline int getNumPlayer() const override { return kSwitch4NumPlayer; }
    inline int getRotatePosition(int position, utils::Rotation rotation) const override { return utils::getPositionByRotating(rotation, position, getBoardSize()); };
    inline int getRotateAction(int action_id, utils::Rotation rotation) const override { return getRotatePosition(action_id, rotation); };
    static void setUpEnv() { config::env_board_size = 3; }

private:
    Player eval() const;

    std::vector<Player> board_;
};

class Switch4EnvLoader : public MultiAgentEnvLoader<Switch4Action, Switch4Env> {
public:
    std::vector<float> getActionFeatures(const int pos, utils::Rotation rotation = utils::Rotation::kRotationNone) const override;
    inline std::vector<float> getValue(const int pos) const { return {getReturn()}; }
    inline std::string name() const override { return kSwitch4Name; }
    inline int getPolicySize() const override { return getBoardSize() * getBoardSize(); }
    inline int getRotatePosition(int position, utils::Rotation rotation) const override { return utils::getPositionByRotating(rotation, position, getBoardSize()); };
    inline int getRotateAction(int action_id, utils::Rotation rotation) const override { return getRotatePosition(action_id, rotation); };
};

} // namespace minizero::env::Switch4
