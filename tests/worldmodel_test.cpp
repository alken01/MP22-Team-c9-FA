// #include "worldmodel.h"
// #include "xenemy.h"
// #include <iostream>
// #include "gtest/gtest.h"

// // Test fixture for WorldModel tests
// class WorldModelTest : public ::testing::Test {
//     protected:
//         // This function will be called before each test case
//         void SetUp() override { createSampleWorld(mapIndex); }

//         void TearDown() override {}

//         void createSampleWorld(int mapIndex) {
//             QString init_worldmap = getMapPath(mapList[mapIndex]);
//             std::shared_ptr<World> world = std::make_shared<World>();
//             world->createWorld(init_worldmap, ENEMY_NR, HEALTHPACK_NR, P_RATIO);
//             worldModel = std::make_shared<WorldModel>(world, XENEMY_NR);
//         }

//         QString getMapPath(QString mapName) {
//             return mapPath + mapName + ".png";
//         }

//         // Test members
//         std::shared_ptr<WorldModel> worldModel;
//         QString mapPath = ":/resources/world_images/";

//         QStringList mapList = {"maze1", "maze2", "maze3", "worldmap",
//                                "worldmap4"};
//         int mapIndex = 0;
//         const unsigned int ENEMY_NR = 5;
//         const unsigned int HEALTHPACK_NR = 5;
//         const float P_RATIO = 0.25f;
//         const unsigned int XENEMY_NR = 3;
// };

// // TEST_F(WorldModelTest, TileGenerationWithDifferentMaps) {
//     // for (int i = 0; i < mapList.size(); ++i) {
//     //     mapIndex = i;  // Set the mapIndex to the current index
//     //     SetUp();

//     //     // Check if tiles are initialized
//     //     for (const auto& tile : worldModel->getTiles()) {
//     //         const Tile::Coordinates& coords = tile->getCoordinates();
//     //         ASSERT_NE(worldModel->getWorldMap()[coords.xPos][coords.yPos],
//     //                   nullptr);
//     //     }
//     //     //  Check if healthpacks are initialized
//     //     for (const auto& healthPack : worldModel->getHealthPacks()) {
//     //         const Tile::Coordinates& coords = healthPack->getCoordinates();
//     //         ASSERT_NE(worldModel->getWorldMap()[coords.xPos][coords.yPos],
//     //                   nullptr);
//     //     }

//     //     // Check if enemies are initialized
//     //     for (const auto& enemy : worldModel->getEnemies()) {
//     //         const Tile::Coordinates& coords = enemy->getCoordinates();
//     //         ASSERT_NE(worldModel->getWorldMap()[coords.xPos][coords.yPos],
//     //                   nullptr);
//     //     }

//     //     // Check if protagonist is initialized
//     //     const auto& protagonist = worldModel->getProtagonist();
//     //     const Tile::Coordinates& coords = protagonist->getCoordinates();
//     //     ASSERT_NE(worldModel->getWorldMap()[coords.xPos][coords.yPos], nullptr);
//     // }
// // }

// // Test world generation with different maps
// TEST_F(WorldModelTest, ProtagonistGenerationWithDifferentMaps) {
//     for (int i = 0; i < mapList.size(); ++i) {
//         mapIndex = i;  // Set the mapIndex to the current index
//         SetUp();
//         ASSERT_NE(worldModel->getProtagonist(), nullptr);
//     }
// }


// TEST_F(WorldModelTest, XEnemyWorldGeneration) {
//     for (int i = 0; i < mapList.size(); ++i) {
//         mapIndex = i;
//         SetUp();
//         unsigned int XEnemyCount = 0;
//         for (const auto& enemy : worldModel->getEnemies())
//             if (std::dynamic_pointer_cast<XEnemy>(enemy)) XEnemyCount++;
//         ASSERT_EQ(XEnemyCount, XENEMY_NR);
//     }
// }

// TEST_F(WorldModelTest, NormalTileType) {
//     Tile normalTile(0, 0, 1.0f);
//     EXPECT_EQ(normalTile.getTileType(), Tile::NormalTile);
// }

// TEST_F(WorldModelTest, WallType) {
//     Tile wallTile(1, 1, INFINITY);
//     EXPECT_EQ(wallTile.getTileType(), Tile::Wall);
// }

// TEST_F(WorldModelTest, HealthpackType) {
//     Tile healthpackTile(2, 2, 2.5f);
//     EXPECT_EQ(healthpackTile.getTileType(), Tile::Healthpack);
// }

// TEST_F(WorldModelTest, ConsumedHealthpackType) {
//     Tile consumedHealthpackTile(3, 3, -1.0f);
//     EXPECT_EQ(consumedHealthpackTile.getTileType(), Tile::ConsumedHealthpack);
// }

// TEST_F(WorldModelTest, EnemyType) {
//     Enemy enemy(4, 4, 10.0f);
//     EXPECT_EQ(enemy.getTileType(), Tile::Enemy);
// }

// TEST_F(WorldModelTest, PEnemyType) {
//     PEnemy pEnemy(5, 5, 15.0f);
//     EXPECT_EQ(pEnemy.getTileType(), Tile::PEnemy);
// }

// TEST_F(WorldModelTest, XEnemyType) {
//     XEnemy xEnemy(6, 6, 20.0f);
//     EXPECT_EQ(xEnemy.getTileType(), Tile::XEnemy);
// }

// TEST_F(WorldModelTest, DefeatedEnemyType) {
//     Enemy defeatedEnemy(7, 7, -1.0f);
//     EXPECT_EQ(defeatedEnemy.getTileType(), Tile::DefeatedEnemy);
// }

// TEST_F(WorldModelTest, ProtagonistType) {
//     Protagonist protagonist;
//     EXPECT_EQ(protagonist.getTileType(), Tile::Protagonist);
// }
