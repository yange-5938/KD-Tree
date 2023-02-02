#include "helper.h"


// this method creats a KD-Tree and it inserts all the points from the file to the tree
std::unique_ptr<KDTree> createKDTreeFromFile(std::string file_name, int dim)
{
    auto tree = std::make_unique<KDTree>(dim);
    std::string line;
    std::ifstream my_file(file_name);
    int x, y;
    while (std::getline(my_file, line))
    {
        std::replace(line.begin(), line.end(), ',', ' ');
        std::stringstream line_stream(line);

        line_stream >> x >> y;

        tree->insert({x,
                      y});
    }
    return tree;
}
