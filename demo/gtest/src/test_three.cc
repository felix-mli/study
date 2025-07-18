#include "gtest/gtest.h"

/*
    TEST和TEST_F有什么区别？

        TEST(TestSuiteName, TestName) {
            // 测试代码
        }
        1. 每一个TEST是完全独立的，不共享任何的状态和数据。测试直接不会影响。
        2. 无fixture(夹具)，不需要setup/teardown(初始化/清理)逻辑
        适合测试​​无状态​​或​​不需要复杂初始化​​的功能。

        TEST_F(TestFixtureName, TestName) {
            // 测试代码
        }
        1. 通过fixtrue(测试夹具类)共享setup和teardown逻辑和成员变量，所有TEST_F使用同一夹具类的实例，​​测试之间可以共享状态​​（需注意线程安全）。
        2. 夹具类可以定义 SetUp() 和 TearDown() 方法，在每个测试前后自动执行初始化和清理。
        3. 适合测试​​需要共享资源​​（如数据库连接、文件句柄）或​​依赖复杂初始化​​的功能。
*/

// 1. 定义夹具类
class DemoTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 在每个测试之前执行的初始化代码
        // 可以在这里设置共享资源或状态
        str = "Hello, World!";
    }

    void TearDown() override {
        // 在每个测试之后执行的清理代码
        // 可以在这里释放资源或重置状态
        str.clear();
    }

    std::string str; // 共享成员变量
};

// 2. 使用 TEST_F 定义测试用例
TEST_F(DemoTest, LengthTest) {
    EXPECT_EQ(str.length(), 11);  // 使用夹具中的 str
}

TEST_F(DemoTest, ContentTest) {
    EXPECT_NE(str.find("gtest"), std::string::npos);  // 共享同一 str
}