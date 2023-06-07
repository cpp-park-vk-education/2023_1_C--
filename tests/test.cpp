#include "TestDBManager.hpp"
#include "TestClientDBManager.hpp"
#include "TestRoomDBManager.hpp"

class DBManagersTest: public ::testing::Test{
protected:
    void SetUp() override {}

    void TearDown() override {}

    MockDBManager DBManager;
    MockClientDBManager clientDBManager;
    MockRoomDBManager roomDBManager;
};

TEST_F(DBManagersTest, RunDBManager) {
    EXPECT_CALL(DBManager, exec   (::testing::_));

    EXPECT_CALL(DBManager, connect(::testing::_));
}

TEST_F(DBManagersTest, RunClientDBManager) {
    EXPECT_CALL(clientDBManager, getClient     (::testing::_));

    EXPECT_CALL(clientDBManager, changeLogin   (::testing::_, ::testing::_));

    EXPECT_CALL(clientDBManager, changePassword(::testing::_, ::testing::_));

    EXPECT_CALL(clientDBManager, setFirstname  (::testing::_, ::testing::_));

    EXPECT_CALL(clientDBManager, setLastname   (::testing::_, ::testing::_));
}

TEST_F(DBManagersTest, RunRoomDBManager) {
    EXPECT_CALL(roomDBManager, getRoom             (::testing::_));

    EXPECT_CALL(roomDBManager, insertRoom          (::testing::_));

    EXPECT_CALL(roomDBManager, insertNewMessage    (::testing::_, ::testing::_));

    EXPECT_CALL(roomDBManager, getNewMessage       (::testing::_));

    EXPECT_CALL(roomDBManager, deleteRoom          (::testing::_));

    EXPECT_CALL(roomDBManager, renameRoom          (::testing::_, ::testing::_));

    EXPECT_CALL(roomDBManager, addClientToRoom     (::testing::_, ::testing::_));

    EXPECT_CALL(roomDBManager, deleteClientFromRoom(::testing::_, ::testing::_));

    EXPECT_CALL(roomDBManager, changeMessageContext(::testing::_, ::testing::_, ::testing::_));
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
