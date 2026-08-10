// in ma_env.h, shared by every factorized env
static constexpr std::array<uint8_t, kMaxActionTokens> kTokenBits = {...};  // per env

int64_t encode(const std::array<int16_t, kMaxActionTokens>& t) {
    int64_t id = 0, shift = 0;
    for (size_t i = 0; i < kMaxActionTokens; ++i) {
        id |= static_cast<int64_t>(t[i] + 1) << shift;   // +1 so 0 means "absent"
        shift += kTokenBits[i];
    }
    return id;
}