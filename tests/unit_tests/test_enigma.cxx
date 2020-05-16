#include "gtest/gtest.h"
#include "Enigma.hxx"

TEST(EnigmaTest, TestReflectorConv)
{
    const std::vector<int> rotors = {2, 3, 4};
    const char reflector_type = 'B';
    const char in_char = 'X';

    _enigma_impl* impl = new _enigma_impl(rotors, reflector_type, "M3", true);

    const char back = impl->_get_reflector_conv(impl->_get_reflector_conv(in_char));
    
    EXPECT_EQ(in_char, back);
}