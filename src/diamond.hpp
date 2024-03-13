#pragma once
#include <vector>
#include "tile.hpp"

class Diamond {
    public:
        Diamond(Vector2 position);
        void Draw();
        Vector2 position;
        std::vector<Tile> tiles;
        static std::vector<std::vector<int>> grid;
    private:
};