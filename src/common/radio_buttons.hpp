#pragma once

#include <cstdint>
#include <cstddef>
template <class T>
constexpr size_t RadioBtnCount() {
    return static_cast<size_t>(T::_last) - static_cast<size_t>(T::_first);
}

enum class RadioBtnLoadUnload : uint16_t {
    _first = 0,
    bt1 = _first,
    bt2,
    NoBtn, //usea sa both couat and no button clicked
    _last = NoBtn
};

extern const uint8_t RadioBtnLoadUnloadCounts[RadioBtnCount<RadioBtnLoadUnload>()];

enum class RadioBtnTest : uint16_t {
    _first = static_cast<uint16_t>(RadioBtnLoadUnload::_last) + 1,
    Test1 = _first,
    Test2,
    NoBtn, //usea sa both couat and no button clicked
    _last = NoBtn
};

extern const uint8_t RadioBtnTestCounts[RadioBtnCount<RadioBtnTest>()];

class RadioButtons {
    RadioButtons() = delete;

public:
    static uint8_t GetCount(RadioBtnLoadUnload bt) {
        return RadioBtnLoadUnloadCounts[static_cast<size_t>(bt)];
    }

    static uint8_t GetCount(RadioBtnTest bt) {
        return RadioBtnTestCounts[static_cast<size_t>(bt)];
    }

    //encode radio button and clicked index into int
    template <class T>
    static uint32_t Encode(T bt, uint8_t clicked_index) {
        if (clicked_index > 3)
            return -1; //button num is 0-3 (1 - 4 buttons)
        if (bt == T::NoBtn_Count)
            return -1; //count cannot be used
        if (clicked_index >= GetCount(bt))
            return -1; // this radio button does not have so many buttons
        return ((static_cast<uint32_t>(bt)) << 2) + uint32_t(clicked_index);
    }
};
