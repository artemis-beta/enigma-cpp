#include "gtest/gtest.h"
#include "spdlog/spdlog.h"
#include "Enigma.hxx"

//TODO Use methods with varying parameters

TEST(EnigmaTest, TestReflectorConv)
{
    spdlog::set_level(spdlog::level::debug);
    const std::vector<int> rotors = {2, 3, 4};
    const char reflector_type = 'B';
    const char in_char = 'X';
    const std::string key = "CAT";


    _enigma_impl* impl = new _enigma_impl(rotors, reflector_type, EnigmaType::M3, true);
    spdlog::info("Testing Reflector Forward/Backward Conversion");

    // Set Rotors to Current Key

    impl->_set_rotor("left", key[0]);
    impl->_set_rotor("middle", key[1]);
    impl->_set_rotor("right", key[2]);

    const char out = impl->_get_reflector_conv(in_char);

    EXPECT_NE(out, in_char);

    const char back = impl->_get_reflector_conv(out);

    spdlog::debug("Key '{0}' - Running Reflector Setting: {1}        {2}  ----->  {3}  ------> {4}", key,
        std::string(1, reflector_type), std::string(1, in_char), std::string(1, out), std::string(1, back));
    
    EXPECT_EQ(in_char, back);
}

TEST(EnigmaTest, TestInterRotorConv)
{
    spdlog::set_level(spdlog::level::debug);
    const std::vector<int> rotors = {2, 3, 4};
    const char reflector_type = 'B';
    const char in_char = 'Y';
    const std::string key = "TRY";

    _enigma_impl* impl = new _enigma_impl(rotors, reflector_type, EnigmaType::M3, true);
    spdlog::info("Testing Inter-Rotor Conversion");

    // Set Rotors to Current Key

    impl->_set_rotor("left", key[0]);
    impl->_set_rotor("middle", key[1]);
    impl->_set_rotor("right", key[2]);

    const char out = impl->_get_inter_rotor_conv("left", "middle", in_char);

    EXPECT_NE(out, in_char);

    const char back = impl->_get_inter_rotor_conv("middle", "left", out);

    std::string rotor_list = "["+std::to_string(rotors[0])+", "+std::to_string(rotors[1]);
    rotor_list += ", "+std::to_string(rotors[2])+"]";

    spdlog::debug("Key '{0}' - Running Rotor Setting: {1}        {2}  ----->  {3}  ------> {4}", key, rotor_list, 
        std::string(1, in_char), std::string(1, out), std::string(1, back));

    EXPECT_EQ(in_char, back);
}

TEST(EnigmaTest, TestRotorConv)
{
    spdlog::set_level(spdlog::level::debug);
    const std::vector<int> rotors = {8, 1, 5};
    const char reflector_type = 'B';
    const char in_char = 'G';
    const std::string key = "YUM";

    _enigma_impl* impl = new _enigma_impl(rotors, reflector_type, EnigmaType::M3, true);
    spdlog::info("Testing Rotor Conversion");

    // Set Rotors to Current Key

    impl->_set_rotor("left", key[0]);
    impl->_set_rotor("middle", key[1]);
    impl->_set_rotor("right", key[2]);

    const char out = impl->_get_rotor_conv("middle", in_char);

    EXPECT_NE(out, in_char);

    const char back = impl->_get_rotor_conv_inv("middle", out);

    std::string rotor_list = "["+std::to_string(rotors[0])+", "+std::to_string(rotors[1]);
    rotor_list += ", "+std::to_string(rotors[2])+"]";

    spdlog::debug("Key '{0}' - Running Rotor Setting: {1}        {2}  ----->  {3}  ------> {4}", key, rotor_list, 
        std::string(1, in_char), std::string(1, out), std::string(1, back));

    EXPECT_EQ(in_char, back);
}

TEST(EnigmaTest, TestEnigmaM3Encoding)
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Testing Enigma M3 Machine");
    const std::vector<int> rotors = {4, 3, 2};
    const char reflector_type = 'C';
    const std::string key = "OUY";
    const std::string phrase = "NOBODYEXPECTSTHESPANISHINQUISITION";
    Enigma* machine = new Enigma(rotors, reflector_type, EnigmaType::M3, true);
    spdlog::debug("Encrypting '{0}'", phrase);
    machine->set_key(key);
    const std::string result = machine->type_phrase(phrase);
    spdlog::debug("Finding Original");
    machine = new Enigma(rotors, reflector_type, EnigmaType::M3, true);
    machine->set_key(key);
    std::string out = machine->type_phrase(result);
    out.erase(remove_if(out.begin(), out.end(), isspace), out.end()); // Undo 5 letter grouping
    const std::string orig = out.substr(0,phrase.size()); // Remove extra added chars in groupings
    spdlog::debug("Key '{0}' - Running Enigma: Phrase Conversion        {1}  ----->  {2}  ------> {3}", key, 
        phrase, result, orig);

    EXPECT_EQ(phrase, orig);

}

TEST(EnigmaTest, TestEnigmaM4Encoding)
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Testing Enigma M4 Machine");
    const std::vector<int> rotors = {4, 3, 2, 1};
    const char reflector_type = 'C';
    const std::string key = "MOAN";
    const std::string phrase = "SOTHATSCAPRICORNISIT";
    Enigma* machine = new Enigma(rotors, reflector_type, EnigmaType::M4, true);
    spdlog::debug("Encrypting '{0}'", phrase);
    machine->set_key(key);
    const std::string result = machine->type_phrase(phrase);
    spdlog::debug("Finding Original");
    machine = new Enigma(rotors, reflector_type, EnigmaType::M4, true);
    machine->set_key(key);
    std::string out = machine->type_phrase(result);
    out.erase(remove_if(out.begin(), out.end(), isspace), out.end()); // Undo 5 letter grouping
    const std::string orig = out.substr(0,phrase.size()); // Remove extra added chars in groupings
    spdlog::debug("Key '{0}' - Running Enigma: Phrase Conversion        {1}  ----->  {2}  ------> {3}", key, 
        phrase, result, orig);

    EXPECT_EQ(phrase, orig);

}

TEST(EnigmaTest, TestKeyCheck)
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Testing Key Validation");
    const std::string key = "BARN";
    Enigma* machine = new Enigma;
    EXPECT_ANY_THROW(machine->set_key(key));
}

TEST(EnigmaTest, TestRingStellungCheck)
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Checking Ringstellung feature");
    const std::string key = "URN";
    const std::vector<int> rotor_list = {4,2,7};
    const std::vector<int> ringstellung = {1,0,2};
    const std::vector<std::string> names = {"left", "middle", "right"};
    const char reflector_type = 'C';
    Enigma* machine = new Enigma(rotor_list, reflector_type, EnigmaType::M3, true);
    machine->set_key(key);

    for(unsigned int i{0}; i < rotor_list.size(); ++i)
    {
        machine->ringstellung(names[i], ringstellung[i]);
    }

    machine->set_key(key);

    const std::string phrase = "THISISATEST";

    const std::string result = machine->type_phrase(phrase);

    machine = new Enigma(rotor_list, reflector_type, EnigmaType::M3, true);
    machine->set_key(key);

    for(unsigned int i{0}; i < rotor_list.size(); ++i)
    {
        machine->ringstellung(names[i], ringstellung[i]);
    }

    std::string out = machine->type_phrase(result);
    out.erase(remove_if(out.begin(), out.end(), isspace), out.end());
    const std::string orig = out.substr(0,phrase.size());

    EXPECT_EQ(phrase, orig);
}