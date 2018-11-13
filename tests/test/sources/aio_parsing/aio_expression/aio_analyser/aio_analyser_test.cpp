//google test:
#include <gtest/gtest.h>
#include <gmock/gmock.h>
//lang:
#include <aio_lang/aio_types/aio_types.h>
//parsing:
#include <aio_parsing/aio_expression/aio_expression_parser.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

static str_hook *input_expression = nullptr;

static str_hook *expected_type = nullptr;

static str_hook *actual_type = nullptr;

class aio_analyser_test : public testing::Test {

protected:

    static void TearDownTestCase()
    {
        str_hook *old_input_expression = input_expression;
        str_hook *old_expected_type = expected_type;
        str_hook *old_actual_type = actual_type;
        input_expression = nullptr;
        expected_type = nullptr;
        actual_type = nullptr;
        delete old_input_expression;
        delete old_expected_type;
        delete old_actual_type;
    }
};

TEST_F(aio_analyser_test, trivial_int)
{
    input_expression = new str_hook("20+5");
    expected_type = new str_hook(INTEGER);
    actual_type = aio_expression_parser::aio_analyser::define_expression_type(input_expression, nullptr);
    ASSERT_TRUE(actual_type->equals_string(expected_type));
}

TEST_F(aio_analyser_test, medium_int)
{
    input_expression = new str_hook("(75.0-10)*20+5");
    expected_type = new str_hook(INTEGER);
    actual_type = aio_expression_parser::aio_analyser::define_expression_type(input_expression, nullptr);
    ASSERT_TRUE(actual_type->equals_string(expected_type));
}

TEST_F(aio_analyser_test, hard_int)
{
    input_expression = new str_hook("((75.0-10)*(20.0+5))*(8-'sss')+7-(14*5)");
    expected_type = new str_hook(INTEGER);
    actual_type = aio_expression_parser::aio_analyser::define_expression_type(input_expression, nullptr);
    ASSERT_TRUE(actual_type->equals_string(expected_type));
}

TEST_F(aio_analyser_test, trivial_string)
{
    input_expression = new str_hook("'a'~7");
    expected_type = new str_hook(STRING);
    actual_type = aio_expression_parser::aio_analyser::define_expression_type(input_expression, nullptr);
    ASSERT_TRUE(actual_type->equals_string(expected_type));
}

TEST_F(aio_analyser_test, medium_string)
{
    input_expression = new str_hook("(75.0-10)~'20'+5");
    expected_type = new str_hook(STRING);
    actual_type = aio_expression_parser::aio_analyser::define_expression_type(input_expression, nullptr);
    ASSERT_TRUE(actual_type->equals_string(expected_type));
}

TEST_F(aio_analyser_test, hard_string)
{
    input_expression = new str_hook("((75.0-10) > (20.0+5))*(8-'sss')~'7'~(14*5)");
    expected_type = new str_hook(STRING);
    actual_type = aio_expression_parser::aio_analyser::define_expression_type(input_expression, nullptr);
    ASSERT_TRUE(actual_type->equals_string(expected_type));
}

TEST_F(aio_analyser_test, trivial_double)
{
    input_expression = new str_hook("17.0*('10'~7)");
    expected_type = new str_hook(DOUBLE);
    actual_type = aio_expression_parser::aio_analyser::define_expression_type(input_expression, nullptr);
    ASSERT_TRUE(actual_type->equals_string(expected_type));
}

TEST_F(aio_analyser_test, medium_double)
{
    input_expression = new str_hook("(75.0-(75.0-10))-97.0");
    expected_type = new str_hook(DOUBLE);
    actual_type = aio_expression_parser::aio_analyser::define_expression_type(input_expression, nullptr);
    ASSERT_TRUE(actual_type->equals_string(expected_type));
}

TEST_F(aio_analyser_test, hard_double)
{
    input_expression = new str_hook("((75.0-10) > (20.0+5))*(8-'sss')+32.0*('5'~'7'~(14*5))");
    expected_type = new str_hook(DOUBLE);
    actual_type = aio_expression_parser::aio_analyser::define_expression_type(input_expression, nullptr);
    ASSERT_TRUE(actual_type->equals_string(expected_type));
}

TEST_F(aio_analyser_test, trivial_boolean)
{
    input_expression = new str_hook("true");
    expected_type = new str_hook(BOOLEAN);
    actual_type = aio_expression_parser::aio_analyser::define_expression_type(input_expression, nullptr);
    ASSERT_TRUE(actual_type->equals_string(expected_type));
}

TEST_F(aio_analyser_test, medium_boolean)
{
    input_expression = new str_hook("75.0 >= 5");
    expected_type = new str_hook(BOOLEAN);
    actual_type = aio_expression_parser::aio_analyser::define_expression_type(input_expression, nullptr);
    ASSERT_TRUE(actual_type->equals_string(expected_type));
}

TEST_F(aio_analyser_test, hard_boolean)
{
    input_expression = new str_hook("((75.0-10) > (20.0+5))*(8-'sss') & ('5'~'7'~(14*5))");
    expected_type = new str_hook(BOOLEAN);
    actual_type = aio_expression_parser::aio_analyser::define_expression_type(input_expression, nullptr);
    ASSERT_TRUE(actual_type->equals_string(expected_type));
}