//google test:
#include <gtest/gtest.h>
#include <gmock/gmock.h>
//lang:
#include <aio_lang/aio_types/aio_types.h>
//parsing:
#include <aio_parsing/aio_expression/aio_expression_parser.h>
//runtime:
#include <aio_runtime/aio_value/aio_value.h>
#include <aio_runtime/aio_value/advanced_functions/compare_aio_value.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

static str_hook *input_expression = nullptr;

static aio_value *actual_value = nullptr;

class aio_parser_test : public testing::Test {

protected:

    static void TearDownTestCase() {
        str_hook *old_input_expression = input_expression;
        aio_value *old_actual_value = actual_value;
        input_expression = nullptr;
        actual_value = nullptr;
        delete old_input_expression;
        delete old_actual_value;
    }
};

TEST_F(aio_parser_test, trivial_int) {
    input_expression = new str_hook("20+5");
    actual_value = aio_expression_parser::parse(input_expression, nullptr);
    ASSERT_TRUE(25 == actual_value->get.int_acc);
}

TEST_F(aio_parser_test, medium_int) {
    input_expression = new str_hook("20+5.0");
    actual_value = aio_expression_parser::parse(input_expression, nullptr);
    ASSERT_TRUE(25 == actual_value->get.int_acc);
}

TEST_F(aio_parser_test, hard_int) {
    input_expression = new str_hook("(20+5.0-'2'+true)%10");
    actual_value = aio_expression_parser::parse(input_expression, nullptr);
    ASSERT_TRUE(4 == actual_value->get.int_acc);
}

TEST_F(aio_parser_test, trivial_double) {
    input_expression = new str_hook("20.0-'5'+2");
    actual_value = aio_expression_parser::parse(input_expression, nullptr);
    ASSERT_TRUE(17.0 == actual_value->get.double_acc);
}

TEST_F(aio_parser_test, medium_double) {
    input_expression = new str_hook("(17.0-'2'+true)/2.0");
    actual_value = aio_expression_parser::parse(input_expression, nullptr);
    ASSERT_TRUE(8.0 == actual_value->get.double_acc);
}

TEST_F(aio_parser_test, hard_double) {
    input_expression = new str_hook("((17-'2'+true)~'0')/2.0");
    actual_value = aio_expression_parser::parse(input_expression, nullptr);
    ASSERT_TRUE(80.0 == actual_value->get.double_acc);
}

TEST_F(aio_parser_test, trivial_string) {
    input_expression = new str_hook("'0.'~5");
    actual_value = aio_expression_parser::parse(input_expression, nullptr);
    ASSERT_TRUE(strcmp("0.5", actual_value->get.string_acc) == 0);
}

TEST_F(aio_parser_test, trivial_boolean) {
    input_expression = new str_hook("'0'<5");
    actual_value = aio_expression_parser::parse(input_expression, nullptr);
    ASSERT_TRUE(actual_value->get.boolean_acc);
}

TEST_F(aio_parser_test, medium_boolean) {
    input_expression = new str_hook("'0'<5&5<8.0");
    actual_value = aio_expression_parser::parse(input_expression, nullptr);
    ASSERT_TRUE(actual_value->get.boolean_acc);
}

TEST_F(aio_parser_test, hard_boolean) {
    input_expression = new str_hook("((17-'2'+true)~'0')/2.0==160.0-'80'");
    actual_value = aio_expression_parser::parse(input_expression, nullptr);
    ASSERT_TRUE(actual_value->get.boolean_acc);
}