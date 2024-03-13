#include "diamond.hpp"

std::vector<std::vector<int>> Diamond::grid = {
    {0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0}
};



Diamond::Diamond(Vector2 position)
{
    this -> position = position;

    for(unsigned int row = 0; row < grid.size(); ++row) {
        for(unsigned int column = 0; column < grid[0].size(); ++column){
            if(grid[row][column] == 1) {
                //multiply pos by tile size to get the exact coordinates
                float pos_x = position.x + column * 4;
                float pos_y = position.y + row * 4;
                Tile tile = Tile({pos_x, pos_y});
                tiles.push_back(tile);
            }
        }
    }
}

void Diamond::Draw() {
    for(auto& tile: tiles) {
        tile.Draw();
    }
}